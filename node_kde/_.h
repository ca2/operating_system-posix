#pragma once


#include "aura_posix/_.h"
#include <QMetaType>


#if defined(_node_kde_project)
   #define CLASS_DECL_NODE_KDE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_KDE  CLASS_DECL_IMPORT
#endif


namespace node_kde
{


   class node;


} // namespace node_kde



