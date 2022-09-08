// Changed by camilo on 2021-12-09 13:40 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "windowing_x11/_.h"


#include <gtk/gtk.h>
#include <gdk/gdkx.h>


#include "gdk_gdk.h"


#include "gtk_gtk.h"


#if defined(_NODE_GTK_LIBRARY)
   #define CLASS_DECL_NODE_GTK  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_GTK  CLASS_DECL_IMPORT
#endif



namespace node_gtk
{


   class node;


} // namespace node_gtk


#define __matter(TYPE) __new(::matter<TYPE>)


//#include "gtk.h"

