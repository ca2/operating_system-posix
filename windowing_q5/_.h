#pragma once


#include "acme_windowing_q5/_.h"
#include "windowing_q/_.h"


#if defined(_windowing_q5_project)
   #define CLASS_DECL_WINDOWING_Q5  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_Q5  CLASS_DECL_IMPORT
#endif


namespace windowing_q5
{


   class windowing;
   class display;
   class window;


} // namespace node_gnome



