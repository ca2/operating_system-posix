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


   void monitor::update_cache()
   {

      //return ::success_none;

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

      //sleep(15_s);

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


   void monitor::get_monitor_rectangle(::RECTANGLE_I32 *prectangle)
   {

      auto pwindowing = x11_windowing();

      auto predicate = [this]() { _get_monitor_rectangle(); };

      pwindowing->windowing_send(predicate);

      ::windowing::monitor::get_monitor_rectangle(prectangle);

   }


   void monitor::get_workspace_rectangle(::RECTANGLE_I32 *prectangle)
   {

      x11_windowing()->windowing_send([this]() { _get_workspace_rectangle(); });

      ::windowing::monitor::get_workspace_rectangle(prectangle);

   }


} // namespace node_gtk



