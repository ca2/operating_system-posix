#include "framework.h"
#include "file_os_watcher.h"
#include "file_context.h"


extern "C"
void apex_posix_factory_exchange(::factory_map * pfactorymap)
{


   pfactorymap->create_factory < ::file::os_watcher, ::file::watcher >();
   pfactorymap->create_factory < ::file::os_watch, ::file::watch >();

   pfactorymap->create_factory < ::apex::posix::node, ::acme::node > ();

   pfactorymap->create_factory < ::posix::file_context, ::file_context >();

}



