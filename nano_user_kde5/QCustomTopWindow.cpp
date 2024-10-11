//
//
// Created by camilo on 2024-09-27 17:17 <3ThomasBorregaardSoresen!!
////
#include "framework.h"
#include "QCustomTopWindow.h"
#include "window.h"
#include <QPainter>
#include <QResizeEvent>

// Custom window class inheriting from QMainWindow
QCustomTopWindow::QCustomTopWindow(::kde5::micro::window * pwindow)
{
   // Resize the window
   m_pwindow = pwindow;
   //this->resize(600, 400);
   // Apply KDE translucent and undecorated window settings
   //setTranslucentAttributes(this);
}


   void QCustomTopWindow::paintEvent(QPaintEvent* event)
   {

      if(m_qimage.size() != this->size())
      {

         m_qimage = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

      }

      m_pwindow->_on_qimage_draw(&m_qimage);

      QPainter painter(this);

      painter.drawImage(0, 0, m_qimage);

   //QColor qcolor(100, 120, 255);
   //QBrush qbrush(qcolor);

   //painter.setBackground(qbrush);

   //painter.fillRect(10, 10, 100, 100, qbrush);

   }


   // Handle mouse button press event
   void QCustomTopWindow::mousePressEvent(QMouseEvent *event)
   {
      // int buttonType = -1;
      // if (event->button() == Qt::LeftButton) {
      //    buttonType = 1;
      // } else if (event->button() == Qt::RightButton) {
      //    buttonType = 2;
      // } else if (event->button() == Qt::MiddleButton) {
      //    buttonType = 3;
      // }
      // label->setText(QString("Mouse Pressed: %1 Button at (%2, %3)")
      //     .arg(buttonType)
      //     .arg(event->pos().x())
      //     .arg(event->pos().y()));
      //qDebug() << "Mouse Pressed:" << buttonType << "at" << event->pos();
      m_pwindow->_on_mouse_press(event);
   }

   // Handle mouse button release event
   void QCustomTopWindow::mouseReleaseEvent(QMouseEvent *event)
   {
      // int buttonType = -1;
      // if (event->button() == Qt::LeftButton) {
      //    buttonType = 1;
      // } else if (event->button() == Qt::RightButton) {
      //    buttonType = 2;
      // } else if (event->button() == Qt::MiddleButton) {
      //    buttonType = 3;
      // }
      // label->setText(QString("Mouse Released at (%1, %2)")
      //     .arg(event->pos().x())
      //     .arg(event->pos().y()));
      //qDebug() << "Mouse Released at" << event->pos();
      m_pwindow->_on_mouse_release(event);
   }

   // Handle mouse motion event
   void QCustomTopWindow::mouseMoveEvent(QMouseEvent *event)
   {
//         label->setText(QString("Mouse Moved to (%1, %2)")
//           .arg(event->pos().x())
 //         .arg(event->pos().y()));
   //   qDebug() << "Mouse Moved to" << event->pos();
      m_pwindow->_on_mouse_motion(event);
   }

void QCustomTopWindow::moveEvent(QMoveEvent *event)
{
   try
   {
      QPoint newPos = event->pos();  // Get the __new size of the window
      //   qDebug() << "Window resized to:" << newSize;
      m_pwindow->_on_reposition(newPos.x(), newPos.y());
      // Update the label with the __new size
      //updateSizeLabel(newSize);
   }
   catch(...)
   {


   }

   // Call the base class implementation (important for proper event handling)
   QWidget::moveEvent(event);

}
   void QCustomTopWindow::resizeEvent(QResizeEvent *event)
   {
      try
      {
         QSize newSize = event->size();  // Get the __new size of the window
         //   qDebug() << "Window resized to:" << newSize;
         m_pwindow->_on_size(newSize.width(), newSize.height());
         // Update the label with the __new size
         //updateSizeLabel(newSize);
      }
      catch(...)
      {


      }

      // Call the base class implementation (important for proper event handling)
      QWidget::resizeEvent(event);
   }

