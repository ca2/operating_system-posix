/* Standalone diagnostic: gcc test_pcm.c -lm -o /tmp/audio_oss_test_pcm
   Usage: /tmp/audio_oss_test_pcm device rate [native-s16-stereo.raw]
   Sends three seconds of a quiet 440 Hz tone using ca2's PCM format and
   write size, without the ca2 mixer, decoder, or output threads. */
#include <sys/soundcard.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int main(int argc, char **argv)
{
   int rate = argc > 2 ? atoi(argv[2]) : 44100;
   int requested_rate = rate;
   int channels = 2, format = AFMT_S16_NE;
   int fd;
   FILE *input = NULL;
   int16_t pcm[2048];
   long frame = 0;
   if (argc < 2 || rate <= 0 || rate > 192000)
   {
      fprintf(stderr, "Usage: %s device [sample-rate] [native-s16-stereo.raw]\n", argv[0]);
      return 1;
   }
   fd = open(argv[1], O_WRONLY);
   if (fd == -1) { perror("open"); return 1; }
   if (ioctl(fd, SNDCTL_DSP_SETFMT, &format) == -1 ||
       ioctl(fd, SNDCTL_DSP_CHANNELS, &channels) == -1 ||
       ioctl(fd, SNDCTL_DSP_SPEED, &rate) == -1)
   { perror("configure PCM"); close(fd); return 1; }
   printf("device=%s rate=%d channels=%d format=%d\n", argv[1], rate, channels, format);
   if (rate != requested_rate || channels != 2 || format != AFMT_S16_NE)
   { fprintf(stderr, "Requested PCM format was not accepted\n"); close(fd); return 1; }
   if (argc > 3)
   {
      input = fopen(argv[3], "rb");
      if (!input) { perror("open PCM file"); close(fd); return 1; }
   }
   while (input || frame < rate * 3L)
   {
      int frames = rate * 3L - frame < 1024 ? (int)(rate * 3L - frame) : 1024;
      int i;
      size_t offset = 0, bytes = frames * 2 * sizeof(int16_t);
      if (input)
      {
         bytes = fread(pcm, 1, sizeof(pcm), input);
         if (ferror(input) || bytes % (2 * sizeof(int16_t)))
         { fprintf(stderr, "Invalid or unreadable stereo PCM file\n"); fclose(input); close(fd); return 1; }
         if (!bytes) break;
      }
      else
      {
         for (i = 0; i < frames; ++i, ++frame)
            pcm[2*i] = pcm[2*i+1] = (int16_t)(4096 * sin(6.283185307179586 * 440 * frame / rate));
      }
      while (offset < bytes)
      {
         ssize_t n = write(fd, (const char *)pcm + offset, bytes - offset);
         if (n < 0 && errno == EINTR) continue;
         if (n <= 0) { perror("write PCM"); if (input) fclose(input); close(fd); return 1; }
         offset += n;
      }
   }
   if (input) fclose(input);
   if (ioctl(fd, SNDCTL_DSP_SYNC, NULL) == -1)
   { perror("drain PCM"); close(fd); return 1; }
   return close(fd) == -1 ? 1 : 0;
}
