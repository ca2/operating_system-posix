// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


namespace node_kde
{


   class CLASS_DECL_WINDOWING_KDE windowing :
      virtual public ::windowing_xcb::windowing
   {
   public:




      windowing();
      virtual ~windowing();


      virtual ::e_status user_fork(const ::promise::routine & routine) override;


      virtual bool message_loop_step() override;


   };


} // namespace node_kde



