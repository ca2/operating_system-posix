#pragma once


#include "aura_posix/_.h"
#include "windowing_kde6/_.h"


#if defined(_node_kde6_project)
   #define CLASS_DECL_NODE_KDE6  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_KDE6  CLASS_DECL_IMPORT
#endif


namespace node_kde6
{


   class node;


} // namespace node_kde6



