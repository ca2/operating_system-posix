//
// Created by camilo on 2025-01-10 16:51 <3ThomasBorregaardSorensen!!
//
#pragma once


#include <QWidget>


namespace q6
{


   namespace micro
   {


      class CLASS_DECL_ACME_WINDOWING_Q6 window
      {
      public:


         virtual void _on_mouse_press(QMouseEvent* pevent);


         virtual void _on_mouse_release(QMouseEvent* pevent);


         virtual void _on_mouse_motion(QMouseEvent* pevent);


         virtual void _on_qimage_draw(QImage* pqimage);


         virtual void _on_reposition(int x, int y);


         virtual void _on_size(int cx, int cy);


         virtual void _on_show(bool bShow);


         virtual void _on_set_focus();


         virtual void _on_kill_focus();


      };


   } // namespace micro

} // namespace q6
