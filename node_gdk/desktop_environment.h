//
// Created by camilo on 2022-08-17 22:39 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "aura_posix/x11/desktop_environment.h"


namespace node_gdk
{


   class CLASS_DECL_NODE_GDK desktop_environment :
      virtual public ::windowing_posix::desktop_environment
   {
   public:


   //bool        m_bX11;


   desktop_environment();
   ~desktop_environment() override;


   virtual ::e_status _get_monitor_rectangle(::collection::index iMonitor, ::rectangle_i32 * prectangle);
   virtual ::e_status _get_workspace_rectangle(::collection::index iMonitor, ::rectangle_i32 * prectangle);
//
//
   void get_monitor_rectangle(::collection::index iMonitor, ::rectangle_i32 * prectangle) override;
   void get_workspace_rectangle(::collection::index iMonitor, ::rectangle_i32 * prectangle) override;
//
//
//   void windowing_post(const ::procedure & procedure) override;
//
//
//   bool aaa_message_loop_step() override;
//
//
//   //virtual xcb_connection_t * _get_connection() override;


};


} // namespace node_gtk3



