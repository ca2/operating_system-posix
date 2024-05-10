// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define WINDOWING_X11_DISPLAY_MEMBER


//#include "acme/operating_system/x11/nano/event_listener.h"
//#include "acme/operating_system/x11/nano/display.h"
#include "acme/operating_system/wayland/nano/display_base.h"
#include "aura/windowing/display.h"

//#include "_x11.h"



namespace windowing_wayland
{


   class CLASS_DECL_WINDOWING_WAYLAND display :
      virtual public ::windowing::display,
      virtual public ::wayland::display_base
   {
   public:



      //Atom                                         m_atoma[::x11::e_atom_count];


      //::pointer<::x11::display>                    m_px11display;
      //::Display *                                m_pdisplay;
      //XVisualInfo                                  m_visualinfo;
      //::Visual *                                   m_pvisual;
      //Colormap                                     m_colormap;
      //int                                          m_iScreen;
      //int                                          m_iDepth;
      //Window                                       m_windowRoot;


//      Atom                                         m_atomLongType;
//      Atom                                         m_atomLongStyle;
//      Atom                                         m_atomLongStyleEx;
//      //Atom                                       m_atomCardinal;
//      Atom                                         m_atomWmState;
//      Atom                                         m_atomNetWmStateFocused;
//      Atom                                         m_atomNetWmStateHidden;
//      Atom                                         m_atomNetWmStateMaximizedHorz;
//      Atom                                         m_atomNetWmStateMaximizedVert;
//      Atom                                         m_atomNetWmState;
//      Atom                                         m_atomWmProtocols;
//      Atom                                         m_atomNetWmSyncRequest;
//      Atom                                         m_atomNetWmSyncRequestCounter;
      iptr                                         m_countReference;
      ::pointer<class window>                      m_pwindowRoot;
      //::pointer<class window>                      m_pwindowKeyboardFocus;
      ::pointer<::windowing_wayland::window>           m_pwindowActive;
      ///::pointer<::windowing_wayland::window>           m_pwindowMouseCapture;
      //bool                                         m_bHasXSync;
      //int                                          m_iXSyncMajor;
      //int                                          m_iXSyncMinor;

  //    wl_compositor_create_surface(compositor);
//

      display();
      ~display() override;


#ifdef _DEBUG


      virtual i64 get_ref_count();
      virtual i64 increment_reference_count() override;
      virtual i64 decrement_reference_count() override;
      virtual i64 release() override;


#endif


      void initialize(::particle * pparticle) override;


      //virtual ::Display * _get_system_default_display();

      bool has_readily_gettable_absolute_pointer_position() const override;


//      virtual ::windowing_wayland::window * _window(::wl_surface * pwlsurface);

      virtual ::windowing_wayland::windowing * x11_windowing();

      virtual void lock_display();

      virtual void unlock_display();

      ::wl_display * __get_wayland_display() override;

      void open() override;

      virtual ::e_status erase_window(::windowing::window * pwindow);

//      virtual ::wl_display * _wl_display();
//
//      virtual ::wl_display * _wl_display() const;
//
//      virtual ::wl_surface * _wl_surface_focus();

//      virtual int Screen();
//
//      virtual int Screen() const;
//
//      virtual Atom atom_long_type();
//
//      virtual Atom atom_long_style();
//
//      virtual Atom atom_long_style_ex();

      virtual bool is_null() const;

      bool get_monitor_rectangle(::collection::collection::index iMonitor, ::rectangle_i32 & rectangle) override;

      bool get_workspace_rectangle(::collection::collection::index iWorkspace, ::rectangle_i32 & rectangle) override;

      //virtual ::windowing::window * get_mouse_capture();

      virtual ::e_status release_mouse_capture();


//      Atom intern_atom(const char * pszAtomName, bool bCreate);
//
//      Atom intern_atom(::x11::enum_atom eatom, bool bCreate);
//
//      Atom _intern_atom_unlocked(const char * pszAtomName, bool bCreate);
//
//      Atom _intern_atom_unlocked(::x11::enum_atom eatom, bool bCreate);
//
//      Atom net_wm_state_atom(bool bCreate);



      virtual bool get_cursor_position(::point_i32 * ppointCursor);

      //virtual comparable_array < Window > x11_window_list();

      virtual ::wl_cursor * create_alpha_cursor(::image *pimage, int xHotSpot, int yHotSpot);
//      virtual Pixmap _x11_create_pixmap(::image_pointer pimage);
//      virtual XImage * _x11_create_image(::image_pointer pimage);
//      virtual Pixmap x11_create_pixmap(::image_pointer pimage);
//      virtual XImage * x11_create_image(::image_pointer pimage);

      //virtual bool point_is_window_origin(::point_i32 pointHitTest, ::windowing::window * pwindowExclude, int iMargin);

      ///virtual Picture xrender_create_picture(::image_pointer pimage);


//      virtual void __handle_pointer_enter(::wl_pointer * pwlpointer, double x, double y, ::windowing_wayland::window * pwindowPointerEnter);
//      virtual void __handle_pointer_motion(::wl_pointer * pwlpointer, double x, double y, ::u32 time);
//      virtual void __handle_pointer_leave(::wl_pointer * pwlpointer, ::windowing_wayland::window * pwindowPointerLeave);
//
//      virtual void __handle_pointer_button(::wl_pointer * pwlpointer, ::u32 linux_button, ::u32 pressed, ::u32 time);
//
//
//      //virtual void __capture_mouse(::windowing_wayland::window * pwindowMouseCapture, ::u32 serial);
//
//
//      virtual void __handle_keyboard_keymap(struct wl_keyboard *keyboard, uint32_t format, int fd, uint32_t size);
//      virtual void __handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_surface *pwlsurface, ::wl_array *pwlarrayKeys);
//      virtual void __handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_surface *pwlsurface);
//      virtual void __handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
//      virtual void __handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);


   };


} // namespace windowing_wayland



