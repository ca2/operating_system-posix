// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "icon.h"
#include "still.h"
#include "acme/windowing/windowing.h"
#include "acme_windowing_gtk4/_.h"
//#include "acme_windowing_gtk4/display.h"
//#include "acme_windowing_gtk4/display.h"


namespace innate_ui_gtk4
{


   still::still()
   {
      m_bIcon = false;
      m_pgtkcssprovider = nullptr;
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

      if(m_bIcon)
      {

         m_pgtkwidget = gtk_image_new();

      }
      else
      {

         m_pgtkwidget = gtk_label_new("");

         //m_strCssClass.format("dynamic-label");

         gtk_label_set_xalign(GTK_LABEL(m_pgtkwidget), 0.0);


      }

      gtk_widget_set_visible(m_pgtkwidget, true);



   }


   void still::_update_style()
   {

      //::cast < ::gtk4::acme::windowing::display > pgtk4acmewindowingdisplay = system()->acme_windowing()->acme_display();

      if (!m_pgtkcssprovider)
      {

         m_pgtkcssprovider = gtk_css_provider_new();

         gtk_style_context_add_provider_for_display(
             gdk_display_get_default(),
             GTK_STYLE_PROVIDER(m_pgtkcssprovider),
             GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
         );

      }

      m_strClassName = "dynamic-label-" + ::as_string((::uptr) m_pgtkwidget);

      gtk_widget_add_css_class(m_pgtkwidget, m_strClassName);

      char css[256];

      g_snprintf(css, sizeof(css),
                 "label.%s { font-size: %.2fem; font-weight: %d; }",
                 m_strClassName.c_str(), m_dFontSizeEm, m_iFontWeight);

      gtk_css_provider_load_from_data(m_pgtkcssprovider, css, -1);

      PangoLayout *layout = gtk_widget_create_pango_layout(m_pgtkwidget, m_strText);

      pango_layout_get_pixel_size(layout, &m_iLayoutWidth, &m_iLayoutHeight);

      g_object_unref(layout);

      gtk_widget_queue_resize(m_pgtkwidget);

      gtk_widget_queue_draw(m_pgtkwidget);

   }


   void still::set_font_size(double dFontSizeEm)
   {

      m_dFontSizeEm = dFontSizeEm;

   }


   void still::set_font_weight(int iFontWeight)
   {

      m_iFontWeight = iFontWeight;

   }

   void still::create_icon_still(::innate_ui::window * pwindowParent)
   {

      //m_iCreateStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | SS_ICON | SS_REALSIZEIMAGE;
m_bIcon = true;
      create_child(pwindowParent);

   }


   void still::layout()
   {

      _update_style();

   }


   void still::set_text(const ::scoped_string & scopedstr)
   {

      ::string str(scopedstr);

      m_strText = str;

      post([this, str]
      ()
      {

         gtk_label_set_label(GTK_LABEL(m_pgtkwidget), str);

      });

   }


   void still::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <::innate_ui_gtk4::icon > picon = piconParam;

      main_send([this, picon]()
      {

         gtk_image_set_from_paintable(GTK_IMAGE(m_pgtkwidget), picon->m_pgdkpaintable);
         //::SendMessage(m_hwnd, STM_SETICON, (WPARAM) picon->m_hicon, 0);
         
      });

   }


} // namespace innate_ui_gtk4
