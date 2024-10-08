// created by Camilo 2021-01-31 05:13 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


#include "aura/windowing/monitor.h"


namespace node_gtk4
{


   class CLASS_DECL_AURA monitor :
         virtual public ::windowing::monitor
   {
   public:


      //::collection::index                                               m_iIndex;
      //::rectangle_i32                                       m_rectangle;
      //::rectangle_i32                                       m_rectangleWorkspace;


      monitor();
      ~monitor() override;


      ::windowing_gtk4::windowing * gtk4_windowing() const;
      ::windowing_gtk4::display * gtk4_display() const;


      void update_cache() override;


      virtual ::u32 monitor_color_temperature() override;
      virtual bool adjust_monitor( ::u32 dwTemperature, double dBrightness, double dwGamma) override;


      ::rectangle_i32 monitor_rectangle() override;
      //::rectangle_i32 _workspace_rectangle() override;


      virtual ::e_status _get_monitor_rectangle();
      //virtual ::e_status _get_workspace_rectangle();


   };


   //using monitor_map = iptr_map < ::pointer<monitor >>


} // namespace node_gtk4



