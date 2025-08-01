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
#include <poll.h>
//
#include "timo_output_plugin.h"
//#include "timo_mixer.h"
//#include "timo_sample_format.h"

#include "audio/audio/wave/out.h"


struct sio_par;


struct sio_hdl;


namespace multimedia
{


   namespace audio_sndio
   {


      class sndio :
         virtual public ::wave::out
      {
      public:
      

         ::sio_par            m_par;
         ::sio_hdl *          m_hdl;
         int                  m_iSndioVolume;
         int                  m_bSndioPaused;
         int                  m_iFrameByteCount;
         int                  m_iBufferCount;
         int                  m_iBufferCountHint;
         ::array < pollfd >   m_pollfda;
         
         
         sndio();
         ~sndio() override;


         int sndio_init();
         int sndio_open();
         int sndio_start();
         int sndio_set_sample_format();
         int sndio_wait_space_avail();
         int sndio_write(const_char_pointer  buf, int cnt);
         int sndio_pause();
         int sndio_unpause();
         int sndio_buffer_space();
         int sndio_exit();
         int sndio_close();


         int sndio_mixer_init();
         int sndio_mixer_open(int *volume_max);
         int sndio_mixer_set_volume(int l, int r);
         int sndio_mixer_get_volume(int *l, int *r);
         int sndio_mixer_close();
         int sndio_mixer_exit();


      };




   } // namespace audio_sndio


} // namespace multimedia


