#pragma once


#include "aura_posix/_.h"
//#include "nano_user_x11/_.h"
//#include "windowing_system_xcb/_.h"
//#include "windowing_system_wayland/_.h"
#include "acme_windowing_kde5/_.h"
#include <QMetaType>


#if defined(_node_kde5_project)
   #define CLASS_DECL_NODE_KDE5  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_KDE5  CLASS_DECL_IMPORT
#endif


namespace node_kde5
{


   class node;


} // namespace node_kde5



