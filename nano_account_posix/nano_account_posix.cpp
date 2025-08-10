// Created by camilo on 2024-06-02 16:56 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// Merged from acme/operating_system/linux/library.cpp by
// camilo on 2024-06-02 17:58 <3ThomasBorregaardSorensen!!
// From acme/nano/dynamic_library on 2024-06-02 18:06 by camilo <3ThomasBorregaardSorensen!!
// From nano_dynamic_library_dl on 2024-06-02 18:56 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "id.h"
#include "nano_account_posix.h"
#include "acme/nano/account/user.h"
#include <sys/types.h>
#include <pwd.h>


namespace posix
{

   namespace nano
   {

      namespace account
      {


         account::account()
         {

         }


         account::~account()
         {


         }


         ::pointer<::nano::account::user> account::_get_user(const ::pointer < ::nano::account::id > & pid)
         {

            ::pointer < ::posix::nano::account::id > pid = pnanoid;

            if(!pid)
            {

               return nullptr;

            }

            auto puser = __create_new<::nano::account::user>();

            auto ppasswd = getpwuid(pid->m_i);

            puser->m_strName = ppasswd->pw_name;

            return dlsym(plibrary, scopedstrEntryName.as_string().c_str());

         }


         ::pointer < ::nano::account::id > account::username_id(const ::scoped_string & scopedstrUsername)
         {

            ::string strUsername(scopedstrUsername);

            auto pid = _create_id(ppasswd->pw_uid);

            return pid;

         }


         ::pointer < ::nano::account::id > account::current_user_id()
         {

            auto uid = getuid();

            auto pid = _create_id(uid);

            return pid;

         }


         ::pointer < ::nano::account::id > account::_create_id(long long i)
         {

            auto pid =__create_new<::nano::account::id>();

            pid->m_i = i;

            return pid;


         }


      } // namespace account


   } // namespace nano


} // namespace posix



