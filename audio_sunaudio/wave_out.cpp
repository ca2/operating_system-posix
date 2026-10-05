#include "platform.h"
#include "wave_out.h"
#include "audio/audio/wave/format.h"
#include <sys/ioctl.h>
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
         m_uLastPlayedSamples = m_audioinfo.play.samples;
         m_uPlayedFrames = 0;
         m_timeQueueProgress = ::time::now();
         m_bQueueAccounting = true;
      }
      return error;
   }
   int wave_out::device_close() { return sunaudio_close(); }
   memsize wave_out::device_queued_bytes()
   {
      if (!m_bQueueAccounting) return -1;
      audio_info_t status;
      if (ioctl(m_fd, AUDIO_GETINFO, &status) == -1) return -1;
      // Accumulate unsigned deltas so a long-running stream handles the
      // native 32-bit sample counter wrapping without losing its queue limit.
      auto delta = (::u32) (status.play.samples - m_uLastPlayedSamples);
      if (delta) m_timeQueueProgress = ::time::now();
      m_uPlayedFrames += delta;
      m_uLastPlayedSamples = status.play.samples;
      auto playedBytes = m_uPlayedFrames * m_pwaveformat->m_waveformat.nBlockAlign;
      // Some native drivers account only whole large DMA buffers. Do not
      // starve such a driver forever by waiting for a sub-buffer counter.
      if (m_llWrittenBytes > playedBytes && m_timeQueueProgress.elapsed() > 250_ms)
      {
         warning() << "sunaudio sample counter stalled; using native blocking-write pacing";
         m_bQueueAccounting = false;
         return -1;
      }
      return m_llWrittenBytes > playedBytes ? m_llWrittenBytes - playedBytes : 0;
   }
   int wave_out::device_pause() { return sunaudio_pause(); }
   int wave_out::device_resume()
   {
      m_timeQueueProgress = ::time::now();
      return sunaudio_unpause();
   }
   memsize wave_out::device_write(const void * data, memsize bytes)
   {
      return sunaudio_write(data, bytes);
   }
   ::string wave_out::device_error_message(int error)
   {
      return sunaudio_strerror(error);
   }
}
