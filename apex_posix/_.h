#pragma once


#include "acme_posix/_.h"
#include "apex/_.h"


#if defined(_apex_posix_project)
   #define CLASS_DECL_APEX_POSIX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APEX_POSIX  CLASS_DECL_IMPORT
#endif



