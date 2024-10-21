//
// Created by camilo on 2024-09-24 23:13 <3ThomasBorregaardSorensen!!
//

#pragma once

#include "acme/nano/graphics/icon.h"

namespace gtk4 {
namespace nano {
namespace user {

class  CLASS_DECL_ACME icon:
virtual public ::cairo::nano::graphics::icon{
  public:

    icon();
    ~icon();


   void load_image_file(const void *p, memsize size) override;

};

} // user
} // nano
} // gtk4



