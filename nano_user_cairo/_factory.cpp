#include "framework.h"
#include "device.h"
#include "acme/nano/user/brush.h"
#include "acme/nano/user/font.h"
#include "acme/nano/user/pen.h"
#include "acme/nano/user/user.h"


IMPLEMENT_FACTORY(nano_user_cairo)
{

   pfactory->add_factory_item < ::cairo::nano::user::device, ::nano::user::device >();

   pfactory->add_factory_item < ::nano::user::user >();

   pfactory->add_factory_item < ::nano::user::brush >();
   pfactory->add_factory_item < ::nano::user::font >();
   pfactory->add_factory_item < ::nano::user::pen >();

}



