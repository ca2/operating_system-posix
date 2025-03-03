#pragma once


#include "aura_posix/_.h"
#include "windowing_q/_.h"


#if defined(_node_q_project)
   #define CLASS_DECL_NODE_Q  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_Q  CLASS_DECL_IMPORT
#endif


namespace node_q
{


   class node;

} // namespace node_q



