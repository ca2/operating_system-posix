/*	$Id: audio_dev_arts.c,v 1.2 2005/01/14 11:04:46 steve Exp $	*/

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
#include <sys/param.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <artsc/artsc.h>

#include "audio_dev.h"

static void *ad_arts_init(const char *);
static void ad_arts_close(void *);
static int ad_arts_config(void *, int, int);
static ssize_t ad_arts_output(void *, void *, size_t);

const struct audio_dev_backend audio_dev_arts = {
	"arts:",
	ad_arts_init,
	ad_arts_close,
	ad_arts_config,
	ad_arts_output,
	NULL			/* XXX: aRts C-API doesn't support poll yet */
};

struct arts_ctx {
	arts_stream_t sc_as;
	const char *sc_dev;
	int sc_rate;
	int sc_channels;
};

static void *
ad_arts_init(const char *dev)
{
	struct arts_ctx *sc;
	int rv;

	if ((sc = calloc(1, sizeof(*sc))) == NULL)
		return (NULL);

	if ((rv = arts_init()) < 0) {
		fprintf(stderr, "ad_arts_init arts_init() failed: %s\n",
		    arts_error_text(rv));
		fflush(stderr);
		return (NULL);
	}

	if (dev == NULL || *dev == '\0')
		dev = "mad123";

	sc->sc_dev = dev;
	sc->sc_as = NULL;
	sc->sc_channels = 0;
	sc->sc_rate = 0;

	return (sc);
}

static void
ad_arts_close(void *arg)
{
	struct arts_ctx *sc = arg;

	if (sc->sc_as != NULL)
		arts_close_stream(sc->sc_as);
	arts_free();
	free(sc);
}

static int
ad_arts_config(void *arg, int rate, int channels)
{
	struct arts_ctx *sc = arg;

	if (sc->sc_as == NULL || rate != sc->sc_rate ||
	    channels != sc->sc_channels) {
		if (sc->sc_as != NULL)
			arts_close_stream(sc->sc_as);

		sc->sc_as = arts_play_stream(rate, 16, channels, sc->sc_dev);
		if (sc->sc_as == NULL)
			return (-1);
		arts_stream_set(sc->sc_as, ARTS_P_BUFFER_TIME, 500);
		arts_stream_set(sc->sc_as, ARTS_P_BLOCKING, 0);

		sc->sc_rate = rate;
		sc->sc_channels = channels;
	}

	return (0);
}

static ssize_t
ad_arts_output(void *arg, void *pcmbuff, size_t len)
{
	struct arts_ctx *sc = arg;

	return ((ssize_t)arts_write(sc->sc_as, pcmbuff, len));
}
