// From acme/filesystem/file/dir.cpp by camilo 
// on 2021-08-09 03:19 BRT
// <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "directory_system.h"
#include "file_system.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/nano/nano.h"
#include "acme/nano/account/account.h"
#include "acme/nano/account/user.h"
#include "acme/operating_system/summary.h"
#include "acme/operating_system/shared_posix/c_error_number.h"
#include "acme/platform/node.h"
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
#elif defined(__BSD__)
#if defined(OPENBSD)
#include "clear_cstddef"
#endif
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


#if defined(DEBUG) && defined(NETBSD)
//#define LOG_HERE
#endif



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


   directory_system::directory_system()
   {


   }


   directory_system::~directory_system()
   {


   }

   //
   //   ::e_status directory_system::create(const char * path)
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
   //   ::e_status directory_system::_create(const char * path)
   //   {
   //
   //      return ::create_directory_path(path);
   //
   //   }
   //
   //
   //   ::e_status directory_system::create_directory(const char * path)
   //   {
   //
   //      return ::create_directory(path);
   //
   //   }


   ::file::path directory_system::module()
   {

      ::file::path pathModule(m_pfilesystem->module());

      return pathModule.folder();

   }


//   ::filebool directory_system::_file_type(const ::file::path & path)
//   {
//
//      bool bDir = false;
//
//      if(!_is(bDir, path))
//      {
//
//         return false;
//
//      }
//
//      return bDir;
//
//   }


   //   void directory_system::rls(::file::path_array & stra, const char * psz)
   //   {
   //
   //      ::collection::count start = stra.get_count();
   //
   //      ls(stra, psz);
   //
   //      ::collection::count end = stra.get_count();
   //
   //      for (::collection::index i = start; i < end; i++)
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


   //   void directory_system::rls_dir(::file::path_array & stra, const char * psz)
   //   {
   //
   //      ::collection::count start = stra.get_count();
   //
   //      ls_dir(stra, psz);
   //
   //      ::collection::count end = stra.get_count();
   //
   //      for (::collection::index i = start; i < end; i++)
   //      {
   //
   //         ::file::path path = stra[i];
   //
   //         rls_dir(stra, path);
   //
   //      }
   //
   //   }


   void directory_system::_defer_add(::file::listing& listing, const dirent* dp)
   {

      if (file_path_is_dots(dp->d_name))
      {
         
         return;

      }


      ::file::path path;

      string strFilename(dp->d_name);

      //const char * psz = dp->d_name;

      path = listing.m_pathFinal / strFilename;
      
#if defined(LOG_HERE)
      
      printf("pathFinal   : %s\n", listing.m_pathFinal.c_str());
      printf("strFilename : %s\n", strFilename.c_str());
      printf("path        : %s\n", path.c_str());
      printf("dp->d_type  : %d\n", dp->d_type);

#endif

      if (path.begins(listing.m_pathBasePath))
      {

         path.m_iBasePathLength = listing.m_pathBasePath.length() + 1;

      }
      
#if defined(LOG_HERE)

      int iDtDir = DT_DIR;
      
      printf("^DT_DIR=%d\n", iDtDir);
      
      int iDtUnknown = DT_UNKNOWN;
      
      printf("^DT_UNKNOWN=%d\n", iDtUnknown);
      
#endif

      bool bIsDir = false;

      if(dp->d_type == DT_UNKNOWN)
      {
         
         if(is(path))
         {
            
            bIsDir = true;
            
         }
         
      }
      else if(dp->d_type & DT_DIR)
      {
         
         bIsDir = true;
         
      }

      if(bIsDir)
      {

#if defined(LOG_HERE)

         printf("^folder\n");
         
#endif
      
         path.set_existent_folder();

      }
      else
      {

#if defined(LOG_HERE)

         printf("^file\n");
         
#endif

         path.set_existent_file();

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


void directory_system::erase_recursively(const ::file::path &path)
{


    // Delete the directory and its contents by traversing the tree in reverse order, without crossing mount boundaries and symbolic links

    if (nftw(path.c_str(), rmFiles,10, FTW_DEPTH|FTW_MOUNT|FTW_PHYS) < 0)
    {
        //perror("ERROR: ntfw");
       //exit(1);
       throw ::exception(error_failed, "failed to erase");
    }
}

   bool directory_system::enumerate(::file::listing& listing)
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

         _defer_add(listing, dp);

      }

      closedir(dirp);

      return true;

   }


   bool directory_system::list(string_array & stra, const ::scoped_string & scopedstr, ::file::e_flag eflag)
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


   //   void directory_system::ls_dir(::file::path_array & stra, const char * psz)
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
   //   void directory_system::ls_file(::file::path_array & stra, const char * psz)
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


   ::file::path directory_system::pathfind(const string& pszEnv, const string& pszTopic, const string& pszMode)
   {

      string_array stra;

      stra.add_tokens(pszEnv, ":");

      string strCandidate;

      for (int i = 0; i < stra.get_count(); i++)
      {

         if (stra[i].is_empty())
         {

            continue;

         }

         strCandidate = ::file::path(stra[i]) / pszTopic;

         if (m_pfilesystem->exists(strCandidate))
         {

            return strCandidate;

         }

      }

      return "";

   }


   ::file::path directory_system::archive()
   {


      return home() / "archive";

}


   ::file::path directory_system::home()
   {

      ::file::path path;//Unix sys are generic ...

      const char* homedir{ nullptr };

      if ((homedir = getenv("HOME")) == nullptr)
      {

         auto puserid = nano()->account()->current_user_id();

         if(puserid)
         {

            auto puser = nano()->account()->get_user(puserid);

            if (puser)
            {

               homedir = puser->m_strDir;

            }

         }
      }

      path = homedir;
   
      return path;
   
   }


::file::path directory_system::get_current(){

      auto pszCurrentDirName = get_current_dir_name();

      if(::is_null(pszCurrentDirName))
      {

         auto cerrornumber = c_error_number();

         auto estatus = cerrornumber.failed_estatus();

         throw ::exception(estatus, "posix::directory_system::get_current");

      }

      string strCurrentDirName = ::string_from_strdup(pszCurrentDirName);

      return strCurrentDirName;

   }


   void directory_system::change_current(const ::file::path & path)
   {

      auto iError = chdir(path);

      if(iError)
      {

         auto cerrornumber = c_error_number();

         auto estatus = cerrornumber.failed_estatus();
         
         throw ::exception(estatus, "posix::directory_system::change_current");

      }

   }


//::file::path directory_system::program_files_x86()
//{
//
//   ::file::path path("/opt/ca2");
//
//   return path;
//
//}
//
//
//::file::path directory_system::program_files()
//{
//
//   ::file::path path("/opt/ca2");
//
//   return path;
//
//}


//
//::file::path directory_system::home()
//{
//
//   return getenv("HOME");
//
//}


#if defined(UNIVERSAL_WINDOWS) || defined(__APPLE__) || defined(LINUX) || defined(ANDROID)

//::file::path directory_system::bookmark()
//{
//
//   auto psystem = system();
//
//   auto pacmedir = psystem->m_pdirectorysystem;
//
//   return pacmedir->localconfig() / "bookmark";
//
//}


#endif


#ifdef UNIVERSAL_WINDOWS


::file::path directory_system::home()
{

   return "";

}


#endif


   bool directory_system::is_accessible(const ::file::path & path)
   {

      return ::access(path, X_OK) == 0;

   }


   ::file::path directory_system::___fonts()
   {

      ::file::path path___fontsFolder;

      auto psummary = node()->operating_system_summary();

      if(psummary->m_strSystemFamily.case_insensitive_equals("debian"))
      {

         path___fontsFolder = "/usr/share/fonts/truetype/___fonts";

      }
      else if(psummary->m_strSystem.case_insensitive_equals("fedora"))
      {

         path___fontsFolder = "/usr/share/fonts/___fonts";

      }
      else
      {

         path___fontsFolder = "/usr/share/fonts/truetype/___fonts";

      }

      return path___fontsFolder;

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



