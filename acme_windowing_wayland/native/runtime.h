#pragma once
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

struct wl_display;
struct wl_surface;

namespace ca2_wayland
{
   struct rectangle { int x = 0, y = 0, width = 0, height = 0; };
   struct output { rectangle bounds; int scale = 1; std::string name; };
   struct callbacks
   {
      std::function<void(int, int)> configure;
      std::function<void()> close;
      std::function<void(double, double)> motion;
      std::function<void(uint32_t, bool, double, double)> button;
      std::function<void(double)> scroll;
      std::function<void(uint32_t, uint32_t, bool, const std::string &)> key;
      std::function<void(bool)> focus;
   };
   class runtime;
   class __attribute__((visibility("default"))) window
   {
   public:
      struct impl;
      std::unique_ptr<impl> state;
      ~window();
      wl_surface * surface() const;
      void set_title(const std::string & title);
      void resize(int width, int height);
      void set_state(bool maximized, bool fullscreen, bool minimized);
      void hide();
      void show();
      void detach_events();
      void acquire_external_presentation();
      void release_external_presentation();
      // False means backpressure, an unconfigured surface, or external ownership.
      bool present(const void * pixels, int width, int height, int stride);
      void start_move();
      void start_resize(uint32_t edges);
      bool configured() const;
   private:
      friend class runtime;
      explicit window(std::unique_ptr<impl> state);
   };
   class __attribute__((visibility("default"))) runtime
   {
   public:
      struct impl;
      std::unique_ptr<impl> state;
      runtime();
      ~runtime();
      runtime(const runtime &) = delete;
      runtime &operator=(const runtime &) = delete;
      wl_display * display() const;
      std::vector<output> outputs();
      std::shared_ptr<window> create_window(int width, int height,
         const std::string & title, const std::string & appId, callbacks events);
      void send(std::function<void()> function);
      void post(std::function<void()> function);
      bool is_current() const;
      bool connected() const;
   };
}
