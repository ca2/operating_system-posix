// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define WINDOWING_X11_DISPLAY_MEMBER


#include "acme/operating_system/x11/nano/event_listener.h"
#include "acme/operating_system/x11/nano/display.h"
#include "aura/windowing/display.h"
#include "_x11.h"


namespace windowing_x11
{


   class CLASS_DECL_WINDOWING_X11 display :
      virtual public ::windowing::display
   {
   public:


      critical_section                             m_criticalsectionWindowMap;
      window_map                                   m_windowmap;


      Atom                                         m_atoma[::x11::e_atom_count];


      ::pointer<::x11::display>                   m_px11display;
      //::Display *                                m_pdisplay;
      XVisualInfo                                  m_visualinfo;
      ::Visual *                                   m_pvisual;
      Colormap                                     m_colormap;
      int                                          m_iScreen;
      int                                          m_iDepth;
      Window                                       m_windowRoot;


      Atom                                         m_atomLongType;
      Atom                                         m_atomLongStyle;
      Atom                                         m_atomLongStyleEx;
      Atom                                         m_atomWmState;
      Atom                                         m_atomNetWmState;
      iptr                                         m_countReference;
      ::pointer<class window>                      m_pwindowRoot;
      ::pointer<class window>                      m_pwindowKeyboardFocus;
      ::pointer<::windowing_x11::window>          m_pwindowActive;
      ::pointer<::windowing_x11::window>          m_pwindowMouseCapture;


      display();
      ~display() override;


#ifdef _DEBUG


      virtual i64 get_ref_count();
      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
      virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;


#endif


      virtual ::Display * _get_system_default_display();


      virtual ::windowing_x11::window * _window(Window window);

      virtual ::windowing_x11::windowing * x11_windowing();

      virtual void _on_capture_changed_to(::windowing_x11::window * pwindowWithCapture);

      virtual void lock_display();

      virtual void unlock_display();

      void open() override;

      virtual ::e_status erase_window(::windowing::window * pwindow);

      virtual ::Display * Display();

      virtual ::Display * Display() const;

      virtual int Screen();

      virtual int Screen() const;

      virtual Atom atom_long_type();

      virtual Atom atom_long_style();

      virtual Atom atom_long_style_ex();

      virtual bool is_null() const;

      bool get_monitor_rectangle(index iMonitor, RECTANGLE_I32 & rectangle) override;

      bool get_workspace_rectangle(index iWorkspace, RECTANGLE_I32 & rectangle) override;

      virtual ::windowing::window * get_mouse_capture();

      virtual ::e_status release_mouse_capture();

      Atom intern_atom(const char * pszAtomName, bool bCreate);

      Atom intern_atom(::x11::enum_atom eatom, bool bCreate);

      Atom net_wm_state_atom(bool bCreate);

      virtual ::windowing_x11::window * get_keyboard_focus();

      virtual ::windowing_x11::window * _get_keyboard_focus();

      virtual ::windowing_x11::window * _get_active_window(::thread * pthread);

      virtual bool get_cursor_position(POINT_I32 * ppointCursor);

      virtual comparable_array < Window > x11_window_list();

      virtual Cursor create_alpha_cursor(const ::image *pimage, int xHotSpot, int yHotSpot);
      virtual Pixmap _x11_create_pixmap(::image_pointer pimage);
      virtual XImage * _x11_create_image(::image_pointer pimage);
      virtual Pixmap x11_create_pixmap(::image_pointer pimage);
      virtual XImage * x11_create_image(::image_pointer pimage);

      virtual bool point_is_window_origin(POINT_I32 pointHitTest, ::windowing::window * pwindowExclude, int iMargin);

      virtual Picture xrender_create_picture(::image_pointer pimage);


   };


} // namespace windowing_x11



