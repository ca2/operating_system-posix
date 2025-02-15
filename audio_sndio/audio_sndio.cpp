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
#include "audio_sndio.h"
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sndio.h>
#include <poll.h>


//#include "timo_output_plugin.h"
#include "timo_mixer.h"
//#include "timo_sample_format.h"
//#include "../xmalloc.h"

// static sample_format_t m_sampleformat;
// static struct sio_par m_par;
// static struct sio_hdl *m_hdl;
// int sndio::m_iSndioVolume = SIO_MAXVOL;
// int sndio::m_bSndioPaused;


namespace multimedia
{


   namespace audio_sndio
   {
      
      
      sndio::sndio()
      {
         
         m_hdl                = nullptr;
         m_iSndioVolume       = SIO_MAXVOL;
         m_bSndioPaused       = false;
         m_iFrameByteCount    = 0;
         m_iBufferCount       = 0;

      }


      sndio::~sndio()
      {
         
         
      }


      int sndio::sndio_init()
      {
         
         return OP_ERROR_SUCCESS;
         
      }


      int sndio::sndio_open()
      {

         int ret = 0;
         
         information() << "";
         information() << "   sndio::sndio_open";
         information() << "";

         m_hdl = sio_open(NULL, SIO_PLAY, 0);
         
         if (m_hdl == NULL)
         {
            
            information() << "sndio::sndio_open sio_open Failed!";
            
            return -OP_ERROR_INTERNAL;
            
         }

         if ((ret = sndio_set_sample_format()) < 0) 
         {
            
            information() << "sndio::sndio_open sndio_set_sample_format Failed!";
            
            sndio_close();
            
            return ret;
            
         }

         return OP_ERROR_SUCCESS;
         
      }


      int sndio::sndio_set_sample_format()
      {
         
         struct sio_par apar;

         //	m_sampleformat = sf;

         sio_initpar(&m_par);
         
         information() << "sndio::sndio_set_sample_format was xrun : " << m_par.xrun;
         m_par.xrun = SIO_IGNORE;
         information() << "sndio::sndio_set_sample_format request SIO_IGNORE xrun : " << m_par.xrun;
         
         m_par.pchan = m_pwaveformat->m_waveformat.nChannels;
         information() << "sndio::sndio_set_sample_format request pchan : " << m_par.pchan;
         m_par.rate = m_pwaveformat->m_waveformat.nSamplesPerSec;
         information() << "sndio::sndio_set_sample_format request rate : " << m_par.rate;
         m_bSndioPaused = 0;

         //if (sf_get_signed(m_sampleformat))
         {
            
            m_par.sig = 1;
            
            information() << "sndio::sndio_set_sample_format request sig : " << m_par.sig;
            
         }
         //else
         //{
            
         //	m_par.sig = 0;
            
         //}

      //	if (sf_get_bigendian(m_sampleformat))
      //		m_par.le = 0;
      //	else
         m_par.le = 1;
         information() << "sndio::sndio_set_sample_format request le : " << m_par.le;

         m_par.bits = m_pwaveformat->m_waveformat.wBitsPerSample;
         information() << "sndio::sndio_set_sample_format request bits : " << m_par.bits;

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

         m_par.appbufsz = m_par.rate * m_timeBufferSizeHint.integral_millisecond() * m_iBufferCountHint / 1000;
         
         information() << "sndio::sndio_set_sample_format request appbufsz : " << m_par.appbufsz;
         
         apar = m_par;

         if (!sio_setpar(m_hdl, &m_par))
         {
            
            information() << "sndio::sndio_set_sample_format failed to set parameters";
            
            return -OP_ERROR_INTERNAL;
            
         }

         if (!sio_getpar(m_hdl, &m_par))
         {
            
            information() << "sndio::sndio_set_sample_format failed to get parameters";
            
            return -OP_ERROR_INTERNAL;
            
         }
        
         information() << "sndio::sndio_set_sample_format got le : " << m_par.le;
         information() << "sndio::sndio_set_sample_format got bits : " << m_par.bits;
         information() << "sndio::sndio_set_sample_format got appbufsz : " << m_par.appbufsz;
         information() << "sndio::sndio_set_sample_format got pchan : " << m_par.pchan;
         information() << "sndio::sndio_set_sample_format got rate : " << m_par.rate;
         information() << "sndio::sndio_set_sample_format got sig : " << m_par.sig;
         information() << "sndio::sndio_set_sample_format got xrun : " << m_par.xrun;

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
         
         information() << "Actual Bufffer Size is : " << m_par.bufsz;
         
         int iFrameSize = m_par.appbufsz / m_iBufferCountHint;
         
         if(iFrameSize < m_iFrameByteCount)
         {
            
            information() << "FrameByte count is less than expected : " << m_iFrameByteCount;
            
         }
         
         m_iFrameByteCount = iFrameSize;
         
         m_iBufferCount = m_iBufferCountHint;

         information() << "FrameByte count is : " << m_iFrameByteCount;
         
         information() << "Buffer count is : " << m_iBufferCount;

         sndio_mixer_set_volume(m_iSndioVolume, m_iSndioVolume);
         
         information() << "sndio::sndio_set_sample_format OK!!";

         return OP_ERROR_SUCCESS;
         
      }
      
      
      int sndio::sndio_start()
      {
         
         if (!sio_start(m_hdl))
         {
            
            information() << "sndio::sndio_start sio_start Failed!";
            
            return -OP_ERROR_INTERNAL;
            
         }
         
         information() << "sndio::sndio_start OK!!";

         return OP_ERROR_SUCCESS;
         
      }
      
      
      int sndio::sndio_wait_space_avail(void)
      {
	
         int nfds, revents;
         
         do
         {
            
            auto iTotalNfds = sio_nfds(m_hdl);
            
            if(iTotalNfds != m_pollfda.size())
            { 
            
               m_pollfda.set_size(iTotalNfds);
               
            }
            
            auto pfds = m_pollfda.data();
      
            nfds = sio_pollfd(m_hdl, pfds, POLLOUT);
         
            if (nfds > 0)
            {
               
               if (poll(pfds, nfds, -1) < 0)
               {
                  
                  information() << "poll(pfds, nfds, -1) < 0";
                  
                  return -OP_ERROR_INTERNAL;
                  
               }
               
            }
		
            revents = sio_revents(m_hdl, pfds);
		
            if (revents & POLLHUP)
            {
               
               information() << "POLLHUP device disappeared";
               
               if(sndio_close() != OP_ERROR_SUCCESS)
               {
                  
                  information() << "sndio_close Failed while trying to recover from POLLHUP";
                  
                  return -OP_ERROR_INTERNAL;
                  
               }
               
               information() << "sndio_close Succeeded while trying to recover from POLLHUP";
               
               if(sndio_open() != OP_ERROR_SUCCESS)
               {
                  
                  information() << "sndio_open Failed while trying to recover from POLLHUP";

                  return -OP_ERROR_INTERNAL;
                  
               }
               
               information() << "sndio_open Succeeded while trying to recover from POLLHUP";
               
               if(sndio_start() != OP_ERROR_SUCCESS)
               {
                  
                  information() << "sndio_start Failed while trying to recover from POLLHUP";
               
                  return -OP_ERROR_INTERNAL;
                  
               }
               
               information() << "sndio_start Succeeded while trying to recover from POLLHUP";
               
               information() << "It seems the stream has recovered from device POLLHUP";
               
            }
            
         }
         while (!(revents & POLLOUT) && ::task_get_run());
         
         return OP_ERROR_SUCCESS;
         
      }



      int sndio::sndio_write(const char *buf, int cnt)
      {
         
         size_t rc;

         rc = sio_write(m_hdl, buf, cnt);
         
         if (rc == 0)
         {
            
            information() << "sndio::sndio_write Failed!";
            
            return -OP_ERROR_INTERNAL;
            
         }
         
         information() << "sndio::sndio_write OK!!";

         return rc;
         
      }


      int sndio::sndio_pause(void)
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


      int sndio::sndio_unpause(void)
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


      int sndio::sndio_buffer_space(void)
      {
         
         /*
         * Do as if there's always some space and let sio_write() block.
         */

         return m_par.bufsz * m_par.bps * m_par.pchan;
         
      }
      
      
      int sndio::sndio_close(void)
      {

         if (m_hdl != NULL) 
         {
            
           sio_close(m_hdl);
         
           m_hdl = NULL;
           
         }

         return OP_ERROR_SUCCESS;
         
      }


      int sndio::sndio_exit(void)
      {
         
         return OP_ERROR_SUCCESS;
         
      }


      int sndio::sndio_mixer_init(void)
      {
         
         return OP_ERROR_SUCCESS;
         
      }

      
      int sndio::sndio_mixer_exit(void)
      {
         
         return OP_ERROR_SUCCESS;
         
      }

      
      int sndio::sndio_mixer_open(int *volume_max)
      {
         
         *volume_max = SIO_MAXVOL;

         return OP_ERROR_SUCCESS;
         
      }

      
      int sndio::sndio_mixer_set_volume(int l, int r)
      {
         
         m_iSndioVolume = l > r ? l : r;

         if (m_hdl == NULL)
         {
            
            return -OP_ERROR_NOT_INITIALIZED;
            
         }

         if (!sio_setvol(m_hdl, m_iSndioVolume))
         {
            
            return -OP_ERROR_INTERNAL;
            
         }

         return OP_ERROR_SUCCESS;
         
      }
      

      int sndio::sndio_mixer_get_volume(int *l, int *r)
      {
         *l = *r = m_iSndioVolume;

         return OP_ERROR_SUCCESS;
      }


      int sndio::sndio_mixer_close(void)
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


