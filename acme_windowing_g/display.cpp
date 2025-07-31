//
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#include "framework.h"
#include "display.h"
//#include "window.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"
//#include "acme/prototype/geometry2d/rectangle.h"
//#include "acme/user/micro/window.h"

#include "acme/exception/interface_only.h"
#include "acme/graphics/image/pixmap.h"
//#include "nano_user_wayland/window_base.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task.h"
#include "acme/platform/acme.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing.h"
#include "acme_windowing_g/gdk_3_and_4.h"
//#if
//#include <linux/input.h> // for BTN_LEFT
#include <sys/poll.h>
#include <wayland-client-protocol.h>
#include <wayland-server-protocol.h>
#include <xkbcommon/xkbcommon.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>

// # ifdef GDK_WINDOWING_X11
// #  include <gdk/x11/gdkx.h>
// # endif
// # ifdef GDK_WINDOWING_WAYLAND
// #  include <gdk/wayland/gdkwayland.h>
// #endif

int os_create_anonymous_file(off_t size);

//#include "windowing_system_x11/_.h"


#define MAXSTR 1000


void x11_init_threads();


//void * x11_get_display();


void set_main_user_thread();


namespace g
{


   namespace acme
   {


      namespace windowing
      {


         display::display()
         {

            // m_pgdkdisplay = nullptr;
            //
            // m_bUnhook = false;

            //      if(!g_p)
            //      {
            //
            //         g_p = this;
            //
            //      }

            defer_create_synchronization();

            // m_bOwnDisplay = false;
            //
            // //m_pxkbkeymap = nullptr;
            // //m_pxkbstate = nullptr;
            // m_bOpened = false;
            // m_pgdkdisplay = nullptr;
            //
            //
            //
            // // //::wl_display * m_pwldisplay;
            // // m_pwlshm = nullptr;
            // // m_pxdgwmbase = nullptr;
            // // m_pwlcompositor = nullptr;
            // // m_pwlsurfaceCursor = nullptr;
            // // m_pwlseat = nullptr;
            // // m_pwlkeyboard = nullptr;
            // // m_pwlpointer = nullptr;
            // // m_pwlsubcompositor = nullptr;
            // // //::wl_shm_pool * m_pwlshmpool;
            // // m_pwlsurfacePointerEnter = nullptr;
            // // m_pwlsurfaceLastLButtonDown = nullptr;
            // // m_pwlsurfaceMouseCapture = nullptr;
            // // m_pxdgsurfaceMouseCapture = nullptr;
            // // m_pxdgtoplevelMouseCapture = nullptr;
            // // //wayland_buffer m_waylandbufferMouseCapture;
            // // m_bMouseCaptured = false;
            // // //::int_rectangle m_rectangleMouseCapture;
            // // m_uLastButtonSerial = 0;
            // // m_uLastPointerSerial = 0;
            // // m_uLastSeatSerial = 0;
            // // m_uLastKeyboardSerial = 0;
            // // m_uLastKeyboardEnterSerial = 0;
            // // m_uLastKeyboardLeaveSerial = 0;
            // // m_pgtkshell1 = nullptr;
            // // m_pxdgactivationv1 = nullptr;
            // // m_pwlsurfaceKeyboardEnter = nullptr;


         }


         display::~display()
         {



            // if(s_pdisplaybase == this)
            // {
            //
            //    s_pdisplaybase = nullptr;
            //
            // }
            //
            // close();
            //
            //
            // if (m_bOwnDisplay && m_pgdkdisplay != nullptr)
            // {
            //
            //    //wl_display_disconnect(m_pwldisplay);
            //
            //    m_pgdkdisplay = nullptr;
            //
            //    m_bOwnDisplay = false;
            //
            //    printf("disconnected from display\n");
            //
            // }

         }


         void display::initialize(::particle* pparticle)
         {

            ::acme::windowing::display::initialize(pparticle);

            //::gtk4::acme::windowing::display::initialize(pparticle);

         }


//          void display::open_display()
//          {
//
//             //    display::open();
//
//             information() << "windowing_gtk4::display::open_display";
//
//             m_sizeaMonitor.clear();
//
//             m_pgdkdisplay = gdk_display_get_default();
//
//             auto * monitors = gdk_display_get_monitors(m_pgdkdisplay);
//
//
//             guint n_monitors = g_list_model_get_n_items(monitors);
//
//             // Iterate over each monitor
//             for (guint i = 0; i < n_monitors; i++) {
//                GdkMonitor *monitor = GDK_MONITOR(g_list_model_get_item(monitors, i));
//
//
//                // Get the geometry (rectangle) of the monitor
//                GdkRectangle geometry;
//                gdk_monitor_get_geometry(monitor, &geometry);
//
//                int cx = geometry.width;
//                int cy = geometry.height;
//                // Print monitor geometry details
//                printf("Monitor %u: x = %d, y = %d, width = %d, height = %d\n",
//                       i, geometry.x, geometry.y, geometry.width, geometry.height);
//                g_object_unref(monitor);
//
//                m_sizeaMonitor.add({cx, cy});
//             }
//
//             // if(is_wayland())
//             // {
//             //    m_pwldisplay = gdk_wayland_display_get_wl_display(m_pgdkdisplay);
//             //
//             //    // Step 2: Get the registry
//             //    auto * wl_registry = wl_display_get_registry(m_pwldisplay);
//             //
//             //    wl_registry_add_listener(wl_registry, &s_registry_listener, this);
//             //
//             //    // Step 3: Roundtrip to process the registry and bind the objects
//             //    wl_display_roundtrip(m_pwldisplay);
//             // }
//
//          }
//
//
//          bool display::is_wallpaper_associated_with_dark_mode()
//          {
//
//             return true;
//
//          }
//
//
// //         bool is_wallpaper_associated_with_theming() override;
//
//
//          //   Atom display::intern_atom(const char *pszAtomName, bool bCreate)
//          //   {
//          //
//          //      return _intern_atom_unlocked(scopedstrAtomName, bCreate);
//          //
//          ////      if (m_pdisplay == nullptr)
//          ////      {
//          ////
//          ////         return 0;
//          ////
//          ////      }
//          ////
//          ////      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
//          ////
//          ////      if (atom == None)
//          ////      {
//          ////
//          ////         windowing_output_debug_string("ERROR: cannot find atom for " + string(scopedstrAtomName) + "\n");
//          ////
//          ////         return None;
//          ////
//          ////      }
//          ////
//          ////      return atom;
//          //
//          //   }
//          //
//          //
//          //   Atom display::intern_atom(enuid() eatom, bool bCreate)
//          //   {
//          //
//          //      return _intern_atom_unlocked(eatom, bCreate);
//          //
//          ////      if (eatom < 0 || eatom >= e_atom_count)
//          ////      {
//          ////
//          ////         return None;
//          ////
//          ////      }
//          ////
//          ////      Atom atom = id()map[eatom];
//          ////
//          ////      if (atom == None)
//          ////      {
//          ////
//          ////         atom = intern_atom(atom_name(eatom), bCreate);
//          ////
//          ////         id()map[eatom] = atom;
//          ////
//          ////      }
//          ////
//          ////      return atom;
//          //
//          //   }
//          //
//          //
//          //
//          //   Atom display::_intern_atom_unlocked(const char *pszAtomName, bool bCreate)
//          //   {
//          //
//          //      if (m_pdisplay == nullptr)
//          //      {
//          //
//          //         return 0;
//          //
//          //      }
//          //
//          //      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
//          //
//          //      if (atom == None)
//          //      {
//          //
//          //         windowing_output_debug_string("ERROR: cannot find atom for " + string(scopedstrAtomName) + "\n");
//          //
//          //         return None;
//          //
//          //      }
//          //
//          //      return atom;
//          //
//          //   }
//          //
//          //
//          //   Atom display::_intern_atom_unlocked(enuid() eatom, bool bCreate)
//          //   {
//          //
//          //      if (eatom < 0 || eatom >= e_atom_count)
//          //      {
//          //
//          //         return None;
//          //
//          //      }
//          //
//          //      Atom atom = id()map[eatom];
//          //
//          //      if (atom == None)
//          //      {
//          //
//          //         atom = _intern_atom_unlocked(atom_name(eatom), bCreate);
//          //
//          //         id()map[eatom] = atom;
//          //
//          //      }
//          //
//          //      return atom;
//          //
//          //   }
//          //
//          //
//          //   unsigned char* display::_get_string_property(Display * display, Window window, char* property_name)
//          //   {
//          //
//          //      unsigned char * prop;
//          //      Atom actual_type, filter_atom;
//          //      int actual_format, status;
//          //      unsigned long nitems, bytes_after;
//          //
//          //      filter_atom = XInternAtom(display, property_name, True);
//          //
//          //      status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
//          //                                  &actual_type, &actual_format, &nitems, &bytes_after, &prop);
//          //
//          //      x11_check_status(status, window);
//          //
//          //      return prop;
//          //
//          //   }
//          //
//          //
//          //   unsigned long display::_get_long_property(Display *d, Window w, char *property_name)
//          //   {
//          //
//          //      unsigned char *prop = _get_string_property(d, w, property_name);
//          //
//          //      unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);
//          //
//          //      XFree(prop);
//          //
//          //      return long_property;
//          //
//          //   }
//          //
//          //
//          //   Window display::_get_active_window()
//          //   {
//          //
//          //      int screen = XDefaultScreen(m_pdisplay);
//          //
//          //      Window windowRoot = RootWindow(m_pdisplay, screen);
//          //
//          //      Window window = _get_long_property(m_pdisplay, windowRoot, (char *) "_NET_ACTIVE_WINDOW");
//          //
//          //      return window;
//          //
//          //   }
//
//
//          //   Window display::window_from_name_search(Display *display, Window current, char const *needle, int iOffset, int depth)
//          //   {
//          //
//          //      Window window, root, parent, *children;
//          //
//          //      unsigned children_count;
//          //
//          //      char *name = NULL;
//          //
//          //      window = 0;
//          //
//          //      /* If it does not: check all subwindows recursively. */
//          //      if(0 != XQueryTree(display, current, &root, &parent, &children, &children_count))
//          //      {
//          //
//          //         unsigned i;
//          //
//          //         for(i = 0; i < children_count; ++i)
//          //         {
//          //
//          //            /* Check if this window has the name we seek */
//          //            if(XFetchName(display,  children[i], &name) > 0)
//          //            {
//          //
//          //               int r = ansi_cmp(needle, name);
//          //
//          //               XFree(name);
//          //
//          //               if(r == 0)
//          //               {
//          //
//          //                  window = children[i+iOffset];
//          //
//          //                  break;
//          //
//          //               }
//          //
//          //            }
//          //
//          //            if(depth > 1)
//          //            {
//          //
//          //               Window win = window_from_name_search(display, children[i], needle, depth - 1);
//          //
//          //               if (win != 0)
//          //               {
//          //
//          //                  window = win;
//          //
//          //                  break;
//          //
//          //               }
//          //
//          //            }
//          //
//          //         }
//          //
//          //         XFree(children);
//          //
//          //      }
//          //
//          //      return window;
//          //
//          //   }
//
//
//          //   Window display::window_from_name(char const *name, int iOffset, int depth)
//          //   {
//          //
//          ////      auto display = m_pdisplay;
//          ////
//          ////      auto windowRoot = XDefaultRootWindow(display);
//          ////
//          ////      auto window = window_from_name_search(display, windowRoot, name, iOffset, depth);
//          //
//          //
//          //
//          ////      return window;
//          //
//          //   }
//
//
//          ::GdkDisplay* display::__get_gdk_display()
//          {
//
//             if (m_pgdkdisplay)
//             {
//
//                return m_pgdkdisplay;
//
//             }
//
//             m_pgdkdisplay = gdk_display_get_default();
//             if (m_pgdkdisplay == NULL)
//             {
//                error() << "Can't connect to display";
//                throw ::exception(error_failed);
//             }
//             information() << "connected to display\n";
//             m_bOwnDisplay = true;
//             //wl_display_disconnect(display);
//             //printf("disconnected from display\n");
//
//             return m_pgdkdisplay;
//
//          }
//
//
//          //   display * display::get(::particle * pparticle, bool bBranch, ::wl_display * pwldisplay)
//          //   {
//          //
//          //      critical_section_lock lock(this->::system()->globals_critical_section());
//          //
//          //      if (g_p == nullptr)
//          //      {
//          //
//          //         auto p = ___new display();
//          //
//          //         p->initialize(pparticle);
//          //
//          //         //p->add_listener(p);
//          //
//          //         p->m_pwldisplay = pwldisplay;
//          //
//          //         if(bBranch)
//          //         {
//          //
//          //            p->branch_synchronously();
//          //
//          //         }
//          //         else
//          //         {
//          //
//          //            p->init_task();
//          //
//          //         }
//          //
//          //      }
//          //
//          //      return g_p;
//          //
//          //   }
//
//
//          //   void display::add_listener(event_listener * plistener)
//          //   {
//          //
//          //      synchronous_lock synchronouslock(this->synchronization());
//          //
//          //      m_happeninglistenera.add(plistener);
//          //
//          //   }
//          //
//          //
//          //   void display::add_window(micro::interchange * pwindow)
//          //   {
//          //
//          //      synchronous_lock synchronouslock(this->synchronization());
//          //
//          //      m_windowa.add(pwindow);
//          //
//          //   }
//
//          //
//          //   void display::erase_listener(event_listener * plistener)
//          //   {
//          //
//          //      synchronous_lock synchronouslock(this->synchronization());
//          //
//          //      m_happeninglistenera.erase(plistener);
//          //
//          //   }
//          //
//          //
//          //   void display::erase_window(micro::interchange * pwindow)
//          //   {
//          //
//          //      synchronous_lock synchronouslock(this->synchronization());
//          //
//          //      m_windowa.erase(pwindow);
//          //
//          //   }
//
//          //
//          bool display::message_loop_step()
//          {
//
//             return ::gtk4::acme::windowing::display::message_loop_step();
//
//          }
//

         //
         //      if (!XPending(m_pdisplay))
         //      {
         //
         //         return false;
         //
         //      }
         //
         //      XEvent happening{};
         //
         //      XNextEvent(m_pdisplay, &happening);
         //
         //      x11_event(&happening);
         //
         //      return true;
         //
         //   }

         //
         //   bool display::aa_x11_posted()
         //   {
         //
         //      return aaa_display_posted_routine_step();
         //
         //   }
         //
         //
         //   bool display::x11_event(XEvent * pevent)
         //   {
         //
         //      bool bHandled = false;
         //
         //      ::collection::index i = 0;
         //
         //      synchronous_lock synchronouslock(this->synchronization());
         //
         //      for (; i < m_happeninglistenera.get_count(); i++)
         //      {
         //
         //         auto plistener = m_happeninglistenera[i];
         //
         //         synchronouslock.unlock();
         //
         //         if(i == 0)
         //         {
         //
         //            if (plistener->_on_event(pevent))
         //            {
         //
         //               bHandled = true;
         //
         //               break;
         //
         //            }
         //
         //         }
         //         else
         //         {
         //
         //            if (plistener->_on_event(pevent))
         //            {
         //
         //               bHandled = true;
         //
         //               break;
         //
         //            }
         //
         //         }
         //
         //         synchronouslock.lock();
         //
         //      }
         //
         //      return bHandled;
         //
         //   }
         //
         //
         //   void display::aaa_message_loop()
         //   {
         //
         //      bool bHandled1;
         //
         //      bool bHandled2;
         //
         //      while (::task_get_run())
         //      {
         //
         //         if(m_bUnhook)
         //         {
         //
         //            break;
         //
         //         }
         //
         //         bHandled1 = false;
         //
         //         bHandled2 = false;
         //
         //         while(aaa_message_loop_step())
         //         {
         //
         //            bHandled1 = true;
         //
         //         }
         //
         //         if(!bHandled1)
         //         {
         //
         //            bHandled2 = aaa_x11_posted();
         //
         //         }
         //
         //         if(!bHandled1 && !bHandled2)
         //         {
         //
         //            preempt(5_ms);
         //
         //         }
         //
         //      }
         //
         //      information() << "Finished display::message_loop for nano::display";
         //
         //   }
         //
         //
         // void display::init_task()
         // {
         //
         //
         //    display::init_task();
         //
         //    //      if(::windowing::get_ewindowing() == ::windowing::e_windowing_none)
         //    //      {
         //    //
         //    //         //set_main_user_thread();
         //    //
         //    //         ::windowing::get_ewindowing() = e_windowing_x11;
         //    //
         //    //      }
         //    ////
         //    ////      XInitxThreads();
         //    ////
         //    ////      if(!m_pdisplay)
         //    ////      {
         //    ////
         //    ////         set_X11_Display(XOpenxDisplay(nullptr));
         //    ////
         //    ////      }
         //
         // }
         //

         // void display::set_gdk_display(::GdkDisplay* pgdkdisplay)
         // {
         //
         //    m_pgdkdisplay = pgdkdisplay;
         //
         //    if (!m_pgdkdisplay)
         //    {
         //
         //       throw ::exception(error_null_pointer);
         //
         //    }
         //
         //    ::int_rectangle rectangleMainScreen;
         //
         //    //      auto pscreen = DefaultScreenOfDisplay(m_pdisplay);
         //    //
         //    //      int wScreen = WidthOfScreen(pscreen);
         //    //      int hScreen = HeightOfScreen(pscreen);
         //
         //    //printf("::x11::display::init_task pscreen=%" PRIxPTR "\n", pscreen);
         //    //printf("::x11::display::init_task (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);
         //
         //    //rectangleMainScreen.left() = 0;
         //    //rectangleMainScreen.top() = 0;
         //    //rectangleMainScreen.right() = wScreen;
         //    //rectangleMainScreen.bottom() = hScreen;
         //
         //    //operating_system_set_main_screen_rectangle(rectangleMainScreen);
         //
         // }
         //
         //
         // bool display::is_branch_current() const
         // {
         //
         //    if (!m_bUnhook && ::object::is_branch_current())
         //    {
         //
         //       return true;
         //
         //    }
         //
         //    if (m_bUnhook && ::is_main_thread())
         //    {
         //
         //       return true;
         //
         //    }
         //
         //    return false;
         //
         // }


         // void display::run()
         // {
         //
         //    display::run();
         //
         // }
         //

         //   bool display::_on_event(XEvent * pevent)
         //   {
         //
         //      if (pevent->xany.window == DefaultRootWindow(m_pdisplay))
         //      {
         //
         //         if(pevent->xany.type == PropertyNotify)
         //         {
         //
         //            Atom atom = XInternAtom(m_pdisplay, "_NET_ACTIVE_WINDOW", False);
         //
         //            if (atom == pevent->xproperty.atom)
         //            {
         //
         //               auto windowActive = m_windowActive;
         //
         //               for(auto & pwindow : m_windowa)
         //               {
         //
         //                  bool bNcActive = windowActive == pwindow->m_window;
         //
         //                  if (is_different(bNcActive, pwindow->m_pinterface->m_bNcActive))
         //                  {
         //
         //                     pwindow->m_pinterface->m_bNcActive = bNcActive;
         //
         //                     pwindow->redraw();
         //
         //                  }
         //
         //               }
         //
         //               m_windowActive = windowActive;
         //
         //            }
         //
         //         }
         //
         //      }
         //
         //      return false;
         //
         //   }


         // ::int_size display::get_main_screen_size()
         // {
         //
         //    //      auto snum = DefaultScreen(m_pdisplay);
         //    //
         //    //      auto width = DisplayWidth(m_pdisplay, snum);
         //    //
         //    //      auto height = DisplayHeight(m_pdisplay, snum);
         //    //
         //    //      return { width, height };
         //
         //    if (m_sizeaMonitor.is_empty())
         //    {
         //
         //       return {};
         //
         //    }
         //
         //    return m_sizeaMonitor[0];
         //
         // }


         // void* get_display(::particle* pparticle)
         // {
         //
         //    auto pdisplay = ::gtk4::acme::windowing::display::get(pparticle, false);
         //
         //    return pdisplay->m_pgdkdisplay;
         //
         // }


         // void set_display(::gtk4::acme::windowing::display* pdisplaybase)
         // {
         //
         //    ::gtk4::acme::windowing::display::s_pdisplaybase = pdisplaybase;
         //
         // }
         //
         //
         // void initialize_display(::particle* pparticle, void* pgdkdisplay)
         // {
         //
         //    ::gtk4::acme::windowing::display::get(pparticle, false, (::GdkDisplay*)pgdkdisplay);
         //
         // }


         // void* initialize_display(::particle* pparticle)
         // {
         //
         //    auto pdisplay = ::gtk4::acme::windowing::display::get(pparticle, false);
         //
         //    return pdisplay->m_pgdkdisplay;
         //         //
         //         // void process_messages()
         //         // {
         //         //
         //         //    if (::gtk4::acme::windowing::display::s_pdisplaybase)
         //         //    {
         //         //
         //         //       ::gtk4::acme::windowing::display::s_pdisplaybase->message_loop_step();
         //         //
         //         //    }
         //         //
         //         // }
         // }


         //display * display::s_pdisplaybase = nullptr;


      //    /**
      // * properties of the output
      // *
      // * The geometry happening describes geometric properties of the
      // * output. The happening is sent when binding to the output object and
      // * whenever any of the properties change.
      // *
      // * The physical size can be set to zero if it doesn't make sense
      // * for this output (e.g. for projectors or virtual outputs).
      // *
      // * The geometry happening will be followed by a done happening (starting
      // * from version 2).
      // *
      // * Note: wl_output only advertises partial information about the
      // * output position and identification. Some compositors, for
      // * instance those not implementing a desktop-style output layout or
      // * those exposing virtual outputs, might fake this information.
      // * Instead of using x and y, clients should use
      // * xdg_output.logical_position. Instead of using make and model,
      // * clients should use name and description.
      // * @param x x position within the global compositor space
      // * @param y y position within the global compositor space
      // * @param physical_width width in millimeters of the output
      // * @param physical_height height in millimeters of the output
      // * @param subpixel subpixel orientation of the output
      // * @param make textual description of the manufacturer
      // * @param model textual description of the model
      // * @param transform transform that maps framebuffer to output
      // */
      //    void wl_output_geometry(void * data,
      //                            struct wl_output * pwloutput,
      //                            int32_t x,
      //                            int32_t y,
      //                            int32_t physical_width,
      //                            int32_t physical_height,
      //                            int32_t subpixel,
      //                            const char * make,
      //                            const char * model,
      //                            int32_t transform)
      //    {
      //
      //       auto pdisplaybase = (display *) data;
      //
      //       pdisplaybase->__handle_wl_output_geometry(pwloutput, x, y, physical_width, physical_height, subpixel, make, model,
      //                                                 transform);
      //
      //    }
      //
      //    /**
      //     * advertise available modes for the output
      //     *
      //     * The mode happening describes an available mode for the output.
      //     *
      //     * The happening is sent when binding to the output object and there
      //     * will always be one mode, the current mode. The happening is sent
      //     * again if an output changes mode, for the mode that is now
      //     * current. In other words, the current mode is always the last
      //     * mode that was received with the current flag set.
      //     *
      //     * Non-current modes are deprecated. A compositor can decide to
      //     * only advertise the current mode and never send other modes.
      //     * Clients should not rely on non-current modes.
      //     *
      //     * The size of a mode is given in physical hardware units of the
      //     * output device. This is not necessarily the same as the output
      //     * size in the global compositor space. For instance, the output
      //     * may be scaled, as described in wl_output.scale, or transformed,
      //     * as described in wl_output.transform. Clients willing to retrieve
      //     * the output size in the global compositor space should use
      //     * xdg_output.logical_size instead.
      //     *
      //     * The vertical refresh rate can be set to zero if it doesn't make
      //     * sense for this output (e.g. for virtual outputs).
      //     *
      //     * The mode happening will be followed by a done happening (starting from
      //     * version 2).
      //     *
      //     * Clients should not use the refresh rate to schedule frames.
      //     * Instead, they should use the wl_surface.frame happening or the
      //     * presentation-time protocol.
      //     *
      //     * Note: this information is not always meaningful for all outputs.
      //     * Some compositors, such as those exposing virtual outputs, might
      //     * fake the refresh rate or the size.
      //     * @param flags bitfield of mode flags
      //     * @param width width of the mode in hardware units
      //     * @param height height of the mode in hardware units
      //     * @param refresh vertical refresh rate in mHz
      //     */
      //    void wl_output_mode(void * data,
      //                        struct wl_output * pwloutput,
      //                        uint32_t flags,
      //                        int32_t width,
      //                        int32_t height,
      //                        int32_t refresh)
      //    {
      //
      //
      //       auto pdisplaybase = (display *) data;
      //
      //       pdisplaybase->__handle_wl_output_mode(pwloutput, flags, width, height, refresh);
      //
      //
      //    }
      //
      //
      //    /**
      //     * sent all information about output
      //     *
      //     * This happening is sent after all other properties have been sent
      //     * after binding to the output object and after any other property
      //     * changes done after that. This allows changes to the output
      //     * properties to be seen as atomic, even if they happen via
      //     * multiple happenings.
      //     * @since 2
      //     */
      //    void wl_output_done(void * data,
      //                        struct wl_output * wl_output)
      //    {
      //
      //    }
      //
      //    /**
      //     * output scaling properties
      //     *
      //     * This happening contains scaling geometry information that is not
      //     * in the geometry happening. It may be sent after binding the output
      //     * object or if the output scale changes later. If it is not sent,
      //     * the client should assume a scale of 1.
      //     *
      //     * A scale larger than 1 means that the compositor will
      //     * automatically scale surface buffers by this amount when
      //     * rendering. This is used for very high resolution displays where
      //     * applications rendering at the native resolution would be too
      //     * small to be legible.
      //     *
      //     * It is intended that scaling aware clients track the current
      //     * output of a surface, and if it is on a scaled output it should
      //     * use wl_surface.set_buffer_scale with the scale of the output.
      //     * That way the compositor can avoid scaling the surface, and the
      //     * client can supply a higher detail image.
      //     *
      //     * The scale happening will be followed by a done happening.
      //     * @param factor scaling factor of output
      //     * @since 2
      //     */
      //    void wl_output_scale(void * data,
      //                         struct wl_output * wl_output,
      //                         int32_t factor)
      //    {
      //
      //    }
      //
      //    /**
      //     * name of this output
      //     *
      //     * Many compositors will assign user-friendly names to their
      //     * outputs, show them to the user, allow the user to refer to an
      //     * output, etc. The client may wish to know this name as well to
      //     * offer the user similar behaviors.
      //     *
      //     * The name is a UTF-8 string with no convention defined for its
      //     * contents. Each name is unique among all wl_output globals. The
      //     * name is only guaranteed to be unique for the compositor
      //     * instance.
      //     *
      //     * The same output name is used for all clients for a given
      //     * wl_output global. Thus, the name can be shared across processes
      //     * to refer to a specific wl_output global.
      //     *
      //     * The name is not guaranteed to be persistent across sessions,
      //     * thus cannot be used to reliably identify an output in e.g.
      //     * configuration files.
      //     *
      //     * Examples of names include 'HDMI-A-1', 'WL-1', 'X11-1', etc.
      //     * However, do not assume that the name is a reflection of an
      //     * underlying DRM connector, X11 connection, etc.
      //     *
      //     * The name happening is sent after binding the output object. This
      //     * happening is only sent once per output object, and the name does not
      //     * change over the lifetime of the wl_output global.
      //     *
      //     * Compositors may re-use the same output name if the wl_output
      //     * global is destroyed and re-created later. Compositors should
      //     * avoid re-using the same name if possible.
      //     *
      //     * The name happening will be followed by a done happening.
      //     * @param name output name
      //     * @since 4
      //     */
      //    void wl_output_name(void * data,
      //                        struct wl_output * wl_output,
      //                        const char * name)
      //    {
      //
      //
      //    }
      //
      //    /**
      //     * human-readable description of this output
      //     *
      //     * Many compositors can produce human-readable descriptions of
      //     * their outputs. The client may wish to know this description as
      //     * well, e.g. for output selection purposes.
      //     *
      //     * The description is a UTF-8 string with no convention defined for
      //     * its contents. The description is not guaranteed to be unique
      //     * among all wl_output globals. Examples might include 'Foocorp 11"
      //     * Display' or 'Virtual X11 output via :1'.
      //     *
      //     * The description happening is sent after binding the output object
      //     * and whenever the description changes. The description is
      //     * optional, and may not be sent at all.
      //     *
      //     * The description happening will be followed by a done happening.
      //     * @param description output description
      //     * @since 4
      //     */
      //    void wl_output_description(void * data,
      //                               struct wl_output * wl_output,
      //                               const char * description)
      //    {
      //
      //
      //    }
      //
      //    const static struct wl_output_listener g_wl_output_listener =
      //       {
      //       wl_output_geometry,
      //       wl_output_mode,
      //       wl_output_done,
      //       wl_output_scale,
      //       wl_output_description
      //
      //    };
      //
      //
      //    // void xdg_surface_mouse_capture_configure(void * data, struct xdg_surface * xdg_surface, uint32_t serial)
      //    //   {
      //    //
      //    //      auto pdisplay = (display *) data;
      //    //
      //    //      xdg_surface_ack_configure(xdg_surface, serial);
      //    //
      //    //      wl_surface_attach(pdisplay->m_pwlsurfaceMouseCapture, pdisplay->m_waylandbufferMouseCapture.m_pwlbuffer, 0, 0);
      //    //
      //    //      wl_surface_commit(pdisplay->m_pwlsurfaceMouseCapture);
      //    //
      //    //   }
      //
      //
      //    //   static const struct xdg_surface_listener xdg_surface_mouse_capture_listener = {
      //    //      xdg_surface_mouse_capture_configure,
      //    //   };
      //
      //
      //    void pointer_handle_enter(void * data, struct wl_pointer * pwlpointer,
      //                         uint32_t serial, struct wl_surface * pwlsurface,
      //                         wl_fixed_t sx, wl_fixed_t sy)
      //    {
      //
      //       auto x = wl_fixed_to_double(sx);
      //
      //       auto y = wl_fixed_to_double(sy);
      //
      //       struct wl_buffer * buffer;
      //
      //       struct wl_cursor_image * image;
      //
      //       fprintf(stderr, "Pointer entered surface %p at %0.0f %0.0f\n", pwlsurface, x, y);
      //
      //       auto pdisplay = (display *) data;
      //
      //       pdisplay->__handle_pointer_enter(pwlpointer, serial, pwlsurface, sx, sy);
      //
      //       //      pdisplay->m_uLastPointerSerial = serial;
      //       //
      //       //      pdisplay->m_uLastSeatSerial = serial;
      //       //
      //       //      if (pwlsurface == pdisplay->m_pwlsurfaceMouseCapture)
      //       //      {
      //       //
      //       //         fprintf(stderr, "entered Mouse Capture surface at %0.0f %0.0f!!\n", x, y);
      //       //
      //       //         pdisplay->m_bMouseCaptured = true;
      //       //
      //       //         ///pdisplay->__handle_pointer_enter(x, y, pwaylandwindow);
      //       //
      //       //         return;
      //       //
      //       //      }
      //       //
      //       //      auto pwaylandwindow = pdisplay->_window(pwlsurface);
      //       //
      //       //      //auto pcursor = pwaylandwindow->get_mouse_cursor();
      //       //
      //       ////      auto pwlsurfaceCursor =  pdisplay->m_pwlsurfaceCursor;
      //       ////
      //       ////      ::pointer < ::windowing_wayland::cursor > pwaylandcursor = pcursor;
      //       //
      //       //      //image = default_cursor->images[0];
      //       //      //buffer = wl_cursor_image_get_buffer(image);
      //       //
      //       ////      if(pwaylandcursor)
      //       ////      {
      //       ////
      //       ////         wl_pointer_set_cursor(pwlpointer, serial,
      //       ////                               pwlsurfaceCursor,
      //       ////                               pwaylandcursor->m_szHotspotOffset.cx(),
      //       ////                               pwaylandcursor->m_szHotspotOffset.cy());
      //       ////         wl_surface_attach(pwlsurfaceCursor, pwaylandcursor->m_waylandbuffer.m_pwlbuffer, 0, 0);
      //       ////         wl_surface_damage(pwlsurfaceCursor, 0, 0, pwaylandcursor->m_pimage->width(),
      //       ////                           pwaylandcursor->m_pimage->height());
      //       ////         wl_surface_commit(pwlsurfaceCursor);
      //       ////
      //       ////      }
      //       //
      //       //      pdisplay->__handle_pointer_enter(pwlpointer, x, y, pwaylandwindow);
      //
      //    }
      //
      //
      //    void
      //    pointer_handle_leave(void * data, struct wl_pointer * pwlpointer,
      //                         uint32_t serial, struct wl_surface * pwlsurface)
      //    {
      //
      //       fprintf(stderr, "Pointer left surface %p\n", pwlsurface);
      //
      //       auto pdisplay = (display *) data;
      //
      //       pdisplay->m_uLastPointerSerial = serial;
      //
      //       pdisplay->m_uLastSeatSerial = serial;
      //
      //       if (pdisplay->m_pwlsurfaceMouseCapture && pwlsurface == pdisplay->m_pwlsurfaceMouseCapture)
      //       {
      //
      //          fprintf(stderr, "pointer left Mouse Capture surface\n");
      //
      //          pdisplay->m_bMouseCaptured = false;
      //
      //          ///pdisplay->__handle_pointer_enter(x, y, pwaylandwindow);
      //
      //          //return;
      //
      //       }
      //
      //       auto pwaylandwindowLeave = pdisplay->_window(pwlsurface);
      //
      //       pdisplay->__handle_pointer_leave(pwlpointer, pwaylandwindowLeave);
      //
      //    }
      //
      //
      //    void
      //    pointer_handle_motion(void * data, struct wl_pointer * pwlpointer,
      //                          uint32_t millis, wl_fixed_t sx, wl_fixed_t sy)
      //    {
      //
      //       auto x = wl_fixed_to_double(sx);
      //
      //       auto y = wl_fixed_to_double(sy);
      //
      //       //printf("Pointer moved at %0.0f %0.0f\n", x, y);
      //
      //       auto pdisplay = (display *) data;
      //
      //       //      if(pdisplay->m_bMouseCaptured)
      //       //      {
      //       //
      //       //         printf("Mouse Capture motion at %0.0f %0.0f!!\n", x, y);
      //       //
      //       //         ///pdisplay->__handle_pointer_enter(x, y, pwaylandwindow);
      //       //
      //       //         //return;
      //       //
      //       //      }
      //       //
      //
      //       pdisplay->__handle_pointer_motion(pwlpointer, x, y, millis);
      //
      //    }
      //
      //
      //    void pointer_handle_button(void * data, struct wl_pointer * pwlpointer,
      //                          uint32_t serial, uint32_t millis, uint32_t linux_button,
      //                          uint32_t pressed)
      //    {
      //
      //       fprintf(stderr, "Pointer button\n");
      //
      //       auto pdisplay = (display *) data;
      //
      //       pdisplay->m_uLastButtonSerial = serial;
      //
      //       pdisplay->m_uLastPointerSerial = serial;
      //
      //       pdisplay->m_uLastSeatSerial = serial;
      //
      //       if (linux_button == BTN_LEFT)
      //       {
      //
      //          if (pressed == WL_POINTER_BUTTON_STATE_PRESSED)
      //          {
      //
      //             pdisplay->m_pwlsurfaceLastLButtonDown = pdisplay->m_pwlsurfacePointerEnter;
      //
      //          }
      //          else
      //          {
      //
      //             //pdisplay->m_pwlsurfacePointerLButtonDown = null
      //
      //          }
      //
      //       }
      //
      //       if (pdisplay->m_pwindowKeyboardFocus)
      //       {
      //
      //          //         if (linux_button == BTN_LEFT && pressed == WL_POINTER_BUTTON_STATE_PRESSED)F
      //          //            xdg_toplevel_move(pdisplay->m_pwindowKeyboardFocus->m_pxdgtoplevel,
      //          //                                  pdisplay->m_pwlseat, serial);
      //
      //       }
      //
      //       pdisplay->__handle_pointer_button(pwlpointer, linux_button, pressed, millis);
      //
      //    }
      //
      //
      //    void
      //    pointer_handle_axis(void * data, struct wl_pointer * wl_pointer,
      //                        uint32_t time, uint32_t axis, wl_fixed_t value)
      //    {
      //       printf("Pointer handle axis\n");
      //    }
      //
      //    static const struct wl_pointer_listener g_wl_pointer_listener = {
      //       pointer_handle_enter,
      //       pointer_handle_leave,
      //       pointer_handle_motion,
      //       pointer_handle_button,
      //       pointer_handle_axis,
      //    };
      //
      //    void shm_format(void * data, struct wl_shm * wl_shm, uint32_t format)
      //    {
      //       const char * s;
      //       switch (format)
      //       {
      //       case WL_SHM_FORMAT_ARGB8888:
      //          s = "ARGB8888";
      //          break;
      //       case WL_SHM_FORMAT_XRGB8888:
      //          s = "XRGB8888";
      //          break;
      //       case WL_SHM_FORMAT_RGB565:
      //          s = "RGB565";
      //          break;
      //       case WL_SHM_FORMAT_RGBA8888:
      //          s = "RGBA8888";
      //          break;
      //       default:
      //          s = "other format";
      //          break;
      //       }
      //       fprintf(stderr, "Possible shmem format %s\n", s);
      //    }
      //
      //    static const struct wl_shm_listener shm_listener = {
      //       shm_format
      //    };
      //
      //
      //    static void
      //    keyboard_handle_keymap(void * data, struct wl_keyboard * keyboard,
      //                           uint32_t format, int fd, uint32_t size)
      //    {
      //
      //       auto pdisplay = (display *) data;
      //
      //       pdisplay->__handle_keyboard_keymap(keyboard, format, fd, size);
      //
      //    }
      //
      //    static void
      //    keyboard_handle_enter(void * data, struct wl_keyboard * pwlkeyboard,
      //                          uint32_t serial, struct wl_surface * pwlsurface,
      //                          struct wl_array * pwlarrayKeys)
      //    {
      //
      //       fprintf(stderr, "Keyboard gained focus\n");
      //
      //       auto pdisplay = (display *) data;
      //
      //       pdisplay->__handle_keyboard_enter(pwlkeyboard, serial, pwlsurface, pwlarrayKeys);
      //
      //    }
      //
      //
      //    static void
      //    keyboard_handle_leave(void * data, struct wl_keyboard * pwlkeyboard,
      //                          uint32_t serial, struct wl_surface * pwlsurface)
      //    {
      //
      //       fprintf(stderr, "Keyboard lost focus\n");
      //
      //       auto pdisplay = (display *) data;
      //
      //       pdisplay->__handle_keyboard_leave(pwlkeyboard, serial, pwlsurface);
      //
      //    }
      //
      //
      //    static void
      //    keyboard_handle_key(void * data, ::wl_keyboard * pwlkeyboard,
      //                        uint32_t serial, uint32_t time, uint32_t key,
      //                        uint32_t pressed)
      //    {
      //
      //       fprintf(stderr, "Key is %d state is %d\n", key, pressed);
      //
      //       auto pdisplay = (display *) data;
      //
      //       pdisplay->__handle_keyboard_key(pwlkeyboard, serial, time, key, pressed);
      //
      //    }
      //
      //
      //    static void
      //    keyboard_handle_modifiers(void * data, ::wl_keyboard * pwlkeyboard,
      //                              uint32_t serial, uint32_t mods_depressed,
      //                              uint32_t mods_latched, uint32_t mods_locked,
      //                              uint32_t group)
      //    {
      //
      //       fprintf(stderr, "Modifiers depressed %d, latched %d, locked %d, group %d\n",
      //               mods_depressed, mods_latched, mods_locked, group);
      //
      //       auto pdisplay = (display *) data;
      //
      //       pdisplay->__handle_keyboard_modifiers(pwlkeyboard, serial, mods_depressed, mods_latched, mods_locked, group);
      //
      //    }
      //
      //    static const struct wl_keyboard_listener g_wl_keyboard_listener = {
      //       keyboard_handle_keymap,
      //       keyboard_handle_enter,
      //       keyboard_handle_leave,
      //       keyboard_handle_key,
      //       keyboard_handle_modifiers,
      //    };
      //
      //    void
      //    seat_handle_capabilities(void * data, struct wl_seat * seat,
      //                             uint32_t caps)
      //    {
      //       auto pdisplay = (display *) data;
      //
      //       if (caps & WL_SEAT_CAPABILITY_KEYBOARD && !pdisplay->m_pwlkeyboard)
      //       {
      //
      //          pdisplay->m_pwlkeyboard = wl_seat_get_keyboard(seat);
      //
      //          wl_keyboard_add_listener(pdisplay->m_pwlkeyboard, &g_wl_keyboard_listener, data);
      //
      //       }
      //       else if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD) && pdisplay->m_pwlkeyboard)
      //       {
      //
      //          wl_keyboard_destroy(pdisplay->m_pwlkeyboard);
      //
      //          pdisplay->m_pwlkeyboard = NULL;
      //
      //       }
      //
      //       if ((caps & WL_SEAT_CAPABILITY_POINTER) && !pdisplay->m_pwlpointer)
      //       {
      //
      //          pdisplay->m_pwlpointer = wl_seat_get_pointer(seat);
      //
      //          wl_pointer_add_listener(pdisplay->m_pwlpointer, &g_wl_pointer_listener, data);
      //
      //       }
      //       else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && pdisplay->m_pwlpointer)
      //       {
      //
      //          wl_pointer_destroy(pdisplay->m_pwlpointer);
      //
      //          pdisplay->m_pwlpointer = NULL;
      //
      //       }
      //
      //    }
      //
      //    static const struct wl_seat_listener g_wl_seat_listener = {
      //       seat_handle_capabilities,
      //    };
      //
      //    void xdg_wm_base_ping(void * data,
      //                          struct xdg_wm_base * xdg_wm_base,
      //                          uint32_t serial)
      //    {
      //
      //       xdg_wm_base_pong(xdg_wm_base, serial);
      //
      //    }
      //
      //    static const struct xdg_wm_base_listener g_xdg_wm_base_listener =
      //       {
      //       xdg_wm_base_ping
      //
      //    };
      //
      //
      //    void global_registry_handler(void * data, struct wl_registry * pwlregistry, uint32_t id,
      //                                 const char * interface, uint32_t version)
      //    {
      //
      //       auto pdisplay = (display *) data;
      //
      //       if (strcmp(interface, "wl_compositor") == 0)
      //       {
      //
      //          pdisplay->m_pwlcompositor = (::wl_compositor *) wl_registry_bind(pwlregistry, id, &wl_compositor_interface, 1);
      //
      //       }
      //       else if (strcmp(interface, "xdg_wm_base") == 0)
      //       {
      //
      //          pdisplay->m_pxdgwmbase = (::xdg_wm_base *) wl_registry_bind(pwlregistry, id, &xdg_wm_base_interface, 1);
      //
      //          xdg_wm_base_add_listener(pdisplay->m_pxdgwmbase, &g_xdg_wm_base_listener, data);
      //
      //       }
      //       else if (strcmp(interface, "wl_subcompositor") == 0)
      //       {
      //
      //          pdisplay->m_pwlsubcompositor = (::wl_subcompositor *) wl_registry_bind(pwlregistry, id,
      //                                                                                 &wl_subcompositor_interface, 1);
      //
      //       }
      //       else if (strcmp(interface, "wl_shm") == 0)
      //       {
      //
      //          pdisplay->m_pwlshm = (::wl_shm *) wl_registry_bind(pwlregistry, id, &wl_shm_interface, 1);
      //
      //          wl_shm_add_listener(pdisplay->m_pwlshm, &shm_listener, data);
      //
      //       }
      //       else if (strcmp(interface, "wl_seat") == 0)
      //       {
      //
      //          pdisplay->m_pwlseat = (::wl_seat *) wl_registry_bind(pwlregistry, id, &wl_seat_interface, 1);
      //
      //          wl_seat_add_listener(pdisplay->m_pwlseat, &g_wl_seat_listener, data);
      //
      //       }
      //       else if (strcmp(interface, "wl_output") == 0)
      //       {
      //
      //          auto pwloutput = (::wl_output *) wl_registry_bind(pwlregistry, id, &wl_output_interface, 1);
      //
      //          if (pdisplay->m_wloutputa.add_unique(pwloutput) >= 0)
      //          {
      //
      //             wl_output_add_listener(pwloutput, &g_wl_output_listener, data);
      //
      //          }
      //
      //       }
      //       else if (strcmp(interface, "xdg_activation_v1") == 0)
      //       {
      //          pdisplay->m_pxdgactivationv1 = (::xdg_activation_v1 *) wl_registry_bind(pwlregistry, id,
      //                                                                                  &xdg_activation_v1_interface, 1);
      //
      //       }
      //       else if (strcmp(interface, "gtk_shell1") == 0)
      //       {
      //          pdisplay->m_pgtkshell1 = (::gtk_shell1 *) wl_registry_bind(pwlregistry, id, &gtk_shell1_interface, 1);
      //
      //       }
      //
      //
      //       pdisplay->informationf("registry interface : %s", interface);
      //
      //
      //    }
      //
      //    void global_registry_remover(void * data, struct wl_registry * registry, uint32_t id)
      //    {
      //
      //       printf("Got a registry losing happening for %d\n", id);
      //
      //    }
      //
      //    static const struct wl_registry_listener g_wl_registry_listener =
      //       {
      //       global_registry_handler,
      //       global_registry_remover
      //    };
      //

         // display::display()
         // {
         //
         //    //m_pxkbkeymap = nullptr;
         //    //m_pxkbstate = nullptr;
         //    m_bOpened = false;
         //    m_pgdkdisplay = nullptr;
         //
         //
         //
         //    // //::wl_display * m_pwldisplay;
         //    // m_pwlshm = nullptr;
         //    // m_pxdgwmbase = nullptr;
         //    // m_pwlcompositor = nullptr;
         //    // m_pwlsurfaceCursor = nullptr;
         //    // m_pwlseat = nullptr;
         //    // m_pwlkeyboard = nullptr;
         //    // m_pwlpointer = nullptr;
         //    // m_pwlsubcompositor = nullptr;
         //    // //::wl_shm_pool * m_pwlshmpool;
         //    // m_pwlsurfacePointerEnter = nullptr;
         //    // m_pwlsurfaceLastLButtonDown = nullptr;
         //    // m_pwlsurfaceMouseCapture = nullptr;
         //    // m_pxdgsurfaceMouseCapture = nullptr;
         //    // m_pxdgtoplevelMouseCapture = nullptr;
         //    // //wayland_buffer m_waylandbufferMouseCapture;
         //    // m_bMouseCaptured = false;
         //    // //::int_rectangle m_rectangleMouseCapture;
         //    // m_uLastButtonSerial = 0;
         //    // m_uLastPointerSerial = 0;
         //    // m_uLastSeatSerial = 0;
         //    // m_uLastKeyboardSerial = 0;
         //    // m_uLastKeyboardEnterSerial = 0;
         //    // m_uLastKeyboardLeaveSerial = 0;
         //    // m_pgtkshell1 = nullptr;
         //    // m_pxdgactivationv1 = nullptr;
         //    // m_pwlsurfaceKeyboardEnter = nullptr;
         //
         // }


         // display::~display()
         // {
         //
         //    // if(s_pdisplaybase == this)
         //    // {
         //    //
         //    //    s_pdisplaybase = nullptr;
         //    //
         //    // }
         //
         //    close();
         //
         // }

         //
         // void display::initialize(::particle * pparticle)
         // {
         //    ::acme::windowing::display::initialize(pparticle);
         //    // ::xkb_input::xkb_input::initialize(pparticle);
         //    //
         //    // m_pxkbcontext = xkb_context_new({});
         //    //
         //    // if (!m_pxkbcontext)
         //    // {
         //    //
         //    //    throw ::exception(error_failed, "Failed to xkb_context_new");
         //    //
         //    // }
         //
         // }

         //
         // ::GdkDisplay * display::__get_gdk_display()
         // {
         //
         //    return m_pgdkdisplay;
         //
         // }


    //      void display::open()
    //      {
    //
    //         if(m_bOpened)
    //         {
    //
    //            return;
    //
    //         }
    //
    //         m_bOpened = true;
    //
    //         user_send([this]()
    //         {
    //
    //            //set_main_user_thread();
    //
    //            if(!m_pgdkdisplay)
    //            {
    //
    //               m_pgdkdisplay = __get_gdk_display();
    //
    //            }
    //
    //            information() << "gtk4::acme::windowing::display::open";
    //
    //            information() << "gtk4::acme::windowing::display::open pgdkdisplay : " << (::iptr) m_pgdkdisplay;
    //
    //   //          auto pwlregistry = wl_display_get_registry(m_pwldisplay);
    //   //
    //   //          wl_registry_add_listener(pwlregistry, &::wayland::micro::g_wl_registry_listener, this);
    //   //
    //   //          wl_display_dispatch(m_pwldisplay);
    //   //
    //   //          wl_display_roundtrip(m_pwldisplay);
    //   //
    //   //          m_pwlsurfaceCursor = wl_compositor_create_surface(m_pwlcompositor);
    //   //
    //   // //      fork([this]()
    //   // //           {
    //   // //
    //   // //
    //   // ////              redraw(NULL, NULL, 0);
    //   // //
    //   // //              while (wl_display_dispatch(m_pwldisplay) != -1)
    //   // //              {
    //   // //
    //   // //
    //   // //              }
    //   // //
    //   // //              wl_display_disconnect(m_pwldisplay);
    //   // //              //printf("disconnected from display\n");
    //   // //
    //   // //
    //   // //           });
    //   //
    //   //                                //bool bBranch = !session()->user()->m_pdesktopenvironment->m_bUnhook;
    //   //
    //   // //      m_px11display->m_bUnhook = bUnhook;
    //   //
    //   // //auto px11displayGdk = _get_system_default_display();
    //   //
    //   // //m_px11display = ::x11::display::get(this, false, px11displayGdk);
    //   //
    //   // // Using another ___new and different X11 Display connection apart from Gtk.
    //   // //m_px11display = ::x11::display::get(this, false);
    //   //
    //   // //if (::is_null(m_px11display))
    //   // //{
    //   //
    //   // // throw ::exception(error_failed);
    //   //
    //   // //}
    //   //
    //   // //_m_pX11Display = m_px11display->m_pdisplay;
    //   //
    //   // //m_px11display->m_bUnhook = true;
    //   //
    //   // //      if (XMatchVisualInfo(m_px11display->m_pdisplay, DefaultScreen(m_px11display->m_pdisplay), 32, TrueColor,
    //   // //                           &m_visualinfo))
    //   // //      {
    //   // //
    //   // //         m_pvisual = m_visualinfo.visual;
    //   // //
    //   // //      }
    //   // //      else
    //   // //      {
    //   // //
    //   // //         zero(m_visualinfo);
    //   // //
    //   // //      }
    //   //
    //   // //      ::Display * pdisplay = m_px11display->m_pdisplay;
    //   // //
    //   // //      m_iScreen = XDefaultScreen(pdisplay);
    //   // //
    //   // //      m_windowRoot = XRootWindow(pdisplay, m_iScreen);
    //   // //
    //   // //      m_iDepth = m_visualinfo.depth;
    //   // //
    //   // //      XSetWindowAttributes attr;
    //   // //
    //   // //      zero(attr);
    //   // //
    //   // //      m_colormap = XCreateColormap(m_px11display->m_pdisplay, m_windowRoot, m_pvisual, AllocNone);
    //   // //
    //   // //      m_bHasXSync = false;
    //   // //
    //   // //#ifdef HAVE_XSYNC
    //   // //
    //   // //      {
    //   // //
    //   // //         int error_base, event_base;
    //   // //
    //   // //         if (XSyncQueryExtension(m_px11display->m_pdisplay, &event_base, &error_base) &&
    //   // //             XSyncInitialize(m_px11display->m_pdisplay, &m_iXSyncMajor, &m_iXSyncMinor))
    //   // //         {
    //   // //
    //   // //            m_bHasXSync = true;
    //   // //
    //   // //         }
    //   // //
    //   // //      }
    //   // //
    //   // //#endif
    //   // //
    //   // //      if (m_bHasXSync)
    //   // //      {
    //   // //
    //   // //         information() << "Display supports XSync";
    //   // //
    //   // //      }
    //   // //      else
    //   // //      {
    //   // //
    //   // //         information() << "Display doesn't support XSync";
    //   // //
    //   // //      }
    //   //
    //   // //      //m_atomCardinal = intern_atom("CARDINAL", True);
    //   // //      m_atomWmProtocols = intern_atom("WM_PROTOCOLS", True);
    //   // //      m_atomWmState = intern_atom("WM_STATE", false);
    //   // //      m_atomNetWmState = intern_atom("_NET_WM_STATE", false);
    //   // //      m_atomNetWmSyncRequest = intern_atom("_NET_WM_SYNC_REQUEST", True);
    //   // //      m_atomNetWmSyncRequestCounter = intern_atom("_NET_WM_SYNC_REQUEST_COUNTER", True);
    //   // //      m_atomNetWmStateFocused = intern_atom("_NET_WM_STATE_FOCUSED", True);
    //   // //      m_atomNetWmStateHidden = intern_atom("_NET_WM_STATE_HIDDEN", True);
    //   // //      m_atomNetWmStateMaximizedHorz = intern_atom("_NET_WM_STATE_MAXIMIZED_HORZ", True);
    //   // //      m_atomNetWmStateMaximizedVert = intern_atom("_NET_WM_STATE_MAXIMIZED_VERT", True);
    //   // //
    //   // //
    //   // //      long *workArea;
    //   // //      int format;
    //   // //      unsigned long items, bytesAfter;
    //   // //      uint8_t *prop;
    //   // //      Atom type;
    //   // //      Atom _NET_WORKAREA = XInternAtom(pdisplay, "_NET_WORKAREA", 0);
    //   // //      m_rectangleaWorkAreas.clear();
    //   // //      if(XGetWindowProperty(pdisplay, m_windowRoot,
    //   // //                            _NET_WORKAREA, 0, ~0, False,
    //   // //                            XA_CARDINAL, &type, &format, &items, &bytesAfter, (uint8_t **)&workArea) || !workArea)
    //   // //      {
    //   // //         warningf("error getting desktop work area, using root window size");
    //   // //      }
    //   // //      else
    //   // //      {
    //   // //         //logMsg("work area: %ld:%ld:%ld:%ld", workArea[0], workArea[1], workArea[2], workArea[3]);
    //   // //         for(int iPos = 0; iPos + 3 < items; iPos+=4)
    //   // //         {
    //   // //            m_rectangleaWorkAreas.add(::int_rectangle_dimension(
    //   // //               workArea[iPos], workArea[iPos+1],
    //   // //               workArea[iPos+2], workArea[iPos+3]));
    //   // //         }
    //   // //         XFree(workArea);
    //   // //      }
    //   // //
    //   // ////      for(auto & r : rectanglea)
    //   // ////      {
    //   // ////         auto pmonitor = get_best_monitor(r);
    //   // ////
    //   // ////         if(::is_set(pmonitor))
    //   // ////         {
    //   // ////
    //   // ////            pmonitor->set_workspace_rectangle(r);
    //   // ////
    //   // ////         }
    //   // ////
    //   // ////      }
    //
    //            m_sizeaMonitor.clear();
    //
    // //m_pgdkdisplay = gdk_display_get_default();
    //
    // auto * monitors = gdk_display_get_monitors(m_pgdkdisplay);
    //
    //
    // guint n_monitors = g_list_model_get_n_items(monitors);
    //
    // // Iterate over each monitor
    // for (guint i = 0; i < n_monitors; i++) {
    //    GdkMonitor *monitor = GDK_MONITOR(g_list_model_get_item(monitors, i));
    //
    //    //auto pmonitor = __create_new < ::windowing::monitor >();
    //
    //    //pmonitor->m_pdisplay = this;
    //
    //
    //    // Get the geometry (rectangle) of the monitor
    //    GdkRectangle geometry;
    //    gdk_monitor_get_geometry(monitor, &geometry);
    //
    //    // Print monitor geometry details
    //    ::int_rectangle r;
    //    printf("Monitor %u: x = %d, y = %d, width = %d, height = %d\n",
    //           i, geometry.x, geometry.y, geometry.width, geometry.height);
    //    ::copy(r, geometry);
    //    //::copy(pmonitor->m_rectangleWorkspace, geometry);
    //
    //    m_sizeaMonitor.add(r.size());
    //
    //
    //    // Unref the monitor object as we no longer need it
    //    g_object_unref(monitor);
    //
    //    //m_monitora.add(pmonitor);
    // }
    //
    //
    //                   });
    //
    //
    //      }
    //
    //
    //      void display::close()
    //      {
    //
    //
    //         // if (m_pxkbcontext)
    //         // {
    //         //
    //         //    ::xkb_context_unref(m_pxkbcontext);
    //         //
    //         //    m_pxkbcontext = nullptr;
    //         //
    //         // }
    //
    //         if (m_pgdkdisplay)
    //         {
    //
    //            //::wl_display_disconnect(m_pgdkdisplay);
    //
    //            m_pgdkdisplay = nullptr;
    //
    //         }
    //
    //
    //      }
    //
    //
    //      void display::destroy()
    //      {
    //
    //         close();
    //
    //         ::acme::windowing::display::destroy();
    //
    //      }
    //
    //
    //      void display::display_post(const ::procedure & procedure)
    //      {
    //
    //         __check_refdbg
    //
    //         system()->acme_windowing()->_main_post(procedure);
    //
    //         __check_refdbg
    //
    //      }
    //

         // ::gtk4::acme::windowing::window * display::_window(::GtkWidget * pgtkwidget)
         // {
         //
         //    if (!pgtkwidget)
         //    {
         //
         //       return nullptr;
         //
         //    }
         //
         //    critical_section_lock synchronouslock(&m_criticalsectionWindowMap);
         //
         //    auto passociation = m_windowmap.plookup(pgtkwidget);
         //
         //    if (passociation.is_null())
         //    {
         //
         //       return nullptr;
         //
         //    }
         //
         //    return passociation->m_element2;
         //
         // }

         //
         // ::GdkDisplay * display::_gdk_display()
         // {
         //
         //    return ::is_null(this) ? nullptr : m_pgdkdisplay;
         //
         // }
         //
         //
         // ::GdkDisplay * display::_gdk_display() const
         // {
         //
         //    return ::is_null(this) ? nullptr : m_pgdkdisplay;
         //
         // }


         // void display::destroy_wayland_buffer(buffer & waylandbuffer)
         // {
         //
         //    if (waylandbuffer.m_pwlbuffer)
         //    {
         //
         //       wl_buffer_destroy(waylandbuffer.m_pwlbuffer);
         //
         //       waylandbuffer.m_pwlbuffer = nullptr;
         //
         //    }
         //
         //    if (waylandbuffer.m_pwlshmpool)
         //    {
         //
         //       wl_shm_pool_destroy(waylandbuffer.m_pwlshmpool);
         //
         //       waylandbuffer.m_pwlshmpool = nullptr;
         //
         //    }
         //
         //    if (waylandbuffer.m_pdata && waylandbuffer.m_memsizeStorage > 0)
         //    {
         //
         //       munmap(waylandbuffer.m_pdata, waylandbuffer.m_memsizeStorage);
         //
         //       waylandbuffer.m_pdata = nullptr;
         //
         //       waylandbuffer.m_memsizeStorage = 0;
         //
         //       waylandbuffer.m_memsize2 = 0;
         //
         //    }
         //
         //    if (waylandbuffer.m_unistdfile.is_opened())
         //    {
         //
         //       waylandbuffer.m_unistdfile.close();
         //
         //    }
         //
         //    waylandbuffer.m_size.cx() = 0;
         //
         //    waylandbuffer.m_size.cy() = 0;
         //
         //    waylandbuffer.m_stride = 0;
         //
         // }
         //
         //
         // void display::update_wayland_buffer(buffer & waylandbuffer, const ::int_size & size)
         // {
         //
         //    //wayland_buffer waylandbuffer{};
         //
         //    int iNewStride = size.cx() * 4; // 4 bytes per pixel;
         //
         //    ::memsize memsizeNew = iNewStride * size.cy();
         //
         //    if (memsizeNew > waylandbuffer.m_memsizeStorage)
         //    {
         //
         //       destroy_wayland_buffer(waylandbuffer);
         //
         //       waylandbuffer.m_memsizeStorage = memsizeNew * 2;
         //
         //       //waylandbuffer
         //
         //       //}
         //
         //       //waylandbuffer.m_stride =
         //
         //       //waylandbuffer.m_memsize = waylandbuffer.m_stride * size.cy();
         //
         //       waylandbuffer.m_unistdfile.create_anonymous_file(waylandbuffer.m_memsizeStorage);
         //
         //       if (!waylandbuffer.m_unistdfile.is_opened())
         //       {
         //
         //          error() << "creating a buffer file for wl_buffer failed: ";
         //
         //          waylandbuffer.m_stride = 0;
         //
         //          waylandbuffer.m_memsize2 = 0;
         //
         //          waylandbuffer.m_memsizeStorage = 0;
         //
         //          return;
         //
         //       }
         //
         //       waylandbuffer.m_pdata = mmap(
         //          NULL, waylandbuffer.m_memsizeStorage,
         //          PROT_READ | PROT_WRITE, MAP_SHARED,
         //          waylandbuffer.m_unistdfile.m_iFile, 0);
         //
         //       if (waylandbuffer.m_pdata == MAP_FAILED)
         //       {
         //
         //          error() << "mmap failed";
         //
         //          waylandbuffer.m_unistdfile.close();
         //
         //          waylandbuffer.m_stride = 0;
         //
         //          waylandbuffer.m_memsize2 = 0;
         //
         //          waylandbuffer.m_memsizeStorage = 0;
         //
         //          waylandbuffer.m_pdata = nullptr;
         //
         //          return;
         //
         //       }
         //
         //       waylandbuffer.m_pwlshmpool = wl_shm_create_pool(m_pwlshm, waylandbuffer.m_unistdfile.m_iFile, waylandbuffer.m_memsizeStorage);
         //
         //    }
         //
         //    waylandbuffer.m_stride = iNewStride;
         //
         //    waylandbuffer.m_memsize2 = memsizeNew;
         //
         //    if (waylandbuffer.m_pwlbuffer)
         //    {
         //
         //       wl_buffer_destroy(waylandbuffer.m_pwlbuffer);
         //
         //       waylandbuffer.m_pwlbuffer = nullptr;
         //
         //    }
         //
         //    waylandbuffer.m_pwlbuffer = wl_shm_pool_create_buffer(waylandbuffer.m_pwlshmpool, 0,
         //                                                          size.cx(), size.cy(),
         //                                                          waylandbuffer.m_stride,
         //                                                          WL_SHM_FORMAT_ARGB8888);
         //
         //    //wl_buffer_add_listener(buffer, &buffer_listener, buffer);
         //
         //    waylandbuffer.m_size = size;
         //
         //    //return waylandbuffer;
         //
         // }
         //
         //
         // void display::update_wayland_buffer(buffer & waylandbuffer, ::pixmap * ppixmap)
         // {
         //
         //    update_wayland_buffer(waylandbuffer, ppixmap->size());
         //
         //    ppixmap->map();
         //
         //    copy_image32((::image32_t *) waylandbuffer.m_pdata,
         //                 waylandbuffer.m_size,
         //                 waylandbuffer.m_stride,
         //                 ppixmap->data(), ppixmap->scan_size());
         //
         //    //return waylandbuffer;
         //
         // }


         // ::GtkWidget * display::_gtk_widget_focus()
         // {
         //
         //    // if (m_pwlsurfaceKeyboardEnter)
         //    // {
         //    //
         //    //    return m_pwlsurfaceKeyboardEnter;
         //    //
         //    // }
         //    // else if (m_pwlsurfaceLastLButtonDown)
         //    // {
         //    //
         //    //    return m_pwlsurfaceLastLButtonDown;
         //    //
         //    // }
         //    //
         //    return nullptr;
         //
         // }
         //

         // //void display::__handle_pointer_enter(::wl_pointer * pwlpointer, double x, double y,
         // //                                        ::wayland::micro::window_base * pwindowPointerEnter)
         //
         // void display::__handle_pointer_enter(struct wl_pointer * pwlpointer,
         //                      uint32_t serial, struct wl_surface * pwlsurface,
         //                      double x, double y)
         // {
         //
         //    //auto x = wl_fixed_to_double(sx);
         //    //auto y = wl_fixed_to_double(sy);
         //
         //    struct wl_buffer * buffer;
         //
         //    struct wl_cursor_image * image;
         //
         //    //fprintf(stderr, "Pointer entered surface %p at %0.0f %0.0f\n", pwlsurface, x, y);
         //
         //    //auto pdisplay = (display *) data;
         //
         //    //pdisplay->__handle_pointer_enter(pwlpointer, serial, pwlsurface, sx, sy);
         //
         //    m_uLastPointerSerial = serial;
         //
         //    m_uLastSeatSerial = serial;
         //
         //    if (pwlsurface == m_pwlsurfaceMouseCapture)
         //    {
         //
         //       fprintf(stderr, "entered Mouse Capture surface at %0.0f %0.0f!!\n", x, y);
         //
         //       m_bMouseCaptured = true;
         //
         //       ///pdisplay->__handle_pointer_enter(x, y, pwaylandwindow);
         //
         //       return;
         //
         //    }
         //
         //    information() << "display::__handle_pointer_enter : " << (::iptr) pwlsurface;
         //
         //    auto pwindowPointerEnter = _window(pwlsurface);
         //
         //    if(::is_null(pwindowPointerEnter))
         //    {
         //
         //       information() << "display::__handle_pointer_enter not found surface window : " << (::iptr) pwindowPointerEnter;
         //
         //       return;
         //
         //    }
         //
         //    //auto pcursor = pwaylandwindow->get_mouse_cursor();
         //
         //    //      auto pwlsurfaceCursor =  pdisplay->m_pwlsurfaceCursor;
         //    //
         //    //      ::pointer < ::windowing_wayland::cursor > pwaylandcursor = pcursor;
         //
         //    //image = default_cursor->images[0];
         //    //buffer = wl_cursor_image_get_buffer(image);
         //
         //    //      if(pwaylandcursor)
         //    //      {
         //    //
         //    //         wl_pointer_set_cursor(pwlpointer, serial,
         //    //                               pwlsurfaceCursor,
         //    //                               pwaylandcursor->m_szHotspotOffset.cx(),
         //    //                               pwaylandcursor->m_szHotspotOffset.cy());
         //    //         wl_surface_attach(pwlsurfaceCursor, pwaylandcursor->m_waylandbuffer.m_pwlbuffer, 0, 0);
         //    //         wl_surface_damage(pwlsurfaceCursor, 0, 0, pwaylandcursor->m_pimage->width(),
         //    //                           pwaylandcursor->m_pimage->height());
         //    //         wl_surface_commit(pwlsurfaceCursor);
         //    //
         //    //      }
         //
         //    //      pdisplay->__handle_pointer_enter(pwlpointer, x, y, pwaylandwindow);
         //    //
         //    //   }
         //    //
         //    //{
         //
         //    m_pwindowPointerEnter = pwindowPointerEnter;
         //
         //    if (m_pwindowPointerEnter)
         //    {
         //
         //       //m_pwindowPointerEnter->m_pointPointer.x() = (double) m_pwindowPointerEnter->m_pointWindow.x() + x;
         //
         //       //m_pwindowPointerEnter->m_pointPointer.y() = (double) m_pwindowPointerEnter->m_pointWindow.y() + y;
         //
         //       m_pwindowPointerEnter->m_pointCursor2.x() = x;
         //
         //       m_pwindowPointerEnter->m_pointCursor2.y() = y;
         //
         //       m_pwindowPointerEnter->__handle_pointer_enter(pwlpointer);
         //
         //    }
         //
         // }
         //
         //
         // void display::__handle_pointer_motion(::wl_pointer * pwlpointer, double x, double y, unsigned int millis)
         // {
         //
         //    ::int_point pointCursor((int) x, (int) y);
         //
         //    if (m_pwindowPointerCapture)
         //    {
         //
         //       m_pwindowPointerCapture->m_sizeDrag = pointCursor - m_pwindowPointerCapture->m_pointCursor2;
         //
         //       m_pwindowPointerCapture->m_pointCursor2 = pointCursor;
         //
         //       if (m_pwindowPointerEnter)
         //       {
         //
         //          m_pwindowPointerEnter->m_sizeDrag = pointCursor - m_pwindowPointerEnter->m_pointCursor2;
         //
         //          m_pwindowPointerEnter->m_pointCursor2 = pointCursor;
         //
         //       }
         //
         //    }
         //    else if (m_pwindowPointerEnter)
         //    {
         //
         //       m_pwindowPointerEnter->m_sizeDrag = pointCursor - m_pwindowPointerEnter->m_pointCursor2;
         //
         //       m_pwindowPointerEnter->m_pointCursor2 = pointCursor;
         //
         //    }
         //
         //
         //    if (m_pwindowPointerCapture)
         //    {
         //
         //       m_pwindowPointerCapture->__handle_pointer_motion(pwlpointer, millis);
         //
         //    }
         //    else if (m_pwindowPointerEnter)
         //    {
         //
         //       m_pwindowPointerEnter->__handle_pointer_motion(pwlpointer, millis);
         //
         //    }
         //
         // }
         //
         //
         // void
         // display::__handle_pointer_leave(::wl_pointer * pwlpointer, ::wayland::micro::window_base * pwaylandwindowLeave)
         // {
         //
         //    if (m_pwindowPointerCapture)
         //    {
         //
         //       ::minimum(m_pwindowPointerCapture->m_pointCursor2.x());
         //
         //       ::minimum(m_pwindowPointerCapture->m_pointCursor2.y());
         //
         //       if (m_pwindowPointerEnter)
         //       {
         //
         //          ::minimum(m_pwindowPointerEnter->m_pointCursor2.x());
         //
         //          ::minimum(m_pwindowPointerEnter->m_pointCursor2.y());
         //
         //       }
         //
         //    }
         //    else if (m_pwindowPointerEnter)
         //    {
         //
         //       ::minimum(m_pwindowPointerEnter->m_pointCursor2.x());
         //
         //       ::minimum(m_pwindowPointerEnter->m_pointCursor2.y());
         //
         //    }
         //
         //    if (m_pwindowPointerCapture)
         //    {
         //
         //       m_pwindowPointerCapture->__handle_pointer_leave(pwlpointer, pwaylandwindowLeave);
         //
         //    }
         //    else if (m_pwindowPointerEnter)
         //    {
         //
         //       m_pwindowPointerEnter->__handle_pointer_leave(pwlpointer, pwaylandwindowLeave);
         //
         //    }
         //
         //    if (m_pwindowPointerEnter == pwaylandwindowLeave)
         //    {
         //
         //       m_pwindowPointerEnter.release();
         //
         //    }
         //
         // }
         //
         //
         // void display::__handle_pointer_button(::wl_pointer * pwlpointer, unsigned int linux_button, unsigned int pressed, unsigned int millis)
         // {
         //
         //    if (m_pwindowPointerCapture)
         //    {
         //
         //       information() << "display::__handle_pointer_button m_pwindowPointerCapture";
         //
         //       m_pwindowPointerCapture->__handle_pointer_button(pwlpointer, linux_button, pressed, millis);
         //
         //    }
         //    else if (m_pwindowPointerEnter)
         //    {
         //
         //       information() << "display::__handle_pointer_button m_pwindowPointerEnter";
         //
         //       m_pwindowPointerEnter->__handle_pointer_button(pwlpointer, linux_button, pressed, millis);
         //
         //    }
         //    else
         //    {
         //
         //       information() << "MISSED BUTTON PRESS/RELEASE: at display::__handle_pointer_button";
         //
         //    }
         //
         // }
         //
         //
         // void display::__handle_keyboard_keymap(::wl_keyboard * pwlkeyboard, uint32_t format, int fd, uint32_t size)
         // {
         //
         //    //      ::pointer < ::windowing_wayland::keyboard > pkeyboard = m_pwindowing->keyboard();
         //    //
         //    //      pkeyboard->__handle_keyboard_keymap(pwlkeyboard, format, fd, size);
         //
         //
         //    if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1)
         //    {
         //
         //       error() << "Only supported format is WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1";
         //
         //       return;
         //
         //    }
         //
         //    void * p = ::mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
         //
         //    if (p != MAP_FAILED)
         //    {
         //
         //       error() << "wl_keyboard keymap mmap Failed";
         //
         //    }
         //
         //    synchronous_lock synchronouslock(this->synchronization());
         //
         //    //      ::pointer < ::xkb_input::xkb_input > pxkbinput = system()->m_pinput;
         //    //
         //    //      if(pxkbinput)
         //    //      {
         //    //
         //    //         pxkbinput->xkb_keymap_new_from_string((const char *) p, XKB_KEYMAP_FORMAT_TEXT_V1,
         //    //                                             XKB_KEYMAP_COMPILE_NO_FLAGS);
         //    //
         //    //      }
         //
         //    m_pxkbkeymap = ::xkb_keymap_new_from_string(
         //       m_pxkbcontext, (const char *) p, XKB_KEYMAP_FORMAT_TEXT_V1,
         //       XKB_KEYMAP_COMPILE_NO_FLAGS);
         //
         //    ::munmap(p, size);
         //
         //    ::close(fd);
         //
         //    m_pxkbstate = ::xkb_state_new(m_pxkbkeymap);
         //    if (!m_pxkbstate)
         //    {
         //       fprintf(stderr, "failed to create XKB state\n");
         //       ::xkb_keymap_unref(m_pxkbkeymap);
         //       m_pxkbkeymap = NULL;
         //       return;
         //    }
         //
         // }
         //
         //
         // void display::__handle_keyboard_enter(::wl_keyboard * pwlkeyboard, uint32_t serial, ::wl_surface * pwlsurface,
         //                                            ::wl_array * pwlarrayKeys)
         // {
         //
         //    information() << "display::__handle_keyboard_enter";
         //
         //    m_pwlkeyboard = pwlkeyboard;
         //
         //    m_pwlsurfaceKeyboardEnter = pwlsurface;
         //
         //    m_uLastSeatSerial = serial;
         //    m_uLastKeyboardSerial = serial;
         //    m_uLastKeyboardEnterSerial = serial;
         //
         //    information() << "display::__handle_keyboard_enter : " << (::iptr) pwlsurface;
         //
         //    auto pwaylandwindow = _window(pwlsurface);
         //
         //    if (!pwaylandwindow)
         //    {
         //
         //       error() << "Could not find pwaylandwindow from pwlsurface";
         //
         //       return;
         //
         //    }
         //
         //    ::string strType(::type(pwaylandwindow));
         //
         //    information() << "display::__handle_keyboard_enter : " << strType;
         //
         //    m_pwindowKeyboardFocus = pwaylandwindow;
         //
         //    m_pwindowKeyboardFocus->__handle_keyboard_enter(pwlkeyboard, serial, pwlarrayKeys);
         //
         // }
         //
         //
         // void display::__handle_keyboard_leave(::wl_keyboard * pwlkeyboard, uint32_t serial, ::wl_surface * pwlsurface)
         // {
         //
         //    if (pwlkeyboard == m_pwlkeyboard)
         //    {
         //
         //       m_pwlkeyboard = nullptr;
         //
         //    }
         //
         //    if (pwlsurface == m_pwlsurfaceKeyboardEnter)
         //    {
         //
         //       m_pwlsurfaceKeyboardEnter = nullptr;
         //
         //    }
         //
         //    m_uLastSeatSerial = serial;
         //    m_uLastKeyboardSerial = serial;
         //    m_uLastKeyboardLeaveSerial = serial;
         //
         //    auto pwaylandwindow = _window(pwlsurface);
         //
         //    if (!pwaylandwindow)
         //    {
         //
         //       error() << "Could not find pwaylandwindow from pwlsurface (2)";
         //
         //       return;
         //
         //    }
         //
         //    if (m_pwindowKeyboardFocus != pwaylandwindow)
         //    {
         //
         //       error() << "What!! but ignoring what seems to be an error";
         //
         //    }
         //
         //    m_pwindowKeyboardFocus->__handle_keyboard_leave(pwlkeyboard, serial);
         //
         // }
         //
         //
         // void display::__handle_keyboard_key(::wl_keyboard * pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key,
         //                                          uint32_t state)
         // {
         //
         //    if (!m_pwindowKeyboardFocus)
         //    {
         //
         //       error() << "Keyboard key with no window with focus!!";
         //
         //       return;
         //
         //    }
         //
         //    m_pwindowKeyboardFocus->__handle_keyboard_key(pwlkeyboard, serial, time, key, state);
         //
         // }
         //
         //
         // void display::__handle_keyboard_modifiers(::wl_keyboard * pwlkeyboard, uint32_t serial, uint32_t mods_depressed,
         //                                                uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
         // {
         //
         //    if (!m_pwindowKeyboardFocus)
         //    {
         //
         //       error() << "Keyboard modifiers with no window with focus!!";
         //
         //       return;
         //
         //    }
         //
         //    m_pwindowKeyboardFocus->__handle_keyboard_modifiers(pwlkeyboard, serial, mods_depressed, mods_latched,
         //                                                        mods_locked, group);
         //
         // }
         //
         //
         // void display::__handle_wl_output_geometry(::wl_output * pwloutput,
         //                                                int32_t x,
         //                                                int32_t y,
         //                                                int32_t physical_width,
         //                                                int32_t physical_height,
         //                                                int32_t subpixel,
         //                                                const char * make,
         //                                                const char * model,
         //                                                int32_t transform)
         // {
         //
         //    auto iFind = m_wloutputa.find_first(pwloutput);
         //
         //    //      if(iFind >=0)
         //    //      {
         //    //
         //    //         m_sizeaMonitor.set_at_grow(iFind, {physical_width, physical_width});
         //    //
         //    //      }
         //
         //
         // }
         //
         //
         // void display::__handle_wl_output_mode(
         //    ::wl_output * pwloutput,
         //    uint32_t flags,
         //    int32_t width,
         //    int32_t height,
         //    int32_t refresh)
         // {
         //
         //    auto iFind = m_wloutputa.find_first(pwloutput);
         //
         //    if (flags & WL_OUTPUT_MODE_CURRENT)
         //    {
         //
         //       if (iFind >= 0)
         //       {
         //
         //          m_sizeaMonitor.set_at_grow(iFind, {width, height});
         //
         //       }
         //
         //    }
         //
         // }


         // void display::init_task()
         // {
         //
         //    ::acme::windowing::display::init_task();
         //
         //    ::task_set_name("wayland:display:run");
         //
         //    if(!m_pgdkdisplay)
         //    {
         //
         //       auto pgdkdisplay = __get_gdk_display();
         //
         //       m_pgdkdisplay = pgdkdisplay;
         //
         //    }
         //
         //    open();
         //
         // }
         //
         //
         // void display::run()
         // {
         //
         //    message_loop();
         //
         //    close();
         //
         // }
         //
         //
         // void display::message_loop()
         // {
         //
         //    while (::task_get_run())
         //    {
         //
         //       message_loop_step();
         //
         //    }
         //
         // }

         //
         // bool display::message_loop_step()
         // {
         //
         //    struct pollfd fds[1];
         //
         //    // while (wl_display_prepare_read(m_pwldisplay) != 0)
         //    //    wl_display_dispatch_pending(m_pwldisplay);
         //    // wl_display_flush(m_pwldisplay);
         //    //
         //    // /* watch stdin for input */
         //    // fds[0].fd = wl_display_get_fd(m_pwldisplay);
         //    // fds[0].happenings = POLLIN;
         //    //
         //    // int ret = poll(fds, 1, 5);
         //    // if (ret <= 0)
         //    // {
         //    //    wl_display_cancel_read(m_pwldisplay);
         //    // }
         //    // else
         //    // {
         //    //    wl_display_read_events(m_pwldisplay);
         //    //
         //    // }
         //    //
         //    // wl_display_dispatch_pending(m_pwldisplay);
         //    // while(true)
         //    // {
         //    //
         //    //    if(!display_posted_routine_step())
         //    //    {
         //    //
         //    //       break;
         //    //
         //    //    }
         //    //
         //    // }
         //
         //    return true;
         //
         // }


         // // todo color:// gradient:// if the operating system doesn't have this, create the file, please.
         // void display::_set_wallpaper(::collection::index iMonitorIndex, const ::scoped_string & scopedstrWallpaper)
         // {
         //
         //
         // }

   ::string display::_get_wallpaper(::collection::index iMonitorIndex)
   {

            ::string strLocalImagePath;

      // wall-changer sourceforge.net contribution

      // auto psystem = system();
      //
      // auto pnode = psystem->node();

      //auto edesktop = pnode->get_eoperating_ambient();

      auto edesktop = ::windowing::get_eoperating_ambient();

      //bool bDark = m_strDarkModeAnnotation.case_insensitive_contains("dark");

            bool bDark = system()->acme_windowing()->dark_mode();

      switch (edesktop)
      {

         case ::windowing::e_operating_ambient_gnome:
         //case ::user::e_operating_ambient_ubuntu_gnome:
         case ::windowing::e_operating_ambient_unity:
         {

            if(bDark)
            {

               ::gdk::gsettings_get(strLocalImagePath, "org.gnome.desktop.background", "picture-uri-dark").ok();

            }
            else
            {

               ::gdk::gsettings_get(strLocalImagePath, "org.gnome.desktop.background", "picture-uri");

            }


         }
         break;
         case ::windowing::e_operating_ambient_cinnamon:

            ::gdk::gsettings_get(strLocalImagePath,"org.cinnamon.desktop.background", "picture-uri");
         break;
         case ::windowing::e_operating_ambient_mate:

             ::gdk::gsettings_get(strLocalImagePath, "org.mate.background", "picture-filename");
         break;

         case ::windowing::e_operating_ambient_lxde:

            //node()->command_system("pcmanfm -w " + strLocalImagePath, 1_min);

            break;

         case ::windowing::e_operating_ambient_xfce:
         {
            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //          if(entry.contains("image-path") || entry.contains("last-image")){
            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //      }
            //}

            ::string strOutput = node()->get_posix_shell_command_output("xfconf-query -c xfce4-desktop -p /backdrop -l");

            ::string_array stra;

            stra.add_lines(strOutput);

            for (auto & str : stra)
            {

               if (str.contains("image-path") || str.contains("last-image"))
               {

                  ::string strOutputPath = node()->get_posix_shell_command_output("xfconf-query -c xfce4-desktop -p " + str);

                  if (strOutputPath.has_character())
                  {

                     strLocalImagePath = strOutputPath;

                     break;

                  }
                  //node()->command_system(" + " -s " + strLocalImagePath, 2_min);

               }

            }

         }

            //break;

         default:

            warning() <<"Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
  //          return false;

      }
            strLocalImagePath.begins_eat("file://");

            return strLocalImagePath;
//      return true;

   }


   void display::_set_wallpaper(::collection::index iMonitorIndex, const ::scoped_string & scopedstrWallpaper)
   {

            ::string strLocalImagePath = scopedstrWallpaper;

      // wall-changer sourceforge.net contribution

      // auto psystem = system();
      //
      // auto pnode = psystem->node();

      //auto edesktop = pnode->get_eoperating_ambient();

      auto edesktop = ::windowing::get_eoperating_ambient();

      //bool bDark = m_strDarkModeAnnotation.case_insensitive_contains("dark");

            bool bDark = system()->acme_windowing()->dark_mode();

      switch (edesktop)
      {

         case ::windowing::e_operating_ambient_gnome:
         //case ::user::e_operating_ambient_ubuntu_gnome:
         case ::windowing::e_operating_ambient_unity:
         {

            if(bDark)
            {

               ::gdk::gsettings_set("org.gnome.desktop.background", "picture-uri-dark",
                                                "file://" + strLocalImagePath).ok();

            }
            else
            {

               ::gdk::gsettings_set("org.gnome.desktop.background", "picture-uri",
                                                "file://" + strLocalImagePath).ok();

            }


         }
         break;
         case ::windowing::e_operating_ambient_cinnamon:

            ::gdk::gsettings_set("org.cinnamon.desktop.background", "picture-uri", "file://"+ strLocalImagePath);
         break;
         case ::windowing::e_operating_ambient_mate:

             ::gdk::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);
         break;

         case ::windowing::e_operating_ambient_lxde:

            node()->command_system("pcmanfm -w " + strLocalImagePath, 1_min);

            break;

         case ::windowing::e_operating_ambient_xfce:
         {


            ::string strOutput = node()->get_posix_shell_command_output("xrandr --listmonitors");

            ::string_array stra;

            stra.add_lines(strOutput);

            for (auto & str : stra)
            {

               str.trim();

               auto iFind = str.find_index('+');

               if(iFind > 0)
               {

                    auto iFind2 = str.index_of(str(iFind).find_first_character_in("\t\r\n "));

                    if(iFind2 > iFind)
                    {

                        ::string strMonitorName = str.substr(iFind + 1, iFind2 - iFind - 1);

                        //node()->command_system("xfconf-query -c xfce4-desktop -p " + str + " -s " + strLocalImagePath, 2_min);

        // Compose xfconf-query commands
                        ::string strCommand;

                        strCommand.formatf(
            "xfconf-query -c xfce4-desktop -p \"/backdrop/screen0/monitor%s/workspace0/last-image\" -n -t string -s \"%s\"",
            strMonitorName.c_str(), strLocalImagePath.c_str());
                        node()->command_system(strCommand, 1_min);

                        strCommand.formatf(
            "xfconf-query -c xfce4-desktop -p \"/backdrop/screen0/monitor%s/workspace0/image-style\" -n -t int -s 3",
            strMonitorName.c_str());
                        node()->command_system(strCommand, 1_min);

                        strCommand.formatf(
            "xfconf-query -c xfce4-desktop -p \"/backdrop/screen0/monitor%s/workspace0/image-show\" -n -t bool -s true",
            strMonitorName.c_str());
                        node()->command_system(strCommand, 1_min);

                    }

               }

            }

            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //          if(entry.contains("image-path") || entry.contains("last-image")){
            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //      }
            //}

         }

            break;

         default:

            warning() <<"Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
  //          return false;

      }

//      return true;

   }


   void display::enable_wallpaper_change_notification()
   {

      // auto psystem = system();
      //
      // auto pnode = psystem->node();

      //auto edesktop = pnode->get_eoperating_ambient();

      auto edesktop = ::windowing::get_eoperating_ambient();

      switch (edesktop)
      {

         case ::windowing::e_operating_ambient_gnome:
         //case ::user::e_operating_ambient_ubuntu_gnome:
         case ::windowing::e_operating_ambient_unity:

            ::gdk::node_enable_wallpaper_change_notification(this, "org.gnome.desktop.background", "picture-uri");

            break;

         case ::windowing::e_operating_ambient_mate:

            ::gdk::node_enable_wallpaper_change_notification(this, "org.mate.background", "picture-filename");

            break;

         case ::windowing::e_operating_ambient_lxde:

            //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

            break;

         case ::windowing::e_operating_ambient_xfce:
         {
            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //          if(entry.contains("image-path") || entry.contains("last-image")){
            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //      }
            //}

         }

            break;
         default:

            warning() <<"Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
            //return "";

      }

   }


         // display * display::get(::particle * pparticle, bool bBranch, ::GdkDisplay * pgdkdisplay)
         // {
         //
         //    ::pointer < ::gtk4::acme::windowing::windowing > pwindowing = ::system()->acme_windowing();
         //
         //    return ::system()->acme_windowing()->_defer_get_display(bBranch, pgdkdisplay);
         //
         // }
         //


         // void copy(xdg_toplevel_resize_edge * presizeedge, ::experience::enum_frame * peframeSizing)
         // {
         //    auto & resizeedge = *presizeedge;
         //
         //    auto & eframeSizing = *peframeSizing;
         //
         //    switch (eframeSizing)
         //    {
         //    case ::experience::e_frame_sizing_left:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_LEFT;
         //       break;
         //    case ::experience::e_frame_sizing_top:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_TOP;
         //       break;
         //    case ::experience::e_frame_sizing_right:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_RIGHT;
         //       break;
         //    case ::experience::e_frame_sizing_bottom:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM;
         //       break;
         //    case ::experience::e_frame_sizing_top_left:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_TOP_LEFT;
         //       break;
         //    case ::experience::e_frame_sizing_top_right:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_TOP_RIGHT;
         //       break;
         //    case ::experience::e_frame_sizing_bottom_left:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT;
         //       break;
         //    case ::experience::e_frame_sizing_bottom_right:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT;
         //       break;
         //    default:
         //       resizeedge = XDG_TOPLEVEL_RESIZE_EDGE_NONE;
         //       break;
         //    }
         //
         // }



         bool display::is_x11()
         {


            //  if (GDK_IS_X11_DISPLAY(m_pgdkdisplay))
            // // {
            // //
            // //    return true;
            // //
            // // }

            return false;

         }


         bool display::is_wayland()
         {

            // if (GDK_IS_WAYLAND_DISPLAY(m_pgdkdisplay))
            // {
            //
            //    return true;
            //
            // }

            return false;

         }


         void display::_on_wallpaper_change()
         {


         }

      } // namespace windowing


   } // namespace acme


} // namespace g
