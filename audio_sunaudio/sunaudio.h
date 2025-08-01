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
//#include <sndio.h>
//
//#include "timo_output_plugin.h"
//#include "timo_mixer.h"
//#include "timo_sample_format.h"
#include "audio/audio/wave/out.h"

#include <sys/audioio.h>


namespace multimedia
{


   namespace audio_sunaudio
   {


      class CLASS_DECL_AUDIO_SUNAUDIO sun_object :
         virtual public ::wave::out

      {
      public:

         //sample_format_t m_sampleformat;
         //struct sio_par m_par;
         //struct sio_hdl *m_hdl;
         //int m_iSndioVolume = SIO_MAXVOL;
         //int m_bSndioPaused;
         int m_iFrameByteCount;
         int m_iBufferCount;

         //struct sun_object
         //{
            //struct audio_object vtable;
   
         int m_fd;
         int m_ctlfd;
         audio_info_t m_audioinfo;

         ::string m_strDevice;
   
         long long m_llWrittenBytes;
         
         long long m_iLastSecond;

         sun_object();
         ~sun_object();
   

         int sunaudio_open(int precision, unsigned int rate, unsigned char channels);

         int sunaudio_close();

         void sunaudio_destroy();

         int sunaudio_drain();

         int sunaudio_flush();

         memsize sunaudio_write(const void * data, memsize bytes);

         const_char_pointer sunaudio_strerror(int error);

         int sunaudio_pause();

         int sunaudio_unpause();
         
         //int sunaudio_wseek();
         
         long sunaudio_avail();

//int sndio_mixer_set_volume(int l, int r);
//int sndio_mixer_get_volume(int *l, int *r);
//int sndio_set_sf(sample_format_t sf);
//int sndio_init(void);
//int sndio_exit(void);
//int sndio_close(void);
//int sndio_open(sample_format_t sf, const channel_position_t *channel_map);
//int sndio_write(const_char_pointer buf, int cnt);
//int sndio_pause(void);
//int sndio_unpause(void);
//int sndio_buffer_space(void);
//int sndio_mixer_init(void);
//int sndio_mixer_exit(void);
//int sndio_mixer_open(int *volume_max);
//int sndio_mixer_close(void);

};




   } // namespace audio_sunaudio


} // namespace multimedia


