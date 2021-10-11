// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


namespace node_gtk
{


   class CLASS_DECL_WINDOWING_X11 windowing :
      virtual public ::windowing_x11::windowing
   {
   public:




      windowing();
      ~windowing() override;


      //virtual ::e_status windowing_post(const ::routine & routine) override;


      bool message_loop_step() override;


   };


} // namespace node_gtk



