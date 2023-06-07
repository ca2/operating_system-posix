/*****<3ThomasBorregaardSorensen!!Created by camilo*/
// From acme_posix/acme_file.h
// on 2021-08-12
// 18:20 BRT
#include "framework.h"
#include "acme_path.h"
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

         return ::file::e_type_folder;

      }
      else
      {

         return ::file::e_type_file;

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



