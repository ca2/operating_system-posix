//
// Created by camilo on 09/04/2022.
// Modified 2023-10-05 23:50
//
#pragma once


#include "acme_posix/_.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>


#if defined(_windowing_system_gtk3_project)
#define CLASS_DECL_WINDOWING_SYSTEM_GTK3  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_WINDOWING_SYSTEM_GTK3  CLASS_DECL_IMPORT
#endif


#include "acme/prototype/geometry2d/rectangle.h"


inline void copy(::rectangle_i32 * prectTarget, const GdkRectangle * prectSource)
{

   prectTarget->left() = prectSource->x;
   prectTarget->top() = prectSource->y;
   prectTarget->right() = prectSource->x + prectSource->width;
   prectTarget->bottom() = prectSource->y + prectSource->height;

}




//void x11_check_status(int status, unsigned long window);



//#ifndef WITH_XI
//#define WITH_XI
//#endif

//#define pointer x11_pointer

// #include <wayland-client.h>
// #include <wayland-server.h>
// #include <wayland-cursor.h>
// #include <wayland-client-protocol.h>
// #include "wayland_static/wayland-gtk_shell1.h"
// #include "wayland_static/wayland-xdg_activation_v1.h"
// #include "wayland_static/wayland-xdg_wm_base.h"
//#include <X11/Xutil.h>
//#include <X11/extensions/Xrender.h>
//#include <X11/Xatom.h>

//#undef pointer



//Visual * get_32bit_visual(Display * pdisplay);


//void x11_kick_idle();


//void x11_wait_timer_or_event(Display * pdisplay);
//void __x11_hook_on_idle(Display * pdisplay);


//CLASS_DECL_ACME ::particle * user_synchronization();


//#include "x11_exception.h"
//#include "x11_keyboard.h"
//#include "x11_hook.h"
//#include "x11_button.h"
//#include "x11_simple_ui_display.h"
//#include "x11_message_box.h"


//::e_status deferx_initializex_x11();
//void x11_handle_just_hooks();
//void x11_defer_handle_just_hooks();
//int x11_message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox);
//bool __x11_hook_process_event(Display * pdisplay, XEvent * pevent, XGenericEventCookie * cookie);


//class x11color32_t
//{
//public:
//
//
//   unsigned int m_ui;
//
//
//   x11color32_t(){m_ui=0;}
//   x11color32_t(const ::color::color & color)
//   {
//
//      auto opacity = color.byte_opacity();
//
//      m_ui = make_u32(
//              color.byte_blue() * opacity / 255,
//              color.byte_green() * opacity / 255,
//              color.byte_red() * opacity / 255,
//              opacity);
//
//   }
//
//
//   operator unsigned long () const { return m_ui; }
//
//
//};

namespace windowing_system_gtk4
{


} // namespace windowing_system_gtk4

