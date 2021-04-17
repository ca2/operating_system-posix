#include "framework.h"
#include "windowing_xcb.h"
#include <fcntl.h> // library for fcntl function
#include <sys/stat.h>


//http://rosettacode.org/wiki/Window_creation/X11

#include <stdio.h>

#include <string.h>


//bool __xcb_hook_process_event(xcb_connection_t * pdisplay, XEvent & e, XGenericEventCookie * cookie);
bool __xcb_hook_process_event(xcb_connection_t * pdisplay, xcb_generic_event_t * pevent);


#define SIMPLE_UI_MAX_BUTTON_COUNT 8


bool __xcb_hook_list_is_empty();


extern ::mutex * user_mutex();


xcb_connection_t * g_pdisplayX11= nullptr;


int g_fdX11[2] = {};


//xcb_connection_t * xcb_get_display()
//{
//
//   if(g_pdisplayX11 == NULL)
//   {
//
//      g_pdisplayX11 =  XOpenDisplay(NULL);
//
//   }
//
//   return g_pdisplayX11;
//
//}





//GC xcb_create_gc(Colormap colormap, xcb_connection_t* pdisplay, xcb_window_t window, byte a, byte r, byte g, byte b)
//{
//
//   GC gc = XCreateGC(pdisplay, window, 0, 0);
//
//   color32_t cr = argb(a, r * a / 255, g * a / 255, b * a / 255);
//
//   XSetForeground (pdisplay, gc, cr);
//
//   return gc;
//
//}


//int xcb_message_box(const string & str, const string & strTitle, const ::e_message_box & emessagebox)
//{
//
//   //defer_initialize_xcb();
//
//   auto pdisplay = __new(simple_ui_display(str, strTitle, emessagebox));
//
//   return pdisplay->show();
//
//}



CLASS_DECL_ACME string message_box_result_to_string(int iResult);

//CLASS_DECL_ACME void xcb_message_box(const string & strMessage, const string & strTitle, const ::e_message_box & emessagebox, const ::promise::process & process);

//::e_status os_message_box(oswindow oswindow, const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, ::future future)
//{
//
//   xcb_message_box(pszMessage, pszTitle, emessagebox, future);
//
//   return ::success;
//
//}


bool g_bX11Idle = false;


void xcb_kick_idle()
{

   //if(g_bX11Idle)
   //{

//      return;

   //}

   //g_bX11Idle = true;

   //char ch = 1;

   //::write(g_fdX11[1], &ch, 1);

}


void xcb_wait_timer_or_event(xcb_connection_t * pconnection)
{

   struct timeval tv;

   // This returns the FD of the X11 display (or something like that)
   int xcb_fd = xcb_get_file_descriptor(pconnection);

   fd_set in_fds;

   // Create a File Description Set containing xcb_fd
   FD_ZERO(&in_fds);
   FD_SET(xcb_fd, &in_fds);
   FD_SET(g_fdX11[0], &in_fds);

   // Set our timer.  One second sounds good.
   tv.tv_usec = 0;
   tv.tv_sec = 1;

   // Wait for X Event or a Timer
   int num_ready_fds = select(maximum(xcb_fd, g_fdX11[0]) + 1, &in_fds, nullptr, NULL, &tv);

   if (num_ready_fds > 0)
   {

      //printf("Event Received!\n");

      g_bX11Idle = false;

      char buf[32];

      int iRead;

      while((iRead = read(g_fdX11[0], buf, sizeof(buf)))>0)
      {

         //printf("X11 fork count = %d\n", iRead);

      }

   }
   else if (num_ready_fds == 0)
   {

      // Handle timer here
      //printf("Timer Fired!\n");

   }
   else
   {

      //printf("An error occured!\n");

   }

}


//::mutex * g_pmutexX11 = nullptr;
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
//   g_pmutexX11 = new ::mutex();
//
//}


//void xcb_defer_handle_just_hooks()
//{
//
//   if(get_platform_level() <= e_platform_level_apex)
//   {
//
//      xcb_handle_just_hooks();
//
//   }
//
//}
//
//
//void xcb_handle_just_hooks()
//{
//
//   xcb_connection_t * pdisplay = xcb_get_display();
//
//   XEvent e = {};
//
//#if !defined(RASPBIAN)
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
//         synchronous_lock sl(user_mutex());
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
//               __xcb_hook_process_event(pdisplay, &e, nullptr);
//
//               if(__xcb_hook_list_is_empty())
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
//         __xcb_hook_on_idle(pdisplay);
//
//         XUnlockDisplay(pdisplay);
//
//      }
//      catch(...)
//      {
//
//      }
//
////      xcb_wait_timer_or_event(pdisplay);
//
//      if(__xcb_hook_list_is_empty())
//      {
//
//         break;
//
//      }
//
//   }
//
//}


::e_status initialize_xcb();

//bool g_bInitializeX11 = false;
//
//::e_status g_estatusInitializeX11 = ::error_not_initialized;
//
//::e_status defer_initialize_xcb()
//{
//
//   if(!g_bInitializeX11)
//   {
//
//      g_bInitializeX11 = true;
//
//      g_estatusInitializeX11 = initialize_xcb();
//
//   }
//
//   return g_estatusInitializeX11;
//
//}


//i32 _c_XErrorHandler(xcb_connection_t * display, XErrorEvent * perrorevent);


::e_status initialize_xcb()
{

//   if(!XInitThreads())
//   {
//
//      return ::error_failed;
//
//   }
//
//   XSetErrorHandler(_c_XErrorHandler);

   return ::success;

}



