#include "framework.h"
#include "node.h"
#include "shell.h"


#ifdef FREEBSD
#include <stdio.h>
#endif


__FACTORY_EXPORT void aura_posix_factory(::factory::factory * pfactory)
{

   printf("aura_posix factory\n");

   pfactory->add_factory_item < ::aura_posix::node    , ::acme::node > ();
   pfactory->add_factory_item < ::aura_posix::shell   , ::user::shell > ();

}



