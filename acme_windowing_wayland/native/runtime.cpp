#include "runtime.h"
using const_char_pointer = const char *;
#include "../../wayland_static/wayland-xdg_wm_base.h"
#include <wayland-client.h>
#include <wayland-cursor.h>
#include <cstdio>
#include <xkbcommon/xkbcommon.h>
#include <sys/eventfd.h>
#include <sys/mman.h>
#include <sys/poll.h>
#include <unistd.h>
#include <linux/input-event-codes.h>
#include <algorithm>
#include <atomic>
#include <cerrno>
#include <cstring>
#include <deque>
#include <future>
#include <map>
#include <mutex>
#include <stdexcept>
#include <thread>

namespace ca2_wayland
{
   struct shm_buffer
   {
      wl_buffer * handle = nullptr;
      void * data = MAP_FAILED;
      size_t bytes = 0;
      int width = 0, height = 0, stride = 0;
      bool busy = false;
      ~shm_buffer() { if (handle) wl_buffer_destroy(handle); if (data != MAP_FAILED) munmap(data, bytes); }
   };
   struct window::impl
   {
      runtime * owner = nullptr;
      wl_surface * surface = nullptr;
      xdg_surface * shell = nullptr;
      xdg_toplevel * toplevel = nullptr;
      callbacks events;
      int width = 1, height = 1;
      std::atomic<bool> ready{false};
      bool visible = false;
      bool hidden = false;
      unsigned external_presenters = 0;
      std::mutex presentation_mutex;
      std::vector<std::unique_ptr<shm_buffer>> buffers;
   };
   struct output_state { runtime::impl * owner; wl_output * handle; output value; };
   struct runtime::impl
   {
      ~impl();
      runtime * owner;
      wl_display * display = nullptr;
      wl_registry * registry = nullptr;
      wl_compositor * compositor = nullptr;
      wl_shm * shm = nullptr;
      xdg_wm_base * shell = nullptr;
      wl_seat * seat = nullptr;
      wl_pointer * pointer = nullptr;
      wl_keyboard * keyboard = nullptr;
      wl_cursor_theme * cursor_theme = nullptr;
      wl_surface * cursor_surface = nullptr;
      xkb_context * xkb = nullptr;
      xkb_keymap * keymap = nullptr;
      xkb_state * keyboard_state = nullptr;
      window::impl * pointer_window = nullptr;
      window::impl * keyboard_window = nullptr;
      std::map<uint32_t, uint32_t> pressed_keys;
      double pointer_x = 0, pointer_y = 0;
      uint32_t serial = 0;
      std::map<uint32_t, std::unique_ptr<output_state>> outputs;
      std::thread thread;
      std::atomic<bool> running{true};
      int wake = -1;
      std::mutex mutex;
      std::deque<std::function<void()>> jobs;
      std::map<wl_surface *, window::impl *> windows;
      void drain()
      {
         std::deque<std::function<void()>> pending;
         { std::lock_guard<std::mutex> lock(mutex); pending.swap(jobs); }
         for (auto & job : pending)
         {
            try { job(); }
            catch (const std::exception & error) { std::fprintf(stderr, "Wayland dispatch: %s\n", error.what()); }
            catch (...) { std::fprintf(stderr, "Wayland dispatch: application callback failed\n"); }
         }
      }
      void loop()
      {
         while (running)
         {
            drain();
            while (wl_display_prepare_read(display) != 0)
               if (wl_display_dispatch_pending(display) < 0) { running = false; break; }
            if (!running) break;
            const int flushed = wl_display_flush(display);
            if (flushed < 0 && errno != EAGAIN) { wl_display_cancel_read(display); break; }
            pollfd fds[] = {{wl_display_get_fd(display), short(POLLIN | (flushed < 0 ? POLLOUT : 0)), 0}, {wake, POLLIN, 0}};
            int status;
            do { status = poll(fds, 2, 100); } while (status < 0 && errno == EINTR);
            if (status < 0 || (fds[0].revents & (POLLERR | POLLHUP | POLLNVAL)))
            { wl_display_cancel_read(display); break; }
            if (fds[0].revents & POLLIN)
            { if (wl_display_read_events(display) < 0) break; }
            else wl_display_cancel_read(display);
            if (fds[1].revents & POLLIN) { uint64_t value; (void)read(wake, &value, sizeof(value)); }
            if (wl_display_dispatch_pending(display) < 0) break;
         }
         running = false;
         drain();
      }
   };

   static void output_geometry(void * data, wl_output *, int32_t x, int32_t y, int32_t, int32_t, int32_t, const char *, const char *, int32_t)
   { auto & o = static_cast<output_state *>(data)->value; o.bounds.x = x; o.bounds.y = y; }
   static void output_mode(void * data, wl_output *, uint32_t flags, int32_t width, int32_t height, int32_t)
   { if (flags & WL_OUTPUT_MODE_CURRENT) { auto & o = static_cast<output_state *>(data)->value; o.bounds.width = width; o.bounds.height = height; } }
   static void output_done(void *, wl_output *) {}
   static void output_scale(void * data, wl_output *, int32_t scale) { static_cast<output_state *>(data)->value.scale = std::max(1, scale); }
   static void output_name(void * data, wl_output *, const char * name) { static_cast<output_state *>(data)->value.name = name; }
   static void output_description(void *, wl_output *, const char *) {}
   static const wl_output_listener output_listener = {output_geometry, output_mode, output_done, output_scale, output_name, output_description};
   static window::impl * find_window(runtime::impl * s, wl_surface * surface)
   { const auto found = s->windows.find(surface); return found == s->windows.end() ? nullptr : found->second; }
   template<class Function, class... Args> static void notify(Function & function, Args &&... args)
   {
      if (!function) return;
      try { function(std::forward<Args>(args)...); }
      catch (...) { std::fprintf(stderr, "Wayland event: application callback failed\n"); }
   }
   static void pointer_enter(void * data, wl_pointer * pointer, uint32_t serial, wl_surface * surface, wl_fixed_t x, wl_fixed_t y)
   {
      auto s = static_cast<runtime::impl *>(data); s->serial = serial; s->pointer_window = find_window(s, surface);
      s->pointer_x = wl_fixed_to_double(x); s->pointer_y = wl_fixed_to_double(y);
      if (s->cursor_theme && s->cursor_surface)
      {
         auto cursor = wl_cursor_theme_get_cursor(s->cursor_theme, "left_ptr");
         if (cursor && cursor->image_count)
         {
            auto image = cursor->images[0];
            wl_pointer_set_cursor(pointer, serial, s->cursor_surface, image->hotspot_x, image->hotspot_y);
            wl_surface_attach(s->cursor_surface, wl_cursor_image_get_buffer(image), 0, 0);
            wl_surface_damage(s->cursor_surface, 0, 0, image->width, image->height);
            wl_surface_commit(s->cursor_surface);
         }
      }
   }
   static void pointer_leave(void * data, wl_pointer *, uint32_t, wl_surface *) { static_cast<runtime::impl *>(data)->pointer_window = nullptr; }
   static void pointer_motion(void * data, wl_pointer *, uint32_t, wl_fixed_t x, wl_fixed_t y)
   { auto s = static_cast<runtime::impl *>(data); s->pointer_x = wl_fixed_to_double(x); s->pointer_y = wl_fixed_to_double(y); auto w = s->pointer_window; if (w) notify(w->events.motion, s->pointer_x, s->pointer_y); }
   static void pointer_button(void * data, wl_pointer *, uint32_t serial, uint32_t, uint32_t button, uint32_t state)
   { auto s = static_cast<runtime::impl *>(data); s->serial = serial; auto w = s->pointer_window; if (w) notify(w->events.button, button, state == WL_POINTER_BUTTON_STATE_PRESSED, s->pointer_x, s->pointer_y); }
   static void pointer_axis(void * data, wl_pointer *, uint32_t, uint32_t axis, wl_fixed_t value)
   { auto s = static_cast<runtime::impl *>(data); auto w = s->pointer_window; if (axis == WL_POINTER_AXIS_VERTICAL_SCROLL && w) notify(w->events.scroll, wl_fixed_to_double(value)); }
   static void pointer_frame(void *, wl_pointer *) {}
   static void pointer_axis_source(void *, wl_pointer *, uint32_t) {}
   static void pointer_axis_stop(void *, wl_pointer *, uint32_t, uint32_t) {}
   static void pointer_axis_discrete(void *, wl_pointer *, uint32_t, int32_t) {}
   static const wl_pointer_listener pointer_listener = {pointer_enter, pointer_leave, pointer_motion, pointer_button, pointer_axis, pointer_frame, pointer_axis_source, pointer_axis_stop, pointer_axis_discrete};
   static void release_keyboard_keys(runtime::impl * s)
   {
      if (s->keyboard_window)
         for (const auto & key : s->pressed_keys)
            notify(s->keyboard_window->events.key, key.first, key.second, false, std::string{});
      s->pressed_keys.clear();
   }
   static void restore_keyboard_keys(runtime::impl * s, const wl_array * keys)
   {
      if (!s->keyboard_window || !s->keyboard_state || !keys) return;
      const auto codes = static_cast<const uint32_t *>(keys->data);
      for (size_t i = 0; i < keys->size / sizeof(uint32_t); ++i)
      {
         const uint32_t code = codes[i];
         const auto symbol = xkb_state_key_get_one_sym(s->keyboard_state, code + 8);
         s->pressed_keys[code] = symbol;
         notify(s->keyboard_window->events.key, code, symbol, true, std::string{});
      }
   }
   static void keyboard_keymap(void * data, wl_keyboard *, uint32_t format, int32_t fd, uint32_t size)
   {
      auto s = static_cast<runtime::impl *>(data);
      if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1 || size == 0) { close(fd); return; }
      void * mapping = mmap(nullptr, size, PROT_READ, MAP_PRIVATE, fd, 0);
      close(fd);
      if (mapping == MAP_FAILED) return;
      auto map = xkb_keymap_new_from_string(s->xkb, static_cast<char *>(mapping), XKB_KEYMAP_FORMAT_TEXT_V1, XKB_KEYMAP_COMPILE_NO_FLAGS);
      munmap(mapping, size);
      if (!map) return;
      release_keyboard_keys(s);
      if (s->keyboard_state) xkb_state_unref(s->keyboard_state);
      if (s->keymap) xkb_keymap_unref(s->keymap);
      s->keymap = map; s->keyboard_state = xkb_state_new(map);
   }
   static void keyboard_enter(void * data, wl_keyboard *, uint32_t, wl_surface * surface, wl_array * keys)
   {
      auto s = static_cast<runtime::impl *>(data);
      release_keyboard_keys(s);
      s->keyboard_window = find_window(s, surface);
      if (s->keyboard_window) notify(s->keyboard_window->events.focus, true);
      restore_keyboard_keys(s, keys);
   }
   static void keyboard_leave(void * data, wl_keyboard *, uint32_t, wl_surface *)
   {
      auto s = static_cast<runtime::impl *>(data);
      if (s->keyboard_window)
      {
         // Releases may otherwise go to the newly focused application.
         release_keyboard_keys(s);
         notify(s->keyboard_window->events.focus, false);
      }
      s->pressed_keys.clear();
      s->keyboard_window = nullptr;
   }
   static void keyboard_key(void * data, wl_keyboard *, uint32_t serial, uint32_t, uint32_t key, uint32_t state)
   {
      auto s = static_cast<runtime::impl *>(data); s->serial = serial; auto w = s->keyboard_window;
      if (!w || !w->events.key || !s->keyboard_state) return;
      char text[128] = {};
      xkb_state_key_get_utf8(s->keyboard_state, key + 8, text, sizeof(text));
      const bool pressed = state == WL_KEYBOARD_KEY_STATE_PRESSED;
      auto symbol = xkb_state_key_get_one_sym(s->keyboard_state, key + 8);
      if (pressed) s->pressed_keys[key] = symbol;
      else if (auto it = s->pressed_keys.find(key); it != s->pressed_keys.end())
      { symbol = it->second; s->pressed_keys.erase(it); }
      notify(w->events.key, key, symbol, pressed, std::string(text));
   }
   static void keyboard_modifiers(void * data, wl_keyboard *, uint32_t, uint32_t depressed, uint32_t latched, uint32_t locked, uint32_t group)
   { auto s = static_cast<runtime::impl *>(data); if (s->keyboard_state) xkb_state_update_mask(s->keyboard_state, depressed, latched, locked, 0, 0, group); }
   static void keyboard_repeat(void *, wl_keyboard *, int32_t, int32_t) {}
   static const wl_keyboard_listener keyboard_listener = {keyboard_keymap, keyboard_enter, keyboard_leave, keyboard_key, keyboard_modifiers, keyboard_repeat};
   static void seat_capabilities(void * data, wl_seat * seat, uint32_t capabilities)
   {
      auto s = static_cast<runtime::impl *>(data);
      if ((capabilities & WL_SEAT_CAPABILITY_POINTER) && !s->pointer) { s->pointer = wl_seat_get_pointer(seat); wl_pointer_add_listener(s->pointer, &pointer_listener, s); }
      if (!(capabilities & WL_SEAT_CAPABILITY_POINTER) && s->pointer) { wl_pointer_destroy(s->pointer); s->pointer = nullptr; s->pointer_window = nullptr; }
      if ((capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && !s->keyboard) { s->keyboard = wl_seat_get_keyboard(seat); wl_keyboard_add_listener(s->keyboard, &keyboard_listener, s); }
      if (!(capabilities & WL_SEAT_CAPABILITY_KEYBOARD) && s->keyboard) { release_keyboard_keys(s); wl_keyboard_destroy(s->keyboard); s->keyboard = nullptr; s->keyboard_window = nullptr; }
   }
   static void seat_name(void *, wl_seat *, const char *) {}
   static const wl_seat_listener seat_listener = {seat_capabilities, seat_name};
   static void shell_ping(void *, xdg_wm_base * shell, uint32_t serial) { xdg_wm_base_pong(shell, serial); }
   static const xdg_wm_base_listener shell_listener = {shell_ping};
   static void registry_global(void * data, wl_registry * registry, uint32_t name, const char * interface, uint32_t version)
   {
      auto s = static_cast<runtime::impl *>(data);
      if (!strcmp(interface, wl_compositor_interface.name)) s->compositor = static_cast<wl_compositor *>(wl_registry_bind(registry, name, &wl_compositor_interface, std::min(version, 4u)));
      else if (!strcmp(interface, wl_shm_interface.name)) s->shm = static_cast<wl_shm *>(wl_registry_bind(registry, name, &wl_shm_interface, 1));
      else if (!strcmp(interface, xdg_wm_base_interface.name)) { s->shell = static_cast<xdg_wm_base *>(wl_registry_bind(registry, name, &xdg_wm_base_interface, std::min(version, 3u))); xdg_wm_base_add_listener(s->shell, &shell_listener, s); }
      else if (!strcmp(interface, wl_seat_interface.name)) { s->seat = static_cast<wl_seat *>(wl_registry_bind(registry, name, &wl_seat_interface, std::min(version, 5u))); wl_seat_add_listener(s->seat, &seat_listener, s); }
      else if (!strcmp(interface, wl_output_interface.name))
      {
         auto o = std::make_unique<output_state>(); o->owner = s;
         o->handle = static_cast<wl_output *>(wl_registry_bind(registry, name, &wl_output_interface, std::min(version, 4u)));
         wl_output_add_listener(o->handle, &output_listener, o.get()); s->outputs[name] = std::move(o);
      }
   }
   static void registry_remove(void * data, wl_registry *, uint32_t name)
   { auto s = static_cast<runtime::impl *>(data); auto found = s->outputs.find(name); if (found != s->outputs.end()) { wl_output_destroy(found->second->handle); s->outputs.erase(found); } }
   static const wl_registry_listener registry_listener = {registry_global, registry_remove};

   runtime::runtime() : state(std::make_unique<impl>())
   {
      auto s = state.get(); s->owner = this;
      s->display = wl_display_connect(nullptr);
      if (!s->display) throw std::runtime_error("Cannot connect to Wayland compositor");
      s->xkb = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
      s->wake = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
      s->registry = wl_display_get_registry(s->display);
      wl_registry_add_listener(s->registry, &registry_listener, s);
      if (wl_display_roundtrip(s->display) < 0 || wl_display_roundtrip(s->display) < 0 || !s->compositor || !s->shell || !s->shm || s->wake < 0 || !s->xkb)
         throw std::runtime_error("Wayland compositor lacks required XDG shell or shared memory support");
      s->cursor_theme = wl_cursor_theme_load(nullptr, 24, s->shm);
      s->cursor_surface = wl_compositor_create_surface(s->compositor);
      s->thread = std::thread([s] { s->loop(); });
   }
   runtime::~runtime() = default;
   runtime::impl::~impl()
   {
      auto s = this; s->running = false; uint64_t value = 1; (void)write(s->wake, &value, sizeof(value));
      if (s->thread.joinable()) s->thread.join();
      for (auto & o : s->outputs) wl_output_destroy(o.second->handle);
      if (s->cursor_surface) wl_surface_destroy(s->cursor_surface);
      if (s->cursor_theme) wl_cursor_theme_destroy(s->cursor_theme);
      if (s->keyboard) wl_keyboard_destroy(s->keyboard);
      if (s->pointer) wl_pointer_destroy(s->pointer);
      if (s->seat) wl_seat_destroy(s->seat);
      if (s->keyboard_state) xkb_state_unref(s->keyboard_state);
      if (s->keymap) xkb_keymap_unref(s->keymap);
      if (s->xkb) xkb_context_unref(s->xkb);
      if (s->shell) xdg_wm_base_destroy(s->shell);
      if (s->shm) wl_shm_destroy(s->shm);
      if (s->compositor) wl_compositor_destroy(s->compositor);
      if (s->registry) wl_registry_destroy(s->registry);
      if (s->display) wl_display_disconnect(s->display);
      if (s->wake >= 0) close(s->wake);
   }
   bool runtime::is_current() const { return state->thread.get_id() == std::this_thread::get_id(); }
   bool runtime::connected() const { return state->running; }
   wl_display * runtime::display() const { return state->display; }
   void runtime::post(std::function<void()> job)
   {
      { std::lock_guard<std::mutex> lock(state->mutex); if (!state->running) throw std::runtime_error("Wayland display disconnected"); state->jobs.push_back(std::move(job)); }
      uint64_t value = 1; (void)write(state->wake, &value, sizeof(value));
   }
   void runtime::send(std::function<void()> job)
   {
      if (is_current()) { job(); return; }
      auto task = std::make_shared<std::packaged_task<void()>>(std::move(job)); auto result = task->get_future();
      post([task] { (*task)(); }); result.get();
   }
   std::vector<output> runtime::outputs()
   {
      std::vector<output> result;
      send([&] { for (const auto & item : state->outputs) { auto o = item.second->value; o.bounds.width /= o.scale; o.bounds.height /= o.scale; result.push_back(o); } });
      return result;
   }
   static void surface_configure(void * data, xdg_surface * shell, uint32_t serial)
   {
      auto w = static_cast<window::impl *>(data); xdg_surface_ack_configure(shell, serial);
      // A configure already queued before unmapping cannot make a hidden
      // surface ready for presentation again.
      w->ready = !w->hidden;
      if (w->hidden) return;
      notify(w->events.configure, w->width, w->height);
   }
   static const xdg_surface_listener surface_listener = {surface_configure};
   static void toplevel_configure(void * data, xdg_toplevel *, int32_t width, int32_t height, wl_array *)
   { auto w = static_cast<window::impl *>(data); if (width > 0) w->width = width; if (height > 0) w->height = height; }
   static void toplevel_close(void * data, xdg_toplevel *) { auto w = static_cast<window::impl *>(data); notify(w->events.close); }
   static const xdg_toplevel_listener toplevel_listener = {toplevel_configure, toplevel_close};
   std::shared_ptr<window> runtime::create_window(int width, int height, const std::string & title, const std::string & appId, callbacks events)
   {
      std::shared_ptr<window> result;
      send([&] {
         auto w = std::make_unique<window::impl>(); w->owner = this; w->width = std::max(1, width); w->height = std::max(1, height); w->events = std::move(events);
         w->surface = wl_compositor_create_surface(state->compositor); w->shell = xdg_wm_base_get_xdg_surface(state->shell, w->surface);
         w->toplevel = xdg_surface_get_toplevel(w->shell);
         xdg_surface_add_listener(w->shell, &surface_listener, w.get()); xdg_toplevel_add_listener(w->toplevel, &toplevel_listener, w.get());
         xdg_toplevel_set_title(w->toplevel, title.c_str()); xdg_toplevel_set_app_id(w->toplevel, appId.c_str());
         state->windows[w->surface] = w.get();
         wl_surface_commit(w->surface);
         // Complete the initial XDG configure before higher-level create callbacks
         // can synchronously request a drawable surface on another thread.
         if (wl_display_roundtrip(state->display) < 0 || !w->ready)
            throw std::runtime_error("Wayland initial surface configure failed");
         result = std::shared_ptr<window>(new window(std::move(w)));
      });
      return result;
   }
   window::window(std::unique_ptr<impl> value) : state(std::move(value)) {}
   window::~window()
   {
      auto w = state.get();
      auto cleanup = [&] {
         auto s = w->owner->state.get(); w->events = {};
         if (s->pointer_window == w) s->pointer_window = nullptr;
         if (s->keyboard_window == w) s->keyboard_window = nullptr;
         s->windows.erase(w->surface); w->buffers.clear();
         xdg_toplevel_destroy(w->toplevel); xdg_surface_destroy(w->shell); wl_surface_destroy(w->surface);
      };
      try { w->owner->send(cleanup); }
      catch (...)
      {
         auto & thread = w->owner->state->thread;
         if (thread.joinable() && thread.get_id() != std::this_thread::get_id()) thread.join();
         cleanup();
      }
   }
   wl_surface * window::surface() const { return state->surface; }
   bool window::configured() const { return state->ready; }
   void window::acquire_external_presentation() { std::lock_guard<std::mutex> lock(state->presentation_mutex); ++state->external_presenters; }
   void window::release_external_presentation() { std::lock_guard<std::mutex> lock(state->presentation_mutex); if (state->external_presenters) --state->external_presenters; }
   void window::detach_events() { state->owner->send([&] { state->events = {}; }); }
   void window::set_title(const std::string & title) { state->owner->send([&] { xdg_toplevel_set_title(state->toplevel, title.c_str()); }); }
   void window::resize(int width, int height) { state->owner->send([&] { state->width = std::max(1, width); state->height = std::max(1, height); }); }
   void window::set_state(bool maximized, bool fullscreen, bool minimized)
   {
      state->owner->send([&] {
         if (maximized) xdg_toplevel_set_maximized(state->toplevel); else xdg_toplevel_unset_maximized(state->toplevel);
         if (fullscreen) xdg_toplevel_set_fullscreen(state->toplevel, nullptr); else xdg_toplevel_unset_fullscreen(state->toplevel);
         if (minimized) xdg_toplevel_set_minimized(state->toplevel);
         wl_surface_commit(state->surface);
      });
   }
   void window::hide() { state->owner->send([&] { wl_surface_attach(state->surface, nullptr, 0, 0); wl_surface_commit(state->surface); state->visible = false; state->ready = false; state->hidden = true; }); }
   void window::show()
   {
      state->owner->send([&] {
         if (!state->hidden) return;
         state->hidden = false;
         // An unmapped xdg surface needs a fresh bufferless configure handshake.
         wl_surface_commit(state->surface);
         if (wl_display_roundtrip(state->owner->state->display) < 0)
            throw std::runtime_error("Wayland remap configure failed");
      });
   }
   static void buffer_release(void * data, wl_buffer *) { static_cast<shm_buffer *>(data)->busy = false; }
   static const wl_buffer_listener buffer_listener = {buffer_release};
   bool window::present(const void * pixels, int width, int height, int stride)
   {
      if (!pixels || width <= 0 || height <= 0 || width > 32768 || height > 32768 || stride < width * 4 || size_t(width) * height * 4 > INT32_MAX) throw std::invalid_argument("Invalid Wayland image layout");
      bool presented = false;
      state->owner->send([&] {
         auto w = state.get();
         std::lock_guard<std::mutex> presentation(w->presentation_mutex);
         if (!w->ready || w->external_presenters) return;
         shm_buffer * buffer = nullptr;
         for (auto & b : w->buffers) if (!b->busy && b->width == width && b->height == height) { buffer = b.get(); break; }
         if (!buffer)
         {
            w->buffers.erase(std::remove_if(w->buffers.begin(), w->buffers.end(), [](const auto & b) { return !b->busy; }), w->buffers.end());
            if (w->buffers.size() >= 3) return;
            auto b = std::make_unique<shm_buffer>(); b->width = width; b->height = height; b->stride = width * 4; b->bytes = size_t(b->stride) * height;
            int fd = memfd_create("ca2-wayland-buffer", MFD_CLOEXEC);
            if (fd < 0) throw std::runtime_error("Cannot create Wayland shared memory");
            if (ftruncate(fd, b->bytes) < 0) { close(fd); throw std::runtime_error("Cannot size Wayland shared memory"); }
            b->data = mmap(nullptr, b->bytes, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
            if (b->data == MAP_FAILED) { close(fd); throw std::runtime_error("Cannot map Wayland shared memory"); }
            auto pool = wl_shm_create_pool(w->owner->state->shm, fd, b->bytes); close(fd);
            b->handle = wl_shm_pool_create_buffer(pool, 0, width, height, b->stride, WL_SHM_FORMAT_ARGB8888); wl_shm_pool_destroy(pool);
            wl_buffer_add_listener(b->handle, &buffer_listener, b.get()); buffer = b.get(); w->buffers.push_back(std::move(b));
         }
         for (int y = 0; y < height; ++y) memcpy(static_cast<char *>(buffer->data) + y * buffer->stride, static_cast<const char *>(pixels) + y * stride, width * 4);
         buffer->busy = true; wl_surface_attach(w->surface, buffer->handle, 0, 0); wl_surface_damage(w->surface, 0, 0, width, height); wl_surface_commit(w->surface); w->visible = true; presented = true;
      });
      return presented;
   }
   void window::start_move() { state->owner->send([&] { auto s = state->owner->state.get(); if (s->seat && s->serial) xdg_toplevel_move(state->toplevel, s->seat, s->serial); }); }
   void window::start_resize(uint32_t edges) { state->owner->send([&] { auto s = state->owner->state.get(); if (s->seat && s->serial) xdg_toplevel_resize(state->toplevel, s->seat, s->serial, edges); }); }
}
