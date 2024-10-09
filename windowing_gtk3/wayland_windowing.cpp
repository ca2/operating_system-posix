#include "framework.h"
#include "windowing_gtk3.h"
#include <fcntl.h> // library for fcntl function
#include <sys/stat.h>


//http://rosettacode.org/wiki/Window_creation/X11

#include <stdio.h>

#include <string.h>


//bool __x11_hook_process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);


#define SIMPLE_UI_MAX_BUTTON_COUNT 8


//bool __x11_hook_list_is_empty();


extern ::particle * user_synchronization();


//Display * g_pdisplayX11= nullptr;


//int g_fdX11[2] = {};


//Display * x11_get_display()
//{
//
//   if(g_pdisplayX11 == NULL)
//   {
//
//      g_pdisplayX11 =  XOpenxDisplay(NULL);
//
//   }
//
//   return g_pdisplayX11;
//
//}
//
//
//
//
//
//GC x11_create_gc(Colormap colormap, Display* pdisplay, Window window, ::u8 a, ::u8 r, ::u8 g, ::u8 b)
//{
//
//   GC gc = XCreateGC(pdisplay, window, 0, 0);
//
//   x11color32_t x11color32 = argb(a, r, g, b);
//
//   XSetForeground (pdisplay, gc, x11color32);
//
//   return gc;
//
//}
//
//
////int x11_message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox)
////{
////
////   //deferx_initializex_x11();
////
////   auto pdisplay = __new simple_ui_display(str, strTitle, emessagebox);
////
////   return pdisplay->show();
////
////}
//


CLASS_DECL_ACME string message_box_result_to_string(int iResult);

//CLASS_DECL_ACME void x11_message_box(const string & strMessage, const string & strTitle, const ::e_message_box & emessagebox, const ::promise::process & process);

//::e_status message_box_synchronous(oswindow oswindow, const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, ::future future)
//{
//
//   x11_message_box(pszMessage, pszTitle, emessagebox, future);
//
//   return ::success;
//
//}



void x11_kick_idle()
{

   //if(g_bX11Idle)
   //{

//      return;

   //}

   //g_bX11Idle = true;

   //char ch = 1;

   //::write(g_fdX11[1], &ch, 1);

}




//::pointer< ::mutex > g_pmutexX11 = nullptr;
//
//
//bool g_bAcmeInitWindowing = false;

//
//void acme_defer_os_init_windowing()
//{
//
//   if(g_bAcmeInitWindowing)
//   {
//
//      return;
//
//   }
//
//   g_bAcmeInitWindowing = true;
//
//   pipe(g_fdX11);
//
//   int retval = fcntl(g_fdX11[0], F_SETFL, fcntl(g_fdX11[0], F_GETFL) | O_NONBLOCK);
//
//   g_pmutexX11 = new ::pointer < ::mutex >();
//
//}


//void x11_defer_handle_just_hooks()
//{
//
//   if(get_platform_level() <= e_platform_level_apex)
//   {
//
//      x11_handle_just_hooks();
//
//   }
//
//}
//
//
//void x11_handle_just_hooks()
//{
//
//   Display * pdisplay = x11_get_display();
//
//   XEvent e = {};
//
//#if !defined(RASPBERRYPIOS)
//
//   XGenericEventCookie * cookie;
//
//#endif
//
//   while(true)
//   {
//
//      try
//      {
//
//         synchronous_lock sl(user_synchronization());
//
//         XLockDisplay(pdisplay);
//
//         try
//         {
//
//            while(XPending(pdisplay))
//            {
//
//               XNextEvent(pdisplay, &e);
//
//               __x11_hook_process_event(pdisplay, &e, nullptr);
//
//               if(__x11_hook_list_is_empty())
//               {
//
//                  break;
//
//               }
//
//            }
//
//         }
//         catch(...)
//         {
//
//         }
//
//         __x11_hook_on_idle(pdisplay);
//
//         XUnlockDisplay(pdisplay);
//
//      }
//      catch(...)
//      {
//
//      }
//
////      x11_wait_timer_or_event(pdisplay);
//
//      if(__x11_hook_list_is_empty())
//      {
//
//         break;
//
//      }
//
//   }
//
//}
//
//
//::e_status initialize_x11();
//
//bool g_bInitializeX11 = false;
//
//::e_status g_estatusInitializeX11 = ::error_not_initialized;
//
//::e_status deferx_initializex_x11()
//{
//
//   if(!g_bInitializeX11)
//   {
//
//      g_bInitializeX11 = true;
//
//      g_estatusInitializeX11 = initialize_x11();
//
//   }
//
//   return g_estatusInitializeX11;
//
//}
//
//
//i32 _cx_XErrorHandler(Display * display, XErrorEvent * perrorevent);
//
//
//::e_status initialize_x11()
//{
//
//   if(!XInitxThreads())
//   {
//
//      return ::error_failed;
//
//   }
//
//   XSetErrorHandler(_cx_XErrorHandler);
//
//   g_pmutexX11 = new ::pointer < ::mutex >();
//
//   return ::success;
//
//}
//


