// From node_gtk/windowing by camilo on 2023-02-23 05:05 BRT <3ThomasBorregaardSOrensen!!
#pragma once


#include "node_gtk/windowing.h"


namespace node_lxq2
{


   class CLASS_DECL_WINDOWING_X11 windowing :
      virtual public ::node_gtk::windowing
   {
   public:




      windowing();
      ~windowing() override;


      //virtual ::e_status windowing_post(const ::procedure & procedure) override;


      //virtual bool aaa_message_loop_step() override;


   };


} // namespace node_lxq2



