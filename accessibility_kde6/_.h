#pragma once


#include "operating_system-posix/accessibility_posix/_.h"
#include "axis/_.h"


#if defined(_accessibility_kde6_project)
#define CLASS_DECL_ACCESSIBILITY_KDE6 CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACCESSIBILITY_KDE6 CLASS_DECL_IMPORT
#endif


namespace accessibility_kde6
{


   class accessibility;
   class application;
   class main_window;


} // namespace accessibility_kde6
