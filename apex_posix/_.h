#pragma once


#include "apex/_.h"
#include "acme_posix/_.h"


#if defined(_apex_posix_project)
   #define CLASS_DECL_APEX_POSIX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APEX_POSIX  CLASS_DECL_IMPORT
#endif



