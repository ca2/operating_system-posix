#pragma once


#define MIDIMSG(status,channel,data1,data2) ( (::u32)((status<<4) | channel | (data1<<8) | (data2<<16)) )


namespace music
{


   namespace midi
   {


      namespace alsa
      {

      //::e_status ::music::translate(::e_status smfrc);


      }

   } // namespace midi_alsa


} // namespace music
