#pragma once


#include "aura/_.h"
#include "aura/node/operating_system/freebsd/appindicator.h"
#include "acme/node/operating_system/ansi/_pthread.h"
#include "acme/node/operating_system/freebsd/_user.h"
#include "platform-posix/aura_posix/x_window_system.h"
#include "aura_posix/_.h"


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


} // namespace windowing_xcb



