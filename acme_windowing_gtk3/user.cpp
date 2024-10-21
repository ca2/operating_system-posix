//
// Created by camilo on 2024-04-19.
//
#include "framework.h"
#include "user.h"
#include "display.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing_base.h"


namespace gtk3
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

            system()->acme_windowing()->user_send(procedure);

         }


         void user::async(const ::procedure & procedure)
         {

            system()->acme_windowing()->user_post(procedure);

         }


         bool user::init_threads()
         {

            //return XInitThreads();
            return true;

         }


      }//namespace user


   }//namespace nano


} // namespace gtk3



