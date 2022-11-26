#pragma once


#include "snd_pcm.h"
#include "app-core/audio/wave/out.h"


namespace multimedia
{


   namespace audio_alsa
   {


      class  CLASS_DECL_AUDIO_ALSA wave_out :
         virtual public snd_pcm,
         virtual public ::wave::out
      {
      public:


         bool                    m_bWrite;
         int                     m_iBuffer;
         bool                    m_bStarted;
         ::u64                   m_uStart;
         snd_pcm_status_t *      m_pstatus;
         timeval                 m_timevalStart;


         wave_out();
         virtual ~wave_out();


         void install_message_routing(::channel * pchannel) override;

         class ::time out_get_position() override;
         //imedia_position out_get_position();

         //virtual ::e_status wave_out_open(::thread * pthreadCallback, ::count iBufferCount, ::count iBufferSampleCount) override;
         void out_open_ex(::thread * pthreadCallback, ::u32 uiSamplesPerSec, ::u32 uiChannelCount, ::u32 uiBitsPerSample, ::wave::enum_purpose epurpose) override;
         void out_stop() override;
         void out_close() override;
         void out_pause() override;
         void out_restart() override;

         snd_pcm_t * out_get_safe_PCM();

         //virtual void alsa_write_thread();

         void out_on_playback_end() override;
         void out_filled(index iBuffer) override;
         virtual bool alsa_should_play();

         void init_task() override;
         void term_task() override;

         void out_start(const class time & time) override;

         virtual int defer_underrun_recovery(int err);

         class ::time out_get_time_for_synch();


      };


   } // namespace audio_alsa


} // namespace multimedia



