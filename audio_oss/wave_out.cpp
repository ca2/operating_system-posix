#include "platform.h"
#include "wave_out.h"
#include <sys/soundcard.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

namespace multimedia::audio_oss
{
   wave_out::~wave_out()
   {
      sunaudio_close();
   }

   ::string wave_out::default_audio_device()
   {
      const char * device = getenv("AUDIODEV");
      return device && *device ? device : "/dev/dsp";
   }

   int wave_out::sunaudio_open(int precision, ::u32 rate, unsigned char channels)
   {
      if (m_fd != -1)
         return EEXIST;
      int format;
      switch (precision)
      {
      case 8: format = AFMT_S8; break;
      case 16: format = AFMT_S16_NE; break;
#ifdef AFMT_S24_PACKED
      case 24: format = AFMT_S24_PACKED; break;
#endif
#ifdef AFMT_S32_NE
      case 32: format = AFMT_S32_NE; break;
#endif
      default: return EINVAL;
      }
      if (!rate || !channels)
         return EINVAL;

      m_fd = open(m_strDevice, O_WRONLY);
      if (m_fd == -1)
         return errno;

      const int requestedFormat = format;
      int channelCount = channels;
      int sampleRate = rate;
      int error = 0;
      if (ioctl(m_fd, SNDCTL_DSP_SETFMT, &format) == -1 ||
          ioctl(m_fd, SNDCTL_DSP_CHANNELS, &channelCount) == -1 ||
          ioctl(m_fd, SNDCTL_DSP_SPEED, &sampleRate) == -1)
         error = errno;
      else if (format != requestedFormat || channelCount != channels || sampleRate != (int) rate)
         error = ENOTSUP;
      if (error)
      {
         close(m_fd);
         m_fd = -1;
         return error;
      }
      // Metadata for the shared PCM buffer lifecycle, not a Sun audio ioctl.
      m_audioinfo.play.precision = precision;
      m_audioinfo.play.channels = channels;
      m_audioinfo.play.sample_rate = rate;
      m_llWrittenBytes = 0;
      m_iLastSecond = -1;
      return 0;
   }

   int wave_out::sunaudio_close()
   {
      if (m_fd == -1)
         return 0;
      sunaudio_flush();
      const int fd = m_fd;
      m_fd = -1;
      return close(fd) == -1 ? errno : 0;
   }

   int wave_out::sunaudio_drain()
   {
      return ioctl(m_fd, SNDCTL_DSP_SYNC, nullptr) == -1 ? errno : 0;
   }

   int wave_out::sunaudio_flush()
   {
      return ioctl(m_fd, SNDCTL_DSP_RESET, nullptr) == -1 ? errno : 0;
   }

   memsize wave_out::sunaudio_write(const void * data, memsize bytes)
   {
      ssize_t written;
      do
      {
         written = write(m_fd, data, bytes);
      } while (written < 0 && errno == EINTR);
      if (written < 0)
         return -errno;
      m_llWrittenBytes += written;
      return written;
   }

   int wave_out::sunaudio_pause()
   {
      // illumos implements SETTRIGGER as a compatibility no-op. Draining
      // stops at the end of the queued buffers without dropping PCM data;
      // the shared wave state then prevents further buffer submissions.
#if defined(__SUNOS__)
      return sunaudio_drain();
#else
      int trigger = 0;
      return ioctl(m_fd, SNDCTL_DSP_SETTRIGGER, &trigger) == -1 ? errno : 0;
#endif
   }

   int wave_out::sunaudio_unpause()
   {
#if defined(__SUNOS__)
      return 0;
#else
      int trigger = PCM_ENABLE_OUTPUT;
      return ioctl(m_fd, SNDCTL_DSP_SETTRIGGER, &trigger) == -1 ? errno : 0;
#endif
   }

   long wave_out::sunaudio_avail()
   {
      count_info position = {};
      if (ioctl(m_fd, SNDCTL_DSP_GETOPTR, &position) == -1)
         return -errno;
      const int frameSize = m_audioinfo.play.channels * m_audioinfo.play.precision / 8;
      return frameSize ? position.bytes / frameSize : 0;
   }
}
