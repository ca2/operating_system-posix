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
      ~node() override;


      ::e_status install_mouse_hook(::matter * pmatter) override;
      ::e_status install_keyboard_hook(::matter * pmatter) override;

      ::e_status uninstall_mouse_hook(::matter * pmatter) override;
      ::e_status uninstall_keyboard_hook(::matter * pmatter) override;


   };


} // namespace windowing_x11



