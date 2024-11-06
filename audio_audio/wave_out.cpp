#include "framework.h"
//#include "aura/message.h"
#include "wave_out.h"
#include "translation.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"

#include <sys/types.h>
#include <sys/param.h>
#include <sys/fcntl.h>
#ifndef __linux__
#include <sys/filio.h>
#endif
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <mad.h>
#define NOARTS
#ifdef __sun
#include <sys/stropts.h>
#endif

//#include "audio_dev.h"

#if (BYTE_ORDER == BIG_ENDIAN)
#define WORDS_BIGENDIAN
#else
#undef WORDS_BIGENDIAN
#endif

#ifdef __DragonFly__
typedef unsigned int nfds_t;
#endif



#include <sys/time.h>
#include <stdio.h>



namespace multimedia
{


   namespace audio_audio
   {


      wave_out::wave_out()
      {

         m_bDirectOutput = false;
         m_eoutstate = ::wave::e_out_state_initial;
         m_pthreadCallback = NULL;
         m_estatusWave = success;
         m_bWrite = false;
         m_bStarted = false;
         m_bStop = false;

         m_iFrameCount = 2048;

      }


      wave_out::~wave_out()
      {

      }


      void wave_out::install_message_routing(::channel *pchannel)
      {

         ::wave::out::install_message_routing(pchannel);

      }


      void wave_out::init_task()
      {

         ::wave::out::init_task();

      }


      void wave_out::term_task()
      {

         ::wave::out::term_task();

         thread::term_task();

      }


      int wave_out::_frames_to_bytes(int iFrameCount)
      {

         return m_pwaveformat->m_waveformat.nChannels * (m_pwaveformat->m_waveformat.wBitsPerSample) * iFrameCount / 8;

      }


      void wave_out::out_open_ex(thread *pthreadCallback, unsigned int uiSamplesPerSec, unsigned int uiChannelCount, unsigned int uiBitsPerSample,
                            ::wave::enum_purpose epurpose)
      {

         synchronous_lock sl(synchronization());

         informationf("multimedia::audio_alsa::out_open_ex");

         if (m_eoutstate != ::wave::e_out_state_initial)
         {

            return;

         }

         if (epurpose == ::wave::e_purpose_playback)
         {

            //          m_dwPeriodTime =  6 * 1000; /* period time in us */

            //m_iBufferCountEffective = 16;

            m_timeBufferSizeHint = 400_ms;

            m_iBufferCountHint = 8;

            m_iFrameCount = 2000;

            m_iBufferCount = 8;
            
            m_iHighWaterMark = 8;
            
            m_iLowWaterMark = 3;

            printf("::wave::purpose_playback %d\n", m_iFrameCount);

         }
         else
         {

            m_timeBufferSizeHint = 100_ms;

            m_iFrameCount = 1152;

            //m_iFrameByteCount = uiSamplesPerSec / 20;

            m_iBufferCountHint = 3;

            m_iBufferCount = 4;

            m_iHighWaterMark = 4;
            
            m_iLowWaterMark = 2;

            printf("::wave::* %d\n", m_iFrameCount);

         }

//         m_iBufferCount = m_iBufferCountEffective;

         m_pthreadCallback = pthreadCallback;

///         ASSERT(m_pAudioDevCtx == NULL);

         ASSERT(m_eoutstate == ::wave::e_out_state_initial);

         m_pwaveformat->m_waveformat.wFormatTag = 0;
         m_pwaveformat->m_waveformat.nChannels = (unsigned short) uiChannelCount;
         m_pwaveformat->m_waveformat.nSamplesPerSec = uiSamplesPerSec;
         m_pwaveformat->m_waveformat.wBitsPerSample = (unsigned short) uiBitsPerSample;
         m_pwaveformat->m_waveformat.nBlockAlign =
                 m_pwaveformat->m_waveformat.wBitsPerSample * m_pwaveformat->m_waveformat.nChannels / 8;
         m_pwaveformat->m_waveformat.nAvgBytesPerSec =
                 m_pwaveformat->m_waveformat.nSamplesPerSec * m_pwaveformat->m_waveformat.nBlockAlign;
         //m_pwaveformat->cbSize            = 0;


	/*
	 * Fork off the audio device slave at the (possibly) elevated priority
	 */

   m_bStop = false;
   
   const char * adev="/dev/audio";
   
        auto estatus = audio_dev_init(adev);

	if (estatus.failed()) 
        {

                printf_line("audio_audio::wave_out::out_open_ex failed (audio_dev_init:%s)", adev);

		throw ::exception(estatus);
	}

//	audio_dev_register_read_callback(m_pAudioDevCtx, play_event, m_pAudioDevCtx);

// m_pAudioDevContext
//          if (!(m_estatusWave = translate_sndio(this->sndio_open(m_sampleformat, nullptr))))
//          {

//             throw ::exception(m_estatusWave);

//          }

//         if(m_iBufferCount < m_iBufferCountEffective)
//         {
//
//            m_iBufferCountEffective = m_iBufferCount;
//
//         }

         //unsigned int uBufferSize = _frames_to_bytes(m_hdl, m_framesPeriodSize);

//         m_uiBufferTime = m_framesBuffer * 1000 * 1000 / uiSamplesPerSec;

         information() << "frame_count : " << m_iFrameCount;

         unsigned int uBufferSize = _frames_to_bytes(m_iFrameCount);

         information() << "uBufferSize in bytes : " << uBufferSize;

         information() << "buffer count : " << m_iBufferCount;

         out_get_buffer()->PCMOutOpen(this, uBufferSize, m_iBufferCount, 128, m_pwaveformat, m_pwaveformat);

         m_pprebuffer->open(m_pwaveformat->m_waveformat.nChannels, m_iBufferCount, uBufferSize);

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

         m_psynthtask->m_iWaitBuffer = 1;

         m_eoutstate = ::wave::e_out_state_opened;

         m_epurpose = epurpose;

         printf_line("audio_audio::wave_out::out_open_ex succeeded (audio_dev_init:%s)", adev);

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

         ::e_status mmr = success;
audio_dev_close();
//        mmr = audio_dev_close(m_pAudioDevCtx);

//         m_pAudioDevCtx = NULL;

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
//         m_estatusWave = translate_sndio(sndio_pause());
audio_dev_pause();

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
    //     m_estatusWave = translate_sndio(audio_dev_unpause(m_pAudioDevCtx));
audio_dev_unpause();

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

//         if (m_hdl != NULL)
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

//         if (m_hdl == NULL)
  //       {

    //        informationf("alsa_out_buffer_ready m_hdl == NULL");

      //      return false;

        // }

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

         auto iFramesToWrite = m_iFrameCount;

         int iBytesToWrite = _frames_to_bytes(iFramesToWrite);

         ::e_status estatus = success;

         auto iFrameFreeCount = 0;

         unsigned char *pbufferata;

         memory m;

         ::wave::buffer::item *pbuffer = nullptr;

         if (iBuffer >= 0)
         {

            pbuffer = m_pwavebuffer->m_buffera[iBuffer];

            pbufferata = (unsigned char *) out_get_buffer_data(iBuffer);

         }
         else
         {

            m.set_size(iBytesToWrite);

            m.zero();

            pbufferata = (unsigned char *) m.data();

         }

         synchronous_lock sl(synchronization());

         synchronous_lock synchronouslockBuffer(pbuffer ? pbuffer->synchronization() : nullptr);

         int iZero = 0;

         while (iBytesToWrite > 0)
         {

	    int iFramesToWrite = iBytesToWrite * 8 / (m_pwaveformat->m_waveformat.nChannels * m_pwaveformat->m_waveformat.wBitsPerSample);

            //iFramesToWrite = minimum(iFramesToWrite, 1152);

            int iFramesJustWritten = 0;

            int iRet = audio_dev_write((char *) pbufferata, iFramesToWrite);

	    if(iRet == AD_NO_ERROR)
            {
		
               iFramesJustWritten = iFramesToWrite;

     	       printf_line("audio_dev_write iFramesJustWritten %d", iFramesJustWritten);

	       if (!m_bStarted)
               {

                  m_timeStart.Now();

                  m_bStarted = true;

	       }

	    }
	    else if(iRet == AD_WOULD_BLOCK)
	    {

               preempt(5_ms);

     	       printf_line("audio_dev_write AD_WOULD_BLOCK");

	    }
	    else if (iRet == AD_UNDER_RUN)
            {

     	       printf_line("audio_dev_write AD_UNDER_RUN");

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
            
            }

  //          iFramesToWrite -= iFramesJustWritten;

//	}

            int iBytesJustWritten = _frames_to_bytes(iFramesJustWritten);

            m_pprebuffer->m_iBytes += iBytesJustWritten;

            pbufferata += iBytesJustWritten;

            iBytesToWrite -= iBytesJustWritten;


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


      void wave_out::out_start(const class time &time)
      {

         synchronous_lock sl(synchronization());

         if (m_eoutstate == ::wave::e_out_state_playing)
         {

            return;

         }

         if (m_eoutstate != ::wave::e_out_state_opened && m_eoutstate != ::wave::e_out_state_stopped)
         {

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

//         m_estatusWave = translate_sndio(audio_dev_unpause(m_pAudioDevCtx));
audio_dev_unpause();

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




#define	ACF_NEW_TRACK	(1 << 0)

#define _ADC_QUIT	(-1)


static const audio_dev_backend *audio_dev_backends[] = {
#ifndef NOSUN
	&audio_dev_sun,
#endif
#ifndef NOOSS
	&audio_dev_pcm,
#endif
#ifndef NOARTS
	&audio_dev_arts,
#endif
	NULL
};


      ::e_status wave_out::audio_dev_init(const char *dev)
      {

         m_pdata = ___new pcm_data;

         ::memset(m_pdata, 0, sizeof(pcm_data));
         
         ::string strDev(dev);

         application()->fork([this, strDev]()
         {

            audio_dev_slave(strDev);
         
         });

         return ::success;
         
      }


      void wave_out::audio_dev_close()
      {
         
         m_bStop = true;

      }


      int wave_out::audio_dev_output(pcm_buffer *pbuffer)
      {

         unsigned char *buf;
         size_t len, played, written;
         ssize_t rv = 0;
         
         if (pbuffer->m_iBufferChannelCount != m_pdata->m_iDataChannelCount ||
         pbuffer->m_iBufferSampleRate != m_pdata->m_iDataSampleRate) 
         {

            print_line("audio_dev_output config");

            if ((ac_device->ad_config)(ac_devarg, pbuffer->m_iBufferSampleRate, pbuffer->m_iBufferChannelCount, m_iLowWaterMark, m_iHighWaterMark) < 0)
            {
            
               return (-1);
               
            }

            m_pdata->m_iDataChannelCount = pbuffer->m_iBufferChannelCount;
            m_pdata->m_iDataSampleRate = pbuffer->m_iBufferSampleRate;
            
         }

         written = 0;

         played = pbuffer->m_iBufferPosition;
         buf = &pbuffer->m_pBufferData[played];
         len = pbuffer->m_iLength;
         
         for (;len > 0; played += rv, written += rv, len -= rv, buf = &buf[rv]) 
         {

            printf_line("audio_dev_output writing %d bytes", len);
               
            do 
            {
            
               rv = (ac_device->ad_output)(ac_devarg, buf, len);
               
            }
            while (rv < 0 && errno == EINTR);

            if (rv < 0 || (rv == 0 && ac_device->ad_pollfd == NULL))
            {
            
               break;
               
            }
            
         }

         pbuffer->m_iBufferPosition = played;
         pbuffer->m_iLength = len;

         written /= pbuffer->m_iBufferChannelCount;
         written /= sizeof(uint16_t);
         m_pdata->pb_playsamples += written;

         return ((rv >= 0) ? 0 : -1);
         
      }


      void wave_out::audio_dev_pause()
      {

         ac_paused = true;

      }


      void wave_out::audio_dev_unpause()
      {

         ac_paused = false;

      }


      void wave_out::audio_dev_slave(const char *dev)
      {
    
         pcm_data *pb = m_pdata;
         const audio_dev_backend *ad;
         pcm_buffer *pbuffer;
         const char *ext = strchr(dev, ':');
         int rv, prodpeer = 0;

         if (ext == NULL)
         {
            
            ad = audio_dev_backends[0];
            
         }
         else 
         {
            int i;
            for (i = 0; (ad = audio_dev_backends[i]) != NULL; i++) 
            {
               if (strncmp(ad->ad_name, dev, strlen(ad->ad_name)) == 0)
               {
                  break;
               }
            }

            if (ad == NULL)
            {
               ad = audio_dev_backends[0];
               
            }
         }

         ac_device = ad;
         
         if (ext != NULL)
         {
            dev += strlen(ad->ad_name);
         }
         
         ac_devarg = (ad->ad_init)(dev);
         
         if (ac_devarg == NULL) 
         {

            fprintf(stderr, "audio_dev_slave: failed to open back-end\n");
            fflush(stderr);
            return;
            
         }

         print_line("audio_dev_slave: succeeded to open back-end.");

         ac_paused = true;
      
         for (;!m_bStop;) 
         {
      
            while (m_pdata->m_iHead != m_pdata->m_iTail && m_pdata->m_iPurge == 0) 
            {
            
               int idx = m_pdata->m_iTail;

               pbuffer = &m_pdata->m_buffera[idx];

               if (!ac_paused && pbuffer->m_iLength) 
               {
               
                  rv = audio_dev_output(pbuffer);
                  
                  if (rv < 0 && errno != EAGAIN) 
                  {
                     
                     print_line("audio_slave: audio_dev_output failed(1)");
                     
                     return;
                     
                  }
                  
               }

               if (pbuffer->m_iLength != 0)
               {
               
                  break;
                  
               }

               m_pdata->m_iTail = (idx + 1) % m_iBufferCount;
               
               prodpeer = 1;
               
            }
            
            if (m_pdata->m_iPurge) 
            {
               m_pdata->m_iPurge = 0;
               m_pdata->m_iTail = m_pdata->m_iHead;
               prodpeer = 1;
            }

            m_eventRead.ResetEvent();

            do 
            {
            
               m_eventRead._wait(5_ms);
               
            } while (ac_paused && m_pdata->m_iHead == m_pdata->m_iTail);
            
         }
         
      }


      int wave_out::audio_dev_write(void *pcmdata, int samplecount)
      {

         //int head, tail, nbufs;
         

         auto iHead = (m_pdata->m_iHead + 1) % m_iBufferCount;
         
         if(iHead == m_pdata->m_iTail) 
         {
            
            return AD_WOULD_BLOCK;
            
         }

         auto pbuffer = &m_pdata->m_buffera[m_pdata->m_iHead];

         pbuffer->m_iBufferChannelCount = m_pwaveformat->m_waveformat.nChannels;
         pbuffer->m_iBufferSampleRate = m_pwaveformat->m_waveformat.nSamplesPerSec;
         pbuffer->m_iBufferPosition = 0;
         pbuffer->m_iLength = samplecount * pbuffer->m_iBufferChannelCount * 2;
         
         memcpy(pbuffer->m_pBufferData, pcmdata, pbuffer->m_iLength);
         
         m_pdata->m_iHead = iHead;
         
         ac_buffersamples += samplecount;

         m_eventRead.SetEvent();

         //tail = m_pdata->m_iTail;
         
         //nbufs = head - tail;
         
         //if (nbufs < 0)
         //{
         
         //   nbufs += m_iBufferCount;
            
         //}

         //if (nbufs > PCM_LOW_WATER)
         //{
         
         //   return AD_UNDER_RUN;
            
         //}


         return AD_NO_ERROR;
      
      }
      

      int wave_out::audio_dev_flush_wait()
      {

         while (m_pdata->m_iHead != m_pdata->m_iTail)
         {
         
            m_eventRead._wait();
      
         }

         ac_buffersamples = m_pdata->pb_playsamples = 0;

         return AD_NO_ERROR;
         
      }


      int wave_out::audio_dev_purge_wait()
      {

         m_pdata->m_iPurge = 1;

         while (m_pdata->m_iHead != m_pdata->m_iTail && m_pdata->m_iPurge)
         {
         
            m_eventRead._wait();
            
         }

         ac_buffersamples = m_pdata->pb_playsamples = 0;

         return (AD_NO_ERROR);
      
      }


      huge_integer wave_out::audio_dev_buffer_time()
      {
         
         if (!m_pdata->m_iDataSampleRate)
         {
            
            return 0;
            
         }
            
         auto diff = ac_buffersamples - m_pdata->pb_playsamples;

         return ((diff * 10) / m_pdata->m_iDataSampleRate);
         
      }


		huge_integer wave_out::audio_dev_played_time()
		{

			if (!m_pdata->m_iDataSampleRate)
			{

				return 0;

			}

			return ((m_pdata->pb_playsamples * 10) /m_pdata->m_iDataSampleRate);

		}
      

   } // namespace audio_audio


} // namespace multimedia



