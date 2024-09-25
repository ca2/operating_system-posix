//
// Created by camilo on 2024-09-24 23:13 <3ThomasBorregaardSorensen!!
//

#pragma once
#include "acme/nano/user/icon.h"
#include <cairo.h>
namespace cairo {
namespace nano {
namespace user {

class  CLASS_DECL_ACME icon:
virtual public ::nano::user::icon{
  public:

    cairo_surface_t * m_pcairosurface;

    icon();
    ~icon();

   ::size_i32 size() const override;


};

} // user
} // nano
} // cairo



