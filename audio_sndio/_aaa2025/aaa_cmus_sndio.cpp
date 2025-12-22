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


      int cmus_sndio::sndio_set_sample_format()
      {
         
         struct sio_par apar;

      //	m_sampleformat = sf;

         sio_initpar(&m_par);

         m_par.pchan = m_pwaveformat->m_waveformat.nChannels;
         information() << "cmus_sndio::sndio_set_sample_format request pchan : " << m_par.pchan;
         m_par.rate = m_pwaveformat->m_waveformat.nSamplesPerSec;
         information() << "cmus_sndio::sndio_set_sample_format request rate : " << m_par.rate;
         m_bSndioPaused = 0;

         //if (sf_get_signed(m_sampleformat))
         {
            
            m_par.sig = 1;
            
            information() << "cmus_sndio::sndio_set_sample_format request sig : " << m_par.sig;
            
         }
         //else
         //{
            
         //	m_par.sig = 0;
            
         //}

      //	if (sf_get_bigendian(m_sampleformat))
      //		m_par.le = 0;
      //	else
         m_par.le = 1;
         information() << "cmus_sndio::sndio_set_sample_format request le : " << m_par.le;

         m_par.bits = m_pwaveformat->m_waveformat.wBitsPerSample;
         information() << "cmus_sndio::sndio_set_sample_format request bits : " << m_par.bits;

         //switch (sf_get_bits(m_sampleformat)) {
         //case 32:
            //m_par.bits = 32;
            //break;
         //case 24:
            //m_par.bits = 24;
            //m_par.bps = 3;
            //break;
         //case 16:
            //m_par.bits = 16;
            //break;
         //case 8:
            //m_par.bits = 8;
            //break;
         //default:
            //return -OP_ERROR_SAMPLE_FORMAT;
         //}

         m_par.appbufsz = m_par.rate * m_timeBufferSizeHint.integral_millisecond() / 1000;
         
         information() << "cmus_sndio::sndio_set_sample_format request appbufsz : " << m_par.appbufsz;
         
         apar = m_par;

         if (!sio_setpar(m_hdl, &m_par))
         {
            
            information() << "cmus_sndio::sndio_set_sample_format failed to set parameters";
            
            return -OP_ERROR_INTERNAL;
            
         }

         if (!sio_getpar(m_hdl, &m_par))
         {
            
            information() << "cmus_sndio::sndio_set_sample_format failed to get parameters";
            
            return -OP_ERROR_INTERNAL;
            
         }
            
         information() << "cmus_sndio::sndio_set_sample_format got le : " << m_par.le;
         information() << "cmus_sndio::sndio_set_sample_format got bits : " << m_par.bits;
         information() << "cmus_sndio::sndio_set_sample_format got appbufsz : " << m_par.appbufsz;
         information() << "cmus_sndio::sndio_set_sample_format got pchan : " << m_par.pchan;
         information() << "cmus_sndio::sndio_set_sample_format got rate : " << m_par.rate;
         information() << "cmus_sndio::sndio_set_sample_format got sig : " << m_par.sig;

         if (apar.rate != m_par.rate)
         {
            
            information() << "Regarded as error : sample rate doesn't match";
            
            return -OP_ERROR_INTERNAL;
            
         } 
         
         if(apar.pchan != m_par.pchan)
         {
            
            information() << "Regarded as error : channel count doesn't match";
            
            return -OP_ERROR_INTERNAL;
            
         } 

         if(apar.bits != m_par.bits)
         {
            
            information() << "Regarded as error : precision doesn't match";
            
            return -OP_ERROR_INTERNAL;
            
         } 
            
         if(m_par.bits > 8 && apar.le != m_par.le) 
         {
            
            information() << "Regarded as error : precision is greater than 8 bits and endiannes doesn't match";
            
            return -OP_ERROR_INTERNAL;
            
         } 

         if(apar.sig != m_par.sig)
         {
            
            information() << "Regarded as error : signed/unsigned doesn't match";
            
            return -OP_ERROR_INTERNAL;
            
         } 

         sndio_mixer_set_volume(m_iSndioVolume, m_iSndioVolume);
         
         information() << "cmus_sndio::sndio_set_sample_format OK!!";

         return OP_ERROR_SUCCESS;
         
      }


      int cmus_sndio::sndio_start()
      {
         
         if (!sio_start(m_hdl))
         {
            
            information() << "cmus_sndio::sndio_start sio_start Failed!";
            
            return -OP_ERROR_INTERNAL;
            
         }
         
         information() << "cmus_sndio::sndio_start OK!!";

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

         if (m_hdl != NULL) 
         {
            
           sio_close(m_hdl);
         
           m_hdl = NULL;
           
         }

         return OP_ERROR_SUCCESS;
         
      }


      int cmus_sndio::sndio_open()
      {

         int ret = 0;
         
         information() << "";
         information() << "   cmus_sndio::sndio_open";
         information() << "";

         m_hdl = sio_open(NULL, SIO_PLAY, 0);
         
         if (m_hdl == NULL)
         {
            
            information() << "cmus_sndio::sndio_open sio_open Failed!";
            
            return -OP_ERROR_INTERNAL;
            
         }

         if ((ret = sndio_set_sample_format()) < 0) 
         {
            
            information() << "cmus_sndio::sndio_open sndio_set_sample_format Failed!";
            
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
         {
            
            information() << "cmus_sndio::sndio_write Failed!";
            
            return -OP_ERROR_INTERNAL;
            
         }
         
         information() << "cmus_sndio::sndio_write OK!!";

         return rc;
         
      }


      int cmus_sndio::sndio_pause(void)
      {
         
         if (!m_bSndioPaused) 
         {
            
            if (!sio_stop(m_hdl))
            {
               
               return -OP_ERROR_INTERNAL;
               
            }
            
            m_bSndioPaused = 1;
            
         }

         return OP_ERROR_SUCCESS;
         
      }


      int cmus_sndio::sndio_unpause(void)
      {

         if (m_bSndioPaused) 
         {
            
            if (!sio_start(m_hdl))
            {
               
               return -OP_ERROR_INTERNAL;
               
            }
            
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


