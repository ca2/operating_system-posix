// created by Camilo 2021-01-31 05:16 BRT <3CamiloSasukeThomasBorregaardSoerensen
// created by Camilo 2021-04-27 06:06 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "monitor.h"
#include <QMetaType>
#include <QScreen>

//::particle * user_synchronization();
//
//
//namespace node_kde
//{
//
//
//   monitor::monitor()
//   {
//
//
//   }
//
//
//   monitor::~monitor()
//   {
//
//
//   }
//
//
//   void monitor::update_cache()
//   {
//
//      //return ::success_none;
//
//   }
//
//
//   ::u32 monitor::get_monitor_color_temperature()
//   {
//
//      return 0;
//
//   }
//
//
//   bool monitor::adjust_monitor(::u32 dwTemperature, double dBrightness, double dwGamma)
//   {
//
//      return false;
//
//   }
//
//
//   ::e_status monitor::_get_monitor_rectangle()
//   {
//
//      synchronous_lock sl(user_synchronization());
//
//      auto screens = QGuiApplication::screens();
//
//      if (m_iIndex < 0 || m_iIndex >= screens.size())
//      {
//
//         return ::error_failed;
//
//      }
//
//      auto pscreen = screens.at(m_iIndex);
//
//      if (pscreen == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      int left             = 0;
//      int top              = 0;
//      int right            = 0;
//      int bottom           = 0;
//
//      pscreen->geometry().getCoords(&left, &top, &right, &bottom);
//
//      m_rectangle.left     = left;
//      m_rectangle.top      = top;
//      m_rectangle.right    = right;
//      m_rectangle.bottom   = bottom;
//
//      return ::success;
//
//   }
//
//
//   ::e_status monitor::_get_workspace_rectangle()
//   {
//
//      synchronous_lock sl(user_synchronization());
//
//      auto screens = QGuiApplication::screens();
//
//      if (m_iIndex < 0 || m_iIndex >= screens.size())
//      {
//
//         return ::error_failed;
//
//      }
//
//      auto pscreen = screens.at(m_iIndex);
//
//      if (pscreen == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      int left             = 0;
//      int top              = 0;
//      int right            = 0;
//      int bottom           = 0;
//
//      pscreen->availableGeometry().getCoords(&left, &top, &right, &bottom);
//
//      m_rectangleWorkspace.left     = left;
//      m_rectangleWorkspace.top      = top;
//      m_rectangleWorkspace.right    = right;
//      m_rectangleWorkspace.bottom   = bottom;
//
//      return ::success;
//
//   }
//
//
//   void monitor::get_monitor_rectangle(::RECTANGLE_I32 *prectangle)
//   {
//
//      //auto estatus =
//      //
//      xcb_windowing()->windowing_send([this]() { _get_monitor_rectangle(); });
//
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
//
//      //estatus =
//      //
//      ::windowing::monitor::get_monitor_rectangle(prectangle);
//
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;
//
//   }
//
//
//   void monitor::get_workspace_rectangle(::RECTANGLE_I32 *prectangle)
//   {
//
//      //auto estatus =
//      //
//      xcb_windowing()->windowing_send([this]() { _get_workspace_rectangle(); });
//
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
//
//      //estatus =
//      //
//      ::windowing::monitor::get_monitor_rectangle(prectangle);
//
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;
//
//   }
//
//
//   //      node_fork(__routine([psession]
////                           {
////
////                              synchronous_lock sl(user_synchronization());
////
////                              //xdisplay d(x11_get_display());
////
////                              GdkDisplay *pdisplay = gdk_display_get_default();
////
////                              if (pdisplay == nullptr)
////                              {
////
////                                 return;
////
////                              }
////
////                              synchronous_lock slSession(psession->synchronization());
////
////                              ::count iMonitorCount = gdk_display_get_n_monitors(pdisplay);
////
////                              psession->m_rectangleaWorkspace.set_size(iMonitorCount);
////
////                              psession->m_rectangleaMonitor.set_size(iMonitorCount);
////
////                              for (index iMonitor = 0; iMonitor < iMonitorCount; iMonitor++)
////                              {
////
////                                 GdkMonitor *pmonitor = gdk_display_get_monitor(pdisplay, iMonitor);
////
////                                 auto &rectangleWorkspace = psession->m_rectangleaWorkspace[iMonitor];
////
////                                 auto &rectangleMonitor = psession->m_rectangleaMonitor[iMonitor];
////
////                                 if (pmonitor == nullptr)
////                                 {
////
////                                    rectangleWorkspace.Null();
////
////                                    rectangleMonitor.Null();
////
////                                    continue;
////
////                                 }
////
////                                 GdkRectangle rect;
////
////                                 zero(rect);
////
////                                 gdk_monitor_get_workarea(pmonitor, &rect);
////
////                                 __copy(rectangleWorkspace, rect);
////
////                                 zero(rect);
////
////                                 gdk_monitor_get_geometry(pmonitor, &rect);
////
////                                 __copy(rectangleMonitor, rect);
////
////                              }
////
////                           }));
////
////   }
//
//
//} // namespace node_kde
//


