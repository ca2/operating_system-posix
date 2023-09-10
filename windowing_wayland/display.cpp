// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "cursor.h"
#include "display.h"
#include "window.h"
#include "windowing.h"
#include "windowing_wayland.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "apex/platform/node.h"
#include "apex/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura/graphics/image/image.h"
#include "aura/windowing/desktop_environment.h"
#include "aura/windowing/monitor.h"
#include "aura_posix/node.h"
//#include "aura_posix/x11/display_lock.h"
//#include <X11/extensions/Xrender.h>
#include <wayland-client-protocol.h>
#include <linux/input.h> // for BTN_LEFT
extern ::app_core * g_pappcore;
int
os_create_anonymous_file(off_t size);
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>

//Display * x11_get_display();

::particle * user_synchronization();


void windowing_output_debug_string(const ::scoped_string & scopedstrDebugString);


namespace windowing_wayland
{

//   /**
//* properties of the output
//*
//* The geometry event describes geometric properties of the
//* output. The event is sent when binding to the output object and
//* whenever any of the properties change.
//*
//* The physical size can be set to zero if it doesn't make sense
//* for this output (e.g. for projectors or virtual outputs).
//*
//* The geometry event will be followed by a done event (starting
//* from version 2).
//*
//* Note: wl_output only advertises partial information about the
//* output position and identification. Some compositors, for
//* instance those not implementing a desktop-style output layout or
//* those exposing virtual outputs, might fake this information.
//* Instead of using x and y, clients should use
//* xdg_output.logical_position. Instead of using make and model,
//* clients should use name and description.
//* @param x x position within the global compositor space
//* @param y y position within the global compositor space
//* @param physical_width width in millimeters of the output
//* @param physical_height height in millimeters of the output
//* @param subpixel subpixel orientation of the output
//* @param make textual description of the manufacturer
//* @param model textual description of the model
//* @param transform transform that maps framebuffer to output
//*/
//   void wl_output_geometry(void *data,
//                           struct wl_output *wl_output,
//                           int32_t x,
//                           int32_t y,
//                           int32_t physical_width,
//                           int32_t physical_height,
//                           int32_t subpixel,
//                           const char *make,
//                           const char *model,
//                           int32_t transform)
//   {
//
//   }
//   /**
//    * advertise available modes for the output
//    *
//    * The mode event describes an available mode for the output.
//    *
//    * The event is sent when binding to the output object and there
//    * will always be one mode, the current mode. The event is sent
//    * again if an output changes mode, for the mode that is now
//    * current. In other words, the current mode is always the last
//    * mode that was received with the current flag set.
//    *
//    * Non-current modes are deprecated. A compositor can decide to
//    * only advertise the current mode and never send other modes.
//    * Clients should not rely on non-current modes.
//    *
//    * The size of a mode is given in physical hardware units of the
//    * output device. This is not necessarily the same as the output
//    * size in the global compositor space. For instance, the output
//    * may be scaled, as described in wl_output.scale, or transformed,
//    * as described in wl_output.transform. Clients willing to retrieve
//    * the output size in the global compositor space should use
//    * xdg_output.logical_size instead.
//    *
//    * The vertical refresh rate can be set to zero if it doesn't make
//    * sense for this output (e.g. for virtual outputs).
//    *
//    * The mode event will be followed by a done event (starting from
//    * version 2).
//    *
//    * Clients should not use the refresh rate to schedule frames.
//    * Instead, they should use the wl_surface.frame event or the
//    * presentation-time protocol.
//    *
//    * Note: this information is not always meaningful for all outputs.
//    * Some compositors, such as those exposing virtual outputs, might
//    * fake the refresh rate or the size.
//    * @param flags bitfield of mode flags
//    * @param width width of the mode in hardware units
//    * @param height height of the mode in hardware units
//    * @param refresh vertical refresh rate in mHz
//    */
//   void wl_output_mode(void *data,
//                struct wl_output *wl_output,
//                uint32_t flags,
//                int32_t width,
//                int32_t height,
//                int32_t refresh);
//   /**
//    * sent all information about output
//    *
//    * This event is sent after all other properties have been sent
//    * after binding to the output object and after any other property
//    * changes done after that. This allows changes to the output
//    * properties to be seen as atomic, even if they happen via
//    * multiple events.
//    * @since 2
//    */
//   void wl_output_done(void *data,
//                struct wl_output *wl_output)
//   {
//
//   }
//   /**
//    * output scaling properties
//    *
//    * This event contains scaling geometry information that is not
//    * in the geometry event. It may be sent after binding the output
//    * object or if the output scale changes later. If it is not sent,
//    * the client should assume a scale of 1.
//    *
//    * A scale larger than 1 means that the compositor will
//    * automatically scale surface buffers by this amount when
//    * rendering. This is used for very high resolution displays where
//    * applications rendering at the native resolution would be too
//    * small to be legible.
//    *
//    * It is intended that scaling aware clients track the current
//    * output of a surface, and if it is on a scaled output it should
//    * use wl_surface.set_buffer_scale with the scale of the output.
//    * That way the compositor can avoid scaling the surface, and the
//    * client can supply a higher detail image.
//    *
//    * The scale event will be followed by a done event.
//    * @param factor scaling factor of output
//    * @since 2
//    */
//   void wl_output_scale(void *data,
//                 struct wl_output *wl_output,
//                 int32_t factor)
//   {
//
//   }
//   /**
//    * name of this output
//    *
//    * Many compositors will assign user-friendly names to their
//    * outputs, show them to the user, allow the user to refer to an
//    * output, etc. The client may wish to know this name as well to
//    * offer the user similar behaviors.
//    *
//    * The name is a UTF-8 string with no convention defined for its
//    * contents. Each name is unique among all wl_output globals. The
//    * name is only guaranteed to be unique for the compositor
//    * instance.
//    *
//    * The same output name is used for all clients for a given
//    * wl_output global. Thus, the name can be shared across processes
//    * to refer to a specific wl_output global.
//    *
//    * The name is not guaranteed to be persistent across sessions,
//    * thus cannot be used to reliably identify an output in e.g.
//    * configuration files.
//    *
//    * Examples of names include 'HDMI-A-1', 'WL-1', 'X11-1', etc.
//    * However, do not assume that the name is a reflection of an
//    * underlying DRM connector, X11 connection, etc.
//    *
//    * The name event is sent after binding the output object. This
//    * event is only sent once per output object, and the name does not
//    * change over the lifetime of the wl_output global.
//    *
//    * Compositors may re-use the same output name if the wl_output
//    * global is destroyed and re-created later. Compositors should
//    * avoid re-using the same name if possible.
//    *
//    * The name event will be followed by a done event.
//    * @param name output name
//    * @since 4
//    */
//   void wl_output_name(void *data,
//                struct wl_output *wl_output,
//                const char *name);
//   /**
//    * human-readable description of this output
//    *
//    * Many compositors can produce human-readable descriptions of
//    * their outputs. The client may wish to know this description as
//    * well, e.g. for output selection purposes.
//    *
//    * The description is a UTF-8 string with no convention defined for
//    * its contents. The description is not guaranteed to be unique
//    * among all wl_output globals. Examples might include 'Foocorp 11"
//    * Display' or 'Virtual X11 output via :1'.
//    *
//    * The description event is sent after binding the output object
//    * and whenever the description changes. The description is
//    * optional, and may not be sent at all.
//    *
//    * The description event will be followed by a done event.
//    * @param description output description
//    * @since 4
//    */
//   void wl_output_description(void *data,
//                       struct wl_output *wl_output,
//                       const char *description);
//
//   const static struct wl_output_listener g_wl_output_listener =
//      {
//wl_output_geometry,
//wl_output_mode,
//wl_output_done,
//wl_output_scale,
//wl_output_description
//
//      };


  // void xdg_surface_mouse_capture_configure(void * data, struct xdg_surface * xdg_surface, uint32_t serial)
//   {
//
//      auto pdisplay = (display *) data;
//
//      xdg_surface_ack_configure(xdg_surface, serial);
//
//      wl_surface_attach(pdisplay->m_pwlsurfaceMouseCapture, pdisplay->m_waylandbufferMouseCapture.m_pwlbuffer, 0, 0);
//
//      wl_surface_commit(pdisplay->m_pwlsurfaceMouseCapture);
//
//   }


//   static const struct xdg_surface_listener xdg_surface_mouse_capture_listener = {
//      xdg_surface_mouse_capture_configure,
//   };


   void
   pointer_handle_enter(void *data, struct wl_pointer *pwlpointer,
                        uint32_t serial, struct wl_surface *pwlsurface,
                        wl_fixed_t sx, wl_fixed_t sy)
   {

      auto x = wl_fixed_to_double(sx);
      auto y = wl_fixed_to_double(sy);

      struct wl_buffer *buffer;
      struct wl_cursor_image *image;

      fprintf(stderr, "Pointer entered surface %p at %0.0f %0.0f\n", pwlsurface, x, y);

      auto pdisplay = (display *) data;

      pdisplay->m_uLastPointerSerial = serial;

      pdisplay->m_uLastSeatSerial = serial;

      if(pwlsurface == pdisplay->m_pwlsurfaceMouseCapture)
      {

         fprintf(stderr, "entered Mouse Capture surface at %0.0f %0.0f!!\n", x, y);

         pdisplay->m_bMouseCaptured = true;

         ///pdisplay->__handle_pointer_enter(x, y, pwaylandwindow);

         return;

      }

      auto pwaylandwindow = pdisplay->_window(pwlsurface);

      //auto pcursor = pwaylandwindow->get_mouse_cursor();

//      auto pwlsurfaceCursor =  pdisplay->m_pwlsurfaceCursor;
//
//      ::pointer < ::windowing_wayland::cursor > pwaylandcursor = pcursor;

      //image = default_cursor->images[0];
      //buffer = wl_cursor_image_get_buffer(image);

//      if(pwaylandcursor)
//      {
//
//         wl_pointer_set_cursor(pwlpointer, serial,
//                               pwlsurfaceCursor,
//                               pwaylandcursor->m_szHotspotOffset.cx(),
//                               pwaylandcursor->m_szHotspotOffset.cy());
//         wl_surface_attach(pwlsurfaceCursor, pwaylandcursor->m_waylandbuffer.m_pwlbuffer, 0, 0);
//         wl_surface_damage(pwlsurfaceCursor, 0, 0, pwaylandcursor->m_pimage->width(),
//                           pwaylandcursor->m_pimage->height());
//         wl_surface_commit(pwlsurfaceCursor);
//
//      }

      pdisplay->__handle_pointer_enter(pwlpointer, x, y, pwaylandwindow);

   }

   void
   pointer_handle_leave(void *data, struct wl_pointer *pwlpointer,
                        uint32_t serial, struct wl_surface *pwlsurface)
   {

      fprintf(stderr, "Pointer left surface %p\n", pwlsurface);

      auto pdisplay = (display *) data;

      pdisplay->m_uLastPointerSerial = serial;

      pdisplay->m_uLastSeatSerial = serial;

      if(pdisplay->m_pwlsurfaceMouseCapture && pwlsurface == pdisplay->m_pwlsurfaceMouseCapture)
      {

         fprintf(stderr, "pointer left Mouse Capture surface\n");

         pdisplay->m_bMouseCaptured = false;

         ///pdisplay->__handle_pointer_enter(x, y, pwaylandwindow);

         return;

      }

      auto pwaylandwindowLeave = pdisplay->_window(pwlsurface);

      pdisplay->__handle_pointer_leave(pwlpointer, pwaylandwindowLeave);


   }

   void
   pointer_handle_motion(void *data, struct wl_pointer *pwlpointer,
                         uint32_t millis, wl_fixed_t sx, wl_fixed_t sy)
   {
      auto x = wl_fixed_to_double(sx);
      auto y = wl_fixed_to_double(sy);
      printf("Pointer moved at %0.0f %0.0f\n", x, y);

      auto pdisplay = (display *) data;

//      if(pdisplay->m_bMouseCaptured)
//      {
//
//         printf("Mouse Capture motion at %0.0f %0.0f!!\n", x, y);
//
//         ///pdisplay->__handle_pointer_enter(x, y, pwaylandwindow);
//
//         //return;
//
//      }
//

      pdisplay->__handle_pointer_motion(pwlpointer, x, y, millis);

   }

   void
   pointer_handle_button(void *data, struct wl_pointer *pwlpointer,
                         uint32_t serial, uint32_t millis, uint32_t linux_button,
                         uint32_t pressed)
   {
      printf("Pointer button\n");


      auto pdisplay = (display *) data;

      pdisplay->m_uLastButtonSerial = serial;

      pdisplay->m_uLastPointerSerial = serial;

      pdisplay->m_uLastSeatSerial = serial;

      if (linux_button == BTN_LEFT)
      {

         if(pressed == WL_POINTER_BUTTON_STATE_PRESSED)
         {

            pdisplay->m_pwlsurfaceLastLButtonDown = pdisplay->m_pwlsurfacePointerEnter;

         }
         else
         {

            //pdisplay->m_pwlsurfacePointerLButtonDown = null

         }

      }

      if(pdisplay->m_pwindowKeyboardFocus)
      {

//         if (linux_button == BTN_LEFT && pressed == WL_POINTER_BUTTON_STATE_PRESSED)
//            xdg_toplevel_move(pdisplay->m_pwindowKeyboardFocus->m_pxdgtoplevel,
//                                  pdisplay->m_pwlseat, serial);

      }

      pdisplay->__handle_pointer_button(pwlpointer, linux_button, pressed, millis);

   }

   void
   pointer_handle_axis(void *data, struct wl_pointer *wl_pointer,
                       uint32_t time, uint32_t axis, wl_fixed_t value)
   {
      printf("Pointer handle axis\n");
   }

   static const struct wl_pointer_listener g_wl_pointer_listener = {
      pointer_handle_enter,
      pointer_handle_leave,
      pointer_handle_motion,
      pointer_handle_button,
      pointer_handle_axis,
   };

   void shm_format(void *data, struct wl_shm *wl_shm, uint32_t format)
   {
      const char *s;
      switch (format) {
         case WL_SHM_FORMAT_ARGB8888: s = "ARGB8888"; break;
         case WL_SHM_FORMAT_XRGB8888: s = "XRGB8888"; break;
         case WL_SHM_FORMAT_RGB565: s = "RGB565"; break;
         case WL_SHM_FORMAT_RGBA8888: s = "RGBA8888"; break;
         default: s = "other format"; break;
      }
      fprintf(stderr, "Possible shmem format %s\n", s);
   }

   static const struct wl_shm_listener shm_listener = {
      shm_format
   };



   static void
   keyboard_handle_keymap(void *data, struct wl_keyboard *keyboard,
                          uint32_t format, int fd, uint32_t size)
   {
   }

   static void
   keyboard_handle_enter(void *data, struct wl_keyboard *pwlkeyboard,
                         uint32_t serial, struct wl_surface *pwlsurface,
                         struct wl_array *keys)
   {
      fprintf(stderr, "Keyboard gained focus\n");
      auto pdisplay = (display *) data;
      pdisplay->m_pwlkeyboard = pwlkeyboard;
      pdisplay->m_pwlsurfaceKeyboardEnter = pwlsurface;

      pdisplay->m_uLastSeatSerial = serial;

   }

   static void
   keyboard_handle_leave(void *data, struct wl_keyboard *pwlkeyboard,
                         uint32_t serial, struct wl_surface *pwlsurface)
   {
      fprintf(stderr, "Keyboard lost focus\n");
      auto pdisplay = (display *) data;
      if(pwlkeyboard == pdisplay->m_pwlkeyboard)
      {
         pdisplay->m_pwlkeyboard = nullptr;
      }
      if(pwlsurface == pdisplay->m_pwlsurfaceKeyboardEnter)
      {
         pdisplay->m_pwlsurfaceKeyboardEnter = nullptr;
      }
      pdisplay->m_uLastSeatSerial = serial;
   }

   static void
   keyboard_handle_key(void *data, struct wl_keyboard *keyboard,
                       uint32_t serial, uint32_t time, uint32_t key,
                       uint32_t state)
   {
      fprintf(stderr, "Key is %d state is %d\n", key, state);
      auto pdisplay = (display *) data;
      pdisplay->m_uLastSeatSerial = serial;
   }

   static void
   keyboard_handle_modifiers(void *data, struct wl_keyboard *keyboard,
                             uint32_t serial, uint32_t mods_depressed,
                             uint32_t mods_latched, uint32_t mods_locked,
                             uint32_t group)
   {
      fprintf(stderr, "Modifiers depressed %d, latched %d, locked %d, group %d\n",
              mods_depressed, mods_latched, mods_locked, group);
      auto pdisplay = (display *) data;
      pdisplay->m_uLastSeatSerial = serial;

   }

   static const  struct wl_keyboard_listener g_wl_keyboard_listener = {
      keyboard_handle_keymap,
      keyboard_handle_enter,
      keyboard_handle_leave,
      keyboard_handle_key,
      keyboard_handle_modifiers,
   };

   void
   seat_handle_capabilities(void *data, struct wl_seat *seat,
                            uint32_t caps)
   {
      auto pdisplay = (display*)data;

      if (caps & WL_SEAT_CAPABILITY_KEYBOARD && !pdisplay->m_pwlkeyboard)
      {

         pdisplay->m_pwlkeyboard = wl_seat_get_keyboard(seat);

         wl_keyboard_add_listener(pdisplay->m_pwlkeyboard, &g_wl_keyboard_listener, data);

      }
      else if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD) && pdisplay->m_pwlkeyboard)
      {

         wl_keyboard_destroy(pdisplay->m_pwlkeyboard);

         pdisplay->m_pwlkeyboard = NULL;

      }

      if ((caps & WL_SEAT_CAPABILITY_POINTER) && !pdisplay->m_pwlpointer)
      {

         pdisplay->m_pwlpointer = wl_seat_get_pointer(seat);

         wl_pointer_add_listener(pdisplay->m_pwlpointer, &g_wl_pointer_listener, data);

      }
      else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && pdisplay->m_pwlpointer)
      {

         wl_pointer_destroy(pdisplay->m_pwlpointer);

         pdisplay->m_pwlpointer = NULL;

      }

   }

   static const struct wl_seat_listener g_wl_seat_listener = {
      seat_handle_capabilities,
   };

   void xdg_wm_base_ping(void *data,
                         struct xdg_wm_base *xdg_wm_base,
                         uint32_t serial)
   {

      xdg_wm_base_pong(xdg_wm_base, serial);

   }

   static const struct  xdg_wm_base_listener g_xdg_wm_base_listener=
      {
         xdg_wm_base_ping

      };


   void global_registry_handler(void *data, struct wl_registry *pwlregistry, uint32_t id,
                           const char *interface, uint32_t version)
   {

      auto pdisplay = (display*)data;

      if (strcmp(interface, "wl_compositor") == 0)
      {

         pdisplay->m_pwlcompositor = (::wl_compositor*)wl_registry_bind(pwlregistry, id, &wl_compositor_interface, 1);

      }
      else if (strcmp(interface, "xdg_wm_base") == 0)
      {

         pdisplay->m_pxdgwmbase = (::xdg_wm_base*)wl_registry_bind(pwlregistry, id, &xdg_wm_base_interface, 1);

         xdg_wm_base_add_listener(pdisplay->m_pxdgwmbase, &g_xdg_wm_base_listener, data);

      }
      else if (strcmp(interface, "wl_shm") == 0)
      {

         pdisplay->m_pwlshm = (::wl_shm*)wl_registry_bind(pwlregistry, id, &wl_shm_interface, 1);

         wl_shm_add_listener(pdisplay->m_pwlshm, &shm_listener, data);

      }
      else if (strcmp(interface, "wl_seat") == 0)
      {

         pdisplay->m_pwlseat = (::wl_seat*)wl_registry_bind(pwlregistry, id, &wl_seat_interface, 1);

         wl_seat_add_listener(pdisplay->m_pwlseat, &g_wl_seat_listener, data);

      }
      else if (strcmp(interface, "wl_output") == 0)
      {

         auto pwloutput =  (::wl_output*)wl_registry_bind(pwlregistry, id, &wl_output_interface, 1);

//         if(pdisplay->m_wloutputa.add_unique(pwloutput) >= 0)
//         {
//
//            wl_output_add_listener(pwloutput, )
//
//
//         }

      }
      else if (strcmp(interface, "xdg_activation_v1") == 0)
      {
         pdisplay->m_pxdgactivationv1=  (::xdg_activation_v1*)wl_registry_bind(pwlregistry, id, &xdg_activation_v1_interface, 1);

      }
      else if (strcmp(interface, "gtk_shell1") == 0)
      {
         pdisplay->m_pgtkshell1=  (::gtk_shell1*)wl_registry_bind(pwlregistry, id, &gtk_shell1_interface, 1);

      }


      pdisplay->information("registry interface : %s", interface);


}

   void global_registry_remover(void *data, struct wl_registry *registry, uint32_t id)
   {

      printf("Got a registry losing event for %d\n", id);

   }

   static const struct wl_registry_listener g_wl_registry_listener =
      {
      global_registry_handler,
      global_registry_remover
   };



   display::display()
   {

      //m_bMouseCaptured = false;

      //zero(m_atoma);

      m_pDisplay = this;
      //m_colormap = None;
      //m_windowRoot = None;
      //m_px11display = nullptr;
      m_pwldisplay = nullptr;
      m_pwlshm = nullptr;
      m_pwlcompositor = nullptr;
      m_pxdgwmbase = nullptr;
      m_pwlseat = nullptr;
      m_pwlpointer = nullptr;
      m_pwlsurfaceCursor = nullptr;
      m_pwlsurfacePointerEnter = nullptr;

      m_pgtkshell1 = nullptr;
      m_pxdgactivationv1 = nullptr;

      m_pwlkeyboard = nullptr;
      m_pwlsurfaceLastLButtonDown = nullptr;
      m_pwlsurfaceKeyboardEnter = nullptr;

//      m_pxdgsurfaceMouseCapture = nullptr;
//      m_pxdgtoplevelMouseCapture = nullptr;
      //m_pwlshmpool = null;

//      m_atomLongType = None;
//      m_atomLongStyle = None;
//      m_atomNetWmState = None;
//      m_atomWmProtocols = None;
//      m_atomNetWmStateFocused = None;
//      m_atomNetWmStateHidden = None;
//      m_atomNetWmStateMaximizedHorz = None;
//      m_atomNetWmStateMaximizedVert = None;
//      m_atomNetWmSyncRequest = None;
//      m_atomNetWmSyncRequestCounter = None;
//      m_atomLongStyleEx = 0;
      m_countReference = 1;
      //m_bHasXSync = true;

   }


   display::~display()
   {

   }


#ifdef _DEBUG


   i64 display::get_ref_count()
   {

      return m_countReference;

   }


   i64 display::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

#ifdef WINDOWS

      return InterlockedIncrement64(&m_countReference);

#elif defined(RASPBERRYPIOS) && defined(OS32BIT)

      return __sync_add_and_fetch_4(&m_countReference,1);

#else

      return __sync_add_and_fetch(&m_countReference, 1);

#endif

   }


   i64 display::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

#ifdef WINDOWS

      return InterlockedDecrement64(&m_countReference);

#elif defined(RASPBERRYPIOS) && defined(OS32BIT)

      return __sync_sub_and_fetch_4(&m_countReference,1);

#else

      return __sync_sub_and_fetch(&m_countReference, 1);

#endif

   }


   i64 display::release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      i64 i = decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      return i;

   }


#endif // DEBUG

//
//   Display * display::_get_system_default_display()
//   {
//
//      return nullptr;
//
//   }


   void display::open()
   {

      if (::is_set(m_pwldisplay))
      {

         return;

      }

      information() << "windowing_wayland::display::open";

      ::pointer < ::aura_posix::node > pauraposixnode = acmenode();

      auto pwldisplay = pauraposixnode->get_wayland_display();

      m_pwldisplay = pwldisplay;

      information() << "windowing_wayland::display::open pwldisplay : " << (::iptr) pwldisplay;

      auto pwlregistry = wl_display_get_registry(m_pwldisplay);


      wl_registry_add_listener(pwlregistry, &g_wl_registry_listener, this);

      wl_display_dispatch(m_pwldisplay);

      wl_display_roundtrip(m_pwldisplay);

      m_pwlsurfaceCursor = wl_compositor_create_surface(m_pwlcompositor);

//      fork([this]()
//           {
//
//
////              redraw(NULL, NULL, 0);
//
//              while (wl_display_dispatch(m_pwldisplay) != -1)
//              {
//
//
//              }
//
//              wl_display_disconnect(m_pwldisplay);
//              //printf("disconnected from display\n");
//
//
//           });

      bool bBranch = !acmesession()->m_paurasession->user()->m_pdesktopenvironment->m_bUnhook;

//      m_px11display->m_bUnhook = bUnhook;

      //auto px11displayGdk = _get_system_default_display();

      //m_px11display = ::x11::display::get(this, false, px11displayGdk);

      // Using another memory_new and different X11 Display connection apart from Gtk.
      //m_px11display = ::x11::display::get(this, false);

      //if (::is_null(m_px11display))
      //{

        // throw ::exception(error_failed);

      //}

      //_m_pX11Display = m_px11display->m_pdisplay;

      //m_px11display->m_bUnhook = true;

//      if (XMatchVisualInfo(m_px11display->m_pdisplay, DefaultScreen(m_px11display->m_pdisplay), 32, TrueColor,
//                           &m_visualinfo))
//      {
//
//         m_pvisual = m_visualinfo.visual;
//
//      }
//      else
//      {
//
//         zero(m_visualinfo);
//
//      }

//      ::Display * pdisplay = m_px11display->m_pdisplay;
//
//      m_iScreen = XDefaultScreen(pdisplay);
//
//      m_windowRoot = XRootWindow(pdisplay, m_iScreen);
//
//      m_iDepth = m_visualinfo.depth;
//
//      XSetWindowAttributes attr;
//
//      zero(attr);
//
//      m_colormap = XCreateColormap(m_px11display->m_pdisplay, m_windowRoot, m_pvisual, AllocNone);
//
//      m_bHasXSync = false;
//
//#ifdef HAVE_XSYNC
//
//      {
//
//         int error_base, event_base;
//
//         if (XSyncQueryExtension(m_px11display->m_pdisplay, &event_base, &error_base) &&
//             XSyncInitialize(m_px11display->m_pdisplay, &m_iXSyncMajor, &m_iXSyncMinor))
//         {
//
//            m_bHasXSync = true;
//
//         }
//
//      }
//
//#endif
//
//      if (m_bHasXSync)
//      {
//
//         information() << "Display supports XSync";
//
//      }
//      else
//      {
//
//         information() << "Display doesn't support XSync";
//
//      }

//      //m_atomCardinal = intern_atom("CARDINAL", True);
//      m_atomWmProtocols = intern_atom("WM_PROTOCOLS", True);
//      m_atomWmState = intern_atom("WM_STATE", false);
//      m_atomNetWmState = intern_atom("_NET_WM_STATE", false);
//      m_atomNetWmSyncRequest = intern_atom("_NET_WM_SYNC_REQUEST", True);
//      m_atomNetWmSyncRequestCounter = intern_atom("_NET_WM_SYNC_REQUEST_COUNTER", True);
//      m_atomNetWmStateFocused = intern_atom("_NET_WM_STATE_FOCUSED", True);
//      m_atomNetWmStateHidden = intern_atom("_NET_WM_STATE_HIDDEN", True);
//      m_atomNetWmStateMaximizedHorz = intern_atom("_NET_WM_STATE_MAXIMIZED_HORZ", True);
//      m_atomNetWmStateMaximizedVert = intern_atom("_NET_WM_STATE_MAXIMIZED_VERT", True);
//
//
//      long *workArea;
//      int format;
//      unsigned long items, bytesAfter;
//      uint8_t *prop;
//      Atom type;
//      Atom _NET_WORKAREA = XInternAtom(pdisplay, "_NET_WORKAREA", 0);
//      m_rectangleaWorkAreas.clear();
//      if(XGetWindowProperty(pdisplay, m_windowRoot,
//                            _NET_WORKAREA, 0, ~0, False,
//                            XA_CARDINAL, &type, &format, &items, &bytesAfter, (uint8_t **)&workArea) || !workArea)
//      {
//         warning("error getting desktop work area, using root window size");
//      }
//      else
//      {
//         //logMsg("work area: %ld:%ld:%ld:%ld", workArea[0], workArea[1], workArea[2], workArea[3]);
//         for(int iPos = 0; iPos + 3 < items; iPos+=4)
//         {
//            m_rectangleaWorkAreas.add(::rectangle_i32_dimension(
//               workArea[iPos], workArea[iPos+1],
//               workArea[iPos+2], workArea[iPos+3]));
//         }
//         XFree(workArea);
//      }
//
////      for(auto & r : rectanglea)
////      {
////         auto pmonitor = get_best_monitor(r);
////
////         if(::is_set(pmonitor))
////         {
////
////            pmonitor->set_workspace_rectangle(r);
////
////         }
////
////      }

   }


   ::windowing_wayland::window * display::_window(::wl_surface * pwlsurface)
   {

      if (!pwlsurface)
      {

         return nullptr;

      }

      critical_section_lock synchronouslock(&m_criticalsectionWindowMap);

      auto passociation = m_windowmap.plookup(pwlsurface);

      if (passociation.is_null())
      {

         return nullptr;

      }

      return passociation->m_element2;

   }


   void display::lock_display()
   {

      if (!is_main_thread())
      {

         information("not main thread");

      }

      //XLockDisplay(m_px11display->m_pdisplay);

   }


   void display::unlock_display()
   {

      //XUnlockDisplay(m_px11display->m_pdisplay);

   }


   ::wl_display * display::_wl_display()
   {

      return ::is_null(this) ? nullptr : m_pwldisplay;

   }


   ::wl_display * display::_wl_display() const
   {

      return ::is_null(this) ? nullptr : m_pwldisplay;

   }


   ::wl_surface * display::_wl_surface_focus()
   {

      if(m_pwlsurfaceKeyboardEnter)
      {

         return m_pwlsurfaceKeyboardEnter;

      }
      else if(m_pwlsurfaceLastLButtonDown)
      {

         return m_pwlsurfaceLastLButtonDown;

      }

      return nullptr;

   }


//   int display::Screen()
//   {
//
//      return ::is_null(this) ? 0 : m_iScreen;
//
//   }
//
//
//   int display::Screen() const
//   {
//
//      return ::is_null(this) ? 0 : m_iScreen;
//
//   }
//
//
//   Atom display::atom_long_type()
//   {
//
//      return ::is_null(this) ? 0 : m_atomLongType;
//
//   }
//
//
//   Atom display::atom_long_style()
//   {
//
//      return ::is_null(this) ? 0 : m_atomLongStyle;
//
//   }
//
//
//   Atom display::atom_long_style_ex()
//   {
//
//      return ::is_null(this) ? 0 : m_atomLongStyleEx;
//
//   }


   bool display::is_null() const
   {

      return ::is_null(this);

   }


   bool display::get_monitor_rectangle(index iMonitor, ::rectangle_i32 & rectangle)
   {

      return ::windowing::display::get_monitor_rectangle(iMonitor, rectangle);

   }


   bool display::get_workspace_rectangle(index iMonitor, ::rectangle_i32 & rectangle)
   {

      return ::windowing::display::get_workspace_rectangle(iMonitor, rectangle);

   }


   ::windowing::window * display::get_mouse_capture()
   {

      return m_pwindowMouseCapture;

   }


   ::e_status display::release_mouse_capture()
   {

      information() << "windowing_wayland::display::release_mouse_capture";

//      auto predicate = [this]()
//      {
//
//         synchronous_lock synchronouslock(user_synchronization());
//
//         //display_lock displaylock(Display());
//
//         information() << "XUngrabPointer";
//
//         int_bool bRet = XUngrabPointer(Display(), CurrentTime) != false;
//
//         _on_capture_changed_to(nullptr);
//
//      };
//
//      auto pwindowing = x11_windowing();
//
//      pwindowing->windowing_post(predicate);

      return ::success;

   }


   ::windowing_wayland::windowing * display::x11_windowing()
   {

      return (::windowing_wayland::windowing *) m_pwindowing->m_pWindowing4;

   }


   void display::_on_capture_changed_to(::windowing_wayland::window * pwindowMouseCaptureNew)
   {

      auto pwindowMouseCaptureOld = m_pwindowMouseCapture;

      m_pwindowMouseCapture = pwindowMouseCaptureNew;

      if (pwindowMouseCaptureOld && pwindowMouseCaptureOld != pwindowMouseCaptureNew)
      {

         MESSAGE msg;

         msg.oswindow = pwindowMouseCaptureOld;
         msg.m_atom = e_message_capture_changed;
         msg.wParam = 0;
         msg.lParam = pwindowMouseCaptureNew;

         auto pwindowing = x11_windowing();

         pwindowing->post_ui_message(msg);

      }

   }


//   Atom display::intern_atom(const char * pszAtomName, bool bCreate)
//   {
//
//      if (m_px11display == nullptr)
//      {
//
//         return 0;
//
//      }
//
//      return m_px11display->intern_atom(pszAtomName, bCreate);
//
//   }
//
//
//   Atom display::intern_atom(::x11::enum_atom eatom, bool bCreate)
//   {
//
//      if (eatom < 0 || eatom >= ::x11::e_atom_count)
//      {
//
//         return None;
//
//      }
//
//      //Atom atom = m_atoma[eatom];
//
//      //if (atom == None)
//      {
//
//         auto atom = intern_atom(atom_name(eatom), bCreate);
//
//         return atom;
//
//         // m_atoma[eatom] = atom;
//
//      }
//
//      //return atom;
//
//   }
//
//
//   Atom display::_intern_atom_unlocked(const char * pszAtomName, bool bCreate)
//   {
//
//      if (m_px11display == nullptr)
//      {
//
//         return 0;
//
//      }
//
//      return m_px11display->_intern_atom_unlocked(pszAtomName, bCreate);
//
//   }
//
//
//   Atom display::_intern_atom_unlocked(::x11::enum_atom eatom, bool bCreate)
//   {
//
//      if (eatom < 0 || eatom >= ::x11::e_atom_count)
//      {
//
//         return None;
//
//      }
//
//      //Atom atom = m_atoma[eatom];
//
//      //if (atom == None)
//      {
//
//         auto atom = _intern_atom_unlocked(atom_name(eatom), bCreate);
//
//         return atom;
//
//         // m_atoma[eatom] = atom;
//
//      }
//
//      //return atom;
//
//   }


   ::e_status display::erase_window(::windowing::window * pwindow)
   {

      return error_failed;

   }


//   Atom display::net_wm_state_atom(bool bCreate)
//   {
//
//      if (m_atomNetWmState == None)
//      {
//
//         m_atomNetWmState = intern_atom(::x11::e_atom_net_wm_state, bCreate);
//
//      }
//
//      return m_atomNetWmState;
//
//   }


//   Picture display::xrender_create_picture(::image_pointer pimage)
//   {
//
//      Pixmap pixmap = _x11_create_pixmap(pimage);
//
//      if (pixmap == 0)
//      {
//
//         return 0;
//
//      }
//
//      auto dpy = Display();
//
//      auto vis = Visual();
//
//      XRenderPictFormat * pformat = XRenderFindVisualFormat(dpy, &vis);
//
//      bool hasAlpha = (pformat->type == PictTypeDirect && pformat->direct.alphaMask);
//      int x = 0;
//      int y = 0;
//      int width = pimage->width();
//      int height = pimage->height();
//
//      XRenderPictureAttributes pa = {};
//
//      Picture picture = XRenderCreatePicture(Display(), pixmap, pformat, CPSubwindowMode, &pa);
//
//      return picture;
//
//   }


   ::windowing_wayland::window * display::_get_active_window(::thread * pthread)
   {

//      auto window = m_px11display->_get_active_window();
//
//      auto pwindow = _window(window);
//
//      windowing_output_debug_string("::GetActiveWindow 2");
//
//      return pwindow;

return nullptr;

   }


   ::windowing_wayland::window * display::get_keyboard_focus()
   {

      return m_pwindowKeyboardFocus;

   }


   ::windowing_wayland::window * display::_get_keyboard_focus()
   {

//      auto ppropertyobject = __new(::property_object);
//
//      auto predicate = [this, ppropertyobject]()
//      {
//
//         synchronous_lock synchronouslock(user_synchronization());
//
//         oswindow oswindow = nullptr;
//
//         windowing_output_debug_string("::GetFocus 1");
//
//#ifdef display_lock_LOCK_LOG
//
//         b_prevent_display_lock_lock_log = false;
//
//#endif
//
//         //display_lock displaylock(Display());
//
//         windowing_output_debug_string("::GetFocus 1.01");
//
//         Window window = None;
//
//         int revert_to = 0;
//
//         bool bOk = XGetInputFocus(Display(), &window, &revert_to) != 0;
//
//         if (!bOk)
//         {
//
//            windowing_output_debug_string("::GetFocus 1.2");
//
//            return;
//
//         }
//
//         if (window == None || window == PointerRoot)
//         {
//
//            windowing_output_debug_string("::GetFocus 1.3");
//
//            return;
//
//         }
//
//         ppropertyobject->payload("window") = (::iptr) window;
//
//         windowing_output_debug_string("::GetFocus 2");
//
//      };
//
//      auto pwindowing = x11_windowing();
//
//      //proutine->set_timeout(5_s);
//
//      pwindowing->windowing_send(predicate);
//
////      if(proutine->has_timed_out())
////      {
////
////         return nullptr;
////
////      }
//
//      if (ppropertyobject->payload("window").is_new())
//      {
//
//         return nullptr;
//
//      }
//
//      Window window = (Window) ppropertyobject->payload("window").as_iptr();
//
//      auto pwindow = _window(window);
//
//      if (!pwindow)
//      {
//
//         return nullptr;
//
//      }
//
//      return pwindow;

return nullptr;

   }


   bool display::get_cursor_position(::point_i32 * ppointCursor)
   {

//      Window root_return;
//      Window child_return;
      i32 win_x_return;
      i32 win_y_return;
      u32 mask_return;

#ifdef display_lock_LOCK_LOG

      b_prevent_display_lock_lock_log = true;

#endif

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("::GetCursorPos 1");

      //display_lock displaylock(Display());

//      XQueryPointer(Display(), DefaultRootWindow(Display()), &root_return, &child_return, &ppointCursor->x(),
//                    &ppointCursor->y(), &win_x_return, &win_y_return, &mask_return);

#ifdef display_lock_LOCK_LOG

      b_prevent_display_lock_lock_log = false;

#endif

      windowing_output_debug_string("::GetCursorPos 2");

      return true;

   }


//   XImage * display::_x11_create_image(::image_pointer pimage)
//   {
//
//      pimage->map();
//
//      char * image32 = (char *) pimage->get_data();
//
//      int width = pimage->width();
//
//      int height = pimage->height();
//
//      int depth = 32; // works fine with depth = 24
//
//      int bitmap_pad = 32; // 32 for 24 and 32 bpp, 16, for 15&16
//
//      int bytes_per_line = pimage->scan_size(); // number of bytes in the client image between the start of one scanline and the start of the next
//
//      XImage * pximage = XCreateImage(Display(), CopyFromParent, depth, ZPixmap, 0, image32, width, height,
//                                      bitmap_pad, bytes_per_line);
//
//      return pximage;
//
//   }
//
//
//   XImage * display::x11_create_image(::image_pointer pimage)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::x11_create_image 1");
//
//      //display_lock displaylock(Display());
//
//      return _x11_create_image(pimage);
//
//   }
//
//
//   Pixmap display::_x11_create_pixmap(::image_pointer pimage)
//   {
//
//      if (!pimage)
//      {
//
//         return 0;
//
//      }
//
//      XImage * pximage = _x11_create_image(pimage);
//
//      if (pximage == nullptr)
//      {
//
//         return 0;
//
//      }
//
//      int depth = 32; // works fine with depth = 24
//
//      Pixmap pixmap = XCreatePixmap(Display(), DefaultRootWindow(Display()), pimage->width(), pimage->height(), depth);
//
//      XGCValues gcvalues = {};
//
//      GC gc = XCreateGC(Display(), pixmap, 0, &gcvalues);
//
//      XPutImage(Display(), pixmap, gc, pximage, 0, 0, 0, 0, pimage->width(), pimage->height());
//
//      XFreeGC(Display(), gc);
//
//      return pixmap;
//
//   }
//
//
//   Pixmap display::x11_create_pixmap(::image_pointer pimage)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::x11_create_pixmap 1");
//
//      //display_lock displaylock(Display());
//
//      return _x11_create_pixmap(pimage);
//
//   }
//
//
//   comparable_array<Window> display::x11_window_list()
//   {
//
//      comparable_array<Window> windowa;
//
//      auto atomWindowList = intern_atom("_NET_CLIENT_LIST_STACKING", False);
//
//      if (atomWindowList == 0)
//      {
//
//         atomWindowList = intern_atom("_NET_CLIENT_LIST", False);
//
//      }
//
//      if (atomWindowList == 0)
//      {
//
//         return windowa;
//
//      }
//
//      Atom type;
//      int form;
//      unsigned long remain;
//      unsigned char * list;
//      unsigned long ulBytesReturned = 0;
//      //errno = 0;
//
//      Atom actual_type;
//
//      int actual_format;
//
//      unsigned long int bytes_after;
//
//      Window * windowList = nullptr;
//
//      if (XGetWindowProperty(
//         Display(),
//         Window(),
//         atomWindowList, 0, 1024, False, XA_WINDOW,
//         &actual_type, &actual_format, &ulBytesReturned, &bytes_after,
//         (unsigned char **) &windowList) != Success)
//      {
//
//         information("winlist() -- GetWinProp");
//
//         return windowa;
//
//      }
//
//      unsigned long nchildren = ulBytesReturned / sizeof(Window);
//
//      windowa.set_size(nchildren);
//
//      memcpy(windowa.data(), windowList, minimum(windowa.get_size_in_bytes(), ulBytesReturned));
//
//      XFree(windowList);
//
//      return windowa;
//
//   }


//   bool display::point_is_window_origin(::point_i32 pointHitTest, ::windowing::window * pwindowExclude, int iMargin)
//   {
//
//      bool bIsOrigin = false;
//
//      auto psystem = acmesystem()->m_papexsystem;
//
//      auto pnode = psystem->node();
//
//      pnode->node_send([this, pointHitTest, pwindowExclude, iMargin, &bIsOrigin]()
//                       {
//
//                          ::windowing_wayland::window * pwindowxcbExclude = nullptr;
//
//                          if (pwindowExclude)
//                          {
//
//                             pwindowxcbExclude = dynamic_cast < ::windowing_wayland::window * >(pwindowExclude);
//
//                          }
//
//                          synchronous_lock synchronouslock(user_synchronization());
//
//                          windowing_output_debug_string("::GetFocus 1");
//
//#ifdef display_lock_LOCK_LOG
//
//                          b_prevent_display_lock_lock_log = false;
//
//#endif
//
//                          if (!Display())
//                          {
//
//                             windowing_output_debug_string("::GetFocus 1.1");
//
//                             return;
//
//                          }
//
//                          //display_lock displaylock(Display());
//
//                          windowing_output_debug_string("::GetFocus 1.01");
//
//                          auto windowa = x11_window_list();
//
//                          ::rectangle_i32 rectangleTest;
//
//                          for (index i = 0; i < windowa.get_size(); i++)
//                          {
//
//                             string strItem = ::x11_get_name(Display(), windowa[i]);
//
//                             ::rectangle_i32 rectangleHigher;
//
//                             if (::is_set(pwindowxcbExclude) && windowa[i] == pwindowxcbExclude->Window())
//                             {
//
//                                continue;
//
//                             }
//
//                             if (::x11_get_window_rect(Display(), windowa[i], &rectangleHigher))
//                             {
//
//                                ::rectangle_i32 rectangleHitTest;
//
//                                rectangleHitTest.set(rectangleHigher.origin(), ::size_i32());
//
//                                rectangleHitTest.inflate(iMargin + 1);
//
//                                if (rectangleHitTest.contains(pointHitTest))
//                                {
//
//                                   bIsOrigin = true;
//
//                                   return;
//
//                                }
//
//                             }
//
//                          }
//
//                       });
//
//      return bIsOrigin;
//
//   }


   void display::destroy_wayland_buffer(wayland_buffer & waylandbuffer)
   {

      if(waylandbuffer.m_pwlbuffer)
      {

         wl_buffer_destroy(waylandbuffer.m_pwlbuffer);

         waylandbuffer.m_pwlbuffer = nullptr;

      }

      if(waylandbuffer.m_pwlshmpool)
      {

         wl_shm_pool_destroy(waylandbuffer.m_pwlshmpool);

         waylandbuffer.m_pwlshmpool = nullptr;

      }

      if(waylandbuffer.m_pdata && waylandbuffer.m_memsizeStorage > 0)
      {

         munmap(waylandbuffer.m_pdata, waylandbuffer.m_memsizeStorage);

         waylandbuffer.m_pdata = nullptr;

         waylandbuffer.m_memsizeStorage = 0;

         waylandbuffer.m_memsize2 = 0;

      }

      if(waylandbuffer.m_iFd >= 0)
      {

         ::close(waylandbuffer.m_iFd);

         waylandbuffer.m_iFd = -1;

      }

      waylandbuffer.m_size.cx() = 0;

      waylandbuffer.m_size.cy() = 0;

      waylandbuffer.m_stride = 0;

   }


   void display::update_wayland_buffer(wayland_buffer &waylandbuffer, const ::size_i32 & size)
   {

      //wayland_buffer waylandbuffer{};

      ::i32 iNewStride = size.cx() * 4; // 4 bytes per pixel;

      ::memsize memsizeNew = iNewStride * size.cy();

      if(memsizeNew > waylandbuffer.m_memsizeStorage)
      {

         destroy_wayland_buffer(waylandbuffer);

         waylandbuffer.m_memsizeStorage = memsizeNew * 2;

         //waylandbuffer

         //}

         //waylandbuffer.m_stride =

         //waylandbuffer.m_memsize = waylandbuffer.m_stride * size.cy();

         waylandbuffer.m_iFd = os_create_anonymous_file(waylandbuffer.m_memsizeStorage);

         if (waylandbuffer.m_iFd < 0)
         {

            error() << "creating a buffer file for wl_buffer failed: ";

            waylandbuffer.m_stride = 0;

            waylandbuffer.m_memsize2 = 0;

            waylandbuffer.m_memsizeStorage = 0;

            return;

         }

         waylandbuffer.m_pdata = mmap(
            NULL, waylandbuffer.m_memsizeStorage,
            PROT_READ | PROT_WRITE, MAP_SHARED,
            waylandbuffer.m_iFd, 0);

         if (waylandbuffer.m_pdata == MAP_FAILED)
         {

            error() << "mmap failed";

            ::close(waylandbuffer.m_iFd);

            waylandbuffer.m_stride = 0;

            waylandbuffer.m_memsize2 = 0;

            waylandbuffer.m_memsizeStorage = 0;

            waylandbuffer.m_pdata = nullptr;

            return;

         }

         waylandbuffer.m_pwlshmpool = wl_shm_create_pool(m_pwlshm, waylandbuffer.m_iFd, waylandbuffer.m_memsizeStorage);

      }

      waylandbuffer.m_stride = iNewStride;

      waylandbuffer.m_memsize2 = memsizeNew;

      if(waylandbuffer.m_pwlbuffer)
      {

         wl_buffer_destroy(waylandbuffer.m_pwlbuffer);

         waylandbuffer.m_pwlbuffer = nullptr;

      }

      waylandbuffer.m_pwlbuffer = wl_shm_pool_create_buffer(waylandbuffer.m_pwlshmpool, 0,
                                       size.cx(), size.cy(),
                                       waylandbuffer.m_stride,
                                       WL_SHM_FORMAT_ARGB8888);

      //wl_buffer_add_listener(buffer, &buffer_listener, buffer);

      waylandbuffer.m_size = size;

      //return waylandbuffer;

   }


   void display::update_wayland_buffer(wayland_buffer &waylandbuffer, ::image * pimage)
   {

      update_wayland_buffer(waylandbuffer, pimage->size());

      pimage->map();

      copy_image32((::image32_t*)waylandbuffer.m_pdata,
                   waylandbuffer.m_size,
                   waylandbuffer.m_stride,
                   pimage->data(), pimage->scan_size());

      //return waylandbuffer;

   }


   void display::__handle_pointer_enter(::wl_pointer * pwlpointer, double x, double y, ::windowing_wayland::window * pwindowPointerEnter)
   {

      m_pwindowPointerEnter = pwindowPointerEnter;

      if(m_pwindowPointerEnter)
      {

         //m_pwindowPointerEnter->m_pointPointer.x() = (double) m_pwindowPointerEnter->m_pointWindow.x() + x;

         //m_pwindowPointerEnter->m_pointPointer.y() = (double) m_pwindowPointerEnter->m_pointWindow.y() + y;

         m_pwindowPointerEnter->m_pointPointer.x() = x;

         m_pwindowPointerEnter->m_pointPointer.y() = y;

         m_pwindowPointerEnter->__handle_pointer_enter(pwlpointer);

      }

   }


   void display::__handle_pointer_motion(::wl_pointer * pwlpointer, double x, double y, ::u32 millis)
   {

      if(m_pwindowPointerCapture)
      {

         m_pwindowPointerCapture->m_pointPointer.x() = x;

         m_pwindowPointerCapture->m_pointPointer.y() = y;

         if(m_pwindowPointerEnter)
         {

            m_pwindowPointerEnter->m_pointPointer.x() = x;

            m_pwindowPointerEnter->m_pointPointer.y() = y;

         }

      }
      else if(m_pwindowPointerEnter)
      {

         m_pwindowPointerEnter->m_pointPointer.x() = x;

         m_pwindowPointerEnter->m_pointPointer.y() = y;

      }


      if(m_pwindowPointerCapture)
      {

         m_pwindowPointerCapture->__handle_pointer_motion(pwlpointer, millis);

      }
      else if(m_pwindowPointerEnter)
      {

         m_pwindowPointerEnter->__handle_pointer_motion(pwlpointer, millis);

      }

   }


   void display::__handle_pointer_leave(::wl_pointer * pwlpointer, ::windowing_wayland::window * pwaylandwindowLeave)
   {

      if(m_pwindowPointerCapture)
      {

         m_pwindowPointerCapture->__handle_pointer_leave(pwlpointer, pwaylandwindowLeave);

      }
      else if(m_pwindowPointerEnter)
      {

         m_pwindowPointerEnter->__handle_pointer_leave(pwlpointer, pwaylandwindowLeave);

      }

      if(m_pwindowPointerEnter == pwaylandwindowLeave)
      {

         m_pwindowPointerEnter.release();

      }

   }


   void display::__handle_pointer_button(::wl_pointer * pwlpointer, ::u32 linux_button, ::u32 pressed, ::u32 millis)
   {

      if(m_pwindowPointerCapture)
      {

         m_pwindowPointerCapture->__handle_pointer_button(pwlpointer, linux_button, pressed, millis);

      }
      else if(m_pwindowPointerEnter)
      {

         m_pwindowPointerEnter->__handle_pointer_button(pwlpointer, linux_button, pressed, millis);

      }

   }


   void display::__capture_mouse(::windowing_wayland::window * pwindowMouseCapture, ::u32 serial)
   {

      if(::is_null(pwindowMouseCapture))
      {

         return;

      }

      m_pwindowMouseCapture = pwindowMouseCapture;

//      m_rectangleMouseCapture = get_monitor_union_rectangle();
//
//      destroy_wayland_buffer(m_waylandbufferMouseCapture);
//
//      m_waylandbufferMouseCapture = create_wayland_buffer(m_rectangleMouseCapture.size());
//
//      memset(m_waylandbufferMouseCapture.m_pdata, 0, m_waylandbufferMouseCapture.m_memsize);
//
//      information() << "__capture_mouse : " << m_rectangleMouseCapture;
//
//      m_pwlsurfaceMouseCapture = wl_compositor_create_surface(m_pwlcompositor);
//
//      m_pxdgsurfaceMouseCapture = xdg_wm_base_get_xdg_surface(m_pxdgwmbase, m_pwlsurfaceMouseCapture);
//
//      xdg_surface_set_window_geometry(m_pxdgsurfaceMouseCapture,
//                                      m_rectangleMouseCapture.left(),
//                                      m_rectangleMouseCapture.top(),
//                                      m_rectangleMouseCapture.width(),
//                                      m_rectangleMouseCapture.height());
//
//      xdg_surface_add_listener(m_pxdgsurfaceMouseCapture,
//                               &xdg_surface_mouse_capture_listener, this);
//
//      m_pxdgtoplevelMouseCapture = xdg_surface_get_toplevel(m_pxdgsurfaceMouseCapture);
//
//      if (m_pxdgtoplevelMouseCapture == NULL)
//      {
//
//         error() << "Can't create Mouse Capture top level window";
//
//         throw ::exception(::error_failed);
//
//      }
//      else
//      {
//
//         information() << "Created Mouse Capture top level window";
//
//      }
//
//      xdg_surface_set_window_geometry(m_pxdgsurfaceMouseCapture,
//         m_rectangleMouseCapture.left(),
//         m_rectangleMouseCapture.top(),
//         m_rectangleMouseCapture.width(),
//         m_rectangleMouseCapture.height());
//
//      //xdg_toplevel_add_listener(m_pxdgtoplevel,
//        //                        &xdg_toplevel_listener, this);
//
//        //xdg_popup_grab(m_pxdgtoplevelMouseCapture, m_pwlseat, serial);
//
//      wl_surface_commit(m_pwlsurfaceMouseCapture);

   }

} // namespace windowing_wayland



