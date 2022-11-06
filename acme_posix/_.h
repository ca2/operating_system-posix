#pragma once


#include "acme/_.h"
//#include "acme/operating_system.h"


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



#ifdef LINUX


#define USE_DBUS 1


#endif


#ifdef USE_DBUS


void dbus_do_power_off (const char *action);


#endif



