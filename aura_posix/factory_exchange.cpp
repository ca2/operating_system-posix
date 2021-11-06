#include "framework.h"


extern "C"
void aura_posix_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::aura::posix::node, ::acme::node > ();
   pfactorymap->create_factory < ::aura::posix::shell, ::user::shell > ();

}



