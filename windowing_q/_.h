#pragma once


#include "acme_windowing_q/_.h"
#include "windowing_posix/_.h"


#if defined(_windowing_q_project)
   #define CLASS_DECL_WINDOWING_Q  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_Q  CLASS_DECL_IMPORT
#endif


namespace windowing_q
{


   class windowing;
   class display;
   class window;


} // namespace windowing_q



