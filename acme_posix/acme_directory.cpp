// From acme/filesystem/file/dir.cpp by camilo 
// on 2021-08-09 03:19 BRT
// <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme_directory.h"
#include "acme_file.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/_operating_system.h"


#include <ftw.h>

#if defined(__APPLE__) || defined(ANDROID)

char * get_current_dir_name();

#endif


#if defined(WINDOWS_DESKTOP)
#include <Shlobj.h>
#include <shellapi.h>
#elif defined(__APPLE__)
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#elif defined(LINUX) || defined(RASPBERRYPIOS)
#include <dlfcn.h>
#include <link.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#elif defined(ANDROID)
#include <sys/stat.h>
#include <dirent.h>
#elif defined(UNIVERSAL_WINDOWS)
#include "acme/os/universal_windows/file_winrt.h"
#elif defined(FREEBSD) || defined(OPENBSD)
#define _GNU_SOURCE
#define __BSD_VISIBLE 1
#include <dlfcn.h>
#include <link.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
char * get_current_dir_name();
#endif


#include <pwd.h>


namespace acme_posix
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


   acme_directory::acme_directory()
   {


   }


   acme_directory::~acme_directory()
   {


   }

   //
   //   ::e_status acme_directory::create(const char * path)
   //   {
   //
   //
   //      return _create(path);
   //
   //      //}
   //
   //      //return ::file::system_dir::g_pthis->mk(path, ::get_context_system());
   //
   //   }
   //
   //
   //   ::e_status acme_directory::_create(const char * path)
   //   {
   //
   //      return ::create_directory_path(path);
   //
   //   }
   //
   //
   //   ::e_status acme_directory::create_directory(const char * path)
   //   {
   //
   //      return ::create_directory(path);
   //
   //   }


   ::file::path acme_directory::module()
   {

      ::file::path pathModule(m_pacmefile->module());

      return pathModule.folder();

   }


   bool acme_directory::is(const ::file::path & path)
   {

      bool bDir = false;

      if(!_is(bDir, path))
      {

         return false;

      }

      return bDir;

   }


   //   void acme_directory::rls(::file::path_array & stra, const char * psz)
   //   {
   //
   //      ::count start = stra.get_count();
   //
   //      ls(stra, psz);
   //
   //      ::count end = stra.get_count();
   //
   //      for (::index i = start; i < end; i++)
   //      {
   //
   //         if (is(stra[i]))
   //         {
   //
   //            rls(stra, stra[i]);
   //
   //         }
   //
   //      }
   //
   //   }


   //   void acme_directory::rls_dir(::file::path_array & stra, const char * psz)
   //   {
   //
   //      ::count start = stra.get_count();
   //
   //      ls_dir(stra, psz);
   //
   //      ::count end = stra.get_count();
   //
   //      for (::index i = start; i < end; i++)
   //      {
   //
   //         ::file::path path = stra[i];
   //
   //         rls_dir(stra, path);
   //
   //      }
   //
   //   }


   void defer_add(::file::listing& listing, const dirent* dp)
   {

      if (file_path_is_dots(dp->d_name))
      {

         return;

      }


      ::file::path path;

      string strFilename(dp->d_name);

      //const char * psz = dp->d_name;

      path = listing.m_pathFinal / strFilename;

      if (path.begins(listing.m_pathBasePath))
      {

         path.m_iBasePathLength = listing.m_pathBasePath.length() + 1;

      }

      if(dp->d_type & DT_DIR)
      {

         path.set_folder_path();

      }
      else
      {

         path.set_file_path();

      }

      //path.m_iSize = make64_from32(finddata.nFileSizeLow, finddata.nFileSizeHigh);

      listing.defer_add(path);

   }


static int rmFiles(const char *pathname, const struct stat *sbuf, int type, struct FTW *ftwb)
{
    if(remove(pathname) < 0)
    {
       return -1;
    }
    return 0;
}


void acme_directory::erase_recursively(const ::file::path &path)
{


    // Delete the directory and its contents by traversing the tree in reverse order, without crossing mount boundaries and symbolic links

    if (nftw(path.c_str(), rmFiles,10, FTW_DEPTH|FTW_MOUNT|FTW_PHYS) < 0)
    {
        //perror("ERROR: ntfw");
       //exit(1);
       throw ::exception(error_failed, "failed to erase");
    }
}

   bool acme_directory::enumerate(::file::listing& listing)
   {

      if (listing.m_pathFinal.is_empty())
      {

         listing.m_pathFinal = listing.m_pathUser;

      }

      if (listing.m_pathBasePath.is_empty())
      {

         listing.m_pathBasePath = listing.m_pathFinal;

      }

      if (!is(listing.m_pathFinal))
      {

         return false;

      }

      if (!listing.on_start_enumerating(this))
      {

         return true;

      }

      DIR* dirp = opendir(listing.m_pathFinal);

      if (dirp == nullptr)
      {

         return true;

      }

      dirent* dp;

      ::file::path path;

      while ((dp = readdir(dirp)) != nullptr)
      {

         defer_add(listing, dp);

      }

      closedir(dirp);

      return true;

   }


   bool acme_directory::list(string_array & stra, const ::scoped_string & scopedstr, ::file::e_flag eflag)
   {

      DIR * dirp = opendir(scopedstr.c_str());

      if (dirp == nullptr)
      {

         return true;

      }

      dirent* dp;

      ::file::path path;

      while ((dp = readdir(dirp)) != nullptr)
      {

         if (dp->d_type & DT_DIR)
         {

            if (eflag & ::file::e_flag_folder && !(eflag & ::file::e_flag_file))
            {

               stra.add(string(dp->d_name) + "/");

            }

         }
         else
         {

            if (eflag & ::file::e_flag_file)
            {

               stra.add(dp->d_name);

            }

         }

      }

      closedir(dirp);

      return true;

   }


   //   void acme_directory::ls_dir(::file::path_array & stra, const char * psz)
   //   {
   //
   //      DIR * dirp = opendir(psz);
   //
   //      if (dirp == nullptr)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      dirent * dp;
   //
   //      while ((dp = readdir(dirp)) != nullptr)
   //      {
   //
   //         if (file_path_is_dots(dp->d_name))
   //         {
   //
   //            continue;
   //
   //         }
   //
   //         ::file::path strPath = ::file::path(psz) / dp->d_name;
   //
   //         if (is(strPath))
   //         {
   //
   //            stra.add(strPath);
   //
   //         }
   //
   //      }
   //
   //      closedir(dirp);
   //
   //   }
   //
   //
   //   void acme_directory::ls_file(::file::path_array & stra, const char * psz)
   //   {
   //
   //      DIR * dirp = opendir(psz);
   //
   //      if (dirp == nullptr)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      dirent * dp;
   //
   //      while ((dp = readdir(dirp)) != nullptr)
   //      {
   //
   //         if (file_path_is_dots(dp->d_name))
   //         {
   //
   //            continue;
   //
   //         }
   //
   //         ::file::path strPath = ::file::path(psz) / dp->d_name;
   //
   //         if (!is(strPath))
   //         {
   //
   //            stra.add(strPath);
   //
   //         }
   //
   //      }
   //
   //      closedir(dirp);
   //
   //   }


   ::file::path acme_directory::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
   {

      string_array stra;

      stra.add_tokens(pszEnv, ":");

      string strCandidate;

      for (i32 i = 0; i < stra.get_count(); i++)
      {

         if (stra[i].is_empty())
         {

            continue;

         }

         strCandidate = ::file::path(stra[i]) / pszTopic;

         if (m_pacmefile->exists(strCandidate))
         {

            return strCandidate;

         }

      }

      return "";

   }


   ::file::path acme_directory::archive()
   {


      return home() / "archive";

}::file::path acme_directory::home(){
      ::file::path path;//Unix sys are generic ...
   const char* homedir{ nullptr };
   if ((homedir = getenv("HOME")) == nullptr)
      homedir = getpwuid(getuid())->pw_dir;
   path = homedir;
   
   return path;
   
}


::file::path acme_directory::get_current(){

      auto pszCurrentDirName = get_current_dir_name();

      if(::is_null(pszCurrentDirName))
      {

         auto cerrornumber = c_error_number();

         auto estatus = cerrornumber.failed_estatus();

         throw ::exception(estatus, "posix::acme_directory::get_current");

      }

      string strCurrentDirName = ::string_from_strdup(pszCurrentDirName);

      return strCurrentDirName;

   }


   void acme_directory::change_current(const ::file::path & path)
   {

      auto iError = chdir(path);

      if(iError)
      {

         auto cerrornumber = c_error_number();

         auto estatus = cerrornumber.failed_estatus();
         
         throw ::exception(estatus, "posix::acme_directory::change_current");

      }

   }


//::file::path acme_directory::program_files_x86()
//{
//
//   ::file::path path("/opt/ca2");
//
//   return path;
//
//}
//
//
//::file::path acme_directory::program_files()
//{
//
//   ::file::path path("/opt/ca2");
//
//   return path;
//
//}


//
//::file::path acme_directory::home()
//{
//
//   return getenv("HOME");
//
//}


#if defined(UNIVERSAL_WINDOWS) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)

//::file::path acme_directory::bookmark()
//{
//
//   auto psystem = system();
//
//   auto pacmedir = psystem->m_pacmedirectory;
//
//   return pacmedir->localconfig() / "bookmark";
//
//}


#endif


#ifdef UNIVERSAL_WINDOWS


::file::path acme_directory::home()
{

   return "";

}


#endif


   bool acme_directory::is_accessible(const ::file::path & path)
   {

      return ::access(path, X_OK) == 0;

   }


} // namespace acme_posix


#if defined(__APPLE__) || defined(ANDROID)


char * get_current_dir_name()
{
   
   auto size = pathconf(".", _PC_PATH_MAX);
   
   if(size <= 0)
   {
      
      size = PATH_MAX;
      
   }
   
   char * buf = (char *) malloc(size + 1);
   
   if(buf == nullptr)
   {
    
      return nullptr;
      
   }
   
   auto ptr = getcwd(buf, (size_t)(size + 1));
   
   return ptr;

}


#endif



