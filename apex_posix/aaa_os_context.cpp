#include "framework.h"
#include "os_context.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
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

      return node()->current_process_identifier();

   }


   ::file::path os_context::_get_auto_start_desktop_file_path(const ::scoped_string & scopedstrAppId)
   {

#if defined(LINUX) || defined(FREEBSD)

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



   void os_context::register_user_auto_start(const ::scoped_string & scopedstrAppId, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bRegister)
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

         file_system()->erase(pathAutoStartDesktopFilePath);

      }

#else

      ::os_context::register_user_auto_start(strAppId, pathExecutable, strArguments, bRegister);

#endif

   }


   bool os_context::is_user_auto_start(const ::scoped_string & scopedstrAppId)
   {

#if defined(LINUX) || defined(FREEBSD)

      ::file::path pathAutoStartDesktopFilePath = _get_auto_start_desktop_file_path(strAppId);

      return pathAutoStartDesktopFilePath.has_character() && file_system()->exists(pathAutoStartDesktopFilePath);
      
#else
      
      return ::os_context::is_user_auto_start(strAppId);

#endif

   }



} // namespace apex_posix




