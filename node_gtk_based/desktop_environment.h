//
// Created by camilo on 2022-08-17 22:52 <3ThomasBorregaardSorensen!!
//
#pragma once



#if defined(HAS_GTK4)
#include "node_gtk4/desktop_environment.h"
#elif defined(HAS_GTK3)
#include "node_gtk3/desktop_environment.h"
#endif


namespace node_gtk_based
{


   class CLASS_DECL_NODE_GTK_BASED desktop_environment :
#if defined(HAS_GTK4)
           virtual public ::node_gtk4::desktop_environment
#elif defined(HAS_GTK3)
      virtual public ::node_gtk3::desktop_environment
#endif
   {
      public:


   //bool        m_bX11;


   desktop_environment();
   ~desktop_environment() override;


//   virtual ::e_status _get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle);
//   virtual ::e_status _get_workspace_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle);
//
//
//   void get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle) override;
//   void get_workspace_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle) override;
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


} // namespace node_gnomes



