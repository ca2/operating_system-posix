//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "window.h"
#include "display.h"
#include "display_lock.h"
#include "acme/nano/graphics/context.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/user/micro/elemental.h"
#include "acme/user/micro/theme.h"
#include "acme/user/user/interaction.h"
#include "acme/user/user/mouse.h"
#include "_x11.h"
#include <X11/Xatom.h>
#include <X11/extensions/Xrender.h>
#include <cairo/cairo-xlib.h>
#include <xkbcommon/xkbcommon.h>
#include <X11/XKBlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <atomic>
#include <cmath>
#include <cstdlib>
#include <mutex>
#include <string>

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

            m_pnanographicscontext.release();

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


         // long window::__x11_Window()
         // {
         //
         //
         //    return __x11_window();
         //
         // }
         //
         //
         // void * window::__x11_Display()
         // {
         //
         //
         //    return __x11_display();
         //
         // }


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


         ::f32 window::get_density_dpi_for_window()
         {

            static std::atomic<::f32> s_fXftDpi{0.0f};

            auto fDpi = s_fXftDpi.load(std::memory_order_acquire);

            if (fDpi > 0.0f)
            {

               return fDpi;

            }

            auto pdisplay = m_px11display ? m_px11display->m_pDisplay : nullptr;

            if (!pdisplay)
            {

               return ::acme::windowing::window::get_density_dpi_for_window();

            }

            static std::once_flag s_xrmInitialized;
            std::call_once(s_xrmInitialized, []() { XrmInitialize(); });

            ::x11::display_lock displaylock(pdisplay);

            auto pszResources = XResourceManagerString(pdisplay);

            fDpi = ::acme::windowing::window::get_density_dpi_for_window();

            if (pszResources)
            {

               auto database = XrmGetStringDatabase(pszResources);

               if (database)
               {

                  char * pszType = nullptr;
                  XrmValue value{};

                  if (XrmGetResource(database, "Xft.dpi", "Xft.Dpi", &pszType, &value)
                     && value.addr && value.size > 0)
                  {

                     std::string strDpi(value.addr, value.size);
                     char * pszEnd = nullptr;
                     auto fCandidate = std::strtof(strDpi.c_str(), &pszEnd);

                     if (pszEnd != strDpi.c_str() && std::isfinite(fCandidate)
                        && fCandidate >= 72.0f && fCandidate <= 768.0f)
                     {

                        fDpi = fCandidate;

                     }

                  }

                  XrmDestroyDatabase(database);

               }

            }

            s_fXftDpi.store(fDpi, std::memory_order_release);
            informationf("X11 window density DPI=%.1f scale=%.2f", fDpi, fDpi / 96.0f);

            return fDpi;

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

            printf("x11::acme::windowing::window::create_window begin window=%p\n", static_cast<void *>(this));
            fflush(stdout);

            get_display();

            main_send([this]()
            {

               printf("x11::acme::windowing::window::create_window main_send begin\n");
               fflush(stdout);

               _create_window();

               printf("x11::acme::windowing::window::create_window main_send completed xid=0x%lx\n",
                      static_cast<unsigned long>(m_window));
               fflush(stdout);

            });

            printf("x11::acme::windowing::window::create_window end xid=0x%lx\n",
                   static_cast<unsigned long>(m_window));
            fflush(stdout);

         }



         void window::_create_window()
         {

            ::cast < ::x11::acme::windowing::display > px11display = get_display();

            display_lock displaylock(px11display->m_pDisplay);

            auto display = m_px11display->m_pDisplay;

            m_pvisual = DefaultVisual(display, DefaultScreen(display));

            zero(m_visualinfo);

            defer_construct_newø(m_px11data);

            bool bVisualHasAlpha = false;

            if (m_lX11NativeVisualId >= 0)
            {

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

               auto pformat = XRenderFindVisualFormat(display, m_pvisual);

               bVisualHasAlpha = pformat
                  && pformat->type == PictTypeDirect
                  && pformat->direct.alphaMask != 0;

               XFree(pvisualinfo);

            }
            else
            {

               // Prefer a real ARGB visual for compositing, but only when
               // XRender confirms that the visual has an alpha channel.
               auto iScreen = DefaultScreen(display);

               XVisualInfo viTemplate{};

               viTemplate.screen = iScreen;

               viTemplate.depth = 32;

               viTemplate.c_class = TrueColor;

               int visualCount = 0;

               auto pvisualinfoa = XGetVisualInfo(
                  display,
                  VisualScreenMask | VisualDepthMask | VisualClassMask,
                  &viTemplate,
                  &visualCount);

               for (int iVisual = 0; pvisualinfoa && iVisual < visualCount; ++iVisual)
               {

                  auto pformat = XRenderFindVisualFormat(display, pvisualinfoa[iVisual].visual);

                  if (pformat
                     && pformat->type == PictTypeDirect
                     && pformat->direct.alphaMask != 0)
                  {

                     m_visualinfo = pvisualinfoa[iVisual];

                     m_pvisual = m_visualinfo.visual;

                     bVisualHasAlpha = true;

                     break;

                  }

               }

               if (pvisualinfoa)
               {

                  XFree(pvisualinfoa);

               }

               if (!bVisualHasAlpha)
               {

                  m_pvisual = DefaultVisual(display, iScreen);

                  m_visualinfo.visual = m_pvisual;

                  m_visualinfo.visualid = XVisualIDFromVisual(m_pvisual);

                  m_visualinfo.screen = iScreen;

                  m_visualinfo.depth = DefaultDepth(display, iScreen);

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

            // attr.background_pixmap = None;

            // attr.border_pixmap = None;

            attr.background_pixel = bVisualHasAlpha ? 0 : WhitePixel(display, screen);

            attr.border_pixel = 0;

            attr.override_redirect = False;

            //auto r = acme_user_interaction()->rect();

            int x = m_pointWindow.x;
            int y = m_pointWindow.y;
            int w = m_sizeWindow.cx;
            int h = m_sizeWindow.cy;

            printf("x11::acme::windowing::window XCreateWindow arguments: display=%p parent=0x%lx position=(%d,%d) size=(%d,%d) border=%d depth=%d class=%d visual=0x%lx colormap=0x%lx event_mask=0x%lx\n",
                   static_cast<void *>(display), static_cast<unsigned long>(m_windowRoot),
                   x, y, w, h, 0, m_iDepth, InputOutput,
                   static_cast<unsigned long>(m_pvisual ? XVisualIDFromVisual(m_pvisual) : 0),
                   static_cast<unsigned long>(m_colormap),
                   static_cast<unsigned long>(attr.event_mask));
            fflush(stdout);

            m_window = XCreateWindow(display, m_windowRoot,
                                     x, y, w, h,
                                     0,
                                     m_iDepth,
                                     InputOutput,
                                     m_pvisual,
                                     // CWBackPixmap | CWBorderPixmap
                                     CWColormap | CWEventMask | CWBackPixel | CWBorderPixel | CWOverrideRedirect,
                                     //CWColormap | CWEventMask | CWBorderPixel | CWOverrideRedirect,
                                     //CWColormap | CWEventMask | CWBorderPixel,
                                     &attr
            );

            printf("x11::acme::windowing::window XCreateWindow returned window=0x%lx\n",
                   static_cast<unsigned long>(m_window));
            fflush(stdout);

            XSync(display, False);

            printf("x11::acme::windowing::window XCreateWindow request synchronized successfully\n");
            fflush(stdout);

            if(!m_window)
            {

               throw exception(error_failed);

            }

            printf("x11::acme::windowing::window::_create_window before _wm_nodecorations xid=0x%lx\n",
                   static_cast<unsigned long>(m_window));
            fflush(stdout);

            _wm_nodecorations(false);

            printf("x11::acme::windowing::window::_create_window after _wm_nodecorations xid=0x%lx\n",
                   static_cast<unsigned long>(m_window));
            fflush(stdout);

            XWindowAttributes attr2;

            auto bGotWindowAttributes = XGetWindowAttributes(display, m_window, &attr2);

            printf("x11::acme::windowing::window::_create_window XGetWindowAttributes returned=%d xid=0x%lx map_state=%d size=(%d,%d) depth=%d visual=0x%lx\n",
                   bGotWindowAttributes, static_cast<unsigned long>(m_window),
                   bGotWindowAttributes ? attr2.map_state : -1,
                   bGotWindowAttributes ? attr2.width : -1,
                   bGotWindowAttributes ? attr2.height : -1,
                   bGotWindowAttributes ? attr2.depth : -1,
                   static_cast<unsigned long>(bGotWindowAttributes ? XVisualIDFromVisual(attr2.visual) : 0));
            fflush(stdout);

            if (!bGotWindowAttributes)
            {

               windowing_output_debug_string("::window::full_screen 1.2");

               //fflush(stdout);

               throw ::exception(error_failed);

            }

            m_lX11NativeVisualId = attr2.visual->visualid;

            constructø(m_pnanographicscontext);

            m_psurface = cairo_xlib_surface_create(
               display,
               m_window,
               m_pvisual,
               attr2.width,
               attr2.height);

            if (cairo_surface_status(m_psurface) != CAIRO_STATUS_SUCCESS)
            {

               throw ::exception(error_failed);

            }

            auto pcairo = cairo_create(m_psurface);

            if (cairo_status(pcairo) != CAIRO_STATUS_SUCCESS)
            {

               cairo_destroy(pcairo);

               throw ::exception(error_failed);

            }

            m_pnanographicscontext->attach(pcairo, {attr2.width, attr2.height}, 0);

            cairo_destroy(pcairo);

            _update_window();

            XFlush(display);

            printf("x11::acme::windowing::window::_create_window completed xid=0x%lx\n",
                   static_cast<unsigned long>(m_window));
            fflush(stdout);

            //on_create_window();

         }


         void window::show_window(::user_interface::enum_show_window eshowwindow)
         {

            printf("x11::acme::windowing::window::show_window xid=0x%lx command=%d\n",
                   static_cast<unsigned long>(m_window), static_cast<int>(eshowwindow));
            fflush(stdout);

            display_lock displaylock(m_px11display->m_pDisplay);

            if (eshowwindow == ::user_interface::e_show_window_show_normal)
            {

               auto iMapResult = XMapWindow(m_px11display->m_pDisplay, m_window);

               auto iRaiseResult = XRaiseWindow(m_px11display->m_pDisplay, m_window);

               XSync(m_px11display->m_pDisplay, False);

               printf("x11::acme::windowing::window::show_window map_result=%d raise_result=%d xid=0x%lx synchronized\n",
                      iMapResult, iRaiseResult, static_cast<unsigned long>(m_window));
               fflush(stdout);

               // Mapping can clear an unmapped X window and queue Expose.
               // Paint once after the map as well, so the initial frame is
               // visible even before the Acme event pump dispatches Expose.
               _update_window();

               XFlush(m_px11display->m_pDisplay);

               set_active_window();

            }
            else if (eshowwindow == ::user_interface::e_show_window_hide)
            {

               XUnmapWindow(m_px11display->m_pDisplay, m_window);

            }
            else
            {

               throw ::not_implemented("x11::acme::windowing::window::show_window unknown eshowwindow");

            }

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


         void window::_on_cairo_draw(cairo_t *pcairo)
         {

            if (!m_pnanographicscontext)
            {

               cairo_set_source_rgba(pcairo, 1.0, 1.0, 1.0, 1.0);

               cairo_fill(pcairo);

               return ;

            }

            m_pnanographicscontext->on_begin_draw();

            _draw(m_pnanographicscontext);

            m_pnanographicscontext->on_end_draw();

            auto pixmap = m_pnanographicscontext->pixmap();

            auto psurface = cairo_surface_for_pixmap(pixmap);

            cairo_set_source_surface(pcairo, psurface, 0., 0.);

            cairo_set_operator(pcairo, CAIRO_OPERATOR_SOURCE);

            cairo_paint(pcairo);

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

               ::i32_rectangle r;

               r.left = pevent->xconfigure.x;

               r.top = pevent->xconfigure.y;

               r.right = pevent->xconfigure.x + pevent->xconfigure.width;

               r.bottom = pevent->xconfigure.y + pevent->xconfigure.height;

               m_pacmeuserinteraction->set_interaction_rectangle(r);

               if (m_pnanographicscontext)
               {

                  if (m_psurface)
                  {

                     cairo_xlib_surface_set_size(m_psurface, r.width(), r.height());

                     m_pnanographicscontext->m_size = r.size();

                  }

               }

            }
            else if (pevent->type == UnmapNotify)
            {

               informationf("UnmapNotify");

            }
            else if (pevent->type == MapNotify)
            {

               printf("x11::acme::windowing::window received MapNotify xid=0x%lx\n",
                      static_cast<unsigned long>(m_window));
               fflush(stdout);

               _update_window();

            }
            else if (pevent->type == Expose)
            {

               printf("x11::acme::windowing::window received Expose xid=0x%lx\n",
                      static_cast<unsigned long>(m_window));
               fflush(stdout);

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

                     auto pmouse = create_newø < ::user::mouse >();

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

                     auto pmouse = create_newø < ::user::mouse >();

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

                     auto pmouse = create_newø < ::user::mouse >();

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

                     auto pmouse = create_newø < ::user::mouse >();

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

                  auto pmouse = create_newø < ::user::mouse >();

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
//                  auto pmouse = create_newø < ::user::mouse >();
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

            printf("x11::acme::windowing::window::_update_window xid=0x%lx context=%p\n",
                   static_cast<unsigned long>(m_window), static_cast<void *>(m_pnanographicscontext));
            fflush(stdout);

            if (!m_pnanographicscontext)
            {

               return;

            }

            m_pnanographicscontext->on_begin_draw();

            ::pointer<::micro::elemental> pelemental = m_pacmeuserinteraction;

            printf("x11::acme::windowing::window draw route interaction=%p micro_elemental=%p\n",
                   static_cast<void *>(m_pacmeuserinteraction), static_cast<void *>(pelemental));
            fflush(stdout);

            if (pelemental)
            {

               printf("x11::acme::windowing::window drawing micro background and foreground\n");
               fflush(stdout);

               auto ptheme = pelemental->micro_theme();

               if (ptheme)
               {

                  // Clear the complete ARGB surface to the active theme's
                  // opaque window color before drawing controls and text.
                  // This preserves alpha-capable visuals without leaving
                  // untouched pixels transparent.
                  m_pnanographicscontext->clear(ptheme->m_colorWindow);

                  // The Cairo clear above paints through the XRender visual
                  // correctly. A parallel XFillRectangle here used an
                  // incorrectly packed XRender pixel and replaced that opaque
                  // clear with transparent pixels on 32-bit ARGB visuals.
                  auto colorWindow = ptheme->m_colorWindow;

                  printf("x11::acme::windowing::window Cairo theme clear visual=0x%lx size=(%d,%d) rgba=(%.3f,%.3f,%.3f,%.3f)\n",
                         static_cast<unsigned long>(m_visualinfo.visualid),
                         m_pnanographicscontext->m_size.cx,
                         m_pnanographicscontext->m_size.cy,
                         colorWindow.f64_red(),
                         colorWindow.f64_green(),
                         colorWindow.f64_blue(),
                         colorWindow.f64_opacity());
                  fflush(stdout);

               }

               pelemental->draw_background(m_pnanographicscontext);

               pelemental->draw_foreground(m_pnanographicscontext);

            }
            else
            {

               printf("x11::acme::windowing::window draw skipped: interaction is not a micro::elemental\n");
               fflush(stdout);

            }

            m_pnanographicscontext->on_end_draw();

            if (m_psurface)
            {

               cairo_surface_flush(m_psurface);

            }

            if (m_psurface)
            {

               printf("x11::acme::windowing::window Cairo surface status=%d\n",
                      cairo_surface_status(m_psurface));
               fflush(stdout);

            }

            printf("x11::acme::windowing::window::_update_window completed xid=0x%lx\n",
                   static_cast<unsigned long>(m_window));
            fflush(stdout);

         }


         void window::_draw(::nano::graphics::context * pnanographicscontext)
         {

            ::cast < ::micro::elemental > pelemental = m_pacmeuserinteraction;

            if(pelemental)
            {

               pelemental->draw_background(pnanographicscontext);

               pelemental->draw_foreground(pnanographicscontext);

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

               if(::is_set(m_pnanographicscontext))
               {

                  //defer_finalize__destroy_and_release(m_pnanodevice);

                  __destroy_and_release(m_pnanographicscontext);

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


//         void window::move_to(const ::i32_point & point)
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


//         void window::get_client_rectangle(::i32_rectangle & rectangle)
//         {
//
//            rectangle.left = 0;
//            rectangle.top = 0;
//
//            Window windowRoot = 0;
//            int x = 0;
//            int y = 0;
//            ::u32 w = 0;
//            ::u32 h = 0;
//            ::u32 border = 0;
//            ::u32 depth = 0;
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


         ::i32_rectangle window::get_window_rectangle()
         {

            display_lock displaylock(m_px11display->m_pDisplay);

            Window windowRoot = 0;
            int x = 0;
            int y = 0;
            ::u32 w = 0;
            ::u32 h = 0;
            ::u32 border = 0;
            ::u32 depth = 0;

            auto status = XGetGeometry(m_px11display->m_pDisplay, m_window, &windowRoot, &x, &y, &w,
                                       &h, &border, &depth);

            if(status == BadDrawable)
            {

               throw ::exception(error_exception);

            }

            ::i32_rectangle rectangle;

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


         //   ::i32_size window::get_main_screen_size()
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

            auto pacmeuserinteractionActive = pacmewindowing->get_active_user_interaction();

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


         void window::user_send(const ::procedure & procedure)
         {

            system()->acme_windowing()->send(procedure);

         }


         void window::user_post(const ::procedure & procedure)
         {

            system()->acme_windowing()->post(procedure);

         }


         void window::main_send(const ::procedure & procedure)
         {

            user_send(procedure);

         }


         void window::main_post(const ::procedure & procedure)
         {

            user_post(procedure);

         }


      }//namespace windowing


   }//namespace acme


} // namespace x11



