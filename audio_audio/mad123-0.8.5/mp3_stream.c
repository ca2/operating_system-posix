/*	$Id: mp3_stream.c,v 1.16 2004/10/21 09:11:42 steve Exp $	*/

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

#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef NOCURL
#include <curl/curl.h>
#endif
#ifndef NOTAGLIB
#include <taglib/tag_c.h>
#else
#ifndef NOID3LIB
#include <id3.h>
#endif
#endif /* NOTAGLIB */
#include <unistd.h>	/* Move *after* curl.h, 'cos it's braindamaged */

#ifdef __sun
#define madvise posix_madvise
#define MAP_FILE 0
#endif

#include "mp3_stream.h"

static void	*mps_file_open(const char *, int);
static void	mps_file_close(void *);
static ssize_t	mps_file_read(void *, void *, size_t);
static long	mps_file_seek(void *, long, int);
static char	*mps_file_id3(void *, enum mp3_stream_id3tag);

static void	*mps_mmap_open(const char *, int);
static void	mps_mmap_close(void *);
static ssize_t	mps_mmap_read(void *, void *, size_t);
static long	mps_mmap_seek(void *, long, int);
static char	*mps_mmap_id3(void *, enum mp3_stream_id3tag);

#ifndef NOCURL
static void	*mps_url_open(const char *, int);
static void	mps_url_close(void *);
static ssize_t	mps_url_read(void *, void *, size_t);
static void	mps_url_spawn_reader(const char *, int);
static size_t	mps_url_writer(void *, size_t, size_t, FILE *);
#endif

struct mp3_stream {
	const char	*mps_name;
	void *		(*mps_open)(const char *, int);
	void		(*mps_close)(void *);
	ssize_t		(*mps_read)(void *, void *, size_t);
	long		(*mps_seek)(void *, long, int);
	char *		(*mps_id3)(void *, enum mp3_stream_id3tag);
};

static struct mp3_stream stream_handlers[] = {
	{"file:/", mps_file_open, mps_file_close,
	           mps_file_read, mps_file_seek, mps_file_id3},
	{"mmap:/", mps_mmap_open, mps_mmap_close,
	           mps_mmap_read, mps_mmap_seek, mps_mmap_id3},
#ifndef NOCURL
	{"http://", mps_url_open, mps_url_close,
	           mps_url_read, NULL, NULL}
#endif
};
#define NHANDLERS	(sizeof(stream_handlers) / sizeof(struct mp3_stream))

struct mp3_stream_ctx {
	struct mp3_stream	*sc_mps;
	void			*sc_arg;
	unsigned char		*sc_buff;
	size_t			sc_buffsize;
	size_t			sc_buffidx;
	size_t			sc_buffdsize;
	size_t			sc_bufflowat;
	size_t			sc_buffhiwat;
	int			sc_buffrefill;
	int			sc_buffeof;
};

struct id3_tag_ctx {
	const char	*id3_path;
#ifndef NOTAGLIB
	TagLib_File	*id3_file;
	TagLib_Tag	*id3_tag;
#else
#ifndef NOID3LIB
	ID3Tag		*id3_tag;
#endif
#endif
};

#if !(defined(NOID3LIB) && defined(NOTAGLIB))
static void	id3_tag_init(struct id3_tag_ctx *, const char *);
static void	id3_tag_delete(struct id3_tag_ctx *);
static const char *id3_tag_lookup(struct id3_tag_ctx *, enum mp3_stream_id3tag);
#endif


void *
mp3_stream_open(const char *path, int buffsize, int stdin_ok)
{
	struct mp3_stream_ctx *sc;
	struct mp3_stream *mps;
	const char *ext;
	int i;

	if ((ext = strchr(path, ':')) == NULL || strcmp(path, "-") == 0)
		mps = &stream_handlers[0];
	else {
		for (i = 0, mps = &stream_handlers[0];
		    i < NHANDLERS; i++, mps++) {
			if (strncmp(mps->mps_name, path,
			    strlen(mps->mps_name)) == 0)
				break;
		}

		if (i >= NHANDLERS)
			mps = &stream_handlers[0];
	}

	if ((sc = calloc(1, sizeof(*sc))) == NULL)
		return (NULL);

	sc->sc_mps = mps;

	if (buffsize >= (MP3_STREAM_DBL_BUFF_SIZE * 3)) {
		if ((sc->sc_buff = malloc(buffsize)) == NULL) {
			free(sc);
			return (NULL);
		}

		sc->sc_buffsize = (size_t) buffsize;
		sc->sc_bufflowat = MP3_STREAM_DBL_BUFF_SIZE;
		sc->sc_buffhiwat = buffsize - MP3_STREAM_DBL_BUFF_SIZE;
	}

	if ((sc->sc_arg = (mps->mps_open)(path, stdin_ok)) == NULL) {
		if (sc->sc_buff)
			free(sc->sc_buff);
		free(sc);
		return (NULL);
	}

	return (sc);
}

void
mp3_stream_close(void *arg)
{
	struct mp3_stream_ctx *sc = arg;

	(sc->sc_mps->mps_close)(sc->sc_arg);
	if (sc->sc_buff)
		free(sc->sc_buff);
	free(sc);
}

ssize_t
mp3_stream_read(void *arg, void *buf, size_t len, int read_ahead_ok)
{
	struct mp3_stream_ctx *sc = arg;
	ssize_t rv;
	size_t dleft;

	if (sc->sc_buff == NULL)
		return ((sc->sc_mps->mps_read)(sc->sc_arg, buf, len));

	dleft = sc->sc_buffdsize - sc->sc_buffidx;
	if ((sc->sc_buffrefill || dleft <= sc->sc_bufflowat) &&
	    !sc->sc_buffeof) {

		if (sc->sc_buffrefill == 0) {
			sc->sc_buffdsize -= sc->sc_buffidx;
			memmove(sc->sc_buff, &sc->sc_buff[sc->sc_buffidx],
			    sc->sc_buffdsize);
			sc->sc_buffidx = 0;
		}

		sc->sc_buffrefill = 1;

		if (read_ahead_ok)
			rv = sc->sc_buffsize - sc->sc_buffdsize;
		else
			rv = len;

		if (rv > 0) {
			rv = (sc->sc_mps->mps_read)(sc->sc_arg,
			    &sc->sc_buff[sc->sc_buffdsize],
			    (rv > MP3_STREAM_DBL_BUFF_SIZE) ?
			    MP3_STREAM_DBL_BUFF_SIZE : rv);

			if (rv < 0)
				return (rv);

			if (rv == 0)
				sc->sc_buffeof = 1;

			sc->sc_buffdsize += rv;
		}

		if (sc->sc_buffdsize > sc->sc_buffhiwat)
			sc->sc_buffrefill = 0;
	}

	dleft = sc->sc_buffdsize - sc->sc_buffidx;

	if ((rv = (len < dleft) ? len : dleft) != 0) {
		memcpy(buf, &sc->sc_buff[sc->sc_buffidx], rv);
		sc->sc_buffidx += rv;
	}

	return (rv);
}

long
mp3_stream_seek(void *arg, long where, int whence)
{
	struct mp3_stream_ctx *sc = arg;

	if (sc->sc_mps->mps_seek == NULL) {
		errno = ESPIPE;
		return (-1);
	}

	if (sc->sc_buff != NULL)
		sc->sc_buffdsize = sc->sc_buffidx = 0;

	return ((sc->sc_mps->mps_seek)(sc->sc_arg, where, whence));
}

int
mp3_stream_id3(void *arg, enum mp3_stream_id3tag tag, char **value)
{
#if !(defined(NOID3LIB) && defined(NOTAGLIB))
	struct mp3_stream_ctx *sc = arg;

	if (sc->sc_mps->mps_id3 == NULL) {
		errno = ESPIPE;
		return (-1);
	}

	*value = (sc->sc_mps->mps_id3)(sc->sc_arg, tag);
	return (0);
#else
	return (-1);
#endif
}

int
mp3_stream_read_ahead_size(void *arg)
{
	struct mp3_stream_ctx *sc = arg;
	size_t dleft;
	int quot, rem;

	if (sc->sc_buffsize) {
		dleft = sc->sc_buffdsize - sc->sc_buffidx;

		quot = (dleft * 100) / sc->sc_buffsize;
		rem = (dleft * 100) % sc->sc_buffsize;

		return ((rem > (sc->sc_buffsize / 2)) ? quot + 1 : quot);
	}

	return (0);
}

struct file_stream {
	FILE			*fs_fp;
#if !(defined(NOID3LIB) && defined(NOTAGLIB))
	char			*fs_str;
	struct id3_tag_ctx	fs_id3;
#endif
};

static void *
mps_file_open(const char *path, int stdin_ok)
{
	struct file_stream *fs;

	if (strncmp("file:/", path, 6) == 0)
		path += 5;

	if ((fs = calloc(1, sizeof(*fs))) == NULL)
		return (NULL);

	if (stdin_ok == 0 || strcmp(path, "-") != 0) {
		if ((fs->fs_fp = fopen(path, "rb")) == NULL) {
			free(fs);
			return (NULL);
		}
#if !(defined(NOID3LIB) && defined(NOTAGLIB))
		id3_tag_init(&fs->fs_id3, path);
#endif
	} else {
		fs->fs_fp = stdin;
#if !(defined(NOID3LIB) && defined(NOTAGLIB))
		id3_tag_init(&fs->fs_id3, NULL);
#endif
	}

	return ((void *) fs);
}

static void
mps_file_close(void *arg)
{
	struct file_stream *fs = arg;

#if !(defined(NOID3LIB) && defined(NOTAGLIB))
	id3_tag_delete(&fs->fs_id3);

	if (fs->fs_str)
		free(fs->fs_str);
#endif

	if (fs->fs_fp != stdin)
		fclose(fs->fs_fp);

	free(fs);
}

static ssize_t
mps_file_read(void *arg, void *buf, size_t len)
{
	struct file_stream *fs = arg;
	ssize_t rv;

	rv = fread(buf, 1, len, fs->fs_fp);

	if (rv == 0 && ferror(fs->fs_fp))
		rv = -1;

	return (rv);
}

static long
mps_file_seek(void *arg, long where, int whence)
{
	struct file_stream *fs = arg;

	return (fseek(fs->fs_fp, where, whence));
}

static char *
mps_file_id3(void *arg, enum mp3_stream_id3tag tag)
{
#if !(defined(NOID3LIB) && defined(NOTAGLIB))
	struct file_stream *fs = arg;
	const char *value;

	if ((value = id3_tag_lookup(&fs->fs_id3, tag)) == NULL)
		return (NULL);

	if (fs->fs_str)
		free(fs->fs_str);

	fs->fs_str = strdup(value);

	return (fs->fs_str);
#else
	return (NULL);
#endif
}

struct mmap_stream {
	int	ms_fd;
	size_t	ms_len;
	size_t	ms_fpos;
	unsigned char *ms_data;
#ifndef NOID3LIB
	char	*ms_str;
	struct id3_tag_ctx ms_id3;
#endif
};

static void *
mps_mmap_open(const char *path, int stdin_ok)
{
	struct mmap_stream *ms;
	struct stat st;
	int fd;

	if (strcmp(path, "-") == 0) {
		errno = EINVAL;
		return (NULL);
	}

	if (strncmp("mmap:/", path, 6) == 0)
		path += 5;

	if (stat(path, &st) < 0)
		return (NULL);

	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);

	if ((ms = calloc(1, sizeof(*ms))) == NULL) {
		close(fd);
		return (NULL);
	}

	ms->ms_data = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE | MAP_FILE,
	    fd, 0);
	if (ms->ms_data == NULL) {
		free(ms);
		close(fd);
	}

	if (madvise(ms->ms_data, st.st_size, MADV_SEQUENTIAL) < 0) {
		munmap(ms->ms_data, st.st_size);
		free(ms);
	}

#if !(defined(NOID3LIB) && defined(NOTAGLIB))
	id3_tag_init(&ms->ms_id3, path);
#endif
	ms->ms_fd = fd;
	ms->ms_len = st.st_size;
	ms->ms_fpos = 0;

	return (ms);
}

static void
mps_mmap_close(void *arg)
{
	struct mmap_stream *ms = arg;

#if !(defined(NOID3LIB) && defined(NOTAGLIB))
	id3_tag_delete(&ms->ms_id3);

	if (ms->ms_str)
		free(ms->ms_str);
#endif
	close(ms->ms_fd);
	munmap(ms->ms_data, ms->ms_len);
	free(ms);
}

static ssize_t
mps_mmap_read(void *arg, void *buf, size_t len)
{
	struct mmap_stream *ms = arg;

	if (len > (ms->ms_len - ms->ms_fpos))
		len = ms->ms_len - ms->ms_fpos;

	if (len)
		memcpy(buf, &ms->ms_data[ms->ms_fpos], len);

	ms->ms_fpos += len;

	return (len);
}

static long
mps_mmap_seek(void *arg, long where, int whence)
{
	struct mmap_stream *ms = arg;
	off_t new_pos;

	switch (whence) {
	case SEEK_SET:
		new_pos = (off_t) where;
		break;

	case SEEK_CUR:
		new_pos = (off_t) (ms->ms_fpos + where);
		break;

	case SEEK_END:
		new_pos = (off_t) (ms->ms_len - where);
		break;

	default:
		errno = EINVAL;
		return (-1);
	}

	if ((signed)new_pos < 0 || new_pos > ms->ms_len) {
		errno = EINVAL;
		return (-1);
	}

	return ((long) new_pos);
}

static char *
mps_mmap_id3(void *arg, enum mp3_stream_id3tag tag)
{
#if !(defined(NOID3LIB) && defined(NOTAGLIB))
	struct mmap_stream *ms = arg;
	const char *value;

	if ((value = id3_tag_lookup(&ms->ms_id3, tag)) == NULL)
		return (NULL);

	if (ms->ms_str)
		free(ms->ms_str);

	ms->ms_str = strdup(value);

	return (ms->ms_str);
#else
	return (NULL);
#endif
}


#ifndef NOCURL
struct url_stream {
	pid_t	us_pid;
	FILE	*us_fp;
};

static void *
mps_url_open(const char *path, int stdin_ok)
{
	struct url_stream *us;
	int pipes[2], status;
	pid_t pid, wpid;

	if (pipe(pipes) < 0)
		return (NULL);

	if ((pid = fork()) < 0) {
		close(pipes[0]);
		close(pipes[1]);
		return (NULL);
	} else
	if (pid == 0) {
		close(pipes[0]);
		signal(SIGHUP, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
		mps_url_spawn_reader(path, pipes[1]);
		exit(1);
		/* NOTREACHED */
	}

	close(pipes[1]);

	if ((us = calloc(1, sizeof(*us))) == NULL)
		goto out;

	us->us_pid = pid;

	if ((us->us_fp = fdopen(pipes[0], "rb")) == NULL) {
		free(us);
out:
		close(pipes[0]);

out2:
		do
			wpid = waitpid(pid, &status, 0);
		while (wpid < 0 && errno == EINTR);

		return (NULL);
	}

	if ((status = getc(us->us_fp)) == EOF) {
		free(us);
		goto out2;
	}

	(void) ungetc(status, us->us_fp);

	return (us);
}

static void
mps_url_close(void *arg)
{
	struct url_stream *us = arg;
	int status;
	pid_t pid;

	fclose(us->us_fp);

	do
		pid = waitpid(us->us_pid, &status, 0);
	while (pid < 0 && errno == EINTR);

	free(us);
	return;
}

static ssize_t
mps_url_read(void *arg, void *buf, size_t len)
{
	struct url_stream *us = arg;
	ssize_t rv;

	rv = fread(buf, 1, len, us->us_fp);

	if (rv == 0 && ferror(us->us_fp))
		rv = -1;

	return (rv);
}

static void
mps_url_spawn_reader(const char *path, int pfd)
{
	CURL *ch;
	FILE *fp;

	if ((fp = fdopen(pfd, "wb")) == NULL) {
		close(pfd);
		exit(1);
	}

	if ((ch = curl_easy_init()) == NULL) {
		fclose(fp);
		exit(1);
	}

	curl_easy_setopt(ch, CURLOPT_WRITEFUNCTION, mps_url_writer);
	curl_easy_setopt(ch, CURLOPT_FILE, fp);
	curl_easy_setopt(ch, CURLOPT_URL, path);
	curl_easy_setopt(ch, CURLOPT_NOPROGRESS, 1);
	curl_easy_setopt(ch, CURLOPT_FAILONERROR, 1);
	curl_easy_setopt(ch, CURLOPT_FOLLOWLOCATION, 1);

	curl_easy_perform(ch);
	exit(1);
}

static size_t
mps_url_writer(void *buf, size_t len, size_t nelem, FILE *fp)
{

	return (fwrite(buf, len, nelem, fp));
}
#endif

#if !(defined(NOID3LIB) && defined(NOTAGLIB))
static void
id3_tag_init(struct id3_tag_ctx *id3, const char *path)
{
#ifndef NOTAGLIB
	id3->id3_file = NULL;
#endif
	id3->id3_tag = NULL;
	id3->id3_path = path;
}

static void
id3_tag_delete(struct id3_tag_ctx *id3)
{
	if (id3->id3_tag == NULL)
		return;

#ifndef NOTAGLIB
	taglib_tag_free_strings();
	taglib_file_free(id3->id3_file);
	id3->id3_file = NULL;
#else
	ID3Tag_Delete(id3->id3_tag);
#endif
	id3->id3_tag = NULL;
}

#ifdef NOTAGLIB
/* id3lib version */
static const char *
id3_tag_lookup(struct id3_tag_ctx *id3, enum mp3_stream_id3tag tag)
{
	ID3Frame *frame;
	ID3Field *field;
	ID3_FrameID id;
	static char value[1024];

	if (id3->id3_path == NULL)
		return (NULL);

	if (id3->id3_tag == NULL) {
		if ((id3->id3_tag = ID3Tag_New()) == NULL)
			return (NULL);

		ID3Tag_Link(id3->id3_tag, id3->id3_path);
	}

	switch (tag) {
	case MP3_STREAM_TAG_ARTIST:
		id = ID3FID_LEADARTIST;
		break;

	case MP3_STREAM_TAG_TITLE:
		id = ID3FID_TITLE;
		break;

	case MP3_STREAM_TAG_ALBUM:
		id = ID3FID_ALBUM;
		break;

	case MP3_STREAM_TAG_COMMENT:
		id = ID3FID_COMMENT;
		break;

	case MP3_STREAM_TAG_GENRE:
		id = ID3FID_CONTENTTYPE;
		break;

	default:
		return (NULL);
	}

	value[0] = '\0';

	if ((frame = ID3Tag_FindFrameWithID(id3->id3_tag, id)) == NULL)
		return (NULL);

	if ((field = ID3Frame_GetField(frame, ID3FN_TEXT)) == NULL) {
		ID3Frame_Delete(frame);
		return (NULL);
	}

	ID3Field_GetASCII(field, value, sizeof(value));

	if (value[0] == '\0')
		return (NULL);

	return (value);
}
#else
/* taglib version */
static const char *
id3_tag_lookup(struct id3_tag_ctx *id3, enum mp3_stream_id3tag tag)
{
	const char *rv;

	if (id3->id3_path == NULL)
		return (NULL);

	if (id3->id3_file == NULL) {
		if ((id3->id3_file = taglib_file_new(id3->id3_path)) == NULL)
			return (NULL);

		id3->id3_tag = taglib_file_tag(id3->id3_file);
		if (id3->id3_tag == NULL) {
			taglib_file_free(id3->id3_file);
			id3->id3_file = NULL;
			return (NULL);
		}
	}

	switch (tag) {
	case MP3_STREAM_TAG_ARTIST:
		rv = taglib_tag_artist(id3->id3_tag);
		break;

	case MP3_STREAM_TAG_TITLE:
		rv = taglib_tag_title(id3->id3_tag);
		break;

	case MP3_STREAM_TAG_ALBUM:
		rv = taglib_tag_album(id3->id3_tag);
		break;

	case MP3_STREAM_TAG_COMMENT:
		rv = taglib_tag_comment(id3->id3_tag);
		break;

	case MP3_STREAM_TAG_GENRE:
		rv = taglib_tag_genre(id3->id3_tag);
		break;

	default:
		rv = NULL;
		break;
	}

	return (rv);
}
#endif
#endif
