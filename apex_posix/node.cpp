//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/system.h"
#if defined(HAS_FREEDESKTOP)
#include "apex/operating_system/freedesktop/desktop_file.h"
#endif
#include "acme/filesystem/filesystem/acme_directory.h"
#include "apex/platform/application.h"


#include "acme/_operating_system.h"


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <limits.h>

#if defined(__APPLE__)

#define HOST_NAME_MAX 64

#endif

#endif


void os_post_quit();


void apex_application_run(const char * pszAppName, const char * pszProgName);


namespace apex_posix
{


   node::node()
   {

      m_pApexPosix = this;

   }


   node::~node()
   {

   }


   void node::on_start_application(::apex::application *papplication)
   {

#if !defined(RASPBERRYPIOS) && !defined(ANDROID) && !defined(__APPLE__) && !defined(LINUX)

      try
      {

         auto psystem = acmesystem();

         auto pnode = psystem->node()->m_papexnode;

         auto papp = papplication;

         ::file::path path = pnode->get_desktop_file_path(papp);

         if(path.has_char() && !acmefile()->exists(path))
         {

            auto pfile = papp->__create_new< ::freedesktop::desktop_file >();

            pfile->set_app_id(papp->m_strAppId);

            pfile->set_file_path(path);

            pfile->create();

            pfile->write();

         }

      }
      catch(...)
      {

         information("Could not create .desktop shortcut file for the Linux papp for the current user.");

      }

#endif

   }


   bool node::shell_link_target(::file::path &pathTarget, const ::file::path &pathLnk)
   {
      
#if defined(HAS_FREEDESKTOP)

      if(pathLnk.case_insensitive_ends(".desktop"))
      {


         //if(path.has_char() && !acmefile()->exists(path))
         {

            auto pfile = __create_new< ::freedesktop::desktop_file >();

            //pfile->set_app_id(papp->m_strAppId);

            pfile->open(pathLnk);

            pathTarget = pfile->get_Target();

            ///pfile->write();

         }

         return true;

      }
      
#endif // HAS_FREEDESKTOP

      return false;

//      catch(...)
//      {
//
//         information("Could not create .desktop shortcut file for the Linux papp for the current user.");
//
//      }

//#endif

   }


   bool node::shell_link_icon(::file::path& pathIcon, int& iIcon, const ::file::path& pathLnk)
   {
      
#if defined(HAS_FREEDESKTOP)

      if(pathLnk.case_insensitive_ends(".desktop"))
      {


         //if(path.has_char() && !acmefile()->exists(path))
         {

            auto pfile = __create_new< ::freedesktop::desktop_file >();

            pfile->open(pathLnk);

            pathIcon = pfile->get_Icon();

            iIcon = 0;

         }
         
         return true;

      }

#endif // HAS_FREEDESKTOP


      return false;

//      catch(...)
//      {
//
//         information("Could not create .desktop shortcut file for the Linux papp for the current user.");
//
//      }
//
//#endif

   }


   void node::create_app_shortcut(::acme::application * papp)
   {
      
#if defined(HAS_FREEDESKTOP)

      ::string strDesktopFileName;

      strDesktopFileName = papp->m_strAppId;

      strDesktopFileName.find_replace("/", ".");

      auto pathShortcut = acmedirectory()->home() / ".local/share/applications"/ (strDesktopFileName +".desktop");

      auto pfile = papp->__create_new< ::freedesktop::desktop_file >();

      pfile->set_file_path(pathShortcut);

      pfile->create();

      pfile->write();
      
#endif

   }


   ::string node::get_host_name()
   {

      //https://stackoverflow.com/questions/27914311/get-computer-name-and-logged-user-name
      //https://stackoverflow.com/users/1155235/pezy
      //char hostname[HOST_NAME_MAX];
      //char username[LOGIN_NAME_MAX];
      //gethostname(hostname, HOST_NAME_MAX);
      //getlogin_r(username, LOGIN_NAME_MAX);

      //return hostname;

      ::string strHostname;

      struct addrinfo hints, *info, *p;

      char hostname[HOST_NAME_MAX + 1];
      hostname[HOST_NAME_MAX ] = '\0';
      gethostname(hostname, HOST_NAME_MAX);

      strHostname = hostname;

      //https://stackoverflow.com/questions/504810/how-do-i-find-the-current-machines-full-hostname-in-c-hostname-and-domain-info
      //https://stackoverflow.com/users/4924/zxaos
      memset(&hints, 0, sizeof hints);
      hints.ai_family = AF_UNSPEC; /*either IPV4 or IPV6*/
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_CANONNAME;

      auto gai_result = getaddrinfo(hostname, "http", &hints, &info);

      if (gai_result != 0)
      {


         warning("getaddrinfo: %s", gai_strerror(gai_result));


      }
      else
      {

         for (p = info; p != NULL; p = p->ai_next)
         {
            ::string strCanonicalName = p->ai_canonname;

            if(strCanonicalName.length() > strHostname.length())
            {

               strHostname = strCanonicalName;

            }
            //printf("hostname: %s\n", p->ai_canonname);
         }

         freeaddrinfo(info);

      }
//      else
//      {
//
//
//         //exit(1);
//      }

//   }

      return strHostname;


   }


} // namespace apex_posix



