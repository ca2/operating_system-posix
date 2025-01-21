#pragma once


#include "audio/audio/_.h"


#if defined(_audio_sndio_project)
   #define CLASS_DECL_AUDIO_SNDIO CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AUDIO_SNDIO CLASS_DECL_IMPORT
#endif


enum {
	/* no error */
	OP_ERROR_SUCCESS,
	/* system error (error code in errno) */
	OP_ERROR_ERRNO,
	/* no such plugin */
	OP_ERROR_NO_PLUGIN,
	/* plugin not initialized */
	OP_ERROR_NOT_INITIALIZED,
	/* function not supported */
	OP_ERROR_NOT_SUPPORTED,
	/* mixer not open */
	OP_ERROR_NOT_OPEN,
	/* plugin does not support the sample format */
	OP_ERROR_SAMPLE_FORMAT,
	/* plugin does not have this option */
	OP_ERROR_NOT_OPTION,
	/*  */
	OP_ERROR_INTERNAL
};



