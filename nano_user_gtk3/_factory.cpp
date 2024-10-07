#include "framework.h"
#include "display.h"
#include "user.h"
#include "window.h"


IMPLEMENT_FACTORY(nano_user_gtk3)
{

   pfactory->add_factory_item < ::gtk3::micro::user, ::micro::user >();
   pfactory->add_factory_item < ::gtk3::micro::window, ::acme::windowing::window >();
   pfactory->add_factory_item < ::gtk3::acme::windowing::display, ::acme::windowing::display >();

}



