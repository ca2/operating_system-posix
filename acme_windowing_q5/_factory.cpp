#include "framework.h"
#include "windowing.h"


IMPLEMENT_FACTORY(acme_windowing_kde5)
{

   pfactory->add_factory_item < ::q5::acme::windowing::windowing, ::acme::windowing::windowing >();

}


