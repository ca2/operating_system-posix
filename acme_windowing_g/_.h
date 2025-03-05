// Changed by camilo on 2024-12-20 16:00 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/_.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>


#if defined(_acme_windowing_g_project)
   #define CLASS_DECL_ACME_WINDOWING_G CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_ACME_WINDOWING_G CLASS_DECL_IMPORT
#endif


namespace g
{

   namespace acme
   {


      namespace windowing
      {

         class display;

      }


   }



}
