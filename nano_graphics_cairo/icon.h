//
// Created by camilo on 2024-09-24 23:13 <3ThomasBorregaardSorensen!!
//

#pragma once
#include "acme/nano/graphics/icon.h"
#include <cairo/cairo.h>
namespace cairo {
namespace nano {
namespace graphics {

class  CLASS_DECL_ACME icon:
virtual public ::nano::graphics::icon{
  public:

    cairo_surface_t * m_pcairosurface;

    icon();
    ~icon();

   ::int_size size() const override;


   void load_image_file(const void *p, memsize size) override;


};

} // user
} // nano
} // cairo



