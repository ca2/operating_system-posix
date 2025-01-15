#include "framework.h"
#include "windowing.h"


IMPLEMENT_FACTORY(windowing_system_kde5)
{

   pfactory->add_factory_item < ::kde5::acme::windowing::windowing, ::acme::windowing::windowing >();

}


