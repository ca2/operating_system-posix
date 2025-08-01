/*
 * Copyright (C) 2011 Donovan "Tsomi" Watteau <tsoomi@gmail.com>
 *
 * Based on Thomas Pfaff's work for XMMS, and some suggestions from
 * Alexandre Ratchov.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "framework.h"
#include "sunaudio.h"


#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>


//#include "timo_output_plugin.h"
#include "timo_mixer.h"
//#include "timo_sample_format.h"
//#include "../xmalloc.h"

// static sample_format_t m_sampleformat;
// static struct sio_par m_par;
// static struct sio_hdl *m_hdl;
// int cmus_sndio::m_iSndioVolume = SIO_MAXVOL;
// int cmus_sndio::m_bSndioPaused;
int get_global_audio_fd();
void set_global_audio_fd(int iAudioFd);
audio_info_t * get_global_initial_audio_info();

namespace multimedia
{


   namespace audio_sunaudio
   {

   
   sun_object::sun_object()
   {
	 m_fd = -1;
	 m_ctlfd = -1;
	m_strDevice = "/dev/audio";
//      signal(SIGINT, cleanup);
	//signal(SIGTERM, cleanup);
	//signal(SIGHUP, cleanup);


   }
      
sun_object::~sun_object()
{
   
}
   

/* Sun Output.
+ *
+ * Based on Oss Output by Reece H. Dunn
 *
 * This file is part of pcaudiolib.
 *
 * pcaudiolib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * pcaudiolib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pcaudiolib.  If not, see <http://www.gnu.org/licenses/>.
 */

//#define to_sun_object(object) container_of(object, struct sun_object, vtable)
//




int
sun_object::sunaudio_open(
int precision,
                uint32_t rate,
                uint8_t channels)
{
	//struct sun_object *self = to_sun_object(object);
		
	if (m_fd != -1)
		return EEXIST;

	struct aformat_sun
	{
      bool bSigned;
		int audio_object_format;
		int sun_format;
		int sun_precision;
	};
	struct aformat_sun aformat_sun_tbl[] = {
{0, 0 /*AUDIO_OBJECT_FORMAT_ALAW*/, AUDIO_ENCODING_ALAW, 8},
{0, 0 /*AUDIO_OBJECT_FORMAT_ULAW*/, AUDIO_ENCODING_ULAW, 8},
{1, 0 /*AUDIO_OBJECT_FORMAT_S8*/, AUDIO_ENCODING_SLINEAR, 8},
{0, 0 /*AUDIO_OBJECT_FORMAT_U8*/, AUDIO_ENCODING_ULINEAR, 8},
{1, 0 /*AUDIO_OBJECT_FORMAT_S16LE*/, AUDIO_ENCODING_SLINEAR_LE, 16},
{0, 0 /*AUDIO_OBJECT_FORMAT_S16BE*/, AUDIO_ENCODING_SLINEAR_BE, 16},
{0, 0 /*AUDIO_OBJECT_FORMAT_U16LE*/, AUDIO_ENCODING_ULINEAR_LE, 16},
{0, 0 /*AUDIO_OBJECT_FORMAT_U16BE*/, AUDIO_ENCODING_ULINEAR_BE, 16},
{0, 0 /*AUDIO_OBJECT_FORMAT_S18LE*/, AUDIO_ENCODING_SLINEAR_LE, 18},
{0, 0 /*AUDIO_OBJECT_FORMAT_S18BE*/, AUDIO_ENCODING_SLINEAR_BE, 18},
{0, 0 /*AUDIO_OBJECT_FORMAT_U18LE*/, AUDIO_ENCODING_ULINEAR_LE, 18},
{0, 0 /*AUDIO_OBJECT_FORMAT_U18BE*/, AUDIO_ENCODING_ULINEAR_BE, 18},
{0, 0 /*AUDIO_OBJECT_FORMAT_S20LE*/, AUDIO_ENCODING_SLINEAR_LE, 20},
{0, 0 /*AUDIO_OBJECT_FORMAT_S20BE*/, AUDIO_ENCODING_SLINEAR_BE, 20},
{0, 0 /*AUDIO_OBJECT_FORMAT_U20LE*/, AUDIO_ENCODING_ULINEAR_LE, 20},
{0, 0 /*AUDIO_OBJECT_FORMAT_U20BE*/, AUDIO_ENCODING_ULINEAR_BE, 20},
{1, 0 /*AUDIO_OBJECT_FORMAT_S24LE*/, AUDIO_ENCODING_SLINEAR_LE, 24},
{0, 0 /*AUDIO_OBJECT_FORMAT_S24BE*/, AUDIO_ENCODING_SLINEAR_BE, 24},
{0, 0 /*AUDIO_OBJECT_FORMAT_U24LE*/, AUDIO_ENCODING_ULINEAR_LE, 24},
{0, 0 /*AUDIO_OBJECT_FORMAT_U24BE*/, AUDIO_ENCODING_ULINEAR_BE, 24},
{0, 0 /*AUDIO_OBJECT_FORMAT_S24_32LE*/, AUDIO_ENCODING_SLINEAR_LE, 32},
{0, 0 /*AUDIO_OBJECT_FORMAT_S24_32BE*/, AUDIO_ENCODING_SLINEAR_BE, 32},
{0, 0 /*AUDIO_OBJECT_FORMAT_U24_32LE*/, AUDIO_ENCODING_ULINEAR_LE, 32},
{0, 0 /*AUDIO_OBJECT_FORMAT_U24_32BE*/, AUDIO_ENCODING_ULINEAR_BE, 32},
{1, 0 /*AUDIO_OBJECT_FORMAT_S32LE*/, AUDIO_ENCODING_SLINEAR_LE, 32},
{0, 0 /*AUDIO_OBJECT_FORMAT_S32BE*/, AUDIO_ENCODING_SLINEAR_BE, 32},
{0, 0 /*AUDIO_OBJECT_FORMAT_U32LE*/, AUDIO_ENCODING_ULINEAR_LE, 32},
{0, 0 /*AUDIO_OBJECT_FORMAT_U32BE*/, AUDIO_ENCODING_ULINEAR_BE, 32},
{0, 0 /*AUDIO_OBJECT_FORMAT_ADPCM*/, AUDIO_ENCODING_ADPCM, 8},
{0, 0 /*AUDIO_OBJECT_FORMAT_AC3*/, AUDIO_ENCODING_AC3, 32},

	};
#define SUNFORMATS (sizeof(aformat_sun_tbl)/sizeof(aformat_sun_tbl[0]))
	int i;
	for(i=0; i < SUNFORMATS; i++)
   {
		//if(aformat_sun_tbl[i].audio_object_format == format
      if(aformat_sun_tbl[i].bSigned
      && aformat_sun_tbl[i].sun_precision == precision)
			break;
   }
	if(i >= SUNFORMATS)
		return EINVAL;

	int data;
	
   if ((m_fd = open(m_strDevice, O_WRONLY, 0)) == -1)
   {
      
      information() << "sunaudio_open Failed to open device: " << m_strDevice;
      
		return errno;
      
   }
   
   audio_info_t audioinfoOld;
   
   audio_info_t audioinfoInit;
   
   audio_info_t audioinfoGetBufInfo;
   
   audio_info_t * paudioinfoOld = nullptr;
   
   AUDIO_INITINFO(&audioinfoInit);  
   
   if(get_global_audio_fd() < 0)
   {
      
      informationf("global_audio_fd was (%d)", get_global_audio_fd());
      
      set_global_audio_fd(m_fd);
      
      informationf("global_audio_fd now is (%d)", get_global_audio_fd());
      
      AUDIO_INITINFO(get_global_initial_audio_info());   
      
      if (ioctl(get_global_audio_fd(), AUDIO_GETINFO, get_global_initial_audio_info()) == -1)
      {
         
         information() << "sunaudio_open Failed to get_info: " << m_strDevice;
         
         goto error;
         
      }
      
      paudioinfoOld = get_global_initial_audio_info();
      
      information() << "INITIAL GETINFO sample_rate: " << paudioinfoOld->play.sample_rate;
      information() << "INITIAL GETINFO channels: " << paudioinfoOld->play.channels;
      information() << "INITIAL GETINFO precision: " << paudioinfoOld->play.precision;
      information() << "INITIAL GETINFO encoding: " << paudioinfoOld->play.encoding;
      information() << "INITIAL GETINFO pause: " << (int) paudioinfoOld->play.pause;
      information() << "INITIAL GETINFO port: " << paudioinfoOld->play.port;
      information() << "INITIAL GETINFO blocksize: " << paudioinfoOld->blocksize;
      information() << "INITIAL GETINFO mode: " << paudioinfoOld->mode;
      
   }
   else
   {
      
      AUDIO_INITINFO(&audioinfoOld);  
      
      if (ioctl(m_fd, AUDIO_GETINFO, &audioinfoOld) == -1)
      {
         
         information() << "sunaudio_open Failed to get_info: " << m_strDevice;
         
         goto error;
         
      }
      
      paudioinfoOld = &audioinfoOld;
      
      information() << "OLD GETINFO sample_rate: " << paudioinfoOld->play.sample_rate;
      information() << "OLD GETINFO channels: " << paudioinfoOld->play.channels;
      information() << "OLD GETINFO precision: " << paudioinfoOld->play.precision;
      information() << "OLD GETINFO encoding: " << paudioinfoOld->play.encoding;
      information() << "OLD GETINFO pause: " << (int) paudioinfoOld->play.pause;
      information() << "OLD GETINFO port: " << paudioinfoOld->play.port;
      information() << "OLD GETINFO blocksize: " << paudioinfoOld->blocksize;
      information() << "OLD GETINFO mode: " << paudioinfoOld->mode;
      
   }
   
   AUDIO_INITINFO(&audioinfoGetBufInfo);  
   
   if (ioctl(m_fd, AUDIO_GETBUFINFO, &audioinfoGetBufInfo) == -1)
   {
      
      information() << "sunaudio_open Failed to get_buf_info: " << m_strDevice;
      
      goto error;
      
   }
      
   memcpy(&m_audioinfo, &audioinfoInit, sizeof(audio_info_t));

	m_audioinfo.play.sample_rate = rate;
	m_audioinfo.play.channels = channels;
	m_audioinfo.play.precision = aformat_sun_tbl[i].sun_precision;
	m_audioinfo.play.encoding = aformat_sun_tbl[i].sun_format;	
   m_audioinfo.play.pause = 1;
   //m_audioinfo.play.port = audioinfoInit.play.port;
   //m_audioinfo.blocksize = audioinfoInit.blocksize;
   m_audioinfo.mode = AUMODE_PLAY;
   
   information() << "GETBUFINFO avail_ports: " << audioinfoGetBufInfo.play.avail_ports;
   
   if(audioinfoGetBufInfo.play.avail_ports != 0)
   {
      
      m_audioinfo.play.port = audioinfoGetBufInfo.play.avail_ports &
      (AUDIO_SPEAKER | AUDIO_HEADPHONE);
      
   }
   
   information() << "going to SETINFO with sample_rate: " << m_audioinfo.play.sample_rate;
   information() << "going to SETINFO with channels: " << m_audioinfo.play.channels;
   information() << "going to SETINFO with precision: " << m_audioinfo.play.precision;
   information() << "going to SETINFO with encoding: " << m_audioinfo.play.encoding;
   information() << "going to SETINFO with pause: " << (int) m_audioinfo.play.pause;
   information() << "going to SETINFO with port: " << m_audioinfo.play.port;
   information() << "going to SETINFO with blocksize: " << m_audioinfo.blocksize;
   information() << "going to SETINFO with mode: " << m_audioinfo.mode;
   
	if (ioctl(m_fd, AUDIO_SETINFO, &m_audioinfo) == -1)
   {
      
      information() << "FAILED to SETINFO (A)";
		
      goto error;
      
   }
   
	AUDIO_INITINFO(&m_audioinfo);
   
	if (ioctl(m_fd, AUDIO_GETINFO, &m_audioinfo) == -1)
   {
      
      information() << "FAILED to GETINFO (B)";

		goto error;
      
   }
   
   m_audioinfo.blocksize = m_audioinfo.play.buffer_size / m_iBufferCountHint;
   
   information() << "going to SETINFO with blocksize: " << m_audioinfo.blocksize;
   
	if (ioctl(m_fd, AUDIO_SETINFO, &m_audioinfo) == -1)
   {
      
      information() << "FAILED to SETINFO (C)";
      
      goto error;
      
   }
	AUDIO_INITINFO(&m_audioinfo);
	if (ioctl(m_fd, AUDIO_GETINFO, &m_audioinfo) == -1)
   {
      
      information() << "FAILED to GETINFO (D)";

		goto error;
      
   }

   informationf("Succesfully opened sunaudio:");
   informationf("sample_rate: %d", rate);
   informationf("channels: %d", channels);
   informationf("precision: %d", m_audioinfo.play.precision);
   informationf("encoding: %d", m_audioinfo.play.encoding);
   m_iBufferCount = minimum(m_audioinfo.play.buffer_size / m_audioinfo.blocksize, m_iBufferCount);
   informationf("buffer count: %d", m_iBufferCount);
   informationf("total buffer size: %d", m_audioinfo.play.buffer_size);
   informationf("port: %d", m_audioinfo.play.port);
   informationf("block size: %d", m_audioinfo.blocksize);
   m_iFrameByteCount = m_audioinfo.blocksize / (channels * precision/8);
	m_llWrittenBytes = 0;
   return 0;
   
error:
	data = errno;
   information() << "errno=" << (int) data;
	close(m_fd);
	m_fd = -1;
	return data;
}

int
sun_object::sunaudio_close()
{
	////struct sun_object *self = to_sun_object(object);

	if (m_fd == -1) {
      sunaudio_flush();
      
    	if(ioctl(m_fd, AUDIO_SETINFO, get_global_initial_audio_info())==-1)
      {
         //goto error;
      }
		close(m_fd);
      set_global_audio_fd(-1);
		m_fd = -1;
	}
   return 0;
}

void
sun_object::sunaudio_destroy()
{
	//struct sun_object *self = to_sun_object(object);

	//free(m_device);
	//free(self);
}

int
sun_object::sunaudio_drain()
{
	//struct sun_object *self = to_sun_object(object);

	if (ioctl(m_fd, AUDIO_DRAIN, NULL) == -1)
		return errno;
	return 0;
}

int
sun_object::sunaudio_flush()
{
	//struct sun_object *self = to_sun_object(object);

	if (ioctl(m_fd, AUDIO_FLUSH, NULL) == -1)
		return errno;
	return 0;
}


   memsize sun_object::sunaudio_write(const void * data, memsize bytes)
   {
      
      //informationf("sunaudio writing %lld bytes", bytes);
      
      auto ssize = write(m_fd, data, bytes);
      
      if(ssize < 0)
      {
      
         int iError = -errno;
         
         informationf("SUNAUDIO WRITE FAILED with %d", iError);
         
         return iError;
         
      }
      
      m_llWrittenBytes += ssize;
      
      double dSeconds = m_llWrittenBytes * 8.0 /
       (double) (m_audioinfo.play.channels *
       m_audioinfo.play.sample_rate *
       m_audioinfo.play.precision);
       
      long long lNewSecond = (long long) dSeconds;
      
      if(lNewSecond != m_iLastSecond)
      {

         informationf("sunaudio write... (%0ds)", lNewSecond);
         
         m_iLastSecond = lNewSecond;
         
      }
      
      //informationf("sunaudio has WRITTEN %lld bytes");
      //informationf("sunaudio has WRITTEN a total of %lld bytes (%0.1fs)", m_llWrittenBytes, dSeconds);
      
      
//      u_long ul = 0;
	//if (ioctl(m_fd, AUDIO_WSEEK, &ul) == -1)
   //{
     // 		int iError -errno;
      //informationf("SUNAUDIO AUDIO_WSEEK FAILED with %d", iError);
        //    return iError;
         //}
         
      return ssize;
      
   }

   
   long sun_object::sunaudio_avail()
   {

      u_long ul = 0;
	AUDIO_INITINFO(&m_audioinfo);
   
      if (ioctl(m_fd, AUDIO_GETINFO, &m_audioinfo) == -1)
      {
     
         int iError = -errno;
         
         informationf("SUNAUDIO AUDIO_GETINFO FAILED with %d", iError);
         
         return iError;
         
      }
      
      informationf("SUNAUDIO AVAIL %d", m_audioinfo.play.samples);
      
      return m_audioinfo.play.samples;
      
   }

const_char_pointer  
sun_object::sunaudio_strerror(
                    int error)
{
	return strerror(error);
}

//struct audio_object *
//create_sun_object(const_char_pointer device,
                  //const_char_pointer application_name,
                  //const_char_pointer description)
//{
	//struct sun_object *self = malloc(sizeof(struct sun_object));
	//if (!self)
		//return NULL;

	//m_fd = -1;
	//m_device = device ? strdup(device) : NULL;

	//m_vtable.open = sun_object_open;
	//m_vtable.close = sun_object_close;
	//m_vtable.destroy = sun_object_destroy;
	//m_vtable.write = sun_object_write;
	//m_vtable.drain = sun_object_drain;
	//m_vtable.flush = sun_object_flush;
	//m_vtable.strerror = sun_object_strerror;

	//return &m_vtable;
//}
int sun_object::sunaudio_pause()
{
   audio_info_t audioinfo;
   AUDIO_INITINFO(&audioinfo);
	if (ioctl(m_fd, AUDIO_GETINFO, &audioinfo) == -1)
		return errno;
   audioinfo.play.pause = 1;
	if (ioctl(m_fd, AUDIO_SETINFO, &audioinfo) == -1)
		return errno;
      

   information() << "multimedia::audio_sunaudio::sun_object::sunaudio_pause PAUSING!!";
   
   return 0;
   
}
int sun_object::sunaudio_unpause()
{
   
      audio_info_t audioinfo;
   AUDIO_INITINFO(&audioinfo);
	if (ioctl(m_fd, AUDIO_GETINFO, &audioinfo) == -1)
		return errno;
   audioinfo.play.pause = 0;
	if (ioctl(m_fd, AUDIO_SETINFO, &audioinfo) == -1)
		return errno;
      

   
   information() << "multimedia::audio_sunaudio::sun_object::sunaudio_unpause RESUMING!!";
   
   return 0;
}


   } // namespace audio_sunaudio


} // namespace multimedia


