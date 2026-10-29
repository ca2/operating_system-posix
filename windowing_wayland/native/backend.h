#pragma once
#include "acme_windowing_wayland/native/backend.h"
#include "windowing_posix/window.h"
#include "windowing_posix/windowing.h"
#include "aura/windowing/display.h"
#include "aura/graphics/graphics/double_buffer.h"
#include "aura/graphics/graphics/bitmap_source_buffer.h"

namespace windowing_wayland
{
   class display : virtual public ::native_wayland::display, virtual public ::windowing::display
   {
   public:
      void open_display() override { ::native_wayland::display::open_display(); }
      void destroy() override { ::native_wayland::display::destroy(); }
      bool has_readily_gettable_absolute_pointer_position() const override { return false; }
      void _on_monitor(::i32 i, const ::i32_rectangle & r, const ::i32_rectangle & w) override
      { ::windowing::display::_on_monitor(i, r, w); }
   };
   class window : virtual public ::native_wayland::window, virtual public ::windowing_posix::window
   {
   public:
      void create_window() override { ::windowing::window::create_window(); }
      void _create_window() override;
      void destroy() override;
      void set_window_text(const ::scoped_string & title) override;
      void main_send(const ::procedure & p) override { ::native_wayland::window::main_send(p); }
      void main_post(const ::procedure & p) override { ::native_wayland::window::main_post(p); }
      void user_send(const ::procedure & p) override { main_send(p); }
      void user_post(const ::procedure & p) override { main_post(p); }
      void show_window(::user_interface::enum_show_window state) override;
      void _window_show_change_visibility(::e_display state, const ::user::activation & activation) override;
      bool _configure_window_unlocked(const class ::zorder &, const ::user::activation &, bool noZorder, ::e_display state) override;
      bool _strict_set_window_position_unlocked(int x, int y, int cx, int cy, bool noMove, bool noSize) override;
      bool is_window() override { return ::native_wayland::window::is_window(); }
      bool is_window_visible() override { return m_native && m_visible; }
      bool _is_window_visible_unlocked() override { return is_window_visible(); }
      bool is_iconic() override { return false; }
      bool is_active_window() override { return m_focused; }
      bool has_keyboard_focus() override { return m_bKeyboardFocus; }
      void set_keyboard_focus(::acme::user::interaction * interaction) override;
      void set_keyboard_focus() override;
      void native_focus(bool active) override;
      void native_configure(int width, int height) override;
      void native_close() override;
      void native_motion(double x, double y) override;
      void native_button(uint32_t button, bool pressed, double x, double y) override;
      void native_scroll(double delta) override;
      void native_key(uint32_t code, uint32_t symbol, bool pressed, const std::string & text) override;
      bool set_window_position(const class ::zorder &, int x, int y, int cx, int cy,
         const ::user::activation &, bool noZorder, bool noMove, bool noSize, ::e_display state) override;
      bool defer_perform_entire_reposition_process(::user::mouse *) override;
      bool defer_perform_entire_resizing_process(const ::experience::e_frame &, ::user::mouse *) override;
      void window_update_screen() override;
   private:
      void deliver_mouse(::user::enum_message message, double x, double y);
   };
   class windowing : virtual public ::native_wayland::windowing, virtual public ::windowing_posix::windowing
   {
   public:
      void initialize_windowing() override { ::native_wayland::windowing::initialize_windowing(); }
      void main_send(const ::procedure & p) override { ::native_wayland::windowing::main_send(p); }
      void main_post(const ::procedure & p) override { ::native_wayland::windowing::main_post(p); }
      void user_send(const ::procedure & p) override { main_send(p); }
      void user_post(const ::procedure & p) override { main_post(p); }
      void run() override { ::native_wayland::windowing::run(); }
      bool has_readily_gettable_absolute_coordinates() const override { return false; }
      bool defer_release_mouse_capture(::thread * thread, ::acme::windowing::window * window) override
      {
         if (!m_pacmewindowingwindowMouseCapture || (window && m_pacmewindowingwindowMouseCapture != window)) return false;
         m_pacmewindowingwindowMouseCapture.release();
         return true;
      }
   };
   class graphics : virtual public ::graphics::double_buffer_graphics, virtual public ::graphics::bitmap_source_buffer_graphics
   {
   public:
      void initialize_graphics_graphics(::windowing::window * pwindow) override;
      bool buffer_lock_round_swap_key_buffers() override;
      void on_update_screen(::graphics::buffer_item * item) override;
   };
}
