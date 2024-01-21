#include "framework.h"
#include "os_context.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/node.h"
#include "apex/operating_system/freedesktop/desktop_file.h"
#include <sys/stat.h>
#include <unistd.h>


namespace apex_posix
{


   os_context::os_context()
   {


   }


   os_context::~os_context()
   {


   }


   bool os_context::is_alias(const ::file::path & path)
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


   ::process_identifier os_context::current_process_identifier()
   {

      return acmenode()->current_process_identifier();

   }


   ::file::path os_context::_get_auto_start_desktop_file_path(const ::string & strAppId)
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

      throw interface_only_exception();

#endif

   }



   void os_context::register_user_auto_start(const string & strAppId, const ::file::path & pathExecutable, const string & strArguments, bool bRegister)
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

      ::os_context::register_user_auto_start(strAppId, pathExecutable);

#endif

   }


   bool os_context::is_user_auto_start(const string & strAppId)
   {

#if defined(LINUX) || defined(FREEBSD)

      ::file::path pathAutoStartDesktopFilePath = _get_auto_start_desktop_file_path(strAppId);

      return pathAutoStartDesktopFilePath.has_char() && acmefile()->exists(pathAutoStartDesktopFilePath);

#endif

   }



} // namespace apex_posix




