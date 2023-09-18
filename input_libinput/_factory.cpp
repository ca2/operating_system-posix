#include "framework.h"
//#include "text_composition_client.h"
//#include "buffer.h"
//#include "display.h"
#include "input.h"
//#include "windowing.h"
//#include "text_composition_client.h"
//#include "icon.h"
//#include "cursor.h"
//#include "keyboard.h"
//#include "aura/windowing/monitor.h"


__FACTORY_EXPORT void input_libinput_factory(::factory::factory * pfactory)
{

   printf("input_libinput factory\n");

   pfactory->add_factory_item < ::input_libinput::input, ::input::input > ();

//   pfactory->add_factory_item < ::windowing_x11::display, ::windowing::display > ();
//   pfactory->add_factory_item < ::windowing_x11::window, ::windowing::window > ();
//   pfactory->add_factory_item < ::windowing_x11::windowing, ::windowing::windowing > ();
//   pfactory->add_factory_item < ::windowing_x11::text_composition_client, ::user::text_composition_client > ();
//
//   pfactory->add_factory_item < ::windowing_x11::icon, ::windowing::icon > ();
//   pfactory->add_factory_item < ::windowing_x11::cursor, ::windowing::cursor > ();
//   pfactory->add_factory_item < ::windowing_x11::keyboard, ::windowing::keyboard > ();
//
//   pfactory->add_factory_item < ::windowing::monitor > ();


}



