#pragma once


#if defined(HAS_GTK4)
#include "node_gtk4/_.h"
#elif defined(HAS_GTK3)
#include "node_gtk3/_.h"
#endif


#if defined(_node_gnome_project)
   #define CLASS_DECL_NODE_GNOME  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_GNOME  CLASS_DECL_IMPORT
#endif


namespace node_gnome
{


   class node;


} // namespace node_gnome


#include "_constant.h"


#define __matter(TYPE) __allocate< ::matter<TYPE> >()


namespace user
{


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);


}


