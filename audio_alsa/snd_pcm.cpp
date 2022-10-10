#include "framework.h"
#include "snd_pcm.h"


namespace multimedia
{


   namespace audio_alsa
   {


      snd_pcm::snd_pcm()
      {

         m_ppcm = NULL;
         m_phwparams = NULL;
         m_pswparams = NULL;
         m_phandler = NULL;
         m_iCurrentBuffer = 0;
         //m_dwBufferTime    = 100 * 1000; /* ring buffer length in us */
      }

      snd_pcm::~snd_pcm()
      {

         if (m_ppcm != NULL)
         {

            snd_pcm_close();
         }
      }


      ::e_status snd_pcm::snd_pcm_open(snd_pcm_stream_t stream_type)
      {

         INFORMATION("snd_pcm::snd_pcm_open");

         if(stream_type == SND_PCM_STREAM_PLAYBACK)
         {

            INFORMATION("Open for SND_PCM_STREAM_PLAYBACK");

         }
         else if(stream_type == SND_PCM_STREAM_CAPTURE)
         {

            INFORMATION("Open for SND_PCM_STREAM_CAPTURE");

         }
         else
         {

            WARNING("Unknown stream_type!!");

         }

         ::e_status mmr;

         ASSERT(m_ppcm == NULL);

         ::pointer<::wave::format>pformat = m_pwaveformat;

         int err;
         short buf[128];

         int cardNum = -1;
         int devNum = -1;
         int subDevNum = -1;
         int subDevCount = 0;
         string strFormat;
         string_array straName;
         string_array straDevice;

         // Start with first card
         cardNum = -1;
         bool bFound = false;

         for (;;)
         {

            // Get next sound card's card number. When "cardNum" == -1, then ALSA
            // fetches the first card
            if ((err = snd_card_next(&cardNum)) < 0)
            {
               FORMATTED_TRACE("Can't get the next card number: %s\n", snd_strerror(err));
               break;
            }

            // No more cards? ALSA sets "cardNum" to -1 if so
            if (cardNum < 0)
               break;

            // Open this card's control interface. We specify only the card number -- not
            // any device nor sub-device too
            {

               snd_ctl_t *cardHandle;

               string strFormat;

               strFormat.format("hw:%i", cardNum);
               if ((err = snd_ctl_open(&cardHandle, strFormat, 0)) < 0)
               {
                  FORMATTED_TRACE("Can't open card %i: %s\n", cardNum, snd_strerror(err));
                  continue;
               }


               // Start with the first wave device on this card
               devNum = -1;

               for (;;)
               {

                  // Get the number of the next wave device on this card
                  if ((err = snd_ctl_pcm_next_device(cardHandle, &devNum)) < 0)
                  {
                     FORMATTED_TRACE("Can't get next wave device number: %s\n", snd_strerror(err));
                     break;
                  }

                  // No more wave devices on this card? ALSA sets "devNum" to -1 if so.
                  // NOTE: It's possible that this sound card may have no wave devices on it
                  // at all, for example if it's only a MIDI card
                  if (devNum < 0)
                     break;

                  // To get some info about the subdevices of this wave device (on the card), we need a
                  // snd_pcm_info_t, so let's allocate one on the stack
                  snd_pcm_info_t *pcmInfo = nullptr;
                  snd_pcm_info_alloca(&pcmInfo);
                  memset(pcmInfo, 0, snd_pcm_info_sizeof());

                  // Tell ALSA which device (number) we want info about
                  snd_pcm_info_set_device(pcmInfo, devNum);

                  // Get info on the wave outs of this device
                  snd_pcm_info_set_stream(pcmInfo, stream_type);

                  subDevCount = snd_pcm_info_get_subdevices_count(pcmInfo);

                  FORMATTED_TRACE("\nFound %i wave output subdevices on card %i, %i : %s \n", subDevCount, cardNum, devNum, snd_strerror(err));

                  if (subDevCount <= 0)
                  {

                     strFormat.format("hw:%d,%d", cardNum, devNum);

                     // NOTE: If there's only one subdevice, then the subdevice number is immaterial,
                     // and can be omitted when you specify the hardware name
                     straName.add(snd_pcm_info_get_name(pcmInfo));

                     straDevice.add(strFormat);
                  }
                  else
                  {

                     for (subDevNum = 0; subDevNum < subDevCount; subDevNum++)
                     {

                        snd_pcm_info_set_subdevice(pcmInfo, subDevNum);

                        if ((err = snd_ctl_pcm_info(cardHandle, pcmInfo)) < 0)
                        {

                           FORMATTED_TRACE("No wave output subdevice hw:%i,%i : %s\n", cardNum, devNum, snd_strerror(err));

                           continue;
                        }

                        strFormat.format("hw:%d,%d,%d", cardNum, devNum, subDevNum);

                        straName.add(snd_pcm_info_get_name(pcmInfo));

                        straDevice.add(strFormat);
                     }

                  }

               }

               // Close the card's control interface after we're done with it
               snd_ctl_close(cardHandle);

            }

         }



         //snd_config_update_free_global();

         if (straDevice.get_count() < 0)
         {

            return error_failed;
         }

         for (int i = 0; i < straDevice.get_count(); i++)
         {

            INFORMATION("snd_pcm::snd_pcm_open " << straName[i] << " : " << straDevice[i]);
         }

         //string strHw = "hw:0,0";
         string strHw = "default";

         if ((err = ::snd_pcm_open(&m_ppcm, strHw, stream_type, SND_PCM_NONBLOCK | SND_PCM_ASYNC)) < 0)
         {

            ERROR("cannot open audio device " << strHw << " (" << snd_strerror(err) << ")");

            return error_failed;

         }

         snd_pcm_hw_params_malloc(&m_phwparams);

         if ((err = snd_pcm_hw_params_any(m_ppcm, m_phwparams)) < 0)
         {

            ERROR("cannot initialize hardware parameter structure (" << snd_strerror(err) << ")");

            return error_failed;

         }

         if ((err = snd_pcm_hw_params_set_access(m_ppcm, m_phwparams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0)
         {

            ERROR("cannot set access type (" << snd_strerror(err) << ")");

            return error_failed;

         }

         snd_pcm_format_t format = SND_PCM_FORMAT_S16_LE;

         if (pformat->m_waveformat.wBitsPerSample == 16)
         {

            format = SND_PCM_FORMAT_S16_LE;

         }
         else if (pformat->m_waveformat.wBitsPerSample == 8)
         {

            format = SND_PCM_FORMAT_U8;

         }

         if ((err = snd_pcm_hw_params_set_format(m_ppcm, m_phwparams, format)) < 0)
         {

            string strError = snd_strerror(err);

            ERROR("cannot set sample format (" << strError << ")");

            return error_failed;

         }

         unsigned int uiFreq = pformat->m_waveformat.nSamplesPerSec;

         int dir = 0;

         if ((err = snd_pcm_hw_params_set_rate_near(m_ppcm, m_phwparams, &uiFreq, &dir)) < 0)
         {

            ERROR("cannot set sample rate (" << snd_strerror(err) << ")");

            return error_failed;

         }

         pformat->m_waveformat.nSamplesPerSec = uiFreq;

         if ((err = snd_pcm_hw_params_set_channels(m_ppcm, m_phwparams, pformat->m_waveformat.nChannels)) < 0)
         {

            ERROR("cannot set channel count (" << snd_strerror(err) << ")");

            return error_failed;

         }

         unsigned int uPeriodMin = 0;

         int dirPeriodMin = 0;

         err = snd_pcm_hw_params_get_periods_min(m_phwparams, &uPeriodMin, &dirPeriodMin);

         if (err < 0)
         {

            const char *pszError = snd_strerror(err);

            ERROR("snd_pcm_hw_params_get_periods_min failed: (" << pszError << ")");

            return error_failed;

         }

         unsigned int uPeriodMax = 0;

         int dirPeriodMax = 0;

         err = snd_pcm_hw_params_get_periods_max(m_phwparams, &uPeriodMax, &dirPeriodMax);

         if (err < 0)
         {

            const char *pszError = snd_strerror(err);

            ERROR("snd_pcm_hw_params_get_period_size failed: " << pszError);

            return error_failed;

         }

         m_iBufferCount = maximum(m_iBufferCount, uPeriodMin);

         m_iBufferCount = minimum(m_iBufferCount, uPeriodMax);

         err = snd_pcm_hw_params_set_periods(m_ppcm, m_phwparams, m_iBufferCount, 0);

         if (err < 0)
         {

            const char *pszError = snd_strerror(err);

            ERROR("snd_pcm_hw_params_get_periods failed: " << pszError);

            return error_failed;

         }

         snd_pcm_uframes_t uPeriodSizeMin = 0;

         int dirPeriodSizeMin = 0;

         err = snd_pcm_hw_params_get_period_size_min(m_phwparams, &uPeriodSizeMin, &dirPeriodSizeMin);

         if (err < 0)
         {

            const char *pszError = snd_strerror(err);

            ERROR("snd_pcm_hw_params_get_period_size_min failed: " << pszError);

            return error_failed;

         }

         snd_pcm_uframes_t uPeriodSizeMax = 0;

         int dirPeriodSizeMax = 0;

         err = snd_pcm_hw_params_get_period_size_max(m_phwparams, &uPeriodSizeMax, &dirPeriodSizeMax);

         if (err < 0)
         {

            const char *pszError = snd_strerror(err);

            ERROR("snd_pcm_hw_params_get_period_size_max failed: " << pszError);

            return error_failed;

         }

         m_frameCount = maximum(m_frameCount, uPeriodSizeMin);

         m_frameCount = minimum(m_frameCount, uPeriodSizeMax / m_iBufferCount);

         err = snd_pcm_hw_params_set_period_size(m_ppcm, m_phwparams, m_frameCount, 0);

         if (err < 0)
         {

            const char *pszError = snd_strerror(err);

            ERROR("snd_pcm_hw_params_get_period_size failed: " << pszError);

            return error_failed;

         }

         //m_framesPeriodSize = size;

         snd_pcm_uframes_t size = 0;

         err = snd_pcm_hw_params_get_buffer_size(m_phwparams, &size);

         if(err < 0)
         {

            ERROR("Unable to get buffer size for playback: " << snd_strerror(err));

            return error_failed;

         }

         //
         //m_framesBufferSize = m_iBufferCount * m_framesPeriodSize;

         //= (m_framesBufferSize / );

         if ((err = snd_pcm_hw_params(m_ppcm, m_phwparams)) < 0)
         {

            ERROR("cannot set parameters (" << snd_strerror(err) << ")");

            return error_failed;

         }

         snd_pcm_sw_params_malloc(&m_pswparams);

         err = snd_pcm_sw_params_current(m_ppcm, m_pswparams);

         if (err < 0)
         {

            ERROR("Unable to determine current m_pswparams: " << snd_strerror(err));

            return error_failed;

         }

         err = snd_pcm_sw_params_set_tstamp_mode(m_ppcm, m_pswparams, SND_PCM_TSTAMP_ENABLE);

         if (err < 0)
         {

            ERROR("Unable to set tstamp mode : " << snd_strerror(err));

            return error_failed;

         }

         err = snd_pcm_sw_params_set_tstamp_type(m_ppcm, m_pswparams, SND_PCM_TSTAMP_TYPE_MONOTONIC);

         if (err < 0)
         {

            ERROR("Unable to set tstamp type : " << snd_strerror(err));

            return error_failed;

         }

         err = snd_pcm_sw_params_set_start_threshold(m_ppcm, m_pswparams, m_frameCount * m_iBufferCount);

         if (err < 0)
         {

            ERROR("Unable to set start threshold type : " << snd_strerror(err));

            return error_failed;

         }

         snd_pcm_uframes_t u1 = 0;

//         err = snd_pcm_sw_params_get_stop_threshold(m_ppcm, m_pswparams, &u1);
//
//         if (err < 0)
//         {
//
//            printf("Unable to set start threshold type : %s\n", snd_strerror(err));
//
//            return error_failed;
//
//         }

         snd_pcm_uframes_t u2 = 1;

         err = snd_pcm_sw_params_set_stop_threshold(m_ppcm, m_pswparams, u2);

         if (err < 0)
         {

            ERROR("Unable to set start threshold type : " << snd_strerror(err));

            return error_failed;

         }

         err = snd_pcm_sw_params(m_ppcm, m_pswparams);

         if (err < 0)
         {

            ERROR("Unable to set swparams_p : " << snd_strerror(err));

            return error_failed;

         }


//         int dir = 0;
//
//         snd_pcm_uframes_t uFrameCount = 0;
//
//         err = snd_pcm_hw_params_get_period_size(m_ppcm, m_phwparams, &uFrameCount, &dir);
//
//         if(err >= 0 && uFrameCount > 0)
//         {
//
//            m_frameCount = uFrameCount;
//            printf("AAAAAAAAAAAAAAAAA snd_pcm_hw_params_get_period_size %d\n", uFrameCount);
//
//         }

         return success;

      }


      ::e_status snd_pcm::snd_pcm_close()
      {

         if (m_ppcm == NULL)
         {

            return success;
         }

         int err;

         if ((err = ::snd_pcm_close(m_ppcm)) < 0)
         {

            FORMATTED_TRACE("failed to close successfully sound interface (%s)\n", snd_strerror(err));

            return error_failed;
         }

         return success;

      }


   } // namespace audio_alsa


} // namespace multimedia



