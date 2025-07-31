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
#include "acme_windowing_g/activation_token.h"


namespace innate_ui_gtk4
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

   // const char * window::__get_class_name()
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

      m_pgtkwidget = gtk_window_new();

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

      main_send([this]()
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

      main_send([this, pwindowImpl]()
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

      if(GTK_IS_WINDOW(m_pgtkwidget))
      {

         gtk_window_destroy(GTK_WINDOW(m_pgtkwidget));

      }
      // else
      // {
      //
      //    g_object_unref(m_pgtkwidget);
      //
      // }

      innate_ui()->m_windowmap[m_pgtkwidget].release();

      m_pgtkwidget = nullptr;

   }


   void window::show()
   {

      main_post([this]()
      {

         if(GTK_IS_WINDOW(m_pgtkwidget))
         {

            gtk_window_present(GTK_WINDOW(m_pgtkwidget));

         }
         else
         {

            gtk_widget_set_visible(m_pgtkwidget, true);

         }

      });

   }


   void window::hide()
   {

   }


   void window::show_front(user::activation_token* puseractivationtoken)
   {

      ::pointer < ::common_gtk::activation_token > pactivationtoken = puseractivationtoken;

      if (::is_null(pactivationtoken))
      {


         show();

         return;

      }

      main_post([this, pactivationtoken]()
      {

         if(GTK_IS_WINDOW(m_pgtkwidget))
         {

            gtk_window_present_with_time(GTK_WINDOW(m_pgtkwidget), pactivationtoken->m_time);

         }
         else
         {

            gtk_widget_set_visible(m_pgtkwidget, true);

         }

      });

   }


   void window::set_position(const ::int_point & pointParam)
   {

      auto point = pointParam;

      main_send([this, point]()
      {

         auto p = point;

         ::pointer < dialog > pdialog = m_pwindowParent;

         if(pdialog)
         {

            gtk_fixed_put(GTK_FIXED(pdialog->m_pgtkwidgetFixed), m_pgtkwidget, point.x(), point.y());

         }

      });

   }


   void window::set_size(const ::int_size & sizeParam)
   {

      auto size = sizeParam;

      main_send([this, size]()
      {

         gtk_widget_set_size_request(m_pgtkwidget, size.cx(), size.cy());

      });

   }


   void window::adjust_for_client_size(const ::int_size & sizeParam)
   {

      auto size = sizeParam;

      set_size(sizeParam + ::int_size(8, 40));

      // main_send([this, size]()
      //    {
      //
      //       RECT r{};
      //
      //       r.right = r.left + size.cx();
      //       r.bottom = r.top + size.cy();
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

      main_send([this]()
      {

            //gtk_window_set_position(GTK_WINDOW(m_pgtkwidget), GTK_WIN_POS_CENTER);
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


   ::innate_ui_gtk4::innate_ui * window::innate_ui()
   {

      return dynamic_cast <::innate_ui_gtk4::innate_ui *> (::innate_ui::window::innate_ui());

   }

   
   void window::defer_show_system_menu(::user::mouse * pmouse)
   {

      node()->defer_show_system_menu(pmouse);

   }


} // namespace innate_ui_gtk4



