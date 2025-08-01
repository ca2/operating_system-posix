//
// Created by camilo on 16/02/2021.
//
#include "framework.h"
#include "display.h"
#include "windowing.h"
#include "window.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/parallelization/thread.h"
#include "windowing_system_xcb/_xcb.h"
//#include "aura/user/user/interaction_impl.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
////#include "sn/sn.h"
#include <fcntl.h> // library for fcntl function
#include <sys/stat.h>
//#include <Xcb/extensions/xf86vmode.h> // libxxf86vm-dev
//#include <Xcb/Xatom.h>
//!!!#define pointer xcb_pointer
//!!!#include <Xcb/extensions/Xrender.h>
//!!!#undef pointer
#include <unistd.h>
//#include <Xcb/XKBlib.h>
//#include <Xcb/cursorfont.h>
//#include <Xcb/extensions/XInput.h>
//#include <Xcb/extensions/XInput2.h>
//#include <Xcb/XKBlib.h>
#include <X11/XKBlib.h>
#include "windowing_system_xcb/_xcb.h"
#include "acme/parallelization/message_queue.h"
#include "windowing_xcb.h"




//message_queue * aaa_get_message_queue(itask idthread, bool bCreate);


void oswindow_set_active_window(oswindow oswindow);


CLASS_DECL_AURA void update_application_session_cursor(void * pvoidApp, const int_point & pointCursor);

//bool is_return_key(XIRawEvent *happening)
//{
//
//   int i;
//   double *val, *raw_val;
//
//   switch(happening->evtype)
//   {
//      case XI_RawKeyPress:
//      case XI_RawKeyRelease:
//      {
//
//         val = happening->valuators.values;
//
//         raw_val = happening->raw_values;
//
//         if(happening->detail == 36)
//         {
//
//            return true;
//
//         }
//
//         printf("is_return_key    detail: %d\n", happening->detail);
//
//         for (i = 0; i < happening->valuators.mask_len * 8; i++)
//         {
//
//            if (XIMaskIsSet(happening->valuators.mask, i))
//            {
//
//               printf("is_return_key    %2d: %.2f (%.2f)\n", i, *val++, *raw_val++);
//
//            }
//
//         }
//
//         printf("\n");
//
//      }
//
//      break;
//
//   }
//
//   return false;
//
//}


//bool is_space_key(XIRawEvent *happening)
//{
//
//   int i;
//   double *val, *raw_val;
//
//   switch(happening->evtype)
//   {
//      case XI_RawKeyPress:
//      case XI_RawKeyRelease:
//      {
//
//         val = happening->valuators.values;
//
//         raw_val = happening->raw_values;
//
//         if(happening->detail == 65)
//         {
//
//            return true;
//
//         }
//
//         printf("is_space_key    detail: %d\n", happening->detail);
//
//         for (i = 0; i < happening->valuators.mask_len * 8; i++)
//         {
//
//            if (XIMaskIsSet(happening->valuators.mask, i))
//            {
//
//               printf("is_space_key    %2d: %.2f (%.2f)\n", i, *val++, *raw_val++);
//
//            }
//
//         }
//
//         printf("\n");
//
//      }
//
//      break;
//
//   }
//
//   return false;
//
//}


// Tutor Exilius Q(t)List streaming contribution
//::pointer< ::mutex > g_pmutexXcbRunnable = nullptr;
//list < ::pointer<::matter >>* g_prunnableptrlXcb = nullptr;
//::pointer< ::mutex > g_pmutexXcbSync = nullptr;
//manual_reset_happening * g_peventXcbSync = nullptr;
//::pointer<::matter>g_prunnableXcbSync;
xcb_window_t g_windowXcbClient = 0;



int_bool _xcb_get_cursor_pos(xcb_connection_t * d, ::int_point * ppointCursor);


//extern ::pointer< ::mutex >g_pmutexXcbRunnable;
//extern list<::pointer<::matter >>*g_prunnableptrlXcb;
//extern ::pointer< ::mutex >g_pmutexXcbSync;
//extern manual_reset_happening *g_peventXcbSync;
//extern ::pointer<::matter>g_prunnableXcbSync;


//int get_best_ordered_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);
//int get_best_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);

//extern SnLauncheeContext* g_psncontext;
//xcb_connection_t * xcb_connection();
//void wm_toolwindow(oswindow w, bool bToolWindow);
//void wm_state_hidden(oswindow w, bool bSet);
//void wm_state_hidden_raw(oswindow w, bool bSet);
//CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(oswindow oswindow);
//
//
//int_bool xcb_get_cursor_pos(::int_point * ppointCursor);



//xcb_window_t g_windowFocus = 0;


#ifdef LINUX


int _cx_XErrorHandler(xcb_connection_t * display, XErrorEvent * perrorevent);


#endif


//struct MWMHints
//{
//
//   unsigned long flags;
//   unsigned long functions;
//   unsigned long decorations;
//   long input_mode;
//   unsigned long status;
//
//};
//
//
//#define MWM_HINTS_DECORATIONS   (1L << 1)
//
//
///* MWM decorations values */
//#define MWM_DECOR_NONE          0
//#define MWM_DECOR_ALL           (1L << 0)
//#define MWM_DECOR_BORDER        (1L << 1)
//#define MWM_DECOR_RESIZEH       (1L << 2)
//#define MWM_DECOR_TITLE         (1L << 3)
//#define MWM_DECOR_MENU          (1L << 4)
//#define MWM_DECOR_MINIMIZE      (1L << 5)
//#define MWM_DECOR_MAXIMIZE      (1L << 6)


//
//
//oswindow oswindow_defer_get(xcb_window_t window)
//{
//
//   return oswindow_get(window);
//
//}


//
//bool oswindow_remove(xcb_connection_t * display, xcb_window_t window)
//{
//
//   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);
//
//   auto pFind = oswindow_find(display, window);
//
//   if(::is_null(pFind))
//   {
//
//      return false;
//
//   }
//
//   delete ::oswindow_data::s_pdataptra->element_at(iFind);
//
//   ::oswindow_data::s_pdataptra->erase_at(iFind);
//
//   return true;
//
//}

//
//bool oswindow_remove_message_only_window(::windowing::window * puibaseMessageOnlyWindow)
//{
//
//   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);
//
//   auto pFind = oswindow_find_message_only_window(puibaseMessageOnlyWindow);
//
//   if(::is_null(pFind))
//   {
//
//      return false;
//
//   }
//
//   delete ::oswindow_data::s_pdataptra->element_at(iFind);
//
//   ::oswindow_data::s_pdataptra->erase_at(iFind);
//
//   return true;
//
//}






//static oswindow g_oswindowCapture;
//
//
//oswindow get_capture()
//{
//
//   return g_oswindowCapture;
//
//}


namespace windowing_xcb
{


   //bool windowing::__xcb_hook_process_event(xcb_connection_t * pdisplay, xcb_generic_event_t * pevent, XGenericEventCookie * cookie);


//#define SIMPLE_UI_MAX_BUTTON_COUNT 8


   //bool __xcb_hook_list_is_empty();


#ifdef display_lock_LOCK_LOG

   extern bool b_prevent_display_lock_lock_log;

#endif

   oswindow g_oswindowActive;


   oswindow get_active_window()
   {

      return g_oswindowActive;

   }

//
//   void oswindow_set_active_window(oswindow oswindow)
//   {
//
//      if (g_oswindowActive)
//      {
//
//         try
//         {
//
//            if (g_oswindowActive->m_pimpl)
//            {
//
//               if (g_oswindowActive->m_pimpl->m_puserinteraction)
//               {
//
//                  g_oswindowActive->m_pimpl->m_puserinteraction->m_ewindowflag -= ::e_window_flag_active;
//
//                  g_oswindowActive->m_pimpl->m_puserinteraction->post_message(e_message_activate, 0);
//
//               }
//
//            }
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//
//      g_oswindowActive = oswindow;
//
//      if (g_oswindowActive)
//      {
//
//         try
//         {
//
//            if (g_oswindowActive->m_pimpl)
//            {
//
//               if (g_oswindowActive->m_pimpl->m_puserinteraction)
//               {
//
//                  g_oswindowActive->m_pimpl->m_puserinteraction->m_ewindowflag += ::e_window_flag_active;
//
//                  g_oswindowActive->m_pimpl->m_puserinteraction->post_message(e_message_activate, 1);
//
//               }
//
//            }
//
//         }
//         catch (...)
//         {
//
//         }
//
//      }
//
//   }
//


//oswindow windowing::get_active_window()
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   oswindow oswindow = nullptr;
//
//   windowing_output_debug_string("::GetFocus 1");
//
//#ifdef display_lock_LOCK_LOG
//
//   b_prevent_display_lock_lock_log = false;
//
//#endif
//
//   display_lock displaylock(xcb_display());
//
//   windowing_output_debug_string("::GetFocus 1.01");
//
//   if(!m_pdisplay)
//   {
//
//      windowing_output_debug_string("::GetFocus 1.1");
//
//      return pwindow;
//
//   }
//
//   return _xcb_get_active_window(d);
//   //int screen = XDefaultScreen((xcb_connection_t *) d);
//
//   //xcb_window_t windowRoot = RootWindow((xcb_connection_t *) d, screen);
//
//   //xcb_window_t window = xcb_get_long_property(d, windowRoot, (char*) "_NET_ACTIVE_WINDOW");
//
//   ///pwindow = oswindow_defer_get(window);
//
//   // windowing_output_debug_string("::GetActiveWindow 2");
//
////   return pwindow;
//
//}




// int_bool is_window_occluded(oswindow oswindow)
// {

//    synchronous_lock synchronouslock(user_synchronization());

//    windowing_output_debug_string("::GetFocus 1");

// #ifdef display_lock_LOCK_LOG

//    b_prevent_display_lock_lock_log = false;

// #endif

//    display_lock display(xcb_connection_t());

//    windowing_output_debug_string("::GetFocus 1.01");

//    if(display.is_null())
//    {

//       windowing_output_debug_string("::GetFocus 1.1");

//       return false;

//    }

//    comparable_array < xcb_window_t > windowa;

//    if(!xcb_window_list(display, windowa))
//    {

//       return true;

//    }

//    if(windowa.last() == oswindow->window())
//    {

//       return false;

//    }

//    auto pFind = windowa.find_last(oswindow->window());

//    if(::is_null(pFind))
//    {

//       return true;

//    }

//    ::int_rectangle rectangle;

//    xcb_get_window_rect(display, oswindow->window(), rectangle);

//    //r = oswindow->m_pimpl->m_puserinteraction->window_rectangle();

//    string strTopic = xcb_get_name(display, oswindow->window());

//    ::int_rectangle rectangleTest;

//    for(iFind++; iFind < windowa.get_size(); iFind++)
//    {

//       string strItem = xcb_get_name(display, windowa[iFind]);

//       ::int_rectangle rectangleHigher;

//       if(xcb_get_window_rect(display, windowa[iFind], rectangleHigher))
//       {

//          if(rectangleTest.intersect(rectangleHigher, rectangle))
//          {

//             return true;

//          }

//       }

//    }

//    return false;

// }







//oswindow oswindow_get_if_found(xcb_window_t w)
//{
//
//   if(::oswindow_find(w) >= 0)
//   {
//
//      return ::oswindow_get(w);
//
//   }
//
//   return nullptr;
//
//}

//
//oswindow get_parent(oswindow oswindow);
//




//
//
//oswindow g_oswindowDesktop;
//
//
//xcb_connection_t * xcb_connection();



//
//oswindow get_desktop_window()
//{
//
//   return g_oswindowDesktop;
//
//}


/* Copyright (c) 2012 the authors listed at the following URL, and/or
the authors of referenced articles or incorporated external code:
http://en.literateprograms.org/Hello_World_(C,_Cairo)?action=history&offset=20070528220552

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to uxse, cxopy, mxodify, mxerge, pxublish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, topic to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Retrieved from: http://en.literateprograms.org/Hello_World_(C,_Cairo)?oldid=10388
*/


#define SIZEX 100
#define SIZEY  50


//void message_box_paint(::draw2d::graphics_pointer & pgraphics, string_array & stra, bool_array  & baTab, ::int_array  & ya,::int_size * psize)
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   pgraphics->fill_rectangle(::int_rectangle(*psize), rgb(84, 90, 80));
//
//   ::draw2d::brush_pointer pen(e_create_new);
//
//   ppen->create_solid(0);
//
//   for(::collection::index i = 0; i < stra.get_count(); i++)
//   {
//
//      pgraphics->text_out(10.0 + 50.0 + (baTab[i] ? 25.0 : 0), 10.0 + 50.0 + ya[i], stra[i]);
//
//   }
//
//}
//
#define _NET_WM_STATE_REMOVE        0    // remove/unset property
#define _NET_WM_STATE_ADD           1    // add/set property
#define _NET_WM_STATE_TOGGLE        2    // toggle property

   xcb_atom_t *wm_get_list_raw(oswindow w, xcb_atom_t atomList, unsigned long int *items);

   int wm_test_state(oswindow w, const_char_pointer pszNetStateFlag);

   int wm_test_state_raw(oswindow w, const_char_pointer pszNetStateFlag);

   int wm_test_list_raw(oswindow w, xcb_atom_t atomList, xcb_atom_t atomFlag);

   bool wm_add_remove_list_raw(oswindow w, xcb_atom_t atomList, xcb_atom_t atomFlag, bool bSet);



//int_bool IsWindowVisibleRaw(oswindow w)
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   xcb_connection_t * display = w->display();
//
//   xcb_window_t window = w->window();
//
//   return IsWindowVisibleRaw(display, window);
//
//}



   ::windowing::window *oswindow_get(oswindow oswindow)
   {

      if (is_null(oswindow))
      {

         return nullptr;

      }

#ifdef WINDOWS_DESKTOP

      critical_section_lock slOsWindow(::user::g_pcsImpl);

      return ::user::g_pmapImpl->operator[](oswindow);

#else

      return oswindow->m_pwindow;

#endif

   }


//
//::e_status xcb_hook::hook()
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   g_xcbhooka.add(this);
//
//   return ::success;
//
//}
//
//::e_status xcb_hook::unhook()
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   g_xcbhooka.remove(this);
//
//   return ::success;
//
//}




#if !defined(RASPBERRYPIOS)


   bool xcb_process_event(xcb_connection_t *pdisplay, xcb_generic_event_t *pevent, XGenericEventCookie *cookie);


#else


   bool xcb_process_event(osdisplay_data * pdisplaydata, XEvent & e);


#endif


   void xcb_post_message(MESSAGE &msg);


   bool g_bSkipMouseMessageInXcess = true;


   unsigned int g_dwLastMotion = 0;


   unsigned int g_dwMotionSkipTimeout = 23;


   bool post_ui_message(const MESSAGE &message);


   void windowing::initialize_windowing(::user::user * puser)
   {


      informationf("windowing_xcb::initialize_windowing");


      ::windowing_posix::windowing::initialize_windowing(puser);


      informationf("windowing_xcb::initialize_windowing starting");

      auto pdisplay = __øcreate<::windowing::display>();

//      if(!pdisplay)
//      {
//
//         informationf("\nFailed to __øcreate < ::windowing::display > at windowing_xcb::windowing::initialize");
//
//         //return ::error_no_factory;
//
//         throw ::exception(error_fac)
//
//      }

      informationf("windowing_xcb::initialize_windowing (1)");

      //estatus =
      //
      pdisplay->initialize_display(this);

//      if(!estatus)
//      {
//
//         informationf("\nFailed to initialize_display at windowing_xcb::windowing::initialize");
//
//         return estatus;
//
//      }

      m_pdisplay = pdisplay;

//      if(!pdisplay)
//      {
//
//         informationf("\nFailed to cast pdisplay to m_pdisplay at windowing_xcb::windowing::initialize");
//
//         return error_no_interface;
//
//      }


      informationf("windowing_xcb::initialize_windowing (1.1)");
      ///estatus =
      ///
      m_pdisplay->open_display();


      informationf("windowing_xcb::initialize_windowing (2)");

      _libsn_start_context();


      //g_pmutexXcbRunnable = ___new ::pointer < ::mutex >();

      //g_prunnableptrlXcb = aaa_memory_new list<::pointer<::matter >>);

//      g_pmutexXcbSync = ___new ::pointer < ::mutex >();

//      g_peventXcbSync = ___new manual_reset_happening();

      //oswindow_data::s_pdataptra = ___new oswindow_dataptra();

      //oswindow_data::s_pmutex = aaa_memory_new ::pointer < ::mutex >;

      //osdisplay_data::s_pdataptra = ___new osdisplay_dataptra();

      //osdisplay_data::s_pmutex = aaa_memory_new ::pointer < ::mutex >;

      //return true;

      informationf("windowing_xcb::initialize_windowing end");

   }


   void windowing::terminate_windowing()
   {

      ::windowing::windowing::terminate_windowing();
      //::acme::del(osdisplay_data::s_pmutex);

      //::acme::del(osdisplay_data::s_pdataptra);

      //::acme::del(oswindow_data::s_pmutex);

      //::acme::del(oswindow_data::s_pdataptra);

//      {
//
//         synchronous_lock synchronouslock(g_pmutexXcbRunnable);
//
//         ::acme::del(g_prunnableptrlXcb);
//
//      }
//
//      ::acme::del(g_pmutexXcbRunnable);

//      ::acme::del(g_peventXcbSync);

//      ::acme::del(g_pmutexXcbSync);

      //return false;

   }



//
//#ifdef RASPBERRYPIOS
//
//
//HCURSOR imaging::CreateAlphaCursor(oswindow window, const ::image::image *pimage, int xHotSpot, int yHotSpot)
//{
//
//   return hcursor_null;
//
//}
//
//
//#else





//#endif // RASPBERRYPIOS


//
//int_bool WINAPI SetWindowPos(oswindow hWnd,oswindow hWndInsertAfter,int X,int Y,int cx,int cy,unsigned int uFlags)
//{
//
//   return hWnd->set_window_position(hWndInsertAfter, X, Y, cx, cy, uFlags);
//
//}






//   void xcb_async_runnable(::matter *prunnable)
//   {
//
////      {
////
////         synchronous_lock synchronouslock(g_pmutexXcbRunnable);
////
////         g_prunnableptrlXcb->add_tail(prunnable);
////
////      }
//
//      //xcb_kick_idle();
//
//   }


   int g_iXcbRef = 0;

   void xcb_term();

   void xcb_start();

   //void ui_post_quit();

//   void defer_term_ui()
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      g_iXcbRef--;
//
//      if (g_iXcbRef <= 0)
//      {
//
//         auto
//
//         windowing_post_quit();
//
//         //ui_post_quit();
//
//      }
//
//   }


//void xcb_thread(osdisplay_data * pdisplaydata);


   ::pointer<::thread>g_pthreadXlib;


   itask g_itaskXlib;


   itask xcb_get_itask()
   {

      return g_itaskXlib;

   }


   CLASS_DECL_ACME ::thread *xcb_get_thread()
   {

      return g_pthreadXlib;

   }

//
//osdisplay_data * xcb_main_display();
//


   bool windowing::post_ui_message(const MESSAGE &message)
   {

      oswindow oswindow = message.oswindow;

      if(::is_null(oswindow))
      {

         return false;

      }

      auto pimpl = oswindow->m_pwindow;

      if(::is_null(pimpl))
      {

         return false;

      }

      auto pinteraction = pimpl->m_puserinteraction;

      if(::is_null(pinteraction))
      {

         return false;

      }

      ::thread *pthread = nullptr;

      if (::is_set(pinteraction))
      {

         pthread = pinteraction->m_pthreadUserInteraction;

      }

      if (::is_null(pthread))
      {

         return false;

      }

      auto pmessagequeue = pthread->m_pmessagequeue.get();

      if (pmessagequeue == nullptr)
      {

         if (message.m_emessage == e_message_quit)
         {

            return false;

         }

         pmessagequeue = pthread->get_message_queue();

      }

      if (pmessagequeue == nullptr)
      {

         return false;

      }

      synchronous_lock ml(pmessagequeue->synchronization());

      if (message.m_emessage == e_message_quit)
      {

         informationf("e_message_quit thread");

      }

      if (message.m_emessage == e_message_left_button_down)
      {

         informationf("post_ui_message::e_message_left_button_down\n");

      }
      else if (message.m_emessage == e_message_left_button_up)
      {

         informationf("post_ui_message::e_message_left_button_up\n");

      }

      pmessagequeue->m_messagea.add(message);

      pmessagequeue->m_happeningNewMessage.set_happening();

      return true;

   }


   bool windowing::post_ui_message(::message::message * pmessage)
   {

      oswindow oswindow = pmessage->m_oswindow;

      if(::is_null(oswindow))
      {

         return false;

      }

      auto pimpl = oswindow->m_pwindow;

      if(::is_null(pimpl))
      {

         return false;

      }

      auto puserinteraction = pimpl->m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         return false;

      }

      puserinteraction->post_message(pmessage);

      return true;

   }


   //
//int_bool set_foreground_window(oswindow oswindow)
//{
//
//   if(!::is_window(oswindow))
//   {
//
//      return false;
//
//   }
//
//   xcb_fork([oswindow]()
//            {
//
//               display_lock d(xcb_connection_t());
//
//               if(d.is_null())
//               {
//
//                  return;
//
//               }
//
//               XRaiseWindow(d, oswindow->window());
//
//               XSetInputFocus(d, oswindow->window(), RevertToNone, CurrentTime);
//
//            });
//
//   return true;
//
//}
//


//   void windowing::windowing_main()
//   {
//
//      xcb_main();
//
//   }


//   void windowing::xcb_main()
//   {
//
//      while (!m_bFinishXcbThread)
//      {
//
//         xcb_message_loop_step();
//
//      }
//
//   }


//
//
//
//message_queue * aaa_get_message_queue(itask idthread, bool bCreate);
//
//
//void oswindow_set_active_window(oswindow oswindow);
//
//
//CLASS_DECL_AURA void update_application_session_cursor(void * pvoidApp, const int_point & pointCursor);
//
//
//
//
//int_bool _xcb_get_cursor_pos(xcb_connection_t * d, ::int_point * ppointCursor);
//



//int get_best_ordered_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);
//int get_best_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);

//extern SnLauncheeContext *g_psncontext;
//xcb_connection_t * xcb_connection();
//void wm_toolwindow(oswindow w, bool bToolWindow);
//void wm_state_hidden(oswindow w, bool bSet);
//void wm_state_hidden_raw(oswindow w, bool bSet);
//CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(oswindow oswindow);
//
//
//int_bool xcb_get_cursor_pos(::int_point * ppointCursor);
//

//
//
//void ui_post_quit();
//
//
//
//
//
//
//void xcb_thread(osdisplay_data * pdisplaydata);

//void __axis_xcb_input_thread(osdisplay_data * pdisplaydata);




//
//osdisplay_data * xcb_main_display();
//
//
//
//void ui_post_quit()
//{
//
//}
//

//
//
//void os_menu_item_enable(void * pitem, bool bEnable)
//{
//
//}
//
//
//void os_menu_item_check(void * pitem, bool bCheck)
//{
//
//}
//
//
//oswindow get_parent(oswindow oswindow)
//{
//111
//   return nullptr;
//
//}







} // namespace windowing_xcb

//
//
//const_char_pointer g_pszaNetWmState[] =
//   {
//      "_NET_WM_STATE_ABOVE",
//      "_NET_WM_STATE_BELOW",
//      "_NET_WM_STATE_HIDDEN",
//      "_NET_WM_STATE_MAXIMIZED_HORZ",
//      "_NET_WM_STATE_MAXIMIZED_VERT",
//      "_NET_WM_STATE_FULLSCREEN",
//      "_NET_WM_STATE_SKIP_TASKBAR",
//      NULL
//   };
//
//

//
//const_char_pointer net_wm_state_text(enum_net_wm_state estate)
//{
//
//   if (estate < e_net_wm_state_first || estate >= e_net_wm_state_count)
//   {
//
//      return "";
//
//   }
//
//   return g_pszaNetWmState[estate];
//
//}
//
//
//enum_net_wm_state net_wm_state(const_char_pointer pszText)
//{
//
//   if (::is_null(scopedstrText))
//   {
//
//      return e_net_wm_state_count;
//
//   }
//
//   auto ppsz = g_pszaNetWmState;
//
//   int i = 0;
//
//   while (ppsz[i] != NULL)
//   {
//
//      if (!case_insensitive_ansi_compare(scopedstrText, ppsz[i]))
//      {
//
//         break;
//
//      }
//
//      i++;
//
//   }
//
//   return (enum_net_wm_state) i;
//
//}


//
//void xcb_check_status(int status, unsigned long window)
//{
//   if (status == BadWindow)
//   {
//      printf("window atom # 0x%lx does not exists!", window);
//      //   exit(1);
//   }
//
//   if (status != Success)
//   {
//      printf("XGetWindowProperty failed!");
//      // exit(2);
//   }
//}
//
//#define MAXSTR 1000
//
//unsigned char *xcb_get_string_property(xcb_connection_t *display, xcb_window_t window, char *property_name)
//{
//
//   unsigned char *prop;
//   xcb_atom_t actual_type, filter_atom;
//   int actual_format, status;
//   unsigned long nitems, bytes_after;
//
//   filter_atom = XInternAtom(display, property_name, true);
//   status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, false, AnyPropertyType,
//                               &actual_type, &actual_format, &nitems, &bytes_after, &prop);
//   xcb_check_status(status, window);
//   return prop;
//
//}
//
//
//unsigned long xcb_get_long_property(xcb_connection_t *d, xcb_window_t w, char *property_name)
//{
//
//   unsigned char *prop = xcb_get_string_property(d, w, property_name);
//
//   unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);
//
//   return long_property;
//
//}
//
//
//bool xcb_get_client_rect(xcb_connection_t * pdisplay, xcb_window_t window, ::int_rectangle *prectangle)
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   XWindowAttributes attr;
//
//   if (XGetWindowAttributes(pdisplay, window, &attr) == 0)
//   {
//
//      windowing_output_debug_string("::this->rectangle 1.2 (xgetwindowattributes failed");
//
//      return false;
//
//   }
//
//   prectangle->left() = 0;
//
//   prectangle->top() = 0;
//
//   prectangle->right() = prectangle->left() + attr.width;
//
//   prectangle->bottom() = prectangle->top() + attr.height;
//
//   windowing_output_debug_string("::this->rectangle 2");
//
//   return true;
//
//}




//
//
//bool xcb_get_window_rect(xcb_connection_t * d, xcb_window_t window, ::int_rectangle * prectangle)
//{
//
//   XWindowAttributes attrs;
//
//   if(!XGetWindowAttributes(d, window, &attrs))
//   {
//
//      windowing_output_debug_string("::xcb_get_window_rect 1.1 (xgetwindowattributes failed)");
//
//      return false;
//
//   }
//
//   int x = 0;
//
//   int y = 0;
//
//   int screen = XDefaultScreen((xcb_connection_t *) d);
//
//   xcb_window_t windowRoot = RootWindow((xcb_connection_t *) d, screen);
//
//   xcb_window_t child;
//
//   XTranslateCoordinates( d, window, windowRoot, 0, 0, &x, &y, &child );
//
//   prectangle->left()      = x + attrs.x;
//
//   prectangle->top()       = y + attrs.y;
//
//   prectangle->right()     = x + attrs.x    + attrs.width;
//
//   prectangle->bottom()    = y + attrs.y    + attrs.height;
//
//
//
//   windowing_output_debug_string("::xcb_get_window_rect 2");
//
//   return true;
//
//}


//bool xcb_runnable_step()
//{
//
//   bool bDoneMuchThings = false;
//
////   {
////
////      synchronous_lock synchronouslock(g_pmutexXcbSync);
////
////      if (g_prunnableXcbSync)
////      {
////
////         g_prunnableXcbSync->operator()();
////
////         g_prunnableXcbSync.release();
////
////         g_peventXcbSync->set_happening();
////
////         bDoneMuchThings = true;
////
////      }
////
////   }
//
//   {
//
//      synchronous_lock synchronouslock(g_pmutexXcbRunnable);
//
//      while (g_prunnableptrlXcb->has_elements() && ::thread_get_run())
//      {
//
//         ::pointer<::matter>prunnable = g_prunnableptrlXcb->pop_front();
//
//         synchronouslock.unlock();
//
//         prunnable->operator()();
//
//         synchronouslock.lock();
//
//         bDoneMuchThings = true;
//
//      }
//
//   }
//
//   return bDoneMuchThings;
//
//}


//::e_status initialize_xcb();
//
//
//::pointer< ::mutex > g_pmutexXcb = nullptr;
//
//
//::e_status g_estatusInitializeXcb = error_not_initialized;
//
//
//::e_status defer_initialize_xcb()
//{
//
//   if(g_estatusInitializeXcb == error_not_initialized)
//   {
//
//      g_estatusInitializeXcb = initialize_xcb();
//
//   }
//
//   return g_estatusInitializeXcb;
//
//}
//
//
//mutex * user_synchronization()
//{
//
//   return g_pmutexXcb;
//
//}



