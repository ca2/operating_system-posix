//
// Created by camilo on 2025-01-10 16:51 <3ThomasBorregaardSorensen!!
//
#pragma once


#include <QWidget>


namespace q
{


   namespace micro
   {


      class CLASS_DECL_COMMON_Q window
      {
      public:


         virtual void _on_mouse_press(QMouseEvent* pevent);


         virtual void _on_mouse_release(QMouseEvent* pevent);


         virtual void _on_mouse_motion(QMouseEvent* pevent);


         virtual void _on_wheel(QWheelEvent* pevent);


         virtual void _on_qimage_draw(QImage* pqimage);


         virtual void _on_reposition(int x, int y);


         virtual void _on_size(int cx, int cy);


         virtual void _on_show(bool bShow);


         virtual void _on_set_focus();


         virtual void _on_kill_focus();


         virtual void _on_key_press(QKeyEvent* pevent);


         virtual void _on_key_release(QKeyEvent* pevent);


         virtual void _on_text(const ::scoped_string & scopedstr);



      };


   } // namespace micro

} // namespace q
