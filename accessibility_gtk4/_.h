#pragma once


#include "axis/_.h"


#if defined(_accessibility_gtk4_project)
#define CLASS_DECL_ACCESSIBILITY_GTK4 CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACCESSIBILITY_GTK4 CLASS_DECL_IMPORT
#endif


namespace accessibility_gtk4
{


   class accessibility;
   class application;
   class main_window;


} // namespace accessibility_gtk4
