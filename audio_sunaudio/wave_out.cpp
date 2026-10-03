#include "platform.h"
#include "wave_out.h"
#include "audio/audio/wave/format.h"
#if defined(__SUNOS__)
#include <stdlib.h>
#else
#include "audiodev.h"
#endif

namespace multimedia::audio_sunaudio
{
      ::string wave_out::default_audio_device()
      {
#if defined(__SUNOS__)
         const char * device = getenv("AUDIODEV");
         return device && *device ? device : "/dev/audio";
#else
         audiodev_refresh();
         if (audiodev_count() > 0)
         {
            auto device = audiodev_get(0);
            return "/dev/" + ::string(device->xname);
         }
         return "/dev/audio";
#endif
      }


   int wave_out::device_open(int precision, ::u32 rate, unsigned char channels)
   {
      const int error = sunaudio_open(precision, rate, channels);
      if (!error)
      {
         // Publish the negotiated format without leaking audio_info_t to audio.
         auto & format = m_pwaveformat->m_waveformat;
         format.wBitsPerSample = m_audioinfo.play.precision;
         format.nChannels = m_audioinfo.play.channels;
         format.nSamplesPerSec = m_audioinfo.play.sample_rate;
         format.nBlockAlign = format.wBitsPerSample * format.nChannels / 8;
         format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;
      }
      return error;
   }
   int wave_out::device_close() { return sunaudio_close(); }
   int wave_out::device_pause() { return sunaudio_pause(); }
   int wave_out::device_resume() { return sunaudio_unpause(); }
   memsize wave_out::device_write(const void * data, memsize bytes)
   {
      return sunaudio_write(data, bytes);
   }
   ::string wave_out::device_error_message(int error)
   {
      return sunaudio_strerror(error);
   }
}
