#pragma once


#include "apex/_.h"
#include "apex/operating_system.h"
#include "acme_posix/_.h"


#if defined(_NODE_ANSIOS_LIBRARY)
   #define CLASS_DECL_NODE_ANSIOS  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_ANSIOS  CLASS_DECL_IMPORT
#endif


namespace node_ansios
{


   class node;


} // namespace node_gnome


#include "file_os_watcher.h"


#include "node.h"



