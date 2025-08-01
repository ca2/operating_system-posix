// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Soerensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:38
#pragma once


#include "aura/windowing/icon.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/size_array.h"


namespace windowing_q
{


   class CLASS_DECL_WINDOWING_Q icon :
      virtual public ::windowing::icon
   {
   public:


      //array < concrete < ::int_size > >         m_sizea;

      int_size_array                               m_sizea;


      icon();
      ~icon() override;


      string get_tray_icon_name() const override;


      void set_tray_icon_name(const ::scoped_string & scopedstrTrayIconName) override;


      void get_sizes(::int_size_array & a) override;


      void * get_os_data(const ::int_size & size) const override;


      virtual void load_matter(const ::scoped_string & scopedstrPath) override;
      virtual void load_app_tray_icon(const ::scoped_string & scopedstrPath) override;
      virtual void load_file(const ::scoped_string & scopedstrPath) override;


      virtual ::image::image_pointer get_image(const ::int_size & size) override;

      
   };



} // namespace windowing_q



