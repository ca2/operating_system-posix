//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#pragma once


#include "aura_posix/appindicator.h"


namespace node_kde6
{


   class appindicator :
      virtual public ::aura_posix::appindicator
   {
   public:


      appindicator();
      ~appindicator() override;


      virtual bool create(const_char_pointer  pszId, const_char_pointer  pszIcon, const_char_pointer  pszFolder, application_menu * papplicationmenu, ::command_handler * pcallback);


   };


} // namespace node_kde6



