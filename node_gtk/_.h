#pragma once


#include "windowing_x11/_.h"


#if defined(_NODE_GTK_LIBRARY)
   #define CLASS_DECL_NODE_GTK  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NODE_GTK  CLASS_DECL_IMPORT
#endif


namespace node_gtk
{


   class node;


} // namespace node_gtk


typedef enum {
   WALLPAPER_ALIGN_TILED     = 0,
   WALLPAPER_ALIGN_CENTERED  = 1,
   WALLPAPER_ALIGN_STRETCHED = 2,
   WALLPAPER_ALIGN_SCALED    = 3,
   WALLPAPER_NONE            = 4
} WallpaperAlign;


bool gconf_set_as_wallpaper( const char *image_path, WallpaperAlign align );

#define __matter(TYPE) __new(::matter<TYPE>)


namespace user
{


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);


   ::e_status gsettings_set(const ::string & strSchema, const ::string & strKey, const ::string & strValue);


} // namespace user



