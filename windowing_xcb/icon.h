// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Soerensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:38
#pragma once


#include "aura/windowing/icon.h"


namespace windowing_xcb
{


   class CLASS_DECL_WINDOWING_XCB icon :
      virtual public ::windowing::icon
   {
   public:


      //Bstring m_strTrayIconName;

      //::int_size_array m_sizea;


      icon();

      ~icon() override;


      string get_tray_icon_name() const override;


      void set_tray_icon_name(const ::scoped_string & scopedstrTrayIconName) override;


      void get_sizes(::int_size_array & a) override;


      void * get_os_data(const ::int_size & size) const override;


      void load_matter(const ::scoped_string & scopedstrPath);

      void load_app_tray_icon(const ::scoped_string & scopedstrPath);

      void load_file(const ::scoped_string & scopedstrPath);


      ::image::image_pointer get_image(const ::int_size & size) override;


   };



} // namespace windowing



