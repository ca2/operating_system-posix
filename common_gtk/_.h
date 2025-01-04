// Changed by camilo on 2024-12-20 16:00 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/_.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>


#if defined(_common_gtk_project)
   #define CLASS_DECL_COMMON_GTK  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_COMMON_GTK  CLASS_DECL_IMPORT
#endif



