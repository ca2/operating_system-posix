// created by Camilo 2021-01-31 05:13 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


namespace node_gtk
{


   class CLASS_DECL_AURA monitor :
         virtual public ::windowing::monitor
   {
   public:


      //::index                                               m_iIndex;
      //::rectangle_i32                                       m_rectangle;
      //::rectangle_i32                                       m_rectangleWorkspace;


      monitor();
      ~monitor() override;


      ::windowing_x11::windowing * x11_windowing() const {return (::windowing_x11::windowing *) m_pdisplay->m_pwindowing->m_pWindowing4; }
      ::windowing_x11::display * x11_display() const {return (::windowing_x11::display *) m_pdisplay->m_pDisplay; }


      void update_cache() override;


      virtual ::u32 get_monitor_color_temperature() override;
      virtual bool adjust_monitor( ::u32 dwTemperature, double dBrightness, double dwGamma) override;


      void get_monitor_rectangle(::RECTANGLE_I32 * prectangle) override;
      void get_workspace_rectangle(::RECTANGLE_I32 * prectangle) override;


      virtual ::e_status _get_monitor_rectangle();
      virtual ::e_status _get_workspace_rectangle();


   };


   //using monitor_map = iptr_map < __pointer(monitor) >;


} // namespace node_gtk



