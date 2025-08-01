#pragma once


#include "acme/_.h"


#if defined(_acme_posix_project)
   #define CLASS_DECL_ACME_POSIX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_ACME_POSIX  CLASS_DECL_IMPORT
#endif


namespace acme_posix
{


   class node;


    class file_system;

class directory_system;


} // namespace acme_posix



#ifdef LINUX


#define USE_DBUS 1


#endif


#ifdef USE_DBUS


void dbus_do_power_off (const_char_pointer  action);


#endif



