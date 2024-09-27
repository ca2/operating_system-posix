//
// Created by camilo on 9/24/24.
//
#include "framework.h"
#include "icon.h"
#include "acme/prototype/geometry2d/size.h"

namespace cairo {
namespace nano {
namespace user {

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


} // user
} // nano
} // cairo