// From windowing_system_x11 by camilo on 2024-06-04 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "windowing_system.h"


IMPLEMENT_FACTORY(windowing_system_xcb)
{

   pfactory->add_factory_item < ::xcb::windowing_system, ::windowing_system::windowing_system >();

}


