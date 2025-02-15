// Created by camilo on 2024-06-02 16:49 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 18:09 <3ThomasBorregaardSorensen!!
// From nano_dynamic_library_dl on 2024-06-02 18:55 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/nano/account/account.h"


namespace posix
{


   namespace nano
   {


      namespace account
      {


         class CLASS_DECL_ACME account :
           virtual public ::nano::account::account
         {
         public:



            account();
            ~account() override;

            ::pointer<::nano::account::user> _get_user(const ::pointer < ::nano::account::id > & pid) override;

            ::pointer < ::nano::account::id > username_id(const ::scoped_string & scopedstrUsername) override;

            ::pointer < ::nano::account::id > current_user_id() override;


            virtual ::pointer < ::nano::account::id > _create_id(long long i);


         };


      } // dynamic_library


   } // nano


} // namespace dl



