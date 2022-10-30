// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "aura_posix/_library.h"
////#include "aura/user/user/_component.h"
#include "acme/operating_system/x11/_.h"
#ifdef FREEBSD
#include "aura/operating_system/freebsd/appindicator.h"
#include "acme/operating_system/freebsd/_user.h"
#endif
#include "acme/operating_system/ansi/_pthread.h"


#define WITH_XI



#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrender.h>
#include <X11/Xatom.h>


Visual * get_32bit_visual(Display * pdisplay);


void x11_kick_idle();


void x11_wait_timer_or_event(Display * pdisplay);
void __x11_hook_on_idle(Display * pdisplay);


CLASS_DECL_ACME ::particle * user_synchronization();


//#include "x11_exception.h"
//#include "x11_keyboard.h"
//#include "x11_hook.h"
//#include "x11_button.h"
//#include "x11_simple_ui_display.h"
//#include "x11_message_box.h"


::e_status defer_initialize_x11();
void x11_handle_just_hooks();
void x11_defer_handle_just_hooks();
int x11_message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox);
bool __x11_hook_process_event(Display * pdisplay, XEvent * pevent, XGenericEventCookie * cookie);


#include "keyboard.h"


#include "window.h"


#include "display.h"


#include "buffer.h"


#include "cursor.h"


#include "icon.h"


#include "windowing.h"


#include "operating-system-posix/aura_posix/x11/display_lock.h"


#include "node.h"



