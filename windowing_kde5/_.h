#pragma once


#include "windowing_posix/_.h"
//#include "windowing_system_wayland/_.h"
//#include "nano_user_wayland/_.h"


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
   class x11data;


   using WINDOW = long;


} // namespace node_gnome


#include "nano_user_wayland/_.h"

#include <QRect>


inline void copy(::rectangle_i32 & rectangleTarget, const QRect & qrect)
{

   rectangleTarget.left() = qrect.x();
   rectangleTarget.right() = qrect.x() + qrect.width();
   rectangleTarget.top() = qrect.y();
   rectangleTarget.bottom() = qrect.y() + qrect.height();

}



