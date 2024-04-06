//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#pragma once


#include "aura_posix/appindicator.h"


namespace node_kde5
{


   class appindicator :
      virtual public ::aura_posix::appindicator
   {
   public:


      appindicator();
      ~appindicator() override;


      bool create(const char * pszId, const char * pszIcon, const char * pszFolder, application_menu * papplicationmenu, application_menu_callback * pcallback) override;


   };


} // namespace node_kde5



