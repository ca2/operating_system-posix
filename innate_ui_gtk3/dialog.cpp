// Created by camilo on 2024-09-12 22:45 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dialog.h"
#include "innate_ui.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"
#include "acme/platform/application.h"
#include "acme/parallelization/manual_reset_event.h"


namespace innate_ui_gtk3
{
   


   dialog::dialog()
   {
   }


   dialog::~dialog()
   {

   }


   // void dialog::_get_class(WNDCLASSEXW & wcex)
   // {
   //
   //    wcex.style = CS_HREDRAW | CS_VREDRAW;
   //    wcex.lpfnWndProc = WndProc;
   //    wcex.cbClsExtra = 0;
   //    wcex.cbWndExtra = 0;
   //    wcex.hInstance = (HINSTANCE) ::platform::get()->m_hinstanceThis;
   //    //wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
   //    wcex.hIcon = nullptr;
   //    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
   //    wcex.hbrBackground = ::GetSysColorBrush(COLOR_3DFACE);
   //    //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
   //    wcex.lpszMenuName = nullptr;
   //    //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
   //    wcex.hIconSm = nullptr;
   //
   // }

   void dialog::_create()
   {

      // m_hwnd = CreateWindowW(_get_class_name(), L"", WS_DLGFRAME | WS_CAPTION | WS_POPUPWINDOW,
      //         CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, (HINSTANCE) ::platform::get()->m_hinstanceThis,
      //         nullptr);

      m_pgtkwidget = gtk_dialog_new_with_buttons("Custom Dialog",
                                                   NULL,
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   NULL);
      if (m_pgtkwidget)
      {

         system()->innate_ui()->add_top_level_window(this);

      }
      GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(m_pgtkwidget));
      m_fixed = gtk_fixed_new();
      gtk_container_add(GTK_CONTAINER(content_area), m_fixed);

   }


} // namespace innate_ui_gtk3
