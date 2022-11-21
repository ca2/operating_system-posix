// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Sørensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:38
#pragma once


#include "aura/windowing/icon.h"
#include "acme/primitive/geometry2d/_geometry2d.h"


namespace windowing_x11
{


   class CLASS_DECL_WINDOWING_X11 icon :
      virtual public ::windowing::icon
   {
   public:


      array < concrete < ::size_i32 > >         m_sizea;


      icon();
      ~icon() override;


      string get_tray_icon_name() const override;


      void set_tray_icon_name(const string & strTrayIconName) override;


      void get_sizes(array < concrete < ::size_i32 > > & a) override;


      void * get_os_data(const ::size_i32 & size) const override;


      virtual void load_matter(const ::string & strPath) override;
      virtual void load_app_tray_icon(const ::string & strPath) override;
      virtual void load_file(const ::string & strPath) override;


      virtual image_pointer get_image(const concrete < ::size_i32 > & size) override;

      
   };



} // namespace windowing



