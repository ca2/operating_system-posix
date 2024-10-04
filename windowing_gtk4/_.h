#pragma once


#include "windowing_posix/_.h"
#include "nano_user_gtk4/_.h"


#if defined(_windowing_gtk4_project)
   #define CLASS_DECL_WINDOWING_GTK4  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_GTK4  CLASS_DECL_IMPORT
#endif


namespace windowing_gtk4
{


   class windowing;
   class display;
   class window;
   class x11data;


   using WINDOW = long;


} // namespace node_gnome


#include "nano_user_wayland/_.h"



