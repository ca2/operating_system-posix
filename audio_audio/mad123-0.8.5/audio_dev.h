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

#include <mad.h>

/*
 * Audio Device return codes
 */
#define	AD_NO_ERROR	0
#define AD_ERROR	(-1)
#define AD_WOULD_BLOCK	(-2)

/*
 * When the audio slave process is idle, it will send 'heartbeat'
 * messages to the controlling process every AD_HEARTBEAT milliseconds.
 */
#define	AD_HEARTBEAT	20

/*
 * Audio Device Commands
 */
#define ADC_PAUSE	1

extern void	*audio_dev_init(const_char_pointer );
extern void	audio_dev_close(void *);
extern void	audio_dev_register_read_callback(void *,void (*)(void *),void*);
extern int	audio_dev_send_command(void *, int, int *, int);
extern int	audio_dev_write(void *, struct mad_header const *,
		    struct mad_pcm *, int *);
extern int	audio_dev_flush_wait(void *);
extern int	audio_dev_purge_wait(void *);
extern int	audio_dev_buffer_time(void *);
extern int	audio_dev_played_time(void *);

/*
 * Interface for back-end audio devices
 */
struct audio_dev_backend {
	const char	*ad_name;
	void *		(*ad_init)(const_char_pointer );
	void		(*ad_close)(void *);
	int		(*ad_config)(void *, int, int);
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
