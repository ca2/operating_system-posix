#include "framework.h"
#include "windowing.h"


IMPLEMENT_FACTORY(acme_windowing_gtk3)
{

   pfactory->add_factory_item < ::gtk3::acme::windowing::window, ::acme::windowing::window >();
   pfactory->add_factory_item < ::gtk3::acme::windowing::windowing, ::acme::windowing::windowing >();

}


