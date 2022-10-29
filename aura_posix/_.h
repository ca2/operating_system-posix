#pragma once


#include "aura/_.h"
#include "apex_posix/_.h"


#if defined(_AURA_POSIX_LIBRARY)
   #define CLASS_DECL_AURA_POSIX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AURA_POSIX  CLASS_DECL_IMPORT
#endif


namespace aura_posix
{


   class node;
   class appindicator;


} // namespace aura_posix


namespace xim
{


   class keyboard;


} // namespace xim


#if defined(LINUX)


#include "x11/_.h"


#endif



