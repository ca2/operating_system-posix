//
// Created by camilo on 2022-08-17 22:39 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "desktop_environment.h"
//#include "wayland_buffer.h"
#include "acme/platform/system.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/windowing/windowing.h"


////#include "windowing.h"
//#include <QtX11Extras/QX11Info>
//#include <X11/Xlib-xcb.h>
//#include <QScreen>
//
//::particle * user_synchronization();
//
//namespace x11
//{
//   namespace nano
//   {
//      namespace user
//      {
//         void x11_sync(const ::procedure & procedure);
//      } // namespace user
//   } // namespace nano
//} // namespace x11
//

namespace node_gtk3
{


   desktop_environment::desktop_environment()
   {

      //m_pWindowing2 = this;

      //m_bX11 = QX11Info::isPlatformX11();

   }


   desktop_environment::~desktop_environment()
   {


   }


//
//    ::pointer < ::graphics::graphics > desktop_environment::create_graphics()
//    {
//
//       auto edisplaytype = ::windowing::get_edisplaytype();
//
//       //#if !defined(RASPBERRYPIOS) && !defined(FREEBSD) && !defined(__XFCE) && !defined(OPENBSD)
//
// // #ifdef HAS_WAYLAND
// //
// //       if(edisplaytype == e_display_type_wayland)
// //       {
// //
// //          //windowing_x11_factory(pfactory);
// //
// //          return __allocate node_gtk3::wayland_buffer;
// //
// //       }
// //       else
// // #endif
//       {
//          return ::windowing::desktop_environment::create_graphics();
//       }
//
//    }
//

//    ::e_status desktop_environment::_get_monitor_rectangle(::collection::index iIndex, ::int_rectangle *prectangle)
//    {
//
//       //synchronous_lock sl(user_synchronization());
//
//       debug() << "node_gtk3::desktop_environment::_get_monitor_rectangle : " << iIndex;
//
//       GdkDisplay * pdisplay = gdk_display_get_default();
//
//       if (pdisplay == nullptr)
//       {
//
//          return ::error_failed;
//
//       }
//
//       GdkMonitor * pmonitor = gdk_display_get_monitor(pdisplay, iIndex);
//
//       if (pmonitor == nullptr)
//       {
//
//          return ::error_failed;
//
//       }
//
//       GdkRectangle rect;
//
//       gdk_monitor_get_geometry(pmonitor, &rect);
//
//       copy(prectangle, &rect);
//
//       debug() << "node_gtk3::desktop_environment::_get_monitor_rectangle rectangle : " << *prectangle;
//
//       return ::success;
//
//
//   }
//
//
//    void desktop_environment::get_workspace_rectangle(::collection::index iIndex, ::int_rectangle *prectangle)
//    {
//
// //      if(m_bX11)
// //      {
// //
// //         synchronous_lock sl(user_synchronization());
// //
// //         _get_workspace_rectangle(iIndex, prectangle);
// //
// //         //m_pwindowing->windowing_send([this, iIndex, prectangle]() { _get_workspace_rectangle(iIndex, prectangle); });
// //
// //      }
// //      else
//       {
//
//          _get_workspace_rectangle(iIndex, prectangle);
//
//       }
//
//    }
//
//
//    ::e_status desktop_environment::_get_workspace_rectangle(::collection::index iIndex, ::int_rectangle *prectangle)
//    {
//
//       //synchronous_lock sl(user_synchronization());
//
//       information() << "node_gtk3::desktop_environment::_get_workspace_rectangle : " << iIndex;
//
//       GdkDisplay * pdisplay = gdk_display_get_default();
//
//       if (pdisplay == nullptr)
//       {
//
//          return ::error_failed;
//
//       }
//
//       GdkMonitor * pmonitor = gdk_display_get_monitor(pdisplay, iIndex);
//
//       if (pmonitor == nullptr)
//       {
//
//          return ::error_failed;
//
//       }
//
//       GdkRectangle rect;
//
//       gdk_monitor_get_workarea(pmonitor, &rect);
//
//       copy(prectangle, &rect);
//
//       information() << "node_gtk3::desktop_environment::_get_workspace_rectangle rectangle : " << *prectangle;
//
//       return ::success;
//
//    }
//
//
//
//   void desktop_environment::get_monitor_rectangle(::collection::index iIndex, ::int_rectangle *prectangle)
//   {
//
//      debug() << "desktop_environment::get_monitor_rectangle";
//
//      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
//      {
//
//         system()->acme_windowing()->sync([this, iIndex, prectangle]() { _get_monitor_rectangle(iIndex, prectangle); });
//
//      }
//      else
//      {
//
//         _get_monitor_rectangle(iIndex, prectangle);
//
//      }
//
//      debug() << "desktop_environment::get_monitor_rectangle" << *prectangle;
//
//   }
//
// //
// //   void desktop_environment::get_workspace_rectangle(::collection::index iIndex, ::int_rectangle *prectangle)
// //   {
// //
// //      if(m_bX11)
// //      {
// //
// //         m_pwindowing->windowing_send([this, iIndex, prectangle]() { _get_workspace_rectangle(iIndex, prectangle); });
// //
// //      }
// //      else
// //      {
// //
// //         _get_workspace_rectangle(iIndex, prectangle);
// //
// //      }
// //
// //   }
// //
// //
// //   void desktop_environment::windowing_post(const ::procedure & procedure)
// //   {
// //
// //      auto psystem = system();
// //
// //      auto pnode = psystem->node()->cast < node >();
// //
// //      auto pqapplication = pnode->m_pqapplication;
// //
// //      // invoke on the main thread
// //      QMetaObject::invokeMethod(
// //         pqapplication,
// //         [procedure]
// //         {
// //
// //            procedure();
// //
// //         });
// //
// //
// //      //return success;
// //
// //   }
// //
// //
// //   bool desktop_environment::aaa_message_loop_step()
// //   {
// //
// //      auto psystem = system();
// //
// //      auto psession = psystem->session();
// //
// //      auto puser = user();
// //
// //      auto pwindowing = system()->windowing();
// //
// //      if(!pwindowing->xcb_message_loop_step())
// //      {
// //
// //         return false;
// //
// //      }
// //
// //      return true;
// //
// //   }


} // namespace node_gtk3



