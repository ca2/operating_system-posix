// From nano_user_x11 by camilo on 2024-06-04 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "display.h"
#include "user.h"
#include "window.h"


IMPLEMENT_FACTORY(nano_user_kde5)
{

   pfactory->add_factory_item<::kde5::micro::window, ::acme::windowing::window>();

   pfactory->add_factory_item < ::kde5::micro::user, ::micro::user >();

   pfactory->add_factory_item < ::kde5::acme::windowing::display, ::acme::windowing::display >();

}



