#include "framework.h"
#include "node.h"
#include "file.h"
#include "file_context.h"
#include "file_memory_map.h"
#include "pipe.h"
#include "directory_system.h"
#include "file_system.h"
#include "path_system.h"
#include "mutex.h"
#include "exception_translator.h"
//#include "environment.h"

#include <stdio.h>


IMPLEMENT_FACTORY(acme_posix)
{

   //printf("acme_posix factory\n");

   pfactory->add_factory_item < ::acme_posix::node                   , ::platform::node > ();
   pfactory->add_factory_item < ::acme_posix::file_memory_map        , ::file::memory_map >();

   pfactory->add_factory_item < ::acme_posix::pipe                   , ::operating_system::pipe >();

   pfactory->add_factory_item < ::acme_posix::directory_system         , ::directory_system >();
   pfactory->add_factory_item < ::acme_posix::file_system              , ::file_system >();
   pfactory->add_factory_item < ::acme_posix::path_system              , ::path_system >();

   
   pfactory->add_factory_item < ::acme_posix::file_context, ::file_context >();



   pfactory->add_factory_item < ::acme_posix::file,                  ::file::file >();


   pfactory->add_factory_item < ::acme_posix::exception_translator   , ::exception_translator >();


   pfactory->add_factory_item < ::acme_posix::mutex                  , ::mutex >();


//   pfactory->add_factory_item < ::acme_posix::environment            , ::operating_system::environment >();

}



