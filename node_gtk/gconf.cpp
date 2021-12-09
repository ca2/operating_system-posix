//
// Created by camilo on 09/12/2021 12:36 BRT <3ThomasBorregaardSorensen!!
//
#include "framework.h"
// bkgmanage.c
#include <glib.h>
#include <gconf/gconf-client.h>
#include <stdio.h>


bool gconf_set_as_wallpaper( const char *image_path, WallpaperAlign align )
{

   GConfClient *client;

   char        *options = "none";

   client = gconf_client_get_default();

   // TODO: проверить, что image_path является файлом и вообще существует
   if ( image_path == NULL ) options = "none";
   else {
      gconf_client_set_string( client,
                               "/desktop/gnome/background/picture_filename",
                               image_path,
                               NULL );

      switch ( align ) {
         case WALLPAPER_ALIGN_TILED: options = "wallpaper"; break;
         case WALLPAPER_ALIGN_CENTERED: options = "centered"; break;
         case WALLPAPER_ALIGN_STRETCHED: options = "stretched"; break;
         case WALLPAPER_ALIGN_SCALED: options = "scaled"; break;
         case WALLPAPER_NONE: options = "none"; break;
      }
   }

   gboolean result = gconf_client_set_string( client,
                                              "/desktop/gnome/background/picture_options",
                                              options,
                                              NULL);
   g_object_unref( G_OBJECT(client) );

   return result;
}

//int main(int argc, const char* argv[])
//{
//   if ( argc > 1 ) {
//      printf( "Setting %s as wallpaper... ", argv[1] );
//      if ( set_as_wallpaper( argv[1], WALLPAPER_ALIGN_STRETCHED ) ) printf( "Ok\n" );
//      else printf( "Failed\n" );
//   } else printf( "Usage: ./bkgmanage <filename>\n" );
//
//   return 0;
//}