// Changed by camilo on 2021-12-09 13:40 BRT <3ThomasBorregaardSorensen!!
#pragma once


//#include "windowing_wayland/_.h"
//#include "windowing_x11/_.h"


#include <gtk/gtk.h>
//#include <gdk/gdkx.h>
//#include <gio/gio.h>
//#include <gdk/gdk.h>

#include "gdk.h"


//#include "gtk3_gtk3.h"


#if defined(_node_gdk_project)
   #define CLASS_DECL_NODE_GDK  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_GDK  CLASS_DECL_IMPORT
#endif



namespace node_gdk
{


   class node;

   class windowing_system;


} // namespace node_gdk


//#define __matter(TYPE) øallocate< ::matter<TYPE> >()


//#include "gtk.h"


