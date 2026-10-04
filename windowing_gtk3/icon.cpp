// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Soerensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:38
#include "platform.h"
#include "icon.h"
#include <gdk-pixbuf/gdk-pixbuf.h>
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
      if (m_pGtkPixbuf)
         g_object_unref(m_pGtkPixbuf);

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


   void * icon::get_os_data(const ::i32_size & size) const
   {

      return m_pGtkPixbuf;

   }


   void icon::set_file(const ::payload & payloadFile)
   {

      auto path = m_papplication->defer_process_path(payloadFile.as_file_path());
      GError *error = nullptr;
      auto pixbuf = gdk_pixbuf_new_from_file(path.c_str(), &error);
      if (!pixbuf)
      {
         warning() << "GTK3 icon load failed: " << path;
         if (error) g_error_free(error);
         return;
      }
      if (m_pGtkPixbuf) g_object_unref(m_pGtkPixbuf);
      m_pGtkPixbuf = pixbuf;

      //return false;

   }


   void icon::set_matter(const ::scoped_string & scopedstrMatter)
   {

      auto pcontext = m_papplication;

      string strPath = pcontext->directory()->matter(scopedstrMatter);

      set_file(strPath);

//      if (!load_file(strPath))
//      {
//
//         //return false;
//
//      }

//      on_update_icon();

      //return true;

   }


   void icon::set_app_tray_icon(const ::scoped_string & scopedstrAppId)
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


   ::image::image_pointer icon::get_image(const ::i32_size& size)
   {

      throw ::interface_only();
      
      return nullptr;

   }


   void icon::get_sizes(::i32_size_array & a)
   {


   }


} // namespace windowing_gtk3



