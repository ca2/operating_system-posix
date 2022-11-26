//
// Created by camilo on 16/02/2021.
//
#include "operating-system-posix/windowing_x11/framework.h"
#include "aura/operating_system/x11/_x11.h"
#include "_x11.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "aura_posix/x11/display_lock.h"
////#include "sn/sn.h"
#include <fcntl.h> // library for fcntl function
#include <sys/stat.h>
// apt install libxxf86vm-dev
#include <X11/extensions/xf86vmode.h>
#include <X11/Xatom.h>
//!!!#define pointer x11_pointer
//!!!#include <X11/extensions/Xrender.h>
//!!!#undef pointer
#include <unistd.h>
//#include <X11/XKBlib.h>
#include <X11/cursorfont.h>
#include <X11/extensions/XInput.h>
#include <X11/extensions/XInput2.h>
#include <X11/XKBlib.h>
//#define memory_new ACME_NEW
//#include "aura/operating_system/x11/_x11.h"
#include "acme/parallelization/message_queue.h"
#include "windowing_x11.h"
#include "windowing.h"
#include "window.h"
#include "display.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/platform/session.h"
#include "aura/platform/application.h"
#include "aura/message/user.h"
#include "aura_posix/x11/xim_keyboard.h"

//bool x11_runnable_step();


//::pointer< ::mutex > g_pmutexX11Runnable = nullptr;
//list < ::pointer<::matter >>* g_prunnableptrlX11 = nullptr;


//::point_i32 g_pointX11Cursor;


message_queue * get_message_queue(itask_t idthread, bool bCreate);


void oswindow_set_active_window(oswindow oswindow);


CLASS_DECL_AURA void update_application_session_cursor(void * pvoidApp, const point_i32 & pointCursor);

bool is_return_key(XIRawEvent *event)
{

   int i;
   double *val, *raw_val;

   switch(event->evtype)
   {
      case XI_RawKeyPress:
      case XI_RawKeyRelease:
      {

         val = event->valuators.values;

         raw_val = event->raw_values;

         if(event->detail == 36)
         {

            return true;

         }

         printf("is_return_key    detail: %d\n", event->detail);

         for (i = 0; i < event->valuators.mask_len * 8; i++)
         {

            if (XIMaskIsSet(event->valuators.mask, i))
            {

               printf("is_return_key    %2d: %.2f (%.2f)\n", i, *val++, *raw_val++);

            }

         }

         printf("\n");

      }

      break;

   }

   return false;

}


bool is_space_key(XIRawEvent *event)
{

   int i;
   double *val, *raw_val;

   switch(event->evtype)
   {
      case XI_RawKeyPress:
      case XI_RawKeyRelease:
      {

         val = event->valuators.values;

         raw_val = event->raw_values;

         if(event->detail == 65)
         {

            return true;

         }

         printf("is_space_key    detail: %d\n", event->detail);

         for (i = 0; i < event->valuators.mask_len * 8; i++)
         {

            if (XIMaskIsSet(event->valuators.mask, i))
            {

               printf("is_space_key    %2d: %.2f (%.2f)\n", i, *val++, *raw_val++);

            }

         }

         printf("\n");

      }

      break;

   }

   return false;

}


// Tutor Exilius Q(t)List streaming contribution
//::pointer< ::mutex > g_pmutexX11Runnable = nullptr;
//list < ::pointer<::matter >>* g_prunnableptrlX11 = nullptr;
//::pointer< ::mutex > g_pmutexX11Sync = nullptr;
//manual_reset_event * g_peventX11Sync = nullptr;
//::pointer<::matter>g_prunnableX11Sync;
Window g_windowX11Client = 0;



int_bool _x11_get_cursor_pos(Display * d, POINT_I32 * ppointCursor);


//extern ::pointer< ::mutex >g_pmutexX11Runnable;
//extern list<::pointer<::matter >>*g_prunnableptrlX11;
//extern ::pointer< ::mutex >g_pmutexX11Sync;
//extern manual_reset_event *g_peventX11Sync;
//extern ::pointer<::matter>g_prunnableX11Sync;


//int get_best_ordered_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);
//int get_best_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);

//extern SnLauncheeContext* g_psncontext;
//Display * Display();
//void wm_toolwindow(oswindow w, bool bToolWindow);
//void wm_state_hidden(oswindow w, bool bSet);
//void wm_state_hidden_raw(oswindow w, bool bSet);
//CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(oswindow oswindow);
//
//
//int_bool x11_get_cursor_pos(POINT_I32 * ppointCursor);



Window g_windowFocus = 0;

i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);


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
//oswindow oswindow_defer_get(Window window)
//{
//
//   return oswindow_get(window);
//
//}


//
//bool oswindow_remove(Display * display, Window window)
//{
//
//   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);
//
//   iptr iFind = oswindow_find(display, window);
//
//   if(iFind < 0)
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
//bool oswindow_remove_message_only_window(::user::interaction_impl * puibaseMessageOnlyWindow)
//{
//
//   single_lock slOsWindow(::osdisplay_data::s_pmutex, true);
//
//   iptr iFind = oswindow_find_message_only_window(puibaseMessageOnlyWindow);
//
//   if(iFind < 0)
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






static oswindow g_oswindowCapture;


oswindow get_capture()
{

   return g_oswindowCapture;

}


namespace windowing_x11
{


   //bool windowing::__x11_hook_process_event(Display * pdisplay, XEvent * pevent, XGenericEventCookie * cookie);


//#define SIMPLE_UI_MAX_BUTTON_COUNT 8


   //bool __x11_hook_list_is_empty();


#ifdef display_lock_LOCK_LOG

   extern bool b_prevent_display_lock_lock_log;

#endif

//   oswindow g_oswindowActive;
//
//
//   oswindow get_active_window()
//   {
//
//      return g_oswindowActive;
//
//   }


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


   void windowing::clear_active_window(::thread * pthread, ::windowing::window * pwindow)
   {

      if (!m_pdisplay)
      {

         //return error_failed;

         throw ::exception(error_failed);

      }

      auto pwindowActive = m_pdisplay->m_pwindowActive;

      if (!pwindowActive)
      {

         //return ::success_none;

         return;

      }

      if(pwindowActive != pwindow)
      {

         return;

      }

      m_pdisplay->m_pwindowActive = nullptr;

      //return ::success;

   }


   ::windowing::window *windowing::get_active_window(::thread *pthread)
   {

      if (!m_pdisplay)
      {

         return nullptr;

      }

      auto pwindowActive = m_pdisplay->m_pwindowActive;

      if (!pwindowActive)
      {

         return nullptr;

      }

      return pwindowActive;

   }


//oswindow windowing::get_active_window()
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   oswindow oswindow = nullptr;
//
//   windowing_output_debug_string("\n::GetFocus 1");
//
//#ifdef display_lock_LOCK_LOG
//
//   b_prevent_display_lock_lock_log = false;
//
//#endif
//
//   display_lock displaylock(x11_display());
//
//   windowing_output_debug_string("\n::GetFocus 1.01");
//
//   if(!m_pdisplay)
//   {
//
//      windowing_output_debug_string("\n::GetFocus 1.1");
//
//      return pwindow;
//
//   }
//
//   return _x11_get_active_window(d);
//   //int screen = XDefaultScreen((Display *) d);
//
//   //Window windowRoot = RootWindow((Display *) d, screen);
//
//   //Window window = x11_get_long_property(d, windowRoot, (char*) "_NET_ACTIVE_WINDOW");
//
//   ///pwindow = oswindow_defer_get(window);
//
//   // windowing_output_debug_string("\n::GetActiveWindow 2");
//
////   return pwindow;
//
//}


//   Window *display::x11_window_list(unsigned long *len)
//   {
//
//      Atom prop = intern_atom("_NET_CLIENT_LIST_STACKING", False);
//
//      if (prop == 0)
//      {
//
//         prop = intern_atom("_NET_CLIENT_LIST", False);
//
//      }
//
//      if (prop == 0)
//      {
//
//         return nullptr;
//
//      }
//
//      Atom type;
//      int form;
//      unsigned long remain;
//      unsigned char *list;
//
//      errno = 0;
//      if (XGetWindowProperty(Display(), DefaultRootWindow(Display()), prop, 0, 1024, False, XA_WINDOW,
//                             &type, &form, len, &remain, &list) != Success)
//      {
//         output_debug_string("winlist() -- GetWinProp");
//         return nullptr;
//      }
//
//      return (Window *) list;
//
//   }


//   bool display::x11_window_list(array<Window> &windowa)
//   {
//
//      unsigned long len = 0;
//
//      Window *list = (Window *) x11_window_list(&len);
//
//      if (list == nullptr)
//      {
//
//         return false;
//
//      }
//
//      for (int i = 0; i < (int) len; i++)
//      {
//
//         windowa.add(list[i]);
//
//      }
//
//      XFree(list);
//
//      return true;
//
//   }


//   bool display::point_is_window_origin(POINT_I32 pointHitTest, ::windowing::window *pwindowExclude, int iMargin)
//   {
//
//      bool bIsOrigin = false;
//
//      auto pwindowing = x11_windowing();
//
//      pwindowing->x11_start(__routine([this, pointHitTest, pwindowExclude, iMargin, &bIsOrigin]()
//               {
//
//                  ::windowing_x11::window *pwindowx11Exclude = nullptr;
//
//                  if (pwindowExclude)
//                  {
//
//                     pwindowx11Exclude = dynamic_cast < ::windowing_x11::window * >(pwindowExclude);
//
//                  }
//
//                  synchronous_lock synchronouslock(user_synchronization());
//
//                  windowing_output_debug_string("\n::GetFocus 1");
//
//#ifdef display_lock_LOCK_LOG
//
//                  b_prevent_display_lock_lock_log = false;
//
//#endif
//
//                  if (!Display())
//                  {
//
//                     windowing_output_debug_string("\n::GetFocus 1.1");
//
//                     return;
//
//                  }
//
//                  display_lock display(this);
//
//                  windowing_output_debug_string("\n::GetFocus 1.01");
//
//                  comparable_array<Window> windowa;
//
//                  if (!x11_window_list(windowa))
//                  {
//
//                     bIsOrigin = true;
//
//                     return;
//
//                  }
//
//                  ::rectangle_i32 rectangleTest;
//
//                  for (index i = 0; i < windowa.get_size(); i++)
//                  {
//
//                     string strItem = ::x11_get_name(Display(), windowa[i]);
//
//                     ::rectangle_i32 rectangleHigher;
//
//                     if (::is_set(pwindowx11Exclude) && windowa[i] == pwindowx11Exclude->Window())
//                     {
//
//                        continue;
//
//                     }
//
//                     if (::x11_get_window_rect(Display(), windowa[i], rectangleHigher))
//                     {
//
//                        ::rectangle_i32 rectangleHitTest;
//
//                        rectangleHitTest.set(rectangleHigher.origin(), ::size_i32());
//
//                        rectangleHitTest.inflate(iMargin + 1);
//
//                        if (rectangleHitTest.contains(pointHitTest))
//                        {
//
//                           bIsOrigin = true;
//
//                           return;
//
//                        }
//
//                     }
//
//                  }
//
//               }));
//
//      return bIsOrigin;
//
//   }


// int_bool is_window_occluded(oswindow oswindow)
// {

//    synchronous_lock synchronouslock(user_synchronization());

//    windowing_output_debug_string("\n::GetFocus 1");

// #ifdef display_lock_LOCK_LOG

//    b_prevent_display_lock_lock_log = false;

// #endif

//    display_lock display(Display());

//    windowing_output_debug_string("\n::GetFocus 1.01");

//    if(display.is_null())
//    {

//       windowing_output_debug_string("\n::GetFocus 1.1");

//       return false;

//    }

//    comparable_array < Window > windowa;

//    if(!x11_window_list(display, windowa))
//    {

//       return true;

//    }

//    if(windowa.last() == oswindow->window())
//    {

//       return false;

//    }

//    index iFind = windowa.find_last(oswindow->window());

//    if(iFind < 0)
//    {

//       return true;

//    }

//    ::rectangle_i32 rectangle;

//    x11_get_window_rect(display, oswindow->window(), rectangle);

//    //r = oswindow->m_pimpl->m_puserinteraction->get_window_rect();

//    string strTopic = x11_get_name(display, oswindow->window());

//    ::rectangle_i32 rectangleTest;

//    for(iFind++; iFind < windowa.get_size(); iFind++)
//    {

//       string strItem = x11_get_name(display, windowa[iFind]);

//       ::rectangle_i32 rectangleHigher;

//       if(x11_get_window_rect(display, windowa[iFind], rectangleHigher))
//       {

//          if(rectangleTest.intersect(rectangleHigher, rectangle))
//          {

//             return true;

//          }

//       }

//    }

//    return false;

// }







//oswindow oswindow_get_if_found(Window w)
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
//Display * Display();



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


//void message_box_paint(::draw2d::graphics_pointer & pgraphics, string_array & stra, bool_array  & baTab, int_array  & ya,SIZE_I32 * psize)
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   pgraphics->fill_rectangle(::rectangle_i32(*psize), rgb(84, 90, 80));
//
//   ::draw2d::brush_pointer pen(e_create_new);
//
//   ppen->create_solid(0);
//
//   for(index i = 0; i < stra.get_count(); i++)
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

   Atom *wm_get_list_raw(oswindow w, Atom atomList, unsigned long int *items);

   int wm_test_state(oswindow w, const char *pszNetStateFlag);

   int wm_test_state_raw(oswindow w, const char *pszNetStateFlag);

   int wm_test_list_raw(oswindow w, Atom atomList, Atom atomFlag);

   bool wm_add_remove_list_raw(oswindow w, Atom atomList, Atom atomFlag, bool bSet);



//int_bool IsWindowVisibleRaw(oswindow w)
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   Display * display = w->display();
//
//   Window window = w->window();
//
//   return IsWindowVisibleRaw(display, window);
//
//}



   ::user::interaction_impl *oswindow_get(oswindow oswindow)
   {

      if (is_null(oswindow))
      {

         return nullptr;

      }

#ifdef WINDOWS_DESKTOP

      critical_section_lock slOsWindow(::user::g_pcsImpl);

      return ::user::g_pmapImpl->operator[](oswindow);

#else

      return oswindow->m_puserinteractionimpl;

#endif

   }


//
//::e_status x11_hook::hook()
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   g_x11hooka.add(this);
//
//   return ::success;
//
//}
//
//::e_status x11_hook::unhook()
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   g_x11hooka.remove(this);
//
//   return ::success;
//
//}




//#if !defined(RASPBIAN)


   bool x11_process_event(Display *pdisplay, XEvent *pevent, XGenericEventCookie *cookie);


//#else


   //bool x11_process_event(osdisplay_data * pdisplaydata, XEvent & e);


//#endif


   void x11_post_message(MESSAGE &msg);


   bool g_bSkipMouseMessageInXcess = true;


   ::u32 g_dwLastMotion = 0;


   ::u32 g_dwMotionSkipTimeout = 23;


#ifdef display_lock_LOCK_LOG


   extern bool b_prevent_display_lock_lock_log;


#endif



   bool post_ui_message(const MESSAGE &message);



//gboolean x11_source_func(gpointer ppointer);


   Atom g_atomKickIdle = 0;




//void start_x11_thread(osdisplay_data * pdisplaydata)
//{
//
//   Display *pdisplay = pdisplaydata->display();
//
//   if (pdisplay == nullptr)
//   {
//
//      return;
//
//   }
//
//   ::task_set_name("x11_thread");
//
////   g_pdisplayX11 = pdisplay;
//
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock d(pdisplay);
//
//      g_atomKickIdle = m_pdisplay->intern_atom("__WM_KICKIDLE", False);
//
//      g_windowX11Client = XCreateSimpleWindow(pdisplay, DefaultRootWindow(pdisplay), 10, 10, 10, 10, 0, 0, 0);
//
//      XSelectInput(pdisplay, g_windowX11Client, StructureNotifyMask);
//
//      g_oswindowDesktop = oswindow_get(pdisplay, DefaultRootWindow(pdisplay));
//
//      g_oswindowDesktop->m_pimpl = nullptr;
//
//      XSelectInput(pdisplay, g_oswindowDesktop->window(), StructureNotifyMask | PropertyChangeMask);
//
//   }
//
//   g_idle_add(x11_source_func, pdisplaydata);
//
//}




   void windowing::windowing_post_quit()
   {

      m_bFinishX11Thread = true;

      m_bInitX11Thread = false;

   }


//osdisplay_data * x11_main_display();



   bool windowing::x11_on_event(XEvent *pevent)
   {

      if (!m_pdisplay)
      {

         return false;

      }

      auto pdisplay = m_pdisplay->Display();

      if (pdisplay == nullptr)
      {

         return false;

      }

      XGenericEventCookie *cookie;


#ifdef WITH_XI


      if (m_pobjectaExtendedEventListener)
      {

         cookie = &pevent->xcookie;

      }
      else
      {

         cookie = nullptr;

      }

      // WITH_XI

#else

      // !WITH_XI

      cookie = nullptr;

#endif

//      if (!__x11_hook_process_event(pevent, cookie))
      {

#ifdef WITH_XI

         if (!x11_process_event(pevent, cookie))

#else

         if (!x11_process_event(pdisplay, pevent))

#endif
         {

            return false;

         }


      }

      return true;

   }



//catch(...)
//{
//
//}
//
//return true;
//
//}


   void x11_add_gdk_filter();




//gboolean x11_source_func(gpointer)
//{

// return false;

//}

   bool windowing::x11_message_handler(XEvent *pevent)
   {

      Display *pdisplay = m_pdisplay->Display();

      if (pdisplay == nullptr)
      {

         return false;

      }

      try
      {

         synchronous_lock synchronouslock(user_synchronization());

         display_lock displaylock(m_pdisplay->Display());

         try
         {

            XEvent &e = *pevent;

//#if !defined(RASPBIAN)

            XGenericEventCookie * pcookie;

//#endif

#ifdef WITH_XI

            if(m_pobjectaExtendedEventListener)
            {

               pcookie = &e.xcookie;

            }
            else
            {

               pcookie = nullptr;

            }

#endif

            //if (!__x11_hook_process_event(&e, cookie))
            {

#ifdef WITH_XI

               if(!x11_process_event(&e, pcookie))

#else

               if (!x11_process_event(m_pdisplay->Display(), pevent))

#endif
               {


               }


            }

         }
         catch (...)
         {

         }

      }
      catch (...)
      {

      }

      while (!m_bFinishX11Thread)
      {

         try
         {

            if (!x11_runnable_step())
            {

               break;

            }

         }
         catch (...)
         {

         }

      }

      if (m_bFinishX11Thread)
      {

#ifdef WITH_XI

         m_pobjectaExtendedEventListener.release();

#endif

         output_debug_string("x11_thread end thread");

         return false;

      }

      return true;

   }


   bool windowing::x11_message_loop()
   {

      while(x11_message_loop_step())
      {

      }

      return true;

   }


//gboolean x11_source_func(gpointer)
   bool windowing::x11_message_loop_step()
   {

//   osdisplay_data * pdisplaydata = (osdisplay_data *) x11_main_display();




//   if(!g_bInitX11Thread)
//   {
//
//      g_bInitX11Thread = true;
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock d(pdisplay);
//
//      g_atomKickIdle = m_pdisplay->intern_atom("__WM_KICKIDLE", False);
//
//      g_windowX11Client = XCreateSimpleWindow(pdisplay, DefaultRootWindow(pdisplay), 10, 10, 10, 10, 0, 0, 0);
//
//      XSelectInput(pdisplay, g_windowX11Client, StructureNotifyMask);
//
//      g_oswindowDesktop = oswindow_get(pdisplay, DefaultRootWindow(pdisplay));
//
//      g_oswindowDesktop->m_pimpl = nullptr;
//
//      XSelectInput(pdisplay, g_oswindowDesktop->window(), StructureNotifyMask | PropertyChangeMask);
//
//   }


      try
      {

         synchronous_lock synchronouslock(user_synchronization());

         display_lock displayLock(m_pdisplay->Display());

         Display *pdisplay = m_pdisplay->Display();

         if (pdisplay == nullptr)
         {

            return true;

         }

         if(!m_bRootSelectInput)
         {

            m_bRootSelectInput = true;

            auto windowRoot = DefaultRootWindow( pdisplay );

            XSelectInput( pdisplay, windowRoot, PropertyChangeMask );

         }

         while (XPending(pdisplay) && !m_bFinishX11Thread)
         {

            try
            {

               XEvent e = {};

               XGenericEventCookie * pcookie;

#ifdef WITH_XI

               if(m_pobjectaExtendedEventListener)
               {

                  pcookie = &e.xcookie;

               }
               else
               {

                  pcookie = nullptr;

               }

#endif

               XNextEvent(pdisplay, &e);

               if(!m_pdisplay->m_px11display->x11_event(&e))
               {

#ifdef WITH_XI

                  if(!x11_process_event(&e, pcookie))

#else

                  if (!x11_process_event(m_pdisplay->Display(), &e))

#endif
                  {

                     //XPutBackEvent(pdisplay, &e);

                     //break;

                  }


               }

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      while (!m_bFinishX11Thread)
      {

         try
         {

            if (!x11_runnable_step())
            {

               break;

            }

         }
         catch (...)
         {

         }

      }

      if (m_bFinishX11Thread)
      {

#ifdef WITH_XI

         m_pobjectaExtendedEventListener.release();

#endif

         output_debug_string("x11_thread end thread");

         return false;

      }

      return true;

   }


//#ifdef display_lock_LOCK_LOG
//
//extern bool b_prevent_display_lock_lock_log;
//
//#endif
//

//thread_pointer < XComposeStatus > t_pcomposestatus;
//thread_int_ptr < XIM > t_xim;
//thread_int_ptr < iptr > t_iXim;


//        XGenericEventCookie *cookie = (XGenericEventCookie*)&ev.xcookie;
//        XNextEvent(display, (XEvent*)&ev);
//
//        if (XGetEventData(display, cookie) &&
//            cookie->type == GenericEvent) //&&            cookie->extension == xi_opcode)
//        {
//            printf("EVENT type %d (%s)\n", cookie->evtype, type_to_name(cookie->evtype));
//            switch (cookie->evtype)
//            {
//                case XI_DeviceChanged:
//                    //print_devicechangedevent(display, cookie->data);
//                    break;
//                case XI_HierarchyChanged:
//                    //print_hierarchychangedevent(cookie->data);
//                    break;
//                case XI_RawKeyPress:
//                printf("RawKeyPress");
//                break;
//                case XI_RawKeyRelease:
//                printf("RawKeyRelease");
//                break;
//                case XI_RawButtonPress:
//                printf("RawButtonPress");
//                break;
//                case XI_RawButtonRelease:
//                printf("RawButtonRelease");
//                break;
//                case XI_RawMotion:
//                case XI_RawTouchBegin:
//                case XI_RawTouchUpdate:
//                case XI_RawTouchEnd:
//                    //print_rawevent(cookie->data);
//                    break;
//                case XI_Enter:
//                case XI_Leave:
//                case XI_FocusIn:
//                case XI_FocusOut:
//                    //print_enterleave(cookie->data);
//                    break;
//                case XI_PropertyEvent:
//                    //print_propertyevent(display, cookie->data);
//                    break;
//                default:
//                    //print_deviceevent(cookie->data);
//                    break;
//            }
//        }
//
//        XFreeEventData(display, cookie);
//    }
//
//    XDestroyWindow(display, win);
//
//
//    x11_


#ifdef WITH_XI
   bool windowing::x11_process_event(XEvent * pevent, XGenericEventCookie *cookie)
#else
   bool windowing::x11_process_event(XEvent *pevent)
#endif
   {

      XEvent &e = *pevent;

      MESSAGE msg;

      zero(msg);

      bool bRet = false;

#ifdef display_lock_LOCK_LOG

      b_prevent_display_lock_lock_log = false;

#endif

#ifdef WITH_XI

      if(cookie)
      {

         bool bProcessed = false;

         if (XGetEventData(m_pdisplay->Display(), cookie) && cookie->type == GenericEvent &&  cookie->extension == m_xi_opcode)
         {

            if(m_pobjectaExtendedEventListener && m_pobjectaExtendedEventListener->get_count() > 0)
            {

               enum_message emessage = e_message_null;

               auto prawevent = (XIRawEvent*)cookie->data;

               auto psystem = acmesystem()->m_papexsystem;

               // detail:
               // 1 - left button
               // 2 - middle button
               // 3 - right button
               // 4 - wheel down(orup)
               // 5 - wheel up(ordown)

               auto detail = prawevent->detail;

               switch (cookie->evtype)
               {

                  case XI_RawKeyPress:
                     emessage = e_message_key_down;
                     break;
                  case XI_RawKeyRelease:
                     emessage = e_message_key_up;
                     break;
                  case XI_RawButtonPress:
                  {
                     if(detail == 1)
                     {
                        emessage = e_message_left_button_down;
                     }
                     else if(detail == 2)
                     {
                        emessage = e_message_middle_button_down;

                     }
                     else if(detail == 3)
                     {
                        emessage = e_message_right_button_down;
                     }
                     //eid = detail == 5 || detail == 4 ? id_none : id_raw_buttondown;

                  }
                     break;
                  case XI_RawButtonRelease:
//                     eid = detail == 5 || detail == 4 ? id_none : id_raw_buttonup;

if(detail == 1)
{
   emessage = e_message_left_button_up;
}
else if(detail == 2)
{
   emessage = e_message_middle_button_up;

}
else if(detail == 3)
{
   emessage = e_message_right_button_up;
}

                     break;

               }

               output_debug_string("\ndetail:" + ::as_string(prawevent->detail));


               if(emessage != e_message_null)
               {

                  ::i64 iWparam = 'a';

                  ::i64 iLparam = XK_a;

                  if (emessage == e_message_key_down || emessage == e_message_key_up)
                  {

                     if(is_return_key((XIRawEvent*)cookie->data))
                     {

                        iWparam = '\n';

                        iLparam = XK_Return;

                     }
                     else if(is_space_key((XIRawEvent*)cookie->data))
                     {

                        iWparam = ' ';

                        iLparam = XK_space;

                     }

                     //ptopic->payload("return") = is_return_key(pgeevent);

                     //ptopic->payload("space") = is_space_key(pgeevent);

                  }

                  //::topic::context context;

                  for (auto & p : *m_pobjectaExtendedEventListener)
                  {

                     p->call(emessage, iWparam, iLparam);

                     //p->on_subject(ptopic, &context);

                  }

//                  if(emessage != e_message_null)
//               {
////                  auto ptopic = psystem->topic(eid);
//
//  //                ::topic::context context;
//
//                  int iKey = XK_A;
//
//                  if(is_return_key((XIRawEvent*)cookie->data))
//                  {
//
//                     iKey = XK_Return;
//
//                  }
//                  else if(is_space_key((XIRawEvent*)cookie->data))
//                  {
//
//                     iKey = XK_space;
//
//                  }
//
//
////                  ptopic->payload("return") = is_return_key(prawevent);
////
////                  ptopic->payload("space") = is_space_key(prawevent);
//
//                  //::topic::context context;
//
////                  for(auto & p : *m_pobjectaExtendedEventListener)
////                  {
////
////                     p->on_subject(ptopic, &context);
////
////                  }
//
//
//                  for(auto & p : *m_pobjectaExtendedEventListener)
//                  {
//
//                     p->call(emessage, iKey);
//
//                  }

               }

               bProcessed = true;

            }

         }

         XFreeEventData(m_pdisplay->Display(), cookie);

         if(bProcessed)
         {

            return true;

         }

      }

#endif

      msg.time = 0;

      auto oswindow = m_pdisplay->_window(e.xany.window);

//      if (oswindow == nullptr)
//      {
//
//         return false;
//
//      }

      msg.oswindow = oswindow;

      if (e.xany.type == ClientMessage && e.xany.window == g_windowX11Client
          && e.xclient.message_type == g_atomKickIdle)
      {

         output_debug_string("\nkick idle received\n");

         return true;

      }

      switch (e.type)
      {
         case LeaveNotify:
         {

            if(msg.oswindow)
            {

               ::minimum(m_pointCursor.x);

               ::minimum(m_pointCursor.y);

//            if(e.xcrossing.mode == NotifyUngrab)
//            {
//
//  //             MESSAGE msgCaptureChanged;
//
////               msgCaptureChanged.oswindow = m_pwindowCapture;
//               msg.m_atom = e_message_capture_changed;
//               msg.wParam = 0;
//               msg.lParam = (lparam) (oswindow) (msg.oswindow == m_pwindowCapture ? nullptr : m_pwindowCapture.m_p);
//               msg.time = e.xcrossing.time;
//
//               post_ui_message(msg);
//
//            }

               msg.m_atom = e_message_mouse_leave;
               msg.wParam = 0;
               msg.lParam = 0;
               msg.time = e.xcrossing.time;

               post_ui_message(msg);

            }

         }
         break;
         case EnterNotify:
         {



            //::minimum(m_pointCursor.x);

            //::minimum(m_pointCursor.y);

         }
            break;
         case MotionNotify:
         {

            if(msg.oswindow)
            {

               m_pointCursor.x = e.xmotion.x_root;

               m_pointCursor.y = e.xmotion.y_root;

               //g_pointX11Cursor.x = e.xmotion.x_root;

               //g_pointX11Cursor.y = e.xmotion.y_root;

               if (msg.oswindow != nullptr && msg.oswindow->m_puserinteractionimpl != nullptr)
               {

                  ((::windowing_x11::window *) msg.oswindow->m_pWindow4)->m_pointCursor = m_pointCursor;

                  bool bOk = true;

                  ::pointer < ::user::interaction > pinteraction = msg.oswindow->m_puserinteractionimpl->m_puserinteraction;

                  if (pinteraction.is_set())
                  {

                     if (pinteraction->m_timeMouseMove.elapsed() < pinteraction->m_timeMouseMoveIgnore)
                     {

                        bOk = false;

                     }

                     if (bOk)
                     {

                        pinteraction->m_timeMouseMove.Now();

                        pinteraction->m_pointMouseMove.x = e.xmotion.x_root;

                        pinteraction->m_pointMouseMove.y = e.xmotion.y_root;

                        if (false)
                        {

                           if (pinteraction->m_timeMouseMovePeriod > 0_s)
                           {

                              ::size_i32 sizeDistance(
                                 (pinteraction->m_pointMouseMoveSkip.x - pinteraction->m_pointMouseMove.x),
                                 (pinteraction->m_pointMouseMoveSkip.y - pinteraction->m_pointMouseMove.y));

                              if (
                                 !pinteraction->m_timeMouseMoveSkip.timeout(pinteraction->m_timeMouseMovePeriod)
                                 && sizeDistance.cx * sizeDistance.cx + sizeDistance.cy * sizeDistance.cy <
                                    pinteraction->m_iMouseMoveSkipSquareDistance)
                              {

                                 pinteraction->m_iMouseMoveSkipCount++;

                                 pinteraction->m_bMouseMovePending = true;

                                 if (pinteraction->m_iMouseMoveSkipCount == 2)
                                 {

                                    //output_debug_string("\nmmv>skip 2!");

                                 }
                                 else if (pinteraction->m_iMouseMoveSkipCount == 5)
                                 {

                                    //output_debug_string("\nmmv>Skip 5!!!");

                                 }
                                 else if (pinteraction->m_iMouseMoveSkipCount == 10)
                                 {

                                    //output_debug_string("\nmmv>SKIP 10 !!!!!!!!!");

                                 }

                                 return true;

                              }

                              pinteraction->m_iMouseMoveSkipCount = 0;

                              pinteraction->m_pointMouseMoveSkip = pinteraction->m_pointMouseMove;

                           }

                        }

                     }

                  }

                  if (!bOk)
                  {

                     return true;

                  }

               }

               wparam wparam(0);

               if (e.xmotion.state & Button1Mask)
               {

                  wparam |= ::user::e_mouse_middle_button;

               }

               msg.m_atom = e_message_mouse_move;
               msg.wParam = wparam;
               msg.lParam = __MAKE_LONG(e.xmotion.x_root, e.xmotion.y_root);
               msg.time = e.xmotion.time;

               post_ui_message(msg);

            }

         }
         break;
         case Expose:
         {

            if (e.xexpose.count == 0)
            {

               auto oswindow = msg.oswindow;

               if(oswindow)
               {

                  auto pimpl = oswindow->m_puserinteractionimpl;

                  if(pimpl)
                  {

                     auto puserinteraction = pimpl->m_puserinteraction;

                     if(puserinteraction)
                     {

                        if (puserinteraction->m_ewindowflag & ::e_window_flag_arbitrary_positioning)
                        {

                           pimpl->_001UpdateScreen();

                        }
                        else
                        {

                           msg.m_atom = e_message_paint;
                           msg.lParam = 0;
                           msg.wParam = 0;

                           post_ui_message(msg);

                        }

                     }

                  }

               }

               //msg.oswindow->m_pimpl->_001UpdateScreen();

               //::pointer<::user::interaction>pinteraction = msg.oswindow->m_pimpl->m_puserinteraction;

               //pinteraction->set_need_redraw();

               //pinteraction->post_redraw();

            }

         }
         break;
         case PropertyNotify:
         {

            if (m_pdisplay->m_atomWmState == None)
            {

               m_pdisplay->m_atomWmState = m_pdisplay->intern_atom("WM_STATE", false);

            }

            {

               if (e.xany.window == DefaultRootWindow(m_pdisplay->Display()))
               {

                  Atom atom = m_pdisplay->intern_atom("_NET_ACTIVE_WINDOW", False);

                  if (atom == e.xproperty.atom)
                  {

                     auto pwindowActiveOld = m_pdisplay->m_pwindowActive;

                     auto pwindowActiveNew = m_pdisplay->_get_active_window(nullptr);

                     if(pwindowActiveNew != pwindowActiveOld)
                     {

                        m_pdisplay->m_pwindowActive = pwindowActiveNew;

                        if(::is_set(pwindowActiveNew))
                        {

                           auto pimplNew = pwindowActiveNew->m_puserinteractionimpl;

                           if(::is_set(pimplNew))
                           {

                              auto puserinteractionNew = pimplNew->m_puserinteraction;

                              if(::is_set(puserinteractionNew))
                              {

                                 puserinteractionNew->set_need_redraw();

                                 puserinteractionNew->post_redraw();

                              }

                           }

                        }

                        if(::is_set(pwindowActiveOld))
                        {

                           auto pimplOld = pwindowActiveOld->m_puserinteractionimpl;

                           if(::is_set(pimplOld))
                           {

                              auto puserinteractionOld = pimplOld->m_puserinteraction;

                              if(::is_set(puserinteractionOld))
                              {

                                 puserinteractionOld->set_need_redraw();

                                 puserinteractionOld->post_redraw();

                              }

                           }

                        }

                     }

                  }

               }

            }

            msg.time = e.xproperty.time;

            if (msg.oswindow != nullptr && msg.oswindow->m_puserinteractionimpl != nullptr)
            {

               int iIconic = -1;

               if (e.xproperty.atom == m_pdisplay->m_atomWmState)
               {

                  iIconic = msg.oswindow->is_iconic() ? 1 : 0;

               }

               ::user::interaction *pinteraction = msg.oswindow->m_puserinteractionimpl->m_puserinteraction;

               if (pinteraction != nullptr)
               {

                  auto pimpl = pinteraction->m_pprimitiveimpl;

                  bool bHandled = false;

                  if (pimpl != nullptr)
                  {

                     if (iIconic >= 0)
                     {

                        if (iIconic == 0)
                        {

                           if (pinteraction->const_layout().design().display() == ::e_display_iconic)
                           {

                              //file_put_contents("/home/camilo/xxx.txt", "");

                              // 1111111111111111111111111111111111111111111

                              //pinteraction->hide();

                              pinteraction->fork([=]()
                                                 {

                                                    auto edisplayPrevious = pinteraction->window_previous_display();

                                                    if (edisplayPrevious == ::e_display_iconic)
                                                    {

                                                       pinteraction->_001OnDeiconify(::e_display_restored);

                                                    }
                                                    else
                                                    {

                                                       pinteraction->_001OnDeiconify(edisplayPrevious);

                                                    }

                                                 });

                              bHandled = true;

                           }
                           else if (pinteraction->const_layout().sketch().display() == ::e_display_full_screen
                                    && pinteraction->const_layout().design().display() != ::e_display_full_screen)
                           {

                              pinteraction->display(::e_display_full_screen);

                           }

                        }
                        else
                        {

                           if (pinteraction->const_layout().design().display() != ::e_display_iconic
                               && pinteraction->const_layout().design().display() != ::e_display_none)
                           {

                              pinteraction->display(::e_display_iconic);

                           }

                        }

                     }

                  }

               }

            }

         }
         break;
         case MapNotify:
         {

            if(msg.oswindow)
            {

               msg.m_atom = e_message_show_window;
               msg.wParam = 1;
               msg.lParam = 0;

               post_ui_message(msg);

            }

         }
         break;
         case UnmapNotify:
         {

            if(msg.oswindow)
            {

               msg.m_atom = e_message_show_window;
               msg.wParam = 0;
               msg.lParam = 0;

               post_ui_message(msg);

            }

         }
         break;
         case ConfigureNotify:
         {

            ::user::primitive_impl *pimpl = msg.oswindow ? msg.oswindow->m_puserinteractionimpl : nullptr;

            if (pimpl != nullptr)
            {

               ::user::interaction *pinteraction = pimpl->m_puserinteraction;

               if (pinteraction != nullptr)
               {

                  if (pinteraction->const_layout().design().display() == ::e_display_iconic && !msg.oswindow->is_iconic())
                  {

//               ::enum_display edisplayPrevious = pinteraction->window_previous_display();
//
//               pinteraction->layout().sketch() = edisplayPrevious;
//
//               pinteraction->layout().design() = edisplayPrevious;
//
//               pinteraction->layout().output() = edisplayPrevious;
//
//               pinteraction->layout().window() = edisplayPrevious;
//
//               pinteraction->m_windowrect.m_edisplay = edisplayPrevious;

                     pinteraction->fork([=]()
                                        {

                                           auto edisplayPrevious = pinteraction->window_previous_display();

                                           if (edisplayPrevious == ::e_display_iconic)
                                           {

                                              pinteraction->_001OnDeiconify(::e_display_restored);

                                           }
                                           else
                                           {

                                              pinteraction->_001OnDeiconify(edisplayPrevious);

                                           }

                                        });

                  }

                  {

                     //XWindowAttributes attrs;

                     //XGetWindowAttributes(m_pdisplay->Display(), e.xconfigure.window, &attrs);

                     //_x11_defer_check_configuration(msg.oswindow);

                     ::point_i32 point(e.xconfigure.x, e.xconfigure.y);

                     ::size_i32 size(e.xconfigure.width, e.xconfigure.height);

                     //::point_i32 point(attrs.x, attrs.y);

                     //::size_i32 size(attrs.width, attrs.height);

                     auto pointWindow = pinteraction->screen_origin();

                     auto sizeWindow = pinteraction->const_layout().window().size();

                     // Robbers -> Smart -> Tough Law
                     // Kids -> Soft Law
                     // 5 year smart
                     // 80 year kids
                     // big companies are?
                     // small companies are?
                     // big companies moved by auto sustainability...
                     // No human is auto sustainable, it currently needs iPhone or something....
                     // so?
                     // art as vanity and not for auto sustainability...
                     // not just for six... six... six...
                     // because sometimes we want cake and flesh and raw fish and not carrots with bread and oreo...
                     // now I imagine: sick of eating flesh-free carrots and bread, and getting drunk with cheetos and oreo
                     // we should let the flesh and the cake for the doctors,
                     // lawyers, politicians, google collaborators, drug-makers,
                     // ill-makers, sue-makers, idea-makers, religious-people,
                     // that make memory_new ammendments to ammendment itself,
                     // people above-the-law... flesh save them...
                     // ... retired and poor, widow people, complaining of dead/gone people,
                     // must eat bird seed grains.... no redemption, only in paradise...
                     // slaves of THEIR their, given by the GODs, laws ...

                     // X11 "knows" window manager can redirect a request
                     // (evidence: override_redirect flag - but that when set leave you outside of much more things)
                     // Lets not fight this X11 "thing"
                     // Accept-"stall" "authocratic" "top-down" window manager set position and size.
                     // This means setting same size_i32 and position to all three sketch and window states.
                     // The buffer may need to be resized so don't mess with current design state.

                     bool bPositionFix = pointWindow != point;

#ifdef X11_PERMISSIVE_WITH_WINDOW_MANAGERS_THE_LAW_MAKERS_BECAUSE_YEAH_KNOW_WHAT_IS_BETTER_FOR_THE_USER_BUTT_DEV_STAKE_IS_MONEY_MONEY_MONEY_COMMODITY_THEY_ARE_BURNING_VALUE_AND_BURYING_MONEY_AND_TREASURES_BELOW_THE_DEAD_LAKE_OF_AVERAGING_BUT_GOD_WILL_SHAKE_THIS_FOR_LIFE

                     if(bPositionFix)
                     {

                        pinteraction->layout().sketch().origin() = point;

                        pinteraction->layout().window().origin() = point;

                        pinteraction->screen_origin() = point;

                        pinteraction->screen_origin() = point;

                        pinteraction->set_reposition(true);

                     }

#endif

                     bool bSizeFix = sizeWindow != size;

#ifdef X11_PERMISSIVE_WITH_WINDOW_MANAGERS_THE_LAW_MAKERS_BECAUSE_YEAH_KNOW_WHAT_IS_BETTER_FOR_THE_USER_BUTT_DEV_STAKE_IS_MONEY_MONEY_MONEY_COMMODITY_THEY_ARE_BURNING_VALUE_AND_BURYING_MONEY_AND_TREASURES_BELOW_THE_DEAD_LAKE_OF_AVERAGING_BUT_GOD_WILL_SHAKE_THIS_FOR_LIFE_FOR_AWESOME_FILE

                     if(bSizeFix)
                     {

                        pinteraction->layout().sketch().size() = size;

                        pinteraction->layout().window().size() = size;

                        pinteraction->set_need_layout();

                     }

#endif

                     if (bPositionFix)
                     {

                        msg.oswindow->m_point = point;

                        msg.m_atom = e_message_move;
                        msg.wParam = 0;
                        msg.lParam = point.lparam();

                        post_ui_message(msg);

                     }

                     if (bSizeFix)
                     {

                        msg.oswindow->m_size = size;

                        msg.m_atom = e_message_size;
                        msg.wParam = 0;
                        msg.lParam = size.lparam();

                        post_ui_message(msg);

                     }

                  }

               }

            }

            if (e.xconfigure.window == DefaultRootWindow(m_pdisplay->Display()))
            {

               auto psession = get_session()->m_papexsession;

               auto applicationa = psession->m_applicationa;

               try
               {

                  for (auto &papp : applicationa)
                  {

                     try
                     {

                        auto pauraapplication = papp->m_pauraapplication;

                        auto userinteractionaFrame = pauraapplication->m_puserinteractionaFrame->interactiona();

                        for (auto &puserinteractionFrame : userinteractionaFrame)
                        {

                           try
                           {

                              puserinteractionFrame->post_message(e_message_display_change);

                           }
                           catch (...)
                           {

                           }

                        }

                     }
                     catch (...)
                     {

                     }

                  }

               }
               catch (...)
               {

               }

            }

         }
            break;
         case ButtonPress:
         case ButtonRelease:
         {

            if(msg.oswindow)
            {

               bRet = true;

               msg.time = e.xbutton.time;

               int iDelta = 0;

               if (e.xbutton.type == ButtonPress)
               {

                  if (e.xbutton.button == Button1)
                  {

                     ::output_debug_string("ButtonPress::Button1\n");

                     msg.m_atom = e_message_left_button_down;

                  }
                  else if (e.xbutton.button == Button2)
                  {

                     msg.m_atom = e_message_middle_button_down;

                  }
                  else if (e.xbutton.button == Button3)
                  {

                     msg.m_atom = e_message_right_button_down;

                  }
                  else if (e.xbutton.button == Button4)
                  {

                     iDelta = 120;

                  }
                  else if (e.xbutton.button == Button5)
                  {

                     iDelta = -120;

                  }
                  else
                  {

                     bRet = false;

                  }

               }
               else if (e.xbutton.type == ButtonRelease)
               {

                  if (e.xbutton.button == Button1)
                  {

                     ::output_debug_string("ButtonRelease::Button1\n");

                     msg.m_atom = e_message_left_button_up;

                  }
                  else if (e.xbutton.button == Button2)
                  {

                     msg.m_atom = e_message_middle_button_up;

                  }
                  else if (e.xbutton.button == Button3)
                  {

                     msg.m_atom = e_message_right_button_up;

                  }
                  else
                  {

                     bRet = false;

                  }

               }
               else
               {

                  bRet = false;

               }

               int XRoot = e.xbutton.x_root;

               int YRoot = e.xbutton.y_root;

//      int l = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_point.x;
//      int t = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_point.y;
//      int w = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_size.cx;
//      int h = msg.oswindow->m_pimpl->m_puserinteraction->layout().sketch().m_size.cy;
//
//      ::rectangle_i32 r;
//
//      get_window_rect(msg.oswindow, &r);
//
//      int l1 = r.left;
//      int t1 = r.top;
//      int w1 = r.width();
//      int h1 = r.height();

               if(iDelta != 0)
               {

                  msg.m_atom = e_message_mouse_wheel;

                  msg.wParam = __MAKE_LONG(0, iDelta);

                  msg.lParam = __MAKE_LONG(e.xbutton.x_root, e.xbutton.y_root);

                  post_ui_message(msg);


               }
               else if (bRet)
               {

                  msg.wParam = 0;

                  msg.lParam = __MAKE_LONG(e.xbutton.x_root, e.xbutton.y_root);

                  post_ui_message(msg);

               }

            }

         }
            break;
         case KeyPress:
         case KeyRelease:
         {

            if(msg.oswindow)
            {

               msg.time = e.xkey.time;

               bRet = true;

               char buf[32];

               zero(buf);

               string strText;

               KeySym keysym = 0;

               if (e.xkey.type == KeyPress)
               {

                  msg.m_atom = e_message_key_down;

                  ::pointer<::windowing_x11::window>pwindow = msg.oswindow;

                  if (!pwindow->m_pximkeyboard)
                  {

                     pwindow->m_pximkeyboard = memory_new ::xim::keyboard(m_pdisplay->Display(), e.xkey.window);

                     pwindow->m_pximkeyboard->initialize(pwindow);

                  }

                  strText = pwindow->m_pximkeyboard->get_key_press_text(&e.xkey, &keysym);

                  //case XK_Escape:
//                dv_dpy->dontdraw = 1;
//                xv_pause=0;
//                XvStopVideo(dv_dpy->dpy, dv_dpy->port, dv_dpy->win);
//                XDestroyWindow(dv_dpy->dpy, dv_dpy->win);
//                break;
//
//            case XK_Q:
//            case XK_q:
//                xv_pause=0;
//                dv_dpy->dontdraw = (dv_dpy->dontdraw) ? 0:1;
//                break;
//
//            case XK_space:
//                xv_pause = (xv_pause)?0:1;
//                while(xv_pause) {
//                    dv_display_event(dv_dpy);
//                    usleep(10000_ms);
//                }
//
//            default:
//                break;
//            }
               }
               else if (e.xkey.type == KeyRelease)
               {

                  keysym = XkbKeycodeToKeysym(m_pdisplay->Display(), e.xkey.keycode, 0,
                                              e.xkey.state & ShiftMask ? 1 : 0);

                  msg.m_atom = e_message_key_up;

               }
               else
               {

                  bRet = false;

               }

               if (bRet)
               {

                  msg.wParam = e.xkey.keycode;

                  msg.lParam = keysym;

                  post_ui_message(msg);

               }

               if (strText.has_char() && !(e.xkey.state & ControlMask))
               {

                  auto pkey = __create_new<::message::key>();

                  pkey->set(oswindow, oswindow, e_message_text_composition, 0, 0);

                  pkey->m_strText = strText;

//               MESSAGE msgText(msg);
//
//               msgText.m_atom = e_message_text_composition;
//
//               msgText.wParam = 0;
//
//               string *pstringText = memory_new string(strText);
//
//               msgText.lParam = (lparam) (iptr) (string *) (pstringText);

                  printf("x11_process_message e_message_text_composition\n");

                  //post_ui_message(msgText);
                  post_ui_message(pkey);

               }

            }

         }
            break;

         case FocusIn:
         {

            ::output_debug_string("FocusIn\n");

            msg.m_atom = e_message_set_focus;

            auto oswindow = msg.oswindow;

            if (::is_set(oswindow))
            {

               m_pdisplay->m_pwindowKeyboardFocus = oswindow;

               auto pimpl = msg.oswindow->m_puserinteractionimpl;

                if (::is_set(pimpl))
                {

                    auto pinteraction = pimpl->m_puserinteraction;

                    if (::is_set(pinteraction))
                    {

                        msg.m_atom = e_message_set_focus;

                        pinteraction->m_ewindowflag |= ::e_window_flag_focus;

                        post_ui_message(msg);

                    }

                }

            }

               //msg.wParam = (WPARAM) oswindow_get(display(), e.xfocus.window);

//      Window wFocus = 0;
//
//      int revert_to_return = 0;
//
//      int iStatus = XGetInputFocus(display, &wFocus, &revert_to_return);
//
//      //if(iStatus == Success)
//      if(iStatus)
//      {
//
//         if(wFocus == e.xfocus.window)
//         {
//
//            output_debug_string("A\n");
//
//         }
//         else
//         {
//
//            output_debug_string("B " + as_string(wFocus));
//
//            g_windowFocus = wFocus;
//
//         }
//
//         if(wFocus == g_windowFocus)
//         {
//
//            output_debug_string("C\n");
//
//         }
//         else
//         {
//
//            output_debug_string("D " + as_string(wFocus));
//
//            g_windowFocus = wFocus;
//
//         }
//
//      }
//
//      synchronous_lock synchronouslock(pdata->m_pmutexInput);
//
//      pdata->m_messsageaInput.add(msg);

        }

        break;
         case FocusOut:
         {

            ::output_debug_string("FocusOut\n");

            auto oswindow = msg.oswindow;

            if (::is_set(oswindow))
            {

               if(m_pdisplay->m_pwindowKeyboardFocus == oswindow)
               {

                  m_pdisplay->m_pwindowKeyboardFocus = nullptr;

               }

               auto pimpl = msg.oswindow->m_puserinteractionimpl;

               if (::is_set(pimpl))
               {

                  auto pinteraction = pimpl->m_puserinteraction;

                  if (::is_set(pinteraction))
                  {

                     msg.m_atom = e_message_kill_focus;

                     pinteraction->m_ewindowflag -= ::e_window_flag_focus;

                     Window wFocus = 0;

                     int revert_to_return = 0;

                     XGetInputFocus(m_pdisplay->Display(), &wFocus, &revert_to_return);

                     msg.wParam = (wparam) (iptr) m_pdisplay->_window(wFocus);

                     post_ui_message(msg);

                  }

               }

            }

         }
            break;

         case DestroyNotify:
         {

            if(msg.oswindow)
            {
               msg.oswindow = m_pdisplay->_window(e.xdestroywindow.window);
               msg.m_atom = e_message_destroy;

               post_ui_message(msg);

            }

            return true;

         }
         break;
         default:
         {
            output_debug_string("axis_x11 case default:");
         }
      }

      // processed

      return true;

   }


//namespace user
//{
//
//
//   lresult interaction_child::send_x11_event(void * pvoidEvent)
//   {
//
//      XEvent * pevent = (XEvent *) pvoidEvent;
//
//      ::pointer<::user::message>spbase;
//
//      spbase = Session->get_message_base(pvoidEvent, m_puserinteraction);
//
//      try
//      {
//
//         ::pointer<::user::interaction>pinteraction = m_puserinteraction;
//
//         while(pinteraction != nullptr && pinteraction->get_parent() != nullptr)
//         {
//
//            try
//            {
//
//               pinteraction->pre_translate_message(spbase);
//
//            }
//            catch(...)
//            {
//
//               break;
//
//            }
//
//            if(spbase->m_bRet)
//            {
//
//               return spbase->m_lresult;
//
//            }
//
//            try
//            {
//
//               pinteraction = pinteraction->get_parent();
//
//            }
//            catch(...)
//            {
//
//               break;
//
//            }
//
//         }
//
//      }
//      catch(...)
//      {
//
//      }
//
//      message_handler(spbase);
//
//      return spbase->m_lresult;
//
//   }
//
//
//} // namespace user


////namespace aura
////{
////
////
//::pointer<::user::message>channel::get_message_base(void * pevent,::user::interaction * pwnd)
//{
//
//   throw ::exception(todo());
//
//   return nullptr;
//
//}
////
////
////} // namespace aura
////

//int_bool set_window_position(oswindow hwnd, oswindow hwndInsertAfter, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags)
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   return hwnd->set_window_position(hwndInsertAfter, x, y, cx, cy, nFlags);
//
//}





//int_bool get_window_rect(oswindow hwnd, RECTANGLE_I32 * prectangle)
//{
//
//   synchronous_lock synchronouslock(user_synchronization());
//
//   display_lock d(hwnd->display());
//
//   if(d.is_null())
//   {
//
//      windowing_output_debug_string("\n::get_window_rect 1.1");
//
//      return false;
//
//   }
//
//   return x11_get_window_rect(d, hwnd->window(), prectangle);
//
//}


//
//int_bool ca2_GetClientRect(oswindow window, RECTANGLE_I32 * prectangle)
//{
//
//   synchronous_lock synchronouslock(window->m_pimpl->m_puserinteraction->synchronization());
//
//   window->m_pimpl->m_puserinteraction->get_window_rect(prectangle);
//
//   offset_rect(prectangle, -prectangle->left, -prectangle->top);
//
//   return true;
//
//}




//
//int_bool GetCursorPos(POINT_I32 * ppointCursor)
//{
//
//   x11_sync([&]()
//            {
//
//               synchronous_lock synchronouslock(user_synchronization());
//
//               x11_get_cursor_pos(ppointCursor);
//
//            });
//
//   return true;
//
//}
//

//::user::interaction * get_system_window_interaction(::os_system_window * psystemwindow)
//{
//
//   return nullptr;
//
//}

//
//void wm_full_screen(oswindow w, const ::rectangle_i32 & rectangle)
//
//{
//
//   w->full_screen(rectangle);
//
//
//}


//
//CLASS_DECL_AURA void defer_dock_application(int_bool bDock)
//{
//
//   __UNREFERENCED_PARAMETER(bDock);
//
//}

//
//void sn_start_context();
//
//void acme_defer_os_init_windowing();

   int xlib_error_handler(Display *d, XErrorEvent *e)
   {

      if (e->request_code == 12)
      {

         if (e->error_code == BadValue)
         {

         }

      }

      char sz[1024];

      XGetErrorText(d, e->error_code, sz, sizeof(sz));

      fputs(sz, stderr);

      abort();

   }
//
//
//i64 oswindow_id(oswindow w)
//{
//
//   return w->window();
//
//}
//
//


//   void windowing::_initialize_windowing()
//   {
//
//      //acme_defer_os_init_windowing();
//
//      //g_pmutexX11Runnable = memory_new ::pointer < ::mutex >();
//
//      //g_prunnableptrlX11 = memory_new list<::pointer<::matter >>);
//
////      g_pmutexX11Sync = memory_new ::pointer < ::mutex >();
//
////      g_peventX11Sync = memory_new manual_reset_event();
//
//      //oswindow_data::s_pdataptra = memory_new oswindow_dataptra;
//
//      //oswindow_data::s_pmutex = memory_new ::pointer < ::mutex >;
//
//      //osdisplay_data::s_pdataptra = memory_new osdisplay_dataptra;
//
//      //osdisplay_data::s_pmutex = memory_new ::pointer < ::mutex >;
//
//      //return true;
//
//   }


   void windowing::terminate_windowing()
   {

      //::acme::del(osdisplay_data::s_pmutex);

      //::acme::del(osdisplay_data::s_pdataptra);

      //::acme::del(oswindow_data::s_pmutex);

      //::acme::del(oswindow_data::s_pdataptra);

//      {
//
//         synchronous_lock synchronouslock(g_pmutexX11Runnable);
//
//         ::acme::del(g_prunnableptrlX11);
//
//      }

      //::acme::del(g_pmutexX11Runnable);

//      ::acme::del(g_peventX11Sync);

//      ::acme::del(g_pmutexX11Sync);

      //return false;

   }



//
//#ifdef RASPBIAN
//
//
//HCURSOR imaging::CreateAlphaCursor(oswindow window, const ::image * pimage, int xHotSpot, int yHotSpot)
//{
//
//   return hcursor_null;
//
//}
//
//
//#else





//#endif // RASPBIAN


//
//int_bool WINAPI SetWindowPos(oswindow hWnd,oswindow hWndInsertAfter,i32 X,i32 Y,i32 cx,i32 cy,::u32 uFlags)
//{
//
//   return hWnd->set_window_position(hWndInsertAfter, X, Y, cx, cy, uFlags);
//
//}






   void x11_async_runnable(::matter *prunnable)
   {

//      {
//
//         synchronous_lock synchronouslock(g_pmutexX11Runnable);
//
//         g_prunnableptrlX11->add_tail(prunnable);
//
//      }

      x11_kick_idle();

   }


   int g_iX11Ref = 0;

   void x11_term();

   void x11_start();

   //void ui_post_quit();

//   void defer_term_ui()
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      g_iX11Ref--;
//
//      if (g_iX11Ref <= 0)
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


//void x11_thread(osdisplay_data * pdisplaydata);


   ::pointer<::thread>g_pthreadXlib;


   itask_t g_itaskXlib;


   itask_t x11_get_itask()
   {

      return g_itaskXlib;

   }


   CLASS_DECL_ACME ::thread *x11_get_thread()
   {

      return g_pthreadXlib;

   }

//
//osdisplay_data * x11_main_display();
//


   void windowing::post_ui_message(const MESSAGE &message)
   {

      oswindow oswindow = message.oswindow;

      ASSERT(oswindow != nullptr);

      auto pimpl = oswindow->m_puserinteractionimpl;

      if(::is_null(pimpl))
      {

         throw ::exception(error_null_pointer);

      }

      auto pinteraction = pimpl->m_puserinteraction;

      if(::is_null(pinteraction))
      {

         return;
         //throw ::exception(error_null_pointer);

      }

      ::thread *pthread = nullptr;

      if (::is_set(pinteraction))
      {

         pthread = pinteraction->m_pthreadUserInteraction;

      }

      if (::is_null(pthread))
      {

         throw ::exception(error_null_pointer);

      }

      auto pmessagequeue = pthread->m_pmessagequeue.get();

      if (pmessagequeue == nullptr)
      {

         if (message.m_atom == e_message_quit)
         {

            return;

         }

         pmessagequeue = pthread->get_message_queue();

      }

      if (pmessagequeue == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock ml(pmessagequeue->synchronization());

      pmessagequeue->m_messagea.add(message);

      if (message.m_atom == e_message_quit)
      {

         output_debug_string("e_message_quit thread");

      }
      else if (message.m_atom == e_message_left_button_down)
      {

         output_debug_string("post_ui_message::e_message_left_button_down\n");

      }
      else if (message.m_atom == e_message_left_button_up)
      {

         output_debug_string("post_ui_message::e_message_left_button_up\n");

      }

      pmessagequeue->m_eventNewMessage.set_event();

      //return true;

   }


   void windowing::post_ui_message(::message::message * pmessage)
   {

      oswindow oswindow = pmessage->m_oswindow;

      ASSERT(oswindow != nullptr);

      auto pimpl = oswindow->m_puserinteractionimpl;

      if(::is_null(pimpl))
      {

         throw ::exception(error_null_pointer);

      }

      auto puserinteraction = pimpl->m_puserinteraction;

      if(::is_null(puserinteraction))
      {

         throw ::exception(error_null_pointer);

      }

      //auto result =
      //
      puserinteraction->post(pmessage);

      //return result;


//      ::thread *pthread = nullptr;
//
//      if (::is_set(pinteraction))
//      {
//
//         pthread = pinteraction->m_pthreadUserInteraction;
//
//      }
//
//      if (::is_null(pthread))
//      {
//
//         return false;
//
//      }
//
//      class ::message_queue *pmq = pthread->m_pmq;
//
//      if (pmq == nullptr)
//      {
//
//         if (message.m_atom == e_message_quit)
//         {
//
//            return false;
//
//         }
//
//         pmq = pthread->get_message_queue();
//
//      }
//
//      if (pmq == nullptr)
//      {
//
//         return false;
//
//      }
//
//      synchronous_lock ml(pmq->synchronization());
//
//      if (message.m_atom == e_message_quit)
//      {
//
//         output_debug_string("e_message_quit thread");
//
//      }
//
//      if (message.m_atom == e_message_left_button_down)
//      {
//
//         output_debug_string("post_ui_message::e_message_left_button_down\n");
//
//      }
//      else if (message.m_atom == e_message_left_button_up)
//      {
//
//         output_debug_string("post_ui_message::e_message_left_button_up\n");
//
//      }
//
//      pmq->m_messagea.add(message);
//
//      pmq->m_eventNewMessage.set_event();
//
//      return true;

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
//   x11_fork([oswindow]()
//            {
//
//               display_lock d(Display());
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


   void windowing::windowing_main()
   {

      x11_main();

   }


   void windowing::x11_main()
   {

      while (!m_bFinishX11Thread)
      {

         x11_message_loop_step();

      }

   }


//
//
//
//message_queue * get_message_queue(itask_t idthread, bool bCreate);
//
//
//void oswindow_set_active_window(oswindow oswindow);
//
//
//CLASS_DECL_AURA void update_application_session_cursor(void * pvoidApp, const point_i32 & pointCursor);
//
//
//
//
//int_bool _x11_get_cursor_pos(Display * d, POINT_I32 * ppointCursor);
//



//int get_best_ordered_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);
//int get_best_monitor(::user::interaction * pinteraction, int & l, int & t, int & cx, int & cy);

//extern SnLauncheeContext *g_psncontext;
//Display * Display();
//void wm_toolwindow(oswindow w, bool bToolWindow);
//void wm_state_hidden(oswindow w, bool bSet);
//void wm_state_hidden_raw(oswindow w, bool bSet);
//CLASS_DECL_AURA int_bool mq_remove_window_from_all_queues(oswindow oswindow);
//
//
//int_bool x11_get_cursor_pos(POINT_I32 * ppointCursor);
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
//void x11_thread(osdisplay_data * pdisplaydata);

//void __axis_x11_input_thread(osdisplay_data * pdisplaydata);




//
//osdisplay_data * x11_main_display();
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







} // namespace windowing_x11



const char *g_pszaNetWmState[] =
   {
      "_NET_WM_STATE_ABOVE",
      "_NET_WM_STATE_BELOW",
      "_NET_WM_STATE_HIDDEN",
      "_NET_WM_STATE_MAXIMIZED_HORZ",
      "_NET_WM_STATE_MAXIMIZED_VERT",
      "_NET_WM_STATE_FULLSCREEN",
      "_NET_WM_STATE_SKIP_TASKBAR",
      NULL
   };




//const char *net_wm_state_text(enum_net_wm_state estate)
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
//enum_net_wm_state net_wm_state(const char *pszText)
//{
//
//   if (::is_null(pszText))
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
//      if (!ansi_compare_ci(pszText, ppsz[i]))
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




//#define MAXSTR 1000

//unsigned char *x11_get_string_property(Display *display, Window window, char *property_name)
//{
//
//   unsigned char *prop;
//   Atom actual_type, filter_atom;
//   int actual_format, status;
//   unsigned long nitems, bytes_after;
//
//   filter_atom = XInternAtom(display, property_name, True);
//   status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
//                               &actual_type, &actual_format, &nitems, &bytes_after, &prop);
//   x11_check_status(status, window);
//   return prop;
//
//}
//
//
//unsigned long x11_get_long_property(Display *d, Window w, char *property_name)
//{
//
//   unsigned char *prop = x11_get_string_property(d, w, property_name);
//
//   unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);
//
//   return long_property;
//
//}


bool x11_get_client_rect(Display * pdisplay, Window window, RECTANGLE_I32 *prectangle)
{

   synchronous_lock synchronouslock(user_synchronization());

   XWindowAttributes attr;

   if (XGetWindowAttributes(pdisplay, window, &attr) == 0)
   {

      windowing_output_debug_string("\n::get_client_rect 1.2 (xgetwindowattributes failed");

      return false;

   }

   prectangle->left = 0;

   prectangle->top = 0;

   prectangle->right = prectangle->left + attr.width;

   prectangle->bottom = prectangle->top + attr.height;

   windowing_output_debug_string("\n::get_client_rect 2");

   return true;

}



string x11_get_name(Display * display, Window w)
{

   string str;

   char* name = NULL;
   int status = XFetchName(display, w, &name);
   if (status >= Success)
   {
      str =name;
   }
   XFree(name);
   return str;

}



bool x11_get_window_rect(Display * d, Window window, RECTANGLE_I32 * prectangle)
{

   XWindowAttributes attrs;

   if(!XGetWindowAttributes(d, window, &attrs))
   {

      windowing_output_debug_string("\n::x11_get_window_rect 1.1 (xgetwindowattributes failed)");

      return false;

   }

   int x = 0;

   int y = 0;

   int screen = XDefaultScreen((Display *) d);

   Window windowRoot = RootWindow((Display *) d, screen);

   Window child;

   XTranslateCoordinates( d, window, windowRoot, 0, 0, &x, &y, &child );

   prectangle->left      = x + attrs.x;

   prectangle->top       = y + attrs.y;

   prectangle->right     = x + attrs.x    + attrs.width;

   prectangle->bottom    = y + attrs.y    + attrs.height;



   windowing_output_debug_string("\n::x11_get_window_rect 2");

   return true;

}



::e_status initialize_x11()
{

   if (!XInitThreads())
   {

      return ::error_failed;

   }

   XSetErrorHandler(_c_XErrorHandler);

   //g_pmutexX11 = memory_new ::pointer < ::mutex >();

   return ::success;

}


::e_status g_estatusInitializeX11 = error_not_initialized;


::e_status defer_initialize_x11()
{

   if(g_estatusInitializeX11 == error_not_initialized)
   {

      g_estatusInitializeX11 = initialize_x11();

   }

   return g_estatusInitializeX11;

}


//mutex * user_synchronization()
//{
//
//   return g_pmutexX11;
//
//
//}



