// From nano_user_x11 by camilo on 2024-06-04 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "user.h"
#include "window.h"


DECLARE_FACTORY(windowing_system_xcb);
DECLARE_FACTORY(nano_user_cairo);


IMPLEMENT_FACTORY(nano_user_xcb)
{

   CALL_FACTORY(windowing_system_xcb);

   CALL_FACTORY(nano_user_cairo);

   pfactory->add_factory_item<::xcb::nano::user::window, ::nano::user::window_implementation>();

   pfactory->add_factory_item < ::xcb::nano::user::user, ::nano::user::user >();

}



