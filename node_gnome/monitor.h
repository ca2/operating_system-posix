// created by Camilo 2021-01-31 05:13 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


#include "node_gtk/monitor.h"


namespace node_gnome
{


   class CLASS_DECL_AURA monitor :
         virtual public ::node_gtk::monitor
   {
   public:


      //::index                                               m_iIndex;
      //::rectangle_i32                                       m_rectangle;
      //::rectangle_i32                                       m_rectangleWorkspace;


      monitor();
      ~monitor() override;


      //::windowing_x11::windowing * x11_windowing() const {return (::windowing_x11::windowing *) m_pdisplay->m_pwindowing->m_pWindowing; }
      //::windowing_x11::display * x11_display() const {return (::windowing_x11::display *) m_pdisplay->m_pDisplay; }



      void update_cache() override;


      ::u32 get_monitor_color_temperature() override;
      bool adjust_monitor( ::u32 dwTemperature, double dBrightness, double dwGamma) override;


//      virtual ::e_status get_monitor_rectangle(::RECTANGLE_I32 * prectangle) override;
//      virtual ::e_status get_workspace_rectangle(::RECTANGLE_I32 * prectangle) override;
//
//
//      virtual ::e_status _get_monitor_rectangle();
//      virtual ::e_status _get_workspace_rectangle();


   };


   //using monitor_map = iptr_map < ::pointer<monitor >>


} // namespace node_gnome



