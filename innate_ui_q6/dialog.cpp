// Created by camilo on 2024-09-12 22:45 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dialog.h"

#include <QDialog>

#include "innate_ui.h"
#include "acme/platform/platform.h"
#include "acme/platform/system.h"
#include "acme/platform/application.h"
#include "acme/parallelization/manual_reset_happening.h"


namespace innate_ui_q6
{
   


   dialog::dialog()
   {

      //m_ptFixed = nullptr;

   }


   dialog::~dialog()
   {

   }

   //
   // void dialog::create()
   // {
   //
   //    ::innate_ui_q6::window::create();
   //
   // }
   //
   //
   // // void dialog::_get_class(WNDCLASSEXW & wcex)
   // // {
   // //
   // //    wcex.style = CS_HREDRAW | CS_VREDRAW;
   // //    wcex.lpfnWndProc = WndProc;
   // //    wcex.cbClsExtra = 0;
   // //    wcex.cbWndExtra = 0;
   // //    wcex.hInstance = (HINSTANCE) ::platform::get()->m_hinstanceThis;
   // //    //wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
   // //    wcex.hIcon = nullptr;
   // //    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
   // //    wcex.hbrBackground = ::GetSysColorBrush(COLOR_3DFACE);
   // //    //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
   // //    wcex.lpszMenuName = nullptr;
   // //    //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
   // //    wcex.hIconSm = nullptr;
   // //
   // // }
   //
   // void dialog::_create()
   // {
   //
   //    // m_hwnd = CreateWindowW(_get_class_name(), L"", WS_DLGFRAME | WS_CAPTION | WS_POPUPWINDOW,
   //    //         CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, (HINSTANCE) ::platform::get()->m_hinstanceThis,
   //    //         nullptr);
   //
   //    // m_pgtkwidget = gtk_dialog_new_with_buttons("Custom Dialog",
   //    //                                              NULL,
   //    //                                              GTK_DIALOG_DESTROY_WITH_PARENT,
   //    //                                              NULL);
   //
   //    m_pqwidget = ___new QDialog();
   //
   //    if (m_pqwidget)
   //    {
   //
   //       system()->innate_ui()->add_top_level_window(this);
   //
   //    }
   //
   //    //m_pgtkwidgetFixed = gtk_fixed_new();
   //
   //    //gtk_window_set_child(GTK_WINDOW(m_pgtkwidget), m_pgtkwidgetFixed);
   //    //gtk_widget_set_parent(m_pgtkwidget, nullptr);
   //    ///GtkWidget *content_area = gtk_dialog_get_content_area(GTK_DIALOG(m_pgtkwidget));
   //    //m_fixed = gtk_fixed_new();
   //    //gtk_box_append(content_area, m_fixed);
   //
   // }
   //

} // namespace innate_ui_q6



