//
// Created by camilo on 26/04/2021. 13:10 BRT --<33ThomasBS!!
//
#include "framework.h"


//void x11_register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);


//namespace windowing_x11
//{
//
//
//   node::node()
//   {
//
//      m_pNodeX11 = this;
//
//   }
//
//
//   node::~node()
//   {
//
//
//   }
//
//
//   void node::install_mouse_hook(::matter * pmatter)
//   {
//
//      auto psystem = acmesystem()->m_paurasystem;
//
//      auto psession = psystem->get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = (::windowing_x11::windowing *) puser->windowing1()->m_pWindowing4;
//
//      pwindowing->x11_register_extended_event_listener(pmatter, true, false);
//
//      //::x11_register_extended_event_listener(pdata, bMouse, bKeyboard);
//
//      //return ::success;
//
//   }
//
//
//   void node::install_keyboard_hook(::matter * pmatter)
//   {
//
//      auto psystem = acmesystem()->m_paurasystem;
//
//      auto psession = psystem->get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = (::windowing_x11::windowing *) puser->windowing1()->m_pWindowing4;
//
//      pwindowing->x11_register_extended_event_listener(pmatter, false, true);
//
//      //::x11_register_extended_event_listener(pdata, bMouse, bKeyboard);
//
//      //return ::success;
//
//   }
//
//
//   void node::uninstall_mouse_hook(::matter * pmatter)
//   {
//
//      //return ::error_failed;
//
//   }
//
//
//   void node::uninstall_keyboard_hook(::matter * pmatter)
//   {
//
//      //return ::error_failed;
//
//   }
//
//
//} // namespace windowing_x11
//
//
//
