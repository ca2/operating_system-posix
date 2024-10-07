#include "framework.h"
#include "user.h"
#include "window.h"
//#include "acme/nano/graphics/font.h"
//#include "acme/nano/graphics/brush.h"
//#include "acme/nano/graphics/pen.h"


//DECLARE_FACTORY(windowing_system_x11);


IMPLEMENT_FACTORY(nano_user_x11)
{

//   CALL_FACTORY(windowing_system_x11);

   pfactory->add_factory_item < ::x11::micro::user, ::micro::user >();
   pfactory->add_factory_item < ::x11::micro::window, ::acme::windowing::window >();
//   pfactory->add_factory_item<::nano::graphics::font>();
//   pfactory->add_factory_item<::nano::graphics::brush>();
//   pfactory->add_factory_item<::nano::graphics::pen>();

}



