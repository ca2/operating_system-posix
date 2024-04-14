/*****<3ThomasBorregaardSorensen!!Created by camilo*/
// From acme_posix/acme_file.h
// on 2021-08-12
// 18:20 BRT
#include "framework.h"
#include "acme_path.h"
#if defined( FREEBSD)
#define __XSI_VISIBLE 1
#include <unistd.h>
#endif
//#include "acme/filesystem/filesystem/path.h"
#include <sys/stat.h>


namespace acme_posix
{


   acme_path::acme_path() = default;


   acme_path::~acme_path()
   {
      
   }


   ::file::enum_type acme_path::get_type(const ::file::path & path1)
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


   ::file::path acme_path::_real_path(const ::file::path & path)
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


   ::file::path acme_path::_safe_real_path(const ::file::path & path)
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


   ::string acme_path::get_default_path()
   {

      return "/bin:/usr/bin:/usr/local/bin";

   }


   /// Test if the given path can be executed.
   /// \return 0 on success, an errno value on failure.
   ::file::e_type acme_path::executable_type(const ::file::path & scopedstrCommand)
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


   ::file::path acme_path::get_absolute_path(const ::scoped_string& scopedstr)
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




} // namespace acme_posix



