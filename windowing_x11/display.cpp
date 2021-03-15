// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "apex/platform/app_core.h"
#include "windowing_x11.h"
//#include "_user.h"
//#include <gdk/gdk.h>


extern ::app_core * g_pappcore;

Display * x11_get_display();

mutex * user_mutex();

#define CA2_X11_WINDOW_LONG "ca2_ccwarehouse_window_long"
#define CA2_X11_WINDOW_LONG_STYLE "ca2_ccwarehouse_window_long_style"
#define CA2_X11_WINDOW_LONG_STYLE_EX "ca2_ccwarehouse_window_long_style_ex"


void windowing_output_debug_string(const char *pszDebugString);


namespace windowing_x11
{


   //display *g_posdisplaydataMain = nullptr;


   //void defer_init_ui();


   //display *x11_main_display()
   //{

   //   return g_posdisplaydataMain;

   //}


   display::display()
   {

      set_layer(LAYERED_X11, this);
      //m_pcsOsDisplayData = new critical_section();
      m_pdisplay = nullptr;
      m_atomLongType = None;
      m_atomLongStyle = None;
      m_atomNetWmState = None;
      m_atomLongStyleEx = 0;
      m_countReference = 1;
//   m_pmutexInput           = new ::mutex();

   }


   display::~ display()
   {

//   ::acme::del(m_pmutexInput);

      //::acme::del(m_pcsOsDisplayData);

   }


#ifdef DEBUG


   i64 display::get_ref_count()
   {

      return m_countReference;

   }


   i64 display::add_ref(OBJ_REF_DBG_PARAMS)
   {

#ifdef WINDOWS

      return InterlockedIncrement64(&m_countReference);

#elif defined(RASPBIAN) && defined(OS32BIT)

      return __sync_add_and_fetch_4(&m_countReference,1);

#else

      return __sync_add_and_fetch(&m_countReference, 1);

#endif

   }


   i64 display::dec_ref(OBJ_REF_DBG_PARAMS)
   {

#ifdef WINDOWS

      return InterlockedDecrement64(&m_countReference);

#elif defined(RASPBIAN) && defined(OS32BIT)

      return __sync_sub_and_fetch_4(&m_countReference,1);

#else

      return __sync_sub_and_fetch(&m_countReference, 1);

#endif

   }


   i64 display::release(OBJ_REF_DBG_PARAMS)
   {

      i64 i = dec_ref(OBJ_REF_DBG_ARGS);

      if (i == 0)
      {

         //osdisplay_remove(m_pdisplay);

      }

      return i;

   }


#endif // DEBUG


   ::e_status display::open()
   {

      if(::is_set(m_pdisplay))
      {

         return ::success;

      }

      m_pdisplay =  XOpenDisplay(NULL);

      if(::is_null(m_pdisplay))
      {

         return ::error_failed;

      }

      if (XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &m_px11data->m_visualinfo))
      {

         visual = m_px11data->m_visualinfo.visual;

      }
      else
      {

         __zero(m_px11data->m_visualinfo);

      }


      m_iScreen = DefaultScreen(display);


      m_iDepth = m_px11data->m_visualinfo.depth;

      XSetWindowAttributes attr;

      __zero(attr);

      m_colormap = XCreateColormap(display, rootwin, visual, AllocNone);

      return ::success;

   }


   ::windowing_x11::window *display::_window(Window window)
   {

      if (!window)
      {

         return nullptr;

      }

      critical_section_lock synchronizationlock(&m_criticalsectionWindowMap);

      auto &pwindow = m_windowmap[window];

      if (!pwindow)
      {

         __construct(pwindow);

         pwindow->set_os_data((void *) (iptr) window);

      }

      return pwindow;

   }


   void display::lock_display()
   {

      XLockDisplay(m_pdisplay);

   }


   void display::unlock_display()
   {

      XUnlockDisplay(m_pdisplay);

   }


   ::Display *display::Display()
   {

      return ::is_null(this) ? nullptr : m_pdisplay;

   }


   ::Display *display::Display() const
   {

      return ::is_null(this) ? nullptr : m_pdisplay;

   }


   Atom display::atom_long_type()
   {

      return ::is_null(this) ? 0 : m_atomLongType;

   }


   Atom display::atom_long_style()
   {

      return ::is_null(this) ? 0 : m_atomLongStyle;

   }


   Atom display::atom_long_style_ex()
   {

      return ::is_null(this) ? 0 : m_atomLongStyleEx;

   }


   bool display::is_null() const
   {

      return ::is_null(this);

   }



   bool display::get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle)
   {
      return ::windowing::display::get_monitor_rectangle(iMonitor, prectangle);
//
//      synchronization_lock synchronizationlock(mutex());
//
//      if (iMonitor < 0 || iMonitor >= get_monitor_count())
//      {
//
//         return false;
//
//      }
//
//      *prectangle = m_rectaMonitor[iMonitor];

      return true;

   }


   bool display::get_workspace_rectangle(index iMonitor, RECTANGLE_I32 * prectangle)
   {

      return ::windowing::display::get_workspace_rectangle(iMonitor, prectangle);

   }


   ::e_status display::release_mouse_capture()
   {

      synchronization_lock synchronizationlock(user_mutex());

      _on_capture_changed_to(nullptr);

      windowing_output_debug_string("\noswindow_data::ReleaseCapture 1");

      display_lock displaylock(this);

      int_bool bRet = XUngrabPointer(Display(), CurrentTime) != false;

      windowing_output_debug_string("\noswindow_data::ReleaseCapture 2");

      return bRet;

   }


//   bool display::has_mouse_capture() const
//   {
//
//      if(::is_null(m_pwindowCapture))
//      {
//
//         return false;
//
//      }
//
//
//   }


   void display::_on_capture_changed_to(::windowing_x11::window * pwindowMouseCaptureNew)
   {

      auto pwindowMouseCaptureOld = m_pwindowMouseCapture;

      m_pwindowMouseCapture = pwindowMouseCaptureNew;

      if (pwindowMouseCaptureOld && pwindowMouseCaptureOld != pwindowMouseCaptureNew)
      {

         MESSAGE msg;

         msg.oswindow = pwindowMouseCaptureOld;
         msg.m_id = e_message_capture_changed;
         msg.wParam = 0;
         msg.lParam = pwindowMouseCaptureNew;

         auto pwindowing = x11_windowing();

         pwindowing->post_ui_message(msg);

      }

   }


//   i32 display::osdisplay_find(Display *pdisplay)
//   {
//
//      single_lock slOsWindow(::display::s_pmutex, true);
//
//      for (i32 i = 0; i < display::s_pdataptra->get_count(); i++)
//      {
//
//         if (display::s_pdataptra->element_at(i)->m_pdisplay == pdisplay)
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


//   display *osdisplay_get(Display *pdisplay)
//   {
//
//      if (pdisplay == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      single_lock slOsWindow(::display::s_pmutex, true);
//
//      iptr iFind = osdisplay_find(pdisplay);
//
//      if (iFind >= 0)
//      {
//
//         return display::s_pdataptra->element_at(iFind);
//
//      }
//
//      display *pdisplaydata = new display;
//
//      pdisplaydata->m_pdisplay = pdisplay;
//      pdisplaydata->m_atomLongType = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG, False);
//      pdisplaydata->m_atomLongStyle = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE, False);
//      pdisplaydata->m_atomLongStyleEx = XInternAtom(pdisplay, CA2_X11_WINDOW_LONG_STYLE_EX, False);
//
//      ::display::s_pdataptra->add(pdisplaydata);
//
//      if (!::g_pappcore->m_bGtkApp)
//      {
//
//         if (!g_posdisplaydataMain)
//         {
//
//            g_posdisplaydataMain = pdisplaydata;
//
//            //defer_init_ui();
//
//         }
//
//      }
//
//      return pdisplaydata;
//
//   }


//   bool osdisplay_remove(Display *pdisplay)
//   {
//
//      single_lock slOsWindow(::display::s_pmutex, true);
//
//      iptr iFind = osdisplay_find(pdisplay);
//
//      if (iFind < 0)
//         return false;
//
//      display *pdata = ::display::s_pdataptra->element_at(iFind);
//
//      XCloseDisplay(pdata->m_pdisplay);
//
//      ::display::s_pdataptra->remove_at(iFind);
//
//      return true;
//
//   }


   Atom display::get_window_long_atom(i32 nIndex)
   {

      if (::is_null(this))
      {

         return 0;

      }

      switch (nIndex)
      {

         default:
         {

            string strProperty;

            strProperty = CA2_X11_WINDOW_LONG + ansi_string_from_i64(nIndex);

            return XInternAtom(Display(), strProperty, False);

         }

      }

   }


   Atom display::intern_atom(const char *pszAtomName, bool bCreate)
   {

      if (m_pdisplay == nullptr)
      {

         return 0;

      }

      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);

      if (atom == None)
      {

         windowing_output_debug_string("ERROR: cannot find atom for " + string(pszAtomName) + "\n");

         return None;

      }

      return atom;

   }


   ::e_status display::remove_window(::windowing::window * pwindow)
   {

      return error_failed;

   }


   Atom display::intern_atom(enum_net_wm_state estate, bool bCreate)
   {

      if (estate < e_net_wm_state_above || estate >= e_net_wm_state_count)
      {

         return None;

      }

      if (m_atomaNetWmState[estate] == None)
      {

         m_atomaNetWmState[estate] = intern_atom(net_wm_state_text(estate), bCreate);

      }

      return m_atomaNetWmState[estate];

   }


   Atom display::net_wm_state_atom(bool bCreate)
   {

      if (m_atomNetWmState == None)
      {

         m_atomNetWmState = intern_atom("_NET_WM_STATE", bCreate);

      }

      return m_atomNetWmState;

   }


//   void enum_display_monitors(::aura::session *psession)
//   {
//
//      auto pnode = Node;
//
//      if (pnode)
//      {
//
//         pnode->enum_display_monitors(psession);
//
//      }
//
//   }


//   virtual ::Display * Display();
//{
//
//   return ::is_null(this) ? nullptr : m_osdisplay->display();
//
//}

//Display * display() const
//{
//   return ::is_null(this) ? nullptr : m_osdisplay->display();
//}

//Window window()
//{
//   return ::is_null(this) ? None : m_window;
//}

//Window window() const
//{
//   return ::is_null(this) ? None : m_window;
//}

//Visual * visual()
//{
//   return ::is_null(this) ? nullptr : &m_visual;
//}

//Visual * visual() const
//{
//   return ::is_null(this) ? nullptr : (Visual * ) & m_visual;
//}
//
//Window root_window_raw() const
//{
//   return ::is_null(this) || ::is_null(m_osdisplay) ? None : RootWindow(display(), m_iScreen);
//}
//


//   ::Display * display::Display()
//   {
//
//      return ::is_null(this) ? nullptr : m_osdisplay->display();
//
//   }


//   ::Display * display::display() const
//   {
//
//      return ::is_null(this) ? nullptr : m_osdisplay->display();
//
//   }

//
//   Window display::window()
//   {
//      return ::is_null(this) ? None : m_window;
//   }

//   Window display::window() const
//   {
//      return ::is_null(this) ? None : m_window;
//   }

//   Visual * display::Visual()
//   {
//
//      return ::is_null(this) ? nullptr : &m_visual;
//
//   }
//
//
//   Visual * display::Visual() const
//   {
//
//      return ::is_null(this) ? nullptr : (Visual * ) & m_visual;
//
//   }


//   Window display::root_window_raw() const
//   {
//
//      return ::is_null(this) || ::is_null(m_osdisplay) ? None : RootWindow(display(), m_iScreen);
//
//   }


   Picture display::xrender_create_picture(::image_pointer pimage)
   {

      Pixmap pixmap = _x11_create_pixmap(pimage);

      if (pixmap == 0)
      {

         return 0;

      }

      //	bool hasNamePixmap = false;
      //
      //	int event_base, error_base;
      //
      //	if (XCompositeQueryExtension(window->display(), &event_base, &error_base))
      //	{
      //
      //		int major = 0;
      //
      //		int minor = 2;
      //
      //		XCompositeQueryVersion(window->display(), &major, &minor);
      //
      //		if(major > 0 || minor >= 2 )
      //		{
      //
      //         hasNamePixmap = true;
      //
      //      }
      //
      //	}

      auto dpy = Display();

      auto vis = Visual();

      XRenderPictFormat *pformat = XRenderFindVisualFormat(dpy, &vis);

      bool hasAlpha = (pformat->type == PictTypeDirect && pformat->direct.alphaMask);
      int x = 0;
      int y = 0;
      int width = pimage->width();
      int height = pimage->height();

      XRenderPictureAttributes pa = {};

      Picture picture = XRenderCreatePicture(Display(), pixmap, pformat, CPSubwindowMode, &pa);

      return picture;

   }


//   Picture display::xrender_create_picture(::image_pointer pimage)
//   {
//
//      Picture picture = 0;
//
//      m_pwindowing->user_sync([&]()
//                              {
//
//                                 synchronization_lock synchronizationlock(user_mutex());
//
//                                 windowing_output_debug_string("\n::xrender_create_picture 1");
//
//                                 xdisplay d(window->display());
//
//                                 if(d.is_null())
//                                 {
//
//                                    windowing_output_debug_string("\n::xrender_create_picture 1.1");
//
//                                    return;
//
//                                 }
//
//                                 picture = _xrender_create_picture(window, pimage);
//
//                              });
//
//      return picture;
//
//   }


   ::windowing_x11::window *display::_get_active_window(::thread *pthread)
   {

      int screen = XDefaultScreen(Display());

      Window windowRoot = RootWindow(Display(), screen);

      Window window = x11_get_long_property(Display(), windowRoot, (char *) "_NET_ACTIVE_WINDOW");

      auto pwindow = _window(window);

      windowing_output_debug_string("\n::GetActiveWindow 2");

      return pwindow;

   }


   ::windowing_x11::window *display::get_keyboard_focus()
   {

      return m_pwindowKeyboardFocus;

   }


   ::windowing_x11::window *display::_get_keyboard_focus()
   {

      synchronization_lock synchronizationlock(user_mutex());

      oswindow oswindow = nullptr;

      windowing_output_debug_string("\n::GetFocus 1");

#ifdef display_lock_LOCK_LOG

      b_prevent_display_lock_lock_log = false;

#endif

      display_lock displaylock(this);

      windowing_output_debug_string("\n::GetFocus 1.01");

      Window window = None;

      int revert_to = 0;

      bool bOk = XGetInputFocus(Display(), &window, &revert_to) != 0;

      if (!bOk)
      {

         windowing_output_debug_string("\n::GetFocus 1.2");

         return nullptr;

      }

      if (window == None || window == PointerRoot)
      {

         windowing_output_debug_string("\n::GetFocus 1.3");

         return nullptr;

      }

      auto pwindow = _window(window);

      windowing_output_debug_string("\n::GetFocus 2");

      return pwindow;

   }


   bool display::get_cursor_position(POINT_I32 *ppointCursor)
   {

      Window root_return;
      Window child_return;
      i32 win_x_return;
      i32 win_y_return;
      u32 mask_return;

#ifdef display_lock_LOCK_LOG

      b_prevent_display_lock_lock_log = true;

#endif

      synchronization_lock synchronizationlock(user_mutex());

      windowing_output_debug_string("\n::GetCursorPos 1");

      display_lock displaylock(this);

      XQueryPointer(Display(), DefaultRootWindow(Display()), &root_return, &child_return, &ppointCursor->x,
                    &ppointCursor->y, &win_x_return, &win_y_return, &mask_return);

#ifdef display_lock_LOCK_LOG

      b_prevent_display_lock_lock_log = false;

#endif

      windowing_output_debug_string("\n::GetCursorPos 2");

      return true;

   }


   XImage *display::_x11_create_image(::image_pointer pimage)
   {

      pimage->map();

      char *image32 = (char *) pimage->get_data();

      int width = pimage->width();

      int height = pimage->height();

      int depth = 32; // works fine with depth = 24

      int bitmap_pad = 32; // 32 for 24 and 32 bpp, 16, for 15&16

      int bytes_per_line = pimage->scan_size(); // number of bytes in the client image between the start of one scanline and the start of the next

      XImage *pximage = XCreateImage(Display(), CopyFromParent, depth, ZPixmap, 0, image32, width, height,
                                     bitmap_pad, bytes_per_line);

      return pximage;

   }


   XImage *display::x11_create_image(::image_pointer pimage)
   {

      synchronization_lock synchronizationlock(user_mutex());

      windowing_output_debug_string("\n::x11_create_image 1");

      display_lock displaylock(this);

      return _x11_create_image(pimage);

   }


   Pixmap display::_x11_create_pixmap(::image_pointer pimage)
   {

      if (!pimage)
      {

         return 0;

      }

      XImage *pximage = _x11_create_image(pimage);

      if (pximage == nullptr)
      {

         return 0;

      }

      int depth = 32; // works fine with depth = 24

      Pixmap pixmap = XCreatePixmap(Display(), DefaultRootWindow(Display()), pimage->width(), pimage->height(), depth);

      XGCValues gcvalues = {};

      GC gc = XCreateGC(Display(), pixmap, 0, &gcvalues);

      XPutImage(Display(), pixmap, gc, pximage, 0, 0, 0, 0, pimage->width(), pimage->height());

      XFreeGC(Display(), gc);

      return pixmap;

   }


   Pixmap display::x11_create_pixmap(::image_pointer pimage)
   {

      synchronization_lock synchronizationlock(user_mutex());

      windowing_output_debug_string("\n::x11_create_pixmap 1");

      display_lock displaylock(this);

      return _x11_create_pixmap(pimage);

   }

   xcb_window_t *display::xcb_window_list(unsigned long *len)
   {

      xcb_atom_t prop = intern_atom("_NET_CLIENT_LIST_STACKING", False);

      if (prop == 0)
      {

         prop = intern_atom("_NET_CLIENT_LIST", False);

      }

      if (prop == 0)
      {

         return nullptr;

      }

      xcb_atom_t type;
      int form;
      unsigned long remain;
      unsigned char *list;

      errno = 0;
      auto cookie = (xcb_get_property(xcb_connection(), 0,  m_windowRoot, prop, 0, 1024, False, XA_WINDOW,
                                      &type, &form, len, &remain, &list) != Success)
      {
         output_debug_string("winlist() -- GetWinProp");
         return nullptr;
      }

      return (xcb_window_t *) list;

   }


   bool display::xcb_window_list(array<xcb_window_t> &windowa)
   {

      unsigned long len = 0;

      xcb_window_t *list = (xcb_window_t *) xcb_window_list(&len);


      if (list == nullptr)
      {

         return false;

      }

      for (int i = 0; i < (int) len; i++)
      {

         windowa.add(list[i]);

      }

      XFree(list);

      return true;

   }

   bool display::point_is_window_origin(POINT_I32 pointHitTest, ::windowing::window *pwindowExclude, int iMargin)
   {

      bool bIsOrigin = false;

      auto pnode = Node;

      pnode->node_sync(10_s, [this, pointHitTest, pwindowExclude, iMargin, &bIsOrigin]()
      {

         ::windowing_xcb::window *pwindowxcbExclude = nullptr;

         if (pwindowExclude)
         {

            pwindowxcbExclude = dynamic_cast < ::windowing_xcb::window * >(pwindowExclude);

         }

         synchronization_lock synchronizationlock(user_mutex());

         windowing_output_debug_string("\n::GetFocus 1");

#ifdef display_lock_LOCK_LOG

         b_prevent_display_lock_lock_log = false;

#endif

         if (!xcb_connection_t())
         {

            windowing_output_debug_string("\n::GetFocus 1.1");

            return;

         }

         display_lock display(this);

         windowing_output_debug_string("\n::GetFocus 1.01");


         comparable_array<xcb_window_t> windowa;

         if (!xcb_window_list(windowa))
         {

            bIsOrigin = true;

            return;

         }

         ::rectangle_i32 rectTest;

         for (index i = 0; i < windowa.get_size(); i++)
         {

            string strItem = ::xcb_get_name(xcb_connection(), windowa[i]);

            ::rectangle_i32 rectHigher;

            if (::is_set(pwindowxcbExclude) && windowa[i] == pwindowxcbExclude->xcb_window_t())
            {

               continue;

            }

            if (::xcb_get_window_rect(xcb_connection(), windowa[i], rectHigher))
            {

               ::rectangle_i32 rectHitTest;

               rectHitTest.set(rectHigher.origin(), ::size_i32());

               rectHitTest.inflate(iMargin + 1);

               if (rectHitTest.contains(pointHitTest))
               {

                  bIsOrigin = true;

                  return;

               }

            }

         }

      });
//
//            });

      return bIsOrigin;

   }


} // namespace windowing_x11



