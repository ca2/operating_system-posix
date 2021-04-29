// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define WINDOWING_X11_DISPLAY_MEMBER


namespace windowing_xcb
{



   class CLASS_DECL_WINDOWING_XCB display :
      virtual public ::windowing::display
   {
   public:


      critical_section                                         m_criticalsectionWindowMap;
      window_map                                               m_windowmap;
      acme::malloc < xcb_render_query_pict_formats_reply_t * > m_prender_query_pict_formats_reply2;
      visual_pictformat_map                                    m_mapVisualPictFormat;
      visual_depth_map                                         m_mapVisualDepth;
      //map < xcb_visualid_t, FbConfigInfo * >                 m_mapVisualFbConfig;
      pictformat_info_map                                      m_mapFormatInfo;
      i32_map < xcb_cursor_t>                                  m_mapGlyphCursor;
      xcb_atom_t                                               m_atoma[x_window::e_atom_count];

      xcb_font_t                                               m_fontCursor;

      xcb_depth_t *                                            m_pdepth;
      xcb_visualtype_t *                                       m_pvisualtype;
      Display *                                                m_pX11Display;
      xcb_connection_t *                                       m_pconnection;
      xcb_screen_t *                                           m_pscreen;
      xcb_colormap_t                                           m_colormap;
      xcb_window_t                                             m_windowRoot;

      __pointer(class window)                                  m_pwindowRoot;
      __pointer(class window)                                  m_pwindowKeyboardFocus;

      __pointer(::windowing_xcb::window)                       m_pwindowActive;
      __pointer(::windowing_xcb::window)                       m_pwindowMouseCapture;


      display();
      virtual ~display();


#ifdef DEBUG


      virtual i64 get_ref_count();
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);
      virtual i64 release(OBJ_REF_DBG_PARAMS);


#endif


      virtual ::windowing_xcb::window * _window(xcb_window_t window);

      inline ::windowing_xcb::windowing * xcb_windowing() { return (::windowing_xcb::windowing *) m_pwindowing->m_pWindowing; }

      virtual void _on_capture_changed_to(::windowing_xcb::window * pwindowWithCapture);

      virtual void lock_display();

      virtual void unlock_display();

      virtual ::e_status open() override;

      virtual ::e_status remove_window(::windowing::window * pwindow);

      virtual xcb_atom_t intern_atom(const char * pszAtomName, bool bCreate = true);

      inline xcb_atom_t atom(x_window::enum_atom eatom) { return m_atoma[eatom]; }

      virtual xcb_cursor_t _create_font_cursor (uint16_t glyph);

      virtual xcb_connection_t * xcb_connection();

      virtual xcb_connection_t * xcb_connection() const;

      virtual bool is_null() const;

      virtual bool get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle);

      virtual bool get_workspace_rectangle(index iWorkspace, RECTANGLE_I32 * prectangle);

      virtual ::e_status release_mouse_capture();

      virtual ::windowing_xcb::window * get_keyboard_focus();

      virtual ::windowing_xcb::window * _get_keyboard_focus();

      virtual ::windowing_xcb::window * _get_active_window(::thread * pthread);

      virtual bool get_cursor_position(POINT_I32 * ppointCursor);


      virtual bool point_is_window_origin(POINT_I32 pointHitTest, ::windowing::window * pwindowExclude, int iMargin);


      virtual ::e_status _request_check(xcb_void_cookie_t cookie);


      virtual ::e_status _send_client_event(xcb_window_t window, xcb_atom_t atom, unsigned int numArgs, ...);
      virtual ::e_status _send_client_event_v(xcb_window_t window, xcb_atom_t atom, unsigned int numArgs, va_list args);


      virtual xcb_cursor_t _create_alpha_cursor(const ::image *pimage, int xHotSpot, int yHotSpot);
      virtual xcb_pixmap_t _create_pixmap(const ::image * pimage);
      virtual xcb_image_t * _create_image(const ::image * pimage);
      virtual xcb_render_picture_t _create_picture(const ::image * pimage);


      virtual comparable_raw_array < xcb_window_t > _window_enumerate();


      virtual comparable_array < xcb_atom_t > _window_get_atom_array(xcb_window_t window, xcb_atom_t property);
      virtual bool _window_has_atom_list_atom(xcb_window_t window, xcb_atom_t propertyList, xcb_atom_t propertyItem);
      virtual string _window_get_string_property(xcb_window_t window, xcb_atom_t property);
      virtual long _window_get_long_property(xcb_window_t window, xcb_atom_t property, xcb_atom_t type);
      virtual string _window_get_name(xcb_window_t window);
      virtual status < xcb_get_geometry_reply_t > _window_get_geometry(xcb_window_t window);
      virtual ::e_status _window_get_window_rectangle(xcb_window_t window, RECTANGLE_I32 * prectangle);
      virtual ::e_status _window_get_client_rectangle(xcb_window_t window, RECTANGLE_I32 * prectangle);


      //virtual xcb_font_t _create_font_cursor(uint16_t glyph);


   };


} // namespace windowing_xcb



