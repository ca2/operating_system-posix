//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "display_lock.h"
#include "acme/nano/graphics/device.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/user/micro/elemental.h"
#include "acme/user/user/interaction.h"
#include "acme/user/user/mouse.h"
#include "_x11.h"
#include <X11/Xatom.h>
#include <xkbcommon/xkbcommon.h>
#include <X11/XKBlib.h>
#include <X11/Xutil.h>

#include "acme/integrate/cairo/surface.h"
#include "acme/windowing/windowing.h"


::windowing::enum_operating_ambient get_eoperating_ambient();


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


   namespace acme
   {


      namespace windowing
      {


         window::window()
         {

            m_psurface = nullptr;
            m_iDepth = -1;
            //m_pvisual = nullptr;
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

            return as_x11_handle(x11_display()->m_pDisplay, m_window, m_pvisual);

         }



         Display * window::__x11_display()
         {

            return x11_display()->m_pDisplay;

         }


         Window window::__x11_window()
         {

            return m_window;

         }


         long window::__x11_Window()
         {


            return __x11_window();

         }


         void * window::__x11_Display()
         {


            return __x11_display();

         }


         ::x11::acme::windowing::display * window::x11_display()
         {

            return dynamic_cast < ::x11::acme::windowing::display * >(get_display());

         }


         ::acme::windowing::display * window::get_display()
         {

            if (!m_px11display)
            {

               m_px11display = system()->acme_windowing()->acme_display();

               if (!m_px11display)
               {

                  throw ::exception(error_null_pointer);

               }

            }

            return m_px11display;

         }


         void window::on_initialize_particle()
         {

            ::acme::windowing::window::on_initialize_particle();

         }


         void window::on_char(int iChar)
         {

            application()->post([this, iChar]()
            {

               //m_pacmeuserinteraction->on_char(iChar);

            });

         }


         bool window::is_active_window()
         {

            return m_pacmeuserinteraction->is_window_active();

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

            ::cast < ::x11::acme::windowing::display > px11display = get_display();

            display_lock displaylock(px11display->m_pDisplay);

            auto display = m_px11display->m_pDisplay;

            m_pvisual = DefaultVisual(display, DefaultScreen(display));

            zero(m_visualinfo);

            ødefer_construct_new(m_px11data);

            if (m_lX11NativeVisualId >= 0)
            //if (false)
            {

               XVisualInfo visualinfo2={};

               XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &visualinfo2);

               XVisualInfo viTemplate = {};
               viTemplate.visualid = m_lX11NativeVisualId;

               int num = 0;
               XVisualInfo* pvisualinfo = XGetVisualInfo(
                   display,
                   VisualIDMask,
                   &viTemplate,
                   &num
               );

               if (!pvisualinfo || num <= 0)
               {

                  throw ::exception(error_failed);

               }

               m_visualinfo = *pvisualinfo;

               m_pvisual = m_visualinfo.visual;

               XFree(pvisualinfo);

            }
            else
            {
               if (XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &m_visualinfo))
               {

                  m_pvisual = m_visualinfo.visual;

               }
               else
               {

                  zero(m_visualinfo);

               }
            }

            m_iDepth = m_visualinfo.depth;

            auto screen = DefaultScreen(display);

            m_windowRoot = RootWindow(display, screen);

            if(m_colormap)
            {

               XFreeColormap(display, m_colormap);

            }

            printf("depth=%d\n", m_visualinfo.depth);

            m_colormap = XCreateColormap(display, m_windowRoot, m_pvisual, AllocNone);

            m_px11display->add_listener(this);

            //m_px11display->add_window(this);

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

            //auto r = acme_user_interaction()->rect();

            int x = m_pointWindow.x;
            int y = m_pointWindow.y;
            int w = m_sizeWindow.cx;
            int h = m_sizeWindow.cy;

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

               throw exception(error_failed);

            }

            //on_create_window();

         }


         void window::show_window()
         {

            display_lock displaylock(m_px11display->m_pDisplay);

            _wm_nodecorations(false);

            XMapWindow(m_px11display->m_pDisplay, m_window);

            XRaiseWindow(m_px11display->m_pDisplay, m_window);

            set_active_window();

         }


         void window::set_active_window()
         {

            XEvent xev;

            zero(xev);

            display_lock displaylock(m_px11display->m_pDisplay);


            Window windowRoot = DefaultRootWindow(m_px11display->m_pDisplay);

            Atom atomActiveWindow = XInternAtom(m_px11display->m_pDisplay, "_NET_ACTIVE_WINDOW", False);

            xev.xclient.type = ClientMessage;
            xev.xclient.send_event = True;
            xev.xclient.display = m_px11display->m_pDisplay;
            xev.xclient.window = m_window;
            xev.xclient.message_type = atomActiveWindow;
            xev.xclient.format = 32;
            xev.xclient.data.l[0] = 1;
            xev.xclient.data.l[1] = 0;
            xev.xclient.data.l[2] = 0;
            xev.xclient.data.l[3] = 0;
            xev.xclient.data.l[4] = 0;

            XSendEvent(m_px11display->m_pDisplay, windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

         }


         void window::_on_cairo_draw(cairo_t *cr)
         {

            if (!m_pnanodevice)
            {

               cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, 1.0);

               cairo_fill(cr);

               return ;

            }

            m_pnanodevice->on_begin_draw();

            _draw(m_pnanodevice);

            m_pnanodevice->on_end_draw();

            auto pixmap = m_pnanodevice->pixmap();

            auto psurface = cairo_surface_for_pixmap(pixmap);

            cairo_set_source_surface(cr, psurface, 0., 0.);

            cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);

            cairo_paint(cr);

            cairo_surface_destroy(psurface);

         }



         bool window::__on_x11_event(XEvent *pevent)
         {

            display_lock displaylock(m_px11display->m_pDisplay);


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

               r.left = pevent->xconfigure.x;

               r.top = pevent->xconfigure.y;

               r.right = pevent->xconfigure.x + pevent->xconfigure.width;

               r.bottom = pevent->xconfigure.y + pevent->xconfigure.height;

               m_pacmeuserinteraction->set_interaction_rectangle(r);

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

                  auto display = m_px11display->m_pDisplay;

                  auto window = m_window;

                  auto w = rectangleWindow.width();

                  auto h = rectangleWindow.height();

                  øconstruct(m_pnanodevice);

                  m_pnanodevice->create(w, h);
                  //m_pnanodevice->create_for_x11(_x11_handle(), w, h);
                  //m_pnanodevice = øallocate ::cairo::nano::graphics::device(pdc);

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

               auto keysym = XkbKeycodeToKeysym(m_px11display->m_pDisplay, pevent->xkey.keycode, 0, pevent->xkey.state & ShiftMask ? 1 : 0);

               int iChar = xkb_keysym_to_utf32(keysym);

               on_char(iChar);

            }
            else if (pevent->type == KeyRelease)
            {

            }
            else if (pevent->type == ButtonPress)
            {

               ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               if (pelemental)
               {

                  if (pevent->xbutton.button == Button1)
                  {

                     auto pmouse = øcreate_new < ::user::mouse >();

                     pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};

                     pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};

                     pelemental->fore_on_left_button_down(pmouse);

                     if (pmouse->m_bRet)
                     {

                        return true;

                     }

                     pelemental->back_on_left_button_down(pmouse);

                     if (pmouse->m_bRet)
                     {

                        return true;


                     }


                  }
                  else if (pevent->xbutton.button == Button3)
                  {

                     auto pmouse = øcreate_new < ::user::mouse >();

                     pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};

                     pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};

                     pelemental->fore_on_right_button_down(pmouse);

                     if (pmouse->m_bRet)
                     {

                        return true;

                     }

                     pelemental->back_on_right_button_down(pmouse);

                     if (pmouse->m_bRet)
                     {

                        return true;


                     }

                  }

               }

            }
            else if (pevent->type == ButtonRelease)
            {

               ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               if (pelemental)
               {
                  if (pevent->xbutton.button == Button1)
                  {

                     auto pmouse = øcreate_new < ::user::mouse >();

                     pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};

                     pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};

                     pelemental->fore_on_left_button_up(pmouse);

                     if (pmouse->m_bRet)
                     {

                        return true;

                     }

                     pelemental->back_on_left_button_up(pmouse);

                     if (pmouse->m_bRet)
                     {

                        return true;


                     }

                  }
                  else if (pevent->xbutton.button == Button3)
                  {

                     auto pmouse = øcreate_new < ::user::mouse >();

                     pmouse->m_pointHost = {pevent->xbutton.x, pevent->xbutton.y};

                     pmouse->m_pointAbsolute = {pevent->xbutton.x_root, pevent->xbutton.y_root};

                     pelemental->fore_on_right_button_up(pmouse);

                     if (pmouse->m_bRet)
                     {

                        return true;

                     }

                     pelemental->back_on_right_button_up(pmouse);

                     if (pmouse->m_bRet)
                     {

                        return true;


                     }

                  }

               }

            }
            else if (pevent->type == MotionNotify)
            {

               ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

               if (pelemental)
               {

                  auto pmouse = øcreate_new < ::user::mouse >();

                  pmouse->m_pointHost = {pevent->xmotion.x, pevent->xmotion.y};

                  pmouse->m_pointAbsolute = {pevent->xmotion.x_root, pevent->xmotion.y_root};

                  ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

                  if(pelemental)
                  {


                     pelemental->fore_on_mouse_move(pmouse);

                  }

                  if (pmouse->m_bRet)
                  {

                     return true;

                  }

                  if(pelemental)
                  {


                     pelemental->back_on_mouse_move(pmouse);

                  }

               }

            }
            else if (pevent->type == LeaveNotify)
            {

//               if (m_pacmeuserinteraction->m_pchildHover)
//               {
//
//                  auto pmouse = øcreate_new < ::user::mouse >();
//
//                  pmouse->m_pointHost = {I32_MINIMUM, I32_MINIMUM};
//
//                  pmouse->m_pointAbsolute = {I32_MINIMUM, I32_MINIMUM};
//
//                  m_pacmeuserinteraction->m_pchildHover->on_mouse_move(pmouse);
//
//                  m_pacmeuserinteraction->m_pchildHover = nullptr;
//
//                  m_pacmeuserinteraction->redraw();
//
//               }

            }

            return true;

         }


         void window::_update_window()
         {

            // if(m_pnanodevice && m_psurface)
            // {
            //
            //    m_pnanodevice->on_begin_draw();
            //
            //    m_pacmeuserinteraction->draw(m_pnanodevice);
            //
            //    m_pnanodevice->on_end_draw();
            //
            //    cairo_surface_flush(m_psurface);
            //
            // }

         }


         void window::_draw(::nano::graphics::device * pnanodevice)
         {

            ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

            if(pelemental)
            {

               pelemental->draw_background(pnanodevice);

               pelemental->draw_foreground(pnanodevice);

            }

         }



         void window::redraw()
         {

            //::RedrawWindow(m_hwnd, nullptr, nullptr, RDW_UPDATENOW | RDW_INVALIDATE);

            _update_window();

         }


         void window::destroy()
         {

            display_lock displaylock(m_px11display->m_pDisplay);


            if(m_window)
            {

               XUnmapWindow(m_px11display->m_pDisplay, m_window);

               if(::is_set(m_pnanodevice))
               {

                  //defer_finalize__destroy_and_release(m_pnanodevice);

                  __destroy_and_release(m_pnanodevice);

               }

               if(m_psurface != nullptr)
               {

                  cairo_surface_destroy(m_psurface);

                  m_psurface = nullptr;

               }

               XDestroyWindow(m_px11display->m_pDisplay, m_window);

               m_window = 0;

            }

            if(m_colormap)
            {

               XFreeColormap(m_px11display->m_pDisplay, m_colormap);

               m_colormap = 0;

            }

            // m_px11display->erase_listener(this);
            //
            // m_px11display->erase_window(this);

            //XCloseDisplay(m_px11display->m_pDisplay);

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
//                    m_pacmeuserinteraction->on_click(payload, pmouse);
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
//                    m_pacmeuserinteraction->on_right_click(payload, pmouse);
//
//                 }, {pmouse});
//
//         }


//         void window::move_to(const ::int_point & point)
//         {
//            display_lock displaylock(m_px11display->m_pDisplay);
//
//            ::XMoveWindow(m_px11display->m_pDisplay, m_window, point.x, point.y);
//
//         }


         void window::set_mouse_capture()
         {

            display_lock displaylock(m_px11display->m_pDisplay);

            if (XGrabPointer(m_px11display->m_pDisplay, m_window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                             GrabModeAsync, GrabModeAsync, None, None, CurrentTime) != GrabSuccess)
            {

               throw ::exception(error_exception);

            }

         }


         void window::release_mouse_capture()
         {
            display_lock displaylock(m_px11display->m_pDisplay);


            int bRet = XUngrabPointer(m_px11display->m_pDisplay, CurrentTime);

         }


//         void window::get_client_rectangle(::int_rectangle & rectangle)
//         {
//
//            rectangle.left = 0;
//            rectangle.top = 0;
//
//            Window windowRoot = 0;
//            int x = 0;
//            int y = 0;
//            unsigned int w = 0;
//            unsigned int h = 0;
//            unsigned int border = 0;
//            unsigned int depth = 0;
//
//            auto status = XGetGeometry(m_px11display->m_pDisplay, m_window, &windowRoot, &x, &y, &w,
//                                &h, &border, &depth);
//
//            if(status == BadDrawable)
//            {
//
//               throw ::exception(error_exception);
//
//            }
//
//            rectangle.right = w;
//            rectangle.bottom = h;
//
//
//         }


         ::int_rectangle window::get_window_rectangle()
         {

            display_lock displaylock(m_px11display->m_pDisplay);

            Window windowRoot = 0;
            int x = 0;
            int y = 0;
            unsigned int w = 0;
            unsigned int h = 0;
            unsigned int border = 0;
            unsigned int depth = 0;

            auto status = XGetGeometry(m_px11display->m_pDisplay, m_window, &windowRoot, &x, &y, &w,
                                       &h, &border, &depth);

            if(status == BadDrawable)
            {

               throw ::exception(error_exception);

            }

            ::int_rectangle rectangle;

            rectangle.left = x;
            rectangle.top = y;
            rectangle.right = x + w;
            rectangle.bottom = y + h;

            return rectangle;

         }


         /// should be run at user_thread
         void window::set_foreground_window()
         {

            ::x11::display_lock displaylock(x11_display()->__x11_display());

            _set_foreground_window_unlocked();

         }


         /// should be run at user_thread
         void window::_set_foreground_window_unlocked()
         {

            if (Window() == 0)
            {

               throw ::exception(error_failed);

            }

            windowing_output_debug_string("\nwindow(x11)::_set_foreground_window_unlocked 1");

            if (!is_window())
            {

               windowing_output_debug_string("\nwindow(x11)::_set_foreground_window_unlocked 1.1");

               throw ::exception(error_failed);

            }

            XRaiseWindow(__x11_display(), Window());

            //XSetInputFocus(__x11_display(), Window(), RevertToNone, CurrentTime);

         }


         void window::_wm_nodecorations(int iMap)
         {

            display_lock displaylock(m_px11display->m_pDisplay);


            auto windowRoot = DefaultRootWindow(m_px11display->m_pDisplay);

            bool bCreateAtom = false;

            Atom atomMotifHints = XInternAtom(m_px11display->m_pDisplay, "_MOTIF_WM_HINTS", bCreateAtom ? True : False);

            if (atomMotifHints != None)
            {

               MWMHints hints = {};

               hints.flags = MWM_HINTS_DECORATIONS;
               hints.decorations = MWM_DECOR_NONE;

               //XChangeProperty(__x11_display(), __x11_window(), atomMotifHints, atomMotifHints, 32, PropModeReplace,
               //              (unsigned char *) &hints, sizeof(MWMHints) / 4);
               XChangeProperty(m_px11display->m_pDisplay, m_window, atomMotifHints, atomMotifHints, 32, PropModeReplace,
                               (unsigned char *) &hints, sizeof(hints) / 4);

            }

            if (iMap)
            {

               XUnmapWindow(m_px11display->m_pDisplay, m_window);

               XMapWindow(m_px11display->m_pDisplay, m_window);

            }

            windowing_output_debug_string("::wm_nodecorations 2");

         }


         bool window::get_state(long &lState)
         {

            bool bOk = false;

            system()->acme_windowing()->send([this, &bOk, &lState]()
                     {


                        windowing_output_debug_string("::window::get_state 1");

                        //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

                        ::x11::display_lock displaylock(x11_display()->__x11_display());

                        bOk = _get_wm_state_unlocked(lState);

                     });

            return bOk;

         }


      bool window::_get_wm_state_unlocked(long &lState)
      {

         static const long WM_STATE_ELEMENTS = 2L;

         if (x11_display()->m_atomWmState == None)
         {

            x11_display()->m_atomWmState = x11_display()->intern_atom("WM_STATE", false);

         }

         Atom actual_type = 0;

         int actual_format = 0;

         unsigned long nitems = 0;

         unsigned long leftover = 0;

         unsigned char *p = nullptr;

         auto atomWmState = x11_display()->m_atomWmState;

         int status = XGetWindowProperty(__x11_display(), __x11_window(), atomWmState, 0L,
                                           WM_STATE_ELEMENTS, False, AnyPropertyType,
                                           &actual_type,
                                           &actual_format, &nitems, &leftover, &p);

         if (status != 0)
         {

            windowing_output_debug_string("::window::_get_state_unlocked 2");

            return false;

         }

         long lStatus = -1;

         if (p != nullptr)
         {

            lStatus = (long) *p;

         }

         XFree(p);

         windowing_output_debug_string("::window::_get_state_unlocked 1.1");

         lState = lStatus;

         return true;

      }


         //   ::int_size window::get_main_screen_size()
         //   {
         //
         //      return m_px11display->get_main_screen_size();
         //
         //   }


   comparable_array<Atom> window::_wm_get_list_unlocked(Atom atomList)
   {

      comparable_array<Atom> atoma;

      if (atomList == None)
      {

         return atoma;

      }

      Atom actual_type;

      int actual_format;

      unsigned long int bytes_after;

      Atom *patoms = nullptr;

      long unsigned int num_items = 0;

      XGetWindowProperty(__x11_display(), __x11_window(), atomList, 0, 1024,
                         False, XA_ATOM, &actual_type, &actual_format,
                         &num_items,
                         &bytes_after, (unsigned char **) &patoms);

      atoma.set_size(num_items);

      ::memory_copy(atoma.data(), patoms, atoma.get_size_in_bytes());

      XFree(patoms);

      return atoma;

   }


   ::comparable_array<Atom> window::_get_net_wm_state_unlocked()
   {

      auto pdisplay = x11_display();

      return _wm_get_list_unlocked(pdisplay->__x11_atom_net_wm_state());

//      bNetWmStateHidden = atoma.contains(pdisplay->m_atomNetWmStateHidden);
//
//      bNetWmStateMaximized = atoma.contains(pdisplay->m_atomNetWmStateMaximizedHorz)
//         || atoma.contains(pdisplay->m_atomNetWmStateMaximizedVert);
//
//      bNetWmStateFocused = atoma.contains(pdisplay->m_atomNetWmStateFocused);

   }


   int window::_wm_test_list_unlocked(Atom atomList, Atom atomFlag)
   {

//      synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      Atom actual_type;

      int actual_format;

      unsigned long i;

      auto atoma = _wm_get_list_unlocked(atomList);

      if (atoma.is_empty())
      {

         return 0;

      }

      bool bFind = atoma.contains(atomFlag);

      return bFind ? 1 : 0;

   }


   int window::_wm_test_state_unlocked(const_char_pointer pszNetStateFlag)
   {

      //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      Atom atomFlag = x11_display()->_intern_atom_unlocked(pszNetStateFlag, 1);

      if (atomFlag == None)
      {

         windowing_output_debug_string("ERROR: cannot find atom for " + string(pszNetStateFlag) + "!\n");

         return 0;

      }

      Atom atomNetState = x11_display()->_intern_atom_unlocked("_NET_WM_STATE", 1);

      if (atomNetState == None)
      {

         windowing_output_debug_string("ERROR: cannot find atom for _NET_WM_STATE !\n");

         return 0;

      }

      return _wm_test_list_unlocked(atomNetState, atomFlag);

   }


   int window::wm_test_state(const_char_pointer pszNetStateFlag)
   {

      ::string strNetStateFlag;

      int i = 0;

      system()->acme_windowing()->send([this, &i, strNetStateFlag]()
               {

                  //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

                  windowing_output_debug_string("::wm_test_state 1");

                  ::x11::display_lock displaylock(__x11_display());

                  if (x11_display()->is_null())
                  {

                     windowing_output_debug_string("::wm_test_state 1.1");

                     i = 0;

                     return;

                  }

                  i = _wm_test_state_unlocked(strNetStateFlag);

                  windowing_output_debug_string("::wm_test_state 2");

               });

      return i;

   }


   bool window::_wm_add_erase_list_unlocked(Atom atomList, Atom atomFlag, bool bSet)
   {

      if (atomFlag == None)
      {

         return false;

      }

      if (atomList == None)
      {

         return false;

      }

      if (bSet)
      {

         if (!_wm_test_list_unlocked(atomList, atomFlag))
         {

            XChangeProperty(__x11_display(), __x11_window(), atomList, XA_ATOM, 32, PropModeAppend, (unsigned char *) &atomFlag, 1);

         }

      } else
      {

         unsigned long num_items;

         auto atoma = _wm_get_list_unlocked(atomList);

         if (atoma.is_empty())
         {

            return false;

         }

         auto iFind = -1;

         int i;

         for (i = 0; i < num_items; i++)
         {

            if (atoma[i] == atomFlag)
            {

               iFind = i;

               break;

            }

         }

         if (::not_found(iFind))
         {

            atoma.erase_at(iFind);

            XChangeProperty(__x11_display(), __x11_window(), atomList, XA_ATOM, 32, PropModeReplace, (unsigned char *) atoma.data(),
                            atoma.size());

         }

      }

      return true;

   }


         bool window::has_mouse_capture() const
         {

            auto pacmewindowing = ::system()->acme_windowing();

            if (::is_null(pacmewindowing))
            {

               return false;

            }

            auto pwindowCapture = pacmewindowing->m_pacmewindowingwindowMouseCapture;

            if (::is_null(pwindowCapture))
            {

               return false;

            }

            if (pwindowCapture != this)
            {

               return false;

            }

            return true;

         }


         bool window::has_keyboard_focus() const
         {

            auto pacmewindowing = ::system()->acme_windowing();

            if (::is_null(pacmewindowing))
            {

               return false;

            }

            auto pacmeuserinteractionActive = pacmewindowing->m_pacmeuserinteractionActive;

            if (::is_null(pacmeuserinteractionActive))
            {

               return false;

            }

            // if (!(pacmeuserinteractionActive->m_ewindowflag & ::e_window_flag_focus))
            // {
            //
            //    return false;
            //
            // }

            return true;

         }

      }//namespace windowing


   }//namespace acme


} // namespace x11

