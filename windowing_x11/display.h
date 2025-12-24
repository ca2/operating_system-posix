// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define WINDOWING_X11_DISPLAY_MEMBER


#include "acme_windowing_x11/_atom.h"
#include "acme_windowing_x11/display.h"
//#include "nano_user_x11/event_listener.h"
//#include "nano_user_x11/display.h"
#include "aura/windowing/display.h"
#include "_x11.h"


namespace windowing_x11
{


   class CLASS_DECL_WINDOWING_X11 display :
      virtual public ::windowing::display,
   virtual public ::x11::acme::windowing::display
   {
   public:


      critical_section                             m_criticalsectionWindowMap;
      window_map                                   m_windowmap;


      Atom                                         m_atoma[::x11::e_atom_count];


      //::pointer<::x11::acme::windowing::display>        m_px11display;
      //::Display *                                  m_pdisplay;
      XVisualInfo                                  m_visualinfo;
      ::Visual *                                   m_pvisual;
      Colormap                                     m_colormap;
      //int                                          m_iScreen;
      int                                          m_iDepth;
      //Window                                       m_windowRoot;


      //Atom                                         m_atomLongType;
      //Atom                                         m_atomLongStyle;
      //Atom                                         m_atomLongStyleEx;
      //Atom                                       m_atomCardinal;
      iptr                                         m_countReference;
      ::pointer<class window>                      m_pwindowRoot;
      ::pointer<class window>                      m_pwindowKeyboardFocus;
      ::pointer<::windowing_x11::window>           m_pwindowActive;
      ::pointer<::windowing_x11::window>           m_pwindowMouseCapture;
      bool                                         m_bHasXSync;
      int                                          m_iXSyncMajor;
      int                                          m_iXSyncMinor;


      display();
      ~display() override;


#ifdef _DEBUG


      virtual long long get_ref_count();
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;
      virtual long long release() override;


#endif



      virtual ::windowing_x11::window * _window(Window window);

      virtual ::windowing_x11::windowing * x11_windowing();

      virtual void _on_capture_changed_to(::windowing_x11::window * pwindowWithCapture);

      virtual void lock_display();

      virtual void unlock_display();

      void open_display() override;

      virtual ::e_status erase_window(::windowing::window * pwindow);

      //virtual ::Display * Display();

      //virtual ::Display * Display() const;

      // virtual int Screen();
      //
      // virtual int Screen() const;
      //
      // virtual Atom atom_long_type();
      //
      // virtual Atom atom_long_style();
      //
      // virtual Atom atom_long_style_ex();

      virtual bool is_null() const;


      void destroy() override;
      ::int_size get_main_screen_size() override;

      bool get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle) override;

      bool get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle & rectangle) override;

      virtual ::windowing::window * get_mouse_capture();

      virtual ::e_status release_mouse_capture();

      ::int_point _get_mouse_cursor_position() override;

      // Atom intern_atom(const_char_pointer pszAtomName, bool bCreate);
      //
      // Atom intern_atom(::x11::enum_atom eatom, bool bCreate);
      //
      // Atom _intern_atom_unlocked(const_char_pointer pszAtomName, bool bCreate);
      //
      // Atom _intern_atom_unlocked(::x11::enum_atom eatom, bool bCreate);
      //
      // Atom net_wm_state_atom(bool bCreate);

      virtual ::windowing_x11::window * get_keyboard_focus();

      virtual ::windowing_x11::window * _get_keyboard_focus();

      virtual ::windowing_x11::window * _get_active_window(::thread * pthread);

      //virtual bool get_cursor_position(::int_point * ppointCursor);

      virtual comparable_array < Window > x11_window_list();

      virtual Cursor create_alpha_cursor(const ::image::image *pimage, int xHotSpot, int yHotSpot);
      virtual Pixmap _x11_create_pixmap(::image::image_pointer pimage);
      virtual XImage * _x11_create_image(::image::image_pointer pimage);
      virtual Pixmap x11_create_pixmap(::image::image_pointer pimage);
      virtual XImage * x11_create_image(::image::image_pointer pimage);

      virtual bool point_is_window_origin(::int_point pointHitTest, ::windowing::window * pwindowExclude, int iMargin);

      virtual Picture xrender_create_picture(::image::image_pointer pimage);


   };


} // namespace windowing_x11



