//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#pragma once


#include "aura_posix/appindicator.h"


namespace node_kde
{


   class appindicator :
      virtual public ::aura_posix::appindicator
   {
   public:


      appindicator();
      ~appindicator() override;


      virtual bool create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge);


   };


} // namespace node_kde



