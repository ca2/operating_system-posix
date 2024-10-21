#include "framework.h"
#include "display.h"
#include "window.h"
#include "windowing.h"


IMPLEMENT_FACTORY(acme_windowing_gtk4)
{

   pfactory->add_factory_item < ::gtk4::acme::windowing::windowing, ::acme::windowing::windowing >();

   pfactory->add_factory_item < ::gtk4::acme::windowing::window, ::acme::windowing::window >();

   pfactory->add_factory_item < ::gtk4::acme::windowing::display, ::acme::windowing::display >();

}


