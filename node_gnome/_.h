#pragma once


#include "windowing_x11/_.h"


#include <gtk/gtk.h>
#include <gdk/gdkx.h>


#if defined(_NODE_GNOME_LIBRARY)
   #define CLASS_DECL_NODE_GNOME  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_GNOME  CLASS_DECL_IMPORT
#endif


namespace node_gnome
{


   class node;


} // namespace node_gnome


#define __matter(TYPE) __new(::matter<TYPE>)


namespace user
{


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);


}


