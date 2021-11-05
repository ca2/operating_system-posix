#include "framework.h"


extern "C"
void node_gtk_factory_exchange(::factory_map * pfactorymap);


extern "C"
void node_gnome_factory_exchange(::factory_map * pfactorymap)
{

   node_gtk_factory_exchange(pfactorymap);

   pfactorymap->create_factory < ::node_gnome::display, ::windowing::display > ();

   pfactorymap->create_factory < ::node_gnome::monitor, ::windowing::monitor > ();
   pfactorymap->create_factory < ::node_gnome::copydesk, ::user::copydesk > ();
   pfactorymap->create_factory < ::node_gnome::notify_icon, ::user::notify_icon > ();
   pfactorymap->create_factory < ::node_gnome::appindicator, ::aura::posix::appindicator >();

   pfactorymap->create_factory < ::node_gnome::windowing, ::windowing::windowing >();

   pfactorymap->create_factory < ::node_gnome::node, ::acme::node > ();


}



