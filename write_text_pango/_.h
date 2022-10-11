// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "aura/_.h"
//#include "acme/operating_system.h"
//#include "node_windows/process_data.h"


#ifdef _WRITE_TEXT_PANGO_STATIC
#define CLASS_DECL_WRITE_TEXT_PANGO
#elif defined(_WRITE_TEXT_PANGO_LIBRARY)
#define CLASS_DECL_WRITE_TEXT_PANGO  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WRITE_TEXT_PANGO  CLASS_DECL_IMPORT
#endif



