//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "acme/nano/graphics/device.h"
#include "acme/user/micro/child.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/user/user/interaction_base.h"
#include "acme/user/user/mouse.h"
#include "windowing_system_x11/display_lock.h"
#include "_x11.h"
#include <X11/Xatom.h>
#include <xkbcommon/xkbcommon.h>
#include <X11/XKBlib.h>
#include <X11/Xutil.h>


::user::enum_operating_ambient get_eoperating_ambient();


struct MWMHints
{

   unsigned long flags;
   unsigned long functions;
   unsigned long decorations;
   long input_mode;
   unsigned long status;

};

#define MWM_HINTS_FUNCTIONS     (1L << 0)
#define MWM_HINTS_DECORATIONS   (1L << 1)


#define MWM_FUNC_ALL            (1L << 0)
#define MWM_FUNC_RESIZE         (1L << 1)
#define MWM_FUNC_MOVE           (1L << 2)
#define MWM_FUNC_MINIMIZE       (1L << 3)
#define MWM_FUNC_MAXIMIZE       (1L << 4)
#define MWM_FUNC_CLOSE          (1L << 5)

/* MWM decorations values */
#define MWM_DECOR_NONE          0
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)


namespace x11
{


   namespace nano
   {


      namespace user
      {


         window::window()
         {

            m_psurface = nullptr;
            m_iDepth = -1;
            m_pvisual = nullptr;
            zero(m_visualinfo);
            m_colormap = 0;

         }


         window::~window()
         {

            //delete_drawing_objects();

            m_pnanodevice.release();

         }


         ::x11::handle_t window::_x11_handle()
         {

            return as_x11_handle(x11_display()->m_pdisplay, m_window, m_pvisual);

         }


         ::x11::acme::windowing::display * window::x11_display()
         {

            return dynamic_cast < ::x11::acme::windowing::display * >(get_display());

         }


         ::acme::windowing::display * window::get_display()
         {

            if (!m_pdisplay)
            {

               m_pdisplay = ::x11::acme::windowing::display_get(this);

               if (!m_pdisplay)
               {

                  throw ::exception(error_null_pointer);
               }

            }

            return m_pdisplay;


         }


         void window::on_initialize_particle()
         {

            ::x11::micro::window_base::on_initialize_particle();

         }


         void window::on_char(int iChar)
         {

            application()->fork([this, iChar]()
            {

               m_puserinteractionbase->on_char(iChar);

            });

         }


         void window::_draw(::nano::graphics::device * pnanodevice)
         {

            m_puserinteractionbase->draw(pnanodevice);

         }


         bool window::is_active_window()
         {

            return m_puserinteractionbase->is_active();

         }


         void window::create_window()
         {

            get_display();

            main_send([this]()
            {

               _create_window();

            });

         }



         void window::_create_window()
         {

            display_lock displaylock(m_pdisplay->m_pdisplay);

            auto display = m_pdisplay->m_pdisplay;

            m_pvisual = DefaultVisual(display, DefaultScreen(display));

            zero(m_visualinfo);

            if (XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &m_visualinfo))
            {

               m_pvisual = m_visualinfo.visual;

            }
            else
            {

               zero(m_visualinfo);

            }

            m_iDepth = m_visualinfo.depth;

            auto screen = DefaultScreen(display);

            m_windowRoot = RootWindow(display, screen);

            if(m_colormap)
            {

               XFreeColormap(display, m_colormap);

            }

            m_colormap = XCreateColormap(display, m_windowRoot, m_pvisual, AllocNone);

            m_pdisplay->add_listener(this);

            m_pdisplay->add_window(this);

            XSetWindowAttributes attr{};

            attr.colormap = m_colormap;

            attr.event_mask =
               PropertyChangeMask | ExposureMask | ButtonPressMask | ButtonReleaseMask
               | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask
               | FocusChangeMask | LeaveWindowMask | EnterWindowMask;

            attr.background_pixmap = None;

            attr.border_pixmap = None;

            attr.border_pixel = 0;

            attr.override_redirect = False;

            auto r = m_puserinteractionbase->get_interaction_rectangle();

            int x = r.left();
            int y = r.top();
            int w = r.width();
            int h = r.height();

            m_window = XCreateWindow(display, m_windowRoot,
                                     x, y, w, h,
                                     0,
                                     m_iDepth,
                                     InputOutput,
                                     m_pvisual,
                                     CWColormap | CWEventMask | CWBackPixmap | CWBorderPixel | CWOverrideRedirect,
                                     &attr
            );

            if(!m_window)
            {

               m_pdisplay->erase_listener(this);

               m_pdisplay->erase_window(this);

               throw exception(error_failed);

            }

            if(m_puserinteractionbase->m_bStartCentered)
            {

               auto atomWindowType = XInternAtom(display, "_NET_WM_WINDOW_TYPE", true);

               auto atomWindowTypeDialog = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", true);

               if (atomWindowType != None && atomWindowTypeDialog != None)
               {

                  XChangeProperty(display, m_window,
                                  atomWindowType, XA_ATOM, 32, PropModeReplace,
                                  (unsigned char *) &atomWindowTypeDialog, 1);

               }

               auto atomNormalHints = m_pdisplay->intern_atom("WM_NORMAL_HINTS", false);

               XSizeHints hints{};

               hints.flags = PWinGravity;

               hints.win_gravity = CenterGravity;

               XSetWMSizeHints(display, m_window, &hints, atomNormalHints);

            }

            if(m_puserinteractionbase->m_bArbitraryPositioning)
            {

               XSetWindowAttributes attributes;

               attributes.override_redirect = True;

               XChangeWindowAttributes(display, m_window,
                                       CWOverrideRedirect,
                                       &attributes);

            }

            on_create_window();

         }


//         void window::on_left_button_down(::user::mouse * pmouse)
//         {
//
//            m_puserinteractionbase->on_left_button_down(pmouse);
//
//         }
//
//
//         void window::on_left_button_up(::user::mouse * pmouse)
//         {
//
//            m_puserinteractionbase->on_left_button_up(pmouse);
//
//         }
//
//
//         void window::on_right_button_down(::user::mouse * pmouse)
//         {
//
//            m_puserinteractionbase->on_right_button_down(pmouse);
//
//         }
//
//
//         void window::on_right_button_up(::user::mouse * pmouse)
//         {
//
//            m_puserinteractionbase->on_right_button_up(pmouse);
//
//         }
//
//
//         void window::on_mouse_move(::user::mouse * pmouse)
//         {
//
//            m_puserinteractionbase->on_mouse_move(pmouse);
//
//         }
//
//
//         ::payload window::get_result()
//         {
//
//            return m_puserinteractionbase->get_result();
//
//         }


//         ::micro::child * window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
//         {
//
//            return m_puserinteractionbase->hit_test(pmouse, ezorder);
//
//         }



         void window::show_window()
         {

            display_lock displaylock(m_pdisplay->m_pdisplay);

            _wm_nodecorations(false);

            XMapWindow(m_pdisplay->m_pdisplay, m_window);

            XRaiseWindow(m_pdisplay->m_pdisplay, m_window);

            set_active_window();

         }


         void window::set_active_window()
         {

            XEvent xev;

            zero(xev);

            display_lock displaylock(m_pdisplay->m_pdisplay);


            Window windowRoot = DefaultRootWindow(m_pdisplay->m_pdisplay);

            Atom atomActiveWindow = XInternAtom(m_pdisplay->m_pdisplay, "_NET_ACTIVE_WINDOW", False);

            xev.xclient.type = ClientMessage;
            xev.xclient.send_event = True;
            xev.xclient.display = m_pdisplay->m_pdisplay;
            xev.xclient.window = m_window;
            xev.xclient.message_type = atomActiveWindow;
            xev.xclient.format = 32;
            xev.xclient.data.l[0] = 1;
            xev.xclient.data.l[1] = 0;
            xev.xclient.data.l[2] = 0;
            xev.xclient.data.l[3] = 0;
            xev.xclient.data.l[4] = 0;

            XSendEvent(m_pdisplay->m_pdisplay, windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

         }


         bool window::_on_event(XEvent *pevent)
         {

            display_lock displaylock(m_pdisplay->m_pdisplay);


            if(m_window == None)
            {

               return false;

            }

            if (pevent->xany.window != m_window)
            {

               return false;

            }

            auto event_type = pevent->type;

            if (event_type == ConfigureNotify)
            {

               ::int_rectangle r;

               r.left() = pevent->xconfigure.x;

               r.top() = pevent->xconfigure.y;

               r.right() = pevent->xconfigure.x + pevent->xconfigure.width;

               r.bottom() = pevent->xconfigure.y + pevent->xconfigure.height;

               m_puserinteractionbase->set_interaction_rectangle(r);

               if (m_psurface)
               {


                  m_pnanodevice->resize(r.size());


               }

            }
            else if (pevent->type == UnmapNotify)
            {

               informationf("UnmapNotify");

            }
            else if (pevent->type == MapNotify)
            {

               if (!m_psurface)
               {

                  int_rectangle rectangleWindow = get_window_rectangle();

                  auto display = m_pdisplay->m_pdisplay;

                  auto window = m_window;

                  auto w = rectangleWindow.width();

                  auto h = rectangleWindow.height();

                  __øconstruct(m_pnanodevice);

                  m_pnanodevice->create_for_x11(_x11_handle(), w, h);
                  //m_pnanodevice = __allocate ::cairo::nano::graphics::device(pdc);

               }

               _update_window();

            }
            else if (pevent->type == Expose)
            {

               _update_window();

            }
            else if (pevent->type == PropertyNotify)
            {

               informationf("PropertyNotify");

            }
            else if (pevent->type == KeyPress)
            {

               auto keysym = XkbKeycodeToKeysym(m_pdisplay->m_pdisplay, pevent->xkey.keycode, 0, pevent->xkey.state & ShiftMask ? 1 : 0);

               int iChar = xkb_keysym_to_utf32(keysym);

               on_char(iChar);

            }
            else if (pevent->type == KeyRelease)
            {

            }
            else if (pevent->type == ButtonPress)
            {

               if (pevent->xbutton.button == Button1)
               {

                  auto pmouse = __create_new < ::user::mouse >();

                  pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};

                  pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};

                  m_puserinteractionbase->on_left_button_down(pmouse);

               }
               else if (pevent->xbutton.button == Button3)
               {

                  auto pmouse = __create_new < ::user::mouse >();

                  pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};

                  pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};

                  m_puserinteractionbase->on_right_button_down(pmouse);

               }

            }
            else if (pevent->type == ButtonRelease)
            {

               if (pevent->xbutton.button == Button1)
               {

                  auto pmouse = __create_new < ::user::mouse >();

                  pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};

                  pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};

                  m_puserinteractionbase->on_left_button_up(pmouse);

               }
               else if (pevent->xbutton.button == Button3)
               {

                  auto pmouse = __create_new < ::user::mouse >();

                  pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};

                  pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};

                  m_puserinteractionbase->on_right_button_up(pmouse);

               }

            }
            else if (pevent->type == MotionNotify)
            {

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = {pevent->xmotion.x, pevent->xmotion.y};

               pmouse->m_pointAbsolute = {pevent->xmotion.x_root, pevent->xmotion.y_root};

               m_puserinteractionbase->on_mouse_move(pmouse);

            }
            else if (pevent->type == LeaveNotify)
            {

//               if (m_puserinteractionbase->m_pchildHover)
//               {
//
//                  auto pmouse = __create_new < ::user::mouse >();
//
//                  pmouse->m_pointHost = {I32_MINIMUM, I32_MINIMUM};
//
//                  pmouse->m_pointAbsolute = {I32_MINIMUM, I32_MINIMUM};
//
//                  m_puserinteractionbase->m_pchildHover->on_mouse_move(pmouse);
//
//                  m_puserinteractionbase->m_pchildHover = nullptr;
//
//                  m_puserinteractionbase->redraw();
//
//               }

            }

            return true;

         }


         void window::_update_window()
         {

            if(m_pnanodevice && m_psurface)
            {

               m_pnanodevice->on_begin_draw();

               m_puserinteractionbase->draw(m_pnanodevice);

               m_pnanodevice->on_end_draw();

               cairo_surface_flush(m_psurface);

            }

         }


         void window::redraw()
         {

            //::RedrawWindow(m_hwnd, nullptr, nullptr, RDW_UPDATENOW | RDW_INVALIDATE);

            _update_window();

         }


         void window::destroy()
         {

            display_lock displaylock(m_pdisplay->m_pdisplay);


            if(m_window)
            {

               XUnmapWindow(m_pdisplay->m_pdisplay, m_window);

               if(::is_set(m_pnanodevice))
               {

                  defer_finalize__destroy_and_release(m_pnanodevice);

               }

               if(m_psurface != nullptr)
               {

                  cairo_surface_destroy(m_psurface);

                  m_psurface = nullptr;

               }

               XDestroyWindow(m_pdisplay->m_pdisplay, m_window);

               m_window = 0;

            }

            if(m_colormap)
            {

               XFreeColormap(m_pdisplay->m_pdisplay, m_colormap);

               m_colormap = 0;

            }

            m_pdisplay->erase_listener(this);

            m_pdisplay->erase_window(this);

            //XCloseDisplay(m_pdisplay->m_pdisplay);

            m_happeningEnd.set_happening();

         }


//         void window::on_click(const ::payload & payloadParam, ::user::mouse * pmouse)
//         {
//
//            ::payload payload(payloadParam);
//
//            fork([this, payload, pmouse]()
//                 {
//
//                    m_puserinteractionbase->on_click(payload, pmouse);
//
//                 }, {pmouse});
//
//         }
//
//
//         void window::on_right_click(const ::payload & payloadParam, ::user::mouse * pmouse)
//         {
//
//            ::payload payload(payloadParam);
//
//            fork([this, payload, pmouse]()
//                 {
//
//                    m_puserinteractionbase->on_right_click(payload, pmouse);
//
//                 }, {pmouse});
//
//         }


//         void window::move_to(const ::int_point & point)
//         {
//            display_lock displaylock(m_pdisplay->m_pdisplay);
//
//            ::XMoveWindow(m_pdisplay->m_pdisplay, m_window, point.x(), point.y());
//
//         }


         void window::set_capture()
         {

            display_lock displaylock(m_pdisplay->m_pdisplay);

            if (XGrabPointer(m_pdisplay->m_pdisplay, m_window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                             GrabModeAsync, GrabModeAsync, None, None, CurrentTime) != GrabSuccess)
            {

               throw ::exception(error_exception);

            }

         }


         void window::release_capture()
         {
            display_lock displaylock(m_pdisplay->m_pdisplay);


            int bRet = XUngrabPointer(m_pdisplay->m_pdisplay, CurrentTime);

         }


//         void window::get_client_rectangle(::int_rectangle & rectangle)
//         {
//
//            rectangle.left() = 0;
//            rectangle.top() = 0;
//
//            Window windowRoot = 0;
//            int x = 0;
//            int y = 0;
//            unsigned int w = 0;
//            unsigned int h = 0;
//            unsigned int border = 0;
//            unsigned int depth = 0;
//
//            auto status = XGetGeometry(m_pdisplay->m_pdisplay, m_window, &windowRoot, &x, &y, &w,
//                                &h, &border, &depth);
//
//            if(status == BadDrawable)
//            {
//
//               throw ::exception(error_exception);
//
//            }
//
//            rectangle.right() = w;
//            rectangle.bottom() = h;
//
//
//         }


         ::int_rectangle window::get_window_rectangle()
         {

            display_lock displaylock(m_pdisplay->m_pdisplay);

            Window windowRoot = 0;
            int x = 0;
            int y = 0;
            unsigned int w = 0;
            unsigned int h = 0;
            unsigned int border = 0;
            unsigned int depth = 0;

            auto status = XGetGeometry(m_pdisplay->m_pdisplay, m_window, &windowRoot, &x, &y, &w,
                                       &h, &border, &depth);

            if(status == BadDrawable)
            {

               throw ::exception(error_exception);

            }

            ::int_rectangle rectangle;

            rectangle.left() = x;
            rectangle.top() = y;
            rectangle.right() = x + w;
            rectangle.bottom() = y + h;

            return rectangle;

         }


         void window::_wm_nodecorations(int iMap)
         {

            display_lock displaylock(m_pdisplay->m_pdisplay);


            auto windowRoot = DefaultRootWindow(m_pdisplay->m_pdisplay);

            bool bCreateAtom = false;

            Atom atomMotifHints = XInternAtom(m_pdisplay->m_pdisplay, "_MOTIF_WM_HINTS", bCreateAtom ? True : False);

            if (atomMotifHints != None)
            {

               MWMHints hints = {};

               hints.flags = MWM_HINTS_DECORATIONS;
               hints.decorations = MWM_DECOR_NONE;

               //XChangeProperty(Display(), Window(), atomMotifHints, atomMotifHints, 32, PropModeReplace,
               //              (unsigned char *) &hints, sizeof(MWMHints) / 4);
               XChangeProperty(m_pdisplay->m_pdisplay, m_window, atomMotifHints, atomMotifHints, 32, PropModeReplace,
                               (unsigned char *) &hints, sizeof(hints) / 4);

            }

            if (iMap)
            {

               XUnmapWindow(m_pdisplay->m_pdisplay, m_window);

               XMapWindow(m_pdisplay->m_pdisplay, m_window);

            }

            windowing_output_debug_string("::wm_nodecorations 2");

         }


         //   ::int_size window::get_main_screen_size()
         //   {
         //
         //      return m_pdisplay->get_main_screen_size();
         //
         //   }


      }//namespace user


   }//namespace nano


} // namespace x11


#define MAXSTR 1000


//CLASS_DECL_ACME ::platform::system * system();
//
//
//void x11_asynchronous(::procedure function)
//{
//
//   auto psystem = system();
//
//   auto pdisplay = ::x11::display::get(psystem);
//
//   if (!pdisplay)
//   {
//
//      throw ::exception(error_null_pointer);
//
//   }
//
//   pdisplay->aaa_display_post([function]()
//                                    {
//
//                                       function();
//
//                                    });
//
//}
//
//
//
