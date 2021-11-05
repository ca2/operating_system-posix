// From acme/filesystem/file/dir.cpp by camilo 
// on 2021-08-09 03:19 BRT
// <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "acme/operating_system.h"


#if defined(WINDOWS_DESKTOP)
#include <Shlobj.h>
#include <shellapi.h>
#elif defined(__APPLE__)
#include <sys/stat.h>
#include <dirent.h>
#elif defined(LINUX)
#include <dlfcn.h>
#include <link.h>
#include <sys/stat.h>
#include <dirent.h>
#elif defined(ANDROID)
#include <sys/stat.h>
#include <dirent.h>
#elif defined(_UWP)
#include "acme/os/universal_windows/file_winrt.h"
#endif

namespace posix
{


   void TranslateLastError()
   {

      if (errno == EEXIST)
      {

         set_last_status(error_already_exists);

      }
      else
      {

         set_last_status(::success);

      }

   }


   acme_dir::acme_dir()
   {


   }


   acme_dir::~acme_dir()
   {


   }


   ::e_status acme_dir::create(const char * path)
   {


      return _create(path);

      //}

      //return ::file::system_dir::g_pthis->mk(path, ::get_context_system());

   }


   ::e_status acme_dir::_create(const char * path)
   {

      return ::create_directory_path(path);

   }


   ::e_status acme_dir::create_directory(const char * path)
   {

      return ::create_directory(path);

   }


   ::file::path acme_dir::module()
   {

      ::file::path pathModule (m_pacmefile->executable());

      return pathModule.folder();

   }


   bool acme_dir::is(const char * path)
   {

      return _is(path);

   }


   void acme_dir::rls(::file::patha & stra, const char * psz)
   {

      ::count start = stra.get_count();

      ls(stra, psz);

      ::count end = stra.get_count();

      for (::index i = start; i < end; i++)
      {

         if (is(stra[i]))
         {

            rls(stra, stra[i]);

         }

      }

   }


   void acme_dir::rls_dir(::file::patha & stra, const char * psz)
   {

      ::count start = stra.get_count();

      ls_dir(stra, psz);

      ::count end = stra.get_count();

      for (::index i = start; i < end; i++)
      {

         ::file::path path = stra[i];

         rls_dir(stra, path);

      }

   }


   void acme_dir::ls(::file::patha & stra, const char * psz)
   {

      DIR * dirp = opendir(psz);

      if (dirp == nullptr)
         return;

      dirent * dp;
      ::file::path path;
      while ((dp = readdir(dirp)) != nullptr)
      {

         if (strcmp(dp->d_name, "..") == 0)
            continue;
         else if (strcmp(dp->d_name, ".") == 0)
            continue;
         path = ::file::path(psz) / dp->d_name;
         path.m_iDir = dp->d_type & DT_DIR ? 1 : 0;
         path.m_iSize = -1;
         stra.add(path);

         //output_debug_string("flood for you: dir::ls ----> " + path);

      }

      closedir(dirp);

   }


   void acme_dir::ls_dir(::file::patha & stra, const char * psz)
   {

      DIR * dirp = opendir(psz);

      if (dirp == nullptr)
         return;

      dirent * dp;

      while ((dp = readdir(dirp)) != nullptr)
      {
         if (dp->d_name[0] == '.')
         {
            if (dp->d_name[1] == '\0')
               continue;
            if (dp->d_name[1] == '.')
            {
               if (dp->d_name[2] == '\0')
                  continue;
            }
         }

         ::file::path strPath = ::file::path(psz) / dp->d_name;

         if (is(strPath))
         {

            stra.add(strPath);

         }

      }

      closedir(dirp);


   }


   void acme_dir::ls_file(::file::patha & stra, const char * psz)
   {

      DIR * dirp = opendir(psz);

      if (dirp == nullptr)
         return;

      dirent * dp;

      while ((dp = readdir(dirp)) != nullptr)
      {
         if (dp->d_name[0] == '.')
         {
            if (dp->d_name[1] == '\0')
               continue;
            if (dp->d_name[1] == '.')
            {
               if (dp->d_name[2] == '\0')
                  continue;
            }
         }
         ::file::path strPath = ::file::path(psz) / dp->d_name;
         if (!is(strPath))
         {
            stra.add(strPath);
         }

      }

      closedir(dirp);

   }


   ::file::path acme_dir::pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode)
   {

      string_array stra;

      stra.add_tokens(pszEnv, ":");

      string strCandidate;

      for (i32 i = 0; i < stra.get_count(); i++)
      {

         if (stra[i].is_empty())
            continue;

         strCandidate = ::file::path(stra[i]) / pszTopic;

         if (m_pacmefile->exists(strCandidate))
         {

            return strCandidate;

         }

      }

      return "";

   }



   ::file::path acme_dir::archive()
   {


      return home() / "archive";

   }


//   int acme_dir::make_path(const char * psz)
//   {
//
//      return create(psz) != false;
//
//   }


   bool acme_dir::_is(const char * path)
   {

      return ::is_directory(path);

   }


} // namespace posix



