#pragma once


#include "snd_pcm.h"
#include "audio/audio/wave/out.h"
//s#include "cmus_sndio.h"

#define PCM_MAX_BUFFSIZE	2 * 8_KiB

namespace multimedia
{


   namespace audio_audio
   {

/*	$Id: audio_dev.h,v 1.10 2004/06/07 21:10:42 steve Exp $	*/

/*
 Command Line Front-end for Robert Leslie's `libmad' mp3 decoder.
 Copyright (C) 2001-2003 Steve Woodford.

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef __AUDIO_DEV_H
#define __AUDIO_DEV_H

//#include <mad.h>

/*
 * Audio Device return codes
 */
#define	AD_NO_ERROR	0
#define AD_ERROR	(-1)
#define AD_WOULD_BLOCK	(-2)
#define AD_UNDER_RUN    (-3)


/*
 * When the audio slave process is idle, it will send 'heartbeat'
 * messages to the controlling process every AD_HEARTBEAT milliseconds.
 */
#define	AD_HEARTBEAT	20

/*
 * Audio Device Commands
 */
#define ADC_PAUSE	1


/*
 * Interface for back-end audio devices
 */
struct audio_dev_backend {
	const char	*ad_name;
	void *		(*ad_init)(const char *);
	void		(*ad_close)(void *);
	int		(*ad_config)(void *, int, int, int lowat, int hiwat);
	ssize_t		(*ad_output)(void *, void *, size_t);
	int		(*ad_pollfd)(void *);
};

extern const struct audio_dev_backend audio_dev_sun;
extern const struct audio_dev_backend audio_dev_pcm;
#ifndef NOARTS
extern const struct audio_dev_backend audio_dev_arts;
#endif

#ifndef INFTIM
#define INFTIM (-1)
#endif

#endif /* __AUDIO_DEV_H */

   struct pcm_buffer
   {
      int		         m_iBufferChannelCount;
      int		         m_iBufferSampleRate;
      size_t	         m_iLength;
      size_t		      m_iBufferPosition;
      unsigned char	   m_pBufferData[PCM_MAX_BUFFSIZE];
   };

   #define	PCM_NBUFFS	100
   #define PCM_LOW_WATER   32
   struct pcm_data 
   {
      uint64_t	         pb_playsamples;
      int		         m_iDataChannelCount;
      int		         m_iDataSampleRate;
      int	            m_iPurge;
      int	            m_iHead;
      int	            m_iTail;
      pcm_buffer	      m_buffera[PCM_NBUFFS];
   };


struct audio_dev_ctx {
	::i64		ac_slave_pid = 0;
	const struct audio_dev_backend *ac_device;
	void		*ac_devarg = nullptr;
	int		ac_paused = true;
	manual_reset_event 		m_eventRead;
	manual_reset_event 		m_eventWrite;
//	int		ac_peerread;
//	int		ac_peerwrite;
::u64	ac_buffersamples;
int m_iLowWaterMark;
int m_iHighWaterMark;
//	void		(*ac_readcallback)(void *);
	void		*ac_cbarg = nullptr;
bool m_bStop;
	struct pcm_data *m_pdata = nullptr;

};


      class  CLASS_DECL_AUDIO_SNDIO wave_out :
virtual public audio_dev_ctx,
         virtual public ::wave::out
      {
      public:


         bool                    m_bWrite;
         int                     m_iBuffer;
         bool                    m_bStarted;
         ::u64                   m_uStart;
         //snd_pcm_status_t *      m_pstatus;
         //timeval                 m_timevalStart;
         class ::time            m_timeStart;
         //::i32_array             m_iaSent;
//         void *                  m_pAudioDevCtx;

	int 				m_iFrameCount;
	int				m_iBufferCount;



bool m_bPause;
bool m_bQuit;
int m_fd;

//int m_samplerate;
//int m_channelcount;

         //snd_async_handler_t *   m_pcm_callback;

         wave_out();
         ~wave_out() override;


         void install_message_routing(::channel * pchannel) override;

         class ::time out_get_position() override;
         //imedia_position out_get_position();

         //virtual ::e_status wave_out_open(::thread * pthreadCallback, ::collection::count iBufferCount, ::collection::count iBufferSampleCount) override;
         void out_open_ex(::thread * pthreadCallback, ::u32 uiSamplesPerSec, ::u32 uiChannelCount, ::u32 uiBitsPerSample, ::wave::enum_purpose epurpose) override;
         void out_stop() override;
         void out_close() override;
         void out_pause() override;
         void out_restart() override;


         virtual int _frames_to_bytes(int iFrameCount);


         //snd_pcm_t * out_get_safe_PCM();

         //virtual void alsa_write_thread();

         void out_on_playback_end() override;
         void out_filled(::collection::index iBuffer) override;
         virtual bool alsa_should_play();

         void init_task() override;
         void term_task() override;

         void out_start(const class time & time) override;

         //virtual int defer_underrun_recovery(int err);

         class ::time out_get_time_for_synch();

         ::e_status	audio_dev_init(const char *);
         void	audio_dev_close();

         int audio_dev_write(void *pcmdata, int samplecount);

         void audio_dev_pause();
         void audio_dev_unpause();

         int audio_dev_output(pcm_buffer * pbuffer);
         int audio_dev_flush_wait();
         int audio_dev_purge_wait();

         void audio_dev_slave(const char *dev);

         ::i64 audio_dev_buffer_time();

         ::i64 audio_dev_played_time();
         
         
      };


   } // namespace audio_audio


} // namespace multimedia



