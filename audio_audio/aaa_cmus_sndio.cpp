/*
 * Copyright (C) 2011 Donovan "Tsomi" Watteau <tsoomi@gmail.com>
 *
 * Based on Thomas Pfaff's work for XMMS, and some suggestions from
 * Alexandre Ratchov.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "framework.h"
#include "cmus_sndio.h"
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sndio.h>

//#include "timo_output_plugin.h"
#include "timo_mixer.h"
//#include "timo_sample_format.h"
//#include "../xmalloc.h"

// static sample_format_t m_sampleformat;
// static struct sio_par m_par;
// static struct sio_hdl *m_hdl;
// int cmus_sndio::m_iSndioVolume = SIO_MAXVOL;
// int cmus_sndio::m_bSndioPaused;


namespace multimedia
{


   namespace audio_sndio
   {


int cmus_sndio::sndio_mixer_set_volume(int l, int r)
{
	m_iSndioVolume = l > r ? l : r;

	if (m_hdl == NULL)
		return -OP_ERROR_NOT_INITIALIZED;

	if (!sio_setvol(m_hdl, m_iSndioVolume))
		return -OP_ERROR_INTERNAL;

	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_mixer_get_volume(int *l, int *r)
{
	*l = *r = m_iSndioVolume;

	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_set_sf(sample_format_t sf)
{
	struct sio_par apar;

	m_sampleformat = sf;

	sio_initpar(&m_par);

	m_par.pchan = sf_get_channels(m_sampleformat);
	m_par.rate = sf_get_rate(m_sampleformat);
	m_bSndioPaused = 0;

	if (sf_get_signed(m_sampleformat))
		m_par.sig = 1;
	else
		m_par.sig = 0;

	if (sf_get_bigendian(m_sampleformat))
		m_par.le = 0;
	else
		m_par.le = 1;

	switch (sf_get_bits(m_sampleformat)) {
	case 32:
		m_par.bits = 32;
		break;
	case 24:
		m_par.bits = 24;
		m_par.bps = 3;
		break;
	case 16:
		m_par.bits = 16;
		break;
	case 8:
		m_par.bits = 8;
		break;
	default:
		return -OP_ERROR_SAMPLE_FORMAT;
	}

	m_par.appbufsz = m_par.rate * 300 / 1000;
	apar = m_par;

	if (!sio_setpar(m_hdl, &m_par))
		return -OP_ERROR_INTERNAL;

	if (!sio_getpar(m_hdl, &m_par))
		return -OP_ERROR_INTERNAL;

	if (apar.rate != m_par.rate || apar.pchan != m_par.pchan ||
	    apar.bits != m_par.bits || (m_par.bits > 8 && apar.le != m_par.le) ||
	    apar.sig != m_par.sig)
		return -OP_ERROR_INTERNAL;

	sndio_mixer_set_volume(m_iSndioVolume, m_iSndioVolume);

	if (!sio_start(m_hdl))
		return -OP_ERROR_INTERNAL;

	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_init(void)
{
	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_exit(void)
{
	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_close(void)
{
	if (m_hdl != NULL) {
		sio_close(m_hdl);
		m_hdl = NULL;
	}

	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_open(sample_format_t sf, const channel_position_t *channel_map)
{
	int ret = 0;

	m_hdl = sio_open(NULL, SIO_PLAY, 0);
	if (m_hdl == NULL)
		return -OP_ERROR_INTERNAL;

	if ((ret = sndio_set_sf(sf)) < 0) {
		sndio_close();
		return ret;
	}

	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_write(const char *buf, int cnt)
{
	size_t rc;

	rc = sio_write(m_hdl, buf, cnt);
	if (rc == 0)
		return -OP_ERROR_INTERNAL;

	return rc;
}

int cmus_sndio::sndio_pause(void)
{
	if (!m_bSndioPaused) {
		if (!sio_stop(m_hdl))
			return -OP_ERROR_INTERNAL;
		m_bSndioPaused = 1;
	}

	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_unpause(void)
{
	if (m_bSndioPaused) {
		if (!sio_start(m_hdl))
			return -OP_ERROR_INTERNAL;
		m_bSndioPaused = 0;
	}

	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_buffer_space(void)
{
	/*
	 * Do as if there's always some space and let sio_write() block.
	 */
	return m_par.bufsz * m_par.bps * m_par.pchan;
}

int cmus_sndio::sndio_mixer_init(void)
{
	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_mixer_exit(void)
{
	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_mixer_open(int *volume_max)
{
	*volume_max = SIO_MAXVOL;

	return OP_ERROR_SUCCESS;
}

int cmus_sndio::sndio_mixer_close(void)
{
	return OP_ERROR_SUCCESS;
}
/*
const struct output_plugin_ops op_pcm_ops = {
	.init = sndio_init,
	.exit = sndio_exit,
	.open = sndio_open,
	.close = sndio_close,
	.write = sndio_write,
	.pause = sndio_pause,
	.unpause = sndio_unpause,
	.buffer_space = sndio_buffer_space,
};

const struct mixer_plugin_ops op_mixer_ops = {
	.init = sndio_mixer_init,
	.exit = sndio_mixer_exit,
	.open = sndio_mixer_open,
	.close = sndio_mixer_close,
	.set_volume = sndio_mixer_set_volume,
	.get_volume = sndio_mixer_get_volume,
};

const struct output_plugin_opt op_pcm_options[] = {
	{ NULL },
};

const struct mixer_plugin_opt op_mixer_options[] = {
	{ NULL },
};

const int op_priority = 2;
const unsigned op_abi_version = OP_ABI_VERSION;

*/




   } // namespace audio_sndio


} // namespace multimedia


