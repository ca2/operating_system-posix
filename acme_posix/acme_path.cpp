/*****<3ThomasBorregaardSørensen!!Created by camilo*/
// From acme_posix/acme_file.h
// on 2021-08-12
// 18:20 BRT


namespace posix
{


   acme_path::acme_path() = default;


   acme_path::~acme_path() = default;


   bool acme_path::is_file_or_dir(const char * path1, ::file::enum_type * petype)
   {

      struct stat st;

      if (stat(path1, &st))
      {

         if (is_set(petype))
         {

            *petype = ::file::e_type_none;

         }

         return false;

      }

      if (is_set(petype))
      {

         if ((st.st_mode & S_IFDIR))
         {

            *petype = ::file::e_type_folder;

         }
         else
         {

            *petype = ::file::e_type_file;

         }

      }

      return true;

   }


   ::file::path acme_path::_final(const char * path)
   {

      if (::is_null(path))
      {

         return "";

      }

      if(*path == '\0')
      {

         return "";

      }

      char * pszRealPath = ::realpath(path, NULL);

      if (::is_null(pszRealPath))
      {

         return "";

      }

      ::file::path filepath(pszRealPath);

      ::free(pszRealPath);

      return filepath;

   }


} // namespace posix



