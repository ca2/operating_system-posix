#include "framework.h"
//#include "file_context.h"
//#include "os_context.h"
#include "node.h"
#include "posix_spawn/process.h"
#if defined(INTERPROCESS_COMMUNICATION_SYSTEM_5)
#include "system_5/interprocess_caller.h"
#include "system_5/interprocess_target.h"
#endif

#if defined(__APPLE__) || defined(__BSD__)
#include <stdio.h>
#endif

#ifdef FILE_SYSTEM_INOTIFY

#include "inotify/watch.h"
#include "inotify/watcher.h"

#endif

__FACTORY_EXPORT void acme_posix_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void apex_posix_factory(::factory::factory * pfactory)
{

   acme_posix_factory(pfactory);

   printf("apex_posix factory\n");

#ifdef FILE_SYSTEM_INOTIFY
   
   pfactory->add_factory_item < ::inotify::watcher, ::file::watcher >();
   pfactory->add_factory_item < ::inotify::watch, ::file::watch >();

#endif


#if defined(INTERPROCESS_COMMUNICATION_SYSTEM_5)

   pfactory->add_factory_item < ::system_5::interprocess_base, ::interprocess::base >();
   pfactory->add_factory_item < ::system_5::interprocess_caller, ::interprocess::caller >();
   pfactory->add_factory_item < ::system_5::interprocess_target, ::interprocess::target >();

#endif


#if defined(POSIX_SPAWN)

   pfactory->add_factory_item < ::ansios::process, ::operating_system::process >();

#endif


   pfactory->add_factory_item < ::apex_posix::node, ::platform::node > ();

   //pfactory->add_factory_item < ::apex_posix::os_context, ::os_context >();

}



