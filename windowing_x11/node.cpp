//
// Created by camilo on 26/04/2021. 13:10 BRT --<33ThomasBS!!
//
#include "framework.h"


//void x11_register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);


namespace windowing_x11
{


   node::node()
   {

      m_pNodeX11 = this;

   }


   node::~node()
   {


   }


   ::e_status node::register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto psession = psystem->get_session();

      auto puser = psession->user();

      auto pwindowing = (::windowing_x11::windowing *) puser->windowing()->m_pWindowing;

      pwindowing->x11_register_extended_event_listener(pdata, bMouse, bKeyboard);

      //::x11_register_extended_event_listener(pdata, bMouse, bKeyboard);

      return ::success;

   }


} // namespace windowing_x11



