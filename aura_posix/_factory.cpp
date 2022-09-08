#include "framework.h"
#include "node.h"
#include "shell.h"


__FACTORY_EXPORT void aura_posix_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::aura_posix::node    , ::acme::node > ();
   pfactory->add_factory_item < ::aura_posix::shell   , ::user::shell > ();

}



