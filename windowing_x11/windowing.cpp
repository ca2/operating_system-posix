// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing_x11.h"
#include <X11/cursorfont.h>


namespace windowing_x11
{


   windowing::windowing()
   {

      defer_create_mutex();

      m_bRootSelectInput = false;

      m_itask = -1;

      m_pWindowing = this;

      m_bFirstWindowMap = false;

      m_bInitX11Thread = false;

      m_bFinishX11Thread = false;

      defer_initialize_x11();

   }


   windowing::~windowing()
   {


   }


   bool windowing::is_branch_current() const
   {

      auto ithreadCurrent = get_current_ithread();

      return ithreadCurrent == m_itask;


   }


   ::windowing::window * windowing::new_window(::user::interaction_impl * pimpl)
   {

      __pointer(::windowing_x11::window) pwindow = pimpl->__create < ::windowing::window >();

      if(!pwindow)
      {

         return nullptr;

      }

      pwindow->m_pwindowing = this;

      pwindow->m_pimpl = pimpl;

      pimpl->m_pwindow = pwindow;

      pwindow->create_window(pimpl);

      return pwindow;

   }


    ::e_status windowing::erase_window(::windowing::window * pwindow)
   {

      return m_pdisplay->remove_window(pwindow);

   }


   ::e_status windowing::initialize(::object * pobject)
   {

      auto estatus = ::windowing::windowing::initialize(pobject);

      if(!estatus)
      {

         return estatus;

      }

      initialize_windowing();

      auto pdisplay = __create < ::windowing::display >();

      if(!pdisplay)
      {

         output_debug_string("\nFailed to __create < ::windowing::display > at windowing_x11::windowing::initialize");

         return ::error_no_factory;

      }

      estatus = pdisplay->initialize_display(this);

      if(!estatus)
      {

         output_debug_string("\nFailed to initialize_display at windowing_x11::windowing::initialize");

         return estatus;

      }

      m_pdisplay = pdisplay;

      if(!pdisplay)
      {

         output_debug_string("\nFailed to cast pdisplay to m_pdisplay at windowing_x11::windowing::initialize");

         return error_no_interface;

      }

      estatus = m_pdisplay->open();

      if(!estatus)
      {

         output_debug_string("\nFailed to m_pdisplay->open at windowing_x11::windowing::initialize");

         return estatus;

      }

      return ::success;

   }


   ::e_status windowing::start()
   {

      auto psystem = m_psystem->m_papexsystem;

      if (psystem->m_bUser)
      {

         defer_initialize_x11();

      }

      auto pnode = psystem->node();

      if(pnode)
      {

         _libsn_start_context();

         branch_task(pnode);

      }
      else
      {

         x11_main();

      }

      return ::success;

   }


   ::e_status windowing::windowing_branch(const ::routine & routine)
   {

      if(::is_null(routine.m_p))
      {

         return error_failed;

      }

      synchronous_lock synchronouslock(mutex());

      m_routinelist.add_tail(routine);

      return ::success_scheduled;

   }


   bool windowing::x11_runnable_step()
   {

      synchronous_lock synchronouslock(mutex());

      if(m_routinelist.is_empty())
      {

         return false;

      }

      do
      {

         {

            auto routine = m_routinelist.pick_head();

            synchronouslock.unlock();

            routine();

         }

         synchronouslock.lock();

      }
      while(m_routinelist.has_element());

      return true;

   }


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


   __pointer(::windowing::cursor) windowing::load_default_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(mutex());

      if (!m_pcursormanager)
      {

         auto estatus = __construct_new(m_pcursormanager);

         if (!estatus)
         {

            return nullptr;

         }

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

      synchronous_lock sl(user_mutex());

      windowing_output_debug_string("\n::x11_GetWindowRect 1");

      display_lock lock(m_pdisplay->Display());

      auto cursor = XCreateFontCursor(m_pdisplay->Display(), iCursor);

      auto pcursorX11 = __create < ::windowing_x11::cursor >();

      pcursor = pcursorX11;

      pcursorX11->m_cursor = cursor;

      return pcursor;

   }


   void windowing::_message_handler(void * p)
   {

      XEvent * pevent = (XEvent *) p;

   }


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


   ::e_status windowing::release_mouse_capture()
   {

      auto estatus = m_pdisplay->release_mouse_capture();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }



} // namespace windowing



