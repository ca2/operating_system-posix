// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "platform.h"
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

      user_send([this, str]
      ()
         {

            gtk_label_set_label(GTK_LABEL(m_pgtkwidget), str);

});

   }

   void still::layout()
   {

      user_send([this]()
      {

         if (!m_pgtkwidget || m_bIcon)
            return;

         auto pattributes = pango_attr_list_new();
         if (m_dFontSizeEm > 0.0)
            pango_attr_list_insert(pattributes, pango_attr_scale_new(m_dFontSizeEm));
         if (m_iFontWeight > 0)
            pango_attr_list_insert(pattributes,
               pango_attr_weight_new(static_cast<PangoWeight>(m_iFontWeight)));
         gtk_label_set_attributes(GTK_LABEL(m_pgtkwidget), pattributes);
         pango_attr_list_unref(pattributes);

         // Dialogs use these dimensions immediately to position the next row.
         auto playout = gtk_label_get_layout(GTK_LABEL(m_pgtkwidget));
         pango_layout_get_pixel_size(playout, &m_iLayoutWidth, &m_iLayoutHeight);
         m_iLayoutHeight = maximum(m_iLayoutHeight, 1);

      });

   }


   void still::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <::innate_ui_gtk3::icon > picon = piconParam;

      user_send([this, picon]()
      {

         gtk_image_set_from_pixbuf(GTK_IMAGE(m_pgtkwidget), picon->m_pgdkpixbuf);
         //::SendMessage(m_hwnd, STM_SETICON, (WPARAM) picon->m_hicon, 0);
         
         });

   }


} // namespace innate_ui_gtk3
