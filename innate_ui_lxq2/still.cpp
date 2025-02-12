// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "icon.h"
#include "still.h"

//#include <KF5/KIOWidgets/KIO/JobUiDelegate>

#include <QLabel>


namespace innate_ui_kde6
{


   still::still()
   {

      m_bIcon = false;

      //m_iCreateStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | SS_LEFT;

   }


   still::~still()
   {

   }


   void still::_create_child(window * pwindowParent)
   {

      m_pwindowParent = pwindowParent;

      // m_hwnd = CreateWindow(
      //    L"STATIC",  // Predefined class; Unicode assumed
      //    L"",      // Button text
      //    m_iCreateStyle,  // Styles
      //    10,         // x position
      //    10,         // y position
      //    100,        // Button width
      //    100,        // Button height
      //    pwindowParent->m_hwnd,     // Parent window
      //    NULL,       // No menu.
      //    (HINSTANCE)GetWindowLongPtr(pwindowParent->m_hwnd, GWLP_HINSTANCE),
      //    NULL);

      // if(m_bIcon)
      // {
      //
      //    m_pqwidget = gtk_image_new();
      //
      // }
      // else
      {

         ::pointer < ::innate_ui_kde6::window > pkde6windowParent = pwindowParent;

         m_pqwidget = ___new QLabel(pkde6windowParent->m_pqwidget);

         //gtk_label_set_xalign(GTK_LABEL(m_pgtkwidget), 0.0);

      }

      //gtk_widget_set_visible(m_pgtkwidget, true);

   }


   void still::create_icon_still(::innate_ui::window * pwindowParent)
   {

      //m_iCreateStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | SS_ICON | SS_REALSIZEIMAGE;

      m_bIcon = true;

      create_child(pwindowParent);

   }


   void still::set_text(const ::scoped_string & scopedstr)
   {

      ::string str(scopedstr);

      _user_post([this, str]
      ()
      {

         ////gtk_label_set_label(GTK_LABEL(m_pgtkwidget), str);
         auto plabel = dynamic_cast<QLabel*>(m_pqwidget);

         if(plabel)
         {

            plabel->setText(str.c_str());

         }

      });

   }


   void still::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <::innate_ui_kde6::icon > picon = piconParam;

      _user_send([this, picon]()
      {

         //gtk_image_set_from_paintable(GTK_IMAGE(m_pqgtkwidget), picon->m_pgdkpaintable);
         //::SendMessage(m_hwnd, STM_SETICON, (WPARAM) picon->m_hicon, 0);

         auto plabel = dynamic_cast<QLabel*>(m_pqwidget);

         if(plabel)
         {

            plabel->setPixmap(*picon->m_pqpixmap);

         }

         
      });

   }


} // namespace innate_ui_kde6



