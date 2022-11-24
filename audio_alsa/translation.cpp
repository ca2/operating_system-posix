#include "framework.h"
//#include "aqua/multimedia/audio/_operating_system.h"
#include "app-core/audio/wave/format.h"


namespace multimedia
{


   namespace audio_alsa
   {


      void translate(WAVEFORMATEX & waveformatex, ::wave::format * pwaveformat)
      {


         waveformatex.wFormatTag        = pwaveformat->m_waveformat.wFormatTag;           /* format type */
         waveformatex.nChannels         = pwaveformat->m_waveformat.nChannels;            /* number of channels (i.e. mono, stereo...) */
         waveformatex.nSamplesPerSec    = pwaveformat->m_waveformat.nSamplesPerSec;       /* sample rate */
         waveformatex.nAvgBytesPerSec   = pwaveformat->m_waveformat.nAvgBytesPerSec;      /* for buffer estimation */
         waveformatex.nBlockAlign       = pwaveformat->m_waveformat.nBlockAlign;          /* block size of data */
         waveformatex.wBitsPerSample    = pwaveformat->m_waveformat.wBitsPerSample;       /* number of bits per sample of mono data */
         //waveformatex.cbSize          = pwaveformat->cbSize;               /* the count in bytes of the size of */
         waveformatex.cbSize            = sizeof(waveformatex);               /* the count in bytes of the size of */
                                                                                 /* extra information (after cbSize) */

      }


/*      void translate(WAVEHDR & wavehdr, ::multimedia::audio::wave_buffer * pwavebuffer, int iBuffer)
      {

         ::multimedia::audio::wave_buffer::buffer * pbuffer = pwavebuffer->get_buffer(iBuffer);

         pbuffer->m_posdata            = &wavehdr;

         wavehdr.lpData                = (char *) pbuffer->m_pData;
         wavehdr.dwBufferLength        = pwavebuffer->m_uiBufferSize;
         wavehdr.dwBytesRecorded       = 0;
         wavehdr.dwUser                = pbuffer->m_iIndex;
         wavehdr.dwFlags               = 0;

      }*/


      /*LPWAVEHDR create_new_WAVEHDR(::multimedia::audio::wave_buffer * pwavebuffer, int iBuffer)
      {

         LPWAVEHDR lpwavehdr = memory_new WAVEHDR;

         translate(*lpwavehdr, pwavebuffer, iBuffer);

         return lpwavehdr;

      }

      LPWAVEHDR get_os_data(::multimedia::audio::wave_buffer * pwavebuffer, int iBuffer)
      {

         ::multimedia::audio::wave_buffer::buffer * pbuffer = pwavebuffer->get_buffer(iBuffer);

         LPWAVEHDR pwavehdr = (LPWAVEHDR) pbuffer->get_os_data();

         return pwavehdr;

      }*/


      CLASS_DECL_AUDIO_ALSA ::e_status translate_alsa(int err)
      {

         if(err < 0)
         {

            return error_failed;

         }
         else
         {

            return success;

         };

      }


   }


}




