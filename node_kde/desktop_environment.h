// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// recreated by Camilo 2021-04-27 06:39 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "aura_posix/x11/desktop_environment.h"


namespace node_kde
{


   class CLASS_DECL_NODE_KDE desktop_environment :
      virtual public ::windowing_posix::desktop_environment
   {
   public:


      bool        m_bX11;


      desktop_environment();
      ~desktop_environment() override;


      virtual ::e_status _get_monitor_rectangle(::index iMonitor, ::RECTANGLE_I32 * prectangle);
      virtual ::e_status _get_workspace_rectangle(::index iMonitor, ::RECTANGLE_I32 * prectangle);


      void get_monitor_rectangle(::index iMonitor, ::RECTANGLE_I32 * prectangle) override;
      void get_workspace_rectangle(::index iMonitor, ::RECTANGLE_I32 * prectangle) override;


      void windowing_post(const ::procedure & procedure) override;


      bool message_loop_step() override;


      //virtual xcb_connection_t * _get_connection() override;


   };


} // namespace node_kde



