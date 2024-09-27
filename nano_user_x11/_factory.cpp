#include "framework.h"
#include "user.h"
#include "window.h"
#include "acme/nano/user/font.h"
#include "acme/nano/user/brush.h"
#include "acme/nano/user/pen.h"


DECLARE_FACTORY(windowing_system_x11);


IMPLEMENT_FACTORY(nano_user_x11)
{

   CALL_FACTORY(windowing_system_x11);

   pfactory->add_factory_item < ::x11::nano::user::user, ::nano::user::user >();
   pfactory->add_factory_item < ::x11::nano::user::interchange, ::nano::user::window_implementation >();
   pfactory->add_factory_item<::nano::graphics::font>();
   pfactory->add_factory_item<::nano::graphics::brush>();
   pfactory->add_factory_item<::nano::graphics::pen>();

}



