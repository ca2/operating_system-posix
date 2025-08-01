/*	$Id: audio_dev_pcm.c,v 1.1 2004/06/07 21:10:42 steve Exp $	*/

/*
 Command Line Front-end for Robert Leslie's `libmad' mp3 decoder.
 Copyright (C) 2001-2004 Steve Woodford.

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#include "audio_dev.h"

static void *ad_pcm_init(const_char_pointer );
static void ad_pcm_close(void *);
static int ad_pcm_config(void *, int, int, int lowat, int hiwat);
static ssize_t ad_pcm_output(void *, void *, size_t);
namespace multimedia
{


   namespace audio_audio
   {
const struct audio_dev_backend audio_dev_pcm = {
	"pcm:",
	ad_pcm_init,
	ad_pcm_close,
	ad_pcm_config,
	ad_pcm_output,
	NULL
};
}}
struct pcm_ctx {
	FILE *sc_fp;
};

static void *
ad_pcm_init(const_char_pointer dev)
{
	struct pcm_ctx *sc;

	if ((sc = (pcm_ctx *)calloc(1, sizeof(*sc))) == NULL)
		return (NULL);

	if (strcmp(dev, "-") == 0)
		sc->sc_fp = stdout;
	else
	if ((sc->sc_fp = fopen(dev, "wb")) == NULL) {
		free(sc);
		return (NULL);
	}

	return (sc);
}

static void
ad_pcm_close(void *arg)
{
	struct pcm_ctx *sc =  (pcm_ctx *)arg;

	fclose(sc->sc_fp);
	free(sc);
}

static int
ad_pcm_config(void *arg, int rate, int channels, int lowat, int hiwat)
{

	return (0);
}

static ssize_t
ad_pcm_output(void *arg, void *pcmbuff, size_t len)
{
	struct pcm_ctx *sc = (pcm_ctx *) arg;

	return (fwrite(pcmbuff, 1, len, sc->sc_fp));
}
