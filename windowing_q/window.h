// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "windowing_posix/window.h"
//#include "q_widget.h"
//#include "acme/operating_system/x11/_atom.h"
#include "acme/prototype/geometry2d/rectangle_array.h"
#include "acme_windowing_q/window.h"
#include "acme_windowing_q/micro_window.h"
//#include <X11/extensions/sync.h>
#include <QWidget>
//#include <gdk/gdk.h>


//#define HAVE_XSYNC 1
//
//#define _NET_WM_STATE_REMOVE        0    // remove/unset property
//#define _NET_WM_STATE_ADD           1    // add/set property
//#define _NET_WM_STATE_TOGGLE        2    // toggle property
//
//
//#define WINDOWING_X11_WINDOW_MEMBER
////using htask = pthread_t;

 enum enum_window_edge
{
       e_window_edge_none = -1,
      e_window_edge_north_west = 0,
      e_window_edge_north,
      e_window_edge_north_east,
      e_window_edge_west,
      e_window_edge_east,
      e_window_edge_south_west,
      e_window_edge_south,
      e_window_edge_south_east
    };

namespace windowing_q
{

      class window;



   class CLASS_DECL_WINDOWING_Q window :
      virtual public ::windowing_posix::window,
      virtual public ::q::acme::windowing::window
   {
   public:
//::int_point m_pointCursor2;
         //typedef struct {
         bool moving;
         bool resizing;
         enum_window_edge resize_edge;
         int start_x;
         int start_y;
         int start_width;
         int start_height;
         int start_window_x;
         int start_window_y;
         ::int_size m_sizeOnSize;
         //} ResizeData;

      //::int_point                                  m_pointPointer;
      //XWindowAttributes                            m_attr;
      //XVisualInfo                                  m_visualinfo;
      //void *                                       m_pgdkwindow;

      //bool                                         m_bPendingConfigureRequest;
      //::pointer<::windowing_q::x11data>          m_px11data;
      ::pointer<::windowing_q::display>          m_pwaylanddisplay;
      //::Window                                     m_parent;
      //Cursor                                       m_cursorLast;
      //int                                          m_iXic;
      //XIC                                          m_xic;
      //::pointer<::windowing_q::display>        m_pdisplay;
      //::Window                                     m_window;
      //::Visual                                     m_visual;
      //int                                          m_iDepth;
      //int                                        m_iScreen;
      //::pointer<::windowing::window>        m_pimpl;
      //::pointer<::message_queue>                 m_pmessagequeue;
      htask                                      m_htask;
      //Colormap                                   m_colormap;
      class ::time                                 m_timeLastMouseMove;
      //Window                                     m_parent;
      //::int_rectangle                              m_rect;
      //string                                       m_strWMClass;
      //int                                          m_iaNetWmState2[::x11::e_atom_net_wm_state_last-::x11::e_atom_net_wm_state_first+1];
      //::int_point                                m_pointCursor;
      //XSyncCounter                                 m_xsynccounterNetWmSync;
      //XSyncValue                                   m_xsyncvalueNetWmSync;
      //XSyncValue                                   m_xsyncvalueNetWmSyncPending;
      ////static oswindow_dataptra *                 s_pdataptra;
      //static::pointer< ::mutex >                 s_pmutex;
      //bool                                         m_bNetWmStateHidden;
      //bool                                         m_bNetWmStateMaximized;
      //bool                                         m_bNetWmStateFocused;
      //::comparable_array < Atom >                  m_atomaNetWmState;
      //XWindowAttributes                            m_xwindowattributes;

      //static Atom                                s_atomLongType;
      //static Atom                                s_atomLongStyle;
      //static Atom                                s_atomLongStyleEx;
      ::int_rectangle_array                        m_rectangleaRedraw;
      ::pointer<::xim::keyboard>                   m_pximkeyboard;
      //unsigned long long                                        m_uLastNetWmSyncRequest;
      ::int_rectangle                              m_rectangleXShm;
      //bool                                         m_bFirstConfigure;
      //bool                                         m_bXShmPutImagePending;
         //QWidget *m_pqwidget;
       ::array < QAction * >                       m_qactiona;

         // Create a GtkGestureClick for handling button press happenings
         //GtkGesture *m_pgtkgestureClick;
         //GtkEventController *m_pgtkeventcontrollerMotion;

         bool m_bPendingStartMove;

      window();
      //oswindow_data(::user::interaction * puibaseMessageOnlyWindow);
      //oswindow_data(const void * p);
      //oswindow_data(const LPARAM & lparam);
      //oswindow_data(const WPARAM & wparam);
      ~window() override;

void on_initialize_particle() override;
         // void _on_button_pressed(GtkGestureClick *widget, int n_press, double x, double y);
         // void _on_button_released(GtkGestureClick *widget, int n_press, double x, double y);
         // void _on_motion_notify(GtkEventControllerMotion *pcontroller, double x, double y);
         // void _on_enter_notify(GtkEventControllerMotion *pcontroller, double x, double y);
         // //bool _on_window_state(GtkWidget* widget, GdkEventWindowState* happening);
         // void _on_window_visibility_changed(GObject *object, GParamSpec *pspec);


         //virtual void _on_cairo_draw(GtkWidget *widget, cairo_t *cr);
      //void create_window(::windowing::window * pimpl) override;

      void create_window() override;


         void _create_window() override;


      void destroy() override;

      void _set_oswindow(::oswindow oswindow) override;
      ::oswindow oswindow() const override;

      void _on_mouse_press(QMouseEvent * pevent) override;
      void _on_mouse_release(QMouseEvent * pevent) override;
      void _on_mouse_motion(QMouseEvent * pevent) override;
      void _on_wheel(QWheelEvent * pevent) override;
      void _on_qimage_draw(QImage * pqimage) override;
      void _on_reposition(int x, int y) override;
      void _on_size(int cx, int cy) override;


      void _on_key_press(QKeyEvent * pevent) override;
      void _on_key_release(QKeyEvent * pevent) override;

         //void _on_window_button_pressed(GtkWidget * pwidget, const_char_pointer  pszName, GtkGestureClick * pgesture, int n_press, double x, double y);
         //void _on_window_button_released(GtkWidget * pwidget, const_char_pointer  pszName, GtkGestureClick * pgesture, int n_press, double x, double y);

//      static Atom get_window_long_atom(int nIndex);
//
//
//      inline int net_wm_state(::x11::enuid() eatom) const
//      {
//
//         return m_iaNetWmState2[eatom - ::x11::e_atom_net_wm_state_first];
//
//      }

      //bool presentation_complete() override;


//      virtual ::Display * Display();
//
//      virtual ::Display * Display() const;
//
//      virtual int Screen();
//
//      virtual int Screen() const;
//
//      virtual ::Window Window();
//
//      virtual ::Window Window() const;
//
//      virtual ::Visual * Visual();
//
//      virtual const ::Visual * Visual() const;

      //virtual ::Window root_window_raw() const;

//      virtual void unmapped_net_state_raw(Atom atom1, ...);
//
//      virtual ::e_status initialize_x11_window(::windowing_q::display * pdisplay, ::Window window, ::Visual *pvisual, int iDepth, int iScreen, Colormap colormap);

//      virtual void send_client_event(Atom atom, unsigned int numArgs, ...);
      virtual int store_name(const_char_pointer  psz);
      virtual int select_input(int iInput);
      virtual int select_all_input();
      virtual int map_window();
      virtual int unmap_window(bool bWithdraw);
      virtual void set_wm_class(const_char_pointer  psz);

      void exit_iconify() override;

      void full_screen(const ::int_rectangle & rect = {}) override;

      void exit_full_screen() override;

      void exit_zoomed() override;

      //virtual void set_user_interaction(::windowing::window * pinteraction);

      virtual void post_nc_destroy();

      virtual ::e_status set_window_icon(const ::file::path & path);

      //virtual bool is_child( WINDOWING_X11_WINDOW_MEMBER ::windowing::window * candidateChildOrDescendant); // or descendant
      //;::windowing::window * get_parent() const override;
      //virtual ::Window get_parent_handle();
      //::oswindow get_parent_oswindow() const override;

      //void _main_send(const ::procedure & procedure) override;
//      ::int_point get_mouse_cursor_host_position() override;
//      ::int_point get_mouse_cursor_absolute_position() override;


      //virtual ::Window get_parent_handle() const;

      ::windowing_q::windowing * q_windowing();
      ::windowing_q::display * q_display();

         //void _on_initialize_system_menu_button(GtkWidget * pbutton, const ::scoped_string & scopedstrAtom);

      void set_parent(::windowing::window * pwindowNewParent) override;
      //virtual ::e_status set_parent(::windowing::window * pwindowNewParent) override;
      //virtual bool get_state(long & lState);
      //bool _get_wm_state_unlocked(long & lState) override;
      bool is_iconic() override;
      bool is_window_visible() override;
//      bool _is_iconic_unlocked() override;
      bool _is_window_visible_unlocked() override;
      //void show_window(const ::e_display & edisplay, const ::user::e_activation & useractivation) override;
      //void _show_window_unlocked(const ::e_display & edisplay, const ::user::e_activation & useractivation) override;
      //virtual iptr get_window_long_ptr(int nIndex);
      //virtual iptr set_window_long_ptr(int nIndex, iptr l);
      virtual bool client_to_screen(::int_point * ppoint) override;

      bool screen_to_client(::int_point * ppoint) override;


      void _main_post(const ::procedure & procedure) override;

      void _user_send(const ::procedure & procedure) override;

      void _main_send(const ::procedure & procedure) override;
      //virtual bool set_window_pos(class::zorder zorder, int x, int y, int cx, int cy,unsigned int nFlags);
      //virtual bool _set_window_pos(class::zorder zorder, int x, int y, int cx, int cy,unsigned int nFlags);
      

      bool is_destroying() override;
      

      virtual bool bamf_set_icon();


      virtual bool set_icon(::image::image *pimage);

      //virtual int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);

      //void set_mouse_cursor(::windowing::cursor * pcursor) override;

      virtual void set_mouse_cursor2(::windowing::cursor * pcursor);

      void set_keyboard_focus() override;
      void _set_keyboard_focus_unlocked() override;

      void defer_show_system_menu(::user::mouse * pmouse) override;
      //void set_mouse_capture() override;
      //void release_mouse_capture() override;


      void set_mouse_cursor(::windowing::cursor * pcursor) override;

      void set_mouse_capture() override;
      bool has_mouse_capture() override;
      bool is_mouse_captured() override;
      void release_mouse_capture() override;


      //virtual void __activate_window(bool bNormalPriority);
      void set_active_window() override;
      void _set_active_window_unlocked() override;


      void set_foreground_window(::user::activation_token * puseractivationtoken) override;
      void _set_foreground_window_unlocked(::user::activation_token * puseractivationtoken) override;


      //bool has_mouse_capture() override;

      bool has_keyboard_focus() override;


      void _on_set_focus() override;
      void _on_kill_focus() override;


         ///virtual void _on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize* size);
         virtual void _on_display_change(::e_display edisplay);


//      //virtual Atom get_window_long_atom(int nIndex);
//      virtual void _mapped_net_state_unlocked(bool add,  WINDOWING_X11_WINDOW_MEMBER int iScreen, Atom state1, Atom state2);
//      //virtual void unmapped_net_state_raw( WINDOWING_X11_WINDOW_MEMBER ...);
//      virtual bool x11_get_window_rect(  WINDOWING_X11_WINDOW_MEMBER  ::int_rectangle * prectangle);
//      virtual bool x11_get_client_rect(  WINDOWING_X11_WINDOW_MEMBER  ::int_rectangle * prectangle);
//      //virtual oswindow set_xxxcapture( WINDOWING_X11_WINDOW_MEMBER );
//      //virtual int_bool release_xxxcapture();
//      //virtual oswindow set_keyboard_focus( WINDOWING_X11_WINDOW_MEMBER );
//      //virtual void x11_check_status(int status, unsigned long window);
//      //virtual unsigned long x11_get_long_property( WINDOWING_X11_WINDOW_MEMBER char* property_name);
//      virtual string x11_get_name( WINDOWING_X11_WINDOW_MEMBER );
//      //virtual ::e_status set_active_window();
//      virtual void upper_window_rects( WINDOWING_X11_WINDOW_MEMBER  int_rectangle_array & ra);
//      //virtual oswindow set_active_window( WINDOWING_X11_WINDOW_MEMBER );
////      virtual  WINDOWING_X11_WINDOW_MEMBER _get_if_found(Window w);
//      //virtual oswindow get_parent( WINDOWING_X11_WINDOW_MEMBER );
//      virtual ::Window _get_window_relative( WINDOWING_X11_WINDOW_MEMBER enum_relative erelative, ::Window * windowa, int numItems);
//      virtual ::windowing::window * get_window( WINDOWING_X11_WINDOW_MEMBER enum_relative erelative);

      void destroy_window() override;
      //virtual int_bool destroy_window( WINDOWING_X11_WINDOW_MEMBER );
      bool is_window() override;
      //virtual int_bool is_window( WINDOWING_X11_WINDOW_MEMBER );

      void set_window_text(const ::scoped_string & scopedstr) override;


      void set_tool_window(bool bSet) override;


      bool set_window_position(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::user::activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay) override;


      bool _set_window_position_unlocked(const class ::zorder& zorder, int x, int y, int cx, int cy, const ::user::activation& useractivation, bool bNoZorder, bool bNoMove, bool bNoSize, ::e_display edisplay) override;
      bool _configure_window_unlocked(const class ::zorder& zorder, const ::user::activation& useractivation, bool bNoZorder, ::e_display edisplay) override;
      bool _strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize) override;


//      virtual comparable_array < Atom > _wm_get_list_unlocked( WINDOWING_X11_WINDOW_MEMBER Atom atomList);
//      virtual ::comparable_array < Atom > _get_net_wm_state_unlocked();
//      virtual int wm_test_state( WINDOWING_X11_WINDOW_MEMBER const_char_pointer  pszNetStateFlag);
//      virtual int _wm_test_state_unlocked( WINDOWING_X11_WINDOW_MEMBER const_char_pointer  pszNetStateFlag);
//      virtual int _wm_test_list_unlocked( WINDOWING_X11_WINDOW_MEMBER Atom atomList, Atom atomFlag);
//      virtual bool _wm_add_remove_list_unlocked( WINDOWING_X11_WINDOW_MEMBER Atom atomList, Atom atomFlag, bool bSet);
//      virtual void _wm_add_remove_state_mapped_unlocked( WINDOWING_X11_WINDOW_MEMBER ::x11::enuid() eatomNetWmState, bool bSet);
//      virtual void wm_add_remove_state_mapped( WINDOWING_X11_WINDOW_MEMBER ::x11::enuid() eatomNetWmState, bool bSet);
//      virtual void _wm_add_remove_state_unmapped_unlocked( WINDOWING_X11_WINDOW_MEMBER ::x11::enuid() eatomNetWmState, bool bSet);
//      virtual void wm_add_remove_state_unmapped( WINDOWING_X11_WINDOW_MEMBER ::x11::enuid() eatomNetWmState, bool bSet);
//      virtual void _wm_add_remove_state_unlocked( WINDOWING_X11_WINDOW_MEMBER ::x11::enuid() eatomNetWmState, bool bSet);
//      virtual void wm_add_remove_state( WINDOWING_X11_WINDOW_MEMBER ::x11::enuid() eatomNetWmState, bool bSet);
//      virtual void _wm_state_clear_unlocked( WINDOWING_X11_WINDOW_MEMBER bool bSet);
//      virtual void _wm_state_below_unlocked( WINDOWING_X11_WINDOW_MEMBER bool bSet);
//      virtual void _wm_state_above_unlocked( WINDOWING_X11_WINDOW_MEMBER bool bSet);
//      virtual void _wm_state_hidden_unlocked( WINDOWING_X11_WINDOW_MEMBER bool bSet);
//      virtual void wm_state_above( WINDOWING_X11_WINDOW_MEMBER bool bSet);
//      virtual void wm_state_below( WINDOWING_X11_WINDOW_MEMBER bool bSet);
//      virtual void wm_state_hidden( WINDOWING_X11_WINDOW_MEMBER bool bSet);
//      virtual void wm_toolwindow( WINDOWING_X11_WINDOW_MEMBER bool bToolWindow);
//      virtual void wm_normalwindow();
//      virtual void wm_hidden_state( WINDOWING_X11_WINDOW_MEMBER bool bHidden);
//      virtual void wm_desktopwindow( WINDOWING_X11_WINDOW_MEMBER bool bDesktopWindow);
//      virtual void wm_centerwindow( WINDOWING_X11_WINDOW_MEMBER bool bCenterWindow);
//      virtual void wm_splashwindow( WINDOWING_X11_WINDOW_MEMBER bool bCenterWindow);
//      virtual void wm_dockwindow( WINDOWING_X11_WINDOW_MEMBER bool bDockWindow);
//      virtual void wm_nodecorations( WINDOWING_X11_WINDOW_MEMBER int bMap);
//      virtual void _wm_nodecorations( WINDOWING_X11_WINDOW_MEMBER int bMap);
//      virtual int_bool _wm_is_window_visible_unlocked( WINDOWING_X11_WINDOW_MEMBER);
//      virtual void wm_iconify_window( WINDOWING_X11_WINDOW_MEMBER );
//      //virtual int_bool IsWindowVisibleRaw( WINDOWING_X11_WINDOW_MEMBER);
//      //virtual int_bool IsWindowVisibleRaw(oswindow w);
////      virtual Atom * wm_get_list_raw( WINDOWING_X11_WINDOW_MEMBER Atom atomList, unsigned long int * pnum_items);
////      virtual int wm_test_list_raw( WINDOWING_X11_WINDOW_MEMBER Atom atomList, Atom atomFlag);
////      virtual int wm_test_state_raw( WINDOWING_X11_WINDOW_MEMBER const_char_pointer  pszNetStateFlag);
////      virtual int wm_test_state( WINDOWING_X11_WINDOW_MEMBER const_char_pointer  pszNetStateFlag);
////      virtual bool wm_add_remove_list_raw( WINDOWING_X11_WINDOW_MEMBER Atom atomList, Atom atomFlag, bool bSet);


//      virtual ::e_status x11_post_message(MESSAGE & msg);
//      virtual ::e_status post_ui_message(const MESSAGE & message);
      //virtual bool x11_process_event(osdisplay_data * pdisplaydata, XEvent * pevent, XGenericEventCookie *cookie);
      //virtual ::e_status set_window_position( WINDOWING_X11_WINDOW_MEMBER const ::zorder & zorder, int x, int y, int cx, int cy, unsigned int nFlags);
      virtual ::e_status window_rectangle( ::int_rectangle * prectangle);
      virtual ::e_status rectangle(::int_rectangle * prectangle);
      //virtual ::e_status wm_full_screen( WINDOWING_X11_WINDOW_MEMBER const ::int_rectangle & rectangle);

      //virtual ::e_status x11_store_name(const_char_pointer  pszName);
      //virtual ::e_status set_foreground_window();
      //virtual ::e_status set_active_window();
      //virtual void wm_toolwindow( WINDOWING_X11_WINDOW_MEMBER bool bToolWindow);
      //virtual void wm_state_hidden( WINDOWING_X11_WINDOW_MEMBER bool bSet);
      //virtual void wm_state_hidden_raw( WINDOWING_X11_WINDOW_MEMBER bool bSet);
//      virtual ::e_status mq_remove_window_from_all_queues( WINDOWING_X11_WINDOW_MEMBER );

      void __update_graphics_buffer() override;
      //void _window_request_presentation_locked() override;

      //void _on_configure_notify_unlocked(const ::int_rectangle & rectangle) override;


      bool is_active_window() override;


      void bring_to_front() override;


      void window_update_screen() override;


      virtual void _on_end_paint();
      //virtual void _enable_net_wm_sync();


//      virtual void __map();
//
//      virtual void __unmap();
//
//
      // virtual void __handle_pointer_enter(::wl_pointer * pwlpointer);
      // virtual void __handle_pointer_motion(::wl_pointer * pwlpointer, unsigned int millis);
      // virtual void __handle_pointer_leave(::wl_pointer * pwlpointer, ::windowing_q::window * pwaylandwindowLeave);
      //
      // virtual void __handle_pointer_button(::wl_pointer * pwlpointer, unsigned int linux_button, unsigned int pressed, unsigned int millis);
//
//
//      virtual void __defer_update_wayland_buffer();
//
//      virtual void __handle_xdg_surface_configure(unsigned int serial);
//
      //virtual void __handle_xdg_toplevel_configure(int width, int height, ::wl_array * pwlarrayState);
//
//      virtual void __defer_xdg_surface_ack_configure();


      //void _on_simple_key_message(::user::e_key ekey, ::enum_message emesssage) override;
      //void _on_text_composition(const ::scoped_string & scopedstrText) override;

      bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

      bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;

      void final_mouse_message_handling(message::mouse* pmouse) override;

      void _on_windowing_close_window() override;

         //GMenu* _create_system_menu();
         //virtual void _on_window_simple_action(const_char_pointer  pszActionName);

       ///virtual void _on_a_system_menu_item_action_triggered(::operating_system::a_system_menu_item * pitem);

      //void __handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_array *pwlarrayKeys) override;
      //void __handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial) override;
//      virtual void __handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
//      virtual void __handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);
      //::particle * get_interface_client_particle() override; // m_pwindow->m_puserinteraction
      //virtual void set_window_width(int iWidth) = 0; // m_sizeWindow.cx()
      //virtual void set_window_height(int iHeight) = 0; // m_sizeWindow.cy()
      //virtual ::int_size get_window_size() = 0; // m_sizeWindow
      // virtual void set_interface_client_size(const ::int_size & sizeWindow) override; // set_size
      //
      // virtual bool is_window_stored_iconic() override; // m_pwindow->m_puserinteraction->const_layout().window().display() == e_display_iconic
      // virtual void window_maximize() override; // m_pwindow->m_puserinteraction->display(::e_display_zoomed);
      // virtual void window_full_screen() override; // m_pwindow->m_puserinteraction->display(::e_display_full_screen);
      // virtual void window_restore() override; // m_pwindow->m_puserinteraction->display(::e_display_normal);

         void window_restore() override;
         void window_minimize() override;
         void window_maximize() override;

         bool is_window_zoomed() override;

         virtual void _set_cursor_from_name(const ::scoped_string & scopedstr);


         //virtual bool _unlocked_gtk_is_x11();
         //virtual bool _unlocked_gtk_is_wayland();
         virtual ::int_rectangle _unlocked_defer_get_window_rectangle();
         virtual void _unlocked_defer_set_window_position(const ::int_point & point);
         virtual void _unlocked_defer_set_window_position(const ::int_point & point, const ::int_size & size);
         virtual void _unlocked_defer_set_window_size(const ::int_size & size);
         //virtual void _unlocked_defer_start_resize(enum_window_edge eedge, GtkGestureClick * pclick, double x, double y);


      void _on_text(const scoped_string& scopedstr) override;

      void show_task(bool bShow) override;



   };



} // namespace windowing_q



