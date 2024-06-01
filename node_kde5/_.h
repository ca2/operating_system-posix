#pragma once


#include "aura_posix/_.h"
#include "nano_user_x11/_.h"
#include "windowing_system_xcb/_.h"
#include "windowing_system_wayland/_.h"
#include <QMetaType>


#if defined(_node_kde_project)
   #define CLASS_DECL_NODE_KDE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_KDE  CLASS_DECL_IMPORT
#endif


namespace node_kde5
{


   class node;


} // namespace node_kde5



