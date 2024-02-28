#pragma once


namespace multimedia
{


   namespace audio_mmsystem
   {


      class  CLASS_DECL_AUDIO_ALSA wave_in :
         virtual public ::multimedia::audio::wave_in
      {
      public:



         snd_pcm_t *                      m_ppcm;
         snd_pcm_hw_params_t *            m_phwparams;



         wave_in(sp(base_application) papp);
         virtual ~wave_in();


         virtual bool wave_in_initialize_encoder();

         virtual ::multimedia::result wave_in_add_buffer(int32_t iBuffer);
         virtual ::multimedia::result wave_in_add_buffer(LPWAVEHDR lpwavehdr);

         HWAVEIN wave_in_get_safe_HWAVEIN();
         virtual void * get_os_data();

         ::multimedia::result wave_in_open(int32_t iBufferCount, int32_t iBufferSampleCount);
         ::multimedia::result wave_in_close();
         ::multimedia::result wave_in_stop();
         ::multimedia::result wave_in_start();
         ::multimedia::result wave_in_reset();

         virtual void translate_wave_in_message(::signal_details * pobj);

         virtual bool initialize_instance();
         virtual int32_t exit_instance();
         virtual void pre_translate_message(::signal_details * pobj);

         static void CALLBACK wave_in_proc(HWAVEIN hwi, ::u32 uMsg, ::u32 dwInstance, ::u32 dwParam1, ::u32 dwParam2);

         WAVEFORMATEX * wave_format();
         LPWAVEHDR wave_hdr(int iBuffer);


      };


   } // namespace audio_mmsystem


} // namespace multimedia




