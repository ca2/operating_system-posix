//
// Created by camilo on 2024-04-19.
//
#include "framework.h"
#include "user.h"
#include "display.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing_base.h"


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

            system()->acme_windowing()->main_send(procedure);

         }


         void user::async(const ::procedure & procedure)
         {

            system()->acme_windowing()->main_post(procedure);

         }

      }//namespace user

   }//namespace nano


} // namespace kde5



