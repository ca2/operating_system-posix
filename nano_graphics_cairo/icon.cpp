//
// Created by camilo on 9/24/24.
//
#include "framework.h"
#include "icon.h"
#include "acme/platform/system.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/windowing/windowing_base.h"


namespace cairo {
namespace nano {
namespace graphics {

   icon::icon()
   {

m_pcairosurface=nullptr;
   }

   icon::~icon()
   {
if(m_pcairosurface)
{


   cairo_surface_destroy(m_pcairosurface);

   m_pcairosurface=nullptr;
}
   }

   ::size_i32 icon::size() const
   {

if(!m_pcairosurface)
{
return{};

}

      auto cx = cairo_image_surface_get_width(m_pcairosurface);
      auto cy = cairo_image_surface_get_height(m_pcairosurface);

      return {cx, cy};



   }


         void icon::load_image_file(const void *p, memsize size)
         {

      if(m_pcairosurface)
      {

         cairo_surface_destroy(m_pcairosurface);

         m_pcairosurface = nullptr;

      }

            ::memory memoryHost;

            auto pixmap = nano()->user()->get_pixmap_from_file(memoryHost, p, size);


      if(pixmap.is_ok())
      {
         // Create a cairo surface using the ARGB32 data from memory
         m_pcairosurface = cairo_image_surface_create_for_data(
             memoryHost.data(),              // Pointer to the raw data in memory
             CAIRO_FORMAT_ARGB32,    // Data format (ARGB32)
             pixmap.width(),                  // Width of the surface
             pixmap.height(),                 // Height of the surface
             pixmap.m_iScan                 // Stride (number of bytes per row)
         );
      }

         }

      } // user

   } // nano

} // cairo



