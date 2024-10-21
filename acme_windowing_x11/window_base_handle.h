//
// Created by camilo on 2024-10-03 04:29 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace x11
{


   namespace nano
   {


      namespace user
      {


         class CLASS_DECL_NANO_USER_X11 window_base_handle :
            virtual public ::particle
         {
         public:


            window_base_handle();
            ~window_base_handle() override;


            virtual ::x11::handle_t _x11_handle();


         };


      } // user


   } // nano


} // x11



