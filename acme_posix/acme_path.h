/*****<3ThomasBorregaardSorensen!!Created by camilo*/
// From acme_posix/acme_file.h
// on 2021-08-12
// 18:18 BRT
#pragma once


#include "acme/filesystem/filesystem/acme_path.h"


namespace acme_posix
{


   class CLASS_DECL_ACME acme_path :
      virtual public ::acme_path
   {
   public:


      //__creatable_from_library(acme_path, ::acme_path, "acme_posix");


      acme_path();
      ~acme_path() override;


      ::file::enum_type get_type(const ::file::path & path1) override;

      ::file::path _safe_real_path(const ::file::path & path) override;

      ::file::path _real_path(const ::file::path & path) override;

      ::string get_default_path() override;

      ::file::e_type executable_type(const ::file::path & path) override;

      ::file::path get_absolute_path(const ::scoped_string& scopedstr) override;


   };



} // namespace acme_posix



