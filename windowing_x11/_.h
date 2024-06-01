#pragma once


#include "aura_posix/_.h"
#include "windowing_posix/_.h"
#include "windowing_system_x11/_.h"
#include "nano_user_x11/_.h"


#if defined(_windowing_x11_project)
   #define CLASS_DECL_WINDOWING_X11  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_X11  CLASS_DECL_IMPORT
#endif


namespace windowing_x11
{


   class windowing;
   class display;
   class window;
   class x11data;


   using WINDOW = long;


   using window_map = map < WINDOW, ::pointer< window > >;


} // namespace node_gnome

