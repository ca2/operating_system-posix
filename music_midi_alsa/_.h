#pragma once


#include "app-veriwell/multimedia/_.h"


#include "seqlib.h"


#if defined(_veriwell_multimedia_music_midi_alsa_project)
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


