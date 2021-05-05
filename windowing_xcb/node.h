//
// // Created by camilo on 27/04/2021. 01:02 BRT <33TBS!!
//

//
// Created by camilo on 27/04/2021. 01:02 BRT  <3-<3ThomasBS!!
//
#pragma once


namespace windowing_xcb
{


   class CLASS_DECL_ACME node :
      virtual public ::aura::posix::node
   {
   public:


      node();
      virtual ~node();


      Display * _get_Display();
      xcb_connection_t * _get_connection();


      virtual ::e_status register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard) override;


   };


} // namespace windowing_xcb



