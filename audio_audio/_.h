#pragma once


#include "audio/audio/_.h"


#if defined(_audio_sndio_project)
   #define CLASS_DECL_AUDIO_SNDIO CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AUDIO_SNDIO CLASS_DECL_IMPORT
#endif




