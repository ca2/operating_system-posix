#pragma once


#include "acme_windowing_q6/_.h"
#include "windowing_q/_.h"


#if defined(_windowing_q6_project)
   #define CLASS_DECL_WINDOWING_Q6  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_Q6  CLASS_DECL_IMPORT
#endif


namespace windowing_q6
{


   class windowing;
   class display;
   class window;
   //class x11data;


   //using WINDOW = long;


} // namespace windowing_q6


//#include "nano_user_wayland/_.h"
//
// #include <QRect>
//
//
// inline void copy(::int_rectangle & rectangleTarget, const QRect & qrect)
// {
//
//    rectangleTarget.left = qrect.x();
//    rectangleTarget.right = qrect.x() + qrect.width();
//    rectangleTarget.top = qrect.y();
//    rectangleTarget.bottom = qrect.y() + qrect.height();
//
// }
//
//
//
