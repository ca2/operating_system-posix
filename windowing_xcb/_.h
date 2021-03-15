#pragma once


#include "aura/_.h"
#include "aura/user/_user.h"
#include "aura/os/linux/appindicator.h"
#include "acme/os/ansios/_pthread.h"
#include "acme/os/linux/_user.h"
#include "platform/x_window.h"


#define WITH_XI
#define WITH_SN


#include <xcb/xcb.h>
#include <xcb/xcb_image.h>
#include <xcb/render.h>


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


   template < typename TYPE >
   using visual_id_map = map < xcb_visualid_t, TYPE >;

   using visual_pictformat_map = visual_id_map < xcb_render_pictformat_t >;

   using visual_depth_map = visual_id_map < uint32_t >;

   template < typename TYPE >
   using pictformat_map = map < xcb_render_pictformat_t, TYPE >;

   using pictformat_info_map = pictformat_map < const xcb_render_pictforminfo_t * >;


} // namespace node_gnome


#include "buffer.h"


#include "cursor.h"


#include "icon.h"


#include "window.h"


#include "windowing.h"


#include "display.h"


#include "display_lock.h"


#include "factory_exchange.h"



