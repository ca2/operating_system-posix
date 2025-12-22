// Changed by camilo on 2021-12-09 13:40 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "windowing_x11/_.h"


#if defined(_node_x11_project)
   #define CLASS_DECL_NODE_X11  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_X11  CLASS_DECL_IMPORT
#endif


namespace node_x11
{


   class node;


} // namespace node_x11



