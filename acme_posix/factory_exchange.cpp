#include "framework.h"


extern "C"
void acme_posix_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::acme::posix::node, ::acme::node > ();
   pfactorymap->create_factory < ::posix::file_memory_map, ::file::memory_map >();

   pfactorymap->create_factory < ::posix::pipe , ::operating_system::pipe          >();


   pfactorymap->create_factory < ::posix::acme_dir , ::acme_dir          >();
   pfactorymap->create_factory < ::posix::acme_file , ::acme_file          >();
   pfactorymap->create_factory < ::posix::acme_path , ::acme_path          >();

}



