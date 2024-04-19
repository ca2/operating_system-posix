#include "framework.h"
#include "display.h"
#include "node.h"
#include "desktop_environment.h"
//#include "os_context.h"
#include "copydesk.h"
#include "notify_icon.h"
#if !defined(OPENBSD)
#include "appindicator.h"
#endif




//#if defined(OPENBSD)
#if 0
__FACTORY_EXPORT void windowing_xcb_factory(::factory::factory * pfactory);
#else
__FACTORY_EXPORT void windowing_x11_factory(::factory::factory * pfactory);
#endif
#if !defined(RASPBERRYPIOS)
__FACTORY_EXPORT void windowing_wayland_factory(::factory::factory * pfactory);
#endif


enum_display_type get_display_type();


__FACTORY_EXPORT void node_gtk_factory(::factory::factory * pfactory)
{

   ::node_gtk3::initialize_gtk();

   auto edisplaytype = get_display_type();

#if !defined(RASPBERRYPIOS) && !defined(FREEBSD) && !defined(__XFCE) && !defined(OPENBSD)

   if(edisplaytype == e_display_type_wayland)
   {

      //windowing_x11_factory(pfactory);

      windowing_wayland_factory(pfactory);

   }
   else
#endif
   {

// #if defined(OPENBSD)
//
//       windowing_xcb_factory(pfactory);
//
// #else

      windowing_x11_factory(pfactory);

// #endif

   }

   //pfactory->add_factory_item < ::node_gtk3::display, ::windowing::display > ();
//
//   pfactory->add_factory_item < ::node_gtk3::monitor, ::windowing::monitor > ();
   pfactory->add_factory_item < ::node_gtk3::copydesk, ::user::copydesk > ();
   pfactory->add_factory_item < ::node_gtk3::notify_icon, ::user::notify_icon > ();
#if !defined(OPENBSD)
   pfactory->add_factory_item < ::node_gtk3::appindicator, ::aura_posix::appindicator >();
#endif
//
//   pfactory->add_factory_item < ::node_gtk3::windowing, ::windowing::windowing >();

   pfactory->add_factory_item < ::node_gtk3::node, ::acme::node > ();


   pfactory->add_factory_item < ::node_gtk3::desktop_environment, ::windowing::desktop_environment > ();


   //pfactory->add_factory_item < ::node_gtk3::os_context, ::os_context >();


}



