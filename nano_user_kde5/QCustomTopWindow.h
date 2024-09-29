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


   ::kde5::nano::user::window *     m_pwindow;
   QImage                           m_qimage;

   QCustomTopWindow(::kde5::nano::user::window * pwindow);


protected:


   void paintEvent(QPaintEvent* event) override;

   void mousePressEvent(QMouseEvent *event) override;

   void mouseReleaseEvent(QMouseEvent *event) override;

   void mouseMoveEvent(QMouseEvent *event) override;

   void moveEvent(QMoveEvent *event) override;

   void resizeEvent(QResizeEvent *event) override;


};
