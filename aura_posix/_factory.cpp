#include "framework.h"


__FACTORY_EXPORT void aura_posix_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::aura::posix::node, ::acme::node > ();
   pfactory->add_factory_item < ::aura::posix::shell, ::user::shell > ();

}



