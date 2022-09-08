#pragma once


#include "node_gtk/_.h"


#if defined(_NODE_GNOME_LIBRARY)
   #define CLASS_DECL_NODE_GNOME  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_GNOME  CLASS_DECL_IMPORT
#endif


namespace node_gnome
{


   class node;


} // namespace node_gnome


#include "_constant.h"


#define __matter(TYPE) __new(::matter<TYPE>)


namespace user
{


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);


}


