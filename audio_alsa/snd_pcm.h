#pragma once


#include "audio/audio/wave/base.h"


namespace multimedia
{


   namespace audio_alsa
   {


      class CLASS_DECL_AUDIO_ALSA snd_pcm :
         virtual public ::wave::base
      {
      public:


         snd_pcm_t *                      m_ppcm;
         snd_pcm_hw_params_t *            m_phwparams;
         snd_pcm_sw_params_t *            m_pswparams;
         snd_async_handler_t *            m_phandler;
         int                              m_iCurrentBuffer;
         snd_pcm_uframes_t                m_frameCount;
         int                              m_iBufferCount;

         int                              m_iPeriodMin;
         int                              m_iPeriodMax;


         snd_pcm();
         virtual ~snd_pcm();


         ::e_status snd_pcm_open(snd_pcm_stream_t stream_type);
         ::e_status snd_pcm_close();


         void print_snd_pcm_status();


      };


   } // namespace audio_alsa


} // namespace multimedia




