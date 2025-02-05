//
// Created by camilo on 2025-02-04 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "node.h"


#include <unistd.h>
#include <sys/utsname.h>


namespace acme_posix
{


   ::string node::_uname_system()
   {

      struct utsname utsname{};

      if (uname(&utsname))
      {

         return {};

      }

      return utsname.sysname;

   }


   ::string node::_uname_release()
   {

      struct utsname utsname{};

      if (uname(&utsname))
      {

         return {};

      }

      return utsname.release;

   }


   ::string node::_uname_machine()
   {

      struct utsname utsname{};

      if (uname(&utsname))
      {

         return {};

      }

      return utsname.machine;

   }


} // namespace acme_posix



