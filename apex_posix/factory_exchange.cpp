#include "framework.h"
//#include "file_os_watcher.h"
#include "file_context.h"

#ifdef FILE_SYSTEM_INOTIFY

#include "inotify/watcher.h"

#endif

extern "C"
void acme_posix_factory_exchange(::factory_map * pfactorymap);


extern "C"
void apex_posix_factory_exchange(::factory_map * pfactorymap)
{

   acme_posix_factory_exchange(pfactorymap);

#ifdef FILE_SYSTEM_INOTIFY
   
   pfactorymap->create_factory < ::inotify::watcher, ::file::watcher >();
   pfactorymap->create_factory < ::inotify::watch, ::file::watch >();

#endif

   pfactorymap->create_factory < ::apex::posix::node, ::acme::node > ();

   pfactorymap->create_factory < ::posix::file_context, ::file_context >();

}



