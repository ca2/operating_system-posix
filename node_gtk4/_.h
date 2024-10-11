// Changed by camilo on 2021-12-09 13:40 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "windowing_gtk4/_.h"


#include <gtk/gtk.h>
//#include <gdk/gdk.h>


//#include "gdk_gdk.h"


#include "gtk4_gtk4.h"


#if defined(_node_gtk4_project)
   #define CLASS_DECL_NODE_GTK4  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_GTK4  CLASS_DECL_IMPORT
#endif



namespace node_gtk4
{


   class node;


} // namespace node_gtk4


//#define __matter(TYPE) ::place(__new< ::matter<TYPE> >())


//#include "gtk.h"

inline void copy(::rectangle_i32 * prectTarget, const GdkRectangle * prectSource)
{

   prectTarget->left() = prectSource->x;
   prectTarget->top() = prectSource->y;
   prectTarget->right() = prectSource->x + prectSource->width;
   prectTarget->bottom() = prectSource->y + prectSource->height;

}


