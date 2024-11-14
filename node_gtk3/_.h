// Changed by camilo on 2021-12-09 13:40 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "windowing_gtk3/_.h"
//#include "node_gdk/_.h"
//#include "windowing_wayland/_.h"
//#include "windowing_x11/_.h"


#include <gtk/gtk.h>
#include <gdk/gdkx.h>


#include "gdk_gdk.h"


#include "gtk3_gtk3.h"


#if defined(_node_gtk3_project)
   #define CLASS_DECL_NODE_GTK3  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_GTK3  CLASS_DECL_IMPORT
#endif



namespace node_gtk3
{


   class node;


} // namespace node_gtk3


