#pragma once


#include "windowing_x11/_.h"


#include <gtk/gtk.h>
#include <gdk/gdkx.h>


#if defined(_NODE_XFCE_LIBRARY)
   #define CLASS_DECL_NODE_XFCE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_XFCE  CLASS_DECL_IMPORT
#endif


namespace node_xfce
{


   class node;


} // namespace node_xfce


#define __matter(TYPE) __new(::matter<TYPE>)


namespace user
{


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);


}


