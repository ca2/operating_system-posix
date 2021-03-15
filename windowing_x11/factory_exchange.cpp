#include "framework.h"
#include "text_composition_client.h"




extern "C"
void windowing_x11_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::windowing_x11::buffer, ::graphics::graphics > ();

   pfactorymap->create_factory < ::windowing_x11::display, ::windowing::display > ();
   pfactorymap->create_factory < ::windowing_x11::window, ::windowing::window > ();
   pfactorymap->create_factory < ::windowing_x11::windowing, ::windowing::windowing > ();
   pfactorymap->create_factory < ::windowing_x11::text_composition_client, ::user::text_composition_client > ();

}



