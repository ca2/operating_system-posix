#pragma once


#include "acme_windows/_.h"


#if defined(_accessibility_windows_project)
#define CLASS_DECL_ACCESSIBILITY_POSIX  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACCESSIBILITY_POSIX  CLASS_DECL_IMPORT
#endif


namespace accessibility_posix
{


   class accessibility;


   class application;

   class main_window;


} // namespace acme_windows



