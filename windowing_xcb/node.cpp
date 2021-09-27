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


   ::e_status node::install_mouse_hook(::matter * pmatterListener)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto psession = psystem->get_session();

      auto puser = psession->user();

      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;

      pwindowing->install_mouse_hook(pmatterListener);

      return ::success;

   }


   ::e_status node::install_keyboard_hook(::matter * pmatterListener)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto psession = psystem->get_session();

      auto puser = psession->user();

      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;

      pwindowing->install_keyboard_hook(pmatterListener);

      return ::success;

   }



   ::e_status node::uninstall_keyboard_hook(::matter * pmatterListener)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto psession = psystem->get_session();

      auto puser = psession->user();

      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;

      pwindowing->uninstall_keyboard_hook(pmatterListener);

      return ::success;

   }


   ::e_status node::uninstall_mouse_hook(::matter * pmatterListener)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto psession = psystem->get_session();

      auto puser = psession->user();

      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;

      pwindowing->uninstall_mouse_hook(pmatterListener);

      return ::success;

   }


} // namespace windowing_xcb



