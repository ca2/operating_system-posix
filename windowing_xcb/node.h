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
      ~node() override;


      Display * _get_Display();
      xcb_connection_t * _get_connection();


      void install_mouse_hook(::matter * pmatterListener) override;
      void install_keyboard_hook(::matter * pmatterListener) override;

      void uninstall_mouse_hook(::matter * pmatterListener) override;
      void uninstall_keyboard_hook(::matter * pmatterListener) override;


   };


} // namespace windowing_xcb



