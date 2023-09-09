// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing.h"
#include "window.h"
#include "display.h"
#include "cursor.h"
#include "acme/parallelization/synchronous_lock.h"
//#include "acme/primitive/primitive/function.h"
#include "aura/windowing/cursor_manager.h"
#include <X11/cursorfont.h>
#include "aura/user/user/interaction_impl.h"
#include "aura/windowing/display.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura_posix/x11/display_lock.h"


namespace windowing_wayland
{


   windowing::windowing()
   {

      printf("windowing_wayland::windowing::windowing()");

      defer_create_synchronization();

      m_bRootSelectInput = false;

      m_itask = -1;

      m_pWindowing4 = this;

      m_bFirstWindowMap = false;

      m_bInitX11Thread = false;

      m_bFinishX11Thread = false;

      //defer_initialize_x11();

   }


   windowing::~windowing()
   {


   }


   bool windowing::is_branch_current() const
   {

      auto itaskCurrent = get_current_itask();

      return itaskCurrent == m_itask;


   }


   ::windowing::window * windowing::new_window(::user::interaction_impl * pimpl)
   {

      ::pointer<::windowing_wayland::window> pwindow = pimpl->__create<::windowing::window>();

      if (!pwindow)
      {

         return nullptr;

      }

      pwindow->m_pwindowing = this;

      pwindow->m_puserinteractionimpl = pimpl;

      pimpl->m_pwindow = pwindow;

      pwindow->create_window(pimpl);

      return pwindow;

   }


   void windowing::erase_window(::windowing::window * pwindow)
   {

      m_pdisplay->erase_window(pwindow);

   }


   void windowing::initialize(::particle * pparticle)
   {

      ::windowing::windowing::initialize(pparticle);

   }


   void windowing::initialize_windowing(::user::user * puser)
   {

      ::windowing_posix::windowing::initialize_windowing(puser);

      information() << "windowing_wayland::windowing::initialize_windowing";

      auto pdisplay = __create<::windowing::display>();

      pdisplay->initialize_display(this);

      m_pdisplay = pdisplay;

      if (!pdisplay)
      {

         throw ::exception(error_no_interface,
                           "Failed to cast pdisplay to m_pdisplay at windowing_wayland::windowing::initialize");

      }

      m_pdisplay->open();

      _libsn_start_context();

   }


//   void windowing::start()
//   {
//
//      auto psystem = acmesystem()->m_papexsystem;
//
//      if (psystem->m_bUser)
//      {
//
//         defer_initialize_x11();
//
//      }
//
//      auto pnode = psystem->node();
//
//      if(pnode)
//      {
//
//         _libsn_start_context();
//
//         branch_element(pnode);
//
//      }
//      else
//      {
//
//         x11_main();
//
//      }
//
//      //return ::success;
//
//   }


   void windowing::windowing_post(const ::procedure & procedure)
   {

      if (!procedure)
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock synchronouslock(this->synchronization());

      m_procedurelist.add_tail(procedure);

      //return ::success_scheduled;

   }


//   bool windowing::x11_runnable_step()
//   {
//
//      bool bHandled = false;
//
//      process_owned_procedure_list(m_procedurelistPriority, bHandled);
//
//      if (m_pdisplay)
//      {
//
//         if (m_pdisplay->m_px11display)
//         {
//
//            while (m_pdisplay->m_px11display->x11_posted())
//            {
//
//               bHandled = true;
//
//            }
//
//         }
//
//      }
//
//      process_owned_procedure_list(m_procedurelist, bHandled);
//
//      return bHandled;
//
//   }


//   void windowing::process_procedure_list(::procedure_list & procedurelist, bool & bHandled)
//   {
//
//      _synchronous_lock synchronouslock(this->synchronization());
//
//      if(procedurelist.is_empty())
//      {
//
//         return;
//
//      }
//
//      do
//      {
//
//         {
//
//            auto routine = procedurelist.pick_head();
//
//            synchronouslock.unlock();
//
//            routine();
//
//         }
//
//         synchronouslock.lock();
//
//      }
//      while(procedurelist.has_element());
//
//   }


   ::windowing::display * windowing::display()
   {

      return m_pdisplay;

   }


   ::windowing_wayland::window * windowing::_window(::wl_surface * pwlsurface)
   {

      if (!m_pdisplay)
      {

         return nullptr;

      }

      auto pwindow = m_pdisplay->_window(pwlsurface);

      return pwindow;

   }


   ::pointer<::windowing::cursor>windowing::load_default_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_pcursormanager)
      {

         //auto estatus =
         //
         //
         __construct_new(m_pcursormanager);

//         if (!estatus)
//         {
//
//            return nullptr;
//
//         }

      }

      auto & pcursor = m_pcursormanager->m_cursormap[ecursor];

      if(pcursor)
      {

         return pcursor;

      }

      int iCursor = 0;

      if(ecursor == e_cursor_size_top_left)
      {

         iCursor = XC_top_left_corner;

      }
      else if(ecursor == e_cursor_size_top_right)
      {

         iCursor = XC_top_right_corner;

      }
      else if(ecursor == e_cursor_size_top)
      {

         iCursor = XC_top_side;

      }
      else if(ecursor == e_cursor_size_right)
      {

         iCursor = XC_right_side;

      }
      else if(ecursor == e_cursor_size_left)
      {

         iCursor = XC_left_side;

      }
      else if(ecursor == e_cursor_size_bottom)
      {

         iCursor = XC_bottom_side;

      }
      else if(ecursor == e_cursor_size_bottom_left)
      {

         iCursor = XC_bottom_left_corner;

      }
      else if(ecursor == e_cursor_size_bottom_right)
      {

         iCursor = XC_bottom_right_corner;

      }
      else if(ecursor == e_cursor_arrow)
      {

         iCursor = XC_arrow;

      }

      if(iCursor == 0)
      {

         return nullptr;

      }

      synchronous_lock sl(user_synchronization());

      windowing_output_debug_string("::x11_GetWindowRect 1");

      //display_lock lock(m_pdisplay->Display());

//      auto cursor = XCreateFontCursor(m_pdisplay->Display(), iCursor);
//
//      auto pcursorX11 = __create < ::windowing_wayland::cursor >();
//
//      pcursor = pcursorX11;
//
//      pcursorX11->m_cursor = cursor;

      //return pcursor;

      return nullptr;


   }


//   void windowing::_message_handler(void * p)
//   {
//
//      XEvent * pevent = (XEvent *) p;
//
//   }


   ::windowing::window * windowing::get_keyboard_focus(::thread *)
   {

      if(!m_pdisplay)
      {

         return nullptr;

      }

      auto pwindow = m_pdisplay->get_keyboard_focus();

      return pwindow;

   }


   ::windowing::window * windowing::get_mouse_capture(::thread *)
   {

      if(!m_pdisplay)
      {

         return nullptr;

      }

      auto pwindow = m_pdisplay->get_mouse_capture();

      return pwindow;

   }


   ::windowing::window * windowing::window(oswindow oswindow)
   {

      return oswindow;

   }


   void windowing::release_mouse_capture()
   {

      //auto estatus =
      //
      m_pdisplay->release_mouse_capture();

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   void windowing::install_mouse_hook(::matter * pmatter)
   {

//      auto psystem = acmesystem()->m_paurasystem;
//
//      auto psession = psystem->get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = (::windowing_wayland::windowing *) puser->windowing()->m_pWindowing4;
//
//      pwindowing->x11_register_extended_event_listener(pmatter, true, false);
//
//      //::x11_register_extended_event_listener(pdata, bMouse, bKeyboard);
//
//      //return ::success;

   }


   void windowing::install_keyboard_hook(::matter * pmatter)
   {

//      auto psystem = acmesystem()->m_paurasystem;
//
//      auto psession = psystem->get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = (::windowing_wayland::windowing *) puser->windowing()->m_pWindowing4;
//
//      pwindowing->x11_register_extended_event_listener(pmatter, false, true);
//
//      //::x11_register_extended_event_listener(pdata, bMouse, bKeyboard);
//
//      //return ::success;

   }


   void windowing::uninstall_mouse_hook(::matter * pmatter)
   {

      //return ::error_failed;

   }


   void windowing::uninstall_keyboard_hook(::matter * pmatter)
   {

      //return ::error_failed;

   }


} // namespace windowing


