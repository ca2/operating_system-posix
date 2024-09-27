//
// Created by camilo on 2024-04-19.
//
#include "framework.h"
#include "user.h"
#include "display.h"
#include "acme/platform/system.h"
#include "acme/windowing_system/windowing_system.h"


namespace kde5
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

            system()->windowing_system()->main_send(procedure);

         }


         void user::async(const ::procedure & procedure)
         {

            system()->windowing_system()->main_post(procedure);

         }

      }//namespace user

   }//namespace nano


} // namespace kde5



