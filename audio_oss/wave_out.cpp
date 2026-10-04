#include "platform.h"
#include "wave_out.h"
#include <sys/soundcard.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

namespace multimedia::audio_oss
{
   wave_out::~wave_out()
   {
      device_close();
   }

   ::string wave_out::default_audio_device()
   {
      const char * device = getenv("AUDIODEV");
      return device && *device ? device : "/dev/dsp";
   }

   int wave_out::device_open(int precision, ::u32 rate, unsigned char channels)
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
      m_iPrecision = precision;
      m_bReportedNonzero = false;
      m_bReportedAudibleLevel = false;
      information() << "audio_oss opened device=" << m_strDevice
         << " rate=" << sampleRate << " channels=" << channelCount
         << " precision=" << precision << " format=" << format;
      return 0;
   }

   int wave_out::device_close()
   {
      if (m_fd == -1)
         return 0;
      device_flush();
      const int fd = m_fd;
      m_fd = -1;
      return close(fd) == -1 ? errno : 0;
   }

   int wave_out::device_drain()
   {
      return ioctl(m_fd, SNDCTL_DSP_SYNC, nullptr) == -1 ? errno : 0;
   }

   int wave_out::device_flush()
   {
      return ioctl(m_fd, SNDCTL_DSP_RESET, nullptr) == -1 ? errno : 0;
   }

   memsize wave_out::device_write(const void * data, memsize bytes)
   {
      ssize_t written;
      do
      {
         written = write(m_fd, data, bytes);
      } while (written < 0 && errno == EINTR);
      if (written < 0)
         return errno == EAGAIN ? 0 : -errno;
      // Inspect only successfully submitted PCM. Two reports per open at most:
      // initial nonzero samples and samples above approximately -30 dBFS.
      if (written > 0 && m_iPrecision == 16 && !m_bReportedAudibleLevel)
      {
         int peak = 0;
         const auto * pcm = static_cast<const unsigned char *>(data);
         for (ssize_t offset = 0; offset + 1 < written; offset += 2)
         {
            short sample;
            memcpy(&sample, pcm + offset, sizeof(sample));
            int magnitude = sample < 0 ? -(int) sample : (int) sample;
            if (magnitude > peak)
               peak = magnitude;
         }
         if ((!m_bReportedNonzero && peak > 0) || peak >= 1024)
         {
            information() << "audio_oss submitted PCM device=" << m_strDevice
               << " bytes=" << written << " peak16=" << peak;
            m_bReportedNonzero = true;
            if (peak >= 1024)
               m_bReportedAudibleLevel = true;
         }
      }
      return written;
   }

   int wave_out::device_pause()
   {
      // illumos implements SETTRIGGER as a compatibility no-op. Draining
      // stops at the end of the queued buffers without dropping PCM data;
      // the shared wave state then prevents further buffer submissions.
#if defined(__SUNOS__)
      return device_drain();
#else
      int trigger = 0;
      return ioctl(m_fd, SNDCTL_DSP_SETTRIGGER, &trigger) == -1 ? errno : 0;
#endif
   }

   int wave_out::device_resume()
   {
#if defined(__SUNOS__)
      return 0;
#else
      int trigger = PCM_ENABLE_OUTPUT;
      return ioctl(m_fd, SNDCTL_DSP_SETTRIGGER, &trigger) == -1 ? errno : 0;
#endif
   }

   ::string wave_out::device_error_message(int error)
   {
      return strerror(error);
   }
}
