#include "framework.h"
#include <fcntl.h> // library for fcntl function
#include <sys/stat.h>


//http://rosettacode.org/wiki/Window_creation/X11

#include <stdio.h>

#include <string.h>


//bool __xcb_hook_process_event(xcb_connection_t * pdisplay, XEvent & e, XGenericEventCookie * cookie);
bool __xcb_hook_process_event(xcb_connection_t * pdisplay, xcb_generic_event_t * pevent);


#define SIMPLE_UI_MAX_BUTTON_COUNT 8


bool __xcb_hook_list_is_empty();


extern ::particle * user_synchronization();


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





//GC xcb_create_gc(Colormap colormap, xcb_connection_t* pdisplay, xcb_window_t window, ::u8 a, ::u8 r, ::u8 g, ::u8 b)
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

//::e_status message_box_synchronous(oswindow oswindow, const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, ::future future)
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



