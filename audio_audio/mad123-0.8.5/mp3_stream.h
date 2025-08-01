/*	$Id: mp3_stream.h,v 1.8 2003/07/03 07:33:28 steve Exp $	*/

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

#ifndef __MP3_STREAM_H
#define __MP3_STREAM_H

enum mp3_stream_id3tag {
	MP3_STREAM_TAG_ARTIST,
	MP3_STREAM_TAG_TITLE,
	MP3_STREAM_TAG_ALBUM,
	MP3_STREAM_TAG_GENRE,
	MP3_STREAM_TAG_COMMENT
};

#define MP3_STREAM_DBL_BUFF_SIZE	0x8000

extern void	*mp3_stream_open(const_char_pointer , int, int);
extern void	mp3_stream_close(void *);
extern ssize_t	mp3_stream_read(void *, void *, size_t, int);
extern long	mp3_stream_seek(void *, long, int);
extern int	mp3_stream_id3(void *, enum mp3_stream_id3tag, char **);
extern int	mp3_stream_read_ahead_size(void *);

#endif /* __MP3_STREAM_H */
