#include "framework.h"
//#include "file_os_watcher.h"
#include "file_context.h"

#ifdef FILE_SYSTEM_INOTIFY

#include "inotify/watcher.h"

#endif

__FACTORY_EXPORT void acme_posix_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_posix_factory(::factory::factory * pfactory)
{

   acme_posix_factory(pfactory);

#ifdef FILE_SYSTEM_INOTIFY
   
   pfactory->add_factory_item < ::inotify::watcher, ::file::watcher >();
   pfactory->add_factory_item < ::inotify::watch, ::file::watch >();

#endif

   pfactory->add_factory_item < ::apex::posix::node, ::acme::node > ();

   pfactory->add_factory_item < ::posix::file_context, ::file_context >();

}



