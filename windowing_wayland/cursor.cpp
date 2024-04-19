// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sorensen MY ONLY LORD
// recreated by Camilo 2021-02-01 20:19
#include "framework.h"
#include "cursor.h"
#include "window.h"
#include "windowing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "aura/graphics/image/image.h"
#include "aura_posix/_x11.h"
#include "acme/operating_system/x11/display_lock.h"
//#include <X11/cursorfont.h>
#include <wayland-cursor.h>
#include <wayland-client.h>
#include <wayland-server.h>
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "display.h"



CLASS_DECL_ACME ::particle * user_synchronization();


namespace windowing_wayland
{


//   static void
//   pointer_handle_leave(void *data, struct wl_pointer *pointer,
//                        uint32_t serial, struct wl_surface *surface)
//   {
//      fprintf(stderr, "Pointer left surface %p\n", surface);
//   }
//
//   static void
//   pointer_handle_motion(void *data, struct wl_pointer *pointer,
//                         uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
//   {
//      printf("Pointer moved at %d %d\n", sx, sy);
//   }
//
//   static void
//   pointer_handle_button(void *data, struct wl_pointer *wl_pointer,
//                         uint32_t serial, uint32_t time, uint32_t button,
//                         uint32_t state)
//   {
//      printf("Pointer button\n");
//
//      auto pdisplay = (display *) data;
//
//      auto pwindow = pdisplay->_window(pwlsurface);
//
//
//      if (button == BTN_LEFT && state == WL_POINTER_BUTTON_STATE_PRESSED)
//         wl_shell_surface_move(shell_surface,
//                               seat, serial);
//
//   }
//
//   static void
//   pointer_handle_axis(void *data, struct wl_pointer *wl_pointer,
//                       uint32_t time, uint32_t axis, wl_fixed_t value)
//   {
//      printf("Pointer handle axis\n");
//   }

//   static const struct wl_pointer_listener pointer_listener = {
//      pointer_handle_enter,
//      pointer_handle_leave,
//      pointer_handle_motion,
//      pointer_handle_button,
//      pointer_handle_axis,
//   };

//   static void
//   seat_handle_capabilities(void *data, struct wl_seat *seat,
//                            enum wl_seat_capability caps)
//   {
//      if ((caps & WL_SEAT_CAPABILITY_POINTER) && !pointer) {
//         pointer = wl_seat_get_pointer(seat);
//         wl_pointer_add_listener(pointer, &pointer_listener, NULL);
//      } else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && pointer) {
//         wl_pointer_destroy(pointer);
//         pointer = NULL;
//      }
//   }
//
//   static const struct wl_seat_listener seat_listener = {
//      seat_handle_capabilities,
//   };
//
//   void
//   global_registry_handler(void *data, struct wl_registry *registry, uint32_t id,
//                           const char *interface, uint32_t version)
//   {
//      printf("Got a registry event for %s id %d\n", interface, id);
//      if (strcmp(interface, "wl_compositor") == 0) {
//         compositor = wl_registry_bind(registry,
//                                       id,
//                                       &wl_compositor_interface,
//                                       1);
//      } else if (strcmp(interface, "wl_shell") == 0) {
//         shell = wl_registry_bind(registry, id,
//                                  &wl_shell_interface, 1);
//
//      } else if (strcmp(interface, "wl_seat") == 0) {
//         seat = wl_registry_bind(registry, id,
//                                 &wl_seat_interface, 1);
//         wl_seat_add_listener(seat, &seat_listener, NULL);
//      } else if (strcmp(interface, "wl_shm") == 0) {
//         shm = wl_registry_bind(registry, id,
//                                &wl_shm_interface, 1);
//
//         cursor_theme = wl_cursor_theme_load(NULL, 32, shm);
//         default_cursor =
//            wl_cursor_theme_get_cursor(cursor_theme, "right_ptr");
//      }
//
//   }
//
//   static void
//   global_registry_remover(void *data, struct wl_registry *registry, uint32_t id)
//   {
//      printf("Got a registry losing event for %d\n", id);
//   }
//
//   static const struct wl_registry_listener registry_listener = {
//      global_registry_handler,
//      global_registry_remover
//   };
//
//
//
//
//   static void
//   create_window() {
//      egl_window = wl_egl_window_create(surface,
//                                        480, 360);
//      if (egl_window == EGL_NO_SURFACE) {
//         fprintf(stderr, "Can't create egl window\n");
//         exit(1);
//      } else {
//         fprintf(stderr, "Created egl window\n");
//      }
//
//      egl_surface =
//         eglCreateWindowSurface(egl_display,
//                                egl_conf,
//                                egl_window, NULL);
//
//      if (eglMakeCurrent(egl_display, egl_surface,
//                         egl_surface, egl_context)) {
//         fprintf(stderr, "Made current\n");
//      } else {
//         fprintf(stderr, "Made current failed\n");
//      }
//
//      glClearColor(1.0, 1.0, 0.0, 0.1);
//      glClear(GL_COLOR_BUFFER_BIT);
//      glFlush();
//
//
//      if (eglSwapBuffers(egl_display, egl_surface)) {
//         fprintf(stderr, "Swapped buffers\n");
//      } else {
//         fprintf(stderr, "Swapped buffers failed\n");
//      }
//      wl_display_dispatch(display);
//      wl_display_roundtrip(display);
//   }



//   static void
//   init_egl() {
//      EGLint major, minor, count, n, size;
//      EGLConfig *configs;
//      EGLBoolean ret;
//      int i;
//      EGLint config_attribs[] = {
//         EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
//         EGL_RED_SIZE, 8,
//         EGL_GREEN_SIZE, 8,
//         EGL_BLUE_SIZE, 8,
//         EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
//         EGL_NONE
//      };
//
//      static const EGLint context_attribs[] = {
//         EGL_CONTEXT_CLIENT_VERSION, 2,
//         EGL_NONE
//      };
//
//
//      egl_display = eglGetDisplay((EGLNativeDisplayType) display);
//      if (egl_display == EGL_NO_DISPLAY) {
//         fprintf(stderr, "Can't create egl display\n");
//         exit(1);
//      } else {
//         fprintf(stderr, "Created egl display\n");
//      }
//
//      if (eglInitialize(egl_display, &major, &minor) != EGL_TRUE) {
//         fprintf(stderr, "Can't initialise egl display\n");
//         exit(1);
//      }
//      printf("EGL major: %d, minor %d\n", major, minor);
//
//      if (! eglBindAPI(EGL_OPENGL_ES_API)) {
//         fprintf(stderr, "Can't bind API\n");
//         exit(1);
//      } else {
//         fprintf(stderr, "Bound API\n");
//      }
//
//      eglGetConfigs(egl_display, NULL, 0, &count);
//      printf("EGL has %d configs\n", count);
//
//      configs = calloc(count, sizeof *configs);
//
//      ret = eglChooseConfig(egl_display, config_attribs,
//                            configs, count, &n);
//
//      for (i = 0; i < n; i++) {
//         eglGetConfigAttrib(egl_display,
//                            configs[i], EGL_BUFFER_SIZE, &size);
//         printf("Buffer size for config %d is %d\n", i, size);
//         eglGetConfigAttrib(egl_display,
//                            configs[i], EGL_RED_SIZE, &size);
//         printf("Red size for config %d is %d\n", i, size);
//
//         egl_conf = configs[i];
//         break;
//      }
//
//      egl_context =
//         eglCreateContext(egl_display,
//                          egl_conf,
//                          EGL_NO_CONTEXT, context_attribs);
//
//   }
//
//   int main(int argc, char **argv) {
//
//      display = wl_display_connect(NULL);
//      if (display == NULL) {
//         fprintf(stderr, "Can't connect to display\n");
//         exit(1);
//      }
//      printf("connected to display\n");
//
//      struct wl_registry *registry = wl_display_get_registry(display);
//      wl_registry_add_listener(registry, &registry_listener, NULL);
//
//      wl_display_dispatch(display);
//      wl_display_roundtrip(display);
//
//      if (compositor == NULL) {
//         fprintf(stderr, "Can't find compositor\n");
//         exit(1);
//      } else {
//         fprintf(stderr, "Found compositor\n");
//      }
//
//      surface = wl_compositor_create_surface(compositor);
//      if (surface == NULL) {
//         fprintf(stderr, "Can't create surface\n");
//         exit(1);
//      } else {
//         fprintf(stderr, "Created surface %p\n", surface);
//      }
//
//      shell_surface = wl_shell_get_shell_surface(shell, surface);
//      wl_shell_surface_set_toplevel(shell_surface);
//
//
//      wl_shell_surface_add_listener(shell_surface,
//                                    &shell_surface_listener, NULL);
//
//      init_egl();
//      create_window();
//
//      cursor_surface =
//         wl_compositor_create_surface(compositor);
//
//      callback = wl_display_sync(display);
//      wl_callback_add_listener(callback, &configure_callback_listener,
//                               NULL);
//
//      while (wl_display_dispatch(display) != -1) {
//         ;
//      }
//
//      wl_display_disconnect(display);
//      printf("disconnected from display\n");
//
//      exit(0);
//   }
//


   cursor::cursor()
   {

      m_pwlcursor = nullptr;
      m_waylandbuffer.m_pwlbuffer  = nullptr;
      m_waylandbuffer.m_pwlbuffer = nullptr;
   }


   cursor::~cursor()
   {


   }


//   ::e_status cursor::initialize_system_default()
//   {
//
//      auto estatus = load_default_cursor(m_ecursor);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
//   }

   
//   ::e_status cursor::create_from_image(const ::image * pimage, ::i32 xHotspot, ::i16 yHotspot)
//   {
//
//      throw ::interface_only();
//
//      throw ::interface_only();
//
//   }


   void cursor::_create_os_cursor()
   {

      if(m_waylandbuffer.m_pwlbuffer)
      {

         return;

      }

      //auto estatus =
      //
      _load_default_cursor(m_ecursor);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }

   
   ::e_status cursor::_load_default_cursor(enum_cursor ecursor)
   {

      auto psystem = system();

      auto psession = psystem->session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      ::pointer < ::windowing_wayland::display> pwaylanddisplay =  pdisplay;

      const char * cursor_name = "left_ptr";

      switch(ecursor)
      {
         case e_cursor_system: cursor_name = "left_ptr"; break;
         case e_cursor_arrow: cursor_name = "left_ptr"; break;
         case e_cursor_hand: cursor_name = "hand1"; break;
         case e_cursor_text_select: cursor_name = "xterm"; break;
         case e_cursor_size_top_left: cursor_name = "top_left_corner"; break;
         case e_cursor_size_top: cursor_name = "top_side"; break;
         case e_cursor_size_top_right: cursor_name = "top_right_corner"; break;
         case e_cursor_size_right: cursor_name = "right_side"; break;
         case e_cursor_size_bottom_right: cursor_name = "bottom_right_corner"; break;
         case e_cursor_size_bottom: cursor_name = "bottom_side"; break;
         case e_cursor_size_bottom_left: cursor_name = "bottom_left_corner"; break;
         case e_cursor_size_left: cursor_name = "left_side"; break;
         case e_cursor_size_vertical: cursor_name = "sb_v_double_arrow"; break;
         case e_cursor_size_horizontal: cursor_name = "sb_h_double_arrow"; break;
         case e_cursor_move: cursor_name = "move"; break;
         case e_cursor_wait: cursor_name = "watch"; break;
         case e_cursor_wait_arrow: cursor_name = "wait"; break;
         default:
            break;
      }

      information() << "_load_default_cursor cursor_name : " << cursor_name;

      auto pwlcursortheme = wl_cursor_theme_load(NULL, 32, pwaylanddisplay->m_pwlshm);

      information() << "_load_default_cursor pwlcursortheme : " << (::iptr) pwlcursortheme;

      auto pwlcursor = wl_cursor_theme_get_cursor(pwlcursortheme, cursor_name);

      information() << "_load_default_cursor pwlcursor : " << (::iptr) pwlcursor;

      m_pwlcursor = pwlcursor;
      m_pwlcursorimage = m_pwlcursor->images[0];
      m_waylandbuffer.m_pwlbuffer = wl_cursor_image_get_buffer(m_pwlcursorimage);

      information() << "_load_default_cursor m_pwlbuffer : " << (::iptr) m_waylandbuffer.m_pwlbuffer;
      m_waylandbuffer.m_size.cx() = m_pwlcursor->images[0]->width;
      m_waylandbuffer.m_size.cy() = m_pwlcursor->images[0]->height;
      information() << "_load_default_cursor size : " << m_waylandbuffer.m_size;

      m_szHotspotOffset.cx() = m_pwlcursor->images[0]->hotspot_x;
      m_szHotspotOffset.cy() = m_pwlcursor->images[0]->hotspot_y;

      information() << "_load_default_cursor hotspot : " << m_szHotspotOffset;

      //m_pwlbuffer

      //iCursor = ::x11::get_default_system_cursor_glyph(ecursor);
//
//      if(iCursor == 0)
//      {
//
//         return ::error_failed;
//
//      }
//
////      if(ecursor == e_cursor_size_top_left)
////      {
////
////         iCursor = XC_top_left_corner;
////
////      }
////      else if(ecursor == e_cursor_size_top_right)
////      {
////
////         iCursor = XC_top_right_corner;
////
////      }
////      else if(ecursor == e_cursor_size_top)
////      {
////
////         iCursor = XC_top_side;
////
////      }
////      else if(ecursor == e_cursor_size_right)
////      {
////
////         iCursor = XC_right_side;
////
////      }
////      else if(ecursor == e_cursor_size_left)
////      {
////
////         iCursor = XC_left_side;
////
////      }
////      else if(ecursor == e_cursor_size_bottom)
////      {
////
////         iCursor = XC_bottom_side;
////
////      }
////      else if(ecursor == e_cursor_size_bottom_left)
////      {
////
////         iCursor = XC_bottom_left_corner;
////
////      }
////      else if(ecursor == e_cursor_size_bottom_right)
////      {
////
////         iCursor = XC_bottom_right_corner;
////
////      }
////      else if(ecursor == e_cursor_arrow)
////      {
////
////         iCursor = XC_arrow;
////
////      }
////
////      if(iCursor < 0)
////      {
////
////         return ::error_failed;
////
////      }
//
//      synchronous_lock sl(user_synchronization());
//
//      windowing_output_debug_string("::x11_GetWindowRect 1");
//
//      auto psystem = system();
//
//      auto psession = psystem->session()->m_paurasession;
//
//      auto puser = psession->user();
//
//      auto pwindowing = puser->windowing();
//
//      auto pdisplay = pwindowing->display();
//
//      auto px11display = (::windowing_wayland::display *) pwindowing->display()->m_pDisplay;
//
//      //display_lock lock(px11display->Display());
//
//      auto cursor = XCreateFontCursor(px11display->Display(), iCursor);
//
//      if(!cursor)
//      {
//
//         return error_failed;
//
//      }
//
//      m_cursor = cursor;

      return ::success;

   }


} // namespace windowing_wayland




