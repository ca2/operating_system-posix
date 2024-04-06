#pragma once


#include "audio/audio/_.h"


// apt install libasound2-dev
// dnf install alsa-lib-devel
// zypper install alsa-devel
#include <alsa/asoundlib.h>


#if defined(_audio_alsa_project)
   #define CLASS_DECL_AUDIO_ALSA  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_AUDIO_ALSA  CLASS_DECL_IMPORT
#endif

