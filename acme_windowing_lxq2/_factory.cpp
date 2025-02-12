#include "framework.h"
#include "display.h"
#include "window.h"
#include "windowing.h"



IMPLEMENT_FACTORY(acme_windowing_lxq2)
{

   pfactory->add_factory_item < ::lxq2::acme::windowing::display, ::acme::windowing::display >();
   pfactory->add_factory_item < ::lxq2::acme::windowing::window, ::acme::windowing::window >();
   pfactory->add_factory_item < ::lxq2::acme::windowing::windowing, ::acme::windowing::windowing >();

}


