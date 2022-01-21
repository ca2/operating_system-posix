//
// Created by camilo on 27/04/2021. 01:02 BRT --<33ThomasBS!!
//
#include "framework.h"

//void x11_register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);


namespace windowing_xcb
{


   node::node()
   {

      m_pNodeXcb = this;

   }


   node::~node()
   {


   }


   Display * node::_get_Display()
   {

      return (Display *) ::aura::posix::node::_get_Display();

   }


   xcb_connection_t * node::_get_connection()
   {

      return (xcb_connection_t *) ::aura::posix::node::_get_connection();

   }




   void node::install_mouse_hook(::matter * pmatterListener)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto psession = psystem->get_session();

      auto puser = psession->user();

      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;

      pwindowing->register_extended_event_listener(pmatterListener, false, true);

      //auto estatus =

//      if(!estatus)
//      {
//
//         throw_status(estatus);
//
//      }

      //return ::success;

   }


   void node::install_keyboard_hook(::matter * pmatterListener)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto psession = psystem->get_session();

      auto puser = psession->user();

      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;

      //o estatus =
      //
      pwindowing->register_extended_event_listener(pmatterListener, true, false);

//      if(!estatus)
//      {
//
//         throw_status(estatus);
//
//      }

      //return ::success;

   }



   void node::uninstall_keyboard_hook(::matter * pmatterListener)
   {

//      auto psystem = m_psystem->m_paurasystem;
//
//      auto psession = psystem->get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;
//
//      pwindowing->uninstall_keyboard_hook(pmatterListener);
//
//      //return ::success;

   }


   void node::uninstall_mouse_hook(::matter * pmatterListener)
   {

//      auto psystem = m_psystem->m_paurasystem;
//
//      auto psession = psystem->get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;
//
//      pwindowing->uninstall_mouse_hook(pmatterListener);

      //return ::success;

   }


} // namespace windowing_xcb



