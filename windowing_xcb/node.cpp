//
// Created by camilo on 27/04/2021. 01:02 BRT --<33ThomasBS!!
//
#include "framework.h"
#include "_windowing_xcb.h"

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


   ::e_status node::register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto psession = psystem->get_session();

      auto puser = psession->user();

      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;

      pwindowing->register_extended_event_listener(pdata, bMouse, bKeyboard);

      //::x11_register_extended_event_listener(pdata, bMouse, bKeyboard);

      return ::success;

   }


} // namespace windowing_xcb



