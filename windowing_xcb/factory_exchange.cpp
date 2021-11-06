#include "framework.h"
#include "text_composition_client.h"
#include "keyboard.h"


extern "C"
void windowing_xcb_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::windowing_xcb::buffer, ::graphics::graphics > ();

   pfactorymap->create_factory < ::windowing_xcb::display, ::windowing::display > ();
   pfactorymap->create_factory < ::windowing_xcb::window, ::windowing::window > ();
   pfactorymap->create_factory < ::windowing_xcb::windowing, ::windowing::windowing > ();
   pfactorymap->create_factory < ::windowing_xcb::text_composition_client, ::user::text_composition_client > ();

   pfactorymap->create_factory < ::windowing_xcb::icon, ::windowing::icon > ();
   pfactorymap->create_factory < ::windowing_xcb::cursor, ::windowing::cursor > ();
   pfactorymap->create_factory < ::windowing_xcb::keyboard, ::windowing::keyboard > ();

}



