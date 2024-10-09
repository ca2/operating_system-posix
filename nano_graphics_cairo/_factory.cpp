#include "framework.h"
#include "device.h"
#include "icon.h"
#include "acme/nano/graphics/brush.h"
#include "acme/nano/graphics/font.h"
#include "acme/nano/graphics/graphics.h"
#include "acme/nano/graphics/pen.h"
#include "acme/user/micro/user.h"


IMPLEMENT_FACTORY(nano_graphics_cairo)
{

   pfactory->add_factory_item < ::cairo::nano::graphics::device, ::nano::graphics::device >();

   pfactory->add_factory_item < ::nano::graphics::brush >();
   pfactory->add_factory_item < ::nano::graphics::font >();
   pfactory->add_factory_item < ::nano::graphics::pen >();

   pfactory->add_factory_item < ::cairo::nano::graphics::icon, ::nano::graphics::icon >();


   pfactory->add_factory_item < ::nano::graphics::graphics>();

}



