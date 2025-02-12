#include "framework.h"
#include "display.h"
#include "window.h"
#include "windowing.h"



IMPLEMENT_FACTORY(acme_windowing_kde6)
{

   pfactory->add_factory_item < ::kde6::acme::windowing::display, ::acme::windowing::display >();
   pfactory->add_factory_item < ::kde6::acme::windowing::window, ::acme::windowing::window >();
   pfactory->add_factory_item < ::kde6::acme::windowing::windowing, ::acme::windowing::windowing >();

}


