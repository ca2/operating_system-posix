#pragma once


#include "app-core/audio/audio/_.h"



#if defined(_AUDIO_ALSA_LIBRARY)
   #define CLASS_DECL_AUDIO_ALSA  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_AUDIO_ALSA  CLASS_DECL_IMPORT
#endif

