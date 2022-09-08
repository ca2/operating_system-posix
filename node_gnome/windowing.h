// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "node_gtk/windowing.h"


namespace node_gnome
{


   class CLASS_DECL_WINDOWING_X11 windowing :
      virtual public ::node_gtk::windowing
   {
   public:




      windowing();
      virtual ~windowing();


      //virtual ::e_status windowing_post(const ::procedure & procedure) override;


      virtual bool message_loop_step() override;


   };


} // namespace node_gnome



