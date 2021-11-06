#pragma once


#include "node_gtk/_.h"


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


