/*****<3ThomasBorregaardSorensen!!Created by camilo*/
// From acme_posix/file_system.h
// on 2021-08-12
// 18:18 BRT
#pragma once


#include "acme/filesystem/filesystem/path_system.h"


namespace acme_posix
{


   class CLASS_DECL_ACME path_system :
      virtual public ::path_system
   {
   public:


      //__creatable_from_library(path_system, ::path_system, "acme_posix");


      path_system();
      ~path_system() override;


      ::file::enum_type get_type(const ::file::path & path1) override;

      ::file::path _safe_real_path(const ::file::path & path) override;

      ::file::path _real_path(const ::file::path & path) override;

      ::string get_default_path() override;

      ::file::e_type executable_type(const ::file::path & path) override;

      ::file::path get_absolute_path(const ::scoped_string& scopedstr) override;
      void rename(const ::file::path& pathNewName, const ::file::path& pathOldName) override;

      void create_symbolic_link(const ::scoped_string & scopedstrLink, const ::scoped_string& scopedstrSource)override;


   };



} // namespace acme_posix



