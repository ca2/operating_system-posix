/*	$Id: audio_dev_sun.c,v 1.1 2003/10/07 08:21:24 steve Exp $	*/

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
#include "framework.h"
#include "wave_out.h"

#include <sys/types.h>
#include <sys/param.h>
#include <sys/audioio.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
static void *ad_sun_init(const_char_pointer );
static void ad_sun_close(void *);
static int ad_sun_config(void *, int, int, int lowat, int hiwat);
static ssize_t ad_sun_output(void *, void *, size_t);
static int ad_sun_pollfd(void *);


namespace multimedia
{


   namespace audio_audio
   {


const struct audio_dev_backend audio_dev_sun = {
	"sun:",
	ad_sun_init,
	ad_sun_close,
	ad_sun_config,
	ad_sun_output,
	ad_sun_pollfd
};

} }

struct sun_ctx {
	int sc_fd;
};

static void *
ad_sun_init(const_char_pointer dev)
{
	struct sun_ctx *sc;
	int retry, fd = -1;

	if ((sc = (sun_ctx *) calloc(1, sizeof(*sc))) == NULL)
		return (NULL);

	sc->sc_fd = -1;
	for (retry = 0; retry < 3 && sc->sc_fd < 0; retry++) {
		if ((sc->sc_fd = open(dev, O_WRONLY | O_NONBLOCK)) < 0) {
			if (errno != EBUSY) {
				free(sc);
				return (NULL);
			}
			sleep(1);
		}
	}

	if (sc->sc_fd < 0) {
		free(sc);
		return (NULL);
	}

	return (sc);
}

static void
ad_sun_close(void *arg)
{
	struct sun_ctx *sc = (sun_ctx*) arg;

	close(sc->sc_fd);
	free(sc);
}

static int
ad_sun_config(void *arg, int rate, int channels, int lowat, int hiwat)
{
	struct sun_ctx *sc =  (sun_ctx*)arg;
	audio_info_t ai;

	AUDIO_INITINFO(&ai);

	ai.play.channels = channels;
	ai.play.sample_rate = rate;
	ai.play.precision = 16;
	ai.play.encoding = AUDIO_ENCODING_LINEAR;
	ai.hiwat = hiwat;
	ai.lowat = lowat;
	ai.blocksize = 4608;

	if (ioctl(sc->sc_fd, AUDIO_DRAIN, 0) < 0)
		return (-1);

	if (ioctl(sc->sc_fd, AUDIO_SETINFO, &ai) < 0)
		return (-1);

	return (0);
}

static ssize_t
ad_sun_output(void *arg, void *pcmbuff, size_t len)
{
	struct sun_ctx *sc =  (sun_ctx*)arg;

	return (write(sc->sc_fd, pcmbuff, len));
}

static int
ad_sun_pollfd(void *arg)
{
	struct sun_ctx *sc = (sun_ctx*) arg;

	return (sc->sc_fd);
}
