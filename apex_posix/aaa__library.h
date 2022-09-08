//
// Created by camilo on 29/04/2021 01:37 BRT <3ThomasBorregaardSoerensen!!
//
#pragma once


#include "apex/operating_system.h"
#include "acme_posix/_library.h"


#include "file_context.h"


#include "os_context.h"


//#ifdef FILE_SYSTEM_INOTIFY
//#include "inotify/file_os_watcher.h"
//#endif


#ifdef POSIX_SPAWN
#include "posix_spawn/process.h"
#endif


#include "node.h"



