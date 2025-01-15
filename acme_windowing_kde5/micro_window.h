//
// Created by camilo on 2025-01-10 16:51 <3ThomasBorregaardSorensen!!
//
#pragma once



#include <QWidget>

namespace kde5
{


namespace micro
{


class CLASS_DECL_ACME_WINDOWING_KDE5 window
{
public:

    virtual void _on_mouse_press(QMouseEvent * pevent);
    virtual void _on_mouse_release(QMouseEvent * pevent);
    virtual void _on_mouse_motion(QMouseEvent * pevent);
    virtual void _on_qimage_draw(QImage * pqimage);
    virtual void _on_reposition(int x, int y);
    virtual void _on_size(int cx, int cy);



};


} // namespace micro

} // namespace kde5


