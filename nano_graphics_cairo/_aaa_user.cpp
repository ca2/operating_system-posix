//
// Created by camilo on 11/04-April/2022. 12:11 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "device.h"
#include "acme/nano/graphics/brush.h"
#include "acme/nano/graphics/font.h"
#include "acme/nano/graphics/pen.h"
#include "acme/prototype/prototype/factory.h"


void operating_system_initialize_cairo_nano(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::nano::graphics::brush>();
   pfactory->add_factory_item<::nano::graphics::font>();
   pfactory->add_factory_item<::nano::graphics::pen>();
   pfactory->add_factory_item<::cairo::nano::graphics::device, ::nano::graphics::device>();

}


