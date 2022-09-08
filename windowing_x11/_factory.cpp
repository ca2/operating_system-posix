#include "framework.h"
#include "text_composition_client.h"
#include "buffer.h"
#include "display.h"
#include "window.h"
#include "windowing.h"
#include "text_composition_client.h"
#include "icon.h"
#include "cursor.h"
#include "keyboard.h"
#include "aura/windowing/monitor.h"


__FACTORY_EXPORT void windowing_x11_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::windowing_x11::buffer, ::graphics::graphics > ();

   pfactory->add_factory_item < ::windowing_x11::display, ::windowing::display > ();
   pfactory->add_factory_item < ::windowing_x11::window, ::windowing::window > ();
   pfactory->add_factory_item < ::windowing_x11::windowing, ::windowing::windowing > ();
   pfactory->add_factory_item < ::windowing_x11::text_composition_client, ::user::text_composition_client > ();

   pfactory->add_factory_item < ::windowing_x11::icon, ::windowing::icon > ();
   pfactory->add_factory_item < ::windowing_x11::cursor, ::windowing::cursor > ();
   pfactory->add_factory_item < ::windowing_x11::keyboard, ::windowing::keyboard > ();

   pfactory->add_factory_item < ::windowing::monitor > ();


}



