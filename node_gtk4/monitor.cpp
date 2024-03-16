// created by Camilo 2021-01-31 05:16 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "monitor.h"
#include "display.h"
#include "windowing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "aura/windowing/windowing.h"
//#include <gdk/x11/gdkx11monitor.h>


//::particle * user_synchronization();


namespace node_gtk4
{


   monitor::monitor()
   {


   }


   monitor::~monitor()
   {


   }


   ::windowing_x11::windowing * monitor::x11_windowing() const
   {

      return (::windowing_x11::windowing *) m_pdisplay->m_pwindowing->m_pWindowing4;

   }


   ::windowing_x11::display * monitor::x11_display() const
   {

      return (::windowing_x11::display *) m_pdisplay->m_pDisplay;

   }


   void monitor::update_cache()
   {

      //return ::success_none;

   }

   
   ::u32 monitor::monitor_color_temperature()
   {

      return 0;

   }


   bool monitor::adjust_monitor(::u32 dwTemperature, double dBrightness, double dwGamma)
   {

      return false;

   }


   ::e_status monitor::_get_monitor_rectangle()
   {

      //synchronous_lock sl(user_synchronization());

      GdkDisplay * pdisplay = gdk_display_get_default();

      if (pdisplay == nullptr)
      {

         return ::error_failed;

      }

      GListModel * plistmodel = gdk_display_get_monitors(pdisplay);

      auto n_monitors = g_list_model_get_n_items(plistmodel);

      if (m_iIndex >= n_monitors)
      {

          return ::error_failed;

      }

      auto pmonitor = static_cast<GdkMonitor*>(g_list_model_get_item(plistmodel, m_iIndex));

      if (pmonitor == nullptr)
      {

         return error_failed;

      }

      GdkRectangle  rect;

      gdk_monitor_get_geometry(pmonitor, &rect);

      ::rectangle_i32 rectangle;

      //sleep(15_s);

      copy(m_rectangle, rect);

      return ::success;

   }


//   ::e_status monitor::_get_workspace_rectangle()
//   {
//
//      synchronous_lock sl(user_synchronization());
//
//      ::pointer auto pdisplay = m_pdisplay->
//
////
////      GdkDisplay * pdisplay = gdk_display_get_default();
////
////      if (pdisplay == nullptr)
////      {
////
////         return error_failed;
////
////      }
////
////      GdkMonitor * pmonitor = gdk_display_get_monitor(pdisplay, m_iIndex);
////
////      if (pmonitor == nullptr)
////      {
////
////         return error_failed;
////
////      }
////
////      GdkRectangle rect;
////
////      gdk_monitor_get_workarea(pmonitor, &rect);
////
////      copy(m_rectangleWorkspace, rect);
//
//      return ::success;
//
//   }


   ::rectangle_i32 monitor::monitor_rectangle()
   {

      user_send([this]()
                {
//      //   {
//
//            synchronous_lock sl(user_synchronization());

            _get_monitor_rectangle();

         });

//      node()->send_procedure(predicate);

      return ::windowing::monitor::monitor_rectangle();

   }


//   ::rectangle_i32 monitor::_workspace_rectangle()
//   {
//
//      //auto predicate = [this]()
//        // {
//
//            synchronous_lock sl(user_synchronization());
//
//            _get_workspace_rectangle();
//
//            return m_rectangleWorkspace;
//
//        // };
//
//      //node()->send_procedure(predicate);
//
//      //return ::windowing::monitor::workspace_rectangle();
//
//   }


} // namespace node_gtk4



