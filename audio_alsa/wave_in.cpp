#include "framework.h"
#include "wave_in.h"
#include "translation.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aqua/platform/system.h"
#include "app-core/audio/audio.h"
#include "app-core/audio/decode/encoder.h"


namespace multimedia
{


   namespace audio_alsa
   {


      wave_in::wave_in()
      {

         m_pencoder = NULL;
         m_einstate = ::wave::e_in_state_initial;
         m_bResetting = false;


      }

      wave_in::~wave_in()
      {
      }


      void wave_in::init_task()
      {

         TRACE("wave_in::initialize_instance %X\n", get_itask());
         //SetMainWnd(NULL);
         //ASSERT(GetMainWnd() == NULL);
         set_thread_priority(::e_priority_highest);
         //m_evInitialized.SetEvent();
         //return true;

      }


      void wave_in::term_task()
      {

         m_eventExitInstance.SetEvent();

         thread::term_task();

      }


      void wave_in::in_open(int32_t iBufferCount, int32_t iBufferSampleCount)
      {

         //return success;

         return;

         if(m_ppcm != NULL && m_einstate != ::wave::e_in_state_initial)
         {

            in_initialize_encoder();

            //return success;

            return;

         }

         single_lock sLock(synchronization(), TRUE);

         ::e_status mmr = success;

         ASSERT(m_ppcm == NULL);

         ASSERT(m_einstate == ::wave::e_in_state_initial);

         m_pwaveformat->m_waveformat.wFormatTag = 0;
         m_pwaveformat->m_waveformat.nChannels = 2;
         m_pwaveformat->m_waveformat.nSamplesPerSec = 44100;
         m_pwaveformat->m_waveformat.wBitsPerSample = sizeof(::wave::WAVEBUFFERDATA) * 8;
         m_pwaveformat->m_waveformat.nBlockAlign = m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels / 8;
         m_pwaveformat->m_waveformat.nAvgBytesPerSec = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;
         //m_pwaveformat->m_waveformat.cbSize = 0;

         //return error_failed;

         throw ::exception(error_failed);

         auto estatus = snd_pcm_open(SND_PCM_STREAM_CAPTURE);

         if(!estatus)
         {

            throw ::exception(estatus);

         }


         goto Opened;
         //m_pwaveformat->wFormatTag = WAVE_FORMAT_PCM;
         //m_pwaveformat->nChannels = 2;
         //m_pwaveformat->nSamplesPerSec = 44100;
         //m_pwaveformat->wBitsPerSample = sizeof(::multimedia::audio::WAVEBUFFERDATA) * 8;
         //m_pwaveformat->nBlockAlign = m_pwaveformat->wBitsPerSample * m_pwaveformat->nChannels / 8;
         //m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         //m_pwaveformat->cbSize = 0;
         //sp(::multimedia::audio::wave) audiowave = Application.audiowave();
         //m_iBuffer = 0;

         /*if(success == (mmr = waveInOpen(
            &m_hwavein,
            audiowave->m_uiWaveInDevice,
            wave_format(),
            get_os_int(),
            (::u32) 0,
            CALLBACK_THREAD)))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 22050;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(success == (mmr = waveInOpen(
            &m_hwavein,
            WAVE_MAPPER,
            wave_format(),
            (::u32) get_os_int(),
            (::u32) 0,
            CALLBACK_THREAD)))
            goto Opened;
         m_pwaveformat->nSamplesPerSec = 11025;
         m_pwaveformat->nAvgBytesPerSec = m_pwaveformat->nSamplesPerSec * m_pwaveformat->nBlockAlign;
         if(success == (mmr = waveInOpen(
            &m_hwavein,
            WAVE_MAPPER,
            wave_format(),
            (::u32) get_os_int(),
            (::u32) 0,
            CALLBACK_THREAD)))
            goto Opened;

         if(mmr !=success)
         {
            if(mmr == MMSYSERR_ALLOCATED)
            {
               TRACE("Specified resource is already allocated.");
            }
            else if(mmr == MMSYSERR_BADDEVICEID)
            {
               TRACE("Specified device identifier is out of range.");
            }
            else if(mmr == WAVERR_BADFORMAT)
            {
               TRACE("Attempted to open with an unsupported waveform-audio_alsa format.");
            }
            TRACE("ERROR OPENING WAVE INPUT DEVICE");
            return mmr;
         }*/

Opened:
         ::u32 uiBufferSizeLog2;
         ::u32 uiBufferSize;
         ::u32 uiAnalysisSize;
         ::u32 uiAllocationSize;
         ::u32 uiInterestSize;
         ::u32 uiSkippedSamplesCount;

         if(m_pwaveformat->m_waveformat.nSamplesPerSec == 44100)
         {
            uiBufferSizeLog2 = 16;
            uiBufferSize = m_pwaveformat->m_waveformat.nChannels * 2 * iBufferSampleCount; // 512 kbytes
            uiAnalysisSize = 4 * 1 << uiBufferSizeLog2;
            if(iBufferCount > 0)
            {
               uiAllocationSize = iBufferCount * uiBufferSize;
            }
            else
            {
               uiAllocationSize = 8 * uiAnalysisSize;
            }
            uiInterestSize = 200;
            uiSkippedSamplesCount = 2;
         }
         else if(m_pwaveformat->m_waveformat.nSamplesPerSec == 22050)
         {
            uiBufferSizeLog2 = 9;
            uiBufferSize = 4 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 16 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 600;
            uiSkippedSamplesCount = 1;
         }
         else if(m_pwaveformat->m_waveformat.nSamplesPerSec == 11025)
         {
            uiBufferSizeLog2 = 9;
            uiBufferSize = 2 * 1 << uiBufferSizeLog2;
            uiAnalysisSize = 8 * 1 << uiBufferSizeLog2;
            uiAllocationSize = 4 * uiAnalysisSize;
            uiInterestSize = 600;
            uiSkippedSamplesCount = 1;
         }
         in_get_buffer()->FFTOpen(
            uiAllocationSize,
            uiBufferSize,
            uiAnalysisSize,
            uiInterestSize,
            uiSkippedSamplesCount);

         /*int32_t i, iSize;

         iSize = (int32_t) in_get_buffer()->GetBufferCount();

         for(i = 0; i < iSize; i++)
         {

            if(success != (mmr =  waveInPrepareHeader(m_hwavein, create_new_WAVEHDR(in_get_buffer(), i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Preparing INPUT DEVICE buffer");
               return mmr;
            }

            in_add_buffer(i);

         }*/

         if(m_pencoder != NULL)
         {

            in_initialize_encoder();

         }

         m_einstate = ::wave::e_in_state_opened;

         //return success;

      }


      void wave_in::in_close()
      {

         single_lock sLock(synchronization(), TRUE);

         ::e_status estatus;

         if(m_einstate != ::wave::e_in_state_opened && m_einstate != ::wave::e_in_state_stopped)
         {

            return;

         }

         in_reset();

         //int32_t i, iSize;

         //iSize = (int32_t) in_get_buffer()->GetBufferCount();

         /*for(i = 0; i < iSize; i++)
         {

            if(success != (mmr = waveInUnprepareHeader(m_hwavein, wave_hdr(i), sizeof(WAVEHDR))))
            {
               TRACE("ERROR OPENING Unpreparing INPUT DEVICE buffer");
               //return mmr;
            }

            delete wave_hdr(i);

         }*/

         estatus = snd_pcm_close();

         m_ppcm = NULL;

         m_einstate = ::wave::e_in_state_initial;

         if(!estatus)
         {

            throw ::exception(estatus);

         }

      }


      void wave_in::in_start()
      {

         //return success;

         return;

         single_lock sLock(synchronization(), TRUE);

         if(m_einstate == ::wave::e_in_state_recording)
         {

            //return success;

            return;

         }

         if(m_einstate != ::wave::e_in_state_opened && m_einstate != ::wave::e_in_state_stopped)
         {

            //return success;

            return;

         }

         ::e_status estatus;

         if((estatus = translate_alsa(snd_pcm_start(m_ppcm))) != success)
         {

            TRACE("ERROR starting INPUT DEVICE ");

            //return mmr;

            throw ::exception(estatus);

         }

         m_einstate = ::wave::e_in_state_recording;

         //return success;

      }


      void wave_in::in_stop()
      {

         synchronous_lock sl(synchronization());

         if(m_einstate != ::wave::e_in_state_recording)
         {

            throw ::exception(error_failed);

         }

         ::e_status estatus;

         m_einstate = ::wave::e_in_state_stopping;

         try
         {

            if(success != (estatus = translate_alsa(snd_pcm_drain(m_ppcm))))
            {

               TRACE("wave_in::in_stop : ERROR OPENING stopping INPUT DEVICE ");

            }

         }
         catch(...)
         {

            TRACE("wave_in::in_stop : Exception OPENING stopping INPUT DEVICE ");

         }

         m_einstate = ::wave::e_in_state_stopped;

         m_eventStopped.SetEvent();

         //return success;

      }


      void wave_in::run()
      {

         int iBuffer = 0;
         int iSize;
         int err;

         while(task_get_run())
         {

            if(in_is_recording() && in_get_buffer()->GetBufferCount() > 0)
            {

               iSize = (int32_t) in_get_buffer()->GetBufferCount();

               if(iBuffer >= iSize)
                  iBuffer = 0;

               if(iBuffer < iSize)
               {

                  if ((err = snd_pcm_readi (m_ppcm, in_get_buffer()->get_buffer_data(iBuffer), in_get_buffer()->m_uiBufferSize)) == in_get_buffer()->m_uiBufferSize)
                  {
                     in_proc(m_ppcm, 0, 0, iBuffer, 0);
                  }
                  else
                  {
                     FORMATTED_TRACE("read from audio interface failed (%s)\n", snd_strerror (err));
                  }

               }

            }
            else
            {

               sleep(5_s);

            }

         }

         //return success;

      }


      void wave_in::in_proc(snd_pcm_t * p, ::u32 uMsg, ::u32 dwInstance, ::u32 dwParam1, ::u32 dwParam2)
      {

         m_iBuffer--;

         auto psystem = acmesystem()->m_paquasystem;

         auto paudio = psystem->audio()->m_paudio;

         auto msSampleTime = ::time::now();

         int iBuffer = dwParam1;

         in_get_buffer()->get_buffer(iBuffer)->OnMultimediaDone();

         m_listenerset.in_data_proc(this, msSampleTime, iBuffer);

         if(m_pencoder != NULL)
         {
            m_pencoder->EncoderWriteBuffer(in_get_buffer()->get_buffer_data(iBuffer), in_get_buffer()->m_uiBufferSize);
         }

         if(!in_is_resetting() && in_is_recording())
         {
            in_add_buffer(iBuffer);
         }

      }


      void wave_in::in_reset()
      {

         synchronous_lock sl(synchronization());

         m_bResetting = true;

         if(m_ppcm == NULL)
         {

            throw ::exception(error_failed);

         }



         if(m_einstate == ::wave::e_in_state_recording)
         {

            in_stop();

         }

         try
         {

            ::e_status estatus;

            if(!(estatus = translate_alsa(snd_pcm_drop(m_ppcm))))
            {

               TRACE("wave_in::Reset error resetting input device");

               throw ::exception(estatus);

            }

         }
         catch(...)
         {
         }

         m_einstate = ::wave::e_in_state_opened;

         m_bResetting = false;

         //return success;

      }


//
//
//      ::e_status wave_in::in_add_buffer(int32_t iBuffer)
//      {
//
//         return in_add_buffer(wave_hdr(iBuffer));
//
//      }
//
//
//      ::e_status wave_in::in_add_buffer(LPWAVEHDR lpwavehdr)
//      {
//
//         ::e_status mmr;
//
//         if(success != (mmr = waveInAddBuffer(m_hwavein, lpwavehdr, sizeof(WAVEHDR))))
//         {
//
//            TRACE("ERROR OPENING Adding INPUT DEVICE buffer");
//
//         }
//
//         m_iBuffer++;
//
//         return mmr;
//
//      }
//

      void wave_in::in_initialize_encoder()
      {

         if(m_pencoder == NULL)
         {

            throw ::exception(error_wrong_state);

         }
            //return false;

         ::wave::in::in_initialize_encoder();

         //if(!::wave::in::in_initialize_encoder())
            //return false;

         //return true;

      }

/*      WAVEFORMATEX * wave_in::wave_format()
      {

         translate(m_waveformatex, m_pwaveformat);

         return &m_waveformatex;

      }
*/
      snd_pcm_t * wave_in::in_get_safe_PCM()
      {

         if(::is_null(this))
         {

            return nullptr;

         }

         return m_ppcm;

      }

      void * wave_in::get_os_data()
      {
         return m_ppcm;
      }

/*      LPWAVEHDR wave_in::wave_hdr(int iBuffer)
      {
         return ::multimedia::audio_alsa::get_os_data(in_get_buffer(), iBuffer);
      }*/


   } // namespace audio_alsa


} // namespace multimedia






