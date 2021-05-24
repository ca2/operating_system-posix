//
// Created by camilo on 16/02/2021.
//
#include "platform-posix/windowing_x11/framework.h"
#include "aura/user/_user.h"
#include "aura/os/x11/_x11.h"
#include "acme/const/id.h"
#include "acme/const/message.h"
////#include "third/sn/sn.h"
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
#define new ACME_NEW
#include "aura/os/x11/_x11.h"
#include "acme/parallelization/message_queue.h"
#include "windowing_x11.h"
#include "acme/os/_user.h"


//bool x11_runnable_step();


//::mutex * g_pmutexX11Runnable = nullptr;
//list < __pointer(::matter) > * g_prunnableptrlX11 = nullptr;


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
//::mutex * g_pmutexX11Runnable = nullptr;
//list < __pointer(::matter) > * g_prunnableptrlX11 = nullptr;
//::mutex * g_pmutexX11Sync = nullptr;
//manual_reset_event * g_peventX11Sync = nullptr;
//__pointer(::matter) g_prunnableX11Sync;
Window g_windowX11Client = 0;



int_bool _x11_get_cursor_pos(Display * d, POINT_I32 * ppointCursor);


//extern ::mutex *g_pmutexX11Runnable;
//extern list<__pointer(::matter) > *g_prunnableptrlX11;
//extern ::mutex *g_pmutexX11Sync;
//extern manual_reset_event *g_peventX11Sync;
//extern __pointer(::matter) g_prunnableX11Sync;


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

#ifdef LINUX
i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);
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
//   ::oswindow_data::s_pdataptra->remove_at(iFind);
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
//   ::oswindow_data::s_pdataptra->remove_at(iFind);
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

   oswindow g_oswindowActive;


   oswindow get_active_window()
   {

      return g_oswindowActive;

   }


   void oswindow_set_active_window(oswindow oswindow)
   {

      if (g_oswindowActive)
      {

         try
         {

            if (g_oswindowActive->m_pimpl)
            {

               if (g_oswindowActive->m_pimpl->m_puserinteraction)
               {

                  g_oswindowActive->m_pimpl->m_puserinteraction->m_ewindowflag -= ::e_window_flag_active;

                  g_oswindowActive->m_pimpl->m_puserinteraction->post_message(e_message_activate, 0);

               }

            }

         }
         catch (...)
         {

         }

      }

      g_oswindowActive = oswindow;

      if (g_oswindowActive)
      {

         try
         {

            if (g_oswindowActive->m_pimpl)
            {

               if (g_oswindowActive->m_pimpl->m_puserinteraction)
               {

                  g_oswindowActive->m_pimpl->m_puserinteraction->m_ewindowflag += ::e_window_flag_active;

                  g_oswindowActive->m_pimpl->m_puserinteraction->post_message(e_message_activate, 1);

               }

            }

         }
         catch (...)
         {

         }

      }

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
//   synchronous_lock synchronouslock(user_mutex());
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
//                  synchronous_lock synchronouslock(user_mutex());
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
//                  ::rectangle_i32 rectTest;
//
//                  for (index i = 0; i < windowa.get_size(); i++)
//                  {
//
//                     string strItem = ::x11_get_name(Display(), windowa[i]);
//
//                     ::rectangle_i32 rectHigher;
//
//                     if (::is_set(pwindowx11Exclude) && windowa[i] == pwindowx11Exclude->Window())
//                     {
//
//                        continue;
//
//                     }
//
//                     if (::x11_get_window_rect(Display(), windowa[i], rectHigher))
//                     {
//
//                        ::rectangle_i32 rectHitTest;
//
//                        rectHitTest.set(rectHigher.origin(), ::size_i32());
//
//                        rectHitTest.inflate(iMargin + 1);
//
//                        if (rectHitTest.contains(pointHitTest))
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

//    synchronous_lock synchronouslock(user_mutex());

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

//    ::rectangle_i32 rectTest;

//    for(iFind++; iFind < windowa.get_size(); iFind++)
//    {

//       string strItem = x11_get_name(display, windowa[iFind]);

//       ::rectangle_i32 rectHigher;

//       if(x11_get_window_rect(display, windowa[iFind], rectHigher))
//       {

//          if(rectTest.intersect(rectHigher, rectangle))
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
permit persons to whom the Software is furnished to do so, subject to
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
//   synchronous_lock synchronouslock(user_mutex());
//
//   pgraphics->fill_rectangle(::rectangle_i32(*psize), rgb(84, 90, 80));
//
//   ::draw2d::brush_pointer pen(e_create_new);
//
//   pen->create_solid(0);
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
//   synchronous_lock synchronouslock(user_mutex());
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

      return oswindow->m_pimpl;

#endif

   }


//
//::e_status x11_hook::hook()
//{
//
//   synchronous_lock synchronouslock(user_mutex());
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
//   synchronous_lock synchronouslock(user_mutex());
//
//   g_x11hooka.remove(this);
//
//   return ::success;
//
//}




#if !defined(RASPBIAN)


   bool x11_process_event(Display *pdisplay, XEvent *pevent, XGenericEventCookie *cookie);


#else


   bool x11_process_event(osdisplay_data * pdisplaydata, XEvent & e);


#endif


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
//      synchronous_lock synchronouslock(user_mutex());
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

         synchronous_lock synchronouslock(user_mutex());

         display_lock displaylock(m_pdisplay->Display());

         try
         {

            XEvent &e = *pevent;

#if !defined(RASPBIAN)

            XGenericEventCookie *cookie;

#endif

#ifdef WITH_XI

            if(m_pobjectaExtendedEventListener)
            {

               cookie = &e.xcookie;

            }
            else
            {

               cookie = nullptr;

            }

#endif

            //if (!__x11_hook_process_event(&e, cookie))
            {

#ifdef WITH_XI

               if(!x11_process_event(&e, cookie))

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

//gboolean x11_source_func(gpointer)
   bool windowing::x11_message_loop_step()
   {

//   osdisplay_data * pdisplaydata = (osdisplay_data *) x11_main_display();




//   if(!g_bInitX11Thread)
//   {
//
//      g_bInitX11Thread = true;
//
//      synchronous_lock synchronouslock(user_mutex());
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

         synchronous_lock synchronouslock(user_mutex());

         display_lock displayLock(m_pdisplay->Display());

         Display *pdisplay = m_pdisplay->Display();

         if (pdisplay == nullptr)
         {

            return true;

         }

         while (XPending(pdisplay) && !m_bFinishX11Thread)
         {

            try
            {

               XEvent e = {};

#if !defined(RASPBIAN)

               XGenericEventCookie *cookie;

#endif

#ifdef WITH_XI

               if(m_pobjectaExtendedEventListener)
               {

                  cookie = &e.xcookie;

               }
               else
               {

                  cookie = nullptr;

               }

#endif

               XNextEvent(pdisplay, &e);

               //if (!__x11_hook_process_event(&e, cookie))
               {

#ifdef WITH_XI

                  if(!x11_process_event(&e, cookie))

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

      __zero(msg);

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

               e_id eid;

               switch (cookie->evtype)
               {

                  case XI_RawKeyPress:
                     eid = id_raw_keydown;
                     break;
                  case XI_RawKeyRelease:
                     eid = id_raw_keyup;
                     break;
                  case XI_RawButtonPress:
                     eid = id_raw_buttondown;
                     break;
                  case XI_RawButtonRelease:
                     eid = id_raw_buttonup;
                     break;

               }

               auto psystem = m_psystem->m_papexsystem;

               auto psubject = psystem->subject(eid);

               psubject->payload("return") = is_return_key((XIRawEvent*)cookie->data);

               psubject->payload("space") = is_space_key((XIRawEvent*)cookie->data);

               ::subject::context context;

               for(auto & p : *m_pobjectaExtendedEventListener)
               {

                  p->on_subject(psubject, &context);

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

      msg.oswindow = m_pdisplay->_window(e.xany.window);

      if (msg.oswindow == nullptr)
      {

         return false;

      }

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

            ::minimum(m_pointCursor.x);

            ::minimum(m_pointCursor.y);

//            if(e.xcrossing.mode == NotifyUngrab)
//            {
//
//  //             MESSAGE msgCaptureChanged;
//
////               msgCaptureChanged.oswindow = m_pwindowCapture;
//               msg.m_id = e_message_capture_changed;
//               msg.wParam = 0;
//               msg.lParam = (lparam) (oswindow) (msg.oswindow == m_pwindowCapture ? nullptr : m_pwindowCapture.m_p);
//               msg.time = e.xcrossing.time;
//
//               post_ui_message(msg);
//
//            }

            msg.m_id = e_message_mouse_leave;
            msg.wParam = 0;
            msg.lParam = 0;
            msg.time = e.xcrossing.time;

            post_ui_message(msg);

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

            m_pointCursor.x = e.xmotion.x_root;

            m_pointCursor.y = e.xmotion.y_root;

            //g_pointX11Cursor.x = e.xmotion.x_root;

            //g_pointX11Cursor.y = e.xmotion.y_root;

            if (msg.oswindow != nullptr && msg.oswindow->m_pimpl != nullptr)
            {

               bool bOk = true;

               __pointer(::user::interaction) pinteraction = msg.oswindow->m_pimpl->m_puserinteraction;

               if (pinteraction.is_set())
               {

                  if (pinteraction->m_millisMouseMove.elapsed() < pinteraction->m_millisMouseMoveIgnore)
                  {

                     bOk = false;

                  }

                  if (bOk)
                  {

                     pinteraction->m_millisMouseMove.Now();

                     pinteraction->m_pointMouseMove.x = e.xmotion.x_root;

                     pinteraction->m_pointMouseMove.y = e.xmotion.y_root;

                     if (false)
                     {

                        if (pinteraction->m_millisMouseMovePeriod > 0)
                        {

                           ::size_i32 sizeDistance(
                              (pinteraction->m_pointMouseMoveSkip.x - pinteraction->m_pointMouseMove.x),
                              (pinteraction->m_pointMouseMoveSkip.y - pinteraction->m_pointMouseMove.y));

                           if (!pinteraction->m_millisMouseMoveSkip.timeout(pinteraction->m_millisMouseMovePeriod)
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

               wparam |= MK_LBUTTON;

            }

            msg.m_id = e_message_mouse_move;
            msg.wParam = wparam;
            msg.lParam = MAKELONG(e.xmotion.x_root, e.xmotion.y_root);
            msg.time = e.xmotion.time;

            post_ui_message(msg);

         }
         break;
         case Expose:
         {

            if (e.xexpose.count == 0)
            {

               auto oswindow = msg.oswindow;

               if(oswindow)
               {

                  auto pimpl = oswindow->m_pimpl;

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

                           msg.m_id = e_message_paint;
                           msg.lParam = 0;
                           msg.wParam = 0;

                           post_ui_message(msg);

                        }

                     }

                  }

               }

               //msg.oswindow->m_pimpl->_001UpdateScreen();

               //__pointer(::user::interaction) pinteraction = msg.oswindow->m_pimpl->m_puserinteraction;

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

                     m_pdisplay->m_pwindowActive = m_pdisplay->_get_active_window(nullptr);

                  }

               }

            }

            msg.time = e.xproperty.time;

            if (msg.oswindow != nullptr && msg.oswindow->m_pimpl != nullptr)
            {

               int iIconic = -1;

               if (e.xproperty.atom == m_pdisplay->m_atomWmState)
               {

                  iIconic = msg.oswindow->is_iconic() ? 1 : 0;

               }

               ::user::interaction *pinteraction = msg.oswindow->m_pimpl->m_puserinteraction;

               if (pinteraction != nullptr)
               {

                  ::user::primitive *pimpl = pinteraction->m_pimpl;

                  bool bHandled = false;

                  if (pimpl != nullptr)
                  {

                     if (iIconic >= 0)
                     {

                        if (iIconic == 0)
                        {

                           if (pinteraction->layout().design().display() == ::e_display_iconic)
                           {

                              //file_put_contents("/home/camilo/xxx.txt", "");

                              // 1111111111111111111111111111111111111111111

                              //pinteraction->hide();

                              pinteraction->fork([=]()
                                                 {

                                                    auto edisplayPrevious = pinteraction->window_previous_display();

                                                    if (edisplayPrevious == ::e_display_iconic)
                                                    {

                                                       pinteraction->_001OnDeiconify(::e_display_normal);

                                                    }
                                                    else
                                                    {

                                                       pinteraction->_001OnDeiconify(edisplayPrevious);

                                                    }

                                                 });

                              bHandled = true;

                           }
                           else if (pinteraction->layout().sketch().display() == ::e_display_full_screen
                                    && pinteraction->layout().design().display() != ::e_display_full_screen)
                           {

                              pinteraction->layout().sketch() = ::e_display_full_screen;

                           }

                        }
                        else
                        {

                           if (pinteraction->layout().design().display() != ::e_display_iconic
                               && pinteraction->layout().design().display() != ::e_display_none)
                           {

                              pinteraction->layout().sketch() = ::e_display_iconic;

                           }

                        }

                     }

                  }

               }

            }

         }
         break;
         case MapNotify:
         case UnmapNotify:
         {

            msg.m_id = e_message_show_window;
            msg.wParam = e.type == MapNotify;
            msg.lParam = 0;

            post_ui_message(msg);

         }
         break;
         case ConfigureNotify:
         {

            ::user::primitive_impl *pimpl = msg.oswindow->m_pimpl;

            if (pimpl != nullptr)
            {

               ::user::interaction *pinteraction = pimpl->m_puserinteraction;

               if (pinteraction != nullptr)
               {

                  if (pinteraction->layout().design().display() == ::e_display_iconic && !msg.oswindow->is_iconic())
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

                                              pinteraction->_001OnDeiconify(::e_display_normal);

                                           }
                                           else
                                           {

                                              pinteraction->_001OnDeiconify(edisplayPrevious);

                                           }

                                        });

                  }

                  {

                     //_x11_defer_check_configuration(msg.oswindow);

                     ::point_i32 point(e.xconfigure.x, e.xconfigure.y);

                     ::size_i32 size(e.xconfigure.width, e.xconfigure.height);

                     auto pointWindow = pinteraction->layout().window().screen_origin();

                     auto sizeWindow = pinteraction->layout().window().size();

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
                     // that make new ammendments to ammendment itself,
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

                        pinteraction->layout().sketch().screen_origin() = point;

                        pinteraction->layout().window().screen_origin() = point;

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

                        msg.m_id = e_message_move;
                        msg.wParam = 0;
                        msg.lParam = point.lparam();

                        post_ui_message(msg);

                     }

                     if (bSizeFix)
                     {

                        msg.oswindow->m_point = size;

                        msg.m_id = e_message_size;
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

                  for (auto &papplication : applicationa)
                  {

                     try
                     {

                        auto pauraapplication = papplication->m_pauraapplication;

                        auto uiptraFrame = pauraapplication->m_puiptraFrame->interactiona();

                        for (auto &pframe : uiptraFrame)
                        {

                           try
                           {

                              pframe->post_message(e_message_display_change);

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

            bRet = true;

            msg.time = e.xbutton.time;

            if (e.xbutton.type == ButtonPress)
            {

               if (e.xbutton.button == Button1)
               {

                  ::output_debug_string("ButtonPress::Button1\n");

                  msg.m_id = e_message_left_button_down;

               }
               else if (e.xbutton.button == Button2)
               {

                  msg.m_id = e_message_middle_button_down;

               }
               else if (e.xbutton.button == Button3)
               {

                  msg.m_id = e_message_right_button_down;

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

                  msg.m_id = e_message_left_button_up;

               }
               else if (e.xbutton.button == Button2)
               {

                  msg.m_id = e_message_middle_button_up;

               }
               else if (e.xbutton.button == Button3)
               {

                  msg.m_id = e_message_right_button_up;

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


            if (bRet)
            {

               msg.wParam = 0;

               msg.lParam = MAKELONG(e.xbutton.x_root, e.xbutton.y_root);

               post_ui_message(msg);

            }

         }
            break;
         case KeyPress:
         case KeyRelease:
         {

            msg.time = e.xkey.time;

            bRet = true;

            char buf[32];

            xxf_zeroa(buf);

            string strText;

            KeySym keysym = 0;

            if (e.xkey.type == KeyPress)
            {

               msg.m_id = e_message_key_down;

               __pointer(::windowing_x11::window) pwindow = msg.oswindow;

               if(!pwindow->m_pximkeyboard)
               {

                  pwindow->m_pximkeyboard = new ::xim::keyboard(m_pdisplay->Display(), e.xkey.window);

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

               keysym = XkbKeycodeToKeysym(m_pdisplay->Display(), e.xkey.keycode, 0, e.xkey.state & ShiftMask ? 1 : 0);

               msg.m_id = e_message_key_up;

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

               MESSAGE msgText(msg);

               msgText.m_id = e_message_text_composition;

               msgText.wParam = 0;

               string *pstringText = new string(strText);

               msgText.lParam = (lparam) (iptr) (string *) (pstringText);

               printf("x11_process_message e_message_text_composition\n");

               post_ui_message(msgText);

            }

         }
            break;

         case FocusIn:
         {

            ::output_debug_string("FocusIn\n");

            msg.m_id = e_message_set_focus;

            auto oswindow = msg.oswindow;

            if (::is_set(oswindow))
            {

               m_pdisplay->m_pwindowKeyboardFocus = oswindow;

               auto pimpl = msg.oswindow->m_pimpl;

                if (::is_set(pimpl))
                {

                    auto pinteraction = pimpl->m_puserinteraction;

                    if (::is_set(pinteraction))
                    {

                        msg.m_id = e_message_set_focus;

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
//            output_debug_string("B " + __str(wFocus));
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
//            output_debug_string("D " + __str(wFocus));
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

               auto pimpl = msg.oswindow->m_pimpl;

               if (::is_set(pimpl))
               {

                  auto pinteraction = pimpl->m_puserinteraction;

                  if (::is_set(pinteraction))
                  {

                     msg.m_id = e_message_kill_focus;

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

            msg.oswindow = m_pdisplay->_window(e.xdestroywindow.window);
            msg.m_id = e_message_destroy;

            post_ui_message(msg);

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
//      ___pointer < ::user::message > spbase;
//
//      spbase = Session->get_message_base(pvoidEvent, m_puserinteraction);
//
//      try
//      {
//
//         __pointer(::user::interaction) pinteraction = m_puserinteraction;
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
//__pointer(::user::message) channel::get_message_base(void * pevent,::user::interaction * pwnd)
//{
//
//   __throw(todo());
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
//   synchronous_lock synchronouslock(user_mutex());
//
//   return hwnd->set_window_position(hwndInsertAfter, x, y, cx, cy, nFlags);
//
//}





//int_bool get_window_rect(oswindow hwnd, RECTANGLE_I32 * prectangle)
//{
//
//   synchronous_lock synchronouslock(user_mutex());
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
//   synchronous_lock synchronouslock(window->m_pimpl->m_puserinteraction->mutex());
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
//               synchronous_lock synchronouslock(user_mutex());
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
//   UNREFERENCED_PARAMETER(bDock);
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


   bool windowing::initialize_windowing()
   {

      //acme_defer_os_init_windowing();

      //g_pmutexX11Runnable = new ::mutex();

      //g_prunnableptrlX11 = new list<__pointer(::matter) >();

//      g_pmutexX11Sync = new ::mutex();

//      g_peventX11Sync = new manual_reset_event();

      //oswindow_data::s_pdataptra = new oswindow_dataptra;

      //oswindow_data::s_pmutex = new ::mutex;

      //osdisplay_data::s_pdataptra = new osdisplay_dataptra;

      //osdisplay_data::s_pmutex = new ::mutex;

      return true;

   }


   bool windowing::terminate_windowing()
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

      return false;

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
//      synchronous_lock synchronouslock(user_mutex());
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


   __pointer(::thread) g_pthreadXlib;


   itask_t g_ithreadXlib;


   itask_t x11_get_ithread()
   {

      return g_ithreadXlib;

   }


   CLASS_DECL_ACME ::thread *x11_get_thread()
   {

      return g_pthreadXlib;

   }

//
//osdisplay_data * x11_main_display();
//


   bool windowing::post_ui_message(const MESSAGE &message)
   {

      oswindow oswindow = message.oswindow;

      ASSERT(oswindow != nullptr);

      auto pimpl = oswindow->m_pimpl;

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

      class ::message_queue *pmq = pthread->m_pmq;

      if (pmq == nullptr)
      {

         if (message.m_id == e_message_quit)
         {

            return false;

         }

         pmq = pthread->get_message_queue();

      }

      if (pmq == nullptr)
      {

         return false;

      }

      synchronous_lock ml(pmq->mutex());

      if (message.m_id == e_message_quit)
      {

         output_debug_string("e_message_quit thread");

      }

      if (message.m_id == e_message_left_button_down)
      {

         output_debug_string("post_ui_message::e_message_left_button_down\n");

      }
      else if (message.m_id == e_message_left_button_up)
      {

         output_debug_string("post_ui_message::e_message_left_button_up\n");

      }

      pmq->m_messagea.add(message);

      pmq->m_eventNewMessage.set_event();

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



void x11_check_status(int status, unsigned long window)
{
   if (status == BadWindow)
   {
      printf("window id # 0x%lx does not exists!", window);
      //   exit(1);
   }

   if (status != Success)
   {
      printf("XGetWindowProperty failed!");
      // exit(2);
   }
}

#define MAXSTR 1000

unsigned char *x11_get_string_property(Display *display, Window window, char *property_name)
{

   unsigned char *prop;
   Atom actual_type, filter_atom;
   int actual_format, status;
   unsigned long nitems, bytes_after;

   filter_atom = XInternAtom(display, property_name, True);
   status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
                               &actual_type, &actual_format, &nitems, &bytes_after, &prop);
   x11_check_status(status, window);
   return prop;

}


unsigned long x11_get_long_property(Display *d, Window w, char *property_name)
{

   unsigned char *prop = x11_get_string_property(d, w, property_name);

   unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);

   return long_property;

}


bool x11_get_client_rect(Display * pdisplay, Window window, RECTANGLE_I32 *prectangle)
{

   synchronous_lock synchronouslock(user_mutex());

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

   //g_pmutexX11 = new ::mutex();

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


//mutex * user_mutex()
//{
//
//   return g_pmutexX11;
//
//
//}



