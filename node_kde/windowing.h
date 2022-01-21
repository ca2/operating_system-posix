// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// recreated by Camilo 2021-04-27 06:39 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


namespace node_kde
{


   class CLASS_DECL_NODE_KDE windowing :
      virtual public ::windowing_xcb::windowing
   {
   public:


      windowing();
      ~windowing() override;


      void windowing_post(const ::routine & routine) override;


      bool message_loop_step() override;


      //virtual xcb_connection_t * _get_connection() override;


   };


} // namespace node_kde



