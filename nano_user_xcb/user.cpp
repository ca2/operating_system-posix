//
// Created by camilo on 2024-04-19.
//
#include "framework.h"
#include "user.h"
#include "display.h"


namespace xcb
{


   namespace nano
   {


      namespace user
      {


         user::user()
         {


         }


         user::~user()
         {


         }


         void user::sync(const ::procedure & procedure)
         {

            ::xcb::nano::windowing::display::get(this)->display_send(procedure);

         }


         void user::async(const ::procedure & procedure)
         {

            ::xcb::nano::windowing::display::get(this)->display_post(procedure);

         }

      }//namespace user

   }//namespace nano


} // namespace x11



