#include "framework.h"
///#include "speech.h"

void operating_system_initialize_gtk4_nano_user(::factory::factory * pfactory);
__FACTORY_EXPORT void windowing_system_gtk4_factory(::factory::factory * pfactory);
__FACTORY_EXPORT void nano_user_cairo_factory(::factory::factory * pfactory);

IMPLEMENT_FACTORY(nano_user_gtk4)
{


   nano_user_cairo_factory(pfactory);

   windowing_system_gtk4_factory(pfactory);

   operating_system_initialize_gtk4_nano_user(pfactory);




   //ssspfactory->add_factory_item < ::sapi::nano::speech::speech, ::nano::speech::speech >();

}



