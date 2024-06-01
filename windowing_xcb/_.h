#pragma once



#include "aura_posix/_.h"
#include "windowing_system_xcb/_.h"
#include "nano_user_xcb/_.h"


#if defined(_windowing_xcb_project)
   #define CLASS_DECL_WINDOWING_XCB  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_XCB  CLASS_DECL_IMPORT
#endif


namespace windowing_xcb
{


   class windowing;
   class display;
   class window;


   using XCB_WINDOW_T = long;


   using window_map = map < XCB_WINDOW_T , ::pointer<window > >;


} // namespace windowing_xcb



//extern ::particle * user_synchronization();


