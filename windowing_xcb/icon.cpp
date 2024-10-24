// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Soerensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:38
#include "framework.h"
#include "icon.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_context.h"


namespace windowing_xcb
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


   void icon::set_tray_icon_name(const ::string & strTrayIconName)
   {

      //auto estatus =
      //
      ::windowing::icon::set_tray_icon_name(strTrayIconName);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   void * icon::get_os_data(const ::size_i32 & size) const
   {

      return nullptr;

   }


   void icon::load_file(string strPath)
   {

      throw ::interface_only();

      //return false;

   }


   void icon::load_matter(string strMatter)
   {

      string strPath = directory()->matter(strMatter);

      load_file(strPath);

      //if (!load_file(strPath))
//      {
//
//         return false;
//
//      }

//      on_update_icon();

//      return true;

   }


   void icon::load_app_tray_icon(string strAppId)
   {

      //auto estatus =
      //
      set_tray_icon_name(strAppId);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   ::image::image_pointer icon::get_image(const ::size_i32 & size)
   {

      throw ::interface_only();
      
      return nullptr;

   }


   void icon::get_sizes(::size_i32_array & a)
   {


   }


} // namespace windowing_xcb



