//
// Created by camilo on 2022-08-17 22:39 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "windowing_posix/desktop_environment.h"


namespace node_gtk3
{


   class CLASS_DECL_NODE_GTK3 desktop_environment :
      virtual public ::windowing_posix::desktop_environment
   {
   public:


   //bool        m_bX11;


   desktop_environment();
   ~desktop_environment() override;


      ::pointer < ::graphics::graphics > create_graphics() override;


//    virtual ::e_status _get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle);
//    virtual ::e_status _get_workspace_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle);
// //
// //
//    void get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle) override;
//    void get_workspace_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle) override;
// //
// //
// //   void windowing_post(const ::procedure & procedure) override;
// //
// //
// //   bool aaa_message_loop_step() override;
// //
// //
// //   //virtual xcb_connection_t * _get_connection() override;
//

};


} // namespace node_gtk3



