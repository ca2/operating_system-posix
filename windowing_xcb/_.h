#pragma once


#include "aura/_.h"
#include "aura/node/operating_system/freebsd/appindicator.h"
#include "acme/node/operating_system/ansi/_pthread.h"
#include "acme/node/operating_system/freebsd/_user.h"
#include "archive/platform-posix/aura_posix/x_window_system.h"
#include "aura_posix/_.h"




#define WITH_XI
#define WITH_SN


//#include <QMetaType>
//#include <X11/Xlib-xcb.h>
//#include <xcb/xcb.h>
//#include <xcb/xcb_image.h>
//#include <xcb/render.h>


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


//#include "buffer.h"


//#include "cursor.h"


//#include "icon.h"


//#include "window.h"


//#include "windowing.h"


//#include "display.h"


//#include "display_lock.h"


//#include "factory_exchange.h"


//#include "node.h"



