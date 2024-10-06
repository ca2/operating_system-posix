// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "cursor.h"
#include "display.h"
#include "keyboard.h"
#include "window.h"
#include "windowing.h"
//#include "windowing_gtk4.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "apex/platform/node.h"
#include "apex/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura/graphics/image/image.h"
#include "aura/windowing/desktop_environment.h"
#include "aura/windowing/monitor.h"
#include "aura_posix/node.h"
//#include "acme/operating_system/x11/display_lock.h"
//#include <X11/extensions/Xrender.h>
//#include <wayland-client-protocol.h>
extern ::app_core * g_pappcore;
//#include <fcntl.h>
//#include <sys/mman.h>
//#include <errno.h>
//#include <unistd.h>

//Display * x11_get_display();
//#include <wayland-client.h>
//#include <wayland-client-protocol.h>
//#include <xdg-shell-client-protocol.h>
::particle * user_synchronization();


void windowing_output_debug_string(const ::scoped_string & scopedstrDebugString);
//
// // Declare global variables for the Wayland objects
// struct wl_display *display = NULL;
// struct wl_compositor *compositor = NULL;
// struct xdg_wm_base *xdg_wm_base = NULL;


//
// int main() {
//    // Step 1: Connect to the Wayland display
//    display = wl_display_connect(NULL);
//    if (!display) {
//       fprintf(stderr, "Failed to connect to Wayland display\n");
//       return -1;
//    }


namespace windowing_gtk4
{

//      // Callback for registry listener to bind global Wayland objects
//      static void
//      s_registry_handler(void *data, struct wl_registry *wl_registry, uint32_t id, const char *interface, uint32_t version)
//      {
//         auto pdisplay = (::windowing_gtk4::display *) data;
//         if (strcmp(interface, wl_compositor_interface.name) == 0) {
//            //compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 1);
//         } else if (strcmp(interface, xdg_wm_base_interface.name) == 0) {
//            pdisplay->m_pxdgwmbase = (xdg_wm_base*) wl_registry_bind(wl_registry, id, &xdg_wm_base_interface, 1);
//            printf("xdg_wm_base obtained!\n");
//         }
//      }
//
//      // Callback for removing global objects (optional)
//      static void
//      s_registry_remover(void *data, struct wl_registry *registry, uint32_t id)
//      {
//         // Do nothing for now
//      }
//
//   static const struct wl_registry_listener s_registry_listener = {
//         s_registry_handler,
//         s_registry_remover
//      };
//

   display::display()
   {

      //m_bMouseCaptured = false;

      //zero(m_atoma);
         //m_pxdgwmbase=nullptr;
      //m_pwldisplay = nullptr;

      m_pDisplay = this;
      m_pgdkdisplay = nullptr;


      //m_colormap = None;
      //m_windowRoot = None;
      //m_px11display = nullptr;
      // m_pwldisplay = nullptr;
      // m_pwlshm = nullptr;
      // m_pwlcompositor = nullptr;
      // m_pxdgwmbase = nullptr;
      // m_pwlseat = nullptr;
      // m_pwlpointer = nullptr;
      // m_pwlsurfaceCursor = nullptr;
      // m_pwlsurfacePointerEnter = nullptr;
      // m_pwlsubcompositor = nullptr;
      //
      // m_pgtkshell1 = nullptr;
      // m_pxdgactivationv1 = nullptr;
      //
      // m_pwlkeyboard = nullptr;
      // m_pwlsurfaceLastLButtonDown = nullptr;
      // m_pwlsurfaceKeyboardEnter = nullptr;

      // m_uLastKeyboardSerial = 0;
      // m_uLastKeyboardEnterSerial = 0;
      // m_uLastKeyboardLeaveSerial = 0;


//      m_pxdgsurfaceMouseCapture = nullptr;
//      m_pxdgtoplevelMouseCapture = nullptr;
      //m_pwlshmpool = null;

//      m_atomLongType = None;
//      m_atomLongStyle = None;
//      m_atomNetWmState = None;
//      m_atomWmProtocols = None;
//      m_atomNetWmStateFocused = None;
//      m_atomNetWmStateHidden = None;
//      m_atomNetWmStateMaximizedHorz = None;
//      m_atomNetWmStateMaximizedVert = None;
//      m_atomNetWmSyncRequest = None;
//      m_atomNetWmSyncRequestCounter = None;
//      m_atomLongStyleEx = 0;
      m_countReference = 1;
      //m_bHasXSync = true;

   }


   display::~display()
   {

   }


#ifdef _DEBUG


   i64 display::get_ref_count()
   {

      return m_countReference;

   }


   i64 display::increment_reference_count()
   {

#ifdef WINDOWS

      return InterlockedIncrement64(&m_countReference);

#elif defined(RASPBERRYPIOS) && defined(OS32BIT)

      return __sync_add_and_fetch_4(&m_countReference,1);

#else

      return __sync_add_and_fetch(&m_countReference, 1);

#endif

   }


   i64 display::decrement_reference_count()
   {

#ifdef WINDOWS

      return InterlockedDecrement64(&m_countReference);

#elif defined(RASPBERRYPIOS) && defined(OS32BIT)

      return __sync_sub_and_fetch_4(&m_countReference,1);

#else

      return __sync_sub_and_fetch(&m_countReference, 1);

#endif

   }


   i64 display::release()
   {

      i64 i = decrement_reference_count();

      return i;

   }


#endif // DEBUG

//
//   Display * display::_get_system_default_display()
//   {
//
//      return nullptr;
//
//   }


   void display::initialize(::particle * pparticle)
   {

      ::windowing::display::initialize(pparticle);


      //::wayland::nano::windowing::display_base::initialize(pparticle);

   }


   // ::wl_display * display::__get_wayland_display()
   // {
   //
   //    if(m_pwldisplay)
   //    {
   //
   //       return m_pwldisplay;
   //
   //    }
   //
   //    ::pointer<::aura_posix::node> pauraposixnode = node();
   //
   //    m_pwldisplay = pauraposixnode->get_wayland_display();
   //
   //    if (m_pwldisplay == NULL)
   //    {
   //
   //       error() << "Can't connect to display";
   //
   //       throw ::exception(error_failed);
   //
   //    }
   //
   //    information() << "connected to display\n";
   //
   //    return m_pwldisplay;
   //
   // }


    void display::open_display()
    {

   //    display_base::open();

      m_monitora.clear();

      m_pgdkdisplay = gdk_display_get_default();

      auto * monitors = gdk_display_get_monitors(m_pgdkdisplay);


      guint n_monitors = g_list_model_get_n_items(monitors);

      // Iterate over each monitor
      for (guint i = 0; i < n_monitors; i++) {
         GdkMonitor *monitor = GDK_MONITOR(g_list_model_get_item(monitors, i));

         auto pmonitor = __create_new < ::windowing::monitor >();

         pmonitor->m_pdisplay = this;


         // Get the geometry (rectangle) of the monitor
         GdkRectangle geometry;
         gdk_monitor_get_geometry(monitor, &geometry);

         // Print monitor geometry details
         printf("Monitor %u: x = %d, y = %d, width = %d, height = %d\n",
                i, geometry.x, geometry.y, geometry.width, geometry.height);
         ::copy(pmonitor->m_rectangle, geometry);
         ::copy(pmonitor->m_rectangleWorkspace, geometry);
         // Unref the monitor object as we no longer need it
         g_object_unref(monitor);

         m_monitora.add(pmonitor);
      }

      // if(is_wayland())
      // {
      //    m_pwldisplay = gdk_wayland_display_get_wl_display(m_pgdkdisplay);
      //
      //    // Step 2: Get the registry
      //    auto * wl_registry = wl_display_get_registry(m_pwldisplay);
      //
      //    wl_registry_add_listener(wl_registry, &s_registry_listener, this);
      //
      //    // Step 3: Roundtrip to process the registry and bind the objects
      //    wl_display_roundtrip(m_pwldisplay);
      // }

    }


   bool display::has_readily_gettable_absolute_pointer_position() const
   {

      return false;

   }


//   ::windowing_gtk4::window * display::_window(::wl_surface * pwlsurface)
//   {
//
//      if (!pwlsurface)
//      {
//
//         return nullptr;
//
//      }
//
//      critical_section_lock synchronouslock(&m_criticalsectionWindowMap);
//
//      auto passociation = m_windowmap.plookup(pwlsurface);
//
//      if (passociation.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      return passociation->m_element2;
//
//   }


   void display::lock_display()
   {

      if (!is_main_thread())
      {

         informationf("not main thread");

      }

      //XLockDisplay(m_px11display->m_pdisplay);

   }


   void display::unlock_display()
   {

      //XUnlockDisplay(m_px11display->m_pdisplay);

   }




//   ::wl_surface * display::_wl_surface_focus()
//   {
//
//      if(m_pwlsurfaceKeyboardEnter)
//      {
//
//         return m_pwlsurfaceKeyboardEnter;
//
//      }
//      else if(m_pwlsurfaceLastLButtonDown)
//      {
//
//         return m_pwlsurfaceLastLButtonDown;
//
//      }
//
//      return nullptr;
//
//   }
//

//   int display::Screen()
//   {
//
//      return ::is_null(this) ? 0 : m_iScreen;
//
//   }
//
//
//   int display::Screen() const
//   {
//
//      return ::is_null(this) ? 0 : m_iScreen;
//
//   }
//
//
//   Atom display::atom_long_type()
//   {
//
//      return ::is_null(this) ? 0 : m_atomLongType;
//
//   }
//
//
//   Atom display::atom_long_style()
//   {
//
//      return ::is_null(this) ? 0 : m_atomLongStyle;
//
//   }
//
//
//   Atom display::atom_long_style_ex()
//   {
//
//      return ::is_null(this) ? 0 : m_atomLongStyleEx;
//
//   }


   bool display::is_null() const
   {

      return ::is_null(this);

   }


   bool display::get_monitor_rectangle(::collection::index iMonitor, ::rectangle_i32 & rectangle)
   {

      return ::windowing::display::get_monitor_rectangle(iMonitor, rectangle);

   }


   bool display::get_workspace_rectangle(::collection::index iMonitor, ::rectangle_i32 & rectangle)
   {

      return ::windowing::display::get_workspace_rectangle(iMonitor, rectangle);

   }


//   ::windowing::window * display::get_mouse_capture()
//   {
//
//      return m_pwindowMouseCapture;
//
//   }


   ::e_status display::release_mouse_capture()
   {

      information() << "windowing_gtk4::display::release_mouse_capture";

//      auto predicate = [this]()
//      {
//
//         synchronous_lock synchronouslock(user_synchronization());
//
//         //display_lock displaylock(Display());
//
//         information() << "XUngrabPointer";
//
//         int_bool bRet = XUngrabPointer(Display(), CurrentTime) != false;
//
//         _on_capture_changed_to(nullptr);
//
//      };
//
//      auto pwindowing = x11_windowing();
//
//      pwindowing->windowing_post(predicate);

      return ::success;

   }


   ::windowing_gtk4::windowing * display::x11_windowing()
   {

      return (::windowing_gtk4::windowing *) m_pwindowing->m_pWindowing4;

   }




//   Atom display::intern_atom(const char * pszAtomName, bool bCreate)
//   {
//
//      if (m_px11display == nullptr)
//      {
//
//         return 0;
//
//      }
//
//      return m_px11display->intern_atom(pszAtomName, bCreate);
//
//   }
//
//
//   Atom display::intern_atom(::x11::enum_atom eatom, bool bCreate)
//   {
//
//      if (eatom < 0 || eatom >= ::x11::e_atom_count)
//      {
//
//         return None;
//
//      }
//
//      //Atom atom = m_atoma[eatom];
//
//      //if (atom == None)
//      {
//
//         auto atom = intern_atom(atom_name(eatom), bCreate);
//
//         return atom;
//
//         // m_atoma[eatom] = atom;
//
//      }
//
//      //return atom;
//
//   }
//
//
//   Atom display::_intern_atom_unlocked(const char * pszAtomName, bool bCreate)
//   {
//
//      if (m_px11display == nullptr)
//      {
//
//         return 0;
//
//      }
//
//      return m_px11display->_intern_atom_unlocked(pszAtomName, bCreate);
//
//   }
//
//
//   Atom display::_intern_atom_unlocked(::x11::enum_atom eatom, bool bCreate)
//   {
//
//      if (eatom < 0 || eatom >= ::x11::e_atom_count)
//      {
//
//         return None;
//
//      }
//
//      //Atom atom = m_atoma[eatom];
//
//      //if (atom == None)
//      {
//
//         auto atom = _intern_atom_unlocked(atom_name(eatom), bCreate);
//
//         return atom;
//
//         // m_atoma[eatom] = atom;
//
//      }
//
//      //return atom;
//
//   }


   ::e_status display::erase_window(::windowing::window * pwindow)
   {

      return error_failed;

   }


//   Atom display::net_wm_state_atom(bool bCreate)
//   {
//
//      if (m_atomNetWmState == None)
//      {
//
//         m_atomNetWmState = intern_atom(::x11::e_atom_net_wm_state, bCreate);
//
//      }
//
//      return m_atomNetWmState;
//
//   }


//   Picture display::xrender_create_picture(::image::image_pointer pimage)
//   {
//
//      Pixmap pixmap = _x11_create_pixmap(pimage);
//
//      if (pixmap == 0)
//      {
//
//         return 0;
//
//      }
//
//      auto dpy = Display();
//
//      auto vis = Visual();
//
//      XRenderPictFormat * pformat = XRenderFindVisualFormat(dpy, &vis);
//
//      bool hasAlpha = (pformat->type == PictTypeDirect && pformat->direct.alphaMask);
//      int x = 0;
//      int y = 0;
//      int width = pimage->width();
//      int height = pimage->height();
//
//      XRenderPictureAttributes pa = {};
//
//      Picture picture = XRenderCreatePicture(Display(), pixmap, pformat, CPSubwindowMode, &pa);
//
//      return picture;
//
//   }


//   ::wayland::nano::user::window_base * display::_get_active_window(::thread * pthread)
//   {
//
////      auto window = m_px11display->_get_active_window();
////
////      auto pwindow = _window(window);
////
////      windowing_output_debug_string("::GetActiveWindow 2");
////
////      return pwindow;
//
//return nullptr;
//
//   }
//
//
//   ::windowing_gtk4::window * display::get_keyboard_focus()
//   {
//
//      return m_pwindowKeyboardFocus;
//
//   }
//
//
//   ::windowing_gtk4::window * display::_get_keyboard_focus()
//   {
//
////      auto ppropertyobject = ::place(new ::property_object());
////
////      auto predicate = [this, ppropertyobject]()
////      {
////
////         synchronous_lock synchronouslock(user_synchronization());
////
////         oswindow oswindow = nullptr;
////
////         windowing_output_debug_string("::GetFocus 1");
////
////#ifdef display_lock_LOCK_LOG
////
////         b_prevent_display_lock_lock_log = false;
////
////#endif
////
////         //display_lock displaylock(Display());
////
////         windowing_output_debug_string("::GetFocus 1.01");
////
////         Window window = None;
////
////         int revert_to = 0;
////
////         bool bOk = XGetInputFocus(Display(), &window, &revert_to) != 0;
////
////         if (!bOk)
////         {
////
////            windowing_output_debug_string("::GetFocus 1.2");
////
////            return;
////
////         }
////
////         if (window == None || window == PointerRoot)
////         {
////
////            windowing_output_debug_string("::GetFocus 1.3");
////
////            return;
////
////         }
////
////         ppropertyobject->payload("window") = (::iptr) window;
////
////         windowing_output_debug_string("::GetFocus 2");
////
////      };
////
////      auto pwindowing = x11_windowing();
////
////      //proutine->set_timeout(5_s);
////
////      pwindowing->windowing_send(predicate);
////
//////      if(proutine->has_timed_out())
//////      {
//////
//////         return nullptr;
//////
//////      }
////
////      if (ppropertyobject->payload("window").is_new())
////      {
////
////         return nullptr;
////
////      }
////
////      Window window = (Window) ppropertyobject->payload("window").as_iptr();
////
////      auto pwindow = _window(window);
////
////      if (!pwindow)
////      {
////
////         return nullptr;
////
////      }
////
////      return pwindow;
//
//return nullptr;
//
//   }
//

   bool display::get_cursor_position(::point_i32 * ppointCursor)
   {

//      Window root_return;
//      Window child_return;
      i32 win_x_return;
      i32 win_y_return;
      u32 mask_return;

#ifdef display_lock_LOCK_LOG

      b_prevent_display_lock_lock_log = true;

#endif

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("::GetCursorPos 1");

      //display_lock displaylock(Display());

//      XQueryPointer(Display(), DefaultRootWindow(Display()), &root_return, &child_return, &ppointCursor->x(),
//                    &ppointCursor->y(), &win_x_return, &win_y_return, &mask_return);

#ifdef display_lock_LOCK_LOG

      b_prevent_display_lock_lock_log = false;

#endif

      windowing_output_debug_string("::GetCursorPos 2");

      return true;

   }


//   XImage * display::_x11_create_image(::image::image_pointer pimage)
//   {
//
//      pimage->map();
//
//      char * image32 = (char *) pimage->get_data();
//
//      int width = pimage->width();
//
//      int height = pimage->height();
//
//      int depth = 32; // works fine with depth = 24
//
//      int bitmap_pad = 32; // 32 for 24 and 32 bpp, 16, for 15&16
//
//      int bytes_per_line = pimage->scan_size(); // number of bytes in the client image between the start of one scanline and the start of the next
//
//      XImage * pximage = XCreateImage(Display(), CopyFromParent, depth, ZPixmap, 0, image32, width, height,
//                                      bitmap_pad, bytes_per_line);
//
//      return pximage;
//
//   }
//
//
//   XImage * display::x11_create_image(::image::image_pointer pimage)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::x11_create_image 1");
//
//      //display_lock displaylock(Display());
//
//      return _x11_create_image(pimage);
//
//   }
//
//
//   Pixmap display::_x11_create_pixmap(::image::image_pointer pimage)
//   {
//
//      if (!pimage)
//      {
//
//         return 0;
//
//      }
//
//      XImage * pximage = _x11_create_image(pimage);
//
//      if (pximage == nullptr)
//      {
//
//         return 0;
//
//      }
//
//      int depth = 32; // works fine with depth = 24
//
//      Pixmap pixmap = XCreatePixmap(Display(), DefaultRootWindow(Display()), pimage->width(), pimage->height(), depth);
//
//      XGCValues gcvalues = {};
//
//      GC gc = XCreateGC(Display(), pixmap, 0, &gcvalues);
//
//      XPutImage(Display(), pixmap, gc, pximage, 0, 0, 0, 0, pimage->width(), pimage->height());
//
//      XFreeGC(Display(), gc);
//
//      return pixmap;
//
//   }
//
//
//   Pixmap display::x11_create_pixmap(::image::image_pointer pimage)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::x11_create_pixmap 1");
//
//      //display_lock displaylock(Display());
//
//      return _x11_create_pixmap(pimage);
//
//   }
//
//
//   comparable_array<Window> display::x11_window_list()
//   {
//
//      comparable_array<Window> windowa;
//
//      auto atomWindowList = intern_atom("_NET_CLIENT_LIST_STACKING", False);
//
//      if (atomWindowList == 0)
//      {
//
//         atomWindowList = intern_atom("_NET_CLIENT_LIST", False);
//
//      }
//
//      if (atomWindowList == 0)
//      {
//
//         return windowa;
//
//      }
//
//      Atom type;
//      int form;
//      unsigned long remain;
//      unsigned char * list;
//      unsigned long ulBytesReturned = 0;
//      //errno = 0;
//
//      Atom actual_type;
//
//      int actual_format;
//
//      unsigned long int bytes_after;
//
//      Window * windowList = nullptr;
//
//      if (XGetWindowProperty(
//         Display(),
//         Window(),
//         atomWindowList, 0, 1024, False, XA_WINDOW,
//         &actual_type, &actual_format, &ulBytesReturned, &bytes_after,
//         (unsigned char **) &windowList) != Success)
//      {
//
//         informationf("winlist() -- GetWinProp");
//
//         return windowa;
//
//      }
//
//      unsigned long nchildren = ulBytesReturned / sizeof(Window);
//
//      windowa.set_size(nchildren);
//
//      memory_copy(windowa.data(), windowList, minimum(windowa.get_size_in_bytes(), ulBytesReturned));
//
//      XFree(windowList);
//
//      return windowa;
//
//   }


//   bool display::point_is_window_origin(::point_i32 pointHitTest, ::windowing::window * pwindowExclude, int iMargin)
//   {
//
//      bool bIsOrigin = false;
//
//      auto psystem = system()->m_papexsystem;
//
//      auto pnode = psystem->node();
//
//      pnode->node_send([this, pointHitTest, pwindowExclude, iMargin, &bIsOrigin]()
//                       {
//
//                          ::windowing_gtk4::window * pwindowxcbExclude = nullptr;
//
//                          if (pwindowExclude)
//                          {
//
//                             pwindowxcbExclude = dynamic_cast < ::windowing_gtk4::window * >(pwindowExclude);
//
//                          }
//
//                          synchronous_lock synchronouslock(user_synchronization());
//
//                          windowing_output_debug_string("::GetFocus 1");
//
//#ifdef display_lock_LOCK_LOG
//
//                          b_prevent_display_lock_lock_log = false;
//
//#endif
//
//                          if (!Display())
//                          {
//
//                             windowing_output_debug_string("::GetFocus 1.1");
//
//                             return;
//
//                          }
//
//                          //display_lock displaylock(Display());
//
//                          windowing_output_debug_string("::GetFocus 1.01");
//
//                          auto windowa = x11_window_list();
//
//                          ::rectangle_i32 rectangleTest;
//
//                          for (::collection::index i = 0; i < windowa.get_size(); i++)
//                          {
//
//                             string strItem = ::x11_get_name(Display(), windowa[i]);
//
//                             ::rectangle_i32 rectangleHigher;
//
//                             if (::is_set(pwindowxcbExclude) && windowa[i] == pwindowxcbExclude->Window())
//                             {
//
//                                continue;
//
//                             }
//
//                             if (::x11_get_window_rect(Display(), windowa[i], &rectangleHigher))
//                             {
//
//                                ::rectangle_i32 rectangleHitTest;
//
//                                rectangleHitTest.set(rectangleHigher.origin(), ::size_i32());
//
//                                rectangleHitTest.inflate(iMargin + 1);
//
//                                if (rectangleHitTest.contains(pointHitTest))
//                                {
//
//                                   bIsOrigin = true;
//
//                                   return;
//
//                                }
//
//                             }
//
//                          }
//
//                       });
//
//      return bIsOrigin;
//
//   }


//   void display::destroy_wayland_buffer(wayland_buffer & waylandbuffer)
//   {
//
//      if(waylandbuffer.m_pwlbuffer)
//      {
//
//         wl_buffer_destroy(waylandbuffer.m_pwlbuffer);
//
//         waylandbuffer.m_pwlbuffer = nullptr;
//
//      }
//
//      if(waylandbuffer.m_pwlshmpool)
//      {
//
//         wl_shm_pool_destroy(waylandbuffer.m_pwlshmpool);
//
//         waylandbuffer.m_pwlshmpool = nullptr;
//
//      }
//
//      if(waylandbuffer.m_pdata && waylandbuffer.m_memsizeStorage > 0)
//      {
//
//         munmap(waylandbuffer.m_pdata, waylandbuffer.m_memsizeStorage);
//
//         waylandbuffer.m_pdata = nullptr;
//
//         waylandbuffer.m_memsizeStorage = 0;
//
//         waylandbuffer.m_memsize2 = 0;
//
//      }
//
//      if(waylandbuffer.m_iFd >= 0)
//      {
//
//         ::close(waylandbuffer.m_iFd);
//
//         waylandbuffer.m_iFd = -1;
//
//      }
//
//      waylandbuffer.m_size.cx() = 0;
//
//      waylandbuffer.m_size.cy() = 0;
//
//      waylandbuffer.m_stride = 0;
//
//   }
//
//
//   void display::update_wayland_buffer(wayland_buffer &waylandbuffer, const ::size_i32 & size)
//   {
//
//      //wayland_buffer waylandbuffer{};
//
//      ::i32 iNewStride = size.cx() * 4; // 4 bytes per pixel;
//
//      ::memsize memsizeNew = iNewStride * size.cy();
//
//      if(memsizeNew > waylandbuffer.m_memsizeStorage)
//      {
//
//         destroy_wayland_buffer(waylandbuffer);
//
//         waylandbuffer.m_memsizeStorage = memsizeNew * 2;
//
//         //waylandbuffer
//
//         //}
//
//         //waylandbuffer.m_stride =
//
//         //waylandbuffer.m_memsize = waylandbuffer.m_stride * size.cy();
//
//         waylandbuffer.m_iFd = os_create_anonymous_file(waylandbuffer.m_memsizeStorage);
//
//         if (waylandbuffer.m_iFd < 0)
//         {
//
//            error() << "creating a buffer file for wl_buffer failed: ";
//
//            waylandbuffer.m_stride = 0;
//
//            waylandbuffer.m_memsize2 = 0;
//
//            waylandbuffer.m_memsizeStorage = 0;
//
//            return;
//
//         }
//
//         waylandbuffer.m_pdata = mmap(
//            NULL, waylandbuffer.m_memsizeStorage,
//            PROT_READ | PROT_WRITE, MAP_SHARED,
//            waylandbuffer.m_iFd, 0);
//
//         if (waylandbuffer.m_pdata == MAP_FAILED)
//         {
//
//            error() << "mmap failed";
//
//            ::close(waylandbuffer.m_iFd);
//
//            waylandbuffer.m_stride = 0;
//
//            waylandbuffer.m_memsize2 = 0;
//
//            waylandbuffer.m_memsizeStorage = 0;
//
//            waylandbuffer.m_pdata = nullptr;
//
//            return;
//
//         }
//
//         waylandbuffer.m_pwlshmpool = wl_shm_create_pool(m_pwlshm, waylandbuffer.m_iFd, waylandbuffer.m_memsizeStorage);
//
//      }
//
//      waylandbuffer.m_stride = iNewStride;
//
//      waylandbuffer.m_memsize2 = memsizeNew;
//
//      if(waylandbuffer.m_pwlbuffer)
//      {
//
//         wl_buffer_destroy(waylandbuffer.m_pwlbuffer);
//
//         waylandbuffer.m_pwlbuffer = nullptr;
//
//      }
//
//      waylandbuffer.m_pwlbuffer = wl_shm_pool_create_buffer(waylandbuffer.m_pwlshmpool, 0,
//                                       size.cx(), size.cy(),
//                                       waylandbuffer.m_stride,
//                                       WL_SHM_FORMAT_ARGB8888);
//
//      //wl_buffer_add_listener(buffer, &buffer_listener, buffer);
//
//      waylandbuffer.m_size = size;
//
//      //return waylandbuffer;
//
//   }
//
//
//   void display::update_wayland_buffer(wayland_buffer &waylandbuffer, ::image::image *pimage)
//   {
//
//      update_wayland_buffer(waylandbuffer, pimage->size());
//
//      pimage->map();
//
//      copy_image32((::image32_t*)waylandbuffer.m_pdata,
//                   waylandbuffer.m_size,
//                   waylandbuffer.m_stride,
//                   pimage->data(), pimage->scan_size());
//
//      //return waylandbuffer;
//
//   }


//   void display::__handle_pointer_enter(::wl_pointer * pwlpointer, double x, double y, ::windowing_gtk4::window * pwindowPointerEnter)
//   {
//
//      m_pwindowPointerEnter = pwindowPointerEnter;
//
//      if(m_pwindowPointerEnter)
//      {
//
//         //m_pwindowPointerEnter->m_pointPointer.x() = (double) m_pwindowPointerEnter->m_pointWindow.x() + x;
//
//         //m_pwindowPointerEnter->m_pointPointer.y() = (double) m_pwindowPointerEnter->m_pointWindow.y() + y;
//
//         m_pwindowPointerEnter->m_pointCursor2.x() = x;
//
//         m_pwindowPointerEnter->m_pointCursor2.y() = y;
//
//         m_pwindowPointerEnter->__handle_pointer_enter(pwlpointer);
//
//      }
//
//   }
//
//
//   void display::__handle_pointer_motion(::wl_pointer * pwlpointer, double x, double y, ::u32 millis)
//   {
//
//      ::point_i32 pointCursor((::i32)x, (::i32)y);
//
//      if(m_pwindowPointerCapture)
//      {
//
//         m_pwindowPointerCapture->m_sizeDrag = pointCursor - m_pwindowPointerCapture->m_pointCursor2;
//
//         m_pwindowPointerCapture->m_pointCursor2 = pointCursor;
//
//         if(m_pwindowPointerEnter)
//         {
//
//            m_pwindowPointerEnter->m_sizeDrag = pointCursor - m_pwindowPointerEnter->m_pointCursor2;
//
//            m_pwindowPointerEnter->m_pointCursor2 = pointCursor;
//
//         }
//
//      }
//      else if(m_pwindowPointerEnter)
//      {
//
//         m_pwindowPointerEnter->m_sizeDrag = pointCursor - m_pwindowPointerEnter->m_pointCursor2;
//
//         m_pwindowPointerEnter->m_pointCursor2 = pointCursor;
//
//      }
//
//
//      if(m_pwindowPointerCapture)
//      {
//
//         m_pwindowPointerCapture->__handle_pointer_motion(pwlpointer, millis);
//
//      }
//      else if(m_pwindowPointerEnter)
//      {
//
//         m_pwindowPointerEnter->__handle_pointer_motion(pwlpointer, millis);
//
//      }
//
//   }
//
//
//   void display::__handle_pointer_leave(::wl_pointer * pwlpointer, ::windowing_gtk4::window * pwaylandwindowLeave)
//   {
//
//      if(m_pwindowPointerCapture)
//      {
//
//         ::minimum(m_pwindowPointerCapture->m_pointCursor2.x());
//
//         ::minimum(m_pwindowPointerCapture->m_pointCursor2.y());
//
//         if(m_pwindowPointerEnter)
//         {
//
//            ::minimum(m_pwindowPointerEnter->m_pointCursor2.x());
//
//            ::minimum(m_pwindowPointerEnter->m_pointCursor2.y());
//
//         }
//
//      }
//      else if(m_pwindowPointerEnter)
//      {
//
//         ::minimum(m_pwindowPointerEnter->m_pointCursor2.x());
//
//         ::minimum(m_pwindowPointerEnter->m_pointCursor2.y());
//
//      }
//
//      if(m_pwindowPointerCapture)
//      {
//
//         m_pwindowPointerCapture->__handle_pointer_leave(pwlpointer, pwaylandwindowLeave);
//
//      }
//      else if(m_pwindowPointerEnter)
//      {
//
//         m_pwindowPointerEnter->__handle_pointer_leave(pwlpointer, pwaylandwindowLeave);
//
//      }
//
//      if(m_pwindowPointerEnter == pwaylandwindowLeave)
//      {
//
//         m_pwindowPointerEnter.release();
//
//      }
//
//   }
//
//
//   void display::__handle_pointer_button(::wl_pointer * pwlpointer, ::u32 linux_button, ::u32 pressed, ::u32 millis)
//   {
//
//      if(m_pwindowPointerCapture)
//      {
//
//         m_pwindowPointerCapture->__handle_pointer_button(pwlpointer, linux_button, pressed, millis);
//
//      }
//      else if(m_pwindowPointerEnter)
//      {
//
//         m_pwindowPointerEnter->__handle_pointer_button(pwlpointer, linux_button, pressed, millis);
//
//      }
//      else
//      {
//
//         information() << "MISSED BUTTON PRESS/RELEASE: at display::__handle_pointer_button";
//
//      }
//
//   }
//

//   void display::__capture_mouse(::windowing_gtk4::window * pwindowMouseCapture, ::u32 serial)
//   {
//
//      if(::is_null(pwindowMouseCapture))
//      {
//
//         return;
//
//      }
//
//      m_pwindowMouseCapture = pwindowMouseCapture;
//
////      m_rectangleMouseCapture = get_monitor_union_rectangle();
////
////      destroy_wayland_buffer(m_waylandbufferMouseCapture);
////
////      m_waylandbufferMouseCapture = create_wayland_buffer(m_rectangleMouseCapture.size());
////
////      memset(m_waylandbufferMouseCapture.m_pdata, 0, m_waylandbufferMouseCapture.m_memsize);
////
////      information() << "__capture_mouse : " << m_rectangleMouseCapture;
////
////      m_pwlsurfaceMouseCapture = wl_compositor_create_surface(m_pwlcompositor);
////
////      m_pxdgsurfaceMouseCapture = xdg_wm_base_get_xdg_surface(m_pxdgwmbase, m_pwlsurfaceMouseCapture);
////
////      xdg_surface_set_window_geometry(m_pxdgsurfaceMouseCapture,
////                                      m_rectangleMouseCapture.left(),
////                                      m_rectangleMouseCapture.top(),
////                                      m_rectangleMouseCapture.width(),
////                                      m_rectangleMouseCapture.height());
////
////      xdg_surface_add_listener(m_pxdgsurfaceMouseCapture,
////                               &xdg_surface_mouse_capture_listener, this);
////
////      m_pxdgtoplevelMouseCapture = xdg_surface_get_toplevel(m_pxdgsurfaceMouseCapture);
////
////      if (m_pxdgtoplevelMouseCapture == NULL)
////      {
////
////         error() << "Can't create Mouse Capture top level window";
////
////         throw ::exception(::error_failed);
////
////      }
////      else
////      {
////
////         information() << "Created Mouse Capture top level window";
////
////      }
////
////      xdg_surface_set_window_geometry(m_pxdgsurfaceMouseCapture,
////         m_rectangleMouseCapture.left(),
////         m_rectangleMouseCapture.top(),
////         m_rectangleMouseCapture.width(),
////         m_rectangleMouseCapture.height());
////
////      //xdg_toplevel_add_listener(m_pxdgtoplevel,
////        //                        &xdg_toplevel_listener, this);
////
////        //xdg_popup_grab(m_pxdgtoplevelMouseCapture, m_pwlseat, serial);
////
////      wl_surface_commit(m_pwlsurfaceMouseCapture);
//
//   }


//   void display::__handle_keyboard_keymap(::wl_keyboard *pwlkeyboard, uint32_t format, int fd, uint32_t size)
//   {
//
//      ::pointer < ::windowing_gtk4::keyboard > pkeyboard = m_pwindowing->keyboard();
//
//      pkeyboard->__handle_keyboard_keymap(pwlkeyboard, format, fd, size);
//
//   }
//
//
//   void display::__handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_surface *pwlsurface, ::wl_array *pwlarrayKeys)
//   {
//
//      m_pwlkeyboard = pwlkeyboard;
//
//      m_pwlsurfaceKeyboardEnter = pwlsurface;
//
//      m_uLastSeatSerial = serial;
//      m_uLastKeyboardSerial = serial;
//      m_uLastKeyboardEnterSerial = serial;
//
//      auto pwaylandwindow = _window(pwlsurface);
//
//      if(!pwaylandwindow)
//      {
//
//         error() << "Could not find pwaylandwindow from pwlsurface";
//
//         return;
//
//      }
//
//      m_pwindowKeyboardFocus = pwaylandwindow;
//
//      m_pwindowKeyboardFocus->__handle_keyboard_enter(pwlkeyboard, serial, pwlarrayKeys);
//
//   }
//
//
//   void display::__handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_surface *pwlsurface)
//   {
//
//      if(pwlkeyboard == m_pwlkeyboard)
//      {
//
//         m_pwlkeyboard = nullptr;
//
//      }
//
//      if(pwlsurface == m_pwlsurfaceKeyboardEnter)
//      {
//
//         m_pwlsurfaceKeyboardEnter = nullptr;
//
//      }
//
//      m_uLastSeatSerial = serial;
//      m_uLastKeyboardSerial = serial;
//      m_uLastKeyboardLeaveSerial = serial;
//
//      auto pwaylandwindow = _window(pwlsurface);
//
//      if(!pwaylandwindow)
//      {
//
//         error() << "Could not find pwaylandwindow from pwlsurface (2)";
//
//         return;
//
//      }
//
//      if(m_pwindowKeyboardFocus != pwaylandwindow)
//      {
//
//         error() << "What!! but ignoring what seems to be an error";
//
//      }
//
//      m_pwindowKeyboardFocus->__handle_keyboard_leave(pwlkeyboard, serial);
//
//   }
//
//
//   void display::__handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state)
//   {
//
//      if(!m_pwindowKeyboardFocus)
//      {
//
//         error() << "Keyboard key with no window with focus!!";
//
//         return;
//
//      }
//
//      m_pwindowKeyboardFocus->__handle_keyboard_key(pwlkeyboard, serial, time, key, state);
//
//   }
//
//
//   void display::__handle_keyboard_modifiers(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
//   {
//
//      if(!m_pwindowKeyboardFocus)
//      {
//
//         error() << "Keyboard modifiers with no window with focus!!";
//
//         return;
//
//      }
//
//      m_pwindowKeyboardFocus->__handle_keyboard_modifiers(pwlkeyboard, serial, mods_depressed, mods_latched, mods_locked, group);
//
//   }
   //
   // bool display::is_x11()
   // {
   //
   //
   //    if (GDK_IS_X11_DISPLAY(m_pgdkdisplay))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    return false;
   //
   // }
   //
   //
   // bool display::is_wayland()
   // {
   //
   //    if (GDK_IS_WAYLAND_DISPLAY(m_pgdkdisplay))
   //    {
   //
   //       return true;
   //
   //    }
   //
   //    return false;
   //
   // }



} // namespace windowing_gtk4



