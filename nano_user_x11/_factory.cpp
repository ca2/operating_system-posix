#include "framework.h"
#include "user.h"


DECLARE_FACTORY(windowing_system_x11);


IMPLEMENT_FACTORY(nano_user_x11)
{

   CALL_FACTORY(windowing_system_x11);

   pfactory->add_factory_item < ::x11::nano::user::user, ::nano::user::user >();

}



