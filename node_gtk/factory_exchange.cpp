#include "framework.h"


extern "C"
void windowing_x11_factory_exchange(::factory_map * pfactorymap);


extern "C"
void node_gtk_factory_exchange(::factory_map * pfactorymap)
{

   windowing_x11_factory_exchange(pfactorymap);

//   pfactorymap->create_factory < ::node_gtk::display, ::windowing::display > ();
//
//   pfactorymap->create_factory < ::node_gtk::monitor, ::windowing::monitor > ();
//   pfactorymap->create_factory < ::node_gtk::copydesk, ::user::copydesk > ();
//   pfactorymap->create_factory < ::node_gtk::notify_icon, ::user::notify_icon > ();
//   pfactorymap->create_factory < ::node_gtk::appindicator, ::aura::posix::appindicator >();
//
//   pfactorymap->create_factory < ::node_gtk::windowing, ::windowing::windowing >();

   pfactorymap->create_factory < ::node_gtk::node, ::acme::node > ();


}



