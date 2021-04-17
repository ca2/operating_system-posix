// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define WINDOWING_X11_DISPLAY_MEMBER


namespace windowing_x11
{


   class CLASS_DECL_WINDOWING_X11 display :
      virtual public ::windowing::display
   {
   public:


      critical_section                             m_criticalsectionWindowMap;
      window_map                                   m_windowmap;


      ::Display *                                  m_pdisplay;
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
      Atom                                         m_atoma[x_window::e_atom_count];
      iptr                                         m_countReference;
      __pointer(class window)                   m_pwindowRoot;
      __pointer(class window)                   m_pwindowKeyboardFocus;
      //array < MESSAGE >                          m_messsageaInput;
      //::mutex *                                  m_pmutexInput;

      //static osdisplay_dataptra *                s_pdataptra;
      //static ::mutex *                           s_pmutex;
      __pointer(::windowing_x11::window)      m_pwindowActive;
      __pointer(::windowing_x11::window)       m_pwindowMouseCapture;


      display();
      virtual ~display();


#ifdef DEBUG


      virtual i64 get_ref_count();
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 release(OBJ_REF_DBG_PARAMS);


#endif

      virtual ::windowing_x11::window * _window(Window window);

      inline ::windowing_x11::windowing * x11_windowing() { return (::windowing_x11::windowing *) m_pwindowing->m_pWindowing; }

      virtual void _on_capture_changed_to(::windowing_x11::window * pwindowWithCapture);

      virtual void lock_display();

      virtual void unlock_display();

      virtual ::e_status open() override;

      virtual ::e_status remove_window(::windowing::window * pwindow);


      virtual ::Display * Display();

      virtual ::Display * Display() const;

      virtual int Screen();

      virtual int Screen() const;

//      virtual ::Visual * Visual();
//
//      virtual ::Visual * Visual() const;

      virtual Atom atom_long_type();

      virtual Atom atom_long_style();

      virtual Atom atom_long_style_ex();

      virtual bool is_null() const;


      virtual bool get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle);


      virtual bool get_workspace_rectangle(index iWorkspace, RECTANGLE_I32 * prectangle);


      virtual ::e_status release_mouse_capture();



      Atom get_window_long_atom(i32 nIndex);

      Atom intern_atom(const char * pszAtomName, bool bCreate);

      Atom intern_atom(x_window::enum_atom eatom, bool bCreate);

      Atom net_wm_state_atom(bool bCreate);

      //virtual ::windowing::window * default_root_window() override;


      virtual ::windowing_x11::window * get_keyboard_focus();

      virtual ::windowing_x11::window * _get_keyboard_focus();


      virtual ::windowing_x11::window * _get_active_window(::thread * pthread);


      //virtual bool x11_window_list(array < Window > & windowa);
      //virtual oswindow get_focus();

      virtual bool get_cursor_position(POINT_I32 * ppointCursor);
      //virtual oswindow _x11_get_active_window(WINDOWING_X11_DISPLAY_MEMBER);
      //virtual oswindow _x11_get_active_window();
      virtual comparable_array < Window > x11_window_list();

      virtual Cursor create_alpha_cursor(const ::image *pimage, int xHotSpot, int yHotSpot);
      virtual Pixmap _x11_create_pixmap(::image_pointer pimage);
      virtual XImage * _x11_create_image(::image_pointer pimage);
      virtual Pixmap x11_create_pixmap(::image_pointer pimage);
      virtual XImage * x11_create_image(::image_pointer pimage);

      virtual bool point_is_window_origin(POINT_I32 pointHitTest, ::windowing::window * pwindowExclude, int iMargin);


      //virtual Atom intern_atom(const char * pszAtomName, bool bCreate);
      //virtual Atom intern_atom(enum_net_wm_state state, bool bCreate);

      virtual Picture xrender_create_picture(::image_pointer pimage);
      //virtual Picture xrender_create_picture(::image_pointer pimage);



   };


//   typedef osdisplay_data *osdisplay;




//class osdisplay_dataptra :
//   public ::raw_array<osdisplay_data *>
//{
//public:
//
//   virtual ~osdisplay_dataptra()
//   {
//
//      remove_all();
//
//   }
//
//   void remove_all()
//   {
//
//      for (auto point : *this)
//      {
//
//         delete point;
//
//      }
//
//      raw_array<osdisplay_data *>::remove_all();
//   }
//
//};


} // namespace windowing_x11



