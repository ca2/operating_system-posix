//
// Created by camilo on 2024-06-02 20:06 <3ThomasBorregaardSorensen!!
// From acme/nano/account/id.h by camilo on 2024-06-02 20:11 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/account/id.h"


namespace posix
{


namespace nano
{


   namespace account
   {


      class id :
         virtual public ::nano::account::id
      {
      public:


         ::i64 m_i;

         id();
         ~id() override;


         bool is_equal(::nano::account::id * pid) override;
         bool is_less(::nano::account::id * pid) override;
         ::string as_string() override;

      };


   } // namespace account


} // namespace nano

