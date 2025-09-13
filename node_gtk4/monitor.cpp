// created by Camilo 2021-01-31 05:16 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "monitor.h"
#include "display.h"
#include "windowing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "aura/windowing/windowing.h"
#include "windowing_gtk4/windowing.h"


//::particle * user_synchronization();


namespace node_gtk4
{


   monitor::monitor()
   {


   }


   monitor::~monitor()
   {


   }


   ::windowing_gtk4::windowing * monitor::gtk4_windowing() const
   {

      return ::system()->acme_windowing()->cast < ::windowing_gtk4::windowing >();

   }


   ::windowing_gtk4::display * monitor::gtk4_display() const
   {

      return m_pdisplay->cast < ::windowing_gtk4::display >();

   }


   void monitor::update_cache()
   {

      //return ::success_none;

   }

   
   unsigned int monitor::monitor_color_temperature()
   {

      return 0;

   }


   bool monitor::adjust_monitor(unsigned int dwTemperature, double dBrightness, double dwGamma)
   {

      return false;

   }


   ::e_status monitor::_get_monitor_rectangle()
   {

      //synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

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

      ::int_rectangle rectangle;

      //sleep(15_s);

      copy(m_rectangle, rect);

      return ::success;

   }


//   ::e_status monitor::_get_workspace_rectangle()
//   {
//
//      synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
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


   ::int_rectangle monitor::monitor_rectangle()
   {

      user_send([this]()
                {
//      //   {
//
//            synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            _get_monitor_rectangle();

         });

//      node()->send_procedure(predicate);

      return ::windowing::monitor::monitor_rectangle();

   }


//   ::int_rectangle monitor::_workspace_rectangle()
//   {
//
//      //auto predicate = [this]()
//        // {
//
//            synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
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



