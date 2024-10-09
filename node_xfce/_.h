#pragma once


#include "node_gtk3/_.h"


#if defined(_node_xfce_project)
   #define CLASS_DECL_NODE_XFCE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_XFCE  CLASS_DECL_IMPORT
#endif


namespace node_xfce
{


   class node;


} // namespace node_xfce


#define __matter(TYPE) ::as(new ::matter<TYPE>()


namespace user
{


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);


}


