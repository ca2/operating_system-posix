#pragma once


#include "aura_posix/_.h"


#if defined(_windowing_wayland_project)
   #define CLASS_DECL_WINDOWING_X11  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_WINDOWING_X11  CLASS_DECL_IMPORT
#endif


namespace windowing_wayland
{


   class windowing;
   class display;
   class window;
   class x11data;


   using WINDOW = long;


   using window_map = map < WINDOW, ::pointer< window > >;


} // namespace node_gnome

struct wl_buffer;
struct wl_surface;
struct wl_compositor;
struct wl_display;
struct wl_shm;
struct wl_shell;
struct wl_cursor;
struct wl_cursor_image;


struct wayland_buffer
{
   ::wl_buffer *  m_pwlbuffer;
   void *         m_pdata;

};