#include "framework.h"


extern "C"
void windowing_x11_factory_exchange(::factory_map * pfactorymap);


extern "C"
void node_xfce_factory_exchange(::factory_map * pfactorymap)
{

   windowing_x11_factory_exchange(pfactorymap);

   pfactorymap->create_factory < ::node_xfce::display, ::windowing::display > ();

   pfactorymap->create_factory < ::node_xfce::node, ::acme::node > ();
   pfactorymap->create_factory < ::node_xfce::monitor, ::windowing::monitor > ();
   pfactorymap->create_factory < ::node_xfce::copydesk, ::user::copydesk > ();
   pfactorymap->create_factory < ::node_xfce::notify_icon, ::user::notify_icon > ();
   pfactorymap->create_factory < ::node_xfce::appindicator, ::aura::posix::appindicator >();

   pfactorymap->create_factory < ::node_xfce::windowing, ::windowing::windowing >();

}



