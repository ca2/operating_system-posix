// Changed by camilo on 2021-12-09 13:44 BRT <3ThomasBorregaardSorensen!!
#pragma once


//::e_status os_defer_init_gtk(::acme::system * psystem);


typedef enum
{

   WALLPAPER_ALIGN_TILED     = 0,
   WALLPAPER_ALIGN_CENTERED  = 1,
   WALLPAPER_ALIGN_STRETCHED = 2,
   WALLPAPER_ALIGN_SCALED    = 3,
   WALLPAPER_NONE            = 4

} WallpaperAlign;


bool gconf_set_as_wallpaper( const char *image_path, WallpaperAlign align );


namespace node_gtk
{

   ::e_status os_defer_init_gtk(::acme::system * psystem);



} // namespace node_gtk



