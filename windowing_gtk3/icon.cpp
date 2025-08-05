// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Soerensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:38
#include "framework.h"
#include "icon.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "apex/platform/context.h"
//#include "_windowing_wayland.h"


namespace windowing_gtk3
{


   icon::icon()
   {

   }


   icon::~icon()
   {


   }


   string icon::get_tray_icon_name() const
   {

      return m_strTrayIconName;

   }


   void icon::set_tray_icon_name(const ::scoped_string & scopedstrTrayIconName)
   {

      //auto estatus =
      //
      //
      ::windowing::icon::set_tray_icon_name(scopedstrTrayIconName);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   void * icon::get_os_data(const ::int_size & size) const
   {

      return nullptr;

   }


   void icon::load_file(const ::scoped_string & scopedstrPath)
   {

      throw ::interface_only();

      //return false;

   }


   void icon::load_matter(const ::scoped_string & scopedstrMatter)
   {

      auto pcontext = m_papplication;

      string strPath = pcontext->directory()->matter(scopedstrMatter);

      load_file(strPath);

//      if (!load_file(strPath))
//      {
//
//         //return false;
//
//      }

//      on_update_icon();

      //return true;

   }


   void icon::load_app_tray_icon(const ::scoped_string & scopedstrAppId)
   {

      //auto estatus =
      //
      set_tray_icon_name(scopedstrAppId);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   ::image::image_pointer icon::get_image(const ::int_size& size)
   {

      throw ::interface_only();
      
      return nullptr;

   }


   void icon::get_sizes(::int_size_array & a)
   {


   }


} // namespace windowing_gtk3



