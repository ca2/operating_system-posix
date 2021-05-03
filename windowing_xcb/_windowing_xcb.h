//
// Created by camilo on 28/04/2021.
//
#pragma once


#include "aura_posix/_aura_posix.h"
#include "aura_posix/xim_keyboard.h"

#include <xcb/xcb.h>
#include <xcb/xcb_image.h>
#include <xcb/render.h>
#include <X11/Xlib-xcb.h>


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


} // namespace windowing_xcb



void xcb_kick_idle();


void xcb_wait_timer_or_event(xcb_connection_t * pdisplay);
void __xcb_hook_on_idle(xcb_connection_t * pdisplay);


CLASS_DECL_ACME mutex * user_mutex();


//#include "xcb_exception.h"
//#include "xcb_keyboard.h"
//#include "xcb_hook.h"
//#include "xcb_button.h"
//#include "xcb_simple_ui_display.h"
//#include "xcb_message_box.h"


//::e_status defer_initialize_xcb();
void xcb_handle_just_hooks();
void xcb_defer_handle_just_hooks();
int xcb_message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox);
//bool __xcb_hook_process_event(xcb_connection_t * pdisplay, xcb_generic_event_t * pevent, XGenericEventCookie * cookie);
bool __xcb_hook_process_event(xcb_connection_t * pdisplay, xcb_generic_event_t * pevent);


#include "buffer.h"


#include "cursor.h"


#include "icon.h"


#include "window.h"


#include "windowing.h"


#include "display.h"


#include "node.h"



