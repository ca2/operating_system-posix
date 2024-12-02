#include "framework.h"
//#include "display.h"
#include "node.h"
#include "desktop_environment.h"
//#include "os_context.h"
#include "copydesk.h"
#include "notify_icon.h"
#if !defined(OPENBSD) && !defined(NETBSD)
#include "appindicator.h"
#endif



////#define DISABLE_APPINDICATOR
//
////#if defined(OPENBSD)
//#if 0
//__FACTORY_EXPORT void windowing_xcb_factory(::factory::factory * pfactory);
//#else
//__FACTORY_EXPORT void windowing_x11_factory(::factory::factory * pfactory);
//#endif
//#if !defined(RASPBERRYPIOS)
//__FACTORY_EXPORT void windowing_wayland_factory(::factory::factory * pfactory);
//#endif

//namespace nano
//{
//   namespace user
//   {
//      enum_display_type get_display_type();
//   }//namespace user
//} // namespace nano

//__FACTORY_EXPORT void node_gdk_factory(::factory::factory * pfactory);

//__FACTORY_EXPORT void windowing_gtk3_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_gtk3_factory(::factory::factory * pfactory)
{

   //::node_gtk3::initialize_gtk();


   //node_gdk_factory(pfactory);

   //windowing_gtk3_factory(pfactory);


//   auto edisplaytype = ::micro::get_display_type();
//
//#if !defined(RASPBERRYPIOS) && !defined(FREEBSD) && !defined(__XFCE) && !defined(OPENBSD)
//
//   if(edisplaytype == e_display_type_wayland)
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
//// #if defined(OPENBSD)
////
////       windowing_xcb_factory(pfactory);
////
//// #else
//
//      windowing_x11_factory(pfactory);
//
//// #endif
//
//   }

   //pfactory->add_factory_item < ::node_gtk3::display, ::windowing::display > ();
//
//   pfactory->add_factory_item < ::node_gtk3::monitor, ::windowing::monitor > ();
   pfactory->add_factory_item < ::node_gtk3::copydesk, ::user::copydesk > ();
   pfactory->add_factory_item < ::node_gtk3::notify_icon, ::user::notify_icon > ();
#if !defined(OPENBSD) && !defined(DISABLE_APPINDICATOR) && !defined(NETBSD)
   pfactory->add_factory_item < ::node_gtk3::appindicator, ::aura_posix::appindicator >();
#endif
//
//   pfactory->add_factory_item < ::node_gtk3::windowing, ::windowing::windowing >();

   pfactory->add_factory_item < ::node_gtk3::node, ::platform::node > ();


   pfactory->add_factory_item < ::node_gtk3::desktop_environment, ::windowing::desktop_environment > ();


   //pfactory->add_factory_item < ::node_gtk3::os_context, ::os_context >();


}



