#include "framework.h"
#include "display.h"
#include "node.h"
#include "desktop_environment.h"
//#include "os_context.h"


__FACTORY_EXPORT void windowing_gtk4_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_gtk_factory(::factory::factory * pfactory)
{

   //::node_gtk4::initialize_gtk();


   windowing_gtk4_factory(pfactory);


//   ::string strSessionType = getenv("XDG_SESSION_TYPE");
//
//   strSessionType.make_lower();
//
//   printf("XDG_SESSION_TYPE %s\n", strSessionType.c_str());
//
//#if !defined(RASPBERRYPIOS) && !defined(FREEBSD) && !defined(OPENBSD)
//   if(strSessionType == "wayland")
//   {
//
//      //windowing_x11_factory(pfactory);
//
//      windowing_wayland_factory(pfactory);
//
//   }
//   else
//#endif
//   {
//
//      //windowing_xcb_factory(pfactory);
//
//      windowing_x11_factory(pfactory);
//
//   }

   //pfactory->add_factory_item < ::node_gtk4::display, ::windowing::display > ();
//
//   pfactory->add_factory_item < ::node_gtk4::monitor, ::windowing::monitor > ();
//   pfactory->add_factory_item < ::node_gtk4::copydesk, ::user::copydesk > ();
//   pfactory->add_factory_item < ::node_gtk4::notify_icon, ::user::notify_icon > ();
//   pfactory->add_factory_item < ::node_gtk4::appindicator, ::aura::posix::appindicator >();
//
//   pfactory->add_factory_item < ::node_gtk4::windowing, ::windowing::windowing >();

   pfactory->add_factory_item < ::node_gtk4::node, ::acme::node > ();


   pfactory->add_factory_item < ::node_gtk4::desktop_environment, ::windowing::desktop_environment > ();


   //pfactory->add_factory_item < ::node_gtk4::os_context, ::os_context >();


}



