#include "acme/_start.h"
#include "acme/_.h"
#include "backend.h"
IMPLEMENT_FACTORY(acme_windowing_wayland)
{
   pfactory->add_factory_item<::native_wayland::display, ::acme::windowing::display>();
   pfactory->add_factory_item<::native_wayland::window, ::acme::windowing::window>();
   pfactory->add_factory_item<::native_wayland::windowing, ::acme::windowing::windowing>();
}
