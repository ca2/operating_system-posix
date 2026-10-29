#include "acme/_start.h"
#include "windowing_posix/_.h"
#include "backend.h"
#include "aura/windowing/monitor.h"
#include "aura/windowing/keyboard.h"
#include "aura/windowing/icon.h"
#include "aura/windowing/cursor.h"
#include "aura/user/user/text_composition_client.h"
namespace windowing_wayland
{
   class native_monitor : virtual public ::windowing::monitor
   {
   public:
      void initialize_monitor(::windowing::display * display, int index) override
      { m_iIndex = index; }
      ::i32_rectangle monitor_rectangle() override { return m_rectangle; }
      ::i32_rectangle workspace_rectangle() override { return m_rectangleWorkspace; }
   };
}
IMPLEMENT_FACTORY(windowing_wayland)
{
   pfactory->add_factory_item<::windowing_wayland::display, ::acme::windowing::display>();
   pfactory->add_factory_item<::windowing_wayland::window, ::acme::windowing::window>();
   pfactory->add_factory_item<::windowing_wayland::windowing, ::acme::windowing::windowing>();
   pfactory->add_factory_item<::windowing_wayland::display, ::windowing::display>();
   pfactory->add_factory_item<::windowing_wayland::window, ::windowing::window>();
   pfactory->add_factory_item<::windowing_wayland::windowing, ::windowing::windowing>();
   pfactory->add_factory_item<::windowing_wayland::graphics, ::graphics::graphics>();
   pfactory->add_factory_item<::windowing_wayland::native_monitor, ::windowing::monitor>();
   pfactory->add_factory_item<::windowing::keyboard>();
   pfactory->add_factory_item<::windowing::icon>();
   pfactory->add_factory_item<::windowing::cursor>();
   pfactory->add_factory_item<::user::text_composition_client>();
}
