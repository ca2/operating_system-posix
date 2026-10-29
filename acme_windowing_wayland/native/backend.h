#pragma once
#include "acme/windowing/display.h"
#include "acme/windowing/window.h"
#include "acme/windowing/windowing.h"
#include "runtime.h"
#include "acme/windowing/native_surface_provider.h"

#if defined(_acme_windowing_wayland_project)
#define CLASS_DECL_NATIVE_WAYLAND CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NATIVE_WAYLAND CLASS_DECL_IMPORT
#endif
namespace native_wayland
{
   class CLASS_DECL_NATIVE_WAYLAND display : virtual public ::acme::windowing::display
   {
   public:
      std::shared_ptr<::ca2_wayland::runtime> m_runtime;
      void open_display() override;
      bool is_display_opened() const override;
      bool is_wayland() override { return true; }
      void _enumerate_monitors() override;
      void display_send(const ::procedure & procedure) override;
      void display_post(const ::procedure & procedure) override;
      void destroy() override;
      void * native_wayland_display() override;
   };
   class CLASS_DECL_NATIVE_WAYLAND window : virtual public ::acme::windowing::window,
      virtual public ::acme::windowing::native_surface_provider
   {
   public:
      std::shared_ptr<::ca2_wayland::runtime> m_runtime;
      std::shared_ptr<::ca2_wayland::window> m_native;
      bool m_visible = false;
      bool m_focused = false;
      void create_window() override;
      void _create_window() override;
      void destroy() override;
      bool is_window() override;
      bool _is_window() override;
      void user_send(const ::procedure & procedure) override;
      void user_post(const ::procedure & procedure) override;
      void main_send(const ::procedure & procedure) override;
      void main_post(const ::procedure & procedure) override;
      ::acme::windowing::display * get_display() override;
      void show_window(::user_interface::enum_show_window state) override;
      void * native_wayland_surface() override;
      void acquire_external_presentation() override { if (m_native) m_native->acquire_external_presentation(); }
      void release_external_presentation() override { if (m_native) m_native->release_external_presentation(); }
      bool native_surface_configured() const override { return m_native && m_native->configured(); }
      void set_size_unlocked(const ::i32_size & size) override;
      virtual void native_configure(int width, int height);
      virtual void native_close();
      virtual void native_motion(double x, double y);
      virtual void native_button(uint32_t button, bool pressed, double x, double y);
      virtual void native_scroll(double delta);
      virtual void native_key(uint32_t code, uint32_t symbol, bool pressed, const std::string & text);
      virtual void native_focus(bool active);
   };
   class CLASS_DECL_NATIVE_WAYLAND windowing : virtual public ::acme::windowing::windowing
   {
   public:
      void initialize_windowing() override;
      bool init_threads() override { return true; }
      ::windowing::enum_windowing calculate_ewindowing() override;
      void main_send(const ::procedure & procedure) override;
      void main_post(const ::procedure & procedure) override;
      void user_send(const ::procedure & procedure) override;
      void user_post(const ::procedure & procedure) override;
      void windowing_application_on_system_start() override;
      void run() override;
   };
}
