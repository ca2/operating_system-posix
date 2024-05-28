#include "framework.h"
///#include "speech.h"


__FACTORY_EXPORT void windowing_system_wayland_factory(::factory::factory * pfactory);

IMPLEMENT_FACTORY(nano_user_wayland)
{




   windowing_system_wayland_factory(pfactory);






   //ssspfactory->add_factory_item < ::sapi::nano::speech::speech, ::nano::speech::speech >();

}



