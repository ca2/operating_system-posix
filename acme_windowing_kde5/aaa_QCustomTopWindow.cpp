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
   setAttribute(Qt::WA_InputMethodEnabled, true);
   // Resize the window
   m_pwindow = pwindow;
   //this->resize(600, 400);
   // Apply KDE translucent and undecorated window settings
   //setTranslucentAttributes(this);
}


   void QCustomTopWindow::paintEvent(QPaintEvent* happening)
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


   // Handle mouse button press happening
   void QCustomTopWindow::mousePressEvent(QMouseEvent *happening)
   {
      // int buttonType = -1;
      // if (happening->button() == Qt::LeftButton) {
      //    buttonType = 1;
      // } else if (happening->button() == Qt::RightButton) {
      //    buttonType = 2;
      // } else if (happening->button() == Qt::MiddleButton) {
      //    buttonType = 3;
      // }
      // label->setText(QString("Mouse Pressed: %1 Button at (%2, %3)")
      //     .arg(buttonType)
      //     .arg(happening->pos().x)
      //     .arg(happening->pos().y));
      //qDebug() << "Mouse Pressed:" << buttonType << "at" << happening->pos();
      m_pwindow->_on_mouse_press(happening);
   }

   // Handle mouse button release happening
   void QCustomTopWindow::mouseReleaseEvent(QMouseEvent *happening)
   {
      // int buttonType = -1;
      // if (happening->button() == Qt::LeftButton) {
      //    buttonType = 1;
      // } else if (happening->button() == Qt::RightButton) {
      //    buttonType = 2;
      // } else if (happening->button() == Qt::MiddleButton) {
      //    buttonType = 3;
      // }
      // label->setText(QString("Mouse Released at (%1, %2)")
      //     .arg(happening->pos().x)
      //     .arg(happening->pos().y));
      //qDebug() << "Mouse Released at" << happening->pos();
      m_pwindow->_on_mouse_release(happening);
   }

   // Handle mouse motion happening
   void QCustomTopWindow::mouseMoveEvent(QMouseEvent *happening)
   {
//         label->setText(QString("Mouse Moved to (%1, %2)")
//           .arg(happening->pos().x)
 //         .arg(happening->pos().y));
   //   qDebug() << "Mouse Moved to" << happening->pos();
      m_pwindow->_on_mouse_motion(happening);
   }

void QCustomTopWindow::moveEvent(QMoveEvent *happening)
{
   try
   {
      QPoint newPos = happening->pos();  // Get the ___new size of the window
      //   qDebug() << "Window resized to:" << newSize;
      m_pwindow->_on_reposition(newPos.x, newPos.y);
      // Update the label with the ___new size
      //updateSizeLabel(newSize);
   }
   catch(...)
   {


   }

   // Call the base class implementation (important for proper happening handling)
   QWidget::moveEvent(happening);

}
   void QCustomTopWindow::resizeEvent(QResizeEvent *happening)
   {
      try
      {
         QSize newSize = happening->size();  // Get the ___new size of the window
         //   qDebug() << "Window resized to:" << newSize;
         m_pwindow->_on_size(newSize.width(), newSize.height());
         // Update the label with the ___new size
         //updateSizeLabel(newSize);
      }
      catch(...)
      {


      }

      // Call the base class implementation (important for proper happening handling)
      QWidget::resizeEvent(happening);
   }


// Handle mouse button press happening
void QCustomTopWindow::keyPressEvent(QKeyEvent *happening)
{
   // int buttonType = -1;
   // if (happening->button() == Qt::LeftButton) {
   //    buttonType = 1;
   // } else if (happening->button() == Qt::RightButton) {
   //    buttonType = 2;
   // } else if (happening->button() == Qt::MiddleButton) {
   //    buttonType = 3;
   // }
   // label->setText(QString("Mouse Pressed: %1 Button at (%2, %3)")
   //     .arg(buttonType)
   //     .arg(happening->pos().x)
   //     .arg(happening->pos().y));
   //qDebug() << "Mouse Pressed:" << buttonType << "at" << happening->pos();
   m_pwindow->_on_key_press(happening);
   QWidget::keyPressEvent(happening);
}

// Handle mouse button release happening
void QCustomTopWindow::keyReleaseEvent(QKeyEvent *happening)
{
   // int buttonType = -1;
   // if (happening->button() == Qt::LeftButton) {
   //    buttonType = 1;
   // } else if (happening->button() == Qt::RightButton) {
   //    buttonType = 2;
   // } else if (happening->button() == Qt::MiddleButton) {
   //    buttonType = 3;
   // }
   // label->setText(QString("Mouse Released at (%1, %2)")
   //     .arg(happening->pos().x)
   //     .arg(happening->pos().y));
   //qDebug() << "Mouse Released at" << happening->pos();
   m_pwindow->_on_key_release(happening);
   QWidget::keyReleaseEvent(happening);
}


void QCustomTopWindow::inputMethodEvent(QInputMethodEvent*happening)
{

   auto str = happening->commitString();

   ::string strText =str.toUtf8().data();

   if (strText.has_character())
   {

      m_pwindow->_on_text(strText);

   }

   QWidget::inputMethodEvent(happening);

}


QVariant QCustomTopWindow::inputMethodQuery(Qt::InputMethodQuery query) const
{
   if (query == Qt::ImEnabled) {
      return true; // Enable input method events
   }
   return QWidget::inputMethodQuery(query);
}