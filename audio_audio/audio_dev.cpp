/*	$Id: audio_dev.c,v 1.15 2004/06/07 21:10:42 steve Exp $	*/

/*
 Command Line Front-end for Robert Leslie's `libmad' mp3 decoder.
 Copyright (C) 2001-2003 Steve Woodford.

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/
#include "framework.cpp"
#include <sys/types.h>
#include <sys/param.h>
#include <sys/fcntl.h>
#ifndef __linux__
#include <sys/filio.h>
#endif
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <mad.h>
#define NOARTS
#ifdef __sun
#include <sys/stropts.h>
#endif

#include "audio_dev.h"

#if (BYTE_ORDER == BIG_ENDIAN)
#define WORDS_BIGENDIAN
#else
#undef WORDS_BIGENDIAN
#endif

#ifdef __DragonFly__
typedef unsigned int nfds_t;
#endif

#define PCM_MAX_BUFFSIZE	2 * 4_KiB

struct pcm_data {
	int		pd_command;
	int		pd_nchannels;
	int		pd_rate;
	volatile size_t	pd_len;
	size_t		pd_bufpos;
	unsigned char	pd_buf[PCM_MAX_BUFFSIZE];
};

#define	PCM_NBUFFS	400
#define PCM_LOW_WATER   32
struct pcm_buffer {
	volatile int	pb_command;
	uint64_t	pb_playsamples;
	int		pb_rate;
	int		pb_nchannels;
	volatile int	pb_purge;
	volatile int	pb_head;
	volatile int	pb_tail;
	struct pcm_data	pb_buffers[PCM_NBUFFS];
};

struct audio_dev_ctx {
	pid_t		ac_slave_pid;
	const struct audio_dev_backend *ac_device;
	void		*ac_devarg;
	int		ac_paused;
	int		ac_peerread;
	int		ac_peerwrite;
	uint64_t	ac_buffersamples;
	void		(*ac_readcallback)(void *);
	void		*ac_cbarg;
	struct pcm_buffer *ac_pcm;
};

#define	ACF_NEW_TRACK	(1 << 0)

#define _ADC_QUIT	(-1)

static int	audio_dev_writepeer(struct audio_dev_ctx *);
static int	audio_dev_readpeer(struct audio_dev_ctx *);
static void	audio_dev_sigpipe(int);
static int	audio_dev_output(struct audio_dev_ctx *, struct pcm_data *);
static void	audio_dev_command(struct audio_dev_ctx *, int *);
static void	audio_dev_slave(const char *, struct audio_dev_ctx *);
//static inline signed long audio_linear_dither(unsigned int, mad_fixed_t,
//		    mad_fixed_t *);
//static void	audio_convert_dither(unsigned char *, unsigned int,
//		    mad_fixed_t const *, mad_fixed_t const *);


static const struct audio_dev_backend *audio_dev_backends[] = {
#ifndef NOSUN
	&audio_dev_sun,
#endif
#ifndef NOOSS
	&audio_dev_pcm,
#endif
#ifndef NOARTS
	&audio_dev_arts,
#endif
	NULL
};



static int
audio_dev_writepeer(struct audio_dev_ctx *ac)
{
	char foo;
	ssize_t rv;

	do
		rv = write(ac->ac_peerwrite, &foo, sizeof(foo));
	while (rv < 0 && errno == EINTR);

	return ((int) rv);
}

static int
audio_dev_readpeer(struct audio_dev_ctx *ac)
{
	char foo[PCM_NBUFFS];
	ssize_t rv;
	int rsize;

	if (ioctl(ac->ac_peerread, FIONREAD, &rsize) < 0)
		return (-1);

	if ((size_t)rsize > sizeof(foo))
		rsize = (int) sizeof(foo);
	else
	if (rsize == 0)
		return (0);

	while ((rv = read(ac->ac_peerread, foo, (size_t)rsize)) < 0 &&
	    errno == EINTR)
		;

	if (rv > 0 && ac->ac_readcallback)
		(ac->ac_readcallback)(ac->ac_cbarg);

	return ((int) rv);
}

static void
audio_dev_sigpipe(int arg)
{
	fprintf(stderr, "audio_dev_sigpipe: whoops!\n");
	fflush(stderr);
	_exit(1);
}

void *
audio_dev_init(const char *dev)
{
	struct audio_dev_ctx *ac;
	struct pcm_buffer *pb;
	int p1[2], p2[2], retry;
	pid_t pid;

	if ((ac = ___new audio_dev_ctx()) == NULL)
		return (NULL);

	pb = ac->ac_pcm = (pcm_buffer *) mmap(NULL, sizeof(*ac->ac_pcm),
	    PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	if (pb == NULL) {
		free(ac);
		return (NULL);
	}

	memset(pb, 0, sizeof(*ac->ac_pcm));

	if (pipe(p1) < 0) {
		munmap(pb, sizeof(*ac->ac_pcm));
		free(ac);
		return (NULL);
	}

	if (pipe(p2) < 0) {
		munmap(pb, sizeof(*ac->ac_pcm));
		free(ac);
		close(p1[0]);
		close(p1[1]);
		return (NULL);
	}

	if ((pid = fork()) == 0) {
		/* Child: Will write to audio device */
		ac->ac_peerread = p1[0];
		ac->ac_peerwrite = p2[1];
		close(p1[1]);
		close(p2[0]);
		audio_dev_slave(dev, ac);
		exit(0);
	} else
	if (pid > 0) {
		/* Parent */
		ac->ac_peerread = p2[0];
		ac->ac_peerwrite = p1[1];
		ac->ac_slave_pid = pid;
		close(p1[0]);
		close(p2[1]);
	} else {
		/* Error */
		munmap(pb, sizeof(*ac->ac_pcm));
		free(ac);
		close(p1[0]);
		close(p1[1]);
		close(p2[0]);
		close(p2[1]);
		return (NULL);
	}

	return (ac);
}

void
audio_dev_close(void *arg)
{
	struct audio_dev_ctx *ac = (audio_dev_ctx*)arg;
	int status;
	pid_t pid;

	if (audio_dev_send_command(arg, _ADC_QUIT, NULL, 1) == AD_NO_ERROR) {
		do
			pid = waitpid(ac->ac_slave_pid, &status, 0);
		while (pid < 0 && errno == EINTR);
	}

	(void) close(ac->ac_peerread);
	(void) close(ac->ac_peerwrite);
	(void) munmap(ac->ac_pcm, sizeof(*ac->ac_pcm));
	(void) free(ac);
}

void
audio_dev_register_read_callback(void *arg, void (*rcb)(void *), void *cbarg)
{
	struct audio_dev_ctx *ac = (audio_dev_ctx*) arg;

	ac->ac_readcallback = rcb;
	ac->ac_cbarg = cbarg;
}

int
audio_dev_send_command(void *arg, int cmd, int *pfd, int immed)
{
	struct audio_dev_ctx *ac = (audio_dev_ctx*) arg;
	struct pcm_buffer *pb = ac->ac_pcm;
	struct pcm_data *pd;
	int head;

	if (immed) {
		while (pb->pb_command) {
			if (pfd != NULL) {
				*pfd = ac->ac_peerread;
				return (AD_WOULD_BLOCK);
			}

			if (audio_dev_readpeer(ac) < 0)
				return (AD_ERROR);
		}

		pb->pb_command = cmd;

	} else {

		head = (pb->pb_head + 1) % PCM_NBUFFS;
		while (head == pb->pb_tail) {
			if (pfd != NULL) {
				*pfd = ac->ac_peerread;
				return (AD_WOULD_BLOCK);
			}

			if (audio_dev_readpeer(ac) < 0)
				return (AD_ERROR);
		}

		pd = &pb->pb_buffers[pb->pb_head];
		pd->pd_command = cmd;
		pd->pd_len = 0;
		pb->pb_head = head;
	}

	if (audio_dev_writepeer(ac) < 0)
		return (AD_ERROR);

	return (AD_NO_ERROR);
}

static int
audio_dev_output(struct audio_dev_ctx *ac, struct pcm_data *pd)
{
	unsigned char *buf;
	size_t len, played, written;
	ssize_t rv = 0;

	if (pd->pd_nchannels != ac->ac_pcm->pb_nchannels ||
	    pd->pd_rate != ac->ac_pcm->pb_rate) {

		if ((ac->ac_device->ad_config)(ac->ac_devarg, pd->pd_rate,
		    pd->pd_nchannels) < 0)
			return (-1);

		ac->ac_pcm->pb_nchannels = pd->pd_nchannels;
		ac->ac_pcm->pb_rate = pd->pd_rate;
	}

	written = 0;

	for (played = pd->pd_bufpos,buf = &pd->pd_buf[played], len = pd->pd_len;
	    len > 0; played += rv, written += rv, len -= rv, buf = &buf[rv]) {

		do {
			rv = (ac->ac_device->ad_output)(ac->ac_devarg,
			    buf, len);
		} while (rv < 0 && errno == EINTR);

		if (rv < 0 || (rv == 0 && ac->ac_device->ad_pollfd == NULL))
			break;
	}

	pd->pd_bufpos = played;
	pd->pd_len = len;

	written /= pd->pd_nchannels;
	written /= sizeof(uint16_t);
	ac->ac_pcm->pb_playsamples += written;

	return ((rv >= 0) ? 0 : -1);
}

static void
audio_dev_command(struct audio_dev_ctx *ac, int *cmdp)
{
	switch (*cmdp) {
	case _ADC_QUIT:
		(void) close(ac->ac_peerread);
		(void) close(ac->ac_peerwrite);
		(void) munmap(ac->ac_pcm, sizeof(*ac->ac_pcm));
		(ac->ac_device->ad_close)(ac->ac_devarg);
		(void) free(ac);
		_exit(1);
		/* NOTREACHED */

	case ADC_PAUSE:
		ac->ac_paused = 1 - ac->ac_paused;
		break;
	}

	*cmdp = 0;
}

void audio_dev_pause(void * arg)
{

	struct audio_dev_ctx *ac = (struct audio_dev_ctx *) ac;

	ac->ac_paused = true;

}

void audio_dev_unpause(void * arg)
{

	struct audio_dev_ctx *ac = (struct audio_dev_ctx *) ac;

	ac->ac_paused = false;

}

static void
audio_dev_slave(const char *dev, struct audio_dev_ctx *ac)
{
	struct pcm_buffer *pb = ac->ac_pcm;
	const struct audio_dev_backend *ad;
	struct pcm_data *pd;
	const char *ext;
	int rv, prodpeer = 0;
	struct pollfd fds[2];
	nfds_t nfds;

	if ((ext = strchr(dev, ':')) == NULL)
		ad = audio_dev_backends[0];
	else {
		int i;
		for (i = 0; (ad = audio_dev_backends[i]) != NULL; i++) {
			if (strncmp(ad->ad_name, dev, strlen(ad->ad_name)) == 0)
				break;
		}

		if (ad == NULL)
			ad = audio_dev_backends[0];
	}

	ac->ac_device = ad;
	if (ext != NULL)
		dev += strlen(ad->ad_name);
	ac->ac_devarg = (ad->ad_init)(dev);
	if (ac->ac_devarg == NULL) {
		perror("audio_dev_slave");
		fprintf(stderr, "audio_dev_slave: failed to open back-end\n");
		fflush(stderr);
		munmap(pb, sizeof(*ac->ac_pcm));
		free(ac);
		return;
	}

//	signal(SIGHUP, SIG_IGN);
//	signal(SIGINT, SIG_IGN);
//	signal(SIGWINCH, SIG_IGN);
	signal(SIGPIPE, audio_dev_sigpipe);

	for (;;) {
		while (pb->pb_head != pb->pb_tail && pb->pb_purge == 0) {
			int idx = pb->pb_tail;

			pd = &pb->pb_buffers[idx];

			if (pd->pd_command)
				audio_dev_command(ac, &pd->pd_command);

			if (!ac->ac_paused && pd->pd_len) {
				rv = audio_dev_output(ac, pd);
				if (rv < 0 && errno != EAGAIN) {
					perror("audio_slave: audio_dev_output");
					return;
				}
			}

			if (pd->pd_len != 0)
				break;

			pb->pb_tail = (idx + 1) % PCM_NBUFFS;
			prodpeer = 1;
		}

		if (pb->pb_purge) {
			pb->pb_purge = 0;
			pb->pb_tail = pb->pb_head;
			prodpeer = 1;
		}

		if (prodpeer) {
			prodpeer = 0;
			if (audio_dev_writepeer(ac) < 0) {
				perror("audio_slave: peer write");
				return;
			}
		}

		do {
			fds[0].fd = ac->ac_peerread;
			fds[0].happenings = POLLRDNORM;
			fds[0].revents = 0;
			nfds = 1;

			if (ac->ac_device->ad_pollfd != NULL &&
			    !ac->ac_paused && pb->pb_head != pb->pb_tail) {
				fds[1].fd =
				    (ac->ac_device->ad_pollfd)(ac->ac_devarg);
				fds[1].happenings = POLLWRNORM;
				fds[1].revents = 0;
				nfds++;
			}

			while ((rv = poll(fds, nfds, AD_HEARTBEAT)) < 0 &&
			    errno == EINTR)
				;

			if (rv < 0) {
				perror("audio_slave: poll");
				return;
			}

			if (rv == 0) {
				if (audio_dev_writepeer(ac) < 0)
					return;
			} else
			if ((fds[0].revents & POLLRDNORM) != 0) {
				if (audio_dev_readpeer(ac) <= 0)
					return;
			}

			if (pb->pb_command) {
				int z = pb->pb_command;
				audio_dev_command(ac, &z);
				pb->pb_command = 0;
			}

		} while (ac->ac_paused && pb->pb_head == pb->pb_tail);
	}
}


//int
//audio_dev_write(void *arg, struct mad_header const *mhead,
//	struct mad_pcm *mpcm, int *pfd, void *pcmdata, int samplecount, int nchannels, int samplerate)
int audio_dev_write(void *arg, void *pcmdata, int samplecount, int nchannels, int samplerate, int *pfd)
{
	struct audio_dev_ctx *ac = (audio_dev_ctx*) arg;
	struct pcm_buffer *pb = ac->ac_pcm;
	struct pcm_data *pd;
	int head, tail, nbufs;

	head = (pb->pb_head + 1) % PCM_NBUFFS;
	while (head == pb->pb_tail) {
		if (pfd != NULL) {
			*pfd = ac->ac_peerread;
			return (AD_WOULD_BLOCK);
		}

		if (audio_dev_readpeer(ac) < 0)
			return (AD_ERROR);
	}

	pd = &pb->pb_buffers[pb->pb_head];

//	audio_convert_dither(pd->pd_buf, mpcm->length, mpcm->samples[0],
//	    (MAD_NCHANNELS(mhead) == 1) ? NULL : mpcm->samples[1]);

	pd->pd_command = 0;
	pd->pd_nchannels = nchannels;
//#if defined(MAD_VERSION_MINOR) && (MAD_VERSION_MINOR > 12)
//	pd->pd_rate = mhead->samplerate;
//#else
//	pd->pd_rate = 44100;
//#endif
        pd->pd_rate = samplerate;
	pd->pd_bufpos = 0;
//	pd->pd_len = mpcm->length * (MAD_NCHANNELS(mhead) * 2);
	pd->pd_len = samplecount * nchannels * 2;
	pb->pb_head = head;
	tail = pb->pb_tail;

	nbufs = head - tail;
	if (nbufs < 0)
		nbufs += PCM_NBUFFS;

	if (nbufs > PCM_LOW_WATER && audio_dev_writepeer(ac) < 0)
		return AD_ERROR;

	ac->ac_buffersamples += samplecount;

	return (AD_NO_ERROR);
}

int
audio_dev_flush_wait(void *arg)
{
	struct audio_dev_ctx *ac = (audio_dev_ctx*) arg;
	struct pcm_buffer *pb = ac->ac_pcm;
	struct pollfd infd;
	int rv;

	if (audio_dev_writepeer(ac) < 0)
		return (AD_ERROR);

	while (pb->pb_head != pb->pb_tail) {
		infd.fd = ac->ac_peerread;
		infd.happenings = POLLRDNORM;
		infd.revents = 0;

		while ((rv = poll(&infd, 1, INFTIM)) < 0 && errno == EINTR)
			;

		if (rv < 0 || audio_dev_readpeer(ac) < 0)
			return (AD_ERROR);
	}

	ac->ac_buffersamples = ac->ac_pcm->pb_playsamples = 0;

	return (AD_NO_ERROR);
}

int
audio_dev_purge_wait(void *arg)
{
	struct audio_dev_ctx *ac =(audio_dev_ctx*)  arg;
	struct pcm_buffer *pb = ac->ac_pcm;
	struct pollfd infd;
	int rv;

	pb->pb_purge = 1;

	if (audio_dev_writepeer(ac) < 0)
		return (AD_ERROR);

	while (pb->pb_head != pb->pb_tail && pb->pb_purge) {
		infd.fd = ac->ac_peerread;
		infd.happenings = POLLRDNORM;
		infd.revents = 0;

		while ((rv = poll(&infd, 1, INFTIM)) < 0 && errno == EINTR)
			;

		if (rv < 0 || audio_dev_readpeer(ac) < 0)
			return (AD_ERROR);
	}

	ac->ac_buffersamples = ac->ac_pcm->pb_playsamples = 0;

	return (AD_NO_ERROR);
}

int
audio_dev_buffer_time(void *arg)
{
	struct audio_dev_ctx *ac = (audio_dev_ctx*) arg;
	u_int diff;

	if (ac->ac_pcm->pb_rate) {
		diff = ac->ac_buffersamples - ac->ac_pcm->pb_playsamples;

		return ((diff * 10) / ac->ac_pcm->pb_rate);
	}

	return (0);
}

int
audio_dev_played_time(void *arg)
{
	struct audio_dev_ctx *ac = (audio_dev_ctx*) arg;

	if (ac->ac_pcm->pb_rate)
		return ((ac->ac_pcm->pb_playsamples * 10) /ac->ac_pcm->pb_rate);
	else
		return (0);
}
