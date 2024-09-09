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
#pragma once
// #include <sys/types.h>
// #include <sys/ioctl.h>
// #include <sys/stat.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <string.h>
// #include <unistd.h>
#include <sndio.h>
//
#include "timo_output_plugin.h"
//#include "timo_mixer.h"
#include "timo_sample_format.h"


namespace multimedia
{


   namespace audio_sndio
   {


class cmus_sndio :
virtual public ::particle
{
public:

sample_format_t m_sampleformat;
struct sio_par m_par;
struct sio_hdl *m_hdl;
int m_iSndioVolume = SIO_MAXVOL;
int m_bSndioPaused;
int m_iFrameByteCount;
int m_iBufferCount;

int sndio_mixer_set_volume(int l, int r);
int sndio_mixer_get_volume(int *l, int *r);
int sndio_set_sf(sample_format_t sf);
int sndio_init(void);
int sndio_exit(void);
int sndio_close(void);
int sndio_open(sample_format_t sf, const channel_position_t *channel_map);
int sndio_write(const char *buf, int cnt);
int sndio_pause(void);
int sndio_unpause(void);
int sndio_buffer_space(void);
int sndio_mixer_init(void);
int sndio_mixer_exit(void);
int sndio_mixer_open(int *volume_max);
int sndio_mixer_close(void);

};




   } // namespace audio_sndio


} // namespace multimedia


