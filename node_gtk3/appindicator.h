//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#pragma once


#include "aura_posix/appindicator.h"
#include "acme/handler/command_handler.h"


#if defined(FREEBSD) || defined(__ARCH_LINUX__) || defined(FEDORA_LINUX) || defined(SUSE_LINUX) || defined(OPENBSD) || defined(NETBSD)
#include <libappindicator3-0.1/libappindicator/app-indicator.h>
#else
#include <libayatana-appindicator/app-indicator.h>
#endif


namespace node_gtk3
{


   class appindicator :
      virtual public ::aura_posix::appindicator
   {
   public:


      AppIndicator * m_pindicator;

      appindicator();
      ~appindicator() override;


      bool create(
         const ::scoped_string & scopedstrId,
         const ::scoped_string & scopedstrIcon,
         const ::scoped_string & scopedstrFolder,
         application_menu * papplicationmenu,
         ::command_handler * pcommandhandler) override;


//      gnome_appindicator();
//      virtual ~gnome_appindicator();
//

      //virtual bool create(const_char_pointer pszId, const_char_pointer pszIcon, const_char_pointer pszFolder, user_notify_icon_bridge * pbridge) override;
      virtual bool init(application_menu * papplicationmenu, ::command_handler * pcommandhandler);
      void close() override;


      //virtual bool step() override;


   };


} // namespace node_gtk3



