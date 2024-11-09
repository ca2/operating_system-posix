//
// Created by camilo on 2024-09-27 17:17 <3ThomasBorregaardSoresen!!
//
#pragma once


#include <QMainWindow>


// Custom window class inheriting from QMainWindow
class QCustomTopWindow :
   public QWidget
{
public:


   ::kde5::micro::window *     m_pwindow;
   QImage                           m_qimage;

   QCustomTopWindow(::kde5::micro::window * pwindow);


protected:


   void paintEvent(QPaintEvent* happening) override;

   void mousePressEvent(QMouseEvent *happening) override;

   void mouseReleaseEvent(QMouseEvent *happening) override;

   void mouseMoveEvent(QMouseEvent *happening) override;

   void moveEvent(QMoveEvent *happening) override;

   void resizeEvent(QResizeEvent *happening) override;


};
