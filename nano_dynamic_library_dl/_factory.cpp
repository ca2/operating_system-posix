#include "framework.h"
#include "device.h"
#include "acme/nano/user/user.h"


IMPLEMENT_FACTORY(nano_user_cairo)
{

   pfactory->add_factory_item < ::cairo::nano::user::device, ::nano::user::device >();

   pfactory->add_factory_item < ::nano::user::user >();

}



