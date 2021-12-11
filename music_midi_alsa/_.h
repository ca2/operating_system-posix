#pragma once


#include "app-veriwell/multimedia/multimedia/_.h"



#if defined(_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA_LIBRARY)
   #define CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_VERIWELL_MULTIMEDIA_MUSIC_MIDI_ALSA  CLASS_DECL_IMPORT
#endif


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         class midi;


      } // namespace alsa


   } // namespace midi


} // namespace music


