// From nano_user_x11 by camilo on 2024-06-04 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "display.h"
#include "user.h"
#include "window.h"


IMPLEMENT_FACTORY(nano_user_kde5)
{

   pfactory->add_factory_item<::kde5::nano::user::window, ::nano::windowing::window>();

   pfactory->add_factory_item < ::kde5::nano::user::user, ::nano::user::user >();

   pfactory->add_factory_item < ::kde5::nano::windowing::display, ::nano::windowing::display >();

}



