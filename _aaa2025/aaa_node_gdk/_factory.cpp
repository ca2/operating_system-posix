#include "framework.h"
//#include "display.h"
#include "node.h"
#include "desktop_environment.h"
//#include "os_context.h"
//#include "copydesk.h"
//#include "notify_icon.h"
#include "wayland_windowing_system.h"
#include "x11_windowing_system.h"
#if !defined(OPENBSD)
//#include "appindicator.h"
#endif



//#define DISABLE_APPINDICATOR

//#if defined(OPENBSD)
#if 0
__FACTORY_EXPORT void windowing_xcb_factory(::factory::factory * pfactory);
#else
__FACTORY_EXPORT void windowing_x11_factory(::factory::factory * pfactory);
#endif
#if !defined(RASPBERRYPIOS)
__FACTORY_EXPORT void windowing_wayland_factory(::factory::factory * pfactory);
#endif

namespace nano
{
   namespace user
   {
      enum_display_type get_display_type();
   }//namespace user
} // namespace nano

__FACTORY_EXPORT void node_gdk_factory(::factory::factory * pfactory)
{

   //::node_gdk::initialize_gdk();

   auto edisplaytype = ::micro::get_display_type();

//#if !defined(RASPBERRYPIOS) && !defined(FREEBSD) && !defined(__XFCE) && !defined(OPENBSD)

#ifdef HAS_WAYLAND

   if(edisplaytype == e_display_type_wayland)
   {

      //windowing_x11_factory(pfactory);

      windowing_wayland_factory(pfactory);
pfactory->add_factory_item<::wayland::node_gdk::windowing_system, ::windowing::windowing_base>();
   }
   else
#endif
   {

// #if defined(OPENBSD)
//
//       windowing_xcb_factory(pfactory);
//
// #else
      //
      // windowing_x11_factory(pfactory);
      // pfactory->add_factory_item<::x11::node_gdk::windowing_system, ::windowing::windowing_base>();
// #endif

   }

   //pfactory->add_factory_item < ::node_gtk3::display, ::windowing::display > ();
//
//   pfactory->add_factory_item < ::node_gtk3::monitor, ::windowing::monitor > ();
   //pfactory->add_factory_item < ::node_gtk3::copydesk, ::user::copydesk > ();
   //pfactory->add_factory_item < ::node_gdk::notify_icon, ::user::notify_icon > ();
#if !defined(OPENBSD) && !defined(DISABLE_APPINDICATOR)
   //pfactory->add_factory_item < ::node_gtk3::appindicator, ::aura_posix::appindicator >();
#endif
//
//   pfactory->add_factory_item < ::node_gtk3::windowing, ::windowing::windowing >();

   pfactory->add_factory_item < ::node_gdk::node, ::platform::node > ();


   pfactory->add_factory_item < ::node_gdk::desktop_environment, ::windowing::desktop_environment > ();

   //pfactory->add_factory_item < ::x11::node_gdk::windowing_system, ::windowing::windowing_base > ();


   //pfactory->add_factory_item < ::node_gtk3::os_context, ::os_context >();


}



