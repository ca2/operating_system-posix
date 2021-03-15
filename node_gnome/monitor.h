// created by Camilo 2021-01-31 05:13 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


namespace node_gnome
{


   class CLASS_DECL_AURA monitor :
         virtual public ::windowing::monitor
   {
   public:


      //::index                                               m_iIndex;
      //::rectangle_i32                                       m_rectangle;
      //::rectangle_i32                                       m_rectangleWorkspace;


      monitor();
      virtual ~monitor();


      virtual ::e_status update_cache();

      virtual ::u32 get_monitor_color_temperature() override;
      virtual bool adjust_monitor( ::u32 dwTemperature, double dBrightness, double dwGamma) override;

      virtual bool get_monitor_rectangle(::RECTANGLE_I32 * prectangle) override;
      virtual bool get_workspace_rectangle(::RECTANGLE_I32 * prectangle) override;


   };


   //using monitor_map = iptr_map < __pointer(monitor) >;


} // namespace node_gnome



