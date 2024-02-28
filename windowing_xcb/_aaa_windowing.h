// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once



//!!!#include <X11/Xlib.h>


//xcb_connection_t * xcb_get_display();


//Visual * get_32bit_visual(xcb_connection_t * pdisplay);


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

#include "display.h"
#include "window.h"

