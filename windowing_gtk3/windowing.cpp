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
#include "windowing_system_x11/display_lock.h"


namespace windowing_gtk3
{


   windowing::windowing()
   {

      printf("windowing_gtk3::windowing::windowing()");

      defer_create_synchronization();

      m_bRootSelectInput = false;

      m_itask = -1;

      m_pWindowing4 = this;

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

      if(::windowing::get_ewindowing() == ::windowing::e_windowing_wayland)
      {

         return false;

      }

      return true;

   }


   bool windowing::is_branch_current() const
   {

      auto itaskCurrent = ::current_itask();

      return itaskCurrent == m_itask;


   }


//   ::windowing::window * windowing::new_window(::windowing::window * pimpl)
//   {
//
//      ::pointer<::windowing_gtk3::window> pwindow = pimpl->__create<::windowing::window>();
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

      m_pdisplay->erase_window(pwindow);

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
//      auto & pfactory = platform()->factory("input", "libinput");
//
//      auto pinput = __create<::input::input>(pfactory);
//
//      return pinput;
//
//   }


   void windowing::initialize_windowing(::user::user * puser)
   {

      ::windowing_posix::windowing::initialize_windowing(puser);

      information() << "windowing_gtk3::windowing::initialize_windowing";

      auto pdisplay = __create<::windowing::display>();

      pdisplay->initialize_display(this);

      m_pdisplay = pdisplay;

      if (!pdisplay)
      {

         throw ::exception(error_no_interface,
                           "Failed to cast pdisplay to m_pdisplay at windowing_gtk3::windowing::initialize");

      }

      _libsn_start_context();

   }


   ::windowing::display * windowing::display()
   {

      return m_pdisplay;

   }


   ::pointer<::windowing::cursor> windowing::load_default_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_pcursormanager)
      {

         __construct_new(m_pcursormanager);

      }

      auto & pcursor = m_pcursormanager->m_cursormap[ecursor];

      if (pcursor)
      {

         return pcursor;

      }

      int iCursor = 0;

      if (ecursor == e_cursor_size_top_left)
      {

         iCursor = XC_top_left_corner;

      }
      else if (ecursor == e_cursor_size_top_right)
      {

         iCursor = XC_top_right_corner;

      }
      else if (ecursor == e_cursor_size_top)
      {

         iCursor = XC_top_side;

      }
      else if (ecursor == e_cursor_size_right)
      {

         iCursor = XC_right_side;

      }
      else if (ecursor == e_cursor_size_left)
      {

         iCursor = XC_left_side;

      }
      else if (ecursor == e_cursor_size_bottom)
      {

         iCursor = XC_bottom_side;

      }
      else if (ecursor == e_cursor_size_bottom_left)
      {

         iCursor = XC_bottom_left_corner;

      }
      else if (ecursor == e_cursor_size_bottom_right)
      {

         iCursor = XC_bottom_right_corner;

      }
      else if (ecursor == e_cursor_arrow)
      {

         iCursor = XC_arrow;

      }

      if (iCursor == 0)
      {

         return nullptr;

      }

      windowing_output_debug_string("::x11_GetWindowRect 1");

      return nullptr;

   }


   ::nano::windowing::window * windowing::get_keyboard_focus(::thread *)
   {

      if (!m_pdisplay)
      {

         return nullptr;

      }

      return nullptr;

   }


   ::windowing::window * windowing::get_mouse_capture(::thread *)
   {

      if (!m_pdisplay)
      {

         return nullptr;

      }

      return m_pwindowMouseCapture;

   }


   ::windowing::window * windowing::window(oswindow oswindow)
   {

      return oswindow;

   }


   void windowing::set_mouse_capture(::thread * pthread, ::windowing::window * pwindow)
   {

      m_pwindowMouseCapture = pwindow;

   }


   void windowing::release_mouse_capture(::thread * pthread, ::windowing::window * pwindow)
   {

      m_pdisplay->release_mouse_capture();

   }


   bool windowing::defer_release_mouse_capture(::thread * pthread, ::windowing::window * pwindow)
   {

      if(m_pwindowMouseCapture != pwindow)
      {

         return false;

      }

      release_mouse_capture(pthread, pwindow);

      m_pwindowMouseCapture.release();

      return true;

   }


   void windowing::_on_capture_changed_to(::windowing_gtk3::window * pwindowMouseCaptureNew)
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

         post_ui_message(msg);

      }

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

      auto pwaylanddisplay = m_pdisplay;

   }


} // namespace windowing



