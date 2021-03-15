#pragma once


#include "node_ansios/_.h"
#include "aura/_.h"


#if defined(_NODE_LINUX_LIBRARY)
   #define CLASS_DECL_NODE_LINUX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_LINUX  CLASS_DECL_IMPORT
#endif


namespace node_linux
{

   class node;


} // namespace node_gnome



#include "appindicator.h"


#include "node.h"


#include "factory_exchange.h"





