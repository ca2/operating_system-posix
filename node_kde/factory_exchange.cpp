#include "framework.h"
#include "_node_kde.h"
#include "monitor.h"
//#include "display.h"
#include "windowing.h"


extern "C"
void windowing_xcb_factory_exchange(::factory_map * pfactorymap);


extern "C"
void node_kde_factory_exchange(::factory_map * pfactorymap)
{

   windowing_xcb_factory_exchange(pfactorymap);

   pfactorymap->create_factory < ::node_kde::display, ::windowing::display > ();

   pfactorymap->create_factory < ::node_kde::node, ::acme::node > ();
   pfactorymap->create_factory < ::node_kde::monitor, ::windowing::monitor > ();
   pfactorymap->create_factory < ::node_kde::copydesk, ::user::copydesk > ();
   pfactorymap->create_factory < ::node_kde::notify_icon, ::user::notify_icon > ();
   pfactorymap->create_factory < ::node_kde::appindicator, ::aura::posix::appindicator >();

   pfactorymap->create_factory < ::node_kde::windowing, ::windowing::windowing >();


}



