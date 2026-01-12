// Created by camilo on 2024-09-13 01:00 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "button.h"
#include "icon.h"


namespace innate_ui_motif
{


   button::button()
   {
   }


   button::~button()
   {

   }

   void on_button_clicked(Widget w, XtPointer client_data, XtPointer call_data)
   {
      auto p = static_cast<button*>(client_data);
      p->call_on_click();
   }



   void button::set_callback_on_click(const ::procedure & callbackOnClickParam)
   {

      ::innate_ui::button::set_callback_on_click(callbackOnClickParam);




      //g_signal_connect(m_pgtkwidget, "clicked", (GCallback) on_button_clicked, this);


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

      ::cast < ::innate_ui_motif::window >  pmotifwindowParent = pwindowParent;


//       Widget button_widget = XtVaCreateManagedWidget(
//    "myButton",
//    commandWidgetClass,
//    pxawwindowParent->m_widget,
//    XtNlabel, "Click me",
//    nullptr
// );
      // Create a PushButton widget (equivalent to Xaw's commandWidgetClass)
      m_widget = XtVaCreateManagedWidget(
          "myButton",                    // Widget name
          xmPushButtonWidgetClass,        // Widget class (PushButton in Motif)
          pmotifwindowParent->m_widget,                         // Parent widget (same as pxawwindowParent->m_widget in Xaw)
          //XmNlabel, "Click me",           // Set the label (text on the button)
          NULL                            // End of argument list
      );
      //m_widget = button_widget;

      XtAddCallback(
         m_widget,
         XtNcallback,
         on_button_clicked,
         (XtPointer)this
      );


      //m_pgtkwidget = gtk_button_new();
      //gtk_widget_show(m_pgtkwidget);

   }


   void button::set_text(const ::scoped_string & scopedstr)
   {

      ::string str(scopedstr);

      post([this, str]
      ()
      {

         //gtk_button_set_label(GTK_BUTTON(m_pgtkwidget), str);

         XtVaSetValues(m_widget, XtNlabel, str.c_str(), NULL);

      });

   }


   void button::set_icon(::innate_ui::icon * piconParam)
   {

      ::pointer <icon > picon = piconParam;

      user_send([this, picon]()
      {

         //::SendMessage(m_hwnd, BM_SETICON, (WPARAM) picon->m_hicon, 0);

         });

   }


} // namespace innate_ui_xaw
