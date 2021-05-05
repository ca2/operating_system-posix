#pragma once


#include "windowing_xcb/_.h"


#if defined(_NODE_KDE_LIBRARY)
   #define CLASS_DECL_NODE_KDE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_KDE  CLASS_DECL_IMPORT
#endif


namespace node_kde
{


   class node;


} // namespace node_kde



