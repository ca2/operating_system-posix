#pragma once


namespace multimedia
{


   namespace audio_sndio
   {


      //void translate(WAVEFORMATEX & formatex, ::multimedia::audio::wave_format * pwaveformat);
      //void translate(WAVEHDR & wavehdr, ::multimedia::audio::wave_buffer * pwavebuffer, int iIndex);
      //LPWAVEHDR create_new_WAVEHDR(::multimedia::audio::wave_buffer * pwavebuffer, int iIndex);
      //LPWAVEHDR get_os_data(::multimedia::audio::wave_buffer * pwavebuffer, int iIndex);

      CLASS_DECL_AUDIO_SNDIO ::e_status translate_sndio(int err);


   } // namespace audio_sndio


} // namespace multimedia





