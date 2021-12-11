#include "framework.h"
#include "file_context.h"
#if defined(INTERPROCESS_COMMUNICATION_SYSTEM_V)
#include "system_v/interprocess_communication.h"
#endif

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


#if defined(INTERPROCESS_COMMUNICATION_SYSTEM_V)

   pfactory->add_factory_item < ::system_v::interprocess_communication_base, ::interprocess_communication::base >();
   pfactory->add_factory_item < ::system_v::interprocess_communication_rx, ::interprocess_communication::rx >();
   pfactory->add_factory_item < ::system_v::interprocess_communication_tx, ::interprocess_communication::tx >();


   ***test***

#endif



   pfactory->add_factory_item < ::apex::posix::node, ::acme::node > ();

   pfactory->add_factory_item < ::posix::file_context, ::file_context >();

}



