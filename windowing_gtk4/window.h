// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "windowing_posix/window.h"
#include "gtk4_widget.h"
#include "acme/prototype/geometry2d/rectangle_array.h"
#include "nano_user_gtk4/window.h"


namespace windowing_gtk4
{


   class window;


   class CLASS_DECL_WINDOWING_GTK4 window :
      virtual public ::windowing_posix::window,
      virtual public ::gtk4::micro::window
   {
   public:


      ::pointer<::xim::keyboard> m_pximkeyboard;


      window();

      ~window() override;


      void on_initialize_particle() override;

      void _on_button_pressed(GtkGestureClick * widget, int n_press, double x, double y) override;

      void _on_button_released(GtkGestureClick * widget, int n_press, double x, double y) override;

      void _on_motion_notify(GtkEventControllerMotion * pcontroller, double x, double y) override;

      void _on_enter_notify(GtkEventControllerMotion * pcontroller, double x, double y) override;

      void _on_window_visibility_changed(GObject * object, GParamSpec * pspec) override;

      void _on_cairo_draw(GtkWidget * widget, cairo_t * cr) override;

      void _on_size(int cx, int cy) override;

      void create_window() override;

      void destroy() override;

      void _set_oswindow(::oswindow oswindow) override;

      ::oswindow oswindow() const override;

      void
      _on_window_button_pressed(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture, int n_press,
                                double x, double y) override;

      void _on_window_button_released(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture,
                                      int n_press, double x, double y) override;

      virtual i32 store_name(const char * psz);

      virtual i32 select_input(i32 iInput);

      virtual i32 select_all_input();

      virtual i32 map_window();

      virtual i32 unmap_window(bool bWithdraw);

      virtual void set_wm_class(const char * psz);

      void exit_iconify() override;

      void full_screen(const ::rectangle_i32 & rect = {}) override;

      void exit_full_screen() override;

      void exit_zoomed() override;

      virtual void set_user_interaction(::windowing::window * pinteraction);

      virtual void post_nc_destroy();

      virtual ::e_status set_window_icon(const ::file::path & path);

      ::oswindow get_parent_oswindow() const override;

      ::windowing_gtk4::windowing * gtk4_windowing();

      ::windowing_gtk4::display * gtk4_display();

      void _on_initialize_system_menu_button(GtkWidget * pbutton, const ::scoped_string & scopedstrAtom);

      void set_parent(::windowing::window * pwindowNewParent) override;

      bool is_iconic() override;

      bool is_window_visible() override;

      bool _is_window_visible_unlocked() override;

      virtual bool client_to_screen(::point_i32 * ppoint) override;

      bool screen_to_client(::point_i32 * ppoint) override;

      bool is_destroying() override;

      virtual bool bamf_set_icon();

      virtual bool set_icon(::image::image * pimage);

      virtual void set_mouse_cursor2(::windowing::cursor * pcursor);

      void set_keyboard_focus() override;

      void _set_keyboard_focus_unlocked() override;

      void defer_show_system_menu(::user::mouse * pmouse) override;

      void set_mouse_cursor(::windowing::cursor * pcursor) override;

      void set_active_window() override;

      void _set_active_window_unlocked() override;

      void set_foreground_window() override;

      void _set_foreground_window_unlocked() override;

      bool has_keyboard_focus() const override;

      void _on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize * size) override;

      void _on_display_change(::e_display edisplay) override;

      void destroy_window() override;

      bool is_window() override;

      void set_window_text(const ::scoped_string & scopedstr) override;

      void set_tool_window(bool bSet) override;

      bool set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,
                               const ::e_activation & eactivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                               ::e_display edisplay) override;


      bool _set_window_position_unlocked(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy,
                                         const ::e_activation & eactivation, bool bNoZorder, bool bNoMove, bool bNoSize,
                                         ::e_display edisplay) override;

      bool _configure_window_unlocked(const class ::zorder & zorder, const ::e_activation & eactivation, bool bNoZorder,
                                      ::e_display edisplay) override;

      bool _strict_set_window_position_unlocked(i32 x, i32 y, i32 cx, i32 cy, bool bNoMove, bool bNoSize) override;

      virtual ::e_status window_rectangle(::rectangle_i32 * prectangle);

      virtual ::e_status rectangle(::rectangle_i32 * prectangle);

      void __update_graphics_buffer() override;

      bool is_active_window() const override;

      void bring_to_front() override;

      void window_update_screen() override;

      virtual void _on_end_paint();

      bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

      bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;

      void on_destruct_mouse_message(::message::mouse * pmouse) override;

      void _on_windowing_close_window() override;

      void window_restore() override;

      void window_minimize() override;

      void window_maximize() override;

      virtual void _set_cursor_from_name(const ::scoped_string & scopedstr);

      virtual ::rectangle_i32 _unlocked_defer_get_window_rectangle();

      virtual void _unlocked_defer_set_window_position(const ::point_i32 & point);

      virtual void _unlocked_defer_set_window_position(const ::point_i32 & point, const ::size_i32 & size);

      virtual void _unlocked_defer_set_window_size(const ::size_i32 & size);

   };


} // namespace windowing_gtk4



