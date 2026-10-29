#include "acme/_start.h"
#include "acme/_.h"
#include "backend.h"
#include "acme/platform/system.h"
#include "acme/platform/application.h"
#include "acme/operating_system/desktop_application_id.h"
#include "acme/user/user/interaction.h"
#include "acme/constant/windowing2.h"
#include <thread>
#include <chrono>

namespace native_wayland
{
   void display::open_display()
   {
      if (!m_runtime) m_runtime = std::make_shared<::ca2_wayland::runtime>();
      _enumerate_monitors();
   }
   bool display::is_display_opened() const { return m_runtime && m_runtime->connected(); }
   void * display::native_wayland_display() { return m_runtime ? m_runtime->display() : nullptr; }
   void display::_enumerate_monitors()
   {
      if (!m_runtime) return;
      m_rectanglea.erase_all();
      int index = 0;
      for (const auto & o : m_runtime->outputs())
      {
         ::i32_rectangle rectangle(o.bounds.x, o.bounds.y, o.bounds.x + o.bounds.width, o.bounds.y + o.bounds.height);
         _on_monitor(index++, rectangle, rectangle);
      }
   }
   void display::display_send(const ::procedure & p) { m_runtime->send([p] { p(); }); }
   void display::display_post(const ::procedure & p) { m_runtime->post([p] { p(); }); }
   void display::destroy() { m_runtime.reset(); ::acme::windowing::display::destroy(); }

   ::acme::windowing::display * window::get_display() { return system()->acme_windowing()->acme_display(); }
   void window::create_window() { main_send([this] { _create_window(); }); }
   void window::_create_window()
   {
      ::cast<::native_wayland::display> pdisplay = get_display();
      if (!pdisplay) throw ::exception(error_wrong_type);
      m_runtime = pdisplay->m_runtime;
      m_pointWindow = {}; // Wayland does not disclose compositor-global placement.
      auto size = m_sizeWindow;
      if (size.is_empty()) size = {640, 480};
      ::ca2_wayland::callbacks events;
      events.configure = [this](int w, int h) { native_configure(w, h); };
      events.close = [this] { native_close(); };
      events.motion = [this](double x, double y) { native_motion(x, y); };
      events.button = [this](uint32_t b, bool down, double x, double y) { native_button(b, down, x, y); };
      events.scroll = [this](double delta) { native_scroll(delta); };
      events.key = [this](uint32_t code, uint32_t symbol, bool down, const std::string & text) { native_key(code, symbol, down, text); };
      events.focus = [this](bool active) { native_focus(active); };
      ::string title = m_pacmeuserinteraction ? m_pacmeuserinteraction->get_window_text() : "";
      if (title.is_empty()) title = application()->m_strAppName;
      if (title.is_empty()) title = application()->m_strAppId;
      const ::string appId = ::freedesktop::desktop_application_id(application()->m_strAppId);
      m_native = m_runtime->create_window(size.cx, size.cy, title.c_str(), appId.c_str(), std::move(events));
      m_visible = true;
   }
   void window::destroy() { m_visible = false; if (m_native) m_native->detach_events(); ::acme::windowing::window::destroy(); }
   bool window::is_window() { return bool(m_native); }
   bool window::_is_window() { return is_window(); }
   void * window::native_wayland_surface() { return m_native ? m_native->surface() : nullptr; }
   void window::main_send(const ::procedure & p) { get_display()->display_send(p); }
   void window::main_post(const ::procedure & p) { get_display()->display_post(p); }
   void window::user_send(const ::procedure & p) { main_send(p); }
   void window::user_post(const ::procedure & p) { main_post(p); }
   void window::show_window(::user_interface::enum_show_window state)
   {
      m_visible = state != ::user_interface::e_show_window_hide;
      if (!m_native) return;
      if (m_visible) m_native->show(); else m_native->hide();
   }
   void window::set_size_unlocked(const ::i32_size & size) { m_sizeWindow = size; if (m_native) m_native->resize(size.cx, size.cy); }
   void window::native_configure(int width, int height) { m_sizeWindow = {width, height}; }
   void window::native_close() { if (m_pacmeuserinteraction) m_pacmeuserinteraction->post_message(::user::e_message_close); }
   void window::native_motion(double, double) {}
   void window::native_button(uint32_t, bool, double, double) {}
   void window::native_scroll(double) {}
   void window::native_key(uint32_t, uint32_t, bool, const std::string &) {}
   void window::native_focus(bool active) { m_focused = active; }

   void windowing::initialize_windowing() {}
   ::windowing::enum_windowing windowing::calculate_ewindowing() { return ::windowing::e_windowing_wayland; }
   void windowing::main_send(const ::procedure & p) { acme_display()->display_send(p); }
   void windowing::main_post(const ::procedure & p) { acme_display()->display_post(p); }
   void windowing::user_send(const ::procedure & p) { main_send(p); }
   void windowing::user_post(const ::procedure & p) { main_post(p); }
   void windowing::windowing_application_on_system_start() { system()->on_branch_system_from_main_thread_startup(this); }
   void windowing::run()
   {
      while (::task_get_run())
      {
         auto task = ::get_task();
         if (task) task->task_iteration();
         std::this_thread::sleep_for(std::chrono::milliseconds(5));
      }
   }
}
