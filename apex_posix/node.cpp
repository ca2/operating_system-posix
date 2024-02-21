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

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <limits.h>

#if defined(__APPLE__) || defined(FREEBSD)

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

         auto psystem = system();

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

         informationf("Could not create .desktop shortcut file for the Linux papp for the current user.");

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
//         informationf("Could not create .desktop shortcut file for the Linux papp for the current user.");
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
//         informationf("Could not create .desktop shortcut file for the Linux papp for the current user.");
//
//      }
//
//#endif

   }


   void node::create_app_shortcut(::acme::application * papp)
   {
      
#if defined(HAS_FREEDESKTOP)

      auto pathShortcut = app_shortcut_path(papp);

      auto pfile = papp->__create_new< ::freedesktop::desktop_file >();

      pfile->set_file_path(pathShortcut);

      pfile->set_get_file_extension_mime_type(papp->get_get_file_extension_mime_type());

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
      memory_set(&hints, 0, sizeof hints);
      hints.ai_family = AF_UNSPEC; /*either IPV4 or IPV6*/
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = AI_CANONNAME;

      auto gai_result = getaddrinfo(hostname, "http", &hints, &info);

      if (gai_result != 0)
      {


         warningf("getaddrinfo: %s", gai_strerror(gai_result));


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



   bool node::is_alias(const ::file::path & path)
   {

      if (::is_empty(path))
      {

         return false;

      }

      struct stat st;

      if (lstat(path, &st) == -1)
      {

         return false;

      }

      if (S_ISLNK(st.st_mode))
      {

         return true;

      }

      return false;

   }


   ::process_identifier node::current_process_identifier()
   {

      return ::acme_posix::node::current_process_identifier();

   }


   ::file::path node::_get_auto_start_desktop_file_path(const ::string & strAppId)
   {

#if defined(LINUX) || defined(FREEBSD)

      auto pathHome = acmedirectory()->home();

      string strDesktopFileName(strAppId);

      strDesktopFileName.find_replace("/", ".");

      strDesktopFileName += ".desktop";

      ::file::path pathDesktopFile;

      pathDesktopFile = pathHome / ".config/autostart" / strDesktopFileName;

      return pathDesktopFile;

#else

      throw interface_only();

#endif

   }



   void node::register_user_auto_start(const string & strAppId, const ::file::path & pathExecutable, const string & strArguments, bool bRegister)
   {

#if defined(LINUX) || defined(FREEBSD)

      ::file::path pathAutoStartDesktopFilePath = _get_auto_start_desktop_file_path(strAppId);

      if(bRegister)
      {

         auto pfile = __create_new < ::freedesktop::desktop_file >();

         pfile->set_app_id(strAppId);

         pfile->set_file_path(pathAutoStartDesktopFilePath);

         pfile->create();

         pfile->m_straLine._007SetLine("[Desktop Entry]", "X-GNOME-Autostart-enabled", "true");

         pfile->write();

      }
      else
      {

         acmefile()->erase(pathAutoStartDesktopFilePath);

      }

#else

      ::node::register_user_auto_start(strAppId, pathExecutable, strArguments, bRegister);

#endif

   }


   bool node::is_user_auto_start(const string & strAppId)
   {

#if defined(LINUX) || defined(FREEBSD)

      ::file::path pathAutoStartDesktopFilePath = _get_auto_start_desktop_file_path(strAppId);

      return pathAutoStartDesktopFilePath.has_char() && acmefile()->exists(pathAutoStartDesktopFilePath);

#else

      return ::node::is_user_auto_start(strAppId);

#endif

   }



} // namespace apex_posix



