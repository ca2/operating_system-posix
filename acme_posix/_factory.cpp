#include "framework.h"
#if defined(INTERPROCESS_COMMUNICATION_SYSTEM_V)
#include "system_v/interprocess_communication.h"
#endif

__FACTORY_EXPORT void acme_posix_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::acme::posix::node, ::acme::node > ();
   pfactory->add_factory_item < ::posix::file_memory_map, ::file::memory_map >();

   pfactory->add_factory_item < ::posix::pipe , ::operating_system::pipe          >();


   pfactory->add_factory_item < ::posix::acme_dir , ::acme_dir          >();
   pfactory->add_factory_item < ::posix::acme_file , ::acme_file          >();
   pfactory->add_factory_item < ::posix::acme_path , ::acme_path          >();


}



