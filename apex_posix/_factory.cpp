#include "framework.h"

#include "file_context.h"
#if defined(INTERPROCESS_COMMUNICATION_SYSTEM_5)
#include "system_5/interprocess_communication.h"
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


#if defined(INTERPROCESS_COMMUNICATION_SYSTEM_5)

   pfactory->add_factory_item < ::system_5::interprocess_communication_base, ::interprocess_communication::base >();
   pfactory->add_factory_item < ::system_5::interprocess_communication_rx, ::interprocess_communication::rx >();
   pfactory->add_factory_item < ::system_5::interprocess_communication_tx, ::interprocess_communication::tx >();

#endif


#if defined(POSIX_SPAWN)

   pfactory->add_factory_item < ::ansios::process, ::operating_system::process >();

#endif


   pfactory->add_factory_item < ::apex_posix::node, ::acme::node > ();

   pfactory->add_factory_item < ::apex_posix::file_context, ::file_context >();

   pfactory->add_factory_item < ::apex_posix::os_context, ::os_context >();

}



