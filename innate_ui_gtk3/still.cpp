// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "icon.h"
#include "still.h"


namespace innate_ui_gtk3
{


   still::still()
   {
      //m_iCreateStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | SS_LEFT;

      m_bIcon = false;

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
      if(m_bIcon)
      {
         m_pgtkwidget = gtk_image_new();
      }
      else {
         m_pgtkwidget = gtk_label_new("");
         gtk_label_set_xalign(GTK_LABEL(m_pgtkwidget), 0.0);
      }
      gtk_widget_show(m_pgtkwidget);

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

      post([this, str]
      ()
         {

            gtk_label_set_label(GTK_LABEL(m_pgtkwidget), str);

});

   }

   void still::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <::innate_ui_gtk3::icon > picon = piconParam;

      sync([this, picon]()
      {

         gtk_image_set_from_pixbuf(GTK_IMAGE(m_pgtkwidget), picon->m_pgdkpixbuf);
         //::SendMessage(m_hwnd, STM_SETICON, (WPARAM) picon->m_hicon, 0);
         
         });

   }


} // namespace innate_ui_gtk3
