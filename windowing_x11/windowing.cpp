// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing.h"
#include "window.h"
#include "display.h"
#include "cursor.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/windowing/cursor_manager.h"
#include <X11/cursorfont.h>
#include "aura/windowing/display.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "acme_windowing_x11/display_lock.h"


namespace windowing_x11
{


   windowing::windowing()
   {

      m_bRootSelectInput = false;

      ///m_itask = -1;

      //m_pWindowing4 = this;

      m_bFirstWindowMap = false;

      m_bInitX11Thread = false;

      m_bFinishX11Thread = false;

      //deferx_initializex_x11();

   }


   windowing::~windowing()
   {


   }


   bool windowing::is_branch_current() const
   {

      auto itaskCurrent = current_itask();

      return itaskCurrent == m_itask;


   }


//   ::windowing::window * windowing::new_window(::windowing::window * pimpl)
//   {
//
//      ::pointer<::windowing_x11::window> pwindow = pimpl->øcreate<::windowing::window>();
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

      ::acme::windowing::windowing::initialize(pparticle);

      defer_create_synchronization();



   }


   void windowing::initialize_windowing()
   {

      ::windowing_posix::windowing::initialize_windowing();

      auto pdisplay = øcreate<::windowing::display>();

      //pdisplay->initialize_display();

      m_pdisplay = pdisplay;

      if (!pdisplay)
      {

         throw ::exception(error_no_interface,
                           "Failed to cast pdisplay to m_pdisplay at windowing_x11::windowing::initialize");

      }

      m_pdisplay->open_display();

      _libsn_start_context();

   }


//   void windowing::start()
//   {
//
//      auto psystem = system();
//
//      if (psystem->m_bUser)
//      {
//
//         deferx_initializex_x11();
//
//      }
//
//      auto pnode = psystem->node();
//
//      if(pnode)
//      {
//
//         _libsnx_start_context();
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


//   void windowing::windowing_post(const ::procedure & procedure)
//   {
//
//      if (!procedure)
//      {
//
//         throw ::exception(error_null_pointer);
//
//      }
//
//      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//      m_procedurelist.add_tail(procedure);
//
//      //return ::success_scheduled;
//
//   }


   bool windowing::x11_runnable_step()
   {

      bool bHandled = false;

      //information() << "windowing_x11::windowing::x11_runnable_step";

      process_owned_procedure_list(m_procedurelistPriority, bHandled);

      if (m_pdisplay)
      {

         //if (m_pdisplay->m_px11display)
         {

            while (m_pdisplay->__x11_posted())
            {

               bHandled = true;

            }

         }

      }

      process_owned_procedure_list(m_procedurelist, bHandled);

      return bHandled;

   }


//   void windowing::process_procedure_list(::procedure_list & procedurelist, bool & bHandled)
//   {
//
//      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
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


   ::windowing_x11::window * windowing::_window(Window window)
   {

      if (!m_pdisplay)
      {

         return nullptr;

      }

      auto pwindow = m_pdisplay->_window(window);

      return pwindow;

   }


   ::pointer<::windowing::cursor>windowing::load_default_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (!m_pcursormanager)
      {

         //auto estatus =
         //
         //
         øconstruct_new(m_pcursormanager);

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

      //synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      windowing_output_debug_string("::x11_GetWindowRect 1");

      ::x11::display_lock lock(m_pdisplay->__x11_display());

      auto cursor = XCreateFontCursor(m_pdisplay->__x11_display(), iCursor);

      auto pcursorX11 = øcreate < ::windowing_x11::cursor >();

      pcursor = pcursorX11;

      pcursorX11->m_cursor = cursor;

      return pcursor;

   }



   ::acme::windowing::window * windowing::get_keyboard_focus(::thread *)
   {

      if(!m_pdisplay)
      {

         return nullptr;

      }

      auto pwindow = m_pdisplay->get_keyboard_focus();

      return pwindow;

   }


   ::acme::windowing::window * windowing::get_mouse_capture(::thread *)
   {

      if(!m_pdisplay)
      {

         return nullptr;

      }

      auto pwindow = m_pdisplay->get_mouse_capture();

      return pwindow;

   }


   // ::acme::windowing::window * windowing::window(oswindow oswindow)
   // {
   //
   //    return oswindow;
   //
   // }


   void windowing::release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow)
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


   bool windowing::defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow)
   {

      release_mouse_capture(pthread, pwindow);

      return true;

   }


//   void windowing::add_mouse_message_handler(::particle * pparticle)
//   {
//
//      auto psystem = system();
//
//      auto psession = psystem->get_session();
//
//      auto puser = user();
//
//      auto pwindowing = (::windowing_x11::windowing *) puser->windowing()->m_pWindowing4;
//
//      pwindowing->x11_register_extended_event_listener(pparticle, true, false);
//
//      //::x11_register_extended_event_listener(pdata, bMouse, bKeyboard);
//
//      //return ::success;
//
//   }
//
//
//   void windowing::add_keyboard_message_handler(::particle * pparticle)
//   {
//
//      auto psystem = system();
//
//      auto psession = psystem->get_session();
//
//      auto puser = user();
//
//      auto pwindowing = (::windowing_x11::windowing *) puser->windowing()->m_pWindowing4;
//
//      pwindowing->x11_register_extended_event_listener(pparticle, false, true);
//
//      //::x11_register_extended_event_listener(pdata, bMouse, bKeyboard);
//
//      //return ::success;
//
//   }
//
//
//   void windowing::erase_mouse_message_handler(::particle * pparticle)
//   {
//
//      //return ::error_failed;
//
//   }
//
//
//   void windowing::erase_keyboard_message_handler(::particle * pparticle)
//   {
//
//      //return ::error_failed;
//
//   }


   bool windowing::message_loop_step()
   {

      information() << "windowing_x11::windowing::message_loop_step";

      if(!x11_message_loop_step())
      {

         return false;

      }

      return true;

   }


   void windowing::_on_wm_state_change(::windowing::window* pwindow)
   {

   }




} // namespace windowing



