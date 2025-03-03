#include "framework.h"
#include "display.h"
#include "window.h"
#include "windowing.h"



IMPLEMENT_FACTORY(acme_windowing_lxq1)
{

   pfactory->add_factory_item < ::lxq1::acme::windowing::display, ::acme::windowing::display >();
   pfactory->add_factory_item < ::lxq1::acme::windowing::window, ::acme::windowing::window >();
   pfactory->add_factory_item < ::lxq1::acme::windowing::windowing, ::acme::windowing::windowing >();

}


