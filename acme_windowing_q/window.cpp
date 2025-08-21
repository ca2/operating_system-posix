//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "acme/constant/message.h"
#include "acme/integrate/qt.h"
#include "acme/nano/graphics/device.h"
#include "acme/nano/nano.h"
#include "acme/operating_system/a_system_menu.h"
#include "acme/user/user/mouse.h"
#include "acme/platform/system.h"
#include "acme/user/user/interaction.h"
#include "acme/windowing/windowing.h"
#include "acme_windowing_q/QCustomTopWindow.h"
#include "acme_windowing_q/q_5_and_6.h"
#include <QMouseEvent>
#include <QMenu>
#include <acme/user/micro/elemental.h>
#include <QWindow>
// #include <xkbcommon/xkbcommon.h>
// #include <X11/XKBlib.h>
// #include <cairo/cairo-xcb.h>
//
//
// //unsigned long xcb_get_long_property(Display *d, Window w, char *property_name);
//
//
// //Window _xcb_get_active_window(Display * pdisplay);
//
//
// struct MWMHints
// {
//
//    unsigned long flags;
//    unsigned long functions;
//    unsigned long decorations;
//    long input_mode;
//    unsigned long status;
//
// };
//
// #define MWM_HINTS_FUNCTIONS     (1L << 0)
// #define MWM_HINTS_DECORATIONS   (1L << 1)
//
//
// #define MWM_FUNC_ALL            (1L << 0)
// #define MWM_FUNC_RESIZE         (1L << 1)
// #define MWM_FUNC_MOVE           (1L << 2)
// #define MWM_FUNC_MINIMIZE       (1L << 3)
// #define MWM_FUNC_MAXIMIZE       (1L << 4)
// #define MWM_FUNC_CLOSE          (1L << 5)
//
// /* MWM decorations values */
// #define MWM_DECOR_NONE          0
// #define MWM_DECOR_ALL           (1L << 0)
// #define MWM_DECOR_BORDER        (1L << 1)
// #define MWM_DECOR_RESIZEH       (1L << 2)
// #define MWM_DECOR_TITLE         (1L << 3)
// #define MWM_DECOR_MENU          (1L << 4)
// #define MWM_DECOR_MINIMIZE      (1L << 5)
// #define MWM_DECOR_MAXIMIZE      (1L << 6)
//


namespace q
{


   namespace acme
   {


      namespace windowing
      {


         window::window()
         {

            //m_psurface = nullptr;

         }


         window::~window()
         {

            //delete_drawing_objects();

            m_pnanodevice.release();

            // if(m_psurface != nullptr)
            // {
            //
            //    cairo_surface_destroy(m_psurface);
            //
            //    m_psurface = nullptr;
            //
            // }


            //   if (m_hfont)
            //   {
            //
            //      ::DeleteObject(m_hfont);
            //
            //      m_hfont = nullptr;
            //
            //   }

         }


         ::acme::windowing::display * window::get_display()
         {

            auto pwindowing = system()->acme_windowing();

            if (!pwindowing)
            {

               return nullptr;

            }

            ::cast<::acme::windowing::display> pdisplay = pwindowing->acme_display();

            if (!pdisplay)
            {

               return nullptr;

            }

            return pdisplay;

            // if (!m_pdisplaybase)
            // {
            //
            //    m_pdisplaybase = system()->acme_windowing()->display();
            //
            //    if (!m_pdisplaybase)
            //    {
            //
            //       throw ::exception(error_null_pointer);
            //
            //    }
            //
            // }
            //
            // return m_pdisplaybase;

         }


         void window::on_initialize_particle()
         {

            ::acme::windowing::window::on_initialize_particle();

         }


         void window::on_character(int iChar)
         {

            // fork([this, iChar]()
            // {
            //
            //    pacmeuserinteraction->on_char(iChar);
            //
            // });

         }


         void window::_draw(::nano::graphics::device * pnanodevice)
         {

            auto pacmeuserinteraction = m_pacmeuserinteraction.m_p;

            if (::is_set(pacmeuserinteraction))
            {

               pacmeuserinteraction->_on_draw(pnanodevice);

            }

            // ::cast<::micro::elemental> pelemental = m_pacmeuserinteraction;
            //
            // if (pelemental)
            // {
            //
            //    pelemental->on_draw(pnanodevice);
            //
            // }
            //
            // //pacmeuserinteraction->draw(pnanodevice);

         }


         bool window::is_active_window()
         {

            //return m_pacmeuserinteraction->is_active();

            return true;

         }


         // void window::delete_drawing_objects()
         // {
         //
         //    pacmeuserinteraction->delete_drawing_objects();
         //
         // }


         // bool window::get_dark_mode()
         // {
         //
         //    return system()->dark_mode();
         //
         // }


         // void window::create_drawing_objects()
         // {
         //
         //    pacmeuserinteraction->create_drawing_objects();
         //
         // }


         // void window::update_drawing_objects()
         // {
         //
         //    pacmeuserinteraction->update_drawing_objects();
         //
         // }


         void window::create_window()
         {

            auto λCreateWindow = [this]()
            {

               _create_window();

            };

            main_send(λCreateWindow);


            //          get_display();
            //
            //          unsigned int uEventMask =       XCB_EVENT_MASK_PROPERTY_CHANGE
            //                                 | XCB_EVENT_MASK_EXPOSURE
            //                                 | XCB_EVENT_MASK_BUTTON_PRESS
            //                                 | XCB_EVENT_MASK_BUTTON_RELEASE
            //                                 | XCB_EVENT_MASK_KEY_PRESS
            //                                 | XCB_EVENT_MASK_KEY_RELEASE
            //                                 | XCB_EVENT_MASK_POINTER_MOTION
            //                                 | XCB_EVENT_MASK_STRUCTURE_NOTIFY
            //                                 | XCB_EVENT_MASK_FOCUS_CHANGE
            //                                 | XCB_EVENT_MASK_LEAVE_WINDOW
            //                                 | XCB_EVENT_MASK_ENTER_WINDOW
            //          ;
            //
            //          auto colormap = m_pdisplay->m_colormap;
            //
            //          auto windowRoot = m_pdisplay->m_windowRoot;
            //
            //          xcb_window_t window = xcb_generate_id(m_pdisplay->m_pconnection);
            //
            //          int x = pacmeuserinteraction->m_rectangle.left();
            //          int y = pacmeuserinteraction->m_rectangle.top();
            //          int cx = pacmeuserinteraction->m_rectangle.width();
            //          int cy = pacmeuserinteraction->m_rectangle.height();
            //
            //          unsigned int uaValueList[5];
            //
            //          uaValueList[0] = 0; // XCB_CW_BACK_PIXMAP
            //          uaValueList[1] = 0; // XCB_CW_BORDER_PIXEL
            //          uaValueList[2] = 1; // XCB_CW_OVERRIDE_REDIRECT
            //          uaValueList[3] = uEventMask; // XCB_CW_EVENT_MASK
            //          uaValueList[4] = colormap; // XCB_CW_COLORMAP
            //
            //          auto cookie = xcb_create_window(
            //             m_pdisplay->m_pconnection,
            //             m_pdisplay->m_pdepth->depth,
            //             window,
            //             m_pdisplay->m_windowRoot,
            //             x, y,
            //             cx, cy,
            //             0,
            //             XCB_WINDOW_CLASS_INPUT_OUTPUT,
            //             m_pdisplay->m_pvisualtype->visual_id,
            //             XCB_CW_BACK_PIXMAP
            //             | XCB_CW_BORDER_PIXEL
            //             | XCB_CW_OVERRIDE_REDIRECT
            //             | XCB_CW_EVENT_MASK
            //             | XCB_CW_COLORMAP,
            //             uaValueList);
            //
            //          auto estatus = m_pdisplay->_request_check(cookie);
            //
            //          if(!estatus)
            //          {
            //
            //             throw exception(estatus);
            //
            //          }
            //
            //          m_window = window;
            //
            //          m_pdisplay->add_listener(this);
            //
            //          m_pdisplay->add_window(this);
            //
            // #if 0
            //
            //          // _NET_WM_WINDOW_TYPE_SPLASH
            //          // KDE seems to close this type of window when it is clicked
            //
            //          if(pacmeuserinteraction->m_bStartCentered)
            //          {
            //
            //             auto atomWindowType = XInternAtom(m_pdisplay->m_pdisplay, "_NET_WM_WINDOW_TYPE", true);
            //
            //             auto atomWindowTypeSplash = XInternAtom(m_pdisplay->m_pdisplay, "_NET_WM_WINDOW_TYPE_SPLASH", true);
            //
            //             if (atomWindowType != None && atomWindowTypeSplash != None)
            //             {
            //
            //                XChangeProperty(m_pdisplay->m_pdisplay, m_window,
            //                                atomWindowType, XA_ATOM, 32, PropModeReplace,
            //                                (unsigned char *) &atomWindowTypeSplash, 1);
            //
            //             }
            //
            //          }
            //
            // #endif
            //
            //          //         if(pacmeuserinteraction->m_bArbitraryPositioning)
            //          //         {
            //          //
            //          //            XSetWindowAttributes attributes;
            //          //
            //          //            attributes.override_redirect = True;
            //          //
            //          //            XChangeWindowAttributes(m_pdisplay->m_pdisplay, m_window,
            //          //                             CWOverrideRedirect,
            //          //                             &attributes);
            //          //
            //          //   //      MWMHints mwm_hints;
            //          //   //
            //          //   //      Atom MotifHints = XInternAtom(m_pdisplay->m_pdisplay, "_MOTIF_WM_HINTS", 0);
            //          //   //
            //          //   //      mwm_hints.flags = MWM_HINTS_FUNCTIONS;
            //          //   //      mwm_hints.functions=  MWM_FUNC_MOVE;
            //          //   //
            //          //   //      XMapWindow(m_pdisplay->m_pdisplay, m_window);
            //          //   //      XChangeProperty(m_pdisplay->m_pdisplay, m_window, MotifHints, MotifHints, 32, PropModeReplace, (unsigned char *)&mwm_hints, 5);
            //          //
            //          //         }
            //
            //          //m_pdisplay->XSelectInput(m_pdisplay->m_pdisplay, m_window, ExposureMask | KeyPressMask | VisibilityChangeMask | StructureNotifyMask | ButtonPressMask | PointerMotionMask | ButtonMotionMask | ButtonReleaseMask | LeaveWindowMask);
            //
            //          nano_window_on_create();
            //
            //          //XMapWindow(m_pdisplay->m_pdisplay, m_window);

         }


         void window::_create_window()
         {

            auto pacmeuserinteraction = m_pacmeuserinteraction;

            pacmeuserinteraction->on_before_create_window(this);

            //auto r = pacmeuserinteraction->get_rectangle();

            int x = m_pointWindow.x();

            int y = m_pointWindow.y();

            int cx = m_sizeWindow.cx();

            int cy = m_sizeWindow.cy();

            auto pmainwindow = ___new QCustomTopWindow(this);

            m_pqwidget = pmainwindow;

            pmainwindow->setWindowFlags(Qt::FramelessWindowHint | Qt::CustomizeWindowHint); // No window decorations
            pmainwindow->setAttribute(Qt::WA_TranslucentBackground); // Translucent background
            pmainwindow->setAttribute(Qt::WA_NoSystemBackground, true);
            pmainwindow->setAttribute(Qt::WA_OpaquePaintEvent, false);

            pmainwindow->setMouseTracking(true);

            pmainwindow->move(x, y);
            pmainwindow->resize(cx, cy);

            set_interface_client_size({cx, cy});

            on_create_window();

         }

         //::atom window::hit_test(int x, int y)
         //{
         //
         //   for (int i = 0; i < m_iButtonCount; i++)
         //   {
         //      if (m_buttona[i].m_rectangle.contains(int_point(x, y)))
         //      {
         //
         //         return m_buttona[i].m_edialogresult;
         //
         //      }
         //
         //   }
         //
         //   return e_dialog_result_none;
         //
         //}
         //

         // void window::on_left_button_down(::user::mouse * pmouse)
         // {
         //
         //    pacmeuserinteraction->on_left_button_down(pmouse);
         //
         // }
         //
         //
         // void window::on_left_button_up(::user::mouse * pmouse)
         // {
         //
         //    pacmeuserinteraction->on_left_button_up(pmouse);
         // }
         //
         //
         //
         // void window::on_right_button_down(::user::mouse * pmouse)
         // {
         //
         //    pacmeuserinteraction->on_right_button_down(pmouse);
         //
         // }
         //
         //
         // void window::on_right_button_up(::user::mouse * pmouse)
         // {
         //
         //    pacmeuserinteraction->on_right_button_up(pmouse);
         // }
         //
         //
         // void window::on_mouse_move(::user::mouse * pmouse)
         // {
         //
         //    pacmeuserinteraction->on_mouse_move(pmouse);
         //
         // }
         //
         //
         // ::payload window::get_result()
         // {
         //
         //    return pacmeuserinteraction->get_result();
         //
         // }
         //
         //
         // ::micro::child * window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
         // {
         //
         //    return pacmeuserinteraction->hit_test(pmouse, ezorder);
         //
         // }


         //LRESULT CALLBACK ::micro::message_box::s_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
         //{
         //if (msg == WM_NCCREATE)
         //{
         //
         //   CREATESTRUCT * pcreatestruct = (CREATESTRUCT *)lParam;
         //   SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pcreatestruct->lpCreateParams);
         //
         //}
         //::micro::message_box * pwindow = (::micro::message_box *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
         //
         //if (!pwindow)
         //{
         //   return DefWindowProc(hwnd, msg, wParam, lParam);
         //}
         //return pwindow->window_procedure(msg, wParam, lParam);
         //
         //}

         //#ifndef int_x
         //#define lparam_int_x(lparam)                          ((int)(short)LOWORD(lparam))
         //#endif
         //
         //
         //#ifndef int_y
         //#define lparam_int_y(lparam)                          ((int)(short)HIWORD(lparam))
         //#endif
         //
         ////LRESULT window::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
         //{
         //   switch (message)
         //   {
         //      case WM_CLOSE:
         //         DestroyWindow(m_hwnd);
         //         break;
         //      case WM_DESTROY:
         //         PostQuitMessage(0);
         //         break;
         //      case WM_CREATE:
         //      {
         //         update_drawing_objects();
         //      }
         //         break;
         //      case WM_CHAR:
         //      {
         //         on_char((int) wparam);
         //         return 0;
         //      }
         //         break;
         //      case WM_LBUTTONDOWN:
         //         on_left_button_down(lparam_int_x(lparam), lparam_int_y(lparam));
         //         break;
         //      case WM_MOUSEMOVE:
         //         on_mouse_move(lparam_int_x(lparam), lparam_int_y(lparam));
         //         break;
         //      case WM_LBUTTONUP:
         //      {
         //         on_left_button_up(lparam_int_x(lparam), lparam_int_y(lparam));
         //
         //      }
         //
         //         break;
         //      case WM_PAINhttps://www.dropbox.com/scl/fi/u8p00c0pz6b36q57svqlz/static_RedDotLogics_PixelPerfectPro-2.6.0.3.zip?rlkey=zhw4b7tkv0wx6nb4xek8zeo3t&dl=0T:
         //      {
         //         PAINTSTRUCT paintstruct{};
         //         HDC hdc = BeginPaint(m_hwnd, &paintstruct);
         //         draw(hdc);
         //         EndPaint(m_hwnd, &paintstruct);
         //      }
         //         break;
         //      case WM_NCACTIVATE:
         //      {
         //         LRESULT lresult = DefWindowProc(m_hwnd, message, wparam, lparam);
         //         m_bNcActive = wparam != 0;
         //         redraw();
         //
         //         return lresult;
         //
         //      }
         //      case WM_ACTIVATE:
         //      {
         //         LRESULT lresult = DefWindowProc(m_hwnd, message, wparam, lparam);
         //
         //
         //         return lresult;
         //
         //      }
         //      default:
         //         return DefWindowProc(m_hwnd, message, wparam, lparam);
         //   }
         //   return 0;
         //}
         //
         //
         //HINSTANCE nano_message_box_hinstance()
         //{
         //
         //   HINSTANCE hinstanceWndProc = (HINSTANCE) ::GetModuleHandleA("acme.dll");
         //
         //   if (hinstanceWndProc == nullptr)
         //   {
         //
         //      hinstanceWndProc = (HINSTANCE)::GetModuleHandleA(NULL);
         //
         //   }
         //
         //   return hinstanceWndProc;
         //
         //}

         //
         //void register_nano_window_class()
         //{
         //
         //   if (g_bNanoWindowClassRegistered)
         //   {
         //
         //      return;
         //
         //   }
         //
         //   auto hinstanceWndProc = nano_message_box_hinstance();
         //
         //   WNDCLASSEX wndclassex;
         //
         //   //Step 1: Registering the Window Class
         //   wndclassex.cbSize = sizeof(WNDCLASSEX);
         //   wndclassex.style = 0;
         //   wndclassex.lpfnWndProc = &message_box_window_procedure;
         //   wndclassex.cbClsExtra = 0;
         //   wndclassex.cbWndExtra = 0;
         //   wndclassex.hInstance = hinstanceWndProc;
         //   wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
         //   wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
         //   wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
         //   wndclassex.lpszMenuName = NULL;
         //   wndclassex.lpszClassName = _T(NANO_MESSAGE_BOX_WINDOW_CLASS);
         //   wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
         //
         //   if (!RegisterClassEx(&wndclassex))
         //   {
         //
         //      throw ::exception(error_failed, "Failed to register nano message box window class.");
         //
         //   }
         //
         //   g_bNanoWindowClassRegistered = true;
         //
         //}
         //


         void window::show_window()
         {

            auto λ_show_window = [this]()
            {

               _map_window();

               _raise_window();

               set_active_window();

            };

            main_post(λ_show_window);

         }


         ::e_status window::_map_window()
         {

            m_pqwidget->show();

            return ::success;

         }


         ::e_status window::_unmap_window()
         {

            //auto estatus = m_pdisplay->_unmap_window(m_window);

            m_pqwidget->hide();

            return ::success;

         }


         ::e_status window::_raise_window()
         {

            //auto estatus = m_pdisplay->_raise_window(m_window);

            m_pqwidget->raise();

            return ::success;

         }


         void window::hide_window()
         {

            _unmap_window();

         }


         void window::set_active_window()
         {

            //auto estatus = m_pdisplay->_set_active_window(m_window);

            m_pqwidget->activateWindow();

            m_pqwidget->setWindowState((m_pqwidget->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);

         }


         void window::_main_send(const ::procedure & procedure)
         {

            system()->acme_windowing()->_main_send(procedure);

         }


         void window::_main_post(const ::procedure & procedure)
         {

            system()->acme_windowing()->_main_post(procedure);

         }

         // bool window::_on_event(xcb_generic_event_t *pevent)
         // {
         //
         //    if(m_window == None)
         //    {
         //
         //       return false;
         //
         //    }
         //
         //    auto event_type = pevent->response_type;
         //
         //    if (event_type == XCB_CONFIGURE_NOTIFY)
         //    {
         //
         //       auto pconfigure = (xcb_configure_notify_happening_t *) pevent;
         //
         //       if (pconfigure->window != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //       pacmeuserinteraction->m_rectangle.left() = pconfigure->x;
         //
         //       pacmeuserinteraction->m_rectangle.top() = pconfigure->y;
         //
         //       pacmeuserinteraction->m_rectangle.right() = pconfigure->x + pconfigure->width;
         //
         //       pacmeuserinteraction->m_rectangle.bottom() = pconfigure->y + pconfigure->height;
         //
         //       if (m_psurface)
         //       {
         //
         //          cairo_xcb_surface_set_size(m_psurface, pacmeuserinteraction->m_rectangle.width(),
         //                                      pacmeuserinteraction->m_rectangle.height());
         //
         //       }
         //
         //    }
         //    else if (event_type == XCB_UNMAP_NOTIFY)
         //    {
         //
         //       auto punmap = (xcb_unmap_notify_event_t *) pevent;
         //
         //       if (punmap->window != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //
         //       informationf("UnmapNotify");
         //
         //    }
         //    else if (event_type == XCB_MAP_NOTIFY)
         //    {
         //
         //       auto pmap = (xcb_map_notify_event_t *) pevent;
         //
         //       if (pmap->window != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //
         //    }
         //    else if (event_type == XCB_EXPOSE)
         //    {
         //
         //       auto pexpose = (xcb_expose_event_t *) pevent;
         //
         //       if (pexpose->window != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //       if (!m_psurface)
         //       {
         //
         //          int_rectangle rectangleX;
         //
         //          get_client_rectangle(rectangleX);
         //
         //          m_psurface = cairo_xcb_surface_create(
         //             m_pdisplay->m_pconnection,
         //             m_window,
         //             m_pdisplay->m_pvisualtype,
         //             rectangleX.width(),
         //             rectangleX.height());
         //
         //          auto pdc = cairo_create(m_psurface);
         //
         //          m_pnanodevice = øallocate ::cairo::nano::graphics::device(pdc);
         //
         //       }
         //
         //       _update_window();
         //
         //    }
         //    else if (event_type == XCB_PROPERTY_NOTIFY)
         //    {
         //
         //       auto pproperty = (xcb_property_notify_event_t *) pevent;
         //
         //       if (pproperty->window != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //       //informationf("PropertyNotify");
         //
         //    }
         //    else if (event_type == XCB_KEY_PRESS)
         //    {
         //
         //       auto pkey = (xcb_key_press_event_t *) pevent;
         //
         //       if (pkey->happening != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //       auto keysym = XkbKeycodeToKeysym((Display *) m_pdisplay->m_pX11Display, pkey->detail, 0, pkey->state & ShiftMask ? 1 : 0);
         //
         //       int iChar = xkb_keysym_to_utf32(keysym);
         //
         //       on_char(iChar);
         //
         //    }
         //    else if (event_type == XCB_KEY_RELEASE)
         //    {
         //
         //       auto pkey = (xcb_key_release_event_t *) pevent;
         //
         //       if (pkey->happening != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //
         //    }
         //    else if (event_type == XCB_BUTTON_PRESS)
         //    {
         //
         //       auto pbutton = (xcb_button_press_event_t *) pevent;
         //
         //       if (pbutton->happening != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //       if (pbutton->detail == XCB_BUTTON_INDEX_1)
         //       {
         //
         //          auto pmouse = øcreate_new < ::user::mouse >();
         //
         //          pmouse->m_pointHost = {pbutton->event_x, pbutton->event_y};
         //
         //          pmouse->m_pointAbsolute = {pbutton->root_x, pbutton->root_y};
         //
         //          on_left_button_down(pmouse);
         //
         //       }
         //       else if (pbutton->detail == XCB_BUTTON_INDEX_3)
         //       {
         //
         //          auto pmouse = øcreate_new < ::user::mouse >();
         //
         //          pmouse->m_pointHost = {pbutton->event_x, pbutton->event_y};
         //
         //          pmouse->m_pointAbsolute = {pbutton->root_x, pbutton->root_y};
         //
         //          on_right_button_down(pmouse);
         //
         //       }
         //
         //    }
         //    else if (event_type == XCB_BUTTON_RELEASE)
         //    {
         //
         //       auto pbutton = (xcb_button_release_event_t *) pevent;
         //
         //       if (pbutton->happening != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //
         //       if (pbutton->detail == XCB_BUTTON_INDEX_1)
         //       {
         //
         //          auto pmouse = øcreate_new < ::user::mouse >();
         //
         //          pmouse->m_pointHost = {pbutton->event_x, pbutton->event_y};
         //
         //          pmouse->m_pointAbsolute = {pbutton->root_x, pbutton->root_y};
         //
         //          on_left_button_up(pmouse);
         //
         //       }
         //       else if (pbutton->detail == XCB_BUTTON_INDEX_3)
         //       {
         //
         //          auto pmouse = øcreate_new < ::user::mouse >();
         //
         //          pmouse->m_pointHost = {pbutton->event_x, pbutton->event_y};
         //
         //          pmouse->m_pointAbsolute = {pbutton->root_x, pbutton->root_y};
         //
         //          on_right_button_up(pmouse);
         //
         //       }
         //
         //    }
         //    else if (event_type == MotionNotify)
         //    {
         //
         //       auto pmotion = (xcb_motion_notify_event_t *) pevent;
         //
         //       if (pmotion->happening != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //       auto pmouse = øcreate_new < ::user::mouse >();
         //
         //       pmouse->m_pointHost = {pmotion->event_x, pmotion->event_y};
         //
         //       pmouse->m_pointAbsolute = {pmotion->root_x, pmotion->root_y};
         //
         //       on_mouse_move(pmouse);
         //
         //    }
         //    else if (event_type == LeaveNotify)
         //    {
         //
         //       auto pleave = (xcb_leave_notify_happening_t *) pevent;
         //
         //       if (pleave->happening != m_window)
         //       {
         //
         //          return false;
         //
         //       }
         //
         //       if (pacmeuserinteraction->m_pchildHover)
         //       {
         //
         //          auto pmouse = øcreate_new < ::user::mouse >();
         //
         //          pmouse->m_pointHost = {I32_MINIMUM, I32_MINIMUM};
         //
         //          pmouse->m_pointAbsolute = {I32_MINIMUM, I32_MINIMUM};
         //
         //          pacmeuserinteraction->m_pchildHover->on_mouse_move(pmouse);
         //
         //          pacmeuserinteraction->m_pchildHover = nullptr;
         //
         //          pacmeuserinteraction->redraw();
         //
         //       }
         //
         //    }
         //
         //    return true;
         //
         // }


         void window::_update_window()
         {

            ::cast<::micro::elemental> pelemental = m_pacmeuserinteraction;

            if (m_pnanodevice && pelemental)
            {

               m_pnanodevice->on_begin_draw();

               pelemental->on_draw(m_pnanodevice);

               m_pnanodevice->on_end_draw();

               //cairo_surface_flush(m_psurface);

            }

         }




         //void window::aaa_message_loop()
         //{
         //
         //   while(aaa_message_loop_step())
         //   {
         //
         //      system()->m_pnode->run_posted_routines();
         //
         //   }
         //
         //   informationf("window::aaa_message_loop exit");
         //
         //}


         //
         //
         //


         //   MSG msg;
         //
         //   while (::task_get_run() && GetMessage(&msg, NULL, 0, 0) > 0)
         //   {
         //
         //      TranslateMessage(&msg);
         //
         //      DispatchMessage(&msg);
         //
         //   }
         //
         //}

         //void window::add_child(::micro::child * pchild)
         //{
         //
         //   pchild->m_pwindow = m_puserinteractionbasethis;
         //
         //   m_childa.add(pchild);
         //
         //}


         void window::redraw()
         {

            //::RedrawWindow(m_hwnd, nullptr, nullptr, RDW_UPDATENOW | RDW_INVALIDATE);

            _update_window();

         }


         //
         //LRESULT window::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
         //{
         //   switch (message)
         //   {
         //   case WM_CLOSE:
         //      DestroyWindow(m_hwnd);
         //      break;
         //   case WM_DESTROY:
         //      PostQuitMessage(0);
         //      break;
         //   case WM_CREATE:
         //   {
         //      update_drawing_objects();
         //   }
         //   break;
         //   case WM_LBUTTONDOWN:
         //      on_left_button_down(lparam_int_x(lparam), lparam_int_y(lparam));
         //      break;
         //   case WM_LBUTTONUP:
         //   {
         //      on_left_button_up(lparam_int_x(lparam), lparam_int_y(lparam));
         //   }
         //
         //   break;
         //   case WM_PAINT:
         //   {
         //      PAINTSTRUCT paintstruct{};
         //      HDC hdc = BeginPaint(m_hwnd, &paintstruct);
         //      draw(hdc);
         //      EndPaint(m_hwnd, &paintstruct);
         //   }
         //   break;
         //   default:
         //      return DefWindowProc(m_hwnd, message, wparam, lparam);
         //   }
         //   return 0;
         //}


         void window::destroy()
         {

            _unmap_window();

            //m_pdisplay->_destroy_window(m_window);

            //m_pdisplay->erase_listener(this);

            //m_pdisplay->erase_window(this);

            m_pqwidget->close();

            delete m_pqwidget;

            m_pqwidget = nullptr;

            //XCloseDisplay(m_pdisplay->m_pdisplay);

            m_happeningEnd.set_happening();

            ::acme::windowing::window::destroy();

         }


         // void window::on_click(const ::payload & payloadParam, ::user::mouse * pmouse)
         // {
         //
         //    auto payload(payloadParam);
         //
         //    fork([this, payload, pmouse]()
         //         {
         //
         //            pacmeuserinteraction->on_click(payload, pmouse);
         //
         //         }, {pmouse});
         //
         // }


         // void window::on_right_click(const ::payload & payloadParam, ::user::mouse * pmouse)
         // {
         //
         //    auto payload(payloadParam);
         //
         //    fork([this, payload, pmouse]()
         //         {
         //
         //            pacmeuserinteraction->on_right_click(payload, pmouse);
         //
         //         }, {pmouse});
         //
         // }


         void window::set_position_unlocked(const ::int_point & point)
         {

            m_pqwidget->move(point.x(), point.y());

         }


         void window::set_size_unlocked(const ::int_size & size)
         {

            m_pqwidget->resize(size.cx(), size.cy());

         }


         void window::_on_set_focus()
         {

            //m_bKeyboardFocus = true;

         }


         void window::_on_kill_focus()
         {

            //m_bKeyboardFocus = false;

         }



         void window::_on_wheel(QWheelEvent * happening)
         {


         }


         // void window::set_mouse_capture()
         // {
         //
         //
         //    //auto estatus = m_pdisplay->_set_mouse_capture(m_window);
         //
         //    //      if (XGrabPointer(m_pdisplay->m_pdisplay, m_window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
         //    //                       GrabModeAsync, GrabModeAsync, None, None, CurrentTime) != GrabSuccess)
         //    //      {
         //    //
         //    //         throw ::exception(error_exception);
         //    //
         //    //      }
         //
         //
         //    //      auto pdisplay = xcb_display();
         //    //
         //    //      if(pdisplay)
         //    //      {
         //    //
         //    //         pdisplay->_on_capture_changed_to(this);
         //    //
         //    //      }
         //
         //    m_pqwidget->grabMouse();
         //
         //
         // }


         void window::_on_qimage_draw(QImage * pqimage)
         {

            if (::is_null(m_pnanodevice))
            {

               return;

            }

            auto pacmeuserinteraction = m_pacmeuserinteraction.get();

            if (::is_set(pacmeuserinteraction))
            {

               pacmeuserinteraction->_on_draw(m_pnanodevice);

            }

            auto pixmap = m_pnanodevice->pixmap();

            QImage image(
               (const uchar *) pixmap.m_pimage32,
               pixmap.width(),
               pixmap.height(),
               pixmap.m_iScan,
               QImage::Format_ARGB32_Premultiplied);

            QPainter painter(pqimage);

            painter.drawImage(0, 0, image);

         }


         // void window::release_mouse_capture()
         // {
         //
         //    //int bRet = XUngrabPointer(m_pdisplay->m_pdisplay, CurrentTime);
         //
         //    //m_pdisplay->_release_mouse_capture();
         //
         //    m_pqwidget->releaseMouse();
         //
         // }

         //
         // void window::get_client_rectangle(::int_rectangle & rectangle)
         // {
         //
         //    xcb_get_geometry_reply_t geometry;
         //
         //    _get_geometry(&geometry);
         //
         //    rectangle.left() = 0;
         //    rectangle.top() = 0;
         //    rectangle.right() = geometry.width;
         //    rectangle.bottom() = geometry.height;
         //
         // }


         ::int_rectangle window::get_window_rectangle()
         {

            ::int_rectangle rectangle;

            auto qrect = m_pqwidget->rect();

            ::copy(rectangle, qrect);

            return rectangle;

            // xcb_get_geometry_reply_t geometry;
            //
            // _get_geometry(&geometry);
            //
            // rectangle.left() = geometry.x;
            // rectangle.top() = geometry.y;
            // rectangle.right() = geometry.x + geometry.width;
            // rectangle.bottom() = geometry.y + geometry.height;

         }


         // void window::_wm_nodecorations(int iMap)
         // {
         //
         //    m_pdisplay->_set_nodecorations(m_window, iMap);
         //
         // }
         //
         //
         // void window::_get_geometry(xcb_get_geometry_reply_t * pgeometry)
         // {
         //
         //    m_pdisplay->_get_window_geometry(pgeometry, m_window);
         //
         //
         // }

         void window::_on_mouse_press(QMouseEvent * pevent)
         {

            if (m_bResizingWindowFromBottomRight ||
                m_bRepositioningWindowFromCenter)
            {
               m_pqwidget->releaseMouse();
               m_bRepositioningWindowFromCenter = false;
               m_bResizingWindowFromBottomRight = false;
            }

            m_bPerformingEntireRepositionProcess = false;
            m_bPerformingEntireResizingProcess = false;

            ::cast<::micro::elemental> pelemental = m_pacmeuserinteraction;

            if (::is_set(pelemental))
            {

               auto pmouse = øcreate_new<::user::mouse>();

               // pmouse->m_oswindow = this;
               //
               // pmouse->m_pwindow = this;

               // GdkEventSequence *sequence = gtk_gesture_get_last_updated_sequence(GTK_GESTURE(pgesture));
               //
               // // Get the GdkEvent from the sequence
               // GdkEvent *happening = gtk_gesture_get_last_event(GTK_GESTURE(pgesture), sequence);
               //
               // guint32 timestamp = gdk_event_get_time (happening);

               pmouse->m_iTimestamp = pevent->timestamp();

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

               m_pointCursor2.x() = pevent->globalPosition().x();
               m_pointCursor2.y() = pevent->globalPosition().y();

               pmouse->m_pointHost.x() = pevent->position().x();
               pmouse->m_pointHost.y() = pevent->position().y();

#else

               m_pointCursor2.x() = pevent->globalPos().x();
               m_pointCursor2.y() = pevent->globalPos().y();

               pmouse->m_pointHost.x() = pevent->pos().x();
               pmouse->m_pointHost.y() = pevent->pos().y();

#endif

               pmouse->m_pointAbsolute = m_pointCursor2;

               if (pevent->button() == Qt::MouseButton::LeftButton)
               {

                  pmouse->m_emessage = e_message_left_button_down;

                  pelemental->fore_on_left_button_down(pmouse);

                  if (!pmouse->m_bRet)
                  {

                     pelemental->back_on_left_button_down(pmouse);

                  }

               }
               else if (pevent->button() == Qt::MouseButton::RightButton)
               {

                  pmouse->m_emessage = e_message_right_button_down;

                  pelemental->fore_on_right_button_down(pmouse);

                  if (!pmouse->m_bRet)
                  {

                     pelemental->back_on_right_button_down(pmouse);

                  }

               }
               else if (pevent->button() == Qt::MouseButton::MiddleButton)
               {

                  pmouse->m_emessage = e_message_middle_button_down;

               }

               // //pmouse->m_time.m_iSecond = millis / 1_k;
               //
               // //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;
               //
               // //pwindow->message_handler(pmouse);
               //
               // //wayland_windowing()->post_ui_message(pmouse);
               //
               // if(m_bPendingStartMove)
               // {
               //    m_bPendingStartMove =false;
               //
               //    defer_perform_entire_reposition_process(pmouse);
               //    return;
               //
               // }
               //
               // pwindow->message_handler(pmouse);
            }

            //}

         }


         void window::_on_mouse_release(QMouseEvent * pevent)
         {

            if (m_bResizingWindowFromBottomRight ||
                m_bRepositioningWindowFromCenter)
            {
               m_pqwidget->releaseMouse();
               m_bRepositioningWindowFromCenter = false;
               m_bResizingWindowFromBottomRight = false;
            }

            //if(n_press == 1)
            {

               // auto button = gtk_gesture_single_get_current_button(GTK_GESTURE_SINGLE(pgesture));
               //
               // if (button == 1)
               // {
               //
               //    moving = FALSE;
               //    resizing = FALSE;
               // }


               ::cast<::micro::elemental> pelemental = m_pacmeuserinteraction;

               if (::is_set(pelemental))
               {

                  auto pmouse = øcreate_new<::user::mouse>();

                  // pmouse->m_oswindow = this;
                  //
                  // pmouse->m_pwindow = this;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

                  m_pointCursor2.x() = pevent->globalPosition().x();
                  m_pointCursor2.y() = pevent->globalPosition().y();

                  pmouse->m_pointHost.x() = pevent->position().x();
                  pmouse->m_pointHost.y() = pevent->position().y();

#else

                  m_pointCursor2.x() = pevent->globalPos().x();
                  m_pointCursor2.y() = pevent->globalPos().y();

                  pmouse->m_pointHost.x() = pevent->pos().x();
                  pmouse->m_pointHost.y() = pevent->pos().y();

#endif

                  pmouse->m_pointAbsolute = m_pointCursor2;

                  if (pevent->button() == Qt::MouseButton::LeftButton)
                  {

                     pmouse->m_emessage = e_message_left_button_up;

                     pelemental->fore_on_left_button_up(pmouse);

                     if (!pmouse->m_bRet)
                     {

                        pelemental->back_on_left_button_up(pmouse);

                     }

                  }
                  else if (pevent->button() == Qt::MouseButton::RightButton)
                  {

                     pmouse->m_emessage = e_message_right_button_up;

                     pelemental->fore_on_right_button_up(pmouse);

                     if (!pmouse->m_bRet)
                     {

                        pelemental->back_on_right_button_up(pmouse);

                     }

                  }
                  else if (pevent->button() == Qt::MouseButton::MiddleButton)
                  {

                     pmouse->m_emessage = e_message_middle_button_up;

                  }

                  //pmouse->m_time.m_iSecond = millis / 1_k;

                  //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;

                  //pwindow->message_handler(pmouse);

                  //wayland_windowing()->post_ui_message(pmouse);

               }

            }

         }

//
//    // Perform resizing as the mouse moves
//    static void on_motion_notify(GtkEventControllerMotion* pcontroller, double x, double y, gpointer p)
//    {
//
//       auto * pwindow = (::windowing_kde5::window *)p;
//
//       pwindow->_on_motion_notify(pcontroller, x, y);
//
//    }
//
//

         bool window::defer_perform_entire_reposition_process(::user::mouse* pmouse)
         {

            auto pqwindow = m_pqwidget->windowHandle();

            if(!pqwindow)
            {

               return false;

            }

            m_bPerformingEntireRepositionProcess = true;

            pqwindow->startSystemMove();

            return true;
         }


         bool window::defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing,
                                                            ::user::mouse* pmouse)
         {

            auto pqwindow = m_pqwidget->windowHandle();

            if(!pqwindow)
            {

               return false;

            }

            m_bPerformingEntireResizingProcess = true;

            auto edges = ::q::as_qt_edges(eframeSizing);

            pqwindow->startSystemResize(edges);

            return true;

         }


         void window::_on_mouse_motion(QMouseEvent * pevent)
         {
//
//
//       //  if (resizing)
//       // {
//       //
//       //     if(kde5_windowing()->m_pdisplay->is_x11())
//       //     {
//       //        auto cursor_name = _gtk_get_resize_cursor_name(resize_edge);
//       //        // Resize the window
//       //        int dx = x - start_x;
//       //        int dy = y - start_y;
//       //        int new_width = start_width;
//       //        int new_height = start_height;
//       //        int xset = INT_MIN;
//       //        int yset = INT_MIN;
//       //
//       //        if (resize_edge == e_window_edge_east || resize_edge == e_window_edge_north_east  || resize_edge == e_window_edge_south_east)
//       //           new_width += dx;
//       //        if (resize_edge == e_window_edge_west || resize_edge == e_window_edge_north_west  || resize_edge == e_window_edge_south_west)
//       //        {
//       //           new_width -= dx;
//       //           xset=start_window_x + dx;
//       //           yset=start_window_y;
//       //        }
//       //        if (resize_edge == e_window_edge_south || resize_edge == e_window_edge_south_east  || resize_edge == e_window_edge_south_west)
//       //           new_height += dy;
//       //        if  (resize_edge == e_window_edge_north || resize_edge == e_window_edge_north_east  || resize_edge == e_window_edge_north_west)
//       //        {
//       //           new_height -= dy;
//       //           xset=start_window_x;
//       //           yset=start_window_y + dy;
//       //        }
//       //
//       //        new_width = MAX(new_width, 100); // Set minimum size
//       //        new_height = MAX(new_height, 100);
//       //
//       //        if(xset != INT_MIN && yset != INT_MIN)
//       //        {
//       //
//       //           _unlocked_defer_set_window_position({xset, yset}, {new_width, new_height});
//       //
//       //        }
//       //        else
//       //        {
//       //           _unlocked_defer_set_window_size({new_width, new_height});
//       //        }
//       //     }
//       // }
//       // else if (moving)
//       // {
//       //    if(kde5_windowing()->m_pdisplay->is_x11())
//       //    {
//       //       // Move the window
//       //       int dx = x - start_x;
//       //       int dy = y - start_y;
//       //       _unlocked_defer_set_window_position({start_window_x + dx, start_window_y + dy});
//       //    }
//       // }
//       // else
//       // {
//       //
//       //    auto edge = detect_resize_edge(m_pgtkwidget, x, y);
//       //
//       //    //GdkWindow* gdk_window = gtk_widget_get_window(widget);
//       //    //      GdkDisplay* display = gdk_window_get_display(gdk_window);
//       //
//       //    auto cursor_name = _gtk_get_resize_cursor_name(edge);
//       //
//       //    _set_cursor_from_name(cursor_name);
//       //
//       // }
//


            if (m_bRepositioningWindowFromCenter)
            {

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

               auto p = pevent->globalPosition();

#else

               auto p = pevent->globalPos();

#endif


               p.setX(p.x() - m_pqwidget->size().width() / 2);
               p.setY(p.y() - m_pqwidget->size().height() / 2);

               m_pqwidget->move(p.x(), p.y());

               return;

            }
            else if (m_bResizingWindowFromBottomRight)
            {

               QSize s;

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

               auto p = pevent->globalPosition();

#else

               auto p = pevent->globalPos();

#endif

               s.setWidth(p.x() - m_pqwidget->pos().x());
               s.setHeight(p.y() - m_pqwidget->pos().y());

               m_pqwidget->resize(s);

               return;

            }

            ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

            if (::is_set(pelemental))
            {

               auto pmouse = øcreate_new<::user::mouse>();

               // pmouse->m_oswindow = this;
               //
               // pmouse->m_pwindow = this;

               pmouse->m_emessage = e_message_mouse_move;


               //pmouse->m_time.m_iSecond = millis / 1_k;

               //pmouse->m_time.m_iNanosecond = (millis % 1_k) * 1_M;

               //pwindow->message_handler(pmouse);

               //wayland_windowing()->post_ui_message(pmouse);

               // if(m_bPendingStartMove)
               // {
               //
               //    m_bPendingStartMove = false;
               //
               //
               //    gtk_gesture_set_state (GTK_GESTURE (pcontroller), GTK_EVENT_SEQUENCE_CLAIMED);
               //
               //
               //    m_pointCursor2.x() = m_sizeOnSize.cx()/2;
               //    m_pointCursor2.y() = m_sizeOnSize.cy()/2;
               //
               //    GdkEvent *happening = gtk_event_controller_get_current_event(GTK_EVENT_CONTROLLER(pcontroller));
               //    guint32 timestamp = gdk_event_get_time(happening);
               //
               //    g_print("Motion happening at x=%.2f, y=%.2f with timestamp: %u\n", x, y, timestamp);
               //
               //    // if (happening) {
               //    //    gdk_event_unref(happening);  // Free the happening object after use
               //    // }
               //
               //    auto pmouse = øcreate_new<::message::mouse>();
               //
               //    pmouse->m_iTimestamp = timestamp;
               //
               // guint button = 0;
               //
               // //auto pgdkeventsequence = gdk_event_get_event_sequence(happening);
               //
               // auto toplevel = gtk_native_get_surface(GTK_NATIVE(m_pgtkwidget));
               //
               //
               // auto pgdkdisplay = kde5_display()->m_pgdkdisplay;
               //
               // GdkSeat * pgdkseat = gdk_display_get_default_seat(pgdkdisplay);
               //
               // // Get the default pointer device (e.g., mouse)
               // GdkDevice *pgdkdevicePointer = gdk_seat_get_pointer(pgdkseat);
               // double x;
               // double y;
               //    x = gtk_widget_get_width(m_pgtkwidget);
               //    y = gtk_widget_get_height(m_pgtkwidget);
               //
               //    x/=2;
               //    y/=2;
               //
               //    //x = 0;
               //    //y = 0;
               //
               //    auto pgdkdevice = gdk_event_get_device (happening);
               //
               // //gdk_toplevel_begin_move(GDK_TOPLEVEL(toplevel), pgdkdevicePointer, button, x, y, timestamp);
               //
               //    gdk_toplevel_begin_move(GDK_TOPLEVEL(toplevel), pgdkdevice, button, x, y, timestamp);
               //
               //    gtk_event_controller_reset (GTK_EVENT_CONTROLLER (pcontroller));
               //    return;
               //
               // }

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

               m_pointCursor2.x() = pevent->globalPosition().x();
               m_pointCursor2.y() = pevent->globalPosition().y();

               pmouse->m_pointHost.x() = pevent->position().x();
               pmouse->m_pointHost.y() = pevent->position().y();

#else

               m_pointCursor2.x() = pevent->globalPos().x();
               m_pointCursor2.y() = pevent->globalPos().y();

               pmouse->m_pointHost.x() = pevent->pos().x();
               pmouse->m_pointHost.y() = pevent->pos().y();

#endif

               pmouse->m_pointAbsolute = m_pointCursor2;

               pelemental->fore_on_mouse_move(pmouse);

               if(!pmouse->m_bRet)
               {

                  pelemental->back_on_mouse_move(pmouse);

               }

            }

         }
//
//
//    static void on_enter_notify(GtkEventControllerMotion* pcontroller, double x, double y, gpointer p)
//    {
//
//       auto pwindow = (::windowing_kde5::window *)p;
//
//       pwindow->_on_enter_notify(pcontroller, x, y);
//
//    }
//
//
//    void window::_on_enter_notify(GtkEventControllerMotion* pcontroller, double x, double y)
//    {
//
// //      GtkWidget* widget = gtk_event_controller_get_widget(GTK_EVENT_CONTROLLER(pcontroller));
//
//
//    }


         void window::_on_reposition(int x, int y)
         {

            m_pacmeuserinteraction->set_position({x, y});

            ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

            if(pelemental)
            {

               pelemental->on_reposition();

            }

         }


         void window::_on_size(int cx, int cy)
         {
            //::windowing::window* pimpl = m_pwindow;


            //auto puserinteraction = pimpl->m_puserinteraction;

            //::int_size s(cx, cy);

            set_interface_client_size({cx, cy});

            ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

            if(pelemental)
            {

               pelemental->on_size();

            }

         }


         void window::set_interface_client_size(const ::int_size & sizeWindow)
         {

            m_sizeWindow = sizeWindow;

            // if (!m_pcairosurface)
            // {
            //
            //    cairo_surface_destroy(m_pcairosurface);
            //
            // }

            int_rectangle r;

            ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

            if(pelemental)
            {

               auto r = pelemental->get_client_rectangle();

               //auto pgdkdisplay = m_pdisplaybase->m_pgdkdisplay;

               //auto window = m_pgtkwidget;

               auto w = r.width();

               auto h = r.height();

               nano()->graphics();

               øconstruct(m_pnanodevice);

               m_pnanodevice->create(w, h);

            }

         }


         //
         // // Callback for when the window visibility changes (minimized/hidden or restored)
         // static void on_window_visibility_chang_wed(GObject* object, GParamSpec* pspec, gpointer p)
         // {
         //    auto pwindow = (::windowing_kde5::window *)p;
         //
         //    pwindow->_on_window_visibility_changed(object, pspec);
         // }
         //
         //
         // void window::_on_window_visibility_changed(GObject* object, GParamSpec* pspec)
         // {
         //    GtkWindow* window = GTK_WINDOW(object);
         //    gboolean is_visible = gtk_widget_get_visible(GTK_WIDGET(window));
         //
         //    if (!is_visible)
         //    {
         //       //      g_print("Window has been minimized (hidden).\n");
         //    }
         //    else
         //    {
         //       g_print("Window has been restored.\n");
         //
         //       ::windowing::window* pimpl = m_puserinteractionbase;
         //
         //       pimpl->m_pacmeuserinteraction->display(::e_display_normal);
         //
         //       pimpl->m_pacmeuserinteraction->set_need_layout();
         //
         //       pimpl->m_pacmeuserinteraction->set_need_redraw();
         //
         //       pimpl->m_pacmeuserinteraction->post_redraw();
         //    }
         // }
         //
         // // Callback for when Option 1 is selected from the popover menu
         // static void on_window_simple_action(GSimpleAction *action, GVariant *parameter, gpointer p)
         // {
         //    auto pwindow = (::windowing_kde5::window *)p;
         //    gchar * name = nullptr;
         //    g_object_get(action, "name", &name, nullptr);
         //    pwindow->_on_window_simple_action(name);
         //    g_free(name);
         //    //g_print("Option 1 selected from popover menu!\n");
         // }

         //   ::int_size window::get_main_screen_size()
         //   {
         //
         //      return m_pdisplay->get_main_screen_size();
         //
         //   }


         void window::defer_show_system_menu(::user::mouse * pmouse)
         {

            // Function to create and show the popup menu

            auto pacmeuserinteraction = m_pacmeuserinteraction;

            m_psystemmenu = pacmeuserinteraction->create_system_menu();

            QMenu contextMenu(m_pqwidget);

            // Create actions for the context menu with custom arguments
            for (auto pmenuitem: *m_psystemmenu)
            {

               if (pmenuitem->m_strName.is_empty())
               {

                  contextMenu.addSeparator();

                  continue;

               }

               auto paction = ___new QAction(pmenuitem->m_strName.c_str(), m_pqwidget);

               m_pqwidget->connect(paction, &QAction::triggered, [this, pmenuitem]()
               {

                  _on_window_simple_action(pmenuitem->m_strAtom, nullptr);

               });

               m_qactiona.add(paction);

               contextMenu.addAction(paction);

            }

            // Show the context menu at the cursor position
            contextMenu.exec({pmouse->m_pointAbsolute.x(), pmouse->m_pointAbsolute.y()});

         }


         void window::set_mouse_capture()
         {

            if (system()->acme_windowing()->get_ewindowing() != ::windowing::e_windowing_wayland)
            {

               main_post([this]()
                         {

                            m_pqwidget->grabMouse();

                  system()->acme_windowing()->m_pwindowMouseCapture = this;

                         });

            }

         }


         bool window::is_mouse_captured()
         {

            bool bIsMouseCaptured = false;

            if (system()->acme_windowing()->get_ewindowing() != ::windowing::e_windowing_wayland)
            {

               if (system()->acme_windowing()->m_pwindowMouseCapture != nullptr)
               {

                  return true;

               }

               main_send([this, &bIsMouseCaptured]()
                         {

                            bIsMouseCaptured = m_pqwidget->mouseGrabber() != nullptr;

                         });

            }

            return bIsMouseCaptured;

         }


         bool window::has_mouse_capture()
         {

            bool bHasMouseCapture = false;

            if (system()->acme_windowing()->get_ewindowing() != ::windowing::e_windowing_wayland)
            {

               if (system()->acme_windowing()->m_pwindowMouseCapture == this)
               {

                  return true;

               }

               main_send([this, &bHasMouseCapture]()
                         {

                            bHasMouseCapture = m_pqwidget->mouseGrabber() == m_pqwidget;

                         });

            }

            return bHasMouseCapture;

         }


         void window::release_mouse_capture()
         {

            if (system()->acme_windowing()->get_ewindowing() != ::windowing::e_windowing_wayland)
            {

               if (system()->acme_windowing()->m_pwindowMouseCapture == this)
               {

                  main_post([this]()
                            {

                               m_pqwidget->releaseMouse();

                     system()->acme_windowing()->m_pwindowMouseCapture = nullptr;

                     information("q::acme::windowing::window::release_mouse_capture()");

                            });

               }

            }

         }


      } // namespace windowing


   } // namespace acme


} // namespace q



