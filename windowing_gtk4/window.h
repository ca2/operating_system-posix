// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "windowing_posix/window.h"
#include "gtk4_widget.h"
#include "acme/prototype/geometry2d/rectangle_array.h"
#include "acme_windowing_gtk4/window.h"


namespace windowing_gtk4
{


   class window;


   class CLASS_DECL_WINDOWING_GTK4 window :
      virtual public ::windowing_posix::window,
      virtual public ::gtk4::acme::windowing::window
   {
   public:


      ::pointer<::xim::keyboard>          m_pximkeyboard;
      GtkIMContext *                      m_pimcontext;

      bool                                m_bImFocus;


      window();
      ~window() override;


      void on_initialize_particle() override;

      void _on_button_pressed(GtkGestureClick * widget, int n_press, double x, double y) override;

      void _on_button_released(GtkGestureClick * widget, int n_press, double x, double y) override;

      void _on_motion_notify(GtkEventControllerMotion * pcontroller, double x, double y) override;

      void _on_enter_notify(GtkEventControllerMotion * pcontroller, double x, double y) override;

      void _on_gtk_key_pressed(unsigned long long uGtkKey, unsigned long long uGtkKeyCode) override;
      void _on_gtk_key_released(unsigned long long uGtkKey, unsigned long long uGtkKeyCode) override;

      bool _on_gtk_key_pressed(GtkEventControllerKey *controller, guint keyval, guint keycode, GdkModifierType state) override;
      bool _on_gtk_key_released(GtkEventControllerKey *controller, guint keyval, guint keycode, GdkModifierType state) override;

      bool _on_gtk_scroll(GtkEventControllerScroll * peventcontrollerScroll, double dx, double dy) override;

      void _on_text(const ::scoped_string & scopedstr) override;

      virtual void _on_gtk_im_context_commit(const_char_pointer psz);

      void _on_window_visibility_changed(GObject * object, GParamSpec * pspec) override;

      void _on_cairo_draw(GtkWidget * widget, cairo_t * cr) override;

      void _on_size(int cx, int cy) override;

      virtual void _on_drawing_area_keyboard_focus();

      virtual void _on_drawing_area_keyboard_focus_lost();

      void create_window() override;

      void _create_window() override;

      void on_set_focus_to_child() override;

      void destroy() override;

      void _set_oswindow(::oswindow oswindow) override;

      ::oswindow oswindow() const override;

      void
      _on_window_button_pressed(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture, int n_press,
                                double x, double y) override;

      void _on_window_button_released(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture,
                                      int n_press, double x, double y) override;

      virtual int store_name(const_char_pointer psz);

      virtual int select_input(int iInput);

      virtual int select_all_input();

      virtual int map_window();

      virtual int unmap_window(bool bWithdraw);

      virtual void set_wm_class(const_char_pointer psz);

      void exit_iconify() override;

      void full_screen(const ::int_rectangle & rect = {}) override;

      void exit_full_screen() override;

      void exit_zoomed() override;

      //virtual void set_user_interaction(::windowing::window * pinteraction);

      //virtual void post_nc_destroy();

      virtual ::e_status set_window_icon(const ::file::path & path);

      //::oswindow get_parent_oswindow() override;

      ::windowing_gtk4::windowing * gtk4_windowing();

      ::windowing_gtk4::display * gtk4_display();

      void _on_initialize_system_menu_button(GtkWidget * pbutton, const ::scoped_string & scopedstrAtom);

      void set_parent(::windowing::window * pwindowNewParent) override;

      bool is_iconic() override;

      bool is_window_visible() override;

      bool _is_window_visible_unlocked() override;

      virtual bool client_to_screen(::int_point * ppoint) override;

      bool screen_to_client(::int_point * ppoint) override;

      bool is_destroying() override;

      virtual bool bamf_set_icon();

      virtual bool set_icon(::image::image * pimage);

      virtual void set_mouse_cursor2(::windowing::cursor * pcursor);

      void set_mouse_capture() override;

      void release_mouse_capture() override;

      void set_keyboard_focus() override;

      void _set_keyboard_focus_unlocked() override;

      void defer_show_system_menu(::user::mouse * pmouse) override;

      void set_mouse_cursor(::windowing::cursor * pcursor) override;

      void set_active_window() override;

      void _set_active_window_unlocked() override;

      void set_foreground_window(::user::activation_token * puseractivationtoken) override;

      void _set_foreground_window_unlocked(::user::activation_token * puseractivationtoken) override;

      bool has_keyboard_focus() override;

      void _on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize * size) override;

      void _on_display_change(::e_display edisplay) override;

      void destroy_window() override;

      bool is_window() override;

      void set_window_text(const ::scoped_string & scopedstr) override;

      void set_tool_window(bool bSet) override;

      void show_task(bool bShow) override;

      bool set_window_position(const class ::zorder & zorder, int x, int y, int cx, int cy,
                               const ::user::activation & useractivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                               ::e_display edisplay) override;


      bool _set_window_position_unlocked(const class ::zorder & zorder, int x, int y, int cx, int cy,
                                         const ::user::activation & useractivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                                         ::e_display edisplay) override;

      bool _configure_window_unlocked(const class ::zorder & zorder, const ::user::activation & useractivation, bool bNoZorder,
                                      ::e_display edisplay) override;

      bool _strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool bNoMove, bool bNoSize) override;

      virtual ::e_status window_rectangle(::int_rectangle * prectangle);

      virtual ::e_status rectangle(::int_rectangle * prectangle);

      void __update_graphics_buffer() override;

      bool is_active_window() override;

      void bring_to_front() override;

      void window_update_screen() override;

      virtual void _on_end_paint();

      bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

      bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;

      void final_mouse_message_handling(::message::mouse * pmouse) override;

      void _on_windowing_close_window() override;

      void window_restore() override;

      void window_minimize() override;

      void window_maximize() override;

      void on_window_deiconified() override;
      void on_window_activated() override;
      void on_window_iconified() override;
      void on_window_deactivated() override;
      void on_window_shown() override;
      void on_window_hidden() override;

      void _on_activation_change(bool bActive);


      virtual void _set_cursor_from_name(const ::scoped_string & scopedstr);

      virtual ::int_rectangle _unlocked_defer_get_window_rectangle();

      virtual void _unlocked_defer_set_window_position(const ::int_point & point);

      virtual void _unlocked_defer_set_window_position(const ::int_point & point, const ::int_size & size);

      virtual void _unlocked_defer_set_window_size(const ::int_size & size);

      void _main_send(const ::procedure & procedure) override;

      void _main_post(const ::procedure & procedure) override;


   };


} // namespace windowing_gtk4



