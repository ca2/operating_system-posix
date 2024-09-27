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
QCustomTopWindow::QCustomTopWindow(::kde5::nano::user::window * pwindow)
{
   // Resize the window
   m_pwindow = pwindow;
   //this->resize(600, 400);
   // Apply KDE translucent and undecorated window settings
   //setTranslucentAttributes(this);
}

   void QCustomTopWindow::paintEvent(QPaintEvent* event)
   {
      // Create a QPixmap to serve as the drawing surface
      //QPixmap pixmap(this->size());
      //pixmap.fill(Qt::transparent);  // Make the QPixmap fully transparent

      if(m_qimage.size() != this->size())
      {

         m_qimage = QImage(this->size(), QImage::Format_ARGB32_Premultiplied);

      }

      // Create a Cairo surface from QImage
      //QImage qImage(this->size(), QImage::Format_ARGB32_Premultiplied);
      //qImage.
      m_pwindow->_on_qimage_draw(&m_qimage);
      // cairo_surface_t* surface = cairo_image_surface_create_for_data(
      //     qImage.bits(),
      //     CAIRO_FORMAT_ARGB32,
      //     qImage.width(),
      //     qImage.height(),
      //     qImage.bytesPerLine()
      // );
      //
      // cairo_t* cr = cairo_create(surface);
      //
      // // Draw a translucent blue rectangle
      // cairo_set_source_rgba(cr, 0, 0, 1, 0.5);  // Blue with 50% opacity
      // cairo_rectangle(cr, 50, 50, 300, 200);
      // cairo_fill(cr);
      //
      // // Draw a translucent pink ellipse
      // cairo_set_source_rgba(cr, 1, 0, 1, 0.5);  // Pink with 50% opacity
      // cairo_arc(cr, 400, 200, 100, 0, 2 * M_PI);  // Circle with radius 100
      // cairo_fill(cr);
      //
      // // Cleanup Cairo resources
      // cairo_destroy(cr);
      // cairo_surface_destroy(surface);

      // Create a QPainter to draw the QImage
      QPainter painter(this);
      painter.drawImage(0, 0, m_qimage);
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


   void QCustomTopWindow::resizeEvent(QResizeEvent *event)
   {
      try
      {
         QSize newSize = event->size();  // Get the new size of the window
         //   qDebug() << "Window resized to:" << newSize;
         m_pwindow->_on_size(newSize.width(), newSize.height());
         // Update the label with the new size
         //updateSizeLabel(newSize);
      }
      catch(...)
      {


      }

      // Call the base class implementation (important for proper event handling)
      QMainWindow::resizeEvent(event);
   }

