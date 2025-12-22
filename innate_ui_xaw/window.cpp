// Created by camilo on 2024-09-12 22:45 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "dialog.h"
#include "innate_ui.h"
#include "window.h"
#include "acme/nano/nano.h"
#include "acme/platform/platform.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/prototype/geometry2d/size.h"
//#include "acme/operating_system/windows/nano/user/user.h"
#include "acme/platform/node.h"


namespace innate_ui_gtk3
{

   

   //const WCHAR * g_pszWindowClass = L"innate_ui_win32_window";

   window::window()
   {
      m_pgtkwidget = nullptr;
      //m_hmenuSystem = nullptr;
      //m_iChildIdSeed = 1000;
   }


   window::~window()
   {

   }



   void window::set_text(const ::scoped_string & scopedstr)
   {

      ::string str(scopedstr);

      post([this, str]
      ()
         {

         //::string str;
            gtk_window_set_title(GTK_WINDOW(m_pgtkwidget), str);

});

   }
   //
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//

   // LONG_PTR window::_get_style()
   // {
   //
   //    return ::GetWindowLongPtr(m_hwnd, GWL_STYLE);
   //
   // }

   // const_char_pointer window::__get_class_name()
   // {
   //
   //    return typeid(*this).name();
   //
   // }

   //
   // wstring window::_get_class_name()
   // {
   //
   //    return __get_class_name();
   //
   // }

   //
   // ATOM window::_register_class()
   // {
   //
   //    auto pszClassName = __get_class_name();
   //
   //    auto & atom = innate_ui()->m_classmap[pszClassName];
   //
   //    if (atom)
   //    {
   //
   //       return atom;
   //
   //    }
   //
   //    WNDCLASSEXW wcex;
   //
   //    wcex.cbSize = sizeof(WNDCLASSEX);
   //    wstring wstrClassName(scopedstrClassName);
   //    wcex.lpszClassName = wstrClassName;
   //
   //
   //    _get_class(wcex);
   //
   //    atom = RegisterClassExW(&wcex);
   //
   //    return atom;
   //
   // }

   //
   // void window::_get_class(WNDCLASSEXW & wcex)
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
   //    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   //    //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
   //    wcex.lpszMenuName = nullptr;
   //    //wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
   //    wcex.hIconSm = nullptr;
   //
   // }
   //

   void window::_create()
   {

      m_pgtkwidget = gtk_window_new(GTK_WINDOW_TOPLEVEL);

      if (m_pgtkwidget)
      {

         system()->innate_ui()->add_top_level_window(this);

      }

   }


   void window::_create_child(window * pwindow)
   {


   }


   void window::create()
   {


      user_send([this]()
         {

            //_register_class();
            
            _create();

            innate_ui()->m_windowmap[m_pgtkwidget] = this;


      });

      if (!m_pgtkwidget)
      {
         throw ::exception(error_failed);
      }



   }
   // int window::_get_id()
   // {
   //
   //    return GetWindowLong(m_hwnd, GWL_ID);
   //
   // }

   // ::pointer < window > window::_get_child_with_id(int iId)
   // {
   //
   //    for (auto & pchild : m_childa)
   //    {
   //
   //       ::pointer < window > pwindow = pchild;
   //
   //       if (pwindow)
   //       {
   //
   //          if (pwindow->_get_id() == iId)
   //          {
   //
   //             return pwindow;
   //          }
   //
   //       }
   //
   //    }
   //
   //    return {};
   //
   // }

   // LRESULT window::_window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
   // {
   //
   //
   //
   //    switch (message)
   //
   //    {
   //    case WM_APP + 124:
   //       PostQuitMessage(0);
   //       break;
   //    case WM_COMMAND:
   //    {
   //       int wmId = LOWORD(wparam);
   //       auto pchild = _get_child_with_id(wmId);
   //
   //       if (pchild)
   //       {
   //
   //          if (pchild->_on_command())
   //          {
   //
   //             return 0;
   //
   //          }
   //
   //       }
   //       //// Parse the menu selections:
   //       //switch (wmId)
   //       //{
   //       //   //case IDM_ABOUT:
   //       //     // DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
   //       //      //break;
   //       //case 123:
   //       //   DestroyWindow(hWnd);
   //       //   break;
   //       //default:
   //       return DefWindowProc(m_hwnd, message, wparam, lparam);
   //       //}
   //    }
   //    break;
   //    case WM_PAINT:
   //    {
   //       //PAINTSTRUCT ps;
   //       //HDC hdc = BeginPaint(hWnd, &ps);
   //       //// TODO: Add any drawing code that uses hdc here...
   //       //EndPaint(hWnd, &ps);
   //       return DefWindowProc(m_hwnd, message, wparam, lparam);
   //    }
   //    break;
   //    case WM_CLOSE:
   //       destroy_window();
   //       break;
   //    case WM_DESTROY:
   //       //PostQuitMessage(0);
   //    default:
   //       return DefWindowProc(m_hwnd, message, wparam, lparam);
   //    }
   //    return 0;
   //
   //
   // }

   //
   // bool window::_on_command()
   // {
   //
   //    return false;
   //
   // }


   void window::create_child(::innate_ui::window * pwindow)
   {

      ::pointer< window > pwindowImpl = pwindow;

      user_send([this, pwindowImpl]()
         {

            _create_child(pwindowImpl);

            innate_ui()->m_windowmap[m_pgtkwidget] = this;
            pwindowImpl->m_childa.add(this);
            //pwindowImpl->m_iChildIdSeed++;
            //::SetWindowLong(m_hwnd, GWL_ID, pwindowImpl->m_iChildIdSeed);


      });

      if (!m_pgtkwidget)
      {
         throw ::exception(error_failed);
      }



   }


   void window::destroy_window()
   {

      ///if (::IsWindow(m_hwnd))
      {

         for (auto pchild : m_childa)
         {

            pchild->destroy_window();

         }

         m_childa.clear();

         //if (!::GetParent(m_hwnd))
         {

            innate_ui()->m_windowa.erase(this);

         }

         //::DestroyWindow(m_hwnd);

         gtk_widget_destroy(m_pgtkwidget);

         innate_ui()->m_windowmap[m_pgtkwidget].release();

         m_pgtkwidget = nullptr;

      }

   }

   void window::show()
   {

      post([this]()
         {

         gtk_widget_show_all(m_pgtkwidget);
            //ShowWindow(m_hwnd, SW_SHOW);
            //UpdateWindow(m_hwnd);

      });



   }

   void window::hide()
   {

   }


   void window::set_position(const ::int_point & pointParam)
   {

      auto point = pointParam;

      user_send([this, point]()
         {

            auto p = point;

            ::pointer < ::innate_ui_gtk3::dialog > pdialog = m_pwindowParent;

            if(pdialog)
            {

               auto fixed = pdialog->m_fixed;

               gtk_fixed_put(GTK_FIXED(fixed), m_pgtkwidget, point.x, point.y);

               //::pointer < ::innate_ui_gtk3::dialog > pdialog = innate_ui()->m_windowmap[pwidgetParentWindow];
               //pdialog

            }

            // if (p.x < 0 || p.y < 0)
            // {
            //    auto hwndParent  = GetParent(m_hwnd);
            //    RECT rParentClient;
            //    GetClientRect(hwndParent, &rParentClient);
            //    RECT rThis;
            //    GetClientRect(m_hwnd, &rParentClient);
            //    if (p.x < 0)
            //    {
            //       p.x += ::width(rParentClient) - ::width(rThis);
            //    }
            //
            //    if (p.y < 0)
            //    {
            //       p.y += ::height(rParentClient) - ::height(rThis);
            //    }
            // }
            //
            // ::SetWindowPos(m_hwnd, nullptr, p.x, p.y, 0, 0, SWP_NOSIZE);

         });

   }

   void window::set_size(const ::int_size & sizeParam)
   {

      auto size = sizeParam;

      user_send([this, size]()
         {

         gtk_widget_set_size_request(m_pgtkwidget, size.cx, size.cy);

            // ::SetWindowPos(m_hwnd, nullptr, 0, 0, size.cx, size.cy, SWP_NOMOVE);
            //
            // RECT rThis2;
            // ::GetWindowRect(m_hwnd, &rThis2);



         });

   }


   void window::adjust_for_client_size(const ::int_size & sizeParam)
   {

      auto size = sizeParam;

      set_size(sizeParam);

      // user_send([this, size]()
      //    {
      //
      //       RECT r{};
      //
      //       r.right = r.left + size.cx;
      //       r.bottom = r.top + size.cy;
      //
      //
      //       AdjustWindowRect(&r, _get_style(), FALSE);
      //
      //       ::SetWindowPos(m_hwnd, nullptr, 0, 0, width(r), height(r), SWP_NOMOVE);
      //
      //       RECT rThis2;
      //       ::GetWindowRect(m_hwnd, &rThis2);
      //
      //
      //    });

   }


   void window::center()
   {

      user_send([this]()
   {

         gtk_window_set_position(GTK_WINDOW(m_pgtkwidget), GTK_WIN_POS_CENTER);
      // auto hwnd = ::GetParent(m_hwnd);
      //
      // if (hwnd == nullptr)
      // {
      //
      //    hwnd = ::GetDesktopWindow();
      //
      // }
      //
      // RECT r;
      //
      // ::GetWindowRect(hwnd, &r);
      // RECT rThis;
      // ::GetWindowRect(m_hwnd, &rThis);
      //
      // int wThis = rThis.right - rThis.left;
      // int hThis = rThis.bottom - rThis.top;
      //
      // int x = ((r.right - r.left) - (wThis)) / 2;
      // int y = ((r.bottom - r.top) - (hThis)) / 2;
      //
      // ::SetWindowPos(m_hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE);
      //
      // RECT rThis2;
      // ::GetWindowRect(m_hwnd, &rThis2);
         });


   }



   ::innate_ui_gtk3::innate_ui * window::innate_ui()
   {

      return dynamic_cast <::innate_ui_gtk3::innate_ui *> (::innate_ui::window::innate_ui());

   }

   
   void window::defer_show_system_menu(::user::mouse * pmouse)
   {

      node()->defer_show_system_menu(pmouse);

   }


} // namespace innate_ui_gtk3



