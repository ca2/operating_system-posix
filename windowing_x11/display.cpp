// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "display.h"
#include "window.h"
#include "windowing.h"
#include "windowing_x11.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/platform/node.h"
#include "apex/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura/graphics/image/image.h"
#include "aura/windowing/desktop_environment.h"
#include "aura_posix/x11/display_lock.h"
#include <X11/extensions/Xrender.h>


extern ::app_core * g_pappcore;

Display * x11_get_display();

::particle * user_synchronization();


void windowing_output_debug_string(const char *pszDebugString);


namespace windowing_x11
{


   display::display()
   {

      zero(m_atoma);

      m_pDisplay = this;
      m_colormap = None;
      m_windowRoot = None;
      m_px11display = nullptr;
      m_atomLongType = None;
      m_atomLongStyle = None;
      m_atomNetWmState = None;
      m_atomLongStyleEx = 0;
      m_countReference = 1;

   }


   display::~display()
   {

   }


#ifdef _DEBUG


   i64 display::get_ref_count()
   {

      return m_countReference;

   }


   i64 display::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

#ifdef WINDOWS

      return InterlockedIncrement64(&m_countReference);

#elif defined(RASPBIAN) && defined(OS32BIT)

      return __sync_add_and_fetch_4(&m_countReference,1);

#else

      return __sync_add_and_fetch(&m_countReference, 1);

#endif

   }


   i64 display::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

#ifdef WINDOWS

      return InterlockedDecrement64(&m_countReference);

#elif defined(RASPBIAN) && defined(OS32BIT)

      return __sync_sub_and_fetch_4(&m_countReference,1);

#else

      return __sync_sub_and_fetch(&m_countReference, 1);

#endif

   }


   i64 display::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      return i;

   }


#endif // DEBUG


   Display * display::_get_system_default_display()
   {

      return nullptr;

   }


   void display::open()
   {

      if(::is_set(m_px11display))
      {

         return;

      }


      bool bBranch = !acmesystem()->m_paurasession->user()->m_pdesktopenvironment->m_bUnhook;

//      m_px11display->m_bUnhook = bUnhook;

      //auto px11displayGdk = _get_system_default_display();

      //m_px11display = ::x11::display::get(this, false, px11displayGdk);

      // Using another memory_new and different X11 Display connection apart from Gtk.
      m_px11display = ::x11::display::get(this, false);

      if(::is_null(m_px11display))
      {

         throw ::exception(error_failed);

      }

      _m_pX11Display = m_px11display->m_pdisplay;

      m_px11display->m_bUnhook = true;

      if (XMatchVisualInfo(m_px11display->m_pdisplay, DefaultScreen(m_px11display->m_pdisplay), 32, TrueColor, &m_visualinfo))
      {

         m_pvisual = m_visualinfo.visual;

      }
      else
      {

         zero(m_visualinfo);

      }

      ::Display * pdisplay = m_px11display->m_pdisplay;

      m_iScreen = XDefaultScreen(pdisplay);

      m_windowRoot = XRootWindow(pdisplay, m_iScreen);

      m_iDepth = m_visualinfo.depth;

      XSetWindowAttributes attr;

      zero(attr);

      m_colormap = XCreateColormap(m_px11display->m_pdisplay, m_windowRoot, m_pvisual, AllocNone);


      //return ::success;

   }


   ::windowing_x11::window * display::_window(Window window)
   {

      if (!window)
      {

         return nullptr;

      }

      critical_section_lock synchronouslock(&m_criticalsectionWindowMap);

      auto passociation = m_windowmap.plookup(window);

      if(::is_null(passociation))
      {

         return nullptr;

      }

      return passociation->m_element2;

   }


   void display::lock_display()
   {

      if(!is_main_thread())
      {

         output_debug_string("not main thread");

      }

      XLockDisplay(m_px11display->m_pdisplay);

   }


   void display::unlock_display()
   {

      XUnlockDisplay(m_px11display->m_pdisplay);

   }


   ::Display *display::Display()
   {

      return ::is_null(this) ? nullptr : m_px11display->m_pdisplay;

   }


   ::Display *display::Display() const
   {

      return ::is_null(this) ? nullptr : m_px11display->m_pdisplay;

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


   bool display::get_monitor_rectangle(index iMonitor, RECTANGLE_I32 & rectangle)
   {

      return ::windowing::display::get_monitor_rectangle(iMonitor, rectangle);

   }


   bool display::get_workspace_rectangle(index iMonitor, RECTANGLE_I32 & rectangle)
   {

      return ::windowing::display::get_workspace_rectangle(iMonitor, rectangle);

   }


   ::windowing::window * display::get_mouse_capture()
   {

      return m_pwindowMouseCapture;

   }


   ::e_status display::release_mouse_capture()
   {

      auto predicate = [this]()
      {

        synchronous_lock synchronouslock(user_synchronization());

        _on_capture_changed_to(nullptr);

        windowing_output_debug_string("\noswindow_data::ReleaseCapture 1");

        display_lock displaylock(Display());

        int_bool bRet = XUngrabPointer(Display(), CurrentTime) != false;

        windowing_output_debug_string("\noswindow_data::ReleaseCapture 2");

      };

      auto pwindowing = x11_windowing();

      pwindowing->windowing_post(predicate);

      return ::success;

   }


   ::windowing_x11::windowing * display::x11_windowing()
   {

      return (::windowing_x11::windowing *) m_pwindowing->m_pWindowing4;

   }


   void display::_on_capture_changed_to(::windowing_x11::window * pwindowMouseCaptureNew)
   {

      auto pwindowMouseCaptureOld = m_pwindowMouseCapture;

      m_pwindowMouseCapture = pwindowMouseCaptureNew;

      if (pwindowMouseCaptureOld && pwindowMouseCaptureOld != pwindowMouseCaptureNew)
      {

         MESSAGE msg;

         msg.oswindow = pwindowMouseCaptureOld;
         msg.m_atom = e_message_capture_changed;
         msg.wParam = 0;
         msg.lParam = pwindowMouseCaptureNew;

         auto pwindowing = x11_windowing();

         pwindowing->post_ui_message(msg);

      }

   }


   Atom display::intern_atom(const char *pszAtomName, bool bCreate)
   {

      if (m_px11display == nullptr)
      {

         return 0;

      }

      return m_px11display->intern_atom(pszAtomName, bCreate);

   }


   Atom display::intern_atom(::x11::enum_atom eatom, bool bCreate)
   {

      if (eatom < 0 || eatom >= ::x11::e_atom_count)
      {

         return None;

      }

      Atom atom = m_atoma[eatom];

      if (atom == None)
      {

         atom = intern_atom(atom_name(eatom), bCreate);

         m_atoma[eatom] = atom;

      }

      return atom;

   }


   ::e_status display::erase_window(::windowing::window * pwindow)
   {

      return error_failed;

   }


   Atom display::net_wm_state_atom(bool bCreate)
   {

      if (m_atomNetWmState == None)
      {

         m_atomNetWmState = intern_atom(::x11::e_atom_net_wm_state, bCreate);

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

      auto window = m_px11display->_get_active_window();

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

      auto ppropertyobject = __new(::property_object);

      auto predicate = [this,ppropertyobject]()
      {

         synchronous_lock synchronouslock(user_synchronization());

         oswindow oswindow = nullptr;

         windowing_output_debug_string("\n::GetFocus 1");

   #ifdef display_lock_LOCK_LOG

         b_prevent_display_lock_lock_log = false;

   #endif

         display_lock displaylock(Display());

         windowing_output_debug_string("\n::GetFocus 1.01");

         Window window = None;

         int revert_to = 0;

         bool bOk = XGetInputFocus(Display(), &window, &revert_to) != 0;

         if (!bOk)
         {

            windowing_output_debug_string("\n::GetFocus 1.2");

            return;

         }

         if (window == None || window == PointerRoot)
         {

            windowing_output_debug_string("\n::GetFocus 1.3");

            return;

         }

         ppropertyobject->payload("window") = (::iptr) window;

         windowing_output_debug_string("\n::GetFocus 2");

      };

      auto pwindowing = x11_windowing();

      //proutine->set_timeout(5_s);

      pwindowing->windowing_send(predicate);

//      if(proutine->has_timed_out())
//      {
//
//         return nullptr;
//
//      }

      if(ppropertyobject->payload("window").is_new())
      {

         return nullptr;

      }

      Window window = (Window) ppropertyobject->payload("window").iptr();

      auto pwindow = _window(window);

      if(!pwindow)
      {

         return nullptr;

      }

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

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("\n::GetCursorPos 1");

      display_lock displaylock(Display());

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

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("\n::x11_create_image 1");

      display_lock displaylock(Display());

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

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("\n::x11_create_pixmap 1");

      display_lock displaylock(Display());

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

      auto psystem = acmesystem()->m_papexsystem;

      auto pnode = psystem->node();

      pnode->node_send([this, pointHitTest, pwindowExclude, iMargin, &bIsOrigin]()
      {

         ::windowing_x11::window *pwindowxcbExclude = nullptr;

         if (pwindowExclude)
         {

            pwindowxcbExclude = dynamic_cast < ::windowing_x11::window * >(pwindowExclude);

         }

         synchronous_lock synchronouslock(user_synchronization());

         windowing_output_debug_string("\n::GetFocus 1");

#ifdef display_lock_LOCK_LOG

         b_prevent_display_lock_lock_log = false;

#endif

         if (!Display())
         {

            windowing_output_debug_string("\n::GetFocus 1.1");

            return;

         }

         display_lock displaylock(Display());

         windowing_output_debug_string("\n::GetFocus 1.01");

         auto windowa = x11_window_list();

         ::rectangle_i32 rectangleTest;

         for (index i = 0; i < windowa.get_size(); i++)
         {

            string strItem = ::x11_get_name(Display(), windowa[i]);

            ::rectangle_i32 rectangleHigher;

            if (::is_set(pwindowxcbExclude) && windowa[i] == pwindowxcbExclude->Window())
            {

               continue;

            }

            if (::x11_get_window_rect(Display(), windowa[i], rectangleHigher))
            {

               ::rectangle_i32 rectangleHitTest;

               rectangleHitTest.set(rectangleHigher.origin(), ::size_i32());

               rectangleHitTest.inflate(iMargin + 1);

               if (rectangleHitTest.contains(pointHitTest))
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



