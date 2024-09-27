#include "framework.h"
///#include "speech.h"
#include "window.h"
#include "acme/nano/user/user.h"
//void operating_system_initialize_gtk4_nano_user(::factory::factory * pfactory);
__FACTORY_EXPORT void windowing_system_gtk4_factory(::factory::factory * pfactory);
//__FACTORY_EXPORT void nano_user_cairo_factory(::factory::factory * pfactory);

IMPLEMENT_FACTORY(nano_user_gtk4)
{


   //nano_user_cairo_factory(pfactory);

   windowing_system_gtk4_factory(pfactory);

   //operating_system_initialize_gtk4_nano_user(pfactory);


   //operating_system_initialize_cairo_nano(pfactory);

   pfactory->add_factory_item<::gtk4::nano::user::window, ::windowing::window_base>();
   pfactory->add_factory_item<::nano::user::user>();
   //pfactory->add_factory_item<::gtk4::nano::graphics::icon, ::nano::graphics::icon>();

   //::wayland::display::get(pfactory);


   //ssspfactory->add_factory_item < ::sapi::nano::speech::speech, ::nano::speech::speech >();

}



