//
// Created by camilo on 2024-04-19.
//
#include "framework.h"
#include "user.h"
#include "display.h"


namespace x11
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

            ::x11::nano::user::display::get(this)->display_send(procedure);

         }


         void user::async(const ::procedure & procedure)
         {

            ::x11::nano::user::display::get(this)->display_post(procedure);

         }


         bool user::init_threads()
         {

            return XInitThreads();

         }


      }//namespace user


   }//namespace nano


} // namespace x11



