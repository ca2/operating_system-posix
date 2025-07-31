#pragma once


#include "aura/user/user/shell.h"


namespace aura_posix
{


   class CLASS_DECL_AURA_POSIX shell :
      virtual public ::user::shell
   {
   public:


      ::pointer<::image::image_context>m_pimagecontext;


      shell();
      ~shell() override;


      void initialize(::particle * pparticle) override;
      //virtual void initialize() override;

      //virtual void defer_start();

      //virtual int get_image_foo(oswindow oswindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;
      //virtual int get_file_extension_image(oswindow oswindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;
      bool get_image_by_file_extension(_get_file_image_ & getfileimage) override;
      //virtual int get_image(oswindow oswindow, const ::scoped_string & scopedstrPath, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;


      void on_update_sizes_interest() override;


      bool _get_file_image(_get_file_image_ & getfileimage) override;


      ::user::shell::enum_folder get_folder_type(::particle * pparticle, const ::wstring & lpcszPath) override;
      ::user::shell::enum_folder get_folder_type(::particle * pparticle, const ::string & lpcszPath) override;

      int add_icon_path(::file::path path, color32_t crBk);



//         int get_image(per_fork * pfork, oswindow oswindow, image_key key, const unichar * lpcszExtra, color32_t crBk);
//         int get_image_by_extension(per_fork * pfork, oswindow oswindow, image_key & key, color32_t crBk);
//         int get_foo_image(per_fork * pfork, oswindow oswindow, image_key key, color32_t crBk);


      //int shell_run();


   };


} // namespace aura



