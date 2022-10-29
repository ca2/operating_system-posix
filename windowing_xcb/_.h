#pragma once


#include "aura/_.h"
#include "aura/operating_system/freebsd/appindicator.h"
#include "acme/operating_system/ansi/_pthread.h"
#include "acme/operating_system/freebsd/_user.h"
#include "acme/operating_system/x11/_.h"
#include "aura_posix/_.h"
#include <xcb/xcb.h>


#define WITH_XI
#define WITH_SN


#if defined(_WINDOWING_XCB_LIBRARY)
   #define CLASS_DECL_WINDOWING_XCB  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_XCB  CLASS_DECL_IMPORT
#endif


namespace windowing_xcb
{


   class windowing;
   class display;
   class window;

   using XCB_WINDOW_T = long;

   using window_map = map < XCB_WINDOW_T , ::pointer<window >>


} // namespace windowing_xcb



extern ::particle * user_synchronization();


