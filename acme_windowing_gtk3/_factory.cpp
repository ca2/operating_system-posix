#include "framework.h"
#include "display.h"
#include "window.h"
#include "windowing.h"


IMPLEMENT_FACTORY(acme_windowing_gtk3)
{

   pfactory->add_factory_item < ::gtk3::acme::windowing::display, ::acme::windowing::display >();
   pfactory->add_factory_item < ::gtk3::acme::windowing::window, ::acme::windowing::window >();
   pfactory->add_factory_item < ::gtk3::acme::windowing::windowing, ::acme::windowing::windowing >();

}


