// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define WINDOWING_X11_DISPLAY_MEMBER

//#include "acme/operating_system/x11/nano/event_listener.h"
//#include "acme/operating_system/x11/nano/display.h"
#include "acme_windowing_kde5/display.h"
#include "windowing_q5/display.h"
#include "_kde5.h"

//#include "_x11.h"



namespace windowing_kde5
{


   class CLASS_DECL_WINDOWING_KDE5 display :
      virtual public ::windowing_q5::display,
      virtual public ::kde5::acme::windowing::display
   {
   public:

//
// //GdkDisplay * m_pgdkdisplay;
//   //       wl_display * m_pwldisplay;
//     //     xdg_wm_base * m_pxdgwmbase;
//       //Atom                                         m_atoma[::x11::e_atom_count];
//
//
//       //::pointer<::x11::display>                    m_px11display;
//       //::Display *                                m_pdisplay;
//       //XVisualInfo                                  m_visualinfo;
//       //::Visual *                                   m_pvisual;
//       //Colormap                                     m_colormap;
//       //int                                          m_iScreen;
//       //int                                          m_iDepth;
//       //Window                                       m_windowRoot;
//
//
// //      Atom                                         m_atomLongType;
// //      Atom                                         m_atomLongStyle;
// //      Atom                                         m_atomLongStyleEx;
// //      //Atom                                       m_atomCardinal;
// //      Atom                                         m_atomWmState;
// //      Atom                                         m_atomNetWmStateFocused;
// //      Atom                                         m_atomNetWmStateHidden;
// //      Atom                                         m_atomNetWmStateMaximizedHorz;
// //      Atom                                         m_atomNetWmStateMaximizedVert;
// //      Atom                                         m_atomNetWmState;
// //      Atom                                         m_atomWmProtocols;
// //      Atom                                         m_atomNetWmSyncRequest;
// //      Atom                                         m_atomNetWmSyncRequestCounter;
//       iptr                                         m_countReference;
//       ::pointer<class window>                      m_pwindowRoot;
//       //::pointer<class window>                      m_pwindowKeyboardFocus;
//       ::pointer<::windowing_kde5::window>           m_pwindowActive;
//       ///::pointer<::windowing_kde5::window>           m_pwindowMouseCapture;
//       //bool                                         m_bHasXSync;
//       //int                                          m_iXSyncMajor;
//       //int                                          m_iXSyncMinor;
//
//   //    wl_compositor_create_surface(compositor);
// //

      display();
      ~display() override;

//
// #ifdef _DEBUG
//
//
//       virtual long long get_ref_count();
//       virtual long long increment_reference_count() override;
//       virtual long long decrement_reference_count() override;
//       virtual long long release() override;
//
//
// #endif
//
//
//       void initialize(::particle * pparticle) override;
//
//          virtual void open_display() override;
//
//
//          virtual void _enumerate_monitor();
//
//       //virtual ::Display * _get_system_default_display();
//
//       bool has_readily_gettable_absolute_pointer_position() const override;
//
//
// //      virtual ::windowing_kde5::window * _window(::wl_surface * pwlsurface);
//
//       virtual ::windowing_kde5::windowing * kde5_windowing();
//
//       virtual void lock_display();
//
//       virtual void unlock_display();
//
//       //::wl_display * __get_wayland_display() override;
//
//       //void open() override;
//
//       virtual ::e_status erase_window(::windowing::window * pwindow);
//
// //      virtual ::wl_display * _wl_display();
// //
// //      virtual ::wl_display * _wl_display() const;
// //
// //      virtual ::wl_surface * _wl_surface_focus();
//
// //      virtual int Screen();
// //
// //      virtual int Screen() const;
// //
// //      virtual Atom atom_long_type();
// //
// //      virtual Atom atom_long_style();
// //
// //      virtual Atom atom_long_style_ex();
//
//       virtual bool is_null() const;
//
//       bool get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle) override;
//
//       bool get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle & rectangle) override;
//
//       //virtual ::windowing::window * get_mouse_capture();
//
//       //void release_mouse_capture() override;
//
//
// //      Atom intern_atom(const char * pszAtomName, bool bCreate);
// //
// //      Atom intern_atom(::x11::enuid() eatom, bool bCreate);
// //
// //      Atom _intern_atom_unlocked(const char * pszAtomName, bool bCreate);
// //
// //      Atom _intern_atom_unlocked(::x11::enuid() eatom, bool bCreate);
// //
// //      Atom net_wm_state_atom(bool bCreate);
//
//
//
//       virtual bool get_cursor_position(::int_point * ppointCursor);
//
//       //virtual comparable_array < Window > x11_window_list();
//
//       //virtual ::wl_cursor * create_alpha_cursor(::image::image *pimage, int xHotSpot, int yHotSpot);
// //      virtual Pixmap _x11_create_pixmap(::image::image_pointer pimage);
// //      virtual XImage * _x11_create_image(::image::image_pointer pimage);
// //      virtual Pixmap x11_create_pixmap(::image::image_pointer pimage);
// //      virtual XImage * x11_create_image(::image::image_pointer pimage);
//
//       //virtual bool point_is_window_origin(::int_point pointHitTest, ::windowing::window * pwindowExclude, int iMargin);
//
//       ///virtual Picture xrender_create_picture(::image::image_pointer pimage);
//
//
// //      virtual void __handle_pointer_enter(::wl_pointer * pwlpointer, double x, double y, ::windowing_kde5::window * pwindowPointerEnter);
// //      virtual void __handle_pointer_motion(::wl_pointer * pwlpointer, double x, double y, unsigned int time);
// //      virtual void __handle_pointer_leave(::wl_pointer * pwlpointer, ::windowing_kde5::window * pwindowPointerLeave);
// //
// //      virtual void __handle_pointer_button(::wl_pointer * pwlpointer, unsigned int linux_button, unsigned int pressed, unsigned int time);
// //
// //
// //      //virtual void __capture_mouse(::windowing_kde5::window * pwindowMouseCapture, unsigned int serial);
// //
// //
// //      virtual void __handle_keyboard_keymap(struct wl_keyboard *keyboard, uint32_t format, int fd, uint32_t size);
// //      virtual void __handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_surface *pwlsurface, ::wl_array *pwlarrayKeys);
// //      virtual void __handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_surface *pwlsurface);
// //      virtual void __handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
// //      virtual void __handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);
//
//          virtual bool is_x11();
//          virtual bool is_wayland();
//
void init_task() override;
      void run() override;
      bool is_dark_mode_through_theming()  override;
      string theming_ui_name()  override;
          ::int_size get_main_screen_size() override;
      string impl_get_desktop_theme() override;
      void impl_set_desktop_theme(const ::scoped_string & scopedstrTheme) override;
      void set_desktop_icon_theme(const ::scoped_string & scopedstrIconTheme) override;


      bool is_branch_current() const override;
//
   };


} // namespace windowing_kde5



