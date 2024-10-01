#include "framework.h"
#include "display.h"
#include "user.h"
#include "window.h"


IMPLEMENT_FACTORY(nano_user_gtk3)
{

   pfactory->add_factory_item < ::gtk3::nano::user::user, ::nano::user::user >();
   pfactory->add_factory_item < ::gtk3::nano::user::window, ::windowing::window_base >();
   pfactory->add_factory_item < ::gtk3::nano::user::display, ::nano::user::display >();

}



