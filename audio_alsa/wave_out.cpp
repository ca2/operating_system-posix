#include "framework.h"
//#include "aura/message.h"
#include "wave_out.h"
#include "translation.h"
#include "acme/parallelization/synchronous_lock.h"


#include <sys/time.h>


long long timestamp2ns(snd_htimestamp_t t)
{

   long long nsec;

   nsec = t.tv_sec * 1000000000;
   nsec += t.tv_nsec;

   return nsec;

}


long long timediff(snd_htimestamp_t t1, snd_htimestamp_t t2)
{

   long long nsec1, nsec2;

   nsec1 = timestamp2ns(t1);
   nsec2 = timestamp2ns(t2);

   return nsec1 - nsec2;

}


namespace multimedia
{


   namespace audio_alsa
   {


      wave_out::wave_out()
      {

         m_bDirectOutput      = false;
         m_eoutstate             = ::wave::e_out_state_initial;
         m_pthreadCallback    = NULL;
         m_estatusWave            = success;
         m_bWrite             = false;
         m_bStarted           = false;

         m_pstatus            = NULL;

         snd_pcm_status_malloc (&m_pstatus);

      }


      wave_out::~wave_out()
      {

         snd_pcm_status_free (m_pstatus);

      }


      void wave_out::install_message_routing(::channel * pchannel)
      {

         ::wave::out::install_message_routing(pchannel);

      }


      void wave_out::init_task()
      {

         //if(!
          ::wave::out::init_task();

//         {
//
//            return false;
//
//         }
//
//         return true;

      }


      void wave_out::term_task()
      {

         ::wave::out::term_task();

         thread::term_task();

      }


      void wave_out::out_open_ex(thread * pthreadCallback, ::u32 uiSamplesPerSec, ::u32 uiChannelCount, ::u32 uiBitsPerSample, ::wave::enum_purpose epurpose)
      {

         synchronous_lock sl(synchronization());

         TRACE("multimedia::audio_alsa::out_open_ex");

         if(m_ppcm != NULL && m_eoutstate != ::wave::e_out_state_initial)
         {

            ///return success;

            return;

         }

//         m_dwPeriodTime =  20 * 1000; /* period time in us */

//         m_iBufferCountEffective = 4;

         if(epurpose == ::wave::e_purpose_playback)
         {

  //          m_dwPeriodTime =  6 * 1000; /* period time in us */

            //m_iBufferCountEffective = 16;

            m_frameCount = uiSamplesPerSec / 20;

            m_iBufferCount = 8;

            printf("::wave::purpose_playback %ld\n", m_frameCount);

         }
         else
         {

            m_frameCount = 1024;

            //m_frameCount = uiSamplesPerSec / 20;

            m_iBufferCount = 4;

            printf("::wave::* %" PRIu64 "\n", m_frameCount);

         }

//         m_iBufferCount = m_iBufferCountEffective;

         m_pthreadCallback = pthreadCallback;

         ASSERT(m_ppcm == NULL);

         ASSERT(m_eoutstate == ::wave::e_out_state_initial);

         m_pwaveformat->m_waveformat.wFormatTag        = 0;
         m_pwaveformat->m_waveformat.nChannels         = (::u16) uiChannelCount;
         m_pwaveformat->m_waveformat.nSamplesPerSec    = uiSamplesPerSec;
         m_pwaveformat->m_waveformat.wBitsPerSample    = (::u16) uiBitsPerSample;
         m_pwaveformat->m_waveformat.nBlockAlign       = m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels / 8;
         m_pwaveformat->m_waveformat.nAvgBytesPerSec   = m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;
         //m_pwaveformat->cbSize            = 0;

         if(!(m_estatusWave = this->snd_pcm_open(SND_PCM_STREAM_PLAYBACK)))
         {

             throw ::exception(m_estatusWave);

         }

//         if(m_iBufferCount < m_iBufferCountEffective)
//         {
//
//            m_iBufferCountEffective = m_iBufferCount;
//
//         }

         //::u32 uBufferSize = snd_pcm_frames_to_bytes(m_ppcm, m_framesPeriodSize);

//         m_uiBufferTime = m_framesBuffer * 1000 * 1000 / uiSamplesPerSec;

         printf("snd_pcm_frames_to_bytes %" PRIu64 "\n", m_frameCount);

         ::u32 uBufferSize = snd_pcm_frames_to_bytes(m_ppcm, m_frameCount);

         out_get_buffer()->PCMOutOpen(this, uBufferSize, m_iBufferCount, 128, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(m_pwaveformat->m_waveformat.nChannels, m_iBufferCount, m_frameCount);

//         m_pprebuffer->SetMinL1BufferCount(out_get_buffer()->GetBufferCount());

         int err;

         if((err = snd_pcm_sw_params_current(m_ppcm, m_pswparams)) < 0)
         {

            FORMATTED_TRACE("unable to determine current m_pswparams for playback: %s\n", snd_strerror(err));

            throw ::exception(error_failed);

         }

         snd_pcm_sframes_t framesThreshold = (m_iBufferCount - 1) * m_frameCount;

         // start the transfer when the buffer is almost full:
         if((err = snd_pcm_sw_params_set_start_threshold(m_ppcm, m_pswparams, framesThreshold)) < 0)
         {

            FORMATTED_TRACE("unable to set start threshold mode for playback: %s\n", snd_strerror(err));

            throw ::exception(error_failed);

         }

         // allow the transfer when at least m_framesPeriodSize samples can be processed
         if((err = snd_pcm_sw_params_set_avail_min(m_ppcm, m_pswparams, m_frameCount)) < 0)
         {

            FORMATTED_TRACE("unable to set avail min for playback: %s\n", snd_strerror(err));

            throw ::exception(error_failed);

         }

         if((err = snd_pcm_sw_params_set_tstamp_mode(m_ppcm, m_pswparams, SND_PCM_TSTAMP_ENABLE)) < 0)
         {

            FORMATTED_TRACE("unable to set time stamp mode: %s\n", snd_strerror(err));

            throw ::exception(error_failed);

         }

         if((err = snd_pcm_sw_params_set_tstamp_type(m_ppcm, m_pswparams,SND_PCM_TSTAMP_TYPE_GETTIMEOFDAY)) <0)
         {

            FORMATTED_TRACE("unable to set time stamp type: %s\n", snd_strerror(err));

            throw ::exception(error_failed);

         }

         // write the parameters to the playback device
         if((err = snd_pcm_sw_params(m_ppcm, m_pswparams)) < 0)
         {

            FORMATTED_TRACE("unable to set sw params for playback: %s\n", snd_strerror(err));

            throw ::exception(error_failed);

         }

         m_psynthtask->m_iWaitBuffer = 1;

         m_eoutstate = ::wave::e_out_state_opened;

         m_epurpose = epurpose;

         //return success;

      }


      void wave_out::out_close()
      {

         synchronous_lock sl(synchronization());

         TRACE("multimedia::audio_alsa::out_close");

         if(m_eoutstate == ::wave::e_out_state_playing)
         {

            out_stop();

         }

         if(m_eoutstate != ::wave::e_out_state_opened)
         {

            //return success;

            return;

         }

         ::e_status mmr;

         mmr = this->snd_pcm_close();

         m_ppcm = NULL;

         ::wave::out::out_close();

         m_eoutstate = ::wave::e_out_state_initial;

         //return success;

      }


      void wave_out::out_stop()
      {

         synchronous_lock sl(synchronization());

         TRACE("multimedia::audio_alsa::out_stop");

         if(m_eoutstate != ::wave::e_out_state_playing && m_eoutstate != ::wave::e_out_state_paused)
         {

            throw ::exception(error_wrong_state);

         }

         //m_pprebuffer->stop();

         m_eoutstate = ::wave::e_out_state_stopping;

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_alsa output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = translate_alsa(snd_pcm_drain(m_ppcm));

         if(m_estatusWave == success)
         {

            m_eoutstate = ::wave::e_out_state_opened;

         }

         if(!m_estatusWave)
         {

            throw ::exception(m_estatusWave);

         }

      }


      void wave_out::out_pause()
      {

         synchronous_lock sl(synchronization());

         ASSERT(m_eoutstate == ::wave::e_out_state_playing);

         TRACE("multimedia::audio_alsa::out_pause");

         if(m_eoutstate != ::wave::e_out_state_playing)
         {

            throw ::exception(error_wrong_state);

         }

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_alsa output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = translate_alsa(snd_pcm_pause(m_ppcm, 1));

         ASSERT(m_estatusWave == success);

         if(m_estatusWave == success)
         {

            m_eoutstate = ::wave::e_out_state_paused;

         }

         if(!m_estatusWave)
         {

            throw ::exception(m_estatusWave);

         }

      }


      void wave_out::out_restart()
      {

         synchronous_lock sl(synchronization());

         ASSERT(m_eoutstate == ::wave::e_out_state_paused);

         TRACE("multimedia::audio_alsa::out_restart");

         if(m_eoutstate != ::wave::e_out_state_paused)
         {

            throw ::exception(error_wrong_state);

         }

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_alsa output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = translate_alsa(snd_pcm_pause(m_ppcm, 0));

         ASSERT(m_estatusWave == success);

         if(m_estatusWave == success)
         {
            m_eoutstate = ::wave::e_out_state_playing;
         }

         if(!m_estatusWave)
         {

            throw ::exception(m_estatusWave);

         }

      }


      ::time wave_out::out_get_position()
      {

         synchronous_lock sl(synchronization());

         ::time time;

         if(m_ppcm != NULL)
         {

            snd_pcm_sframes_t frames;

            snd_pcm_delay(m_ppcm, &frames);

            auto iBytes = m_pprebuffer->m_iBytes;

            auto iFrameSize = wave_base_get_frame_size();

            auto iFrame = iBytes / iFrameSize;

            double dSecond = (double) (iFrame - frames) / (double) m_pwaveformat->m_waveformat.nSamplesPerSec;

            time.m_iSecond = floor(dSecond);

            time.m_iNanosecond = fmod(dSecond, 1.0) * 1'000'000'000.0;

            //}

//            if(snd_pcm_status(m_ppcm, m_pstatus) == 0)
//            {
//
//               snd_htimestamp_t t;
//
//               snd_pcm_status_get_trigger_htstamp (m_pstatus, &t);
//
////               timespec tnow;
////
////               clock_gettime(CLOCK_REALTIME, &tnow);
////
////               time duratioNow;
////
////               timeNow.tv_sec = tnow.tv_sec;
////
////               timeNow.tv_nsec = tnow.tv_nsec;
//
//               time timeStart;
//
//               timeStart.m_iSecond = t.tv_sec;
//
//               timeStart.m_iNanosecond = t.tv_nsec;
//
//               time = timeStart.elapsed();
//
//            }

         }

         if(time > 0_s)
         {

            //output_debug_string("test");

         }

         return time;

      }


//      imedia_position wave_out::out_get_position()
//      {
//
//         return out_get_position_millis()/1'000.0;
//
//      }


      void wave_out::out_on_playback_end()
      {

         TRACE("multimedia::audio_alsa::out_on_playback_end");

         ::wave::out::out_on_playback_end();

      }


      snd_pcm_t * wave_out::out_get_safe_PCM()
      {

         if(::is_null(this))
         {

            return NULL;

         }

         return m_ppcm;

      }


      bool wave_out::alsa_should_play()
      {

         if(!::task_get_run())
         {

            return false;

         }

         if(m_ppcm == NULL)
         {

            TRACE("alsa_out_buffer_ready m_ppcm == NULL");

            return false;

         }

         if(m_eoutstate != ::wave::e_out_state_playing && m_eoutstate != ::wave::e_out_state_stopping)
         {

            TRACE("alsa_out_buffer_ready failure: !playing && !stopping");

            return false;

         }

         return true;

      }


      void wave_out::out_filled(index iBuffer)
      {

         snd_pcm_sframes_t iFramesToWrite = m_frameCount;

         int iBytesToWrite = -1;

         ::e_status estatus = success;

         snd_pcm_sframes_t iFrameFreeCount = 0;

         {

            synchronous_lock sl(synchronization());

            if (m_ppcm == NULL)
            {

               return;

            }

            iBytesToWrite = snd_pcm_frames_to_bytes(m_ppcm, iFramesToWrite);

         }

         while(::task_get_run())
         {

            {

               synchronous_lock sl(synchronization());

               iFrameFreeCount = snd_pcm_avail_update(m_ppcm);

               if (iFrameFreeCount == -EAGAIN)
               {

                  continue;

               }
               else if (iFrameFreeCount < 0)
               {

                  const char * pszError = snd_strerror(iFrameFreeCount);

                  FORMATTED_TRACE("ALSA wave_out snd_pcm_avail error: %s (%d)\n", pszError, iFrameFreeCount);

                  iFrameFreeCount = defer_underrun_recovery(iFrameFreeCount);

                  if (iFrameFreeCount >= 0)
                  {

                     TRACE("ALSA wave_out snd_pcm_avail underrun recovery success (snd_pcm_avail)");

                     break;

                  }

                  FORMATTED_TRACE("ALSA wave_out snd_pcm_avail minimum byte count %d\n", iFramesToWrite);

                  m_eoutstate = ::wave::e_out_state_opened;

                  m_estatusWave = error_failed;

                  FORMATTED_TRACE("ALSA wave_out snd_pcm_avail error: %s\n", snd_strerror(iFrameFreeCount));

                  return;

               }
               else if (iFrameFreeCount >= iFramesToWrite)
               {

                  break;

               }

            }

            usleep((iFramesToWrite - iFrameFreeCount) * 500'000 / m_pwaveformat->m_waveformat.nSamplesPerSec);

         }

         byte * pdata;

         memory m;

         ::wave::buffer::item * pbuffer = nullptr;

         if(iBuffer >= 0)
         {

            pbuffer = m_pwavebuffer->m_buffera[iBuffer];

            pdata = (byte *) out_get_buffer_data(iBuffer);

         }
         else
         {

            m.set_size(iBytesToWrite);

            m.zero();

            pdata = (byte *) m.get_data();

         }

         synchronous_lock sl(synchronization());

         synchronous_lock synchronouslockBuffer(pbuffer ? pbuffer->synchronization() : nullptr);

         int iZero = 0;

         int iFramesJustWritten = 0;

         while (iBytesToWrite > 0)
         {

            iFramesJustWritten = snd_pcm_writei(m_ppcm, pdata, iFramesToWrite);

            if(!m_bStarted)
            {

               gettimeofday(&m_timevalStart, nullptr);

            }

            m_bStarted = true;

            if(iFramesJustWritten == -EINTR)
            {

               TRACE("snd_pcm_writei -EINTR\n");

               continue;

            }
            else if(iFramesJustWritten == -EAGAIN)
            {

               //TRACE("snd_pcm_writei -EAGAIN\n");

               sl.unlock();

               snd_pcm_wait(m_ppcm, 100);

               sl.lock();

               continue;

            }
            else if(iFramesJustWritten < 0)
            {

               TRACE("snd_pcm_writei Underrun\n");

               FORMATTED_TRACE("ALSA wave_out snd_pcm_writei error: %s (%d)\n", snd_strerror(iFramesJustWritten), iFramesJustWritten);

               iFramesJustWritten = defer_underrun_recovery(iFramesJustWritten);

               if(iFramesJustWritten < 0 && iFramesJustWritten != -EAGAIN)
               {

                  m_eoutstate = ::wave::e_out_state_opened;

                  m_estatusWave = error_failed;

                  FORMATTED_TRACE("ALSA wave_out snd_pcm_writei couldn't recover from error: %s\n", snd_strerror(iFramesJustWritten));

                  return;

               }

               iFramesJustWritten = 0;

               continue;

            }

            iFramesToWrite -= iFramesJustWritten;

            int iBytesJustWritten = snd_pcm_frames_to_bytes(m_ppcm, iFramesJustWritten);

            m_pprebuffer->m_iBytes += iBytesJustWritten;

            pdata += iBytesJustWritten;

            iBytesToWrite -= iBytesJustWritten;

   //            if(iBytesToWrite > 0)
   //            {
   //
   //               sl.unlock();
   //
   //               snd_pcm_wait(m_ppcm, 100);
   //
   //               sl.lock();
   //
   //            }

         }

         m_iBufferedCount++;

         sl.unlock();

         if(iBuffer >= 0)
         {

            m_psynthtask->on_free(iBuffer);

         }

      }


      ::time wave_out::out_get_time_for_synch()
      {

         if (m_pprebuffer.is_null())
         {

            return e_zero;

         }

         int64_t dwPosition = m_pprebuffer->m_iBytes;

         dwPosition *= 1000;

         if (m_pwaveformat->m_waveformat.nSamplesPerSec <= 0)
         {

            return e_zero;

         }

         dwPosition /= m_pwaveformat->m_waveformat.nSamplesPerSec;

         return INTEGRAL_MILLISECOND(dwPosition / 1000.0);

      }


      void wave_out::out_start(const class time & time)
      {

         synchronous_lock sl(synchronization());

         if(m_eoutstate == ::wave::e_out_state_playing)
         {

            //return success;

            return;

         }

         if(m_eoutstate != ::wave::e_out_state_opened && m_eoutstate != ::wave::e_out_state_stopped)
         {

            //return error_failed;

            throw ::exception(error_wrong_state);

         }

         int err = 0;

         if ((err = snd_pcm_prepare (m_ppcm)) < 0)
         {

            FORMATTED_TRACE ("out_start: Cannot prepare audio interface for use (%s)\n",snd_strerror (err));

            throw ::exception(error_failed);

         }

         TRACE("out_start: snd_pcm_prepare OK");

         m_bStarted = false;

         ::wave::out::out_start(time);

         if(!m_estatusWave)
         {

            TRACE("out_start: ::wave::out::out_start FAILED");

            throw ::exception(m_estatusWave);

         }

//         m_pthreadWriter = fork([&]()
//         {
//
//            alsa_write_thread();
//
//         });

         TRACE("out_start: ::wave::out::out_start OK");

         //return success;

      }


      int wave_out::defer_underrun_recovery(int err)
      {

         return snd_pcm_recover(m_ppcm, err, 0);

//         if (err == -EPIPE)
//         {
//
//            FORMATTED_TRACE("underrun_recovery, going to snd_pcm_prepare: %s\n", snd_strerror(err));
//
//
//
//            if (err < 0)
//            {
//
//               FORMATTED_TRACE("Can't recover from underrun, snd_pcm_prepare failed: %s\n", snd_strerror(err));
//
//            }
//
//         }
//         else if (err == -ESTRPIPE)
//         {
//
//            FORMATTED_TRACE("underrun_recovery, snd_pcm_prepare returned -ESTRPIPE: %s\n", snd_strerror(err));
//
//            while ((err = snd_pcm_resume(m_ppcm)) == -EAGAIN)
//            {
//
//               FORMATTED_TRACE("underrun_recovery, snd_pcm_resume returned -EAGAIN: %s\n", snd_strerror(err));
//
//               sleep(1); /* wait until the suspend flag is released */
//
//            }
//
//            if (err < 0)
//            {
//
//               err = snd_pcm_prepare(m_ppcm);
//
//               if (err < 0)
//               {
//
//                  FORMATTED_TRACE("Can't recovery from suspend, snd_pcm_prepare failed: %s\n", snd_strerror(err));
//
//               }
//
//            }
//
//         }
//
//         return err;

      }


   } // namespace audio_alsa


} // namespace multimedia



