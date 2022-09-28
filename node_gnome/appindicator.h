//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#pragma once


#include "aura_posix/appindicator.h"


namespace node_gnome
{


   class appindicator :
      virtual public ::aura_posix::appindicator
   {
   public:


      AppIndicator * m_pindicator;

      appindicator();
      ~appindicator() override;


      bool create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge) override;




//      gnome_appindicator();
//      virtual ~gnome_appindicator();
//

      //virtual bool create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge) override;
      virtual bool init(user_notify_icon_bridge * pbridge);
      void close() override;


      //virtual bool step() override;


   };


} // namespace node_gnome



