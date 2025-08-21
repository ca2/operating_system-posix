// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing.h"
#include "window.h"
#include "display.h"
#include "cursor.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/input/input.h"
#include "aura/windowing/cursor_manager.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/windowing/display.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
//#include "windowing_system_x11/display_lock.h"


namespace windowing_gtk3
{


   windowing::windowing()
   {

      printf("windowing_gtk3::windowing::windowing()");

      defer_create_synchronization();

      m_bRootSelectInput = false;

//      m_itask = -1;

      //m_pWindowing4 = this;

      m_bFirstWindowMap = false;

      m_bInitX11Thread = false;

      m_bFinishX11Thread = false;

      //deferx_initializex_x11();

   }


   windowing::~windowing()
   {


   }


   bool windowing::has_readily_gettable_absolute_coordinates() const
   {

      if(::windowing::get_edisplaytype() == ::windowing::e_display_type_wayland)
      {

         return false;

      }

      return windowing_posix::windowing::has_readily_gettable_absolute_coordinates();

   }


   bool windowing::has_mouse_capture_capability()
   {

      if(::windowing::get_edisplaytype() == ::windowing::e_display_type_wayland)
      {

         return false;

      }

      return windowing_posix::windowing::has_mouse_capture_capability();

   }


   bool windowing::is_branch_current() const
   {

      auto itaskCurrent = ::current_itask();

      return itaskCurrent == m_itask;


   }


//   ::windowing::window * windowing::new_window(::windowing::window * pimpl)
//   {
//
//      ::pointer<::windowing_gtk3::window> pwindow = pimpl->øcreate<::windowing::window>();
//
//      if (!pwindow)
//      {
//
//         return nullptr;
//
//      }
//
//      pwindow->m_pwindowing = this;
//
//      pwindow->m_pwindow = pimpl;
//
//      pimpl->m_pwindow = pwindow;
//
//      pwindow->create_window(pimpl);
//
//      return pwindow;
//
//   }


   void windowing::erase_window(::windowing::window * pwindow)
   {

      gtk3_display()->erase_window(pwindow);

   }


   void windowing::initialize(::particle * pparticle)
   {

      ::windowing::windowing::initialize(pparticle);

//      ::pointer < ::input::input > windowing::get_input()
//      {

//      auto & pfactory = acmesystem()->factory("input", "libinput");
//
//      pfactory->merge_to_global_factory();

//         return windowing_posix::windowing::get_input();
//
//      }

   }


//   ::pointer <::input::input> windowing::_get_input()
//   {
//
//      auto & pfactory = ::system()->factory("input", "libinput");
//
//      auto pinput = øcreate<::input::input>(pfactory);
//
//      return pinput;
//
//   }


   void windowing::initialize_windowing()
   {

      ::windowing_posix::windowing::initialize_windowing();

      ::gtk3::acme::windowing::windowing::initialize_windowing();

      information() << "windowing_gtk3::windowing::initialize_windowing";

//      auto pdisplay = øcreate<::windowing::display>();
//
//      pdisplay->open_display();
//
//      m_pdisplay = pdisplay;
//
//      if (!pdisplay)
//      {
//
//         throw ::exception(error_no_interface,
//                           "Failed to cast pdisplay to m_pdisplay at windowing_gtk3::windowing::initialize");
//
//      }

		// commented here: as this is a gtk wrapper, try using gtk's startup notification capability.
      //_libsn_start_context();

   }


   ::windowing::display * windowing::display()
   {

      auto pdisplay = ::windowing::windowing::display();

      if(::is_null(pdisplay))
      {

         return nullptr;

      }

      return pdisplay;

   }


   ::windowing_gtk3::display * windowing::gtk3_display()
   {

      auto pdisplay = this->display();

      if(::is_null(pdisplay))
      {

         return nullptr;

      }

      ::cast < ::windowing_gtk3::display > pgtk3display = pdisplay;

      if(!pgtk3display)
      {

         return nullptr;

      }

      return pgtk3display;

   }


   ::windowing_gtk3::window *windowing:: _window(GtkWindow * pgtkwindow)
   {

      auto pgtk3acmewindowingwindow = ::gtk3::acme::windowing::windowing::_window(pgtkwindow);

      if (! pgtk3acmewindowingwindow)
      {

         return nullptr;

      }

      ::cast < ::windowing_gtk3::window > pgtk3window = pgtk3acmewindowingwindow;

      if (!pgtk3window)
      {

         return nullptr;

      }

      return pgtk3window;

   }


   ::pointer<::windowing::cursor> windowing::load_default_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_pcursormanager)
      {

         øconstruct_new(m_pcursormanager);

      }

      auto & pcursor = m_pcursormanager->m_cursormap[ecursor];

      if (pcursor)
      {

         return pcursor;

      }

//      int iCursor = 0;
//
//      if (ecursor == e_cursor_size_top_left)
//      {
//
//         iCursor = XC_top_left_corner;
//
//      }
//      else if (ecursor == e_cursor_size_top_right)
//      {
//
//         iCursor = XC_top_right_corner;
//
//      }
//      else if (ecursor == e_cursor_size_top)
//      {
//
//         iCursor = XC_top_side;
//
//      }
//      else if (ecursor == e_cursor_size_right)
//      {
//
//         iCursor = XC_right_side;
//
//      }
//      else if (ecursor == e_cursor_size_left)
//      {
//
//         iCursor = XC_left_side;
//
//      }
//      else if (ecursor == e_cursor_size_bottom)
//      {
//
//         iCursor = XC_bottom_side;
//
//      }
//      else if (ecursor == e_cursor_size_bottom_left)
//      {
//
//         iCursor = XC_bottom_left_corner;
//
//      }
//      else if (ecursor == e_cursor_size_bottom_right)
//      {
//
//         iCursor = XC_bottom_right_corner;
//
//      }
//      else if (ecursor == e_cursor_arrow)
//      {
//
//         iCursor = XC_arrow;
//
//      }

      const_char_pointer cursor_name = "left_ptr";

      switch(ecursor)
      {
         case e_cursor_system: cursor_name = "left_ptr"; break;
         case e_cursor_arrow: cursor_name = "left_ptr"; break;
         case e_cursor_hand: cursor_name = "hand1"; break;
         case e_cursor_text_select: cursor_name = "xterm"; break;
         case e_cursor_size_top_left: cursor_name = "top_left_corner"; break;
         case e_cursor_size_top: cursor_name = "top_side"; break;
         case e_cursor_size_top_right: cursor_name = "top_right_corner"; break;
         case e_cursor_size_right: cursor_name = "right_side"; break;
         case e_cursor_size_bottom_right: cursor_name = "bottom_right_corner"; break;
         case e_cursor_size_bottom: cursor_name = "bottom_side"; break;
         case e_cursor_size_bottom_left: cursor_name = "bottom_left_corner"; break;
         case e_cursor_size_left: cursor_name = "left_side"; break;
         case e_cursor_size_vertical: cursor_name = "sb_v_double_arrow"; break;
         case e_cursor_size_horizontal: cursor_name = "sb_h_double_arrow"; break;
         case e_cursor_move: cursor_name = "move"; break;
         case e_cursor_wait: cursor_name = "watch"; break;
         case e_cursor_wait_arrow: cursor_name = "wait"; break;
         default:
            break;
      }
//      if (iCursor == 0)
//      {
//
//         return nullptr;
//
//      }
//
//      windowing_output_debug_string("::x11_GetWindowRect 1");

      øconstruct(pcursor);

      pcursor->m_strCursorName = cursor_name;

      return pcursor;

   }


   ::acme::windowing::window * windowing::get_keyboard_focus(::thread *)
   {

      if (!gtk3_display())
      {

         return nullptr;

      }

      return nullptr;

   }


   ::acme::windowing::window * windowing::get_mouse_capture(::thread *)
   {
	   
      if (!gtk3_display())
      {

         return nullptr;

      }


      // if (has_mouse_capture_capability())
      // {
      //
      //    GdkDisplay *display;
      //    GdkSeat *seat;
      //    GdkDevice *pointer_device;
      //    GdkWindow *grabbed_window;
      //
      //    // Get the default display
      //    display = gdk_display_get_default();
      //    if (!display) {
      //       g_print("No display found.\n");
      //       return nullptr;
      //    }
      //
      //    // Get the default seat
      //    seat = gdk_display_get_default_seat(display);
      //    if (!seat) {
      //       g_print("No seat found.\n");
      //       return nullptr;
      //    }
      //
      //    // Get the pointer device from the seat
      //    pointer_device = gdk_seat_get_pointer(seat);
      //    if (!pointer_device) {
      //       g_print("No pointer device found.\n");
      //       return nullptr;
      //    }
      //    // Check if the device is grabbed and get the window under grab
      //    grabbed_window = gdk_device_get_window_at_position(pointer_device, NULL, NULL);
      //    if (!grabbed_window)
      //    {
      //       g_print("Pointer is not currently grabbed.\n");
      //       return nullptr;
      //    }
      //    g_print("Pointer is grabbed by window: %p\n", grabbed_window);
      //
      //    GtkWindow * pgtkwindow = GTK_WINDOW(grabbed_window);
      //    if (!pgtkwindow)
      //    {
      //
      //       information() << "grabbed_window is not gtk window (but gdk window)";
      //       return nullptr;
      //
      //    }
      //
      //    auto pwindow = _window(pgtkwindow);
      //
      //    if (!pwindow)
      //       {
      //
      //       information() << "grabbed_window is not mapped to a framework window object instance";
      //    return nullptr;
      //
      //    }
      //
      //    return pwindow;
      // }
      // else
      {

         return m_pwindowMouseCapture;

      }

   }


   ::acme::windowing::window * windowing::window(oswindow oswindow)
   {

      return oswindow;

   }


   void windowing::set_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow)
   {

      if (has_mouse_capture_capability())
      {

         pwindow->set_mouse_capture();

      }

      m_pwindowMouseCapture = pwindow;

   }


   void windowing::release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow)
   {

      if (has_mouse_capture_capability())
      {

         pwindow->release_mouse_capture();

      }

      m_pwindowMouseCapture = nullptr;

   }


   bool windowing::defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow)
   {

      if (has_mouse_capture_capability())
      {

         auto pgtk3window = get_mouse_capture(pthread);

         if (!pgtk3window)
         {

            return false;

         }

         ::cast < ::windowing_gtk3::window > pwindowRelease = pwindow;

         if (pgtk3window != pwindowRelease)
         {

            return false;

         }

         release_mouse_capture(pthread, pwindow);

         return true;

      }
      else
      {

         if(m_pwindowMouseCapture != pwindow)
         {

            return false;

         }

         release_mouse_capture(pthread, pwindow);

         m_pwindowMouseCapture.release();

         return true;

      }

   }


   void windowing::_on_capture_changed_to(::windowing_gtk3::window * pwindowMouseCaptureNew)
   {

      auto pwindowMouseCaptureOld = m_pwindowMouseCapture;

      m_pwindowMouseCapture = pwindowMouseCaptureNew;

      if (pwindowMouseCaptureOld && pwindowMouseCaptureOld != pwindowMouseCaptureNew)
      {

         MESSAGE msg;

         msg.m_oswindow = pwindowMouseCaptureOld;
         msg.m_emessage = e_message_capture_changed;
         msg.m_wparam = 0;
         msg.m_lparam = pwindowMouseCaptureNew;

         post_ui_message(msg);

      }

   }


   void windowing::windowing_post_quit()
   {

      ::gtk3::acme::windowing::windowing::windowing_post_quit();

   }


   void windowing::set_mouse_cursor2(::windowing::cursor * pcursor)
   {

      if (
         ::is_null(pcursor)
         )
      {

         return;

      }

      ::pointer < ::windowing_gtk3::cursor > pwaylandcursor = pcursor;

      if (!pwaylandcursor)
      {

         throw
            ::exception(error_null_pointer);

      }

      pwaylandcursor->_create_os_cursor();

      //auto pwaylanddisplay = m_pdisplay;

   }


   ::windowing::windowing * windowing::windowing_windowing()
   {

      return this;

   }


} // namespace windowing



