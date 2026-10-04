#pragma once
#include "audio/audio/wave/buffered_wave_out.h"

namespace multimedia::audio_oss
{
   class CLASS_DECL_AUDIO_OSS wave_out : public ::wave::buffered_wave_out
   {
   public:
      int m_fd = -1;
      int m_iPrecision = 0;
      bool m_bReportedNonzero = false;
      bool m_bReportedAudibleLevel = false;

      wave_out() = default;
      ~wave_out() override;
      ::string default_audio_device() override;
      int device_open(int precision, ::u32 rate, unsigned char channels) override;
      int device_close() override;
      int device_drain();
      int device_flush();
      memsize device_write(const void * data, memsize bytes) override;
      int device_pause() override;
      int device_resume() override;
      ::string device_error_message(int error) override;
   };
}
