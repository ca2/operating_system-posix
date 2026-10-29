#include "acme/_start.h"
#include "windowing_posix/_.h"
#include "backend.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/user/user/key.h"
#include "aura/platform/application.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/interaction_thread.h"
#include "aura/user/user/interaction_graphics_thread.h"
#include "aura/graphics/graphics/buffer_item.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/image_pixmap_lease.h"
#include "aura/message/user.h"
#include <linux/input-event-codes.h>
#include <xkbcommon/xkbcommon-keysyms.h>
#include <cstdlib>

namespace windowing_wayland
{
   void window::_create_window()
   {
      ::native_wayland::window::_create_window();
      ::cast<::user::interaction> interaction = m_pacmeuserinteraction;
      if (interaction)
      {
         interaction->send_message(::user::e_message_create, 0, 0);
         interaction->m_ewindowflag |= e_window_flag_window_created;
         interaction->set_flag(e_flag_task_started);
         native_configure(m_sizeWindow.cx, m_sizeWindow.cy);
      }
   }
   void window::destroy()
   {
      m_visible = false;
      if (m_native) m_native->detach_events();
      ::windowing_posix::window::destroy();
   }
   void window::native_configure(int width, int height)
   {
      ::pointer<window> hold(this);
      auto apply = [hold, width, height] {
         if (!hold->m_visible) return;
         // The initial configure must reach layout even if the compositor kept
         // our requested size; otherwise child views can stay at zero size.
         hold->m_sizeWindow = {width, height};
         hold->on_window_configuration_change();
         if (auto interaction = hold->user_interaction())
         {
            interaction->set_need_layout(); interaction->set_need_redraw(); interaction->post_redraw();
         }
      };
      if (m_puserthread) m_puserthread->post(apply); else apply();
   }
   void window::set_window_text(const ::scoped_string & title)
   {
      const ::string text(title);
      if (m_native) m_native->set_title(text.c_str());
   }
   void window::show_window(::user_interface::enum_show_window state)
   {
      const bool wasVisible = m_visible;
      ::native_wayland::window::show_window(state);
      if (m_visible != wasVisible)
         if (auto interaction = user_interaction())
            interaction->post_message(::user::e_message_show_window, m_visible ? 1 : 0, 0);
   }
   void window::_window_show_change_visibility(::e_display state, const ::user::activation &)
   {
      if (m_native)
         m_native->set_state(state == e_display_zoomed, state == e_display_full_screen, state == e_display_iconic);
      show_window(state == e_display_none || state == e_display_hide
         ? ::user_interface::e_show_window_hide : ::user_interface::e_show_window_show_normal);
   }
   bool window::_configure_window_unlocked(const class ::zorder &, const ::user::activation & activation, bool, ::e_display state)
   {
      if (!m_native) return false;
      _window_show_change_visibility(state, activation);
      return true;
   }
   bool window::_strict_set_window_position_unlocked(int, int, int cx, int cy, bool, bool noSize)
   {
      if (!m_native) return false;
      if (!noSize && cx > 0 && cy > 0 && m_sizeWindow != ::i32_size(cx, cy))
      {
         m_sizeWindow = {cx, cy};
         m_native->resize(cx, cy);
      }
      return true;
   }
   void window::native_close() { if (auto interaction = user_interaction()) interaction->post_message(::user::e_message_close); }
   void window::set_keyboard_focus(::acme::user::interaction * interaction)
   {
      if (m_pacmeuserinteractionKeyboardFocus == interaction) return;
      ::cast<::user::interaction> previous = m_pacmeuserinteractionKeyboardFocus;
      ::acme::windowing::window::set_keyboard_focus(interaction);
      if (previous) previous->on_kill_keyboard_focus();
      ::cast<::user::interaction> focused = m_pacmeuserinteractionKeyboardFocus;
      if (focused) focused->on_set_keyboard_focus();
   }
   void window::set_keyboard_focus()
   {
      // The compositor grants surface focus. Child focus is maintained by
      // acme::windowing::window::set_keyboard_focus(interaction).
      // Requesting a child must not try to activate a Wayland surface.
   }
   void window::native_focus(bool active)
   {
      ::pointer<window> hold(this);
      auto deliver = [hold, active] {
         hold->m_focused = active;
         if (active)
         {
            hold->window_on_activate();
            hold->window_on_set_keyboard_focus();
         }
         else
         {
            hold->window_on_kill_keyboard_focus();
            hold->window_on_deactivate();
         }
         ::cast<::user::interaction> focused = hold->m_pacmeuserinteractionKeyboardFocus;
         if (focused)
         {
            if (active) focused->on_set_keyboard_focus();
            else focused->on_kill_keyboard_focus();
         }
      };
      if (m_puserthread) m_puserthread->post(deliver); else deliver();
   }
   void window::deliver_mouse(::user::enum_message message, double x, double y)
   {
      auto mouse = create_newø<::message::mouse>();
      mouse->m_eusermessage = message; mouse->m_pwindow = this; mouse->m_operatingsystemwindow = operating_system_window();
      mouse->m_pointHost = {int(x), int(y)};
      // Surface-local coordinates; global coordinates are not exposed by Wayland.
      mouse->m_pointAbsolute = mouse->m_pointHost;
      ::pointer<window> hold(this);
      auto deliver = [hold, mouse] {
         if (hold->m_visible) hold->message_handler(mouse);
      };
      if (m_puserthread) m_puserthread->post(deliver); else deliver();
   }
   void window::native_motion(double x, double y) { deliver_mouse(::user::e_message_mouse_move, x, y); }
   void window::native_button(uint32_t button, bool pressed, double x, double y)
   {
      auto message = pressed ? ::user::e_message_left_button_down : ::user::e_message_left_button_up;
      if (button == BTN_RIGHT) message = pressed ? ::user::e_message_right_button_down : ::user::e_message_right_button_up;
      else if (button == BTN_MIDDLE) message = pressed ? ::user::e_message_middle_button_down : ::user::e_message_middle_button_up;
      else if (button != BTN_LEFT) return;
      deliver_mouse(message, x, y);
   }
   void window::native_scroll(double delta)
   {
      auto mouse = create_newø<::message::mouse_wheel>();
      mouse->m_eusermessage = ::user::e_message_mouse_wheel;
      mouse->m_pwindow = this; mouse->m_operatingsystemwindow = operating_system_window();
      mouse->m_Δ = (short)(-delta * 12.0);
      ::pointer<window> hold(this);
      auto deliver = [hold, mouse] {
         if (hold->m_visible) hold->message_handler(mouse);
      };
      if (m_puserthread) m_puserthread->post(deliver); else deliver();
   }
   void window::native_key(uint32_t code, uint32_t symbol, bool pressed, const std::string & text)
   {
      auto key = create_newø<::message::key>();
      key->m_eusermessage = pressed ? ::user::e_message_key_down : ::user::e_message_key_up;
      key->m_pwindow = this; key->m_operatingsystemwindow = operating_system_window();
      key->m_wparam = symbol;
      key->m_lparam = 0;
      key->m_iCode = code;
      key->m_iVirtualKey = symbol;
      key->m_nRepCnt = 1;
      key->m_nFlags = 0;
      key->m_bExt = symbol == XKB_KEY_Left || symbol == XKB_KEY_Right || symbol == XKB_KEY_Up || symbol == XKB_KEY_Down;
      key->m_nChar = symbol;
      key->m_nScanCode = code + 8;
      key->m_ekey = ::user::e_key_none;
      if (symbol >= XKB_KEY_a && symbol <= XKB_KEY_z) key->m_ekey = (::user::enum_key)((int)::user::e_key_a + (int)(symbol - XKB_KEY_a));
      else if (symbol >= XKB_KEY_A && symbol <= XKB_KEY_Z) key->m_ekey = (::user::enum_key)((int)::user::e_key_a + (int)(symbol - XKB_KEY_A));
      else if (symbol >= XKB_KEY_0 && symbol <= XKB_KEY_9) key->m_ekey = (::user::enum_key)((int)::user::e_key_0 + (int)(symbol - XKB_KEY_0));
      else if (symbol == XKB_KEY_Escape) key->m_ekey = ::user::e_key_escape;
      else if (symbol == XKB_KEY_Return) key->m_ekey = ::user::e_key_return;
      else if (symbol == XKB_KEY_space) key->m_ekey = ::user::e_key_space;
      else if (symbol == XKB_KEY_BackSpace) key->m_ekey = ::user::e_key_back;
      else if (symbol == XKB_KEY_Tab) key->m_ekey = ::user::e_key_tab;
      else if (symbol == XKB_KEY_Left) key->m_ekey = ::user::e_key_left;
      else if (symbol == XKB_KEY_Right) key->m_ekey = ::user::e_key_right;
      else if (symbol == XKB_KEY_Up) key->m_ekey = ::user::e_key_up;
      else if (symbol == XKB_KEY_Down) key->m_ekey = ::user::e_key_down;
      else if (symbol == XKB_KEY_Shift_L) key->m_ekey = ::user::e_key_left_shift;
      else if (symbol == XKB_KEY_Shift_R) key->m_ekey = ::user::e_key_right_shift;
      else if (symbol == XKB_KEY_Control_L) key->m_ekey = ::user::e_key_left_control;
      else if (symbol == XKB_KEY_Control_R) key->m_ekey = ::user::e_key_right_control;
      else if (symbol == XKB_KEY_Alt_L) key->m_ekey = ::user::e_key_left_alt;
      else if (symbol == XKB_KEY_Alt_R) key->m_ekey = ::user::e_key_right_alt;
      key->m_strText = text.c_str();
      // Framework input and session state belong to the interaction thread.
      ::pointer<window> hold(this);
      auto deliver = [hold, key, pressed] {
         if (pressed && !hold->m_visible) return;
         // Always clear releases, including after unmap or interaction teardown.
         // Keep other framework controls' event-fed session state synchronized too.
         if (auto session = hold->session(); session && key->m_ekey != ::user::e_key_none)
            session->set_key_pressed(key->m_ekey, pressed);
         if (std::getenv("CA2_TRACE_INPUT"))
            hold->informationf("CA2_INPUT key code=%u symbol=%u key=%d down=%d", key->m_iCode, key->m_iVirtualKey, (int)key->m_ekey, pressed);
         hold->message_handler(key);
      };
      if (m_puserthread) m_puserthread->post(deliver); else deliver();
   }
   bool window::set_window_position(const class ::zorder &, int, int, int cx, int cy,
      const ::user::activation &, bool, bool, bool noSize, ::e_display state)
   {
      if (!m_native) return false;
      const bool wasVisible = m_visible;
      if (!noSize && cx > 0 && cy > 0) { m_sizeWindow = {cx, cy}; m_native->resize(cx, cy); }
      m_native->set_state(state == e_display_zoomed, state == e_display_full_screen, state == e_display_iconic);
      m_visible = state != e_display_none && state != e_display_hide;
      if (!m_visible) m_native->hide();
      else m_native->show();
      if (m_visible != wasVisible)
         if (auto interaction = user_interaction())
            interaction->post_message(::user::e_message_show_window, m_visible ? 1 : 0, 0);
      return true;
   }
   bool window::defer_perform_entire_reposition_process(::user::mouse *) { if (!m_native) return false; m_native->start_move(); return true; }
   bool window::defer_perform_entire_resizing_process(const ::experience::e_frame & frame, ::user::mouse *)
   {
      if (!m_native) return false;
      unsigned edge = 0;
      if (frame & ::experience::e_frame_sizing_left) edge |= 4;
      if (frame & ::experience::e_frame_sizing_right) edge |= 8;
      if (frame & ::experience::e_frame_sizing_top) edge |= 1;
      if (frame & ::experience::e_frame_sizing_bottom) edge |= 2;
      if (!edge || (edge & 3) == 3 || (edge & 12) == 12) return false;
      m_native->start_resize(edge); return true;
   }
   void window::window_update_screen() { if (m_pgraphicsthread) m_pgraphicsthread->post_redraw(); }

   void graphics::initialize_graphics_graphics(::windowing::window * window)
   {
      ::graphics::double_buffer_graphics::initialize_graphics_graphics(window);
      ::graphics::bitmap_source_buffer_graphics::initialize_graphics_graphics(window);
   }
   bool graphics::buffer_lock_round_swap_key_buffers()
   {
      const bool swapped = ::graphics::double_buffer_graphics::buffer_lock_round_swap_key_buffers();
      return ::graphics::bitmap_source_buffer_graphics::buffer_lock_round_swap_key_buffers() && swapped;
   }
   void graphics::on_update_screen(::graphics::buffer_item * item)
   {
      ::cast<::windowing_wayland::window> window = m_pwindow;
      if (!window || !window->m_native || !item || !item->m_pimageBufferItem) return;
      auto image = item->m_pimageBufferItem->map();
      if (!image || !image->data()) return;
      window->m_native->present(image->data(), image->width(), image->height(), image->m_iScan);
   }
}
