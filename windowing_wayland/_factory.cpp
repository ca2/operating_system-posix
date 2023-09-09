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


__FACTORY_EXPORT void windowing_wayland_factory(::factory::factory * pfactory)
{

   printf("windowing_wayland factory\n");

   pfactory->add_factory_item < ::windowing_wayland::buffer, ::graphics::graphics > ();

   pfactory->add_factory_item < ::windowing_wayland::display, ::windowing::display > ();
   pfactory->add_factory_item < ::windowing_wayland::window, ::windowing::window > ();
   pfactory->add_factory_item < ::windowing_wayland::windowing, ::windowing::windowing > ();
   pfactory->add_factory_item < ::windowing_wayland::text_composition_client, ::user::text_composition_client > ();

   pfactory->add_factory_item < ::windowing_wayland::icon, ::windowing::icon > ();
   pfactory->add_factory_item < ::windowing_wayland::cursor, ::windowing::cursor > ();
   pfactory->add_factory_item < ::windowing_wayland::keyboard, ::windowing::keyboard > ();

   pfactory->add_factory_item < ::windowing::monitor > ();


}



