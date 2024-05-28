#include "framework.h"
#include "device.h"


IMPLEMENT_FACTORY(nano_user_cairo)
{

   pfactory->add_factory_item < ::cairo::nano::user::device, ::nano::user::device >();

}



