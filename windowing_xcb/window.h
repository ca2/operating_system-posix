// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define _NET_WM_STATE_REMOVE        0    // erase/unset property
#define _NET_WM_STATE_ADD           1    // add/set property
#define _NET_WM_STATE_TOGGLE        2    // toggle property


#define WINDOWING_X11_WINDOW_MEMBER


struct xkb_context;
struct xkb_keymap;
struct xkb_state;


#include "windowing_posix/window.h"
#include "windowing_system_x11/_atom.h"
#include <X11/XKBlib.h>
#include <xcb/sync.h>


namespace windowing_xcb
{


   class CLASS_DECL_WINDOWING_XCB window :
      virtual public ::windowing_posix::window
   {
   public:


      xkb_context *                                m_pkeyboarcontext;
      int                                          m_iKeyboardX11DeviceId;
      xkb_keymap *                                 m_pkeymap;
      xkb_state *                                  m_pkeystate;


      xcb_get_window_attributes_reply_t            m_attributes;
      xcb_get_geometry_reply_t                     m_geometry;

      xcb_sync_counter_t                           m_xsynccounterNetWmSync;
      xcb_sync_int64_t                             m_xsyncintNetWmSync;
      xcb_sync_int64_t                             m_xsyncintNetWmSyncPending;
      xcb_window_t                                 m_parent;
      xcb_cursor_t                                 m_cursorLast;
      xcb_window_t                                 m_window;
      xcb_visualid_t                               m_visualid;
      htask_t                                      m_htask;
      //class ::time                                 m_timeLastMouseMove;
      //::point_i32                                  m_pointMouseCursor;

      bool                                         m_bNetWmStateHidden;
      bool                                         m_bNetWmStateMaximized;
      bool                                         m_bNetWmStateFocused;


      window();
      ~window() override;


      //void create_window(::windowing::window * pimpl) override;

      void create_window() override;


      virtual xcb_connection_t * xcb_connection();
      virtual xcb_connection_t * xcb_connection() const;


      virtual xcb_window_t xcb_window();
      virtual xcb_window_t xcb_window() const;

      virtual void _enable_net_wm_sync();

      ::windowing_xcb::windowing * xcb_windowing() const;
      ::windowing_xcb::display * xcb_display() const;


      ::e_status get_wm_hints(void * p_xcb_icccm_wm_hints_t);


      virtual ::e_status initialize_xcb_window(::windowing_xcb::display * pdisplay, xcb_window_t window, int iDepth, xcb_colormap_t colormap);


      void destroy_window() override;
      bool is_window() override;


      void set_window_text(const ::scoped_string & scopedstrText) override;


      bool set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay) override;

      bool _set_window_position_unlocked(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::e_activation& eactivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay) override;

      bool _configure_window_unlocked(const class ::zorder& zorder, const ::e_activation& eactivation, bool bNoZorder, ::e_display edisplay) override;

      bool _strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize) override;

      virtual int_bool IsWindowVisibleRaw();

      virtual void set_user_interaction(::windowing::window * pinteraction);

      virtual void post_nc_destroy();


      virtual ::e_status set_bamf_desktop_file(const ::file::path & path);


      virtual bool is_child( ::windowing::window * candidateChildOrDescendant); // or descendant
      ::windowing::window * get_parent() const override;
      ::oswindow get_parent_oswindow() const override;


      bool is_iconic() override;
      bool is_window_visible() override;


      //void _configure_window_unlocked(const class ::zorder& zorder, const ::e_activation& eactivation, bool bNoZorder, ::e_display edisplay) override;

      void exit_iconify()override;
      void full_screen(const ::rectangle_i32 & rect = {})override;
      void exit_full_screen()override;
      void exit_zoomed() override;


      void set_parent(::windowing::window * pwindowNewParent) override;

      virtual long _get_wm_state();

      bool client_to_screen(::point_i32 * ppoint) override;

      bool screen_to_client(::point_i32 * ppoint) override;

      bool is_destroying() override;
      
      virtual ::e_status bamf_set_icon();

      virtual bool set_icon(::image::image *pimage);

      void set_mouse_cursor(::windowing::cursor * pcursor) override;

      virtual ::e_status set_mouse_cursor2(::windowing::cursor * pcursor);

      //::point_i32 get_mouse_cursor_position() override;

      void set_keyboard_focus() override;
      void set_mouse_capture() override;
      void set_active_window() override;


      virtual void _set_mouse_capture_unlocked();

      virtual ::string atom_name(xcb_atom_t atom);

      virtual void _set_keyboard_focus(xcb_window_t window);


      void set_foreground_window() override;


      bool has_mouse_capture() const override;

      bool has_keyboard_focus() const override;


      virtual rectangle_i32_array upper_window_rects();



      virtual ::e_status _get_window_rectangle(::rectangle_i32 * prectangle);
      virtual ::e_status _get_client_rectangle(::rectangle_i32 * prectangle);
      virtual xcb_window_t _get_window_relative(enum_relative erelative, xcb_window_t * windowa, int numItems);
      virtual ::windowing::window * get_window(enum_relative erelative);


      virtual ::e_status _unmapped_net_state_raw(xcb_atom_t atom1, ...);
      virtual ::e_status _mapped_net_state_raw(bool add,  xcb_atom_t state1, xcb_atom_t state2);

      virtual string _get_wm_name();


      virtual comparable_array < xcb_atom_t > _list_atom(xcb_atom_t atomList);
      virtual void _get_net_wm_state_unlocked(bool & bNetWmStateHidden, bool & bNetWmStateMaximized, bool & bNetWmStateFocused);
      virtual bool _has_net_wm_state(xcb_atom_t propertyItem);
      virtual bool _list_has_atom(xcb_atom_t propertyList, xcb_atom_t propertyItem);
      virtual ::e_status _list_add_atom(xcb_atom_t atomList, xcb_atom_t atomFlag);
      virtual ::e_status _list_erase_atom(xcb_atom_t atomList, xcb_atom_t atomFlag);
      virtual ::e_status _mapped_add_net_wm_state(::x11::enum_atom eatomNetWmState);
      virtual ::e_status _mapped_erase_net_wm_state(::x11::enum_atom eatomNetWmState);
      virtual ::e_status _unmapped_add_net_wm_state(::x11::enum_atom eatomNetWmState);
      virtual ::e_status _unmapped_erase_net_wm_state(::x11::enum_atom eatomNetWmState);
      virtual ::e_status _add_net_wm_state(::x11::enum_atom eatomNetWmState);
      virtual ::e_status _erase_net_wm_state(::x11::enum_atom eatomNetWmState);
      virtual ::e_status _clear_net_wm_state();
      virtual ::e_status _add_net_wm_state_below();
      virtual ::e_status _add_net_wm_state_above();
      virtual ::e_status _add_net_wm_state_hidden();
      virtual ::e_status _erase_net_wm_state_below();
      virtual ::e_status _erase_net_wm_state_above();
      virtual ::e_status _erase_net_wm_state_hidden();
      virtual ::e_status _set_tool_window(bool bToolWindow = true);
      virtual ::e_status _set_normal_window();
      virtual ::e_status _set_hidden_state(bool bHidden);
      virtual ::e_status _set_desktop_window(bool bDesktopWindow = true);
      virtual ::e_status _set_center_window(bool bCenterWindow = true);
      virtual ::e_status _set_splash_window(bool bSplashWindow = true);
      virtual ::e_status _set_dock_window(bool bDockWindow = true);
      virtual ::e_status _set_nodecorations(int bMap);
      virtual ::e_status _set_iconify_window();
      virtual ::e_status _raise_window();
      virtual ::e_status _lower_window();


      void bring_to_front() override;


      void set_tool_window(bool bSet) override;


      void xcb_post_message(MESSAGE & msg);
      void post_ui_message(const MESSAGE & message);
      //virtual ::e_status window_rectangle(::rectangle_i32 * prectangle);
      //virtual ::e_status this->rectangle(::rectangle_i32 * prectangle);
      void mq_erase_window_from_all_queues( );


      void __update_graphics_buffer() override;
      //void _window_request_presentation_locked() override;


      virtual ::e_status defer_update_keyboard_context();
      virtual int keycode_to_keysym(xcb_keycode_t code);
      virtual void release_keyboard();
      virtual string _on_key_down(xcb_keycode_t code, ::u16 state, KeySym * pkeysym);


      static xcb_atom_t _get_window_long_atom(int nIndex);


      virtual ::e_status _change_atom_atom(xcb_atom_t atomWindowType, xcb_atom_t atomWindowTypeValue);
      virtual ::e_status _change_property(xcb_atom_t property, xcb_atom_t type, int mode, int format, int nelements, const void * data);
      virtual ::e_status _delete_property(xcb_atom_t property);
      virtual ::e_status _replace_string_property(xcb_atom_t property, const ::block & block);
      virtual ::e_status _request_check(xcb_void_cookie_t cookie);


      virtual ::e_status _send_client_event(xcb_atom_t atom, unsigned int numArgs, ...);
      virtual ::e_status _store_name(const char * psz);
      virtual ::e_status _select_input(int iInput);
      virtual ::e_status _select_all_input();
      virtual ::e_status _map_window();
      //virtual ::e_status _unmap_window(bool bWithdraw);
      virtual ::e_status _unmap_window();
      virtual ::e_status _withdraw_window();
      virtual ::e_status _destroy_window();


      virtual ::e_status _set_class_hint(const char * pszName, const char * pszClass);
      virtual ::e_status _get_window_attributes();
      virtual ::e_status _get_geometry();
      virtual ::e_status _move_resize(int x, int y, int cx, int cy);
      virtual ::e_status _move(int x, int y);
      virtual ::e_status _resize(int cx, int cy);

      virtual ::e_status _move_resize_unlocked(int x, int y, int cx, int cy);
      virtual ::e_status _move_unlocked(int x, int y);
      virtual ::e_status _resize_unlocked(int cx, int cy);


      void window_update_screen() override;


      virtual void _on_end_paint();


//      bool _strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize) override;


   };


} // namespace windowing_xcb



