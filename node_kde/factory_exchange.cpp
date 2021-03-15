#include "framework.h"


extern "C"
void windowing_xcb_factory_exchange(::factory_map * pfactorymap);



extern "C"
void node_kde_factory_exchange(::factory_map * pfactorymap)
{

   windowing_xcb_factory_exchange(pfactorymap);

   create_factory < ::node_kde::node, ::acme::node > ();
   create_factory < ::node_kde::copydesk, ::user::copydesk > ();
   pfactorymap->create_factory < ::node_kde::appindicator, ::node_linux::appindicator >();

}



