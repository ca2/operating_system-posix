// Changed by camilo on 2024-12-20 16:00 BRT <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/_.h"


#if defined(_gnome_library_project)
   #define CLASS_DECL_GNOME_LIBRARY CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_GNOME_LIBRARY CLASS_DECL_IMPORT
#endif


namespace gnome_library
{


   class file;


   class gnome_library;


}
