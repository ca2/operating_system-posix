// created by Camilo 2021-01-31 05:13 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


namespace node_xfce
{


   class CLASS_DECL_AURA monitor :
         virtual public ::windowing::monitor
   {
   public:


      //::collection::index                                               m_iIndex;
      //::int_rectangle                                       m_rectangle;
      //::int_rectangle                                       m_rectangleWorkspace;


      monitor();
      virtual ~monitor();


      ::windowing_x11::windowing * x11_windowing() const {return (::windowing_x11::windowing *) m_pdisplay->m_pwindowing->m_pWindowing; }
      ::windowing_x11::display * x11_display() const {return (::windowing_x11::display *) m_pdisplay->m_pDisplay; }



      virtual ::e_status update_cache();


      virtual unsigned int get_monitor_color_temperature() override;
      virtual bool adjust_monitor( unsigned int dwTemperature, double dBrightness, double dwGamma) override;


      virtual ::e_status get_monitor_rectangle(::int_rectangle * prectangle) override;
      virtual ::e_status get_workspace_rectangle(::int_rectangle * prectangle) override;


      virtual ::e_status _get_monitor_rectangle();
      virtual ::e_status _get_workspace_rectangle();


   };


   //using monitor_map = iptr_map < ::pointer<monitor >>


} // namespace node_xfce



