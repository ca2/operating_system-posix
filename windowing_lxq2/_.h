#pragma once


#include "windowing_posix/_.h"
//#include "windowing_system_wayland/_.h"
#include "acme_windowing_lxq2/_.h"


#if defined(_windowing_lxq2_project)
   #define CLASS_DECL_WINDOWING_LXQ2  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_LXQ2  CLASS_DECL_IMPORT
#endif


namespace windowing_lxq2
{


   class windowing;
   class display;
   class window;
   //class x11data;


   //using WINDOW = long;


} // namespace windowing_lxq2


//#include "nano_user_wayland/_.h"
//
// #include <QRect>
//
//
// inline void copy(::int_rectangle & rectangleTarget, const QRect & qrect)
// {
//
//    rectangleTarget.left() = qrect.x();
//    rectangleTarget.right() = qrect.x() + qrect.width();
//    rectangleTarget.top() = qrect.y();
//    rectangleTarget.bottom() = qrect.y() + qrect.height();
//
// }
//
//
//
