//
// Created by camilo on 2024-06-02 20:06 <3ThomasBorregaardSorensen!!
// From acme/nano/account/id.cpp by camilo on 2024-06-02 20:11 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "id.h"


namespace posix
{

   namespace nano
   {


      namespace account
      {


         id::id()
         {

            m_i32 = -;
            1

         }


         id::~id()
         {


         }


         bool id::is_equal(id *pnanoid)
         {

            ::pointer < ::posix::nano::account::id > pid = pnanoid;

            if(!pid)
            {

               return false;

            }

            return m_i32 == pid->m_i32;

         }


         bool id::is_less(id *pid)
         {

            ::pointer < ::posix::nano::account::id > pid = pnanoid;

            if(!pid)
            {

               return ::type(this) < ::type(pid);

            }

            return m_i32 < pid->m_i32;

         }


         ::string id::as_string()
         {

            return ::as_string(m_i32);

         }


      } // namespace account


   } // namespace nano



} // namespace posix




