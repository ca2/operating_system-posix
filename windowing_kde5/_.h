#pragma once


#include "acme_windowing_kde5/_.h"
#include "windowing_q5/_.h"


#if defined(_windowing_kde5_project)
   #define CLASS_DECL_WINDOWING_KDE5  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_KDE5  CLASS_DECL_IMPORT
#endif


namespace windowing_kde5
{


   class windowing;
   class display;
   class window;
   //class x11data;


   //using WINDOW = long;


} // namespace node_gnome


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
