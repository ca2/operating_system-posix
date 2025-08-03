/*****<3ThomasBorregaardSorensen!!Created by camilo*/
// From acme_posix/file_system.h
// on 2021-08-12
// 18:20 BRT
#include "framework.h"
#include "directory_system.h"
#include "path_system.h"
#if defined( FREEBSD) || defined(OPENBSD)
//#define __XSI_VISIBLE 1
#include <unistd.h>
#else
#include <unistd.h>
#endif
//#include "acme/filesystem/filesystem/path.h"
#include <sys/stat.h>
#include <stdio.h>


namespace acme_posix
{


   path_system::path_system() = default;


   path_system::~path_system()
   {
      
   }


   ::file::enum_type path_system::get_type(const ::file::path & path1)
   {

      struct stat st;

      if (stat(path1, &st))
      {

         return ::file::e_type_doesnt_exist;

      }

      if ((st.st_mode & S_IFDIR))
      {

         return ::file::e_type_existent_folder;

      }
      else
      {

         return ::file::e_type_existent_file;

      }

   }


   ::file::path path_system::_real_path(const ::file::path & path)
   {

      if (path.is_empty())
      {

         return "";

      }

      char * pszRealPath = ::realpath(path.c_str(), NULL);

      if (::is_null(pszRealPath))
      {

         return path;

      }

      ::file::path filepath(pszRealPath);

      ::free(pszRealPath);

      return filepath;

   }


   ::file::path path_system::_safe_real_path(const ::file::path & path)
   {

      if (path.is_empty())
      {

         return "";

      }
       
       ::string str(path);
       
       //char pszRealPath[PATH_MAX];
       
       //::zero(scopedstrRealPath);

      //auto pszReturnedRealPath = ::realpath(str, pszRealPath);

      auto pszReturnedRealPath = ::realpath(str, nullptr);

      ::file::path filepath;

      if(!pszReturnedRealPath)
      {

         filepath = str;

      }
      else
      {

         filepath = pszReturnedRealPath;

      }

      //::free(scopedstrRealPath);

      return filepath;

   }


   ::string path_system::get_default_path()
   {

      return "/bin:/usr/bin:/usr/local/bin";

   }


   /// Test if the given path can be executed.
   /// \return 0 on success, an errno value on failure.
   ::file::e_type path_system::executable_type(const ::file::path & scopedstrCommand)
   {

      struct stat buff;

      if (stat(scopedstrCommand.c_str(), &buff))
      {

         return ::file::e_type_doesnt_exist;

      }

      if(access(scopedstrCommand.c_str(), X_OK))
      {

         return ::file::e_type_non_executable;

      }

      return S_ISREG(buff.st_mode) ? ::file::e_type_executable : ::file::e_type_folder2;

   }


   ::file::path path_system::get_absolute_path(const ::scoped_string& scopedstr)
   {

      ::file::path path(scopedstr);

      char* full_path = realpath(scopedstr.c_str(), nullptr);

      if (full_path)
      {

         path = ::string(full_path);

         free(full_path);

      }

      return path;

   }

void path_system::rename(const ::file::path& pathNewName, const ::file::path& pathOldName)
{
   
   ::string strOldName(pathOldName);
   
   ::string strNewName(pathNewName);

   auto iError = ::rename(strOldName, strNewName);
   
   if(iError)
   {
    
      throw ::exception(error_io, "rename from \"" + strOldName + "\" to \"" + strNewName + "\" failed");
      
   }

}


void path_system::create_symbolic_link(const ::scoped_string & scopedstrLink, const ::scoped_string& scopedstrSource)
{

   ::string strTarget = scopedstrLink;


      ::file::path pathTarget;

      pathTarget = strTarget;

      ::file::path pathTargetFolder;

      pathTargetFolder = pathTarget.folder();

      directory_system()->create(pathTargetFolder);

   ::string strSource = scopedstrSource;
   
   int iError = ::symlink(strSource, strTarget);

      if(iError != 0)
      {

         throw ::exception(error_failed);

      }

}


} // namespace acme_posix



