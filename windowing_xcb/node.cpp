//
// Created by camilo on 27/04/2021. 01:02 BRT --<33ThomasBS!!
//
#include "framework.h"

////void x11_register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);
//
//
//namespace windowing_xcb
//{
//
//
//   node::node()
//   {
//
//      m_pNodeXcb = this;
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
//   Display * node::_get_Display()
//   {
//
//      return (Display *) ::aura_posix::node::_get_Display();
//
//   }
//
//
//   ::x11::display * node::_get_display()
//   {
//
//      return ::x11::display::get(this);
//
//   }
//
//
//   xcb_connection_t * node::_get_connection()
//   {
//
//      return (xcb_connection_t *) ::aura_posix::node::_get_connection();
//
//   }
//
//
//
//
//   void node::install_mouse_hook(::matter * pmatterListener)
//   {
//
//      auto psystem = acmesystem()->m_paurasystem;
//
//      auto psession = psystem->get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing1()->m_pWindowing4;
//
//      pwindowing->register_extended_event_listener(pmatterListener, true, false);
//
//      //auto estatus =
//
////      if(!estatus)
////      {
////
////         throw ::exception(estatus);
////
////      }
//
//      //return ::success;
//
//   }
//
//
//   void node::install_keyboard_hook(::matter * pmatterListener)
//   {
//
//      auto psystem = acmesystem()->m_paurasystem;
//
//      auto psession = psystem->get_session();
//
//      auto puser = psession->user();
//
//      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing1()->m_pWindowing4;
//
//      //o estatus =
//      //
//      pwindowing->register_extended_event_listener(pmatterListener, false, true);
//
////      if(!estatus)
////      {
////
////         throw ::exception(estatus);
////
////      }
//
//      //return ::success;
//
//   }
//
//
//
//   void node::uninstall_keyboard_hook(::matter * pmatterListener)
//   {
//
////      auto psystem = acmesystem()->m_paurasystem;
////
////      auto psession = psystem->get_session();
////
////      auto puser = psession->user();
////
////      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;
////
////      pwindowing->uninstall_keyboard_hook(pmatterListener);
////
////      //return ::success;
//
//   }
//
//
//   void node::uninstall_mouse_hook(::matter * pmatterListener)
//   {
//
////      auto psystem = acmesystem()->m_paurasystem;
////
////      auto psession = psystem->get_session();
////
////      auto puser = psession->user();
////
////      auto pwindowing = (::windowing_xcb::windowing *) puser->windowing()->m_pWindowing;
////
////      pwindowing->uninstall_mouse_hook(pmatterListener);
//
//      //return ::success;
//
//   }
//
//
//} // namespace windowing_xcb
//


