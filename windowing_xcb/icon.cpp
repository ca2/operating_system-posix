// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sørensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:38
#include "framework.h"
#include "icon.h"


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

      auto pcontext = m_pcontext;

      string strPath = dir()->matter(strMatter);

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


   image_pointer icon::get_image(const concrete < ::size_i32 > & size)
   {

      throw ::interface_only();
      
      return nullptr;

   }


   void icon::get_sizes(array < concrete < ::size_i32 > > & a)
   {


   }


} // namespace windowing_xcb



