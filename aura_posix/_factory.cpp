#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


__FACTORY_EXPORT void aura_posix_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::aura_posix::node    , ::acme::node > ();
   pfactory->add_factory_item < ::aura_posix::shell   , ::user::shell > ();

}



