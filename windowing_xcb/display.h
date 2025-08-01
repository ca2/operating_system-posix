// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define WINDOWING_X11_DISPLAY_MEMBER


#include "acme/exception/status.h"
#include "acme/prototype/collection/int_map.h"
#include "aura/windowing/display.h"
#include "windowing_system_x11/_atom.h"
#include <xcb/xcb.h>
#include <xcb/xcb_image.h>
#include <xcb/render.h>
#include <X11/Xlib.h>


namespace windowing_xcb
{



   class CLASS_DECL_WINDOWING_XCB display :
      virtual public ::windowing::display
   {
   public:


      critical_section                                         m_criticalsectionWindowMap;
      ::pointer<::xcb::acme::windowing::display>                    m_pxcbdisplay;
      window_map                                               m_windowmap;
      int_map < xcb_cursor_t>                                  m_mapGlyphCursor;
      xcb_atom_t                                               m_atoma[::x11::e_atom_count];

      xcb_font_t                                               m_pfontCursor;
      int                                                      m_iXcbShmCompletionTypeId;
      Atom                                                     m_atomNetWmStateFocused;
      Atom                                                     m_atomNetWmStateHidden;
      Atom                                                     m_atomNetWmStateMaximizedHorz;
      Atom                                                     m_atomNetWmStateMaximizedVert;
      Atom                                                     m_atomWmProtocols;
      Atom                                                     m_atomNetWmSyncRequest;
      Atom                                                     m_atomNetWmSyncRequestCounter;
      Atom                                                     m_atomNetWmState;
      Atom                                                     m_atomWmState;
      Display *                                                m_pX11Display;
      //xcb_connection_t *                                       m_pconnection;
      map < xcb_atom_t, ::string >                             m_mapAtomName;
      bool                                                     m_bHasXSync;

      ::pointer<class window>                                  m_pwindowRoot;
      ::pointer<class window>                                  m_pwindowKeyboardFocus;

      ::pointer<::windowing_xcb::window>                       m_pwindowActive;


      display();
      ~display() override;


#ifdef _DEBUG


      virtual long long get_ref_count();
      long long increment_reference_count() override;
      long long decrement_reference_count() override;
      long long release() override;


#endif


      virtual ::windowing_xcb::window * _window(xcb_window_t window);

      inline ::windowing_xcb::windowing * xcb_windowing();

      virtual void lock_display();

      virtual void unlock_display();

      void open_display() override;

      virtual ::e_status erase_window(::windowing::window * pwindow);

      virtual xcb_atom_t intern_atom(const_char_pointer pszAtomName, bool bCreate = true);

      virtual xcb_atom_t intern_atom(::x11::enuid() eatom, bool bCreate = true);

      virtual ::string atom_name(xcb_atom_t atom);
      virtual ::string _atom_name(xcb_atom_t atom);

      virtual xcb_cursor_t _create_font_cursor (uint16_t glyph);

      virtual xcb_connection_t * xcb_connection();

      virtual xcb_connection_t * xcb_connection() const;

      virtual bool is_null() const;

      bool get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle & rectangle) override;

      bool get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle & rectangle) override;

      //virtual ::e_status release_mouse_capture();

      virtual ::windowing_xcb::window * get_keyboard_focus();

      virtual ::windowing_xcb::window * _get_keyboard_focus();

      virtual ::windowing_xcb::window * _get_active_window(::thread * pthread);

      //virtual bool get_cursor_position(::int_point * ppointCursor);

      ::int_point _get_mouse_cursor_position() override;




      virtual bool point_is_window_origin(::int_point pointHitTest, ::windowing::window * pwindowExclude, int iMargin);


      virtual ::e_status _request_check(xcb_void_cookie_t cookie);


      //virtual ::e_status _send_client_event(xcb_window_t window, xcb_atom_t atom, unsigned int numArgs, ...);
      //virtual ::e_status _send_client_event_v(xcb_window_t window, xcb_atom_t atom, unsigned int numArgs, va_list args);


      virtual xcb_cursor_t _create_alpha_cursor(const ::image::image *pimage, int xHotSpot, int yHotSpot);
      virtual xcb_pixmap_t _create_pixmap(const ::image::image *pimage);
      virtual xcb_image_t * _create_image(const ::image::image *pimage);
      virtual xcb_render_picture_t _create_picture(const ::image::image *pimage);


      virtual comparable_raw_array < xcb_window_t > _window_enumerate();


      virtual comparable_array < xcb_atom_t > _window_get_atom_array(xcb_window_t window, xcb_atom_t property);
      virtual bool _window_has_atom_list_atom(xcb_window_t window, xcb_atom_t propertyList, xcb_atom_t propertyItem);
      virtual string _window_get_string_property(xcb_window_t window, xcb_atom_t property);
      virtual long _window_get_long_property(xcb_window_t window, xcb_atom_t property, xcb_atom_t type);
      virtual string _window_get_name(xcb_window_t window);
      virtual status < xcb_get_window_attributes_reply_t > _window_get_window_attributes(xcb_window_t window);
      virtual status < xcb_get_geometry_reply_t > _window_get_geometry(xcb_window_t window);
      virtual ::int_rectangle _window_get_frame_extents(xcb_window_t window);
      virtual ::e_status _window_get_window_rectangle(xcb_window_t window, ::int_rectangle * prectangle);
      virtual ::e_status _window_get_client_rectangle(xcb_window_t window, ::int_rectangle * prectangle);


      //virtual xcb_font_t _create_font_cursor(uint16_t glyph);




   };


} // namespace windowing_xcb



