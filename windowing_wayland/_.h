#pragma once


#include "aura_posix/_.h"


#if defined(_windowing_wayland_project)
   #define CLASS_DECL_WINDOWING_WAYLAND  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_WAYLAND  CLASS_DECL_IMPORT
#endif


namespace windowing_wayland
{


   class windowing;
   class display;
   class window;
   class x11data;


   using WINDOW = long;


} // namespace node_gnome


#include "nano_user_wayland/_.h"



