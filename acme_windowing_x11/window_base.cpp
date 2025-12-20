//
// Created by camilo on 2024-10-03 04:32 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window_base.h"
#include "_x11.h"


namespace x11
{


   namespace nano
   {


      namespace user
      {


         window_base::window_base()
         {


         }


         window_base::~window_base()
         {


         }


//         ::x11::acme::windowing::display_t * window_base::_x11_display()
//         {
//
//            if(!m_px11windowbasehandle)
//            {
//
//               return nullptr;
//
//            }
//
//            return m_px11windowbasehandle->_x11_display();
//
//         }


//         ::x11::micro::window_t  window_base::_x11_window()
//         {
//
//            if(!m_px11windowbasehandle)
//            {
//
//               return 0;
//
//            }
//
//            return m_px11windowbasehandle->_x11_window();
//
//         }


         void window_base::set_rectangle_unlocked(const ::int_rectangle & rectangle)
         {

            auto handle = _x11_handle();

            XMoveResizeWindow(
               __x11_handle(handle),
               rectangle.left,
               rectangle.top,
               rectangle.width(),
               rectangle.height());

         }


         void window_base::set_position_unlocked(const ::int_point & point)
         {

            auto handle = _x11_handle();

            XMoveWindow(__x11_handle(handle), point.x, point.y);

         }


         void window_base::set_size_unlocked(const ::int_size & size)
         {

            auto handle = _x11_handle();

            XResizeWindow(__x11_handle(handle), size.cx, size.cy);

         }


         ::int_rectangle window_base::get_window_rectangle_unlocked()
         {

            auto handle = _x11_handle();

            Window windowRoot = 0;

            int x = 0;

            int y = 0;

            unsigned int w = 0;

            unsigned int h = 0;

            unsigned int border = 0;

            unsigned int depth = 0;

            auto status = XGetGeometry(__x11_handle(handle),
               &windowRoot, &x, &y, &w,
                                       &h, &border, &depth);

            if (status == BadDrawable)
            {

               throw ::exception(error_exception);

            }

            ::int_rectangle rectangle;

            rectangle.left = x;
            rectangle.top = y;
            rectangle.right = x + w;
            rectangle.bottom = y + h;

            return rectangle;

         }


         void window_base::_defer_translate_to_absolute_coordinates_unlocked(::int_point & point)
         {

            auto handle = _x11_handle();

            Window child_return;

            int abs_x, abs_y;

            int x = point.x;

            int y = point.y;

            XTranslateCoordinates(__x11_handle(handle),
                                  XDefaultRootWindow(as_x11_display(handle)),
                                  (int) x, (int) y, &abs_x, &abs_y,
                                  &child_return);

            point.x = abs_x;

            point.y = abs_y;

         }


      } // user


   } // nano


} // x11



