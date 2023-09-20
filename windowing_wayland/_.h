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


} // namespace node_gnome

struct wl_buffer;
struct wl_surface;
struct wl_compositor;
struct wl_display;
struct wl_shm;
struct wl_shell;
struct wl_cursor;
struct wl_cursor_image;
struct wl_seat;
struct wl_keyboard;
struct wl_pointer;
struct wl_shell_surface;
struct wl_callback;
struct wl_shm_pool;
struct wl_keyboard;
struct wl_array;
struct wl_subsurface;
struct wl_subcompositor;

struct xdg_wm_base;
struct xdg_surface;
struct xdg_toplevel;
struct xdg_output;
struct xdg_popup;
struct xdg_positioner;

struct xdg_activation_v1;
struct xdg_activation_token_v1;

struct xkb_keymap;
struct xkb_context;
struct xkb_state;

struct gtk_shell1;

struct wayland_buffer
{


   ::wl_buffer *     m_pwlbuffer;
   ::wl_shm_pool *   m_pwlshmpool;
   void *            m_pdata;
   int               m_iFd;
   memsize           m_memsize2;
   memsize           m_memsizeStorage;
   ::size_i32        m_size;
   ::i32             m_stride;


   wayland_buffer(const wayland_buffer & waylandbuffer) = default;
   wayland_buffer()
   {
      m_pwlbuffer = nullptr;
      m_pwlshmpool = nullptr;
      m_pdata = nullptr;
      m_iFd = -1;
      m_memsize2 = 0;
      m_memsizeStorage = 0;
      m_stride = 0;
   }



};


namespace windowing_wayland
{

   using window_map = map<::wl_surface *, ::pointer<window> >;

} // namespace windowing_wayland

