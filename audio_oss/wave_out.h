#pragma once
#include "audio_sunaudio/_.h"
#include "audio_sunaudio/wave_out.h"

namespace multimedia::audio_oss
{
   // Reuse ca2 buffer/state handling, with OSS-specific device operations.
   class CLASS_DECL_AUDIO_OSS wave_out :
      public ::multimedia::audio_sunaudio::wave_out
   {
   public:
      wave_out() = default;
      ~wave_out() override;
      ::string default_audio_device() override;
      int sunaudio_open(int precision, ::u32 rate, unsigned char channels) override;
      int sunaudio_close() override;
      int sunaudio_drain() override;
      int sunaudio_flush() override;
      memsize sunaudio_write(const void * data, memsize bytes) override;
      int sunaudio_pause() override;
      int sunaudio_unpause() override;
      long sunaudio_avail() override;
   };
}
