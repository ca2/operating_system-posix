#pragma once


#include "acme_windowing_lxq1/_.h"
#include "windowing_q5/_.h"


#if defined(_windowing_lxq1_project)
   #define CLASS_DECL_WINDOWING_LXQ1  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_LXQ1  CLASS_DECL_IMPORT
#endif


namespace windowing_lxq1
{


   class windowing;
   class display;
   class window;


} // namespace windowing_lxq1



