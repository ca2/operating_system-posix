// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "button.h"
#include "dialog.h"
#include "icon.h"


namespace innate_ui_gtk4
{


   button::button()
   {
   }


   button::~button()
   {

   }


   void button::set_callback_on_click(const ::procedure & callbackOnClickParam)
   {

      ::innate_ui::button::set_callback_on_click(callbackOnClickParam);

      // Callback function to handle the button click happening
      auto on_button_clicked = [](GtkWidget *widget, gpointer data)->void
      {
         auto p = (button *) data;
         p->call_on_click();
      };


      g_signal_connect(m_pgtkwidget, "clicked", G_HANDLER(on_button_clicked), this);


   }


   void button::_create_child(window * pwindowParent)
   {

      m_pwindowParent = pwindowParent;

      // m_hwnd = CreateWindow(
      //    L"BUTTON",  // Predefined class; Unicode assumed
      //    L"",      // Button text
      //    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
      //    10,         // x position
      //    10,         // y position
      //    100,        // Button width
      //    100,        // Button height
      //    pwindowParent->m_hwnd,     // Parent window
      //    NULL,       // No menu.
      //    (HINSTANCE)GetWindowLongPtr(pwindowParent->m_hwnd, GWLP_HINSTANCE),
      //    NULL);

      m_pgtkwidget = gtk_button_new();

      gtk_widget_set_visible(m_pgtkwidget, true);

   }


   void button::set_text(const ::scoped_string & scopedstr)
   {

      ::string str(scopedstr);

      post([this, str]
      ()
         {

            gtk_button_set_label(GTK_BUTTON(m_pgtkwidget), str);

});

   }


   void button::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <icon > picon = piconParam;

      main_send([this, picon]()
      {

         //::SendMessage(m_hwnd, BM_SETICON, (WPARAM) picon->m_hicon, 0);

         });

   }


} // namespace innate_ui_gtk4
