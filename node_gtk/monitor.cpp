// created by Camilo 2021-01-31 05:16 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"


mutex * user_mutex();


namespace node_gtk
{


   monitor::monitor()
   {


   }


   monitor::~monitor()
   {


   }


   ::e_status monitor::update_cache()
   {

      return ::success_none;

   }

   
   ::u32 monitor::get_monitor_color_temperature()
   {

      return 0;

   }


   bool monitor::adjust_monitor(::u32 dwTemperature, double dBrightness, double dwGamma)
   {

      return false;

   }


   ::e_status monitor::_get_monitor_rectangle()
   {

      synchronous_lock sl(user_mutex());

      GdkDisplay * pdisplay = gdk_display_get_default();

      if (pdisplay == nullptr)
      {

         return ::error_failed;

      }

      GdkMonitor * pmonitor = gdk_display_get_monitor(pdisplay, m_iIndex);

      if (pmonitor == nullptr)
      {

         return error_failed;

      }

      GdkRectangle  rect;

      gdk_monitor_get_geometry(pmonitor, &rect);

      ::rectangle_i32 rectangle;

      __copy(m_rectangle, rect);

      return ::success;

   }


   ::e_status monitor::_get_workspace_rectangle()
   {

      synchronous_lock sl(user_mutex());

      GdkDisplay * pdisplay = gdk_display_get_default();

      if (pdisplay == nullptr)
      {

         return error_failed;

      }

      GdkMonitor * pmonitor = gdk_display_get_monitor(pdisplay, m_iIndex);

      if (pmonitor == nullptr)
      {

         return error_failed;

      }

      GdkRectangle rect;

      gdk_monitor_get_workarea(pmonitor, &rect);

      __copy(m_rectangleWorkspace, rect);

      return ::success;

   }


   ::e_status monitor::get_monitor_rectangle(::RECTANGLE_I32 *prectangle)
   {

      auto estatus = x11_windowing()->windowing_sync(5_s, __routine([this]() { _get_monitor_rectangle(); }));

      if(!estatus)
      {

         return estatus;

      }

      estatus = ::windowing::monitor::get_monitor_rectangle(prectangle);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status monitor::get_workspace_rectangle(::RECTANGLE_I32 *prectangle)
   {

      auto estatus = x11_windowing()->windowing_sync(5_s, __routine([this]() { _get_workspace_rectangle(); }));

      if(!estatus)
      {

         return estatus;

      }

      estatus = ::windowing::monitor::get_workspace_rectangle(prectangle);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   //      node_fork(__routine([psession]
//                           {
//
//                              synchronous_lock sl(user_mutex());
//
//                              //xdisplay d(x11_get_display());
//
//                              GdkDisplay *pdisplay = gdk_display_get_default();
//
//                              if (pdisplay == nullptr)
//                              {
//
//                                 return;
//
//                              }
//
//                              synchronous_lock slSession(psession->mutex());
//
//                              ::count iMonitorCount = gdk_display_get_n_monitors(pdisplay);
//
//                              psession->m_rectaWorkspace.set_size(iMonitorCount);
//
//                              psession->m_rectaMonitor.set_size(iMonitorCount);
//
//                              for (index iMonitor = 0; iMonitor < iMonitorCount; iMonitor++)
//                              {
//
//                                 GdkMonitor *pmonitor = gdk_display_get_monitor(pdisplay, iMonitor);
//
//                                 auto &rectWorkspace = psession->m_rectaWorkspace[iMonitor];
//
//                                 auto &rectMonitor = psession->m_rectaMonitor[iMonitor];
//
//                                 if (pmonitor == nullptr)
//                                 {
//
//                                    rectWorkspace.Null();
//
//                                    rectMonitor.Null();
//
//                                    continue;
//
//                                 }
//
//                                 GdkRectangle rect;
//
//                                 __zero(rect);
//
//                                 gdk_monitor_get_workarea(pmonitor, &rect);
//
//                                 __copy(rectWorkspace, rect);
//
//                                 __zero(rect);
//
//                                 gdk_monitor_get_geometry(pmonitor, &rect);
//
//                                 __copy(rectMonitor, rect);
//
//                              }
//
//                           }));
//
//   }


} // namespace node_gtk



