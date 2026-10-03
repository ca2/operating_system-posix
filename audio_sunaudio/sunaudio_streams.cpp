// Deliberately compiled without ca2 headers or its precompiled header:
// illumos STREAMS headers declare struct mutex, which conflicts with ca2 mutex.
#include "sunaudio_streams.h"
#include <errno.h>
#include <sys/ioctl.h>
#include <stropts.h>

extern "C" int audio_sunaudio_flush_stream(int fd)
{
   return ioctl(fd, I_FLUSH, FLUSHW) == -1 ? errno : 0;
}
