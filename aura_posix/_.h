#pragma once


#include "aura/_.h"
#include "apex_posix/_.h"


#if defined(_AURA_POSIX_LIBRARY)
   #define CLASS_DECL_AURA_POSIX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AURA_POSIX  CLASS_DECL_IMPORT
#endif


namespace aura
{


   namespace posix
   {


      class node;


   } // namespace posix


} // namespace aura_posix



