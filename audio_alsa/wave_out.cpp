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

         m_bDirectOutput = false;
         m_eoutstate = ::wave::e_out_state_initial;
         m_pthreadCallback = NULL;
         m_estatusWave = success;
         m_bWrite = false;
         m_bStarted = false;

         m_pstatus = NULL;

         snd_pcm_status_malloc(&m_pstatus);

      }


      wave_out::~wave_out()
      {

         snd_pcm_status_free(m_pstatus);

      }


      void wave_out::install_message_routing(::channel *pchannel)
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


      void
      wave_out::out_open_ex(thread *pthreadCallback, ::u32 uiSamplesPerSec, ::u32 uiChannelCount, ::u32 uiBitsPerSample,
                            ::wave::enum_purpose epurpose)
      {

         synchronous_lock sl(synchronization());

         information("multimedia::audio_alsa::out_open_ex");

         if (m_ppcm != NULL && m_eoutstate != ::wave::e_out_state_initial)
         {

            ///return success;

            return;

         }

//         m_dwPeriodTime =  20 * 1000; /* period time in us */

//         m_iBufferCountEffective = 4;

         if (epurpose == ::wave::e_purpose_playback)
         {

            //          m_dwPeriodTime =  6 * 1000; /* period time in us */

            //m_iBufferCountEffective = 16;

            m_timeBufferSizeHint = 400_ms;

            m_frameCount = uiSamplesPerSec / 20;

            m_iBufferCount = 8;

            printf("::wave::purpose_playback %ld\n", m_frameCount);

         }
         else
         {

            m_timeBufferSizeHint = 100_ms;

            m_frameCount = 1024;

            //m_frameCount = uiSamplesPerSec / 20;

            m_iBufferCount = 4;

            printf("::wave::* %" PRIu64 "\n", m_frameCount);

         }

//         m_iBufferCount = m_iBufferCountEffective;

         m_pthreadCallback = pthreadCallback;

         ASSERT(m_ppcm == NULL);

         ASSERT(m_eoutstate == ::wave::e_out_state_initial);

         m_pwaveformat->m_waveformat.wFormatTag = 0;
         m_pwaveformat->m_waveformat.nChannels = (::u16) uiChannelCount;
         m_pwaveformat->m_waveformat.nSamplesPerSec = uiSamplesPerSec;
         m_pwaveformat->m_waveformat.wBitsPerSample = (::u16) uiBitsPerSample;
         m_pwaveformat->m_waveformat.nBlockAlign =
                 m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels / 8;
         m_pwaveformat->m_waveformat.nAvgBytesPerSec =
                 m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;
         //m_pwaveformat->cbSize            = 0;

         if (!(m_estatusWave = this->snd_pcm_open(SND_PCM_STREAM_PLAYBACK)))
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

         information() << "frame_count : " << m_frameCount;

         ::u32 uBufferSize = snd_pcm_frames_to_bytes(m_ppcm, m_frameCount);

         information() << "uBufferSize in bytes : " << uBufferSize;

         information() << "buffer count : " << m_iBufferCount;

         out_get_buffer()->PCMOutOpen(this, uBufferSize, m_iBufferCount, 128, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(m_pwaveformat->m_waveformat.nChannels, m_iBufferCount, m_frameCount);

//         m_pprebuffer->SetMinL1BufferCount(out_get_buffer()->GetBufferCount());

//         int err;
//
//         if((err = snd_pcm_sw_params_current(m_ppcm, m_pswparams)) < 0)
//         {
//
//            information("unable to determine current m_pswparams for playback: %s\n", snd_strerror(err));
//
//            throw ::exception(error_failed);
//
//         }
//
//         int errSet, errSave;
//
//         errSet = 0;
//         errSave = 0;
//
//         snd_pcm_sframes_t framesThreshold = (m_iBufferCount - 1) * m_frameCount;
//
//         // start the transfer when the buffer is almost full:
//         if((errSet = snd_pcm_sw_params_set_start_threshold(m_ppcm, m_pswparams, framesThreshold)) < 0
//            || (errSave = snd_pcm_sw_params(m_ppcm, m_pswparams)) < 0)
//         {
//
//            information("unable to set start threshold mode for playback: %s\n", snd_strerror(err));
//
//         }
//
//         if((err = snd_pcm_sw_params_current(m_ppcm, m_pswparams)) < 0)
//         {
//
//            information("unable to determine current m_pswparams for playback (2): %s\n", snd_strerror(err));
//
//            throw ::exception(error_failed);
//
//         }
//
//         errSet = 0;
//         errSave = 0;
//
//         // allow the transfer when at least m_framesPeriodSize samples can be processed
//         if((err = snd_pcm_sw_params_set_avail_min(m_ppcm, m_pswparams, m_frameCount)) < 0
//            || ((errSave = snd_pcm_sw_params(m_ppcm, m_pswparams)) < 0))
//         {
//
//            information("unable to set avail min for playback: %s\n", snd_strerror(err));
//
//         }
//
//         if((err = snd_pcm_sw_params_current(m_ppcm, m_pswparams)) < 0)
//         {
//
//            information("unable to determine current m_pswparams for playback (3): %s\n", snd_strerror(err));
//
//            throw ::exception(error_failed);
//
//         }
//
//         errSet = 0;
//         errSave = 0;
//
//         if((err = snd_pcm_sw_params_set_tstamp_mode(m_ppcm, m_pswparams, SND_PCM_TSTAMP_ENABLE)) < 0
//            || (errSave = snd_pcm_sw_params(m_ppcm, m_pswparams)) < 0
//                 )
//         {
//
//            information("unable to set time stamp mode: %s\n", snd_strerror(err));
//
//         }
//
//         if((err = snd_pcm_sw_params_current(m_ppcm, m_pswparams)) < 0)
//         {
//
//            information("unable to determine current m_pswparams for playback (4): %s\n", snd_strerror(err));
//
//            throw ::exception(error_failed);
//
//         }
//
//         errSet = 0;
//         errSave = 0;
//
//         if((err = snd_pcm_sw_params_set_tstamp_type(m_ppcm, m_pswparams,SND_PCM_TSTAMP_TYPE_GETTIMEOFDAY)) <0
//            || (errSave = snd_pcm_sw_params(m_ppcm, m_pswparams)) < 0
//                 )
//         {
//
//            information("unable to set time stamp type (SND_PCM_TSTAMP_TYPE_GETTIMEOFDAY): %s\n", snd_strerror(err));
//
//            if((err = snd_pcm_sw_params_current(m_ppcm, m_pswparams)) < 0)
//            {
//
//               information("unable to determine current m_pswparams for playback (3): %s\n", snd_strerror(err));
//
//               throw ::exception(error_failed);
//
//            }
//
//            if((err = snd_pcm_sw_params_set_tstamp_type(m_ppcm, m_pswparams,SND_PCM_TSTAMP_TYPE_MONOTONIC)) <0
//               || (errSave = snd_pcm_sw_params(m_ppcm, m_pswparams)) < 0
//                    )
//            {
//
//               information("unable to set time stamp type (SND_PCM_TSTAMP_TYPE_MONOTONIC): %s\n", snd_strerror(err));
//
//            }
//
//         }


//         // write the parameters to the playback device
//         if((err = snd_pcm_sw_params(m_ppcm, m_pswparams)) < 0)
//         {
//
//            information("unable to set sw params for playback: %s\n", snd_strerror(err));
//
//            throw ::exception(error_failed);
//
//         }

         m_psynthtask->m_iWaitBuffer = 1;

         m_eoutstate = ::wave::e_out_state_opened;

         m_epurpose = epurpose;

         //return success;

      }


      void wave_out::out_close()
      {

         synchronous_lock sl(synchronization());

         information("multimedia::audio_alsa::out_close");

         if (m_eoutstate == ::wave::e_out_state_playing)
         {

            out_stop();

         }

         if (m_eoutstate != ::wave::e_out_state_opened)
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

         information("multimedia::audio_alsa::out_stop");

         if (m_eoutstate != ::wave::e_out_state_playing && m_eoutstate != ::wave::e_out_state_paused)
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

         if (m_estatusWave == success)
         {

            m_eoutstate = ::wave::e_out_state_opened;

         }

         if (!m_estatusWave)
         {

            throw ::exception(m_estatusWave);

         }

      }


      void wave_out::out_pause()
      {

         synchronous_lock sl(synchronization());

         ASSERT(m_eoutstate == ::wave::e_out_state_playing);

         information("multimedia::audio_alsa::out_pause");

         if (m_eoutstate != ::wave::e_out_state_playing)
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

         if (m_estatusWave == success)
         {

            m_eoutstate = ::wave::e_out_state_paused;

         }

         if (!m_estatusWave)
         {

            throw ::exception(m_estatusWave);

         }

      }


      void wave_out::out_restart()
      {

         synchronous_lock sl(synchronization());

         ASSERT(m_eoutstate == ::wave::e_out_state_paused);

         information("multimedia::audio_alsa::out_restart");

         if (m_eoutstate != ::wave::e_out_state_paused)
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

         if (m_estatusWave == success)
         {
            m_eoutstate = ::wave::e_out_state_playing;
         }

         if (!m_estatusWave)
         {

            throw ::exception(m_estatusWave);

         }

      }


      class ::time wave_out::out_get_position()
      {

         synchronous_lock sl(synchronization());

         class ::time time;

         if (m_ppcm != NULL)
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

         if (time > 0_s)
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

         information("multimedia::audio_alsa::out_on_playback_end");

         ::wave::out::out_on_playback_end();

      }


      snd_pcm_t *wave_out::out_get_safe_PCM()
      {

         if (::is_null(this))
         {

            return NULL;

         }

         return m_ppcm;

      }


      bool wave_out::alsa_should_play()
      {

         if (!::task_get_run())
         {

            return false;

         }

         if (m_ppcm == NULL)
         {

            information("alsa_out_buffer_ready m_ppcm == NULL");

            return false;

         }

         if (m_eoutstate != ::wave::e_out_state_playing && m_eoutstate != ::wave::e_out_state_stopping)
         {

            information("alsa_out_buffer_ready failure: !playing && !stopping");

            return false;

         }

         return true;

      }


//      void wave_out::on_my_callback()
//      {
//
//         int iBuffer = -1;
//
//         information("on_my_callback");
//
//         {
//
//            synchronous_lock sl(synchronization());
//
//            if(m_iaSent.has_element())
//            {
//
//               iBuffer = m_iaSent.pick_last();
//
//               information("m_iaSent.pick_last(): " << iBuffer);
//
//            }
//
//         }
//
//         if (iBuffer >= 0)
//         {
//
//            m_psynthtask->on_free(iBuffer);
//
//         }
//
//      }


      void wave_out::out_filled(index iBuffer)
      {

//         static class ::time t;
//
//         information("out_filled: " << iBuffer);
//         information("thread: " << pthread_self());
//         information("elapsed micros: " << t.elapsed().integral_microsecond());

//         t.Now();

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

         while (::task_get_run())
         {

            {

               synchronous_lock sl(synchronization());

               //print_snd_pcm_status();

               iFrameFreeCount = snd_pcm_avail(m_ppcm);

               if (iFrameFreeCount == -EAGAIN)
               {

                  continue;

               }
               else if (iFrameFreeCount < 0)
               {

                  const char *pszError = snd_strerror(iFrameFreeCount);

                  information("ALSA wave_out snd_pcm_avail error: %s (%d)\n", pszError, iFrameFreeCount);

                  iFrameFreeCount = defer_underrun_recovery(iFrameFreeCount);

                  if (iFrameFreeCount >= 0)
                  {

                     information("ALSA wave_out snd_pcm_avail underrun recovery success (snd_pcm_avail)");

                     break;

                  }

                  information("ALSA wave_out snd_pcm_avail minimum ::u8 count %d\n", iFramesToWrite);

                  m_eoutstate = ::wave::e_out_state_opened;

                  m_estatusWave = error_failed;

                  information("ALSA wave_out snd_pcm_avail error: %s\n", snd_strerror(iFrameFreeCount));

                  return;

               }
               else if (iFrameFreeCount >= iFramesToWrite)
               {

                  break;

               }

            }

            auto waitFrames = (iFramesToWrite - iFrameFreeCount);

            auto mugreeklettersecondsWait = waitFrames * 100'000 / m_pwaveformat->m_waveformat.nSamplesPerSec;

//            information("frames to write: " << iFramesToWrite << " frame free count : " << iFrameFreeCount
//                                      << " frames to wait: " << waitFrames << " μs to wait : " << mugreeklettersecondsWait);
//
            usleep(mugreeklettersecondsWait);

         }

         ::u8 *pdata;

         memory m;

         ::wave::buffer::item *pbuffer = nullptr;

         if (iBuffer >= 0)
         {

            pbuffer = m_pwavebuffer->m_buffera[iBuffer];

            pdata = (::u8 *) out_get_buffer_data(iBuffer);

         }
         else
         {

            m.set_size(iBytesToWrite);

            m.zero();

            pdata = (::u8 *) m.data();

         }

         synchronous_lock sl(synchronization());

         //m_iaSent.insert_at(0, iBuffer);

         synchronous_lock synchronouslockBuffer(pbuffer ? pbuffer->synchronization() : nullptr);

         int iZero = 0;

         int iFramesJustWritten = 0;

         while (iBytesToWrite > 0)
         {

            iFramesJustWritten = snd_pcm_writei(m_ppcm, pdata, iFramesToWrite);

            //information("snd_pcm_writei iFramesJustWritten " << iFramesJustWritten);

            if (!m_bStarted)
            {

               m_timeStart.Now();

               //gettimeofday(&m_timevalStart, nullptr);

               m_bStarted = true;

            }

            if (iFramesJustWritten == -EINTR)
            {

               information("snd_pcm_writei -EINTR\n");

               continue;

            }
            else if (iFramesJustWritten == -EAGAIN)
            {

               //information("snd_pcm_writei -EAGAIN\n");

               sl.unlock();

               snd_pcm_wait(m_ppcm, 10);

               sl.lock();

               continue;

            }
            else if (iFramesJustWritten < 0)
            {

               information("snd_pcm_writei Underrun\n");

               information("ALSA wave_out snd_pcm_writei error: %s (%d)\n", snd_strerror(iFramesJustWritten),
                               iFramesJustWritten);

               iFramesJustWritten = defer_underrun_recovery(iFramesJustWritten);

               if (iFramesJustWritten < 0 && iFramesJustWritten != -EAGAIN)
               {

                  m_eoutstate = ::wave::e_out_state_opened;

                  m_estatusWave = error_failed;

                  information("ALSA wave_out snd_pcm_writei couldn't recover from error: %s\n",
                                  snd_strerror(iFramesJustWritten));

                  return;

               }

               iFramesJustWritten = 0;

               continue;

            }

            iFramesToWrite -= iFramesJustWritten;

            int iBytesJustWritten = snd_pcm_frames_to_bytes(m_ppcm, iFramesJustWritten);

            //information("snd_pcm_frames_to_bytes iBytesJustWritten " << iBytesJustWritten);

            //information("m_pwaveformat->m_waveformat.nSamplesPerSec " << m_pwaveformat->m_waveformat.nSamplesPerSec);

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

         if (iBuffer >= 0)
         {

            m_psynthtask->on_free(iBuffer);

         }

      }


      class ::time wave_out::out_get_time_for_synch()
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

         return integral_millisecond(dwPosition / 1000.0);

      }


      //void MyCallback(snd_async_handler_t *pcm_callback);
      //What happens in the callback is fairly simple; this is simply and roughly what it will look like:


//      void MyCallback(snd_async_handler_t *pcm_callback)
//      {
//         wave_out *p = (wave_out *) snd_async_handler_get_callback_private(pcm_callback);
//         p->on_my_callback();
////         snd_pcm_t *pcm_handle = snd_async_handler_get_pcm(pcm_callback);
////         snd_pcm_sframes_t avail;
////         int err;
////
////         avail = snd_pcm_avail_update(pcm_handle);
////         while (avail >= period_size) {
////            snd_pcm_writei(pcm_handle, MyBuffer, period_size);
////            avail = snd_pcm_avail_update(handle);
////         }
//      }


      void wave_out::out_start(const class time &time)
      {

         synchronous_lock sl(synchronization());

         if (m_eoutstate == ::wave::e_out_state_playing)
         {

            //return success;

            return;

         }

         if (m_eoutstate != ::wave::e_out_state_opened && m_eoutstate != ::wave::e_out_state_stopped)
         {

            //return error_failed;

            throw ::exception(error_wrong_state);

         }

         int err = 0;

         if ((err = snd_pcm_prepare(m_ppcm)) < 0)
         {

            information ("out_start: Cannot prepare audio interface for use (%s)\n", snd_strerror(err));

            throw ::exception(error_failed);

         }

//         m_pcm_callback = nullptr;
//
//         snd_async_add_pcm_handler(&m_pcm_callback, m_ppcm, MyCallback, this);

         //information("out_start: snd_pcm_prepare OK");

         m_bStarted = false;

         ::wave::out::out_start(time);

         if (!m_estatusWave)
         {

            information("out_start: ::wave::out::out_start FAILED");

            throw ::exception(m_estatusWave);

         }

         snd_pcm_start(m_ppcm);

//         m_pthreadWriter = fork([&]()
//         {
//
//            alsa_write_thread();
//
//         });

         information("out_start: ::wave::out::out_start OK");

         //return success;

      }


      int wave_out::defer_underrun_recovery(int err)
      {

         return snd_pcm_recover(m_ppcm, err, 0);

//         if (err == -EPIPE)
//         {
//
//            information("underrun_recovery, going to snd_pcm_prepare: %s\n", snd_strerror(err));
//
//
//
//            if (err < 0)
//            {
//
//               information("Can't recover from underrun, snd_pcm_prepare failed: %s\n", snd_strerror(err));
//
//            }
//
//         }
//         else if (err == -ESTRPIPE)
//         {
//
//            information("underrun_recovery, snd_pcm_prepare returned -ESTRPIPE: %s\n", snd_strerror(err));
//
//            while ((err = snd_pcm_resume(m_ppcm)) == -EAGAIN)
//            {
//
//               information("underrun_recovery, snd_pcm_resume returned -EAGAIN: %s\n", snd_strerror(err));
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
//                  information("Can't recovery from suspend, snd_pcm_prepare failed: %s\n", snd_strerror(err));
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



