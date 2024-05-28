//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#pragma once


#include "aura_posix/appindicator.h"
#include "acme/platform/application_menu_callback.h"


namespace node_gtk3
{


   class appindicator :
      virtual public ::aura_posix::appindicator
   {
   public:


      AppIndicator * m_pindicator;

      appindicator();
      ~appindicator() override;


      bool create(const char * pszId, const char * pszIcon, const char * pszFolder, application_menu * papplicationmenu, application_menu_callback * pcallback) override;




//      gnome_appindicator();
//      virtual ~gnome_appindicator();
//

      //virtual bool create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge) override;
      virtual bool init(application_menu * papplicationmenu, application_menu_callback * pcallback);
      void close() override;


      //virtual bool step() override;


   };


} // namespace node_gtk3



