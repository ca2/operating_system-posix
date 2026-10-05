#pragma once
#include "sunaudio.h"

namespace multimedia::audio_sunaudio
{
   class CLASS_DECL_AUDIO_SUNAUDIO wave_out : virtual public sun_object
   {
   public:
      ::u32 m_uLastPlayedSamples = 0;
      ::u64 m_uPlayedFrames = 0;
      class ::time m_timeQueueProgress;
      bool m_bQueueAccounting = true;
      ::string default_audio_device() override;
      int device_open(int precision, ::u32 rate, unsigned char channels) override;
      int device_close() override;
      int device_pause() override;
      int device_resume() override;
      memsize device_write(const void * data, memsize bytes) override;
      memsize device_queued_bytes() override;
      int device_minimum_queue_frames() override { return 1024; }
      ::string device_error_message(int error) override;
   };
}
