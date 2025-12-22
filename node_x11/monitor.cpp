// created by Camilo 2021-01-31 05:16 BRT <3CamiloSasukeThomasBorregaardSoerensen
#include "framework.h"
#include "monitor.h"
//#include "display.h"
#include "windowing_gtk3/display.h"
#include "windowing_gtk3/windowing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "aura/windowing/display.h"
#include "aura/windowing/windowing.h"
//#include <gdk/x11/gdkx11monitor.h>


//::particle * user_synchronization();


namespace node_x11
{


   monitor::monitor()
   {


   }


   monitor::~monitor()
   {


   }


   ::windowing_gtk3::windowing * monitor::gtk3_windowing() const
   {

      ::cast < ::windowing_gtk3::windowing> pgtk3windowing = ((monitor*)this)->system()->acme_windowing();

      return pgtk3windowing;

   }


   ::windowing_gtk3::display * monitor::gtk3_display() const
   {

      ::cast < ::windowing_gtk3::windowing> pgtk3windowing = ((monitor*)this)->system()->acme_windowing();

      ::cast < ::windowing_gtk3::display> pgtk3display = pgtk3windowing->acme_display();

      return pgtk3display;

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

//      _synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      information() << "::node_gtk3::monitor::_get_monitor_rectangle : " << m_iIndex;

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

      ::int_rectangle rectangle;

      //sleep(15_s);

      copy(m_rectangle, rect);

      information() << "::node_gtk3::monitor::_get_monitor_rectangle : " << m_rectangle;

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

//       user_send([this]()
//                 {
// //      //   {
// //
// //            synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//             _get_monitor_rectangle();
//
//          });

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


} // namespace node_x11



