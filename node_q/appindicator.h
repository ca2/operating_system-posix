//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#pragma once


#include "aura_posix/appindicator.h"


namespace node_lxq2
{


   class appindicator :
      virtual public ::aura_posix::appindicator
   {
   public:


      appindicator();
      ~appindicator() override;


      bool create(
          const ::scoped_string & scopedstrId,
          const ::scoped_string & scopedstrIcon,
          const ::scoped_string & scopedstrFolder,
          application_menu * papplicationmenu,
          command_handler * pcommandhandler) override;


   };


} // namespace node_lxq2



