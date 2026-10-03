#pragma once
#include "sunaudio.h"

namespace multimedia::audio_sunaudio
{
   class CLASS_DECL_AUDIO_SUNAUDIO wave_out : virtual public sun_object
   {
   public:
      ::string default_audio_device() override;
      int device_open(int precision, ::u32 rate, unsigned char channels) override;
      int device_close() override;
      int device_pause() override;
      int device_resume() override;
      memsize device_write(const void * data, memsize bytes) override;
      ::string device_error_message(int error) override;
   };
}
