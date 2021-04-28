//
// // Created by camilo on 26/04/2021. 13:10 BRT <33TBS!!
//

//
// Created by camilo on 26/04/2021. 13:10 BRT  <3-<3ThomasBS!!
//
#pragma once


namespace windowing_x11
{


   class CLASS_DECL_ACME node :
      virtual public ::aura::posix::node
   {
   public:



      node();
      virtual ~node();


      virtual ::e_status register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard) override;


   };


} // namespace windowing_x11



