// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define WINDOWING_X11_DISPLAY_MEMBER


//#include "acme/operating_system/x11/nano/event_listener.h"
//#include "acme/operating_system/x11/nano/display.h"
#include "aura/windowing/display.h"

//#include "_x11.h"



namespace windowing_wayland
{


   class CLASS_DECL_WINDOWING_X11 display :
      virtual public ::windowing::display
   {
   public:


      ::wl_display *                               m_pwldisplay;

      critical_section                             m_criticalsectionWindowMap;
      window_map                                   m_windowmap;


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
      ::pointer<class window>                      m_pwindowKeyboardFocus;
      ::pointer<::windowing_wayland::window>           m_pwindowActive;
      ///::pointer<::windowing_wayland::window>           m_pwindowMouseCapture;
      //bool                                         m_bHasXSync;
      //int                                          m_iXSyncMajor;
      //int                                          m_iXSyncMinor;
   ::wl_shm *m_pwlshm;
   ::xdg_wm_base *m_pxdgwmbase;
   ::wl_compositor * m_pwlcompositor;
      ::wl_surface *       m_pwlsurfaceCursor;
      ::wl_seat *             m_pwlseat;
      ::wl_keyboard * m_pwlkeyboard;
      ::wl_pointer * m_pwlpointer;
      //::wl_shm_pool * m_pwlshmpool;
      ::wl_surface * m_pwlsurfacePointerEnter;
      ::wl_surface * m_pwlsurfaceLastLButtonDown;
      ::wl_surface * m_pwlsurfaceMouseCapture;
      ::xdg_surface * m_pxdgsurfaceMouseCapture;
      ::xdg_toplevel * m_pxdgtoplevelMouseCapture;
      wayland_buffer m_waylandbufferMouseCapture;
      bool m_bMouseCaptured ;
      ::rectangle_i32 m_rectangleMouseCapture;
      ::u32 m_uLastButtonSerial;
      ::u32 m_uLastPointerSerial;
      ::u32 m_uLastSeatSerial;
      ::gtk_shell1 * m_pgtkshell1;
      ::xdg_activation_v1 *m_pxdgactivationv1;
      //::wl_keyboard * m_pwlkeyboard;
      ::wl_surface * m_pwlsurfaceKeyboardEnter;
      //::comparable_array < ::wl_output * > m_wloutputa;
      //::comparable_array < ::xdg_output * > m_xdgoutputa;

      //::point_f64 m_pointPointer;

      //::u32 m_uLastPointerButton;
      //::u32 m_uLastPointerState;

      ::pointer < ::windowing_wayland::window > m_pwindowPointerEnter;
      ::pointer < ::windowing_wayland::window > m_pwindowPointerCapture;
  //    wl_compositor_create_surface(compositor);
//

      display();
      ~display() override;


#ifdef _DEBUG


      virtual i64 get_ref_count();
      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


      //virtual ::Display * _get_system_default_display();


      virtual ::windowing_wayland::window * _window(::wl_surface * pwlsurface);

      virtual ::windowing_wayland::windowing * x11_windowing();

      virtual void lock_display();

      virtual void unlock_display();

      void open() override;

      virtual ::e_status erase_window(::windowing::window * pwindow);

      virtual ::wl_display * _wl_display();

      virtual ::wl_display * _wl_display() const;

      virtual ::wl_surface * _wl_surface_focus();

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

      bool get_monitor_rectangle(index iMonitor, ::rectangle_i32 & rectangle) override;

      bool get_workspace_rectangle(index iWorkspace, ::rectangle_i32 & rectangle) override;

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

      void destroy_wayland_buffer(wayland_buffer & waylandbuffer);
      void update_wayland_buffer(wayland_buffer & waylandbuffer, const ::size_i32 & size);
      void update_wayland_buffer(wayland_buffer & waylandbuffer, ::image * pimage);

      virtual ::windowing_wayland::window * get_keyboard_focus();

      virtual ::windowing_wayland::window * _get_keyboard_focus();

      virtual ::windowing_wayland::window * _get_active_window(::thread * pthread);

      virtual bool get_cursor_position(::point_i32 * ppointCursor);

      //virtual comparable_array < Window > x11_window_list();

      virtual ::wl_cursor * create_alpha_cursor(::image *pimage, int xHotSpot, int yHotSpot);
//      virtual Pixmap _x11_create_pixmap(::image_pointer pimage);
//      virtual XImage * _x11_create_image(::image_pointer pimage);
//      virtual Pixmap x11_create_pixmap(::image_pointer pimage);
//      virtual XImage * x11_create_image(::image_pointer pimage);

      //virtual bool point_is_window_origin(::point_i32 pointHitTest, ::windowing::window * pwindowExclude, int iMargin);

      ///virtual Picture xrender_create_picture(::image_pointer pimage);


      virtual void __handle_pointer_enter(::wl_pointer * pwlpointer, double x, double y, ::windowing_wayland::window * pwindowPointerEnter);
      virtual void __handle_pointer_motion(::wl_pointer * pwlpointer, double x, double y, ::u32 time);
      virtual void __handle_pointer_leave(::wl_pointer * pwlpointer, ::windowing_wayland::window * pwindowPointerLeave);

      virtual void __handle_pointer_button(::wl_pointer * pwlpointer, ::u32 linux_button, ::u32 pressed, ::u32 time);


      //virtual void __capture_mouse(::windowing_wayland::window * pwindowMouseCapture, ::u32 serial);


   };


} // namespace windowing_wayland



