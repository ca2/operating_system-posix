// From nano_user_x11 by camilo on 2024-06-04 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "user.h"
#include "window.h"


//DECLARE_FACTORY(windowing_system_xcb);
//DECLARE_FACTORY(nano_user_cairo);


IMPLEMENT_FACTORY(nano_user_kde5)
{

   //CALL_FACTORY(windowing_system_xcb);

   //CALL_FACTORY(nano_user_cairo);

   pfactory->add_factory_item<::kde5::nano::user::window, ::windowing::window_base>();

   pfactory->add_factory_item < ::kde5::nano::user::user, ::nano::user::user >();

}



