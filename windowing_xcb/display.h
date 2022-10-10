// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define WINDOWING_X11_DISPLAY_MEMBER


#include "acme/operating_system/xcb/nano/_nano.h"
#include "aura/windowing/display.h"


namespace windowing_xcb
{



   class CLASS_DECL_WINDOWING_XCB display :
      virtual public ::windowing::display
   {
   public:


      critical_section                                         m_criticalsectionWindowMap;
      ::pointer<::xcb::display>                               m_pxcbdisplay;
      window_map                                               m_windowmap;
      i32_map < xcb_cursor_t>                                  m_mapGlyphCursor;
      xcb_atom_t                                               m_atoma[::x11::e_atom_count];

      xcb_font_t                                               m_pfontCursor;

      Display *                                                m_pX11Display;
      //xcb_connection_t *                                       m_pconnection;

      ::pointer<class window>                                  m_pwindowRoot;
      ::pointer<class window>                                  m_pwindowKeyboardFocus;

      ::pointer<::windowing_xcb::window>                      m_pwindowActive;
      ::pointer<::windowing_xcb::window>                      m_pwindowMouseCapture;


      display();
      ~display() override;


#ifdef _DEBUG


      virtual i64 get_ref_count();
      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);
      virtual i64 release(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS);


#endif


      virtual ::windowing_xcb::window * _window(xcb_window_t window);

      inline ::windowing_xcb::windowing * xcb_windowing();

      virtual void _on_capture_changed_to(::windowing_xcb::window * pwindowWithCapture);

      virtual void lock_display();

      virtual void unlock_display();

      void open() override;

      virtual ::e_status erase_window(::windowing::window * pwindow);

      virtual xcb_atom_t intern_atom(const char * pszAtomName, bool bCreate = true);

      virtual xcb_atom_t intern_atom(::x11::enum_atom eatom, bool bCreate = true);

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


      //virtual ::e_status _send_client_event(xcb_window_t window, xcb_atom_t atom, unsigned int numArgs, ...);
      //virtual ::e_status _send_client_event_v(xcb_window_t window, xcb_atom_t atom, unsigned int numArgs, va_list args);


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
      virtual status < xcb_get_window_attributes_reply_t > _window_get_window_attributes(xcb_window_t window);
      virtual status < xcb_get_geometry_reply_t > _window_get_geometry(xcb_window_t window);
      virtual ::rectangle_i32 _window_get_frame_extents(xcb_window_t window);
      virtual ::e_status _window_get_window_rectangle(xcb_window_t window, RECTANGLE_I32 * prectangle);
      virtual ::e_status _window_get_client_rectangle(xcb_window_t window, RECTANGLE_I32 * prectangle);


      //virtual xcb_font_t _create_font_cursor(uint16_t glyph);


   };


} // namespace windowing_xcb



