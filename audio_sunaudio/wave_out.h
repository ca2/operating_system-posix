#pragma once


#include "snd_pcm.h"
#include "sunaudio.h"


namespace multimedia
{


   namespace audio_sunaudio
   {


      class  CLASS_DECL_AUDIO_SUNAUDIO wave_out :
         virtual public sun_object
      {
      public:


         bool                    m_bWrite;
         int                     m_iBuffer;
         bool                    m_bStarted;
         unsigned long long                   m_uStart;
         //snd_pcm_status_t *      m_pstatus;
         //timeval                 m_timevalStart;
         class ::time            m_timeStart;
         //::int_array             m_iaSent;

         //snd_async_handler_t *   m_pcm_callback;

         wave_out();
         ~wave_out() override;


         void install_message_routing(::channel * pchannel) override;

         class ::time out_get_position() override;
         //imedia_position out_get_position();

         //virtual ::e_status wave_out_open(::thread * pthreadCallback, ::collection::count iBufferCount, ::collection::count iBufferSampleCount) override;
         void out_open_ex(::thread * pthreadCallback, unsigned int uiSamplesPerSec, unsigned int uiChannelCount, unsigned int uiBitsPerSample, ::wave::enum_purpose epurpose) override;
         void out_stop() override;
         void out_close() override;
         void out_pause() override;
         void out_restart() override;


         virtual int _frames_to_bytes(int iFrameCount);


         //snd_pcm_t * out_get_safe_PCM();

         //virtual void alsa_write_thread();

         void out_on_playback_end() override;
         void out_filled(::collection::index iBuffer) override;
         virtual bool alsa_should_play();

         void init_task() override;
         void term_task() override;

         void out_start(const class time & time) override;

         //virtual int defer_underrun_recovery(int err);

         class ::time out_get_time_for_synch();

         //void on_my_callback();

         //void send_buffer(int iBuffer);


      };


   } // namespace audio_sunaudio


} // namespace multimedia



