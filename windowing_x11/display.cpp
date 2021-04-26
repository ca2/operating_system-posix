// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "apex/platform/app_core.h"
#include "windowing.h"
#include "windowing_x11.h"


extern ::app_core * g_pappcore;

Display * x11_get_display();

mutex * user_mutex();


void windowing_output_debug_string(const char *pszDebugString);


namespace windowing_x11
{


   display::display()
   {

      m_pDisplay = this;
      m_colormap = None;
      m_windowRoot = None;
      m_pdisplay = nullptr;
      m_atomLongType = None;
      m_atomLongStyle = None;
      m_atomNetWmState = None;
      m_atomLongStyleEx = 0;
      m_countReference = 1;

   }


   display::~display()
   {

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

      if (XMatchVisualInfo(m_pdisplay, DefaultScreen(m_pdisplay), 32, TrueColor, &m_visualinfo))
      {

         m_pvisual = m_visualinfo.visual;

      }
      else
      {

         __zero(m_visualinfo);

      }

      m_iScreen = DefaultScreen(m_pdisplay);

      m_windowRoot = RootWindow(m_pdisplay, m_iScreen);

      m_iDepth = m_visualinfo.depth;

      XSetWindowAttributes attr;

      __zero(attr);

      m_colormap = XCreateColormap(m_pdisplay, m_windowRoot, m_pvisual, AllocNone);

      return ::success;

   }


   ::windowing_x11::window * display::_window(Window window)
   {

      if (!window)
      {

         return nullptr;

      }

      critical_section_lock synchronouslock(&m_criticalsectionWindowMap);

      auto & pwindow = m_windowmap[window];

      return pwindow;

   }


   void display::lock_display()
   {

      if(!is_main_thread())
      {

         output_debug_string("not main thread");

      }

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


   int display::Screen()
   {

      return ::is_null(this) ? 0 : m_iScreen;

   }


   int display::Screen() const
   {

      return ::is_null(this) ? 0 : m_iScreen;

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

   }


   bool display::get_workspace_rectangle(index iMonitor, RECTANGLE_I32 * prectangle)
   {

      return ::windowing::display::get_workspace_rectangle(iMonitor, prectangle);

   }


   ::windowing::window * display::get_mouse_capture()
   {

      return m_pwindowMouseCapture;

   }


   ::e_status display::release_mouse_capture()
   {

      auto proutine =  __routine([this]()
      {

        synchronous_lock synchronouslock(user_mutex());

        _on_capture_changed_to(nullptr);

        windowing_output_debug_string("\noswindow_data::ReleaseCapture 1");

        display_lock displaylock(this);

        int_bool bRet = XUngrabPointer(Display(), CurrentTime) != false;

        windowing_output_debug_string("\noswindow_data::ReleaseCapture 2");

      });

      auto pwindowing = x11_windowing();

      pwindowing->windowing_branch(proutine);

      return ::success;

   }


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


   Atom display::intern_atom(x_window::enum_atom eatom, bool bCreate)
   {

      if (eatom < 0 || eatom >= x_window::e_atom_count)
      {

         return None;

      }

      Atom atom = m_atoma[eatom];

      if (atom == None)
      {

         atom = intern_atom(x_window::atom_name(eatom), bCreate);

         m_atoma[eatom] = atom;

      }

      return atom;

   }


   Atom display::net_wm_state_atom(bool bCreate)
   {

      if (m_atomNetWmState == None)
      {

         m_atomNetWmState = intern_atom(x_window::e_atom_net_wm_state, bCreate);

      }

      return m_atomNetWmState;

   }


   Picture display::xrender_create_picture(::image_pointer pimage)
   {

      Pixmap pixmap = _x11_create_pixmap(pimage);

      if (pixmap == 0)
      {

         return 0;

      }

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

      //auto pmatterWindow = __matter(__pointer(::windowing_x11::window));

      auto pmatter = __new(::matter);

      output_debug_string("A");

      auto proutine = __routine([this,pmatter]()
      {

         synchronous_lock synchronouslock(user_mutex());

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

         //pmatterWindow = _window(window);

         windowing_output_debug_string("\n::GetFocus 2");

      });

      auto pwindowing = x11_windowing();

      pwindowing->windowing_branch(proutine);

      if(proutine->sync_wait(5_s).failed())
      {

         return nullptr;

      }

      //return *pmatterWindow;
      return nullptr;

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

      synchronous_lock synchronouslock(user_mutex());

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

      synchronous_lock synchronouslock(user_mutex());

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

      synchronous_lock synchronouslock(user_mutex());

      windowing_output_debug_string("\n::x11_create_pixmap 1");

      display_lock displaylock(this);

      return _x11_create_pixmap(pimage);

   }


   comparable_array < Window > display::x11_window_list()
   {

      comparable_array < Window > windowa;

      auto atomWindowList = intern_atom("_NET_CLIENT_LIST_STACKING", False);

      if (atomWindowList == 0)
      {

         atomWindowList = intern_atom("_NET_CLIENT_LIST", False);

      }

      if (atomWindowList == 0)
      {

         return windowa;

      }

      Atom type;
      int form;
      unsigned long remain;
      unsigned char *list;
      unsigned long ulBytesReturned = 0;
      errno = 0;

      Atom actual_type;

      int actual_format;

      unsigned long int bytes_after;

      Window * windowList = nullptr;

      if(XGetWindowProperty(
         Display(),
         Window(),
         atomWindowList, 0, 1024, False, XA_WINDOW,
         &actual_type, &actual_format, &ulBytesReturned, &bytes_after,
         (unsigned char **) &windowList) != Success)
      {

         output_debug_string("winlist() -- GetWinProp");

         return windowa;

      }

      unsigned long nchildren = ulBytesReturned / sizeof(Window);

      windowa.set_size(nchildren);

      memcpy(windowa.get_data(), windowList, minimum(windowa.get_size_in_bytes(), ulBytesReturned));

      XFree(windowList);

      return windowa;

   }


   bool display::point_is_window_origin(POINT_I32 pointHitTest, ::windowing::window *pwindowExclude, int iMargin)
   {

      bool bIsOrigin = false;

      auto psystem = m_psystem->m_papexsystem;

      auto pnode = psystem->node();

      pnode->node_sync(10_s, [this, pointHitTest, pwindowExclude, iMargin, &bIsOrigin]()
      {

         ::windowing_x11::window *pwindowxcbExclude = nullptr;

         if (pwindowExclude)
         {

            pwindowxcbExclude = dynamic_cast < ::windowing_x11::window * >(pwindowExclude);

         }

         synchronous_lock synchronouslock(user_mutex());

         windowing_output_debug_string("\n::GetFocus 1");

#ifdef display_lock_LOCK_LOG

         b_prevent_display_lock_lock_log = false;

#endif

         if (!Display())
         {

            windowing_output_debug_string("\n::GetFocus 1.1");

            return;

         }

         display_lock display(this);

         windowing_output_debug_string("\n::GetFocus 1.01");


         auto windowa = x11_window_list();

         ::rectangle_i32 rectTest;

         for (index i = 0; i < windowa.get_size(); i++)
         {

            string strItem = ::x11_get_name(Display(), windowa[i]);

            ::rectangle_i32 rectHigher;

            if (::is_set(pwindowxcbExclude) && windowa[i] == pwindowxcbExclude->Window())
            {

               continue;

            }

            if (::x11_get_window_rect(Display(), windowa[i], rectHigher))
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

      return bIsOrigin;

   }


} // namespace windowing_x11



