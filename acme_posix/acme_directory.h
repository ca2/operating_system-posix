// From acme/filesystem/file/dir.cpp by camilo 
// on 2021-08-09 03:20 BRT
// <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/filesystem/filesystem/acme_directory.h"


namespace acme_posix
{


   class CLASS_DECL_ACME_POSIX acme_directory :
      virtual public ::acme_directory
   {
   public:


      //__creatable_from_library(acme_directory, ::acme_directory, "acme_posix");


      acme_directory();
      ~acme_directory() override;
      

      //virtual string name(const char * path1) override;

      ::file::path module() override;

      //::e_status create(const char * path) override;

      //::e_status _create(const char * path) override;

      //::e_status create_directory(const char * path) override;

      //::file::path module() override;

      bool is(const char * path) override;

      //bool _is(const char * path1) override;

      //string name(string path) override;

      //void rls(::file::path_array & stra, const char * psz) override;

      //void rls_dir(::file::path_array & stra, const char * psz) override;
      //void ls(::file::path_array & stra, const char * psz) override;

      //void ls_dir(::file::path_array & stra, const char * psz) override;
      //void ls_file(::file::path_array & stra, const char * psz) override;

      bool enumerate(::file::listing & listing) override;

      bool list(::string_array & stra, const char * psz, ::file::e_flag eflag = ::file::e_flag_file_or_folder) override;

      ::file::path pathfind(const string & pszEnv, const string & pszTopic, const string & pszMode) override;

      ::file::path archive() override;

      //int make_path(const char * psz) override;

      string get_current() override;

      void change_current(const char * psz) override;


   };


} // namespace acme_posix



