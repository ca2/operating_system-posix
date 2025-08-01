//
// Created by camilo on 01/01/2021. 6:52 BRT <3Tbs, Mummi and bilbo!!
//
// From _.h by camilo on 2022-09-24 23:21 <3ThomasBorregaardSorensen!!
#pragma once




#ifndef WITH_XI
#define WITH_XI
#endif

#define pointer x11_pointer

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xrender.h>
#include <X11/Xatom.h>

#undef pointer



Visual * get_32bit_visual(Display * pdisplay);


void x11_kick_idle();


void x11_wait_timer_or_event(Display * pdisplay);
void __x11_hook_on_idle(Display * pdisplay);


//CLASS_DECL_ACME ::particle * user_synchronization();


//#include "x11_exception.h"
//#include "x11_keyboard.h"
//#include "x11_hook.h"
//#include "x11_button.h"
//#include "x11_simple_ui_display.h"
//#include "x11_message_box.h"


::e_status deferx_initializex_x11();
void x11_handle_just_hooks();
void x11_defer_handle_just_hooks();
int x11_message_box(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, const ::e_message_box & emessagebox);
bool __x11_hook_process_event(Display * pdisplay, XEvent * pevent, XGenericEventCookie * cookie);


class x11color32_t
{
public:

   
   unsigned int m_ui;


   x11color32_t(){m_ui=0;}
   x11color32_t(const ::color::color & color)
   {

      auto opacity = color.byte_opacity();

      m_ui = make_unsigned_int(
              color.byte_blue() * opacity / 255,
              color.byte_green() * opacity / 255,
              color.byte_red() * opacity / 255,
              opacity);

   }


   operator unsigned long () const { return m_ui; }


};




