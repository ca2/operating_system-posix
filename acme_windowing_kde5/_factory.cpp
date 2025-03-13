#include "framework.h"
#include "display.h"
#include "window.h"
#include "windowing.h"


IMPLEMENT_FACTORY(acme_windowing_kde5)
{

   pfactory->add_factory_item < ::kde5::acme::windowing::display, ::acme::windowing::display >();
   pfactory->add_factory_item < ::kde5::acme::windowing::window, ::acme::windowing::window >();
   pfactory->add_factory_item < ::kde5::acme::windowing::windowing, ::acme::windowing::windowing >();

}


