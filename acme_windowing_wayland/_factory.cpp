#include "framework.h"
#include "windowing_system.h"


IMPLEMENT_FACTORY(windowing_system_wayland)
{

   pfactory->add_factory_item < ::wayland::windowing_system, ::windowing::windowing_base >();

}


