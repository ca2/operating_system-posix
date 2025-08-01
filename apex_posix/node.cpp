//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/system.h"
#include "acme/exception/interface_only.h"
#if defined(HAS_FREEDESKTOP)
#include "apex/operating_system/freedesktop/desktop_file.h"
#endif
#include "acme/filesystem/filesystem/directory_system.h"
#include "apex/platform/application.h"


#include "acme/_operating_system.h"


#if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__) || defined(__BSD__)

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <limits.h>

#if defined(__APPLE__) || defined(FREEBSD) || defined(NETBSD)

#define HOST_NAME_MAX 64

#endif

#endif


void os_post_quit();


void apex_application_run(const_char_pointer  pszAppName, const_char_pointer  pszProgName);


namespace apex_posix
{


   node::node()
   {

      //m_pApexPosix = this;

   }


   node::~node()
   {

   }


   void node::on_start_application(::apex::application *papplication)
   {

#if !defined(RASPBERRYPIOS) && !defined(__ANDROID__) && !defined(__APPLE__) && !defined(LINUX)

      try
      {

         auto psystem = system();

         auto pnode = psystem->node();

         auto papp = papplication;

         ::file::path path = pnode->get_desktop_file_path(papp);

         if(path.has_character() && !file_system()->exists(path))
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


         //if(path.has_character() && !file_system()->exists(path))
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


         //if(path.has_character() && !file_system()->exists(path))
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


   void node::create_app_shortcut(::platform::application * papp)
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


   ::file::path node::_get_auto_start_desktop_file_path(const ::scoped_string & scopedstrAppId)
   {

#if defined(LINUX) || defined(__BSD__)

      auto pathHome = directory_system()->home();

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



   void node::register_user_auto_start(::platform::application * papplication, const ::scoped_string & scopedstrArguments, bool bRegister)
   {

#if defined(LINUX) || defined(__BSD__)

      ::file::path pathAutoStartDesktopFilePath = _get_auto_start_desktop_file_path(papplication->m_strAppId);

      if(bRegister)
      {

         informationf("register_user_auto_start true : %s", pathAutoStartDesktopFilePath.c_str());

         auto pfile = papplication->__create_new < ::freedesktop::desktop_file >();

         pfile->set_app_id(papplication->m_strAppId);

         pfile->set_file_path(pathAutoStartDesktopFilePath);

         pfile->create();

         pfile->m_straLine._007SetLine("[Desktop Entry]", "X-GNOME-Autostart-enabled", "true");

         pfile->write();

         informationf("register_user_auto_start wrote file : %s", pathAutoStartDesktopFilePath.c_str());

         informationf("register_user_auto_start end");

      }
      else
      {

         file_system()->erase(pathAutoStartDesktopFilePath);

      }

#else

      ::acme_posix::node::register_user_auto_start(papplication, strArguments, bRegister);

#endif

   }


   bool node::is_user_auto_start(const ::scoped_string & scopedstrAppId)
   {

#if defined(LINUX) || defined(__BSD__)

//#error "error that is good if occurs temporarily (for testing if this portion of code is included in compilation)"

      ::file::path pathAutoStartDesktopFilePath = _get_auto_start_desktop_file_path(strAppId);

      return pathAutoStartDesktopFilePath.has_character() && file_system()->exists(pathAutoStartDesktopFilePath);

#else

      return ::acme_posix::node::is_user_auto_start(strAppId);

#endif

   }


   void node::defer_innate_ui()
   {

      apex::node::defer_innate_ui();

   }


} // namespace apex_posix



