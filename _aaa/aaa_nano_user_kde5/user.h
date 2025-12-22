//
// Created by camilo on 2024-04-19 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/micro/user.h"


namespace kde5
{


   namespace nano
   {


      namespace user
      {


         class CLASS_DECL_NANO_USER_KDE5 user :
            virtual public ::micro::user
         {
         public:


            user();
            ~user();


            void sync(const ::procedure & procedure) override;
            void async(const ::procedure & procedure) override;


         };


      } // namespace user


   } // namespace nano


} // namespace kde5



