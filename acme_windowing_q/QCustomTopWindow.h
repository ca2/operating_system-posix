//
// Created by camilo on 2024-09-27 17:17 <3ThomasBorregaardSoresen!!
//
#pragma once


#include "acme_windowing_q/micro_window.h"
#include <QMainWindow>


// Custom window class inheriting from QMainWindow
class CLASS_DECL_COMMON_Q QCustomTopWindow :
   public QWidget
{
public:


   ::q::micro::window *                m_pwindow;
   QImage                                 m_qimage;

   QCustomTopWindow(::q::micro::window * pwindow);


protected:


   void paintEvent(QPaintEvent* happening) override;

   void mousePressEvent(QMouseEvent *happening) override;

   void mouseReleaseEvent(QMouseEvent *happening) override;

   void mouseMoveEvent(QMouseEvent *happening) override;

   void wheelEvent(QWheelEvent *happening) override;

   void moveEvent(QMoveEvent *happening) override;

   void resizeEvent(QResizeEvent *happening) override;

   void hideEvent(QHideEvent * happening) override;

   void showEvent(QShowEvent * happening) override;

   void focusInEvent(QFocusEvent* event) override;

   void focusOutEvent(QFocusEvent* event) override;

   void keyPressEvent(QKeyEvent* event) override;

   void keyReleaseEvent(QKeyEvent* event) override;

   void inputMethodEvent(QInputMethodEvent*) override;

   QVariant inputMethodQuery(Qt::InputMethodQuery query) const override;


};
