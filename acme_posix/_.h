#pragma once


#include "acme/_.h"


#if defined(_ACME_POSIX_LIBRARY)
   #define CLASS_DECL_ACME_POSIX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_ACME_POSIX  CLASS_DECL_IMPORT
#endif


namespace acme
{


   namespace posix
   {


      class node;


   } // namespace posix


} // namespace node_gnome


