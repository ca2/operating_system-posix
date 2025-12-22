//
// Created by camilo on 2024-10-03 04:33 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window_base_handle.h"


namespace x11
{


   namespace nano
   {


      namespace user
      {


         window_base_handle::window_base_handle()
         {


         }


         window_base_handle::~window_base_handle()
         {



         }


         ::x11::handle_t window_base_handle::_x11_handle()
         {

            return {nullptr, 0, nullptr};

         }


      } // user


   } // nano


} // x11



