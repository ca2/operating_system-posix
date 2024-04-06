//
// Created by camilo on 28/04/2021.
//
#pragma once


#include "aura_posix/_library.h"
#include "aura_posix/x11/xim_keyboard.h"

#include "acme/operating_system/xcb/nano/_nano.h"


void xcb_kick_idle();


void xcb_wait_timer_or_event(xcb_connection_t * pdisplay);
void __xcb_hook_on_idle(xcb_connection_t * pdisplay);


//CLASS_DECL_ACME ::particle * user_synchronization();


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



