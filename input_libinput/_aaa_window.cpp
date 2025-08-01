// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "buffer.h"
#include "window.h"
#include "windowing_x11.h"
#include "windowing.h"
#include "display.h"
#include "cursor.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/user/user/_text_stream.h"
#include "apex/platform/node.h"
#include "apex/platform/system.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/user/user/interaction_graphics_thread.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/platform/message_queue.h"
#include <X11/Xatom.h>
#include <X11/extensions/sync.h>
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/platform/application.h"
#include "acme/operating_system/x11/display_lock.h"


void on_sn_launch_context(void * pSnContext, Window window);

void on_sn_launch_complete(void * pSnContext);


::particle * user_synchronization();


#undef ALOG_CONTEXT
#define ALOG_CONTEXT ::trace_object(::trace_category_windowing)


namespace windowing_x11
{


   window::window()
   {

      //m_bXShmPutImagePending = false;

      //m_bXShmComplete = false;
      m_pWindow4 = this;

      m_iXic = 0;

      m_xic = nullptr;


      //m_bNetWmStateHidden = false;
      //m_bNetWmStateMaximized = false;
      //m_bNetWmStateFocused = false;


      //      for (auto & i : m_iaNetWmState)
      //      {
      //
      //         i = -1;
      //
      //      }

      m_cursorLast = 0;

      m_htask = 0;

      m_window = None;

      //m_pwindow = nullptr;

      m_bMessageOnlyWindow = false;

      zero(m_visual);

      m_iDepth = -1;

      //m_iScreen = -1;

      //m_colormap = None;

      m_iXic = 0;

   }


   window::~window()
   {

   }


   void window::create_window(::windowing::window * pimpl)
   {

      bool bOk = true;

      {

         synchronous_lock synchronouslock(user_synchronization());

         auto pusersystem = pimpl->m_puserinteraction->m_pusersystem;

         pimpl->m_puserinteraction->m_bMessageWindow = false;

         auto pwindowing = x11_windowing();

         auto pwindowingdisplay = pwindowing->display();

         auto pdisplayx11 = dynamic_cast < ::windowing_x11::display * > (pwindowingdisplay);

         ::Display * display = pdisplayx11->Display();

         if (display == nullptr)
         {

            fprintf(stderr, "ERROR: Could not open display\n");

            bOk = false;

            //return ::success;
            throw ::exception(error_failed);

         }

         m_pwindow = pimpl;

         m_pwindow->m_puserinteraction->m_pwindow = this;

         // if(::is_null(m_pwindow->m_puserinteraction->m_pwindow))
         // {

         //    printf("m_pwindow->m_puserinteraction->m_pwindow is null!! (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("m_pwindow->m_puserinteraction->m_pwindow is set!! (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

         // }

         // fflush(stdout);

         m_pwindow->m_puserinteraction->m_puserinteractionTopLevel = m_pwindow->m_puserinteraction;

         m_pdisplay = pwindowing->display();

         pimpl->m_pwindow = this;

         // printf("pimpl->m_pwindow.m_p (0x%x)\n", pimpl->m_pwindow.m_p);
         // printf("pimpl->m_pwindow.m_pelement (0x%x)\n", pimpl->m_pwindow.m_pelement);

         display_lock displaylock(pdisplayx11->Display());

         int x = m_pwindow->m_puserinteraction->const_layout().sketch().origin().x();

         int y = m_pwindow->m_puserinteraction->const_layout().sketch().origin().y();

         int cx = m_pwindow->m_puserinteraction->const_layout().sketch().width();

         int cy = m_pwindow->m_puserinteraction->const_layout().sketch().height();

         bool bVisible = m_pwindow->m_puserinteraction->const_layout().sketch().is_screen_visible();

         //      if(pusersystem)
         //      {
         //
         //         if (pusersystem->m_createstruct.x <= 0)
         //         {
         //
         //            x = pusersystem->m_createstruct.x;
         //
         //         }
         //
         //         if (pusersystem->m_createstruct.y <= 0)
         //         {
         //
         //            y = pusersystem->m_createstruct.y;
         //
         //         }
         //
         //         if (pusersystem->m_createstruct.cx() <= 0)
         //         {
         //
         //            cx = 1;
         //
         //         }
         //
         //         if (pusersystem->m_createstruct.cy() <= 0)
         //         {
         //
         //            cy = 1;
         //
         //         }
         //
         //         if (pusersystem->m_createstruct.style & WS_VISIBLE)
         //         {
         //
         //            bVisible = true;
         //
         //         }
         //
         //      }

         if (cx <= 0)
         {

            cx = 1;

         }

         if (cy <= 0)
         {

            cy = 1;

         }

         ::Window rootwin = RootWindow(display, pdisplayx11->m_iScreen);

         XEvent e;

         // query Visual for "TrueColor" and 32 bits depth (RGBA)

         ::Visual * visual = DefaultVisual(display, DefaultScreen(display));

         m_iDepth = 0;

         if (m_px11data.is_null())
         {

            m_px11data = __allocate x11data();

         }

         if (XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &m_visualinfo))
         {

            visual = m_visualinfo.visual;

         } else
         {

            zero(m_visualinfo);

         }

         m_iDepth = m_visualinfo.depth;

         XSetWindowAttributes attr;

         zero(attr);

         attr.colormap = pdisplayx11->m_colormap;

         attr.event_mask =
            PropertyChangeMask | ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask |
            PointerMotionMask | StructureNotifyMask | FocusChangeMask | LeaveWindowMask | EnterWindowMask;

         attr.background_pixmap = None;

         attr.border_pixmap = None;

         attr.border_pixel = 0;

         attr.override_redirect =
            pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning ? True : False;

         //attr.override_redirect = True;

         m_xsynccounterNetWmSync = None;
         XSyncIntToValue(&m_xsyncvalueNetWmSync, 0);
         XSyncIntToValue(&m_xsyncvalueNetWmSyncPending, 0);

         informationf("XCreateWindow (l=%d, t=%d) (w=%d, h=%d)", x, y, cx, cy);

         //m_bNetWmStateHidden = false;
         //m_bNetWmStateMaximized = false;
         //m_bNetWmStateFocused = false;

         m_atomaNetWmState.clear();

         ::Window window = XCreateWindow(display, DefaultRootWindow(display),
                                         x, y,
                                         cx, cy,
                                         0,
                                         m_iDepth,
                                         InputOutput,
                                         visual,
                                         CWColormap | CWEventMask | CWBackPixmap | CWBorderPixel
                                         | CWOverrideRedirect, &attr);

         {

            XSizeHints sizehints = {0};

            sizehints.flags = PPosition | PSize;     /* I want to specify position and size */
            sizehints.x = x;       /* The origin and size coords I want */
            sizehints.y = y;
            sizehints.width = cx;
            sizehints.height = cy;

            XSetNormalHints(display, window, &sizehints);  /* Where new_window is the ___new window */

         }



         // if(::is_null(m_pwindow->m_puserinteraction->m_pwindow))
         // {

         //    printf("m_pwindow->m_puserinteraction->m_pwindow is null!! (2)(0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("m_pwindow->m_puserinteraction->m_pwindow is set!! (2)(0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

         // }

         // fflush(stdout);


         //auto & windowstate3 = pimpl->m_puserinteraction->m_layout.window();

         //windowstate3.origin() = {INT_MIN, INT_MIN};

         //windowstate3.size() = {INT_MIN, INT_MIN};

         //windowstate3.screen_origin() = {INT_MIN, INT_MIN};

         //auto & state = pimpl->m_puserinteraction->m_layout.design();

         //state.origin() = {x, y};

         //state.size() = {cx, cy};

         //state.screen_origin() = state.origin();

         if (window == 0)
         {

            bOk = false;

            throw ::exception(error_failed);

         }

         auto estatus = initialize_x11_window(pdisplayx11, window, visual, m_iDepth, pdisplayx11->m_iScreen,
                                              attr.colormap);

         if (!estatus)
         {

            throw ::exception(error_failed);

         }

         // if(::is_null(m_pwindow->m_puserinteraction->m_pwindow))
         // {

         //    printf("m_pwindow->m_puserinteraction->m_pwindow is null!! (3)(0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("m_pwindow->m_puserinteraction->m_pwindow is set!! (3)(0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

         // }

         //fflush(stdout);


         set_oswindow(this);

         set_os_data((void *) window);

         _enable_net_wm_sync();

         //pimpl->set_os_data((::windowing::window *)this);

         //set_os_data(LAYERED_X11, (::windowing_x11::window *)this);

         //pimpl->set_os_data(LAYERED_X11, (::windowing_x11::window *)this);

         pimpl->m_puserinteraction->m_pinteractionimpl = pimpl;

         pimpl->m_puserinteraction->increment_reference_count(
            REFERENCING_DEBUGGING_P_NOTE(this, "native_create_window"));

         auto papp = get_app();

         if (!(pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window))
         {

            auto psystem = system();

            string strApplicationServerName = psystem->get_application_server_name();

            set_wm_class(strApplicationServerName);

            //         XClassHint * pupdate = XAllocClassHint();
            //
            //         auto psystem = system();
            //
            //         string strApplicationServerName = psystem->get_application_server_name();
            //
            //         pupdate->res_class = (char *) (const_char_pointer )strApplicationServerName;
            //
            //         pupdate->res_name = (char *) (const_char_pointer )strApplicationServerName;
            //
            //         XSetClassHint(display, window, pupdate);
            //
            //         XFree(pupdate);

         }

         // if(::is_null(m_pwindow->m_puserinteraction->m_pwindow))
         // {

         //    printf("m_pwindow->m_puserinteraction->m_pwindow is null!! (4) (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("m_pwindow->m_puserinteraction->m_pwindow is set!! (4) (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

         // }

         // fflush(stdout);


#ifndef RASPBERRYPIOS

         if (pwindowing->m_pSnLauncheeContext != nullptr && !papp->m_bSnLauncheeSetup)
         {

            //papp->os_on_start_application();

            on_sn_launch_context(pwindowing->m_pSnLauncheeContext, window);

            papp->m_bSnLauncheeSetup = true;

         }

#endif

         if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_dock_window)
         {

            wm_dockwindow(true);

         } else if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_desktop_window)
         {

            wm_desktopwindow(true);

         } else if (pimpl->m_puserinteraction->const_layout().sketch().activation() & ::user::e_activation_on_center_of_screen)
         {

            wm_centerwindow(true);

         } else if (pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_satellite_window
                    || pimpl->m_puserinteraction->m_bToolWindow)
         {

            wm_toolwindow(true);

         } else
         {

            wm_normalwindow();

         }

         //m_px11data->m_pgdkwindow = gdk_x11_window_foreign_new_for_display(gdk_display_get_default(), window);

         ::Window root = 0;

         ::Window * pchildren = nullptr;

         unsigned int ncount = 0;

         XQueryTree(display, window, &root, &m_parent, &pchildren, &ncount);

         if (pchildren != nullptr)
         {

            XFree(pchildren);

         }

         htask htask = ::current_htask();

         m_htask = htask;

         if (!XGetWindowAttributes(Display(), Window(), &m_px11data->m_attr))
         {

            information() << "freebsd::interaction_impl::_native_create_window_ex XGetWindowAttributes failed.";

         }

         int event_base, error_base, major_version, minor_version;

         pimpl->m_bComposite = XGetSelectionOwner(Display(), x11_display()->intern_atom("_NET_WM_CM_S0", True));

         string strName;

         //      if (pusersystem && pusersystem->m_createstruct.lpszName != nullptr && strlen(pusersystem->m_createstruct.lpszName) > 0)
         //      {
         //
         //         strName = pusersystem->m_createstruct.lpszName;
         //
         //      }

         //if(strName.is_empty())
         //{

         string strWindowText = pimpl->m_puserinteraction->get_window_text();

         if (strWindowText.has_character())
         {

            strName = strWindowText;

         }

         //}

         if (strName.has_character())
         {

            XStoreName(Display(), Window(), strName);

         }

         // if(::is_null(m_pwindow->m_puserinteraction->m_pwindow))
         // {

         //    printf("m_pwindow->m_puserinteraction->m_pwindow is null!!(5) (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("m_pwindow->m_puserinteraction->m_pwindow is set!!(5) (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

         // }

         // fflush(stdout);

         auto psystem = system();

         auto pnode = psystem->node();

         auto papp = get_app();

         ::file::path pathDesktop = pnode->get_desktop_file_path(papp);

         _bamf_set_icon_unlocked(pathDesktop);

         _wm_nodecorations(0);

         //if (pusersystem->m_createstruct.style & WS_VISIBLE)
         if (bVisible)
         {

            map_window();

         } else
         {

            pimpl->m_puserinteraction->const_layout().window().display() = e_display_none;

         }

         //if(m_px11data->m_attr.map_state != IsUnmapped)
         {

            if (!attr.override_redirect)
            {

               auto edisplay = pimpl->m_puserinteraction->const_layout().sketch().display();

               if (is_docking_appearance(edisplay))
               {

                  // window managers generally "don't like" windows that starts "docked/snapped".
                  // initial (XCreateWindow) int_size and position maybe not be honored.
                  // so requesting the same change again in a effort to set the "docked/snapped" int_size and position.

                  //set_window_position(e_zorder_top, pusersystem->m_createstruct.x, pusersystem->m_createstruct.y,
                  //                  pusersystem->m_createstruct.cx(), pusersystem->m_createstruct.cy(), SWP_SHOWWINDOW);

                  set_window_position(e_zorder_top, x, y, cx, cy, ::user::e_activation_set_active, false, false, false,
                                      edisplay);

               }

            }

         }


      }

//      //displaylock.unlock();
//
//      //if(pshowwindow->m_bShow)
//      {
//
//         //::int_rectangle rect32;
//
//         //(::window_rectangle((oswindow) get_handle(), rect32))
//         {
//
//
//            if (get_session() != nullptr)
//            {
//
//               // Initial position of window below the cursor position
//               // with invalid (empty) size.
//               // (Hinting for monitor placement, if no stored information
//               // available).
//
//               if (pimpl->m_puserinteraction->const_layout().sketch().display() == e_display_undefined)
//               {
//
//                  auto pointCursor = get_cursor_position();
//
//                  pimpl->m_puserinteraction->set_position(pointCursor);
//
//                  pimpl->m_puserinteraction->set_size({0, 0});
//
//               }
//
//            }
//
//         }

         //   }

         //});
         //}

//      }

      // if(::is_null(m_pwindow->m_puserinteraction->m_pwindow))
      // {

      //    printf("m_pwindow->m_puserinteraction->m_pwindow is null!! (6)(0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
      //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

      // }
      // else
      // {

      //    printf("m_pwindow->m_puserinteraction->m_pwindow is set!! (6)(0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
      //    printf("m_pwindow->m_puserinteraction (0x%x)\n", m_pwindow->m_puserinteraction.m_p);

      // }

      // fflush(stdout);


      if (bOk)
      {

         //auto lresult = pimpl->m_puserinteraction->send_message(e_message_create, 0, (lparam) &pusersystem->m_createstruct);

         // if(::is_null(pimpl->m_puserinteraction->m_pwindow))
         // {

         //    printf("pimpl->m_puserinteraction->m_pwindow is null!! (7) (0x%x)\n", pimpl->m_puserinteraction->m_pwindow);
         //    printf("pimpl->m_puserinteraction (0x%x)\n", pimpl->m_puserinteraction.m_p);

         // }
         // else
         // {

         //    printf("pimpl->m_puserinteraction->m_pwindow is set!! (7) (0x%x)\n", m_pwindow->m_puserinteraction->m_pwindow);
         //    printf("pimpl->m_puserinteraction (0x%x)\n", pimpl->m_puserinteraction.m_p);

         // }

         // fflush(stdout);

         // auto & pwindowInteraction = pimpl->m_puserinteraction->m_pwindow;

         // printf("pwindowInteraction (7B) (0x%x)\n", pwindowInteraction);
         // printf("&pwindowInteraction (7BA) (0x%x)\n", &pwindowInteraction);

         // fflush(stdout);

// // https://stackoverflow.com/questions/23367775/pragma-packshow-with-gcc - Morten Jensen
//       /*
//    The static_assert macro will generate an error at compile-time, if the predicate is false
//    but will only work for predicates that are resolvable at compile-time!

//    E.g.: to assert the size of a data structure, static_assert(sizeof(struct_t) == 10)
// */
// #define STATIC_ASSERT(COND,MSG)      typedef char static_assertion_##MSG[(!!(COND))*2-1]
// /* token pasting madness: */
// #define COMPILE_TIME_ASSERT3(X,L)     STATIC_ASSERT(X,at_line_##L)             /* add line-number to error message for better warnings, especially GCC will tell the name of the variable as well */
// #define COMPILE_TIME_ASSERT2(X,L)     COMPILE_TIME_ASSERT3(X, L)               /* expand line-number */
// #define static_assert(X)              COMPILE_TIME_ASSERT2(X, __LINE__)        /* call with line-number macro */

// #define PACKED  __attribute__ ((gcc_struct, __packed__))

// typedef struct {
//   uint8_t bytes[3];
//   uint32_t looong;
// } PACKED struct_t;
// static_assert(sizeof(struct_t) == 8);

//  typedef struct {
//    uint8_t bytes[3];
//    uint32_t looong;
//  } struct_t2;
// // static_assert(sizeof(struct_t) == 8);

// printf("sizeof(struct_t2) = %d\n", sizeof(struct_t2));


//       #ifdef _DEBUG
//       printf("_DEBUG defined\n");
//       #else
//       printf("_DEBUG not defined\n");
//       #endif

//       #ifdef RASPBERRYPIOS
//       printf("RASPBERRYPIOS defined\n");
//       #else
//       printf("RASPBERRYPIOS not defined\n");
//       #endif


#ifdef REPORT_OFFSET

         printf("(7BB) offset of m_timeFocusStart in ::user::interaction_base = %d\n", offsetof(::user::interaction_base,m_timeFocusStart));
         printf("(7BB) offset of m_bExtendOnParent in ::user::interaction = %d\n", offsetof(::user::interaction, m_bExtendOnParent));
         printf("(7BB) offset of m_pwindow in ::user::interaction = %d\n", offsetof(::user::interaction, m_pwindow));
         printf("(7BB) offset of m_pImpl2 in ::windowing::window = %d\n", offsetof(::windowing::window, m_pImpl2));
         printf("(7BB) offset of m_timeLastExposureAddUp in ::windowing::window = %d\n", offsetof(::windowing::window, m_timeLastExposureAddUp));
         printf("(7BB) offset of m_strBitmapSource in ::windowing::window = %d\n", offsetof(::windowing::window, m_strBitmapSource));
         printf("(7BB) offset of m_bCursorRedraw in ::windowing::window = %d\n", offsetof(::windowing::window, m_bCursorRedraw));
         printf("(7BB) offset of m_bLockWindowUpdate in ::windowing::window = %d\n", offsetof(::windowing::window, m_bLockWindowUpdate));
         printf("(7BB) offset of m_bOkToUpdateScreen in ::windowing::window = %d\n", offsetof(::windowing::window, m_bOkToUpdateScreen));
         printf("(7BB) offset of m_sizeDrawn in ::windowing::window = %d\n", offsetof(::windowing::window, m_sizeDrawn));
         printf("(7BB) offset of m_pthreadMouseLeave in ::windowing::window = %d\n", offsetof(::windowing::window, m_pthreadMouseLeave));
         printf("(7BB) offset of m_bPointInside in ::windowing::window = %d\n", offsetof(::windowing::window, m_bPointInside));
         printf("(7BB) offset of m_pwindow in ::windowing::window = %d\n", offsetof(::windowing::window, m_pwindow));

#endif

         auto lresult = pimpl->m_puserinteraction->send_message(e_message_create, 0, 0);

         if (lresult == -1)
         {

            throw ::exception(error_failed);

         }

         pimpl->m_puserinteraction->m_ewindowflag |= e_window_flag_window_created;

         pimpl->m_puserinteraction->set_flag(e_flag_task_started);

      }

      if (!bOk)
      {

         throw ::exception(error_failed);

      }

   }


   void window::set_wm_class(const_char_pointer psz)
   {

      synchronous_lock synchronouslock(user_synchronization());

      m_strWMClass = psz;

      display_lock displaylock(x11_display()->Display());

      XClassHint classHint;

      classHint.res_name = (char *) (const_char_pointer )m_strWMClass;

      classHint.res_class = (char *) (const_char_pointer )m_strWMClass;

      XSetClassHint(Display(), Window(), &classHint);

   }


   int window::map_window()
   {

      int i = 0;

      synchronous_lock synchronouslock(user_synchronization());

      {

         windowing_output_debug_string("\nwindow::map_window");

         display_lock displaylock(x11_display()->Display());

         i = XMapWindow(Display(), Window());

      }

      //#ifdef WITH_SN

      auto pwindowing = x11_windowing();

      //  if (pwindowing->m_pSnLauncheeContext != nullptr)
      if (!pwindowing->m_bFirstWindowMap)
      {

         pwindowing->m_bFirstWindowMap = true;

         auto psystem = system();

         auto pnode = psystem->node();

         pnode->defer_notify_startup_complete();

         on_sn_launch_complete(pwindowing->m_pSnLauncheeContext);

         pwindowing->m_pSnLauncheeContext = nullptr;

      }

      //#endif // RASPBERRYPIOS

      windowing_output_debug_string("\nwindow::map_window END");

      return i;

   }


   int window::unmap_window(bool bWithdraw)
   {

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("\nwindow::unmap_window");

      display_lock displaylock(x11_display()->Display());

      int i;

      if (bWithdraw)
      {

         i = XWithdrawWindow(Display(), Window(), x11_display()->m_iScreen);

      } else
      {

         i = XUnmapWindow(Display(), Window());

      }

      windowing_output_debug_string("\nwindow::unmap_window END");

      return i;

   }


   //   oswindow_dataptra *window::s_pdataptra = nullptr;
   //
   //
   //   ::pointer< ::mutex >window::s_pmutex = nullptr;


   //   int oswindow_find_message_only_window(::windowing::window *pimpl)
   //   {
   //
   //      if (pimpl == nullptr)
   //      {
   //
   //         return -1;
   //
   //      }
   //
   //      single_lock slOsWindow(window::s_pmutex, true);
   //
   //      for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //      {
   //
   //         if (::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //             && ::window::s_pdataptra->element_at(i)->m_pwindow == pimpl)
   //         {
   //
   //            return i;
   //
   //         }
   //
   //      }
   //
   //      return -1;
   //
   //   }

   //   int oswindow_find(Display *Display(), Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //      {
   //         if (!::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //             && ::window::s_pdataptra->element_at(i)->m_osdisplay->display() == Display()
   //             && ::window::s_pdataptra->element_at(i)->m_window == window)
   //         {
   //            return i;
   //         }
   //      }
   //
   //      return -1;
   //
   //   }

   //   int oswindow_find(Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      for (int i = 0; i < ::window::s_pdataptra->get_count(); i++)
   //      {
   //         if (!::window::s_pdataptra->element_at(i)->m_bMessageOnlyWindow
   //             && ::window::s_pdataptra->element_at(i)->m_window == window)
   //         {
   //            return i;
   //         }
   //      }
   //
   //      return -1;
   //
   //   }

   //
   //   window *oswindow_get_message_only_window(::windowing::window *pinteraction)
   //   {
   //
   //      if (pinteraction == nullptr)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      auto pFind = oswindow_find_message_only_window(pinteraction);
   //
   //      if (::is_set(pFind))
   //      {
   //
   //         return ::window::s_pdataptra->element_at(iFind);
   //
   //      }
   //
   //      ::window *pdata = ___new window();
   //
   //      pdata->m_bMessageOnlyWindow = true;
   //      pdata->m_window = None;
   //      pdata->m_pwindow = pinteraction;
   //      pdata->m_osdisplay = nullptr;
   //      pdata->m_parent = 0;
   //      pdata->m_pmq = pinteraction->m_puserinteraction->m_pthreadUserInteraction->get_mq();
   //
   //      ::window::s_pdataptra->add(pdata);
   //
   //      return pdata;
   //
   //   }

   //
   //   window *oswindow_defer_get(Display *Display(), Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      auto pFind = oswindow_find(Display(), window);
   //
   //      if (::is_null(pFind))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      return ::window::s_pdataptra->element_at(iFind);
   //
   //   }


   ::e_status
   window::initialize_x11_window(::windowing_x11::display * pdisplay, ::Window window, ::Visual * pvisual, int iDepth,
                                 int iScreen, Colormap colormap)
   {

      //single_lock slOsWindow(::window::s_pmutex, true);

      //      auto pFind = oswindow_find(Display(), window);
      //
      //      if (::is_set(pFind))
      //      {
      //
      //         return ::window::s_pdataptra->element_at(iFind);
      //
      //      }
      //
      //      ::window *pdata = ___new ::window();

      m_bMessageOnlyWindow = false;
      //m_osdisplay = osdisplay_get(Display());
      m_pdisplay = pdisplay;
      m_window = window;

      if (pvisual != nullptr)
      {

         m_visual = *pvisual;

      }

      m_iDepth = iDepth;
      //m_iScreen = iScreen;
      //m_colormap = colormap;
      //m_parent = 0;

      //::window::s_pdataptra->add(pdata);

      x11_display()->m_windowmap[m_window] = this;

      return ::success;

   }


   //void x11_on_start_session()
   //{

   //   Display * dpy = x11_get_display();
   //
   //   g_oswindowDesktop = oswindow_get(dpy, DefaultRootWindow(dpy));
   //
   //   g_oswindowDesktop->m_pwindow = nullptr;
   //
   //   XSelectInput(g_oswindowDesktop->Display(), g_oswindowDesktop->Window(), StructureNotifyMask);
   //
   //}

   Display * window::Display()
   {

      return x11_display()->Display();

   }

   Display * window::Display() const
   {

      return x11_display()->Display();

   }


   int window::Screen()
   {

      return x11_display()->Screen();

   }


   int window::Screen() const
   {

      return x11_display()->Screen();

   }


   Window window::Window()
   {

      return m_window;

   }


   Window window::Window() const
   {

      return m_window;

   }


   Visual * window::Visual()
   {

      return &m_visual;

   }


   const Visual * window::Visual() const
   {

      return &m_visual;

   }

   //   window *oswindow_get(Window window)
   //   {
   //
   //      single_lock slOsWindow(::window::s_pmutex, true);
   //
   //      auto pFind = oswindow_find(window);
   //
   //      if (::is_null(pFind))
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      return ::window::s_pdataptra->element_at(iFind);
   //
   //   }


   bool window::bamf_set_icon()
   {

      synchronous_lock synchronouslock(user_synchronization());

      auto psystem = system();

      auto pnode = psystem->node();

      auto papp = get_app();

      ::file::path path = pnode->get_desktop_file_path(papp);

      informationf("windowing_x11::interaction_impl::set_window_text");

      //fflush(stdout);

      display_lock displaylock(x11_display()->Display());

      Atom atomBamfDesktopFile = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);

      //Atom cardinal = x11_display()->intern_atom("STRING", False);

      int status = XChangeProperty(
         Display(),
         Window(),
         atomBamfDesktopFile,
         XA_STRING,
         8,
         PropModeReplace,
         (const unsigned char *) (const_char_pointer )path,
         path.length());

      informationf("windowingx_x11::windoxw::bamfx_set_icon END");

      //fflush(stdout);

      if (status != 0)
      {

         return false;

      }

      return true;

   }


   int window::x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements)
   {

      return XChangeProperty(Display(), Window(), property, type, format, mode, data, nelements);

   }


   bool window::set_icon(::image::image *pimage)
   {

      // http://stackoverflow.com/questions/10699927/xlib-argb-window-icon
      // http://stackoverflow.com/users/432509/ideasman42

#if 0

      unsigned int buffer[] =
         {
         16, 16,
         4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 338034905, 3657433343, 0, 184483840, 234881279, 3053453567, 3221225727, 1879048447, 0, 0, 0, 0, 0, 0, 0, 1224737023, 3305111807, 3875537151,0, 0, 2063597823, 1291845887, 0, 67109119, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 50266112, 3422552319, 0, 0, 3070230783, 2063597823, 2986344703, 771752191, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 3372220671, 1509949695, 704643327, 3355443455, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 134152192, 3187671295, 251658495, 0, 3439329535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3422552319, 0, 0, 2332033279, 1342177535, 167772415, 3338666239, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 3422552319, 0, 0, 436207871, 3322085628, 3456106751, 1375731967, 4278255360, 4026597120, 3758161664, 3489726208, 3204513536, 2952855296, 2684419840, 2399207168, 2130771712, 1845559040, 1593900800, 1308688128, 1040252672, 755040000, 486604544, 234946304, 4278255360, 4043374336, 3774938880, 3506503424, 3221290752, 2952855296, 2667642624, 2399207168, 2130771712, 1862336256, 1627453957, 1359017481, 1073805064, 788591627, 503379721, 218169088, 4278255360, 4043374336, 3758161664, 3506503424, 3221290752, 2952855296, 2684419840, 2415984384, 2130771712, 1862336256, 1577123584, 1308688128, 1040252672, 755040000, 486604544, 218169088, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 520093951, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2667577599, 2415919359, 2130706687, 1862271231, 1593835775, 1325400319, 1056964863, 771752191, 503316735, 234881279, 4278190335, 4026532095, 3758096639, 3489661183, 3221225727, 2952790271, 2684354815, 2399142143, 2130706687, 1862271231, 1593835775, 1325400319, 1040187647, 771752191, 520093951, 234881279, 4294901760, 4043243520, 3774808064, 3506372608, 3221159936, 2952724480, 2684289024, 2399076352, 2147418112, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4060020736, 3758030848, 3506372608, 3221159936, 2952724480, 2684289024, 2415853568, 2130640896, 1862205440, 1593769984, 1308557312, 1040121856, 771686400, 503250944, 234815488, 4294901760, 4043243520, 3774808064, 3489595392, 3237937152, 2952724480, 2684289024, 2415853568, 2147418112, 1862205440, 1593769984, 1325334528, 1056899072, 788463616, 503250944, 234815488,
         32, 32,
         4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 268369920, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 1509949695, 3120562431, 4009754879, 4194304255, 3690987775, 2130706687, 83886335, 0, 50331903, 1694499071, 3170894079, 3992977663, 4211081471, 3657433343, 1879048447, 16777471, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3087007999, 2281701631, 1191182591, 1040187647, 2030043391, 4127195391, 2566914303, 0, 16777471, 3254780159, 2181038335, 1191182591, 973078783, 2030043391,4177527039, 2130706687, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2214592767, 4093640959, 0, 0, 0, 0, 0, 0, 0, 2298478847, 3909091583, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2214592767, 3607101695, 0, 0, 0, 0, 0, 0, 0, 1946157311, 4093640959, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 536871167, 1191182591, 2281701631,3019899135, 637534463, 0, 0, 0, 100597760, 251592704, 33488896, 0, 3321889023, 2919235839, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2550137087, 4278190335, 4278190335, 3405775103, 570425599, 0, 0, 0, 0, 0, 0, 2046820607, 4043309311, 620757247, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 33488896, 0, 0, 218104063, 1291845887, 3841982719, 3388997887, 0, 0, 0, 0, 0, 1996488959, 4093640959, 1073742079, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1761607935, 4278190335, 150995199, 0, 0, 67109119, 2550137087, 3909091583, 889192703, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 2181038335, 3925868799, 0, 0, 218104063, 3070230783, 3623878911, 570425599, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 805306623, 3288334591, 1795162367, 1040187647, 1023410431, 2231369983, 4211081471, 1694499071, 0, 369099007, 3456106751, 3825205503, 1174405375, 872415487, 872415487, 872415487, 872415487, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4293984270, 2046951677, 3422552319, 4110418175, 4177527039, 3405775103, 1409286399, 0, 0, 1409286399, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 4278190335, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760,4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 4294901760, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2936078080, 2801860352, 2650865408, 2516647680, 2382429952, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1577123584, 1459683072, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 385941248, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3724607232, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2516647680, 2399207168, 2264989440, 2130771712, 1996553984, 1845559040, 1728118528, 1593900800, 1459683072, 1308688128, 1191247616, 1057029888, 922812160, 788594432, 637599488, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3053518592, 2919300864, 2801860352, 2650865408, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528,1593900800, 1459683072, 1325465344, 1191247616, 1040252672, 906034944, 771817216, 654376704, 503381760, 369164032, 234946304, 117505792, 4278255360, 4144037632, 4009819904, 3858824960, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2936078080, 2801860352, 2667642624, 2533424896, 2382429952, 2264989440, 2130771712, 1979776768, 1862336256, 1728118528, 1577123584, 1442905856, 1325465344, 1191247616, 1040252672, 922812160, 771817216, 637599488, 503381760, 369164032, 234946304, 100728576, 4278255360, 4144037632, 4009819904, 3875602176, 3741384448, 3607166720, 3472948992, 3338731264, 3204513536, 3070295808, 2919300864, 2801860352, 2667642624, 2533424896, 2399207168, 2264989440, 2113994496, 1996553984, 1862336256, 1728118528, 1593900800, 1442905856, 1342241795, 1174470400, 1057029888, 906034944, 788594432, 654376704, 503381760, 385941248, 251723520, 100728576, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3472883967, 3338666239, 3221225727, 3070230783, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951,385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3741319423, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2533359871, 2399142143, 2281701631, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775,1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 234881279, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2936013055, 2801795327, 2667577599, 2550137087, 2415919359, 2264924415, 2130706687, 1996488959, 1862271231, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 503316735, 369099007, 251658495, 100663551, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3204448511, 3087007999, 2936013055, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2130706687, 1996488959, 1879048447, 1728053503, 1593835775, 1459618047, 1325400319, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 117440767, 4278190335, 4160749823, 4026532095, 3892314367, 3758096639, 3623878911, 3489661183, 3355443455, 3221225727, 3087007999, 2952790271, 2818572543, 2667577599, 2533359871, 2399142143, 2264924415, 2147483903, 2013266175, 1862271231, 1744830719, 1610612991, 1476395263, 1342177535, 1191182591, 1056964863, 922747135, 788529407, 654311679, 520093951, 385876223, 251658495, 100663551, 4294901760, 4160684032, 4026466304, 3909025792, 3774808064, 3623813120, 3489595392, 3355377664, 3237937152, 3103719424, 2952724480, 2818506752, 2684289024, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1593769984, 1476329472,1325334528, 1207894016, 1056899072, 939458560, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3506372608, 3355377664, 3221159936, 3086942208, 2952724480, 2818506752, 2701066240, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1727987712, 1610547200, 1476329472, 1325334528, 1191116800, 1073676288, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3103719424, 2952724480, 2818506752, 2700935170, 2550071296, 2415853568, 2281635840, 2147418112, 2013200384, 1878982656, 1744764928, 1610547200, 1459552256, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 671023104, 520028160, 385810432, 251592704, 100597760, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3640590336, 3489595392, 3372154880, 3237937152, 3086942208, 2969501696, 2818506752, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2013200384, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744, 1191116800, 1056899072, 922681344, 788463616, 654245888, 520028160, 385810432, 251592704, 117374976, 4294901760, 4177461248, 4043243520, 3909025792, 3774808064, 3623813120, 3506372608, 3372154880, 3237937152, 3103719424, 2952724480, 2835283968, 2684289024, 2550071296, 2432630784, 2281635840, 2147418112, 2046492676, 1862205440, 1744764928, 1610547200, 1476329472, 1342111744,1207894016, 1056899072, 939458560, 788463616, 654245888, 536281096, 385810432, 251592704, 134152192,
         };

      display_lock displaylock(x11_display()->Display());

      int iScreen = DefaultScreen(d);

      Atom net_wm_icon = x11_display()->intern_atom("_NET_WM_ICON", False);

      Atom cardinal = x11_display()->intern_atom("CARDINAL", False);

      int length = 2 + 16 * 16 + 2 + 32 * 32;

      int status = XChangeProperty(Display(), w->Window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) buffer, length);

      if(status != 0)
      {

         return false;

      }

#elif 1

      auto image1 = image()->create_image({32, 32});

      if (image1.nok())
      {

         return false;

      }

      image1->g()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

      {

         ::image::image_source imagesource(pimage->g(), pimage->rectangle());

         double_rectangle rectangle(image1->rectangle());

         ::image::image_drawing_options imagedrawingoptions(rectangle);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         //getfileimage.m_iImage = m_pimagelist[16]->set(getfileimage.m_iImage, imagedrawing);

         image1->g()->draw(imagedrawing);

      }

      memory m(m_pwindow->m_puserinteraction->get_app());

      int length = 2 + image1->area();

      m.set_size(length * 4);

      unsigned int * pcr = (unsigned int *) m.data();

      pcr[0] = image1->width();

      pcr[1] = image1->height();

      int c = image1->area();

      for (int i = 0; i < c; i++)
      {

         pcr[i + 2] = image1->image32()[i].m_ui;

      }

      windowing_output_debug_string("\nwindow::set_icon");

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      Atom net_wm_icon = x11_display()->intern_atom("_NET_WM_ICON", False);

      Atom cardinal = x11_display()->intern_atom("CARDINAL", False);

      int status = x_change_property(net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char *) pcr, length);

      if (status == BadAlloc)
      {


      } else if (status != 0)
      {

         return false;

      }

      windowing_output_debug_string("\nwindow::set_icon END");

      fflush(stdout);

#else

      image d1(w->m_pwindow->m_puserinteraction->create_new, this);

      if(!d1->create(24, 24))
      {

         return false;

      }

      d1->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

      d1->get_graphics()->StretchBlt(0, 0, d1.width(), d1.height(), point->get_graphics(), 0, 0, point.width(), point.height());

      image d2(w->m_pwindow->m_puserinteraction->create_new, this);

      if(!d2->create(54, 54))
      {

         return false;

      }

      d2->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

      d2->get_graphics()->StretchBlt(0, 0, d2.width(), d2.height(), point->get_graphics(), 0, 0, point.width(), point.height());

      memory m(w->m_pwindow->m_puserinteraction->get_context_application());

      int length = 2 + d1->area() + 2 + d2->area();

      m.set_size(length * 4);

      unsigned int * pcr = (unsigned int *) m.get_data();

      pcr[0] = d1.width();

      pcr[1] = d1.height();

      int c = d1->area();

      for(int i = 0; i < c; i++)
      {

         pcr[i+2] = d1->m_pcolorref[i];

      }

      memsize o;

      o = 2 + d1->area();

      pcr[o] = d2.width();

      pcr[o+1] = d2.height();

      c = d2->area();

      for(int i = 0; i < c; i++)
      {

         pcr[i+o+2] = d2->m_pcolorref[i];

      }

      Display *display = w->display();

      Atom net_wm_icon = XInternAtom(display, "_NET_WM_ICON", False);

      Atom cardinal = XInternAtom(display, "CARDINAL", False);

      int status = XChangeProperty(display, w->Window(), net_wm_icon, cardinal, 32, PropModeReplace, (const unsigned char*) pcr, length);

      if(status != 0)
      {

         //file_put_contents("/home/camilo/window.txt", as_string((int)w->Window()));
         return false;

      }
#endif
      return true;

   }


   int window::store_name(const_char_pointer psz)
   {

      windowing_output_debug_string("\nwindow::store_name");

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      int i = XStoreName(Display(), Window(), psz);

      windowing_output_debug_string("\nwindow::store_name END");

      return i;

   }


   int window::select_input(int iInput)
   {

      windowing_output_debug_string("\nwindow::select_input");

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      int i = XSelectInput(Display(), Window(), iInput);

      windowing_output_debug_string("\nwindow::select_input END");

      return i;

   }


   int window::select_all_input()
   {

      windowing_output_debug_string("\nwindow::select_all_input");

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      int i = select_input(ExposureMask | ButtonPressMask);

      windowing_output_debug_string("\nwindow::select_all_input");

      return i;

   }


   void window::post_nc_destroy()
   {

      if (!::is_null(this))
      {

         m_pwindowing->erase_window(this);

      }

   }


   void window::set_user_interaction(::windowing::window * pimpl)
   {

//      single_lock sl(ms_pmutex, true);
//
//      if (::is_null(this))
//      {
//
//         throw ::exception(::exception("error, m_pdata cannot be nullptr to ::oswindow::set_user_interaction"));
//
//      }

      m_pwindow = pimpl;

      m_htask = pimpl->get_app()->get_os_handle();

      m_pmessagequeue = pimpl->m_puserinteraction->m_pthreadUserInteraction->aaa_get_message_queue();

      //oswindow_assign(this, pimpl);

   }


   bool window::is_child(::oswindow oswindow)
   {

      if (oswindow == nullptr || oswindow->m_pwindow == nullptr ||
          oswindow->m_pwindow->m_puserinteraction == nullptr)
      {

         return false;

      }

      if (m_pwindow == nullptr || m_pwindow->m_puserinteraction == nullptr)
      {

         return false;

      }

      return m_pwindow->m_puserinteraction->is_child(oswindow->m_pwindow->m_puserinteraction);

   }


   ::windowing::window * window::get_parent() const
   {

      return nullptr;

   }


   //virtual ::Window get_parent_handle();
   oswindow window::get_parent_oswindow() const
   {

      return nullptr;

   }


//   ::int_point window::get_mouse_cursor_position()
//   {
//
//      return m_pointCursor;
//
//   }


   ::windowing_x11::windowing * window::x11_windowing() const
   {

      return (::windowing_x11::windowing *) m_pwindowing->m_pWindowing4;

   }


   ::windowing_x11::display * window::x11_display() const
   {

      return (::windowing_x11::display *) m_pdisplay->m_pDisplay;

   }


//   ::Window window::get_parent_handle()
//   {
//
//      //single_lock slOsWindow(s_pmutex, true);
//
//      //if (::is_null(this))
//        // return 0;
//
//      return m_parent;
//
//   }


//   oswindow window::get_parent()
//   {
//
//      if (::is_null(this))
//      {
//
//         return nullptr;
//
//      }
//
//      return nullptr;
//
//   }


   void window::set_parent(::windowing::window * pwindowNewParent)
   {

      if (::is_null(this))
      {

         throw ::exception(error_failed);

      }

      if (::is_null(pwindowNewParent))
      {

         throw ::exception(error_failed);

      }

      auto pwindowx11NewParent = dynamic_cast < ::windowing_x11::window * > (pwindowNewParent);

      if (::is_null(pwindowx11NewParent))
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      XReparentWindow(Display(), Window(), pwindowx11NewParent->Window(), 0, 0);

      //return ::success;

   }


/// Post an happening from the client to the X server
   void window::send_client_event(Atom atom, unsigned int numArgs, ...)
   {

      XEvent xevent;

      unsigned int i;

      va_list argp;

      va_start(argp, numArgs);

      zero(xevent);

      xevent.xclient.type = ClientMessage;
      xevent.xclient.serial = 0;
      xevent.xclient.send_event = False;
      xevent.xclient.display = Display();
      xevent.xclient.window = Window();
      xevent.xclient.message_type = atom;
      xevent.xclient.format = 32;

      for (i = 0; i < numArgs; i++)
      {

         xevent.xclient.data.l[i] = va_arg(argp, int);

      }

      XSendEvent(Display(), RootWindow(Display(), x11_display()->m_iScreen), False,
                 SubstructureRedirectMask | SubstructureNotifyMask, &xevent);

      va_end(argp);

   }


   Atom get_window_long_atom(int nIndex);

// Change _NET_WM_STATE if Window is Mapped
   void window::_mapped_net_state_unlocked(bool add, int iScreen, Atom state1, Atom state2)
   {

      //synchronous_lock synchronouslock(user_synchronization());

      XClientMessageEvent xclient;

#define _NET_WM_STATE_REMOVE        0    /* remove/unset property */
#define _NET_WM_STATE_ADD           1    /* add/set property */
#define _NET_WM_STATE_TOGGLE        2    /* toggle property  */

      zero(xclient);
      xclient.type = ClientMessage;
      xclient.window = Window();
      xclient.message_type = x11_display()->intern_atom("_NET_WM_STATE", False);
      xclient.format = 32;
      xclient.data.l[0] = add ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
      xclient.data.l[1] = state1;
      xclient.data.l[2] = state2;
      xclient.data.l[3] = 1; /* source indication */
      xclient.data.l[4] = 0;

      if(add)
      {

         if(state1 != None)
         {
            m_atomaNetWmState.add_unique(state1);
         }
         if(state2 != None)
         {
            m_atomaNetWmState.add_unique(state2);
         }

      }
      else
      {
         if(state1 != None)
         {
            m_atomaNetWmState.erase(state1);
         }
         if(state2 != None)
         {
            m_atomaNetWmState.erase(state2);
         }

      }
      XSendEvent(Display(), RootWindow(Display(), iScreen), False, SubstructureRedirectMask | SubstructureNotifyMask,
                 (XEvent *) &xclient);
      //     XSendEvent(Display(), RootWindow(Display(), iScreen), False, 0, (XEvent *) &xclient);





   }


   void window::unmapped_net_state_raw(Atom atom1, ...)
   {

      synchronous_lock synchronouslock(user_synchronization());

      XEvent xevent;

      unsigned int i;

      va_list argp;

      va_start(argp, atom1);

      zero(xevent);

      array<Atom> atoms;

      atoms.add(atom1);

      while (true)
      {

         Atom atom = va_arg(argp, int);

         if (atom == 0)
         {

            break;

         }

         atoms.add(atom);

      }

      if (atoms.has_elements())
      {

         XChangeProperty(Display(), Window(), x11_display()->intern_atom("_NET_WM_STATE", False),
                         XA_ATOM, 32, PropModeReplace,
                         (const unsigned char *) atoms.data(), atoms.size());
      } else
      {

         XDeleteProperty(Display(), Window(), x11_display()->intern_atom("_NET_WM_STATE", False));

      }

      va_end(argp);

   }

//
//   /// this function should be called in user/main thread
//   void window::show_window(const ::e_display & edisplay, const ::user::e_activation & useractivation)
//   {
//
//      aaa_user_post([this, edisplay, useractivation]()
//                                      {
//
//                                         windowing_output_debug_string("::window::show_window 1");
//
//                                         synchronous_lock synchronouslock(user_synchronization());
//
//                                         display_lock displaylock(x11_display()->Display());
//
//                                         _show_window_unlocked(edisplay, useractivation);
//
////         XWindowAttributes attr;
////
////         if (!XGetWindowAttributes(Display(), Window(), &attr))
////         {
////
////            windowing_output_debug_string("::window::show_window 1.2");
////
////            return;
////
////            //return false;
////
////         }
////
////         if (edisplay == e_display_zoomed)
////         {
////
////            int iMapState = attr.map_state;
////
////            if (iMapState != IsViewable)
////            {
////
////               XMapWindow(Display(), Window());
////
////            }
////
////            auto atomMaxH = x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false);
////
////            auto atomMaxP = x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_penn, false);
////
////            mapped_net_state_raw(true, x11_display()->m_iScreen, atomMaxH, atomMaxP);
////
////
////
////
////         }
////         else if (edisplay == e_display_iconic)
////         {
////
////            wm_iconify_window();
////
////         }
////         else if (::is_visible(edisplay))
////         {
////
////            if (attr.map_state == IsUnmapped)
////            {
////
////               XMapWindow(Display(), Window());
////
////            }
////
////            wm_state_clear_raw(false);
////
////         }
////         else
////         {
////
////            if (attr.map_state != IsUnmapped)
////            {
////
////               XWithdrawWindow(Display(), Window(), Screen());
////
////            }
////
////         }
////
////         windowing_output_debug_string("::window::show_window 2");
//
//                                         //return true;
//
//                                      }
//
//      );
//
//      //return ::success;
//
//   }
//
//
//   void window::_show_window_unlocked(const ::e_display & edisplay, const ::user::e_activation & useractivation)
//   {
//
//      //aaa_user_post([this, edisplay, useractivation]()
//      //{
//
//      windowing_output_debug_string("::window::show_window 1");
//
////      synchronous_lock synchronouslock(user_synchronization());
////
////      display_lock displaylock(x11_display()->Display());
//
//      XWindowAttributes attr;
//
//      if (!XGetWindowAttributes(Display(), Window(), &attr))
//      {
//
//         windowing_output_debug_string("::window::show_window 1.2");
//
//         return;
//
//         //return false;
//
//      }
//
//      if (edisplay == e_display_zoomed)
//      {
//
//         int iMapState = attr.map_state;
//
//         if (iMapState != IsViewable)
//         {
//
//            XMapWindow(Display(), Window());
//
//         }
//
//         auto atomMaxH = x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false);
//
//         auto atomMaxP = x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_penn, false);
//
//         _mapped_net_state_unlocked(true, x11_display()->m_iScreen, atomMaxH, atomMaxP);
//
//      } else if (edisplay == e_display_iconic)
//      {
//
//         wm_iconify_window();
//
//      } else if (::is_visible(edisplay))
//      {
//
//         if (attr.map_state == IsUnmapped)
//         {
//
//            XMapWindow(Display(), Window());
//
//         }
//
//         _wm_state_clear_unlocked(false);
//
//      } else
//      {
//
//         if (attr.map_state != IsUnmapped)
//         {
//
//            XWithdrawWindow(Display(), Window(), Screen());
//
//         }
//
//      }
//
//      windowing_output_debug_string("::window::show_window 2");
//
//      //return true;
//
//      //}
//
//      //);
//
//      //return ::success;
//
//   }


   void window::full_screen(const ::int_rectangle & rectangle)
   {

      ::int_rectangle rBest;

      int iMonitor = m_pdisplay->get_best_monitor(&rBest, rectangle);

      windowing_output_debug_string("::window::full_screen 1");

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

//      if (x11_display()->is_null())
//      {
//
//         windowing_output_debug_string("::window::full_screen 1.1");
//
//         return;
//
//      }

      XWindowAttributes attr;

      if (!XGetWindowAttributes(Display(), Window(), &attr))
      {

         windowing_output_debug_string("::window::full_screen 1.2");

         fflush(stdout);

         throw ::exception(error_failed);

      }

      ::int_rectangle rWindow;

      rWindow.left() = attr.x;
      rWindow.top() = attr.y;
      rWindow.right() = attr.x + attr.width;
      rWindow.bottom() = attr.y + attr.height;

      if (rBest != rWindow)
      {

         m_pwindow->m_puserinteraction->place(rBest);

         XMoveResizeWindow(Display(), Window(), rBest.left(), rBest.top(), rBest.width(), rBest.height());

      }

      if (attr.map_state == IsViewable)
      {

         _mapped_net_state_unlocked(true, Screen(),
                                    x11_display()->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);

      } else
      {

         unmapped_net_state_raw(x11_display()->intern_atom(::x11::e_atom_net_wm_state_fullscreen, false), 0);

         XMapWindow(Display(), Window());

      }

      windowing_output_debug_string("::window::full_screen 2");

      ::fflush(stdout);

      //return ::success;

   }


   void window::exit_iconify()
   {

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      XWindowAttributes attr;

      if (!XGetWindowAttributes(Display(), Window(), &attr))
      {

         windowing_output_debug_string("::window::exit_full_screen 1.2");

         fflush(stdout);

         throw ::exception(error_failed);

      }

      if (attr.map_state == IsViewable)
      {

         _mapped_net_state_unlocked(false, Screen(),
                                    x11_display()->intern_atom(::x11::e_atom_net_wm_state_hidden, false), 0);

      }

      //return ::success;

   }


   void window::exit_full_screen()
   {

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      XWindowAttributes attr;

      if (!XGetWindowAttributes(Display(), Window(), &attr))
      {

         windowing_output_debug_string("::window::exit_full_screen 1.2");

         fflush(stdout);

         throw ::exception(error_failed);

      }

      if (attr.map_state == IsViewable)
      {

         _mapped_net_state_unlocked(false, Screen(), x11_display()->intern_atom("_NET_WM_STATE_FULLSCREEN", false), 0);

      }

      //return ::success;

   }


   void window::exit_zoomed()
   {

//      synchronous_lock sl(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());
//
//      XWindowAttributes attr;
//
//      if (!XGetWindowAttributes(Display(), Window(), &attr))
//      {
//
//         windowing_output_debug_string("::window::exit_zoomed 1.2");
//
//         fflush(stdout);
//
//         throw ::exception(error_failed);
//
//      }
//
//      if (attr.map_state == IsViewable)
//      {
//
//         mapped_net_state_raw(false, Screen(),
//                              x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false),
//                              x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_penn, false));
//
//      }

      //return success;

   }


//   iptr window::get_window_long_ptr(int nIndex)
//   {
//
//      return m_pwindow->get_window_long_ptr(nIndex);
//
//   }


//   iptr window::set_window_long_ptr(int nIndex, iptr i)
//   {
//
//      return m_pwindow->set_window_long_ptr(nIndex, i);
//
//      //iptr iOld = m_plongmap->operator[](nIndex);
//
//      //   if(nIndex == GWL_EXSTYLE)
//      //   {
//      //
//      //      if(is_different((l & WS_EX_TOOLWINDOW), (m_plongmap->operator[](nIndex) & WS_EX_TOOLWINDOW)))
//      //      {
//      //
//      //         wm_toolwindow(this, (l & WS_EX_TOOLWINDOW) != 0);
//      //
//      //      }
//      //
//      //   }
//
//      //m_plongmap->operator[](nIndex) = i;
//
//      //return iOld;
//
//   }


   bool window::client_to_screen(::int_point * ppoint)
   {

      return true;

   }


   bool window::screen_to_client(::int_point * ppoint)
   {

      return true;

   }


   bool window::get_state(long & lState)
   {

      windowing_output_debug_string("::window::get_state 1");

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      return _get_wm_state_unlocked(lState);

   }


   bool window::_get_wm_state_unlocked(long & lState)
   {

      static const long WM_STATE_ELEMENTS = 2L;

      if (x11_display()->m_atomWmState == None)
      {

         x11_display()->m_atomWmState = x11_display()->intern_atom("WM_STATE", false);

      }

      Atom actual_type = 0;

      int actual_format = 0;

      unsigned long nitems = 0;

      unsigned long leftover = 0;

      unsigned char * p = nullptr;

      auto atomWmState = x11_display()->m_atomWmState;

      int status = XGetWindowProperty(Display(), Window(), atomWmState, 0L,
                                        WM_STATE_ELEMENTS, False, AnyPropertyType,
                                  &actual_type,
                                  &actual_format, &nitems, &leftover, &p);

      if (status != 0)
      {

         windowing_output_debug_string("::window::_get_state_unlocked 2");

         return false;

      }

      long lStatus = -1;

      if (p != nullptr)
      {

         lStatus = (long) *p;

      }

      XFree(p);

      windowing_output_debug_string("::window::_get_state_unlocked 1.1");

      lState = lStatus;

      return true;

   }


   bool window::is_iconic()
   {

#ifdef XDISPLAY_LOCK_LOG

      b_prevent_xdisplay_lock_log = true;

#endif

      long lState = -1;

      if(!get_state(lState))
      {

         return false;

      }

      bool bIconic = lState == IconicState;

#ifdef XDISPLAY_LOCK_LOG

      b_prevent_xdisplay_lock_log = false;

#endif

      return lState;

   }




   bool window::is_window_visible()
   {

      windowing_output_debug_string("::window::is_window_visible 1");

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      if (x11_display()->is_null())
      {

         windowing_output_debug_string("::window::is_window_visible 1.1");

         return false;

      }

      return _is_window_visible_unlocked();

//      XWindowAttributes attr;
//
//      if (!XGetWindowAttributes(Display(), Window(), &attr))
//      {
//
//         windowing_output_debug_string("::window::is_window_visible 1.2");
//
//         return false;
//
//      }
//
//      windowing_output_debug_string("::window::is_window_visible 2");
//
//      return attr.map_state == IsViewable;

   }


   bool window::_is_window_visible_unlocked()
   {

//      windowing_output_debug_string("::window::is_window_visible 1");
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());
//
//      if (x11_display()->is_null())
//      {
//
//         windowing_output_debug_string("::window::is_window_visible 1.1");
//
//         return false;
//
//      }

      XWindowAttributes attr;

      if (!XGetWindowAttributes(Display(), Window(), &attr))
      {

         windowing_output_debug_string("::window::is_window_visible 1.2");

         return false;

      }

      windowing_output_debug_string("::window::is_window_visible 2");

      return attr.map_state == IsViewable;

   }


   bool window::is_destroying()
   {

      if (::is_null(this))
      {

         return true;

      }

      if (m_pwindow == nullptr)
      {

         return true;

      }

      if (!m_pwindow->m_puserinteraction->m_bUserElementOk)
      {

         return true;

      }

      return false;

   }


#undef SET_WINDOW_POS_LOG


//   bool window::set_window_pos(class ::zorder zorder, int x, int y, int cx, int cy, unsigned int nFlags)
//   {
//
//      bool bOk = false;
//
//
//                  bOk = _set_window_pos(zorder, x, y, cx, cy, nFlags);
//
//               });
//
//      return bOk;
//
//   }


   ::e_status window::set_window_icon(const ::file::path & path)
   {


      Atom net_wm_icon = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);

      Atom cardinal = x11_display()->intern_atom("STRING", False);

      int ixa = XA_STRING;

      int status = XChangeProperty(
         Display(),
         Window(),
         net_wm_icon,
         ixa,
         8,
         PropModeReplace,
         (const unsigned char *) (const_char_pointer )path,
         path.length());

      informationf("\nfreebsd::interaction_impl::bamf_set_icon END");

      fflush(stdout);

      if (status != 0)
      {

         return ::error_failed;

      }

      return ::success;

   }


//   void oswindow_data::wm_full_screen(const ::int_rectangle & rectangle)
//   {
//
//      ::int_rectangle rBest;
//
//      int iMonitor = best_xinerama_monitor(m_pwindow->m_puserinteraction, rectangle, rBest);
//
//      windowing_output_debug_string("::oswindow_data::full_screen 1");
//
//      xdisplay d(display());
//
//      if(d.is_null())
//      {
//
//         windowing_output_debug_string("::oswindow_data::full_screen 1.1");
//
//         return;
//
//      }
//
//      XWindowAttributes attr;
//
//      if(!XGetWindowAttributes(display(), window(), &attr))
//      {
//
//         windowing_output_debug_string("::oswindow_data::full_screen 1.2");
//
//         fflush(stdout);
//
//         return;
//
//      }
//
//      ::int_rectangle rWindow;
//
//      rWindow.left()      = attr.x;
//      rWindow.top()       = attr.y;
//      rWindow.right()     = attr.x    + attr.width;
//      rWindow.bottom()    = attr.y    + attr.height;
//
//      if(rBest != rWindow)
//      {
//
//         m_pwindow->m_puserinteraction->place(rBest);
//
//         XMoveResizeWindow(d, m_window, rBest.left(), rBest.top(), rBest.width(), rBest.height());
//
//      }
//
//      if(attr.map_state == IsViewable)
//      {
//
//         mapped_net_state_raw(true, d, window(), m_iScreen, intern_atom(net_wm_state_fullscreen, false), 0);
//
//      }
//      else
//      {
//
//         unmapped_net_state_raw(d, window(), intern_atom(net_wm_state_fullscreen, false), 0);
//
//         XMapWindow(display(), window());
//
//      }
//
//      windowing_output_debug_string("::oswindow_data::full_screen 2");
//
//      ::fflush(stdout);
//
//   }
//


   ::e_status window::x11_post_message(MESSAGE & msg)
   {

      try
      {

         if (msg.oswindow == nullptr)
         {

            auto pcontext = m_papplication;

            pcontext->post_message(msg.id(), msg.wParam, msg.lParam);

         } else
         {

            if (msg.oswindow != nullptr && msg.oswindow->m_pwindow != nullptr &&
                msg.oswindow->m_pwindow->m_puserinteraction != nullptr)
            {

               ::user::interaction * pinteraction = msg.oswindow->m_pwindow->m_puserinteraction;

               pinteraction->post_message(msg.id(), msg.wParam, msg.lParam);

            }

         }

      }
      catch (...)
      {

      }

      return ::success;

   }


   ::e_status window::post_ui_message(const MESSAGE & message)
   {

      ::oswindow oswindow = message.oswindow;

      ASSERT(oswindow != nullptr);

      ::user::interaction * pinteraction = oswindow->m_pwindow->m_puserinteraction;

      ::thread * pthread = nullptr;

      if (::is_set(pinteraction))
      {

         pthread = pinteraction->m_pthreadUserInteraction;

      }

      if (::is_null(pthread))
      {

         return ::error_failed;

      }

      auto pmessagequeue = pthread->m_pmessagequeue.get();

      if (pmessagequeue == nullptr)
      {

         if (message.m_emessage == e_message_quit)
         {

            return ::error_failed;

         }

         pmessagequeue = pthread->aaa_get_message_queue();

      }

      if (pmessagequeue == nullptr)
      {

         return error_failed;

      }

      synchronous_lock ml(pmessagequeue->synchronization());

      if (message.m_emessage == e_message_quit)
      {

         informationf("e_message_quit thread");

      }

      if (message.m_emessage == e_message_left_button_down)
      {

         informationf("post_ui_message::e_message_left_button_down\n");

      } else if (message.m_emessage == e_message_left_button_up)
      {

         informationf("post_ui_message::e_message_left_button_up\n");

      }

      pmessagequeue->m_messagea.add(message);

      pmessagequeue->m_happeningNewMessage.set_happening();

      return ::success;

   }


   ::e_status window::mq_remove_window_from_all_queues()
   {

      ::user::interaction * pinteraction = m_pwindow->m_puserinteraction;

      if (pinteraction == nullptr)
      {

         return error_failed;

      }

      if (pinteraction->get_app() == nullptr)
      {

         return error_failed;

      }

      itask idthread = pinteraction->get_app()->get_itask();

      message_queue * pmq = aaa_get_message_queue(idthread, false);

      if (pmq == nullptr)
      {

         return error_failed;

      }

      synchronous_lock ml(pmq->synchronization());

      pmq->m_messagea.predicate_erase([this](MESSAGE & item)
                                      {

                                         return item.oswindow == this;

                                      });

      return ::success;

   }


   bool window::set_window_position(const class ::zorder & zorder, int x, int y, int cx, int cy,
                                    const ::user::e_activation & useractivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                                    ::e_display edisplay)
   {

      synchronous_lock sl(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      information() << "windowing_x11 window::set_window_position ";

      return _set_window_position_unlocked(zorder, x, y, cx, cy, useractivation, bNoZorder, bNoMove, bNoSize,
                                           edisplay);

   }


   bool window::_set_window_position_unlocked(const class ::zorder & zorder, int x, int y, int cx, int cy,
                                              const ::user::e_activation & useractivation, bool bNoZorder, bool bNoMove,
                                              bool bNoSize, ::e_display edisplay)
   {

      windowing_output_debug_string("::window::set_window_pos 1");

      XWindowAttributes attrs = {};

      if (!XGetWindowAttributes(Display(), Window(), &attrs))
      {

         windowing_output_debug_string("::window::set_window_pos 1.1 xgetwindowattr failed");

         return false;

      }

      if (windowing()->is_screen_visible(edisplay))
      {

         if (attrs.map_state == IsUnmapped)
         {

            windowing_output_debug_string("::window::set_window_pos Mapping Window 1.2");

            XMapWindow(Display(), Window());

         }

         if (!XGetWindowAttributes(Display(), Window(), &attrs))
         {

            windowing_output_debug_string("::window::set_window_pos 1.3 xgetwindowattr failed");

            return false;

         }

      }

      bool bMove = !bNoMove;

      bool bSize = !bNoSize;

      if (bMove)
      {

         if (bSize)
         {

            windowing_output_debug_string("::window::set_window_pos Move Resize Window 1.4");

#ifdef SET_WINDOW_POS_LOG

            informationf("XMoveResizeWindow (%Display(), %d) - (%Display(), %d)", x, y, cx, cy);

#endif

            if (cx <= 0 || cy <= 0)
            {

               cx = 1;

               cy = 1;

#ifdef SET_WINDOW_POS_LOG

               informationf("Changing parameters... (%d, %d) - (%d, %d)", x, y, cx, cy);

#endif

            }

//            if (x < 100 || y < 100)
//            {
//
//               informationf("XMoveResizeWindow x or y less than 100 ... (Win=%d) (%d, %d) - (%d, %d)", Window(), x, y, cx, cy);
//
//            }

            //informationf("XMoveResizeWindow (Win=%d) (%d, %d) - (%d, %d) - (%d, %d)", Window(), x, y, cx, cy, x + cx, y + cy);

            //information() << node()->get_callstack();

            XMoveResizeWindow(Display(), Window(), x, y, cx, cy);


//            if(m_pwindow->m_puserinteraction->const_layout().design().display() == e_display_zoomed) {
//
//               x11_windowing()->_defer_position_and_size_message(m_oswindow);
//
//
//            }


         } else
         {

            if (x < 100 || y < 100)
            {

               informationf("XMoveWindow x or y less than 100 ... (Win=%d) (%d, %d) - (%d, %d)", Window(), x, y, cx, cy);

            }

            windowing_output_debug_string("::window::set_window_pos Move Window 1.4.1");

            XMoveWindow(Display(), Window(), x, y);

         }

      } else if (bSize)
      {

         windowing_output_debug_string("::window::set_window_pos Resize Window 1.4.2");

         XResizeWindow(Display(), Window(), cx, cy);

      }

      //   if(bMove || bSize)
      //   {
      //
      //      if(attrs.override_redirect)
      //      {
      //
      //         if(!(m_pwindow->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning))
      //         {
      //
      //            XSetWindowAttributes set;
      //
      //            set.override_redirect = False;
      //
      //            if(!XChangeWindowAttributes(Display(), Window(), CWOverrideRedirect, &set))
      //            {
      //
      //               information() << "freebsd::interaction_impl::_native_create_window_ex failed to clear override_redirect";
      //
      //            }
      //
      //         }
      //
      //      }
      //
      //   }


      if (!windowing()->is_screen_visible(edisplay))
      {

         if (attrs.map_state == IsViewable)
         {

            windowing_output_debug_string("::window::set_window_pos Withdraw Window 1.4.3");

            XWithdrawWindow(Display(), Window(), Screen());

         }

      }

      if (XGetWindowAttributes(Display(), Window(), &attrs) == 0)
      {

         windowing_output_debug_string("::window::set_window_pos xgetwndattr 1.4.4");

         return false;

      }

      if (attrs.map_state == IsViewable || windowing()->is_screen_visible(edisplay))
      {

         if (!bNoZorder)
         {

            if (zorder.m_ezorder == e_zorder_top_most)
            {

               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 1)
               {

                  _wm_state_above_unlocked(true);

               }

               XRaiseWindow(Display(), Window());

            } else if (zorder.m_ezorder == e_zorder_top)
            {

               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 0
                   || net_wm_state(::x11::e_atom_net_wm_state_below) != 0
                   || net_wm_state(::x11::e_atom_net_wm_state_hidden) != 0
                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_horz) != 0
                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_penn) != 0
                   || net_wm_state(::x11::e_atom_net_wm_state_fullscreen) != 0)
               {

                  _wm_state_clear_unlocked(false);

               }

               XRaiseWindow(Display(), Window());

            } else if (zorder.m_ezorder == e_zorder_bottom)
            {

               if (net_wm_state(::x11::e_atom_net_wm_state_below) != 1)
               {

                  _wm_state_below_unlocked(true);

               }

               XLowerWindow(Display(), Window());

            }

         }

         //m_pwindow->m_puserinteraction->ModifyStyle(0, WS_VISIBLE, 0);

      }
//      else
//      {
//
//         //m_pwindow->m_puserinteraction->ModifyStyle(WS_VISIBLE, 0, 0);
//
//      }

      //m_pwindow->on_change_visibility();

      windowing_output_debug_string("::window::set_window_pos 2");

      return true;

   }


//   bool window::_set_window_position_unlocked(const class ::zorder & zorder, int x, int y, int cx, int cy,
//                                              const ::user::e_activation & useractivation, bool bNoZorder, bool bNoMove,
//                                              bool bNoSize, bool bShow, bool bHide)
//   {
//
//      windowing_output_debug_string("::window::set_window_pos 1");
//
//      XWindowAttributes attrs = {};
//
//      if (!XGetWindowAttributes(Display(), Window(), &attrs))
//      {
//
//         windowing_output_debug_string("::window::set_window_pos 1.1 xgetwindowattr failed");
//
//         return false;
//
//      }
//
//      if (bShow)
//      {
//
//         if (attrs.map_state == IsUnmapped)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Mapping Window 1.2");
//
//            XMapWindow(Display(), Window());
//
//         }
//
//         if (!XGetWindowAttributes(Display(), Window(), &attrs))
//         {
//
//            windowing_output_debug_string("::window::set_window_pos 1.3 xgetwindowattr failed");
//
//            return false;
//
//         }
//
//      }
//
//      bool bMove = !bNoMove;
//
//      bool bSize = !bNoSize;
//
//      if (bMove)
//      {
//
//         if (bSize)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Move Resize Window 1.4");
//
//#ifdef SET_WINDOW_POS_LOG
//
//            informationf("XMoveResizeWindow (%Display(), %d) - (%Display(), %d)", x, y, cx, cy);
//
//#endif
//
//            if (cx <= 0 || cy <= 0)
//            {
//
//               cx = 1;
//
//               cy = 1;
//
//#ifdef SET_WINDOW_POS_LOG
//
//               informationf("Changing parameters... (%d, %d) - (%d, %d)", x, y, cx, cy);
//
//#endif
//
//            }
//
////            if (x < 100 || y < 100)
////            {
////
////               informationf("XMoveResizeWindow x or y less than 100 ... (Win=%d) (%d, %d) - (%d, %d)", Window(), x, y, cx, cy);
////
////            }
//
//            //informationf("XMoveResizeWindow (Win=%d) (%d, %d) - (%d, %d) - (%d, %d)", Window(), x, y, cx, cy, x + cx, y + cy);
//
//            //information() << node()->get_callstack();
//
//            XMoveResizeWindow(Display(), Window(), x, y, cx, cy);
//
//
////            if(m_pwindow->m_puserinteraction->const_layout().design().display() == e_display_zoomed) {
////
////               x11_windowing()->_defer_position_and_size_message(m_oswindow);
////
////
////            }
//
//
//         } else
//         {
//
//            if (x < 100 || y < 100)
//            {
//
//               informationf("XMoveWindow x or y less than 100 ... (Win=%d) (%d, %d) - (%d, %d)", Window(), x, y, cx, cy);
//
//            }
//
//            windowing_output_debug_string("::window::set_window_pos Move Window 1.4.1");
//
//            XMoveWindow(Display(), Window(), x, y);
//
//         }
//
//      } else if (bSize)
//      {
//
//         windowing_output_debug_string("::window::set_window_pos Resize Window 1.4.2");
//
//         XResizeWindow(Display(), Window(), cx, cy);
//
//      }
//
//      //   if(bMove || bSize)
//      //   {
//      //
//      //      if(attrs.override_redirect)
//      //      {
//      //
//      //         if(!(m_pwindow->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning))
//      //         {
//      //
//      //            XSetWindowAttributes set;
//      //
//      //            set.override_redirect = False;
//      //
//      //            if(!XChangeWindowAttributes(Display(), Window(), CWOverrideRedirect, &set))
//      //            {
//      //
//      //               information() << "freebsd::interaction_impl::_native_create_window_ex failed to clear override_redirect";
//      //
//      //            }
//      //
//      //         }
//      //
//      //      }
//      //
//      //   }
//
//
//      if (bHide)
//      {
//
//         if (attrs.map_state == IsViewable)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Withdraw Window 1.4.3");
//
//            XWithdrawWindow(Display(), Window(), Screen());
//
//         }
//
//      }
//
//      if (XGetWindowAttributes(Display(), Window(), &attrs) == 0)
//      {
//
//         windowing_output_debug_string("::window::set_window_pos xgetwndattr 1.4.4");
//
//         return false;
//
//      }
//
//      if (attrs.map_state == IsViewable || bShow)
//      {
//
//         if (!bNoZorder)
//         {
//
//            if (zorder.m_ezorder == e_zorder_top_most)
//            {
//
//               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 1)
//               {
//
//                  _wm_state_above_unlocked(true);
//
//               }
//
//               XRaiseWindow(Display(), Window());
//
//            } else if (zorder.m_ezorder == e_zorder_top)
//            {
//
//               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_below) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_hidden) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_horz) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_penn) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_fullscreen) != 0)
//               {
//
//                  _wm_state_clear_unlocked(false);
//
//               }
//
//               XRaiseWindow(Display(), Window());
//
//            } else if (zorder.m_ezorder == e_zorder_bottom)
//            {
//
//               if (net_wm_state(::x11::e_atom_net_wm_state_below) != 1)
//               {
//
//                  _wm_state_below_unlocked(true);
//
//               }
//
//               XLowerWindow(Display(), Window());
//
//            }
//
//         }
//
//         //m_pwindow->m_puserinteraction->ModifyStyle(0, WS_VISIBLE, 0);
//
//      }
////      else
////      {
////
////         //m_pwindow->m_puserinteraction->ModifyStyle(WS_VISIBLE, 0, 0);
////
////      }
//
//      //m_pwindow->on_change_visibility();
//
//      windowing_output_debug_string("::window::set_window_pos 2");
//
//      return true;
//
//   }


   bool window::_configure_window_unlocked(const class ::zorder & zorder,
                                              const ::user::e_activation & useractivation, bool bNoZorder, ::e_display edisplay)
   {

      windowing_output_debug_string("::window::_configure_window_unlocked 1");

      m_atomaNetWmState = _get_net_wm_state_unlocked();

      if (windowing()->is_screen_visible(edisplay))
      {

         if (m_xwindowattributes.map_state == IsUnmapped)
         {

            information() << "_configure_window_unlocked XMapWindow";

            windowing_output_debug_string("::window::set_window_pos Mapping Window 1.2");

            XMapWindow(Display(), Window());

            if (!XGetWindowAttributes(Display(), Window(), &m_xwindowattributes))
            {

               windowing_output_debug_string("::window::set_window_pos 1.3 xgetwindowattr failed");

               return false;

            }

         }

      }

      if (edisplay != e_display_zoomed)
      {

         auto atomMaxH = x11_display()->m_atomNetWmStateMaximizedHorz;

         auto atomMaxP = x11_display()->m_atomNetWmStateMaximizedVert;

         for(auto & a : m_atomaNetWmState)
         {

            informationf("atom_name: %s", XGetAtomName(Display(), a));

         }

         if(m_atomaNetWmState.contains(atomMaxH) || m_atomaNetWmState.contains(atomMaxP))
         {

            information() << "_configure_window_unlocked Clearing Maximized States";

            _wm_state_clear_unlocked(false);

         }

      }

      if(edisplay == e_display_iconic)
      {

         information() << "_configure_window_unlocked XIconifyWindow";

         XIconifyWindow(Display(), Window(), Screen());

         return true;

      }
      else if (edisplay == e_display_zoomed)
      {

         auto atomMaxH = x11_display()->m_atomNetWmStateMaximizedHorz;

         auto atomMaxP = x11_display()->m_atomNetWmStateMaximizedVert;

         if (!m_atomaNetWmState.contains(atomMaxH) || !m_atomaNetWmState.contains(atomMaxP))
         {

            information() << "_configure_window_unlocked Setting Maximized States";

            _mapped_net_state_unlocked(true, x11_display()->m_iScreen, atomMaxH, atomMaxP);

//            comparable_array<Atom> atoma;
//
//            auto atomList = x11_display()->m_atomNetWmState;
//
//            if (atomList != None)
//            {
//
//               Atom actual_type;
//
//               int actual_format;
//
//               unsigned long int bytes_after;
//
//               Atom * patoms = nullptr;
//
//               long unsigned int num_items = 0;
//
//               XGetWindowProperty(Display(), Window(), atomList, 0, 1024,
//                                  False, XA_ATOM, &actual_type, &actual_format,
//                                  &num_items,
//                                  &bytes_after, (unsigned char **) &patoms);
//
//               atoma.set_size(num_items);
//
//               memory_copy(atoma.data(), patoms, atoma.get_size_in_bytes());
//
//               XFree(patoms);
//
//
//            }


         }

      }

      if (!windowing()->is_screen_visible(edisplay))
      {

         if (m_xwindowattributes.map_state == IsViewable)
         {

            information() << "_configure_window_unlocked XWithdrawWindow";

            windowing_output_debug_string("::window::set_window_pos Withdraw Window 1.4.3");

            XWithdrawWindow(Display(), Window(), Screen());

            if (XGetWindowAttributes(Display(), Window(), &m_xwindowattributes) == 0)
            {

               windowing_output_debug_string("::window::set_window_pos xgetwndattr 1.4.4");

               return false;

            }

         }

      }

      if (m_xwindowattributes.map_state == IsViewable || windowing()->is_screen_visible(edisplay))
      {

         if (!bNoZorder)
         {

            if (zorder.m_ezorder == e_zorder_top_most)
            {

               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 1)
               {

                  _wm_state_above_unlocked(true);

               }

               information() << "_configure_window_unlocked XRaiseWindow";

               XRaiseWindow(Display(), Window());

            }
            else if (zorder.m_ezorder == e_zorder_top)
            {

               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 0
                   || net_wm_state(::x11::e_atom_net_wm_state_below) != 0
                   || net_wm_state(::x11::e_atom_net_wm_state_hidden) != 0
                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_horz) != 0
                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_penn) != 0
                   || net_wm_state(::x11::e_atom_net_wm_state_fullscreen) != 0)
               {

                  _wm_state_clear_unlocked(false);

               }

               information() << "_configure_window_unlocked XRaiseWindow";

               XRaiseWindow(Display(), Window());

            }
            else if (zorder.m_ezorder == e_zorder_bottom)
            {

               if (net_wm_state(::x11::e_atom_net_wm_state_below) != 1)
               {

                  _wm_state_below_unlocked(true);

               }

               information() << "_configure_window_unlocked XLowerWindow";

               XLowerWindow(Display(), Window());

            }

         }

      }

      windowing_output_debug_string("::window::set_window_pos 2");

      return true;

   }


   bool window::_strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize)
   {

      bool bMove = !bNoMove;

      bool bSize = !bNoSize;

      m_pointWindow.x() = x;

      m_pointWindow.y() = y;

      m_sizeWindow.cx() = cx;

      m_sizeWindow.cy() = cy;

      if (bMove)
      {

         if (bSize)
         {

            windowing_output_debug_string("::window::set_window_pos Move Resize Window 1.4");

#ifdef SET_WINDOW_POS_LOG

            informationf("XMoveResizeWindow (%Display(), %d) - (%Display(), %d)", x, y, cx, cy);

#endif

            if (cx <= 0 || cy <= 0)
            {

               cx = 1;

               cy = 1;

#ifdef SET_WINDOW_POS_LOG

               //informationf("Changing parameters... (%d, %d) - (%d, %d)", x, y, cx, cy);

#endif

            }

//            if (x < 100 || y < 100)
//            {
//
//               informationf("XMoveResizeWindow x or y less than 100 ... (Win=%d) (%d, %d) - (%d, %d)", Window(), x, y, cx, cy);
//
//            }

            informationf("XMoveResizeWindow (Win=%d) (%d, %d) - (%d, %d) - (%d, %d)", Window(), x, y, cx, cy, x + cx, y + cy);

            //information() << node()->get_callstack();

            XMoveResizeWindow(Display(), Window(), x, y, cx, cy);


//            if(m_pwindow->m_puserinteraction->const_layout().design().display() == e_display_zoomed) {
//
//               x11_windowing()->_defer_position_and_size_message(m_oswindow);
//
//
//            }


         }
         else
         {

            if (x < 100 || y < 100)
            {

               //informationf("XMoveWindow x or y less than 100 ... (Win=%d) (%d, %d) - (%d, %d)", Window(), x, y, cx, cy);

            }

            windowing_output_debug_string("::window::set_window_pos Move Window 1.4.1");

            informationf("XMoveWindow (Win=%d) (%d, %d)", Window(), x, y);

            XMoveWindow(Display(), Window(), x, y);

         }

      }
      else if (bSize)
      {

         windowing_output_debug_string("::window::set_window_pos Resize Window 1.4.2");

         informationf("XResizeWindow (Win=%d) (%d, %d)", Window(), cx, cy);

         //information() << node()->get_callstack();

         XResizeWindow(Display(), Window(), cx, cy);

      }

      //   if(bMove || bSize)
      //   {
      //
      //      if(attrs.override_redirect)
      //      {
      //
      //         if(!(m_pwindow->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning))
      //         {
      //
      //            XSetWindowAttributes set;
      //
      //            set.override_redirect = False;
      //
      //            if(!XChangeWindowAttributes(Display(), Window(), CWOverrideRedirect, &set))
      //            {
      //
      //               information() << "freebsd::interaction_impl::_native_create_window_ex failed to clear override_redirect";
      //
      //            }
      //
      //         }
      //
      //      }
      //
      //   }


//      if (bHide)
//      {
//
//         if (attrs.map_state == IsViewable)
//         {
//
//            windowing_output_debug_string("::window::set_window_pos Withdraw Window 1.4.3");
//
//            XWithdrawWindow(Display(), Window(), Screen());
//
//         }
//
//      }
//
//      if (XGetWindowAttributes(Display(), Window(), &attrs) == 0)
//      {
//
//         windowing_output_debug_string("::window::set_window_pos xgetwndattr 1.4.4");
//
//         return false;
//
//      }
//
//      if (attrs.map_state == IsViewable || bShow)
//      {
//
//         if (!bNoZorder)
//         {
//
//            if (zorder.m_ezorder == e_zorder_top_most)
//            {
//
//               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 1)
//               {
//
//                  _wm_state_above_unlocked(true);
//
//               }
//
//               XRaiseWindow(Display(), Window());
//
//            } else if (zorder.m_ezorder == e_zorder_top)
//            {
//
//               if (net_wm_state(::x11::e_atom_net_wm_state_above) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_below) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_hidden) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_horz) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_maximized_penn) != 0
//                   || net_wm_state(::x11::e_atom_net_wm_state_fullscreen) != 0)
//               {
//
//                  _wm_state_clear_unlocked(false);
//
//               }
//
//               XRaiseWindow(Display(), Window());
//
//            } else if (zorder.m_ezorder == e_zorder_bottom)
//            {
//
//               if (net_wm_state(::x11::e_atom_net_wm_state_below) != 1)
//               {
//
//                  _wm_state_below_unlocked(true);
//
//               }
//
//               XLowerWindow(Display(), Window());
//
//            }
//
//         }
//
//         //m_pwindow->m_puserinteraction->ModifyStyle(0, WS_VISIBLE, 0);
//
//      }
////      else
////      {
////
////         //m_pwindow->m_puserinteraction->ModifyStyle(WS_VISIBLE, 0, 0);
////
////      }
//
//      //m_pwindow->on_change_visibility();

      windowing_output_debug_string("::window::_strict_set_window_position_unlocked 2");

      //information() << "::windowing_x11::window::_strict_set_window_position_unlocked";

      return true;

   }


//   int_bool window::show_window(
//                        const ::e_display &edisplay,
//                        const ::user::e_activation &useractivation
//   )
//   {
//
//      x11_sync([oswindow, edisplay, useractivation]()
//               {
//
//                  return oswindow->
//                     show_window(edisplay, useractivation
//                  );
//
//               });
//
//      return true;
//
//   }


//   iptr get_window_long_ptr(window *pdata, int
//   nIndex)
//   {
//
//      return pdata->
//         get_window_long_ptr(nIndex);
//
//   }


//   iptr set_window_long_ptr(window *pdata, int
//   nIndex,
//                            iptr i
//   )
//   {
//
//      return pdata->
//         set_window_long_ptr(nIndex, i
//      );
//
//   }


   void window::set_window_text(const ::scoped_string & scopedstr)
   {

//      m_strWindowText = pszString;

      //windowing_output_debug_string("\nfreebsd::interaction_impl::set_window_text");

      //fflush(stdout);

      //x11_store_name(m_oswindow, m_strWindowText);

      x11_store_name(scopedstr);

      //windowing_output_debug_string("\nfreebsd::interaction_impl::set_window_text END");

      //fflush(stdout);

   }


   void window::set_tool_window(bool bSet)
   {

      wm_toolwindow(bSet);

      //return ::success;

   }


   void window::set_mouse_cursor2(::windowing::cursor * pcursor)
   {

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      Atom net_wm_icon = x11_display()->intern_atom("_BAMF_DESKTOP_FILE", False);

      Atom cardinal = x11_display()->intern_atom("STRING", False);

      int ixa = XA_STRING;

      ::file::path path = pcursor->get_file_path();

      int status = XChangeProperty(
         Display(),
         Window(),
         net_wm_icon,
         ixa,
         8,
         PropModeReplace,
         (const unsigned char *) (const_char_pointer )path,
         path.length());

      informationf("\nfreebsd::interaction_impl::bamf_set_icon END");

      fflush(stdout);

      if (status != 0)
      {

         throw ::exception(error_failed);

      }

      //return true;

   }


   void window::aaa_set_mouse_cursor(::windowing::cursor * pcursor)
   {

      if (::is_null(pcursor))
      {

         throw ::exception(error_null_pointer);

      }

      auto pcursorx11 = dynamic_cast < ::windowing_x11::cursor * >(pcursor);

      if (::is_null(pcursorx11))
      {

         throw ::exception(error_null_pointer);

      }


      aaa_user_post([this, pcursorx11]()
                                   {

                                      if (!pcursorx11->m_cursor)
                                      {

                                         //auto estatus =
                                         //
                                         pcursorx11->aaa_create_os_cursor();

//         if(!estatus)
//         {
//
//            return estatus;
//
//         }

                                      }

                                      if (m_cursorLast == pcursorx11->m_cursor)
                                      {

                                         //return true;

                                         return;

                                      }

                                      synchronous_lock sl(user_synchronization());

                                      windowing_output_debug_string("::SetCursor 1");

                                      display_lock displaylock(x11_display()->Display());;

                                      XDefineCursor(Display(), Window(), pcursorx11->m_cursor);

                                      m_cursorLast = pcursorx11->m_cursor;

                                   });

      //return true;

   }


   string window::x11_get_name()
   {

      return ::x11_get_name(Display(), Window());

   }


   bool window::x11_get_window_rect(::int_rectangle * prectangle)
   {

      return ::x11_get_window_rect(Display(), Window(), prectangle);

   }


   ::e_status window::window_rectangle(::int_rectangle * prectangle)
   {

      return x11_get_window_rect(prectangle) ? ::success : ::error_failed;

   }


   bool window::x11_get_client_rect(::int_rectangle * prectangle)
   {

      return ::x11_get_client_rect(Display(), Window(), prectangle);

   }


   ::e_status window::rectangle(::int_rectangle * prectangle)
   {

      return x11_get_client_rect(prectangle) ? ::success : error_failed;

   }


   void window::upper_window_rects(int_rectangle_array & ra)
   {

      synchronous_lock synchronouslock(user_synchronization());

      ra.erase_all();

      windowing_output_debug_string("::GetFocus 1");

#ifdef display_lock_LOCK_LOG

      b_prevent_display_lock_lock_log = false;

#endif

      display_lock displaylock(x11_display()->Display());

      windowing_output_debug_string("::GetFocus 1.01");

      auto windowa = x11_display()->x11_window_list();

      if (windowa.last() == Window())
      {

         return;

      }

      auto iFind = windowa.find_last(Window());

      if (not_found(iFind))
      {

         return;

      }

      ::int_rectangle rectangle;

      x11_get_window_rect(&rectangle);

//r = oswindow->m_pwindow->m_puserinteraction->window_rectangle();

//string strTopic = x11_get_name(x11_display(), Window());

      ::int_rectangle rectangleTest;

      for (iFind++; iFind < windowa.get_size(); iFind++)
      {

//string strItem = x11_get_name(x11_display(), windowa[iFind]);

         ::int_rectangle rectangleHigher;

         if (::x11_get_window_rect(Display(), windowa[iFind], &rectangleHigher))
         {

            ra.add(rectangleHigher);

         }

      }

   }


   void window::set_active_window()
   {

      synchronous_lock synchronouslock(user_synchronization());

      {

         windowing_output_debug_string("::set_active_window 1");

         display_lock displaylock(x11_display()->Display());

         _set_active_window_unlocked();

//         XEvent xev;
//
//         zero(xev);
//
//         auto windowRoot = DefaultRootWindow(Display());
//
//         Atom atomActiveWindow = x11_display()->intern_atom("_NET_ACTIVE_WINDOW", False);
//
//         xev.xclient.type = ClientMessage;
//         xev.xclient.send_event = True;
//         xev.xclient.display = Display();
//         xev.xclient.window = Window();
//         xev.xclient.message_type = atomActiveWindow;
//         xev.xclient.format = 32;
//         xev.xclient.data.l[0] = 1;
//         xev.xclient.data.l[1] = 0;
//         xev.xclient.data.l[2] = 0;
//         xev.xclient.data.l[3] = 0;
//         xev.xclient.data.l[4] = 0;
//
//         XSendEvent(Display(), windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
//
//         windowing_output_debug_string("::set_active_window 2");

      }

//      //auto estatus =
//      //
//      set_keyboard_focus();
//
////      if (!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;

   }


   void window::_set_active_window_unlocked()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      {

         windowing_output_debug_string("::set_active_window 1");

         //display_lock displaylock(x11_display()->Display());

         XEvent xev;

         zero(xev);

         auto windowRoot = DefaultRootWindow(Display());

         Atom atomActiveWindow = x11_display()->_intern_atom_unlocked("_NET_ACTIVE_WINDOW", False);

         xev.xclient.type = ClientMessage;
         xev.xclient.send_event = True;
         xev.xclient.display = Display();
         xev.xclient.window = Window();
         xev.xclient.message_type = atomActiveWindow;
         xev.xclient.format = 32;
         xev.xclient.data.l[0] = 1;
         xev.xclient.data.l[1] = 0;
         xev.xclient.data.l[2] = 0;
         xev.xclient.data.l[3] = 0;
         xev.xclient.data.l[4] = 0;

         XSendEvent(Display(), windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

         windowing_output_debug_string("::set_active_window 2");

      }

      //auto estatus =
      //
      set_keyboard_focus();

//      if (!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   /// should be run at user_thread
   void window::set_foreground_window()
   {

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      _set_foreground_window_unlocked();

//      XRaiseWindow(Display(), Window());
//
//      XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime);

      //return true;

   }


   /// should be run at user_thread
   void window::_set_foreground_window_unlocked()
   {

//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());

      XRaiseWindow(Display(), Window());

      XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime);

      //return true;

   }


   Window window::_get_window_relative(enum_relative erelative, ::Window * windowa, int numItems)
   {

      if (::is_null(windowa))
      {

         windowing_output_debug_string("::_get_window_relative");

         return 0;

      }

      ::Window window = 0;

      switch (erelative)
      {

         case e_relative_first_sibling:
         {

            window = windowa[0];

         }
            break;

         case e_relative_last_sibling:
         {

            window = windowa[numItems - 1];

         }
            break;

         case e_relative_next_sibling:
         case e_relative_previous_sibling:
         {

            int iFound = -1;

            for (int i = 0; i < numItems; i++)
            {

               if (windowa[i] == Window())
               {

                  iFound = i;

                  break;

               }

            }

            if (iFound < 0)
            {

               return 0;

            }

            if (erelative == e_relative_next_sibling)
            {

               if (iFound + 1 >= numItems)
               {

                  return 0;

               }

               window = windowa[iFound + 1];

            } else if (erelative == e_relative_previous_sibling)
            {

               if (iFound - 1 < 0)
               {

                  return 0;

               }

               window = windowa[iFound - 1];

            } else
            {

               return 0;

            }

         }
         default:
         {

            return 0;

         }

      }

      return window;

   }


   ::windowing::window * window::get_window(enum_relative erelative)
   {

      synchronous_lock synchronouslock(user_synchronization());

      ::Window window = 0;

      windowing_output_debug_string("::get_window 1");

      display_lock displaylock(x11_display()->Display());

      if (erelative == e_relative_first_sibling ||
          erelative == e_relative_last_sibling ||
          erelative == e_relative_next_sibling ||
          erelative == e_relative_previous_sibling)
      {

         ::oswindow oswindowParent = get_parent();

         if (oswindowParent == nullptr)
         {

            Atom atomNetClientListStacking = x11_display()->intern_atom("_NET_CLIENT_LIST_STACKING", False);

            Atom atomActualType;

            int format;

            unsigned long numItems, bytesAfter;

            ::Window * windowa = nullptr;

            int status = XGetWindowProperty(
               Display(),
               RootWindow(Display(), Screen()),
               atomNetClientListStacking,
               0L,
               1024,
               false,
               AnyPropertyType,
               &atomActualType,
               &format,
               &numItems,
               &bytesAfter,
               (unsigned char **) &windowa);

            if (status >= Success && numItems)
            {

               window = _get_window_relative(erelative, windowa, numItems);

            }

            if (windowa != NULL)
            {

               XFree(windowa);

            }

         } else
         {

            ::Window root = 0;
            ::Window parent = 0;
            ::Window * pchildren = nullptr;
            unsigned int numItems = 0;

            int status = XQueryTree(Display(), Window(),
                                    &root, &parent, &pchildren, &numItems);

            if (status >= Success && numItems)
            {

               window = _get_window_relative(erelative, pchildren, numItems);

            }

            if (pchildren != nullptr)
            {

               XFree(pchildren);

            }

         }

      } else
      {

         ::Window root = 0;
         ::Window parent = 0;
         ::Window * pchildren = nullptr;
         unsigned int numItems = 0;

         int status = XQueryTree(Display(), Window(),
                                 &root, &parent, &pchildren, &numItems);

         if (status >= Success && numItems)
         {

            if (erelative == e_relative_first_child)
            {

               window = pchildren[0];

            } else if (erelative == e_relative_last_child)
            {

               window = pchildren[numItems - 1];

            }

         }

         if (pchildren != nullptr)
         {

            XFree(pchildren);

         }

      }

      auto pwindowx11 = x11_display()->_window(window);

      if (::is_null(pwindowx11))
      {

         return nullptr;

      }

      return pwindowx11;

   }


   void window::destroy_window()
   {

      bool bOk = false;

      if (::is_set(m_pwindow))
      {

         ::pointer<::user::interaction> pinteraction = m_pwindow->m_puserinteraction;

         if (pinteraction.is_set())
         {

            pinteraction->send_message(e_message_destroy, 0, 0);

            mq_remove_window_from_all_queues();

            pinteraction->send_message(e_message_non_client_destroy, 0, 0);

         } else
         {

            try
            {

//window->m_pwindow->release();

            }
            catch (...)
            {

            }

         }

         //oswindow_remove_impl(window->m_pwindow);

         m_pwindowing->erase_window(this);

      }

//      x11_fork([window]()
//               {

      synchronous_lock synchronouslock(user_synchronization());

      //Display *Display() = Display();

      //Window win = window->window();

      //oswindow_data * pdata = (oswindow_data * )(void * )
      //window;

      bool bIs = is_window();

      m_pwindowing->erase_window(this);

      windowing_output_debug_string("::DestroyWindow 1");

      display_lock displaylock(x11_display()->Display());

      XUnmapWindow(Display(), Window());

      XDestroyWindow(Display(), Window());

      windowing_output_debug_string("::DestroyWindow 2");
//
//               });

      //return ::success;

   }


   bool window::is_window()
   {

//      if (::oswindow_data::s_pdataptra->find_first(oswindow) < 0)
//      {
//
//         return false;
//
//      }

      //return true;

      return true;

   }


   comparable_array<Atom> window::_wm_get_list_unlocked(Atom atomList)
   {

      comparable_array<Atom> atoma;

      if (atomList == None)
      {

         return atoma;

      }

      Atom actual_type;

      int actual_format;

      unsigned long int bytes_after;

      Atom * patoms = nullptr;

      long unsigned int num_items = 0;

      XGetWindowProperty(Display(), Window(), atomList, 0, 1024,
                         False, XA_ATOM, &actual_type, &actual_format,
                         &num_items,
                         &bytes_after, (unsigned char **) &patoms);

      atoma.set_size(num_items);

      memory_copy(atoma.data(), patoms, atoma.get_size_in_bytes());

      XFree(patoms);

      return atoma;

   }


   ::comparable_array < Atom > window::_get_net_wm_state_unlocked()
   {

      auto pdisplay = x11_display();

      return _wm_get_list_unlocked(pdisplay->m_atomNetWmState);

//      bNetWmStateHidden = atoma.contains(pdisplay->m_atomNetWmStateHidden);
//
//      bNetWmStateMaximized = atoma.contains(pdisplay->m_atomNetWmStateMaximizedHorz)
//         || atoma.contains(pdisplay->m_atomNetWmStateMaximizedVert);
//
//      bNetWmStateFocused = atoma.contains(pdisplay->m_atomNetWmStateFocused);

   }


   int window::_wm_test_list_unlocked(Atom atomList, Atom atomFlag)
   {

//      synchronous_lock synchronouslock(user_synchronization());

      Atom actual_type;

      int actual_format;

      unsigned long i;

      auto atoma = _wm_get_list_unlocked(atomList);

      if (atoma.is_empty())
      {

         return 0;

      }

      bool bFind = atoma.contains(atomFlag);

      return bFind ? 1 : 0;

   }


   int window::_wm_test_state_unlocked(const_char_pointer pszNetStateFlag)
   {

      //synchronous_lock synchronouslock(user_synchronization());

      Atom atomFlag = x11_display()->_intern_atom_unlocked(scopedstrNetStateFlag, 1);

      if (atomFlag == None)
      {

         windowing_output_debug_string("ERROR: cannot find atom for " + string(scopedstrNetStateFlag) + "!\n");

         return 0;

      }

      Atom atomNetState = x11_display()->_intern_atom_unlocked("_NET_WM_STATE", 1);

      if (atomNetState == None)
      {

         windowing_output_debug_string("ERROR: cannot find atom for _NET_WM_STATE !\n");

         return 0;

      }

      return _wm_test_list_unlocked(atomNetState, atomFlag);

   }


   int window::wm_test_state(const_char_pointer pszNetStateFlag)
   {

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("::wm_test_state 1");

      display_lock displaylock(x11_display()->Display());

      if (x11_display()->is_null())
      {

         windowing_output_debug_string("::wm_test_state 1.1");

         return 0;

      }

      int i = _wm_test_state_unlocked(scopedstrNetStateFlag);

      windowing_output_debug_string("::wm_test_state 2");

      return i;

   }


   bool window::_wm_add_remove_list_unlocked(Atom atomList, Atom atomFlag, bool bSet)
   {

      if (atomFlag == None)
      {

         return false;

      }

      if (atomList == None)
      {

         return false;

      }

      if (bSet)
      {

         if (!_wm_test_list_unlocked(atomList, atomFlag))
         {

            XChangeProperty(Display(), Window(), atomList, XA_ATOM, 32, PropModeAppend, (unsigned char *) &atomFlag, 1);

         }

      }
      else
      {

         unsigned long num_items;

         auto atoma = _wm_get_list_unlocked(atomList);

         if (atoma.is_empty())
         {

            return false;

         }

         auto iFind = -1;

         int i;

         for (i = 0; i < num_items; i++)
         {

            if (atoma[i] == atomFlag)
            {

               iFind = i;

               break;

            }

         }

         if (::not_found(iFind))
         {

            atoma.erase_at(iFind);

            XChangeProperty(Display(), Window(), atomList, XA_ATOM, 32, PropModeReplace, (unsigned char *) atoma.data(),
                            atoma.size());

         }

      }

      return true;

   }


   bool window::has_mouse_capture() const
   {

      auto pdisplay = x11_display();

      if (::is_null(pdisplay))
      {

         return false;

      }

      auto pwindowCapture = pdisplay->m_pwindowMouseCapture;

      if (::is_null(pwindowCapture))
      {

         return false;

      }

      if (pwindowCapture != this)
      {

         return false;

      }

      return true;

   }


   bool window::has_keyboard_focus() const
   {

      auto pdisplay = x11_display();

      if (::is_null(pdisplay))
      {

         return false;

      }

      auto pwindowFocus = pdisplay->m_pwindowKeyboardFocus;

      if (::is_null(pwindowFocus))
      {

         return false;

      }

      auto pimplFocus = pwindowFocus->m_pwindow;

      if (::is_null(pimplFocus))
      {

         return false;

      }

      auto pinteractionFocus = pimplFocus->m_puserinteraction;

      if (::is_null(pinteractionFocus))
      {

         return false;

      }

      if (!(pinteractionFocus->m_ewindowflag & ::e_window_flag_focus))
      {

         return false;

      }

      return true;

   }


   /// should be run in user thread
   ::e_status window::x11_store_name(const_char_pointer pszName)
   {

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_display()->Display());

      XStoreName(Display(), Window(), pszName);

      return ::success;

   }


//   string window::x11_get_name()
//   {
//
//      string str;
//
//      char *name = NULL;
//      int status = XFetchName(Display(), Window(), &name);
//      if (status >= Success)
//      {
//         str = name;
//      }
//      XFree(name);
//      return str;
//
//   }

//// should be called in user_thread
//   int_bool window::x11_get_window_rect(::int_rectangle *prectangle)
//   {
//
//      XWindowAttributes attrs;
//
//      if (!XGetWindowAttributes(Display(), window, &attrs))
//      {
//
//         windowing_output_debug_string("::x11_get_window_rect 1.1 (xgetwindowattributes failed)");
//
//         return false;
//
//      }
//
//      int x = 0;
//
//      int y = 0;
//
//      int screen = XDefaultScreen((Display *) d);
//
//      Window windowRoot = RootWindow((Display *) Display(), screen);
//
//      Window child;
//
//      XTranslateCoordinates(Display(), window, windowRoot, 0, 0, &x, &y, &child);
//
//      prectangle->left() = x + attrs.x;
//
//      prectangle->top() = y + attrs.y;
//
//      prectangle->right() = x + attrs.x + attrs.width;
//
//      prectangle->bottom() = y + attrs.y + attrs.height;
//
//
//      windowing_output_debug_string("::x11_get_window_rect 2");
//
//      return true;
//
//   }

//   int_bool window::this->rectangle(::int_rectangle *prectangle)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displaylock(x11_display()->Display());
//
//      if (x11_display()->is_null())
//      {
//
//         windowing_output_debug_string("::this->rectangle 1.1 (display is null)");
//
//         return false;
//
//      }
//
//      XWindowAttributes attr;
//
//      if (XGetWindowAttributes(Display(), Window(), &attr) == 0)
//      {
//
//         windowing_output_debug_string("::this->rectangle 1.2 (xgetwindowattributes failed");
//
//         return false;
//
//      }
//
//      prectangle->left() = 0;
//
//      prectangle->top() = 0;
//
//      prectangle->right() = prectangle->left() + attr.width;
//
//      prectangle->bottom() = prectangle->top() + attr.height;
//
//      windowing_output_debug_string("::this->rectangle 2");
//
//      return true;
//
//   }


   void window::window_update_screen_buffer()
   {

      aaa_user_post([this]()
                                   {

                                      auto pimpl = m_pwindow;

                                      if (::is_set(pimpl))
                                      {

                                         pimpl->m_pgraphics->update_screen();

                                      }

                                   });

      //}
      //);

   }


   void window::window_do_update_screen()
   {

//      if(m_interlockedPostedScreenUpdate > 0)
//      {
//
//         return;
//
//      }
//
//      m_interlockedPostedScreenUpdate++;

      //windowing()->windowing_post([this]()
        //                          {

      {

         synchronous_lock synchronouslock(user_synchronization());

         display_lock displayLock(x11_display()->Display());

         auto pimpl = m_pwindow;

         configure_window_unlocked();

         ::pointer<buffer> pbuffer = pimpl->m_pgraphics;

         pbuffer->_update_screen_lesser_lock();

      }

      auto pimpl = m_pwindow;

      pimpl->m_pgraphicsthread->on_graphics_thread_iteration_end();

//                                  });

      //m_interlockedPostedScreenUpdate--;

   }


//   void window::_window_request_presentation_locked()
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      display_lock displayLock(x11_display()->Display());
//
//      auto pimpl = m_pwindow;
//
//      if (::is_set(pimpl))
//      {
//
//         pimpl->_window_request_presentation_unlocked();
//
//      }
//
//   }


   void window::_on_visual_changed_unlocked()
   {

   }


   void window::set_mouse_capture()
   {

      aaa_user_post([this]()
                                   {

                                      synchronous_lock synchronouslock(user_synchronization());

                                      display_lock displaylock(x11_display()->Display());

                                      information() << "XGrabPointer";

                                      auto grabStatus = XGrabPointer(Display(), Window(), False,
                                                                     ButtonPressMask | ButtonReleaseMask |
                                                                     PointerMotionMask,
                                                                     GrabModeAsync, GrabModeAsync, None, None,
                                                                     CurrentTime);

                                      if (grabStatus != GrabSuccess)
                                      {

                                         windowing_output_debug_string("\noswindow_data::SetCapture 2.1");

                                         return;

                                      }

                                      auto pdisplay = x11_display();

                                      if (pdisplay)
                                      {

                                         pdisplay->_on_capture_changed_to(this);

                                      }

                                      windowing_output_debug_string("\noswindow_data::SetCapture 2");

                                   });

      //return ::success;

   }


   void window::set_keyboard_focus()
   {

      synchronous_lock synchronouslock(user_synchronization());

      if (Window() == 0)
      {

         throw ::exception(error_failed);

      }

      windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1");

      display_lock displaylock(x11_display()->Display());

      _set_keyboard_focus_unlocked();

//      if (!is_window())
//      {
//
//         windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.1");
//
//         throw ::exception(error_failed);
//
//      }
//
//      if (!XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime))
//      {
//
//         windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.3");
//
//         throw ::exception(error_failed);
//
//      }
//
//      windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 2");

      //return ::success;

   }


   void window::_set_keyboard_focus_unlocked()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      if (Window() == 0)
      {

         throw ::exception(error_failed);

      }

      windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1");

      //display_lock displaylock(x11_display()->Display());

      if (!is_window())
      {

         windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.1");

         throw ::exception(error_failed);

      }

      if (!XSetInputFocus(Display(), Window(), RevertToNone, CurrentTime))
      {

         windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1.3");

         throw ::exception(error_failed);

      }

      windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 2");

      //return ::success;

   }


   bool window::is_active_window() const
   {

      return ::windowing::window::is_active_window();

   }


   void window::bring_to_front()
   {

      synchronous_lock synchronouslock(user_synchronization());

      if (Window() == 0)
      {

         throw ::exception(error_failed);

      }

      windowing_output_debug_string("\nwindow(x11)::set_keyboard_focus 1");

      display_lock displaylock(x11_display()->Display());

      XRaiseWindow(displaylock.m_pdisplay, Window());

      //return ::success;

   }


//   bool window::presentation_complete()
//   {
//
//      return m_pwindow->m_pgraphics->presentation_complete();
//
//   }


   void window::_on_end_paint()
   {

      if(m_enetwmsync == window::e_net_wm_sync_wait_paint)
      {

         m_enetwmsync == window::e_net_wm_sync_none;

         if (!XSyncValueIsZero(m_xsyncvalueNetWmSync))
         {

            x_change_property(
               x11_display()->m_atomNetWmSyncRequestCounter,
               XA_CARDINAL,
               32,
               PropModeReplace,
               (const unsigned char *) &m_xsyncvalueNetWmSync, 1);

            XSyncIntToValue(&m_xsyncvalueNetWmSync, 0);

         }

      }



   }


   void window::_enable_net_wm_sync()
   {

      if (m_xsynccounterNetWmSync != None)
      {

         return;

      }

      //return;

      auto atomWmProtocols = x11_display()->m_atomWmProtocols;

      auto atomNetWmSyncRequest = x11_display()->m_atomNetWmSyncRequest;

      m_enetwmsync = e_net_wm_sync_none;

      _wm_add_remove_list_unlocked(atomWmProtocols, atomNetWmSyncRequest, true);

      {

         XSyncValue xsyncvalue;

         XSyncIntToValue(&xsyncvalue, 1);

         m_xsynccounterNetWmSync = XSyncCreateCounter(x11_display()->Display(), xsyncvalue);

      }

      auto atomNetWmSyncRequestCounter = x11_display()->m_atomNetWmSyncRequestCounter;

      x_change_property(atomNetWmSyncRequestCounter,
                        XA_CARDINAL, 32, PropModeReplace, (const unsigned char *) &m_xsynccounterNetWmSync,
                        1);

      XSyncIntToValue(&m_xsyncvalueNetWmSyncPending, 0);

      XSyncIntToValue(&m_xsyncvalueNetWmSync, 0);

   }


} // namespace windowing_x11



