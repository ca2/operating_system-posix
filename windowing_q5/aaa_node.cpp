//
// Created by camilo on 26/04/2021. 13:10 BRT --<33ThomasBS!!
//
#include "framework.h"


//void x11_register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);


//namespace windowing_kde5
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
//      auto psystem = system();
//
//      auto psession = psystem->get_session();
//
//      auto puser = user();
//
//      auto pwindowing = (::windowing_kde5::windowing *) puser->windowing()->m_pWindowing4;
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
//      auto psystem = system();
//
//      auto psession = psystem->get_session();
//
//      auto puser = user();
//
//      auto pwindowing = (::windowing_kde5::windowing *) puser->windowing()->m_pWindowing4;
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
//} // namespace windowing_kde5
//
//
//
