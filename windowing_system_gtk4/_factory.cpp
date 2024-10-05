#include "framework.h"
#include "windowing_system.h"


IMPLEMENT_FACTORY(windowing_system_gtk4)
{

   pfactory->add_factory_item < ::windowing_system_gtk4::windowing_system, ::windowing::windowing_base >();

}


