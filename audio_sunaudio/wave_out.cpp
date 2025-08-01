#include "framework.h"
//#include "aura/message.h"
#include "wave_out.h"
#include "translation.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/prototype/time/_text_stream.h"
#include "audiodev.h"

#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
// long long timestamp2ns(snd_htimestamp_t t)
// {
//    long long nsec;
//
//    nsec = t.tv_sec * 1000000000;
//    nsec += t.tv_nsec;
//
//    return nsec;
//
// }

/*
long long timediff(snd_htimestamp_t t1, snd_htimestamp_t t2)
{

   long long nsec1, nsec2;

   nsec1 = timestamp2ns(t1);
   nsec2 = timestamp2ns(t2);

   return nsec1 - nsec2;

}*/


namespace multimedia
{


   namespace audio_sunaudio
   {


      wave_out::wave_out()
      {

         m_bDirectOutput = false;
         m_eoutstate = ::wave::e_out_state_initial;
         m_pthreadCallback = NULL;
         m_estatusWave = success;
         m_bWrite = false;
         m_bStarted = false;

         //m_pstatus = NULL;

         //snd_pcm_status_malloc(&m_pstatus);

      }


      wave_out::~wave_out()
      {

         //snd_pcm_status_free(m_pstatus);

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


      int wave_out::_frames_to_bytes(int iFrameCount)
      {

         //return sf_get_frame_size(m_sampleformat) * iFrameCount;
         
         return m_audioinfo.play.precision * m_audioinfo.play.channels * iFrameCount / 8;

      }


      void
      wave_out::out_open_ex(thread *pthreadCallback, unsigned int uiSamplesPerSec, unsigned int uiChannelCount, unsigned int uiBitsPerSample,
                            ::wave::enum_purpose epurpose)
      {

         synchronous_lock sl(synchronization());

         informationf("multimedia::audio_sunaudio::wave_out::out_open_ex");

         //if (m_hdl != NULL && m_eoutstate != ::wave::e_out_state_initial)
         if (m_eoutstate != ::wave::e_out_state_initial)
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

            m_iBufferCountHint = 8;

            m_iFrameByteCount = uiSamplesPerSec / 20;

            m_iBufferCount = 8;

            printf("::wave::purpose_playback %d\n", m_iFrameByteCount);

         }
         else
         {

            m_timeBufferSizeHint = 100_ms;

            m_iFrameByteCount = 1024;

            //m_iFrameByteCount = uiSamplesPerSec / 20;

            m_iBufferCountHint = 4;

            m_iBufferCount = 4;

            printf("::wave::* %d\n", m_iFrameByteCount);

         }

//         m_iBufferCount = m_iBufferCountEffective;

         m_pthreadCallback = pthreadCallback;

         //ASSERT(m_hdl == NULL);
         
         information() << "open_ex(1)";

         ASSERT(m_eoutstate == ::wave::e_out_state_initial);
         
         information() << "open_ex(2)";

         m_pwaveformat->m_waveformat.wFormatTag = 0;
         m_pwaveformat->m_waveformat.nChannels = (unsigned short) uiChannelCount;
         m_pwaveformat->m_waveformat.nSamplesPerSec = uiSamplesPerSec;
         m_pwaveformat->m_waveformat.wBitsPerSample = (unsigned short) uiBitsPerSample;
         m_pwaveformat->m_waveformat.nBlockAlign =
                 m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels / 8;
         m_pwaveformat->m_waveformat.nAvgBytesPerSec =
                 m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;
         //m_pwaveformat->cbSize            = 0;
         
         information() << "open_ex(3)";
         
         ::string strDevice;
         
         information() << "going to try to get audio_device override (audio_device.txt)";
         
         strDevice = file()->safe_get_string(directory_system()->home() / "audio_device.txt");
         
         information() << "audio_device.txt = \"" << strDevice << "\".";
         
         if(strDevice.is_empty())
         {
            
            information() << "going to try to run command \"audiocfg list\".";
            
            //string strAudioCfgListOutput = node()->get_posix_shell_command_output("audiocfg list");
            audiodev_refresh();
            int iAudioDevCount = audiodev_count();
            
            information() << "audiodev_count(): " << iAudioDevCount;
            
            if(iAudioDevCount > 0)
            {
            
               auto paudiodev =	audiodev_get(0);
               
               information() << "First Device Name: " << paudiodev->xname;
               
               strDevice = "/dev/" + ::string(paudiodev->xname);
               
            }
            
            //::string_array straLines;
            
            //straLines.add_lines(strAudioCfgListOutput);
            
            //if(straLines.size() >= 1)
            //{
            
               //::string strFirstLine = straLines.first();
               
               //auto stra = strFirstLine.explode(" ");
               
               //if(stra.size() >= 3)
               //{
                  
                  //strDevice = "/dev/" + stra[2];
                  
               //}
               
            //}
            
         }
         
         if(strDevice.has_character())
         {
            
            m_strDevice = strDevice;
            
         }
         
         if (!(m_estatusWave = translate_sunaudio(this->sunaudio_open(uiBitsPerSample, uiSamplesPerSec, uiChannelCount))))
         {

            throw ::exception(m_estatusWave);

         }

//         if(m_iBufferCount < m_iBufferCountEffective)
//         {
//
//            m_iBufferCountEffective = m_iBufferCount;
//
//         }

         //unsigned int uBufferSize = _frames_to_bytes(m_hdl, m_framesPeriodSize);

//         m_uiBufferTime = m_framesBuffer * 1000 * 1000 / uiSamplesPerSec;

         information() << "frame_count : " << m_iFrameByteCount;

         unsigned int uBufferSize = _frames_to_bytes(m_iFrameByteCount);

         information() << "uBufferSize in bytes : " << uBufferSize;

         information() << "buffer count : " << m_iBufferCount;

         out_get_buffer()->PCMOutOpen(this, uBufferSize, m_iBufferCount, 128, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(m_pwaveformat->m_waveformat.nChannels, m_iBufferCount, m_iFrameByteCount);

//         m_pprebuffer->SetMinL1BufferCount(out_get_buffer()->GetBufferCount());

//         int err;
//
//         if((err = snd_pcm_sw_params_current(m_hdl, m_pswparams)) < 0)
//         {
//
//            informationf("unable to determine current m_pswparams for playback: %s\n", snd_strerror(err));
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
//         snd_pcm_sframes_t framesThreshold = (m_iBufferCount - 1) * m_iFrameByteCount;
//
//         // start the transfer when the buffer is almost full:
//         if((errSet = snd_pcm_sw_params_set_start_threshold(m_hdl, m_pswparams, framesThreshold)) < 0
//            || (errSave = snd_pcm_sw_params(m_hdl, m_pswparams)) < 0)
//         {
//
//            informationf("unable to set start threshold mode for playback: %s\n", snd_strerror(err));
//
//         }
//
//         if((err = snd_pcm_sw_params_current(m_hdl, m_pswparams)) < 0)
//         {
//
//            informationf("unable to determine current m_pswparams for playback (2): %s\n", snd_strerror(err));
//
//            throw ::exception(error_failed);
//
//         }
//
//         errSet = 0;
//         errSave = 0;
//
//         // allow the transfer when at least m_framesPeriodSize samples can be processed
//         if((err = snd_pcm_sw_params_set_avail_min(m_hdl, m_pswparams, m_iFrameByteCount)) < 0
//            || ((errSave = snd_pcm_sw_params(m_hdl, m_pswparams)) < 0))
//         {
//
//            informationf("unable to set avail min for playback: %s\n", snd_strerror(err));
//
//         }
//
//         if((err = snd_pcm_sw_params_current(m_hdl, m_pswparams)) < 0)
//         {
//
//            informationf("unable to determine current m_pswparams for playback (3): %s\n", snd_strerror(err));
//
//            throw ::exception(error_failed);
//
//         }
//
//         errSet = 0;
//         errSave = 0;
//
//         if((err = snd_pcm_sw_params_set_tstamp_mode(m_hdl, m_pswparams, SND_PCM_TSTAMP_ENABLE)) < 0
//            || (errSave = snd_pcm_sw_params(m_hdl, m_pswparams)) < 0
//                 )
//         {
//
//            informationf("unable to set time stamp mode: %s\n", snd_strerror(err));
//
//         }
//
//         if((err = snd_pcm_sw_params_current(m_hdl, m_pswparams)) < 0)
//         {
//
//            informationf("unable to determine current m_pswparams for playback (4): %s\n", snd_strerror(err));
//
//            throw ::exception(error_failed);
//
//         }
//
//         errSet = 0;
//         errSave = 0;
//
//         if((err = snd_pcm_sw_params_set_tstamp_type(m_hdl, m_pswparams,SND_PCM_TSTAMP_TYPE_GETTIMEOFDAY)) <0
//            || (errSave = snd_pcm_sw_params(m_hdl, m_pswparams)) < 0
//                 )
//         {
//
//            informationf("unable to set time stamp type (SND_PCM_TSTAMP_TYPE_GETTIMEOFDAY): %s\n", snd_strerror(err));
//
//            if((err = snd_pcm_sw_params_current(m_hdl, m_pswparams)) < 0)
//            {
//
//               informationf("unable to determine current m_pswparams for playback (3): %s\n", snd_strerror(err));
//
//               throw ::exception(error_failed);
//
//            }
//
//            if((err = snd_pcm_sw_params_set_tstamp_type(m_hdl, m_pswparams,SND_PCM_TSTAMP_TYPE_MONOTONIC)) <0
//               || (errSave = snd_pcm_sw_params(m_hdl, m_pswparams)) < 0
//                    )
//            {
//
//               informationf("unable to set time stamp type (SND_PCM_TSTAMP_TYPE_MONOTONIC): %s\n", snd_strerror(err));
//
//            }
//
//         }


//         // write the parameters to the playback device
//         if((err = snd_pcm_sw_params(m_hdl, m_pswparams)) < 0)
//         {
//
//            informationf("unable to set sw params for playback: %s\n", snd_strerror(err));
//
//            throw ::exception(error_failed);
//
//         }

         //m_psynthtask->m_iWaitBuffer = 1;

         m_eoutstate = ::wave::e_out_state_opened;

         m_epurpose = epurpose;

         //return success;

      }


      void wave_out::out_close()
      {

         synchronous_lock sl(synchronization());

         informationf("multimedia::audio_alsa::out_close");

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

         mmr = translate_sunaudio(sunaudio_close());

         //m_hdl = NULL;

         ::wave::out::out_close();

         m_eoutstate = ::wave::e_out_state_initial;

         //return success;

      }


      void wave_out::out_stop()
      {

         synchronous_lock sl(synchronization());

         informationf("multimedia::audio_alsa::out_stop");

         if (m_eoutstate != ::wave::e_out_state_playing && m_eoutstate != ::wave::e_out_state_paused)
         {

            throw ::exception(error_wrong_state);

         }

         //m_pprebuffer->stop();

         m_eoutstate = ::wave::e_out_state_stopping;

         // // waveOutReset
         // // The waveOutReset function stops playback on the given
         // // waveform-audio_alsa output device and resets the current position
         // // to zero. All pending playback buffers are marked as done and
         // // returned to the application.
         // m_estatusWave = translate_alsa(snd_pcm_drain(m_hdl));
         //
         // if (m_estatusWave == success)
         // {
         //
         //    m_eoutstate = ::wave::e_out_state_opened;
         //
         // }

         if (!m_estatusWave)
         {

            throw ::exception(m_estatusWave);

         }

      }


      void wave_out::out_pause()
      {

         synchronous_lock sl(synchronization());

         ASSERT(m_eoutstate == ::wave::e_out_state_playing);

         informationf("multimedia::audio_alsa::out_pause");

         if (m_eoutstate != ::wave::e_out_state_playing)
         {

            throw ::exception(error_wrong_state);

         }

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_alsa output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = translate_sunaudio(sunaudio_pause());

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

         informationf("multimedia::audio_alsa::out_restart");

         if (m_eoutstate != ::wave::e_out_state_paused)
         {

            throw ::exception(error_wrong_state);

         }

         // waveOutReset
         // The waveOutReset function stops playback on the given
         // waveform-audio_alsa output device and resets the current position
         // to zero. All pending playback buffers are marked as done and
         // returned to the application.
         m_estatusWave = translate_sunaudio(sunaudio_unpause());

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

         //if (m_hdl != NULL)
         {

            //snd_pcm_sframes_t frames;

            //snd_pcm_delay(m_hdl, &frames);

            auto iBytes = m_pprebuffer->m_iBytes;

            auto iFrameSize = wave_base_get_frame_size();

            auto iFrame = iBytes / iFrameSize;

            //double dSecond = (double) (iFrame - frames) / (double) m_pwaveformat->m_waveformat.nSamplesPerSec;

            double dSecond = (double) iFrame / (double) m_pwaveformat->m_waveformat.nSamplesPerSec;

            time.m_iSecond = floor(dSecond);

            time.m_iNanosecond = fmod(dSecond, 1.0) * 1'000'000'000.0;

            //}

//            if(snd_pcm_status(m_hdl, m_pstatus) == 0)
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

            //informationf("test");

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

         informationf("multimedia::audio_alsa::out_on_playback_end");

         ::wave::out::out_on_playback_end();

      }


      // snd_pcm_t *wave_out::out_get_safe_PCM()
      // {
      //
      //    if (::is_null(this))
      //    {
      //
      //       return NULL;
      //
      //    }
      //
      //    return m_hdl;
      //
      // }


      bool wave_out::alsa_should_play()
      {

         if (!::task_get_run())
         {

            return false;

         }

         //if (m_hdl == NULL)
         //{

            //informationf("alsa_out_buffer_ready m_hdl == NULL");

            //return false;

         //}

         if (m_eoutstate != ::wave::e_out_state_playing && m_eoutstate != ::wave::e_out_state_stopping)
         {

            informationf("alsa_out_buffer_ready failure: !playing && !stopping");

            return false;

         }

         return true;

      }


//      void wave_out::on_my_callback()
//      {
//
//         int iBuffer = -1;
//
//         informationf("on_my_callback");
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
//               informationf("m_iaSent.pick_last(): " << iBuffer);
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


      void wave_out::out_filled(::collection::index iBuffer)
      {

//         static class ::time t;
//
//         informationf("out_filled: " << iBuffer);
//         informationf("thread: " << pthread_self());
//         informationf("elapsed micros: " << t.elapsed().integral_microsecond());

//         t.Now();

         auto iFramesToWrite = m_iFrameByteCount;

         int iBytesToWrite = _frames_to_bytes(iFramesToWrite);

         ::e_status estatus = success;

         long iByteFreeCount = 0;

         {

            synchronous_lock sl(synchronization());

            //if (m_hdl == NULL)
            //{

               //return;

            //}

            //iBytesToWrite = _frames_to_bytes(m_hdl, iFramesToWrite);

         }
         
         if(0)
         {

         while (::task_get_run())
         {

            {

                //synchronous_lock sl(synchronization());

                ////print_snd_pcm_status();

            iByteFreeCount = sunaudio_avail();


                if (iByteFreeCount == -EAGAIN)
                {

                   continue;

               }
               else if (iByteFreeCount < 0)
               {
                  
                  continue;

/////                  const_char_pointer pszError = //snd_strerror(iFrameFreeCount);
/////                   //informationf("ALSA wave_out snd_pcm_avail error: %s (%d)\n", pszError, iFrameFreeCount);
//////
//////                   //iFrameFreeCount = defer_underrun_recovery(iFrameFreeCount);
////// /*
//////                   if (iFrameFreeCount >= 0)
//////                   {
//////
//////                      informationf("ALSA wave_out snd_pcm_avail underrun recovery success (snd_pcm_avail)");
//////
//////                      break;
//////
//////                   }
//////
//////                   informationf("ALSA wave_out snd_pcm_avail minimum unsigned char count %d\n", iFramesToWrite);*/
//////
//////                   m_eoutstate = ::wave::e_out_state_opened;
//////
//////                   m_estatusWave = error_failed;
//////
//////                   informationf("ALSA wave_out snd_pcm_avail error: %s\n", snd_strerror(iFrameFreeCount));
//////
//////                   return;
//////
                  }
                  
                  
                  
               }
               
               auto waitFrames = iBytesToWrite;

               auto μsecondsWait =
                  microsecond_time(((iBytesToWrite - iByteFreeCount) *8/(m_audioinfo.play.precision * 
                  m_audioinfo.play.channels)) * 100'000 / m_pwaveformat->m_waveformat.nSamplesPerSec);


               information() << " written: " << iBytesToWrite << " free : " << iByteFreeCount
                         << " waiting\"" << (iBytesToWrite - iByteFreeCount) << " waiting(us) : " << μsecondsWait;


               if (iByteFreeCount >= iBytesToWrite)
               {

                  break;

               }

             //}

            ////auto waitFrames = (iFramesToWrite - iFrameFreeCount);

            preempt(μsecondsWait);

         }
         
      }

         unsigned char *pdata;

         memory m;

         ::wave::buffer::item *pbuffer = nullptr;

         if (iBuffer >= 0)
         {

            pbuffer = m_pwavebuffer->m_buffera[iBuffer];

            pdata = (unsigned char *) out_get_buffer_data(iBuffer);

         }
         else
         {

            m.set_size(iBytesToWrite);

            m.zero();

            pdata = (unsigned char *) m.data();

         }

         synchronous_lock sl(synchronization());

         //m_iaSent.insert_at(0, iBuffer);

         synchronous_lock synchronouslockBuffer(pbuffer ? pbuffer->synchronization() : nullptr);

         int iZero = 0;

         int iBytesJustWritten = 0;

         while (iBytesToWrite > 0)
         {

            iBytesJustWritten = sunaudio_write((const_char_pointer )pdata, iBytesToWrite);

            //informationf("snd_pcm_writei iFramesJustWritten " << iFramesJustWritten);

            if (!m_bStarted)
            {

               m_timeStart.Now();

               //gettimeofday(&m_timevalStart, nullptr);

               m_bStarted = true;

            }

//            if (iFramesJustWritten == -OP_ERROR_INTERNAL)
            if(iBytesJustWritten <=0)
            {
               
               preempt(1_ms * (int)((float)( iBytesToWrite*8000.f 
                /(float)(m_audioinfo.play.sample_rate * 
               m_audioinfo.play.precision * 
               m_audioinfo.play.channels))));

               informationf("snd_pcm_writei -OP_ERROR_INTERNAL");

               continue;

            }
            
            
            //iFramesJustWritten = i;
            // else if (iFramesJustWritten == -EAGAIN)
            // {
            //
            //    //informationf("snd_pcm_writei -EAGAIN");
            //
            //    sl.unlock();
            //
            //    //snd_pcm_wait(m_hdl, 10);
            //    preempt(10_ms);
            //
            //    sl.lock();
            //
            //    continue;
            //
            // }
            // else if (iFramesJustWritten < 0)
            // {
            //
            //    informationf("snd_pcm_writei Underrun");
            //
            //    informationf("ALSA wave_out snd_pcm_writei error: %s (%d)\n", snd_strerror(iFramesJustWritten),
            //                    iFramesJustWritten);
            //
            //    iFramesJustWritten = defer_underrun_recovery(iFramesJustWritten);
            //
            //    if (iFramesJustWritten < 0 && iFramesJustWritten != -EAGAIN)
            //    {
            //
            //       m_eoutstate = ::wave::e_out_state_opened;
            //
            //       m_estatusWave = error_failed;
            //
            //       informationf("ALSA wave_out snd_pcm_writei couldn't recover from error: %s\n",
            //                       snd_strerror(iFramesJustWritten));
            //
            //       return;
            //
            //    }
            //
            //    iFramesJustWritten = 0;
            //
            //    continue;
            //
            // }
            //
            //iFramesToWrite -= iFramesJustWritten;

            //int iBytesJustWritten = _frames_to_bytes(iFramesJustWritten);

            //informationf("_frames_to_bytes iBytesJustWritten " << iBytesJustWritten);

            //informationf("m_pwaveformat->m_waveformat.nSamplesPerSec " << m_pwaveformat->m_waveformat.nSamplesPerSec);

            m_pprebuffer->m_iBytes += iBytesJustWritten;

            pdata += iBytesJustWritten;

            iBytesToWrite -= iBytesJustWritten;

            //            if(iBytesToWrite > 0)
            //            {
            //
            //               sl.unlock();
            //
            //               snd_pcm_wait(m_hdl, 100);
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

            return zero_t{};

         }

         int64_t dwPosition = m_pprebuffer->m_iBytes;

         dwPosition *= 1000;

         if (m_pwaveformat->m_waveformat.nSamplesPerSec <= 0)
         {

            return zero_t{};

         }

         dwPosition /= m_pwaveformat->m_waveformat.nSamplesPerSec;

         return millisecond_time(dwPosition / 1000.0);

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

         // if ((err = snd_pcm_prepare(m_hdl)) < 0)
         // {
         //
         //    informationf("out_start: Cannot prepare audio interface for use (%s)\n", snd_strerror(err));
         //
         //    throw ::exception(error_failed);
         //
         // }

//         m_pcm_callback = nullptr;
//
//         snd_async_add_pcm_handler(&m_pcm_callback, m_hdl, MyCallback, this);

         //informationf("out_start: snd_pcm_prepare OK");

         m_bStarted = false;

         ::wave::out::out_start(time);

         if (!m_estatusWave)
         {

            informationf("out_start: ::wave::out::out_start FAILED");

            throw ::exception(m_estatusWave);

         }

         m_estatusWave = translate_sunaudio(sunaudio_unpause());

         if (!m_estatusWave)
         {

            informationf("out_start: ::wave::out::out_start FAILED");

            throw ::exception(m_estatusWave);

         }

//         m_pthreadWriter = fork([&]()
//         {
//
//            alsa_write_thread();
//
//         });

         informationf("out_start: ::wave::out::out_start OK");

         //return success;

      }


//       int wave_out::defer_underrun_recovery(int err)
//       {
//
//          return snd_pcm_recover(m_hdl, err, 0);
//
// //         if (err == -EPIPE)
// //         {
// //
// //            informationf("underrun_recovery, going to snd_pcm_prepare: %s\n", snd_strerror(err));
// //
// //
// //
// //            if (err < 0)
// //            {
// //
// //               informationf("Can't recover from underrun, snd_pcm_prepare failed: %s\n", snd_strerror(err));
// //
// //            }
// //
// //         }
// //         else if (err == -ESTRPIPE)
// //         {
// //
// //            informationf("underrun_recovery, snd_pcm_prepare returned -ESTRPIPE: %s\n", snd_strerror(err));
// //
// //            while ((err = snd_pcm_resume(m_hdl)) == -EAGAIN)
// //            {
// //
// //               informationf("underrun_recovery, snd_pcm_resume returned -EAGAIN: %s\n", snd_strerror(err));
// //
// //               sleep(1); /* wait until the suspend flag is released */
// //
// //            }
// //
// //            if (err < 0)
// //            {
// //
// //               err = snd_pcm_prepare(m_hdl);
// //
// //               if (err < 0)
// //               {
// //
// //                  informationf("Can't recovery from suspend, snd_pcm_prepare failed: %s\n", snd_strerror(err));
// //
// //               }
// //
// //            }
// //
// //         }
// //
// //         return err;
//
//       }


   } // namespace audio_sunaudio


} // namespace multimedia



