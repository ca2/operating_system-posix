#pragma once


#include "aura_posix/_.h"


#if defined(_WINDOWING_X11_LIBRARY)
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

