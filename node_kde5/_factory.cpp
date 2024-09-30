#include "framework.h"
#include "copydesk.h"
#include "notify_icon.h"
#include "appindicator.h"
#include "desktop_environment.h"
#include "node.h"
//#include "windowing_system_wayland/windowing_system.h"
//#include "windowing_system_xcb/windowing_system.h"
//#include "windowing_system_kde5/windowing_system.h"

//
//namespace nano
//{
//
//
//   namespace user
//   {
//
//      void initialize_display_type(enum_display_type edisplaytype);
//
//   } // namespace user
//
//}// namespace nano
//

// __FACTORY_EXPORT void windowing_xcb_factory(::factory::factory * pfactory);
// __FACTORY_EXPORT void windowing_x11_factory(::factory::factory * pfactory);
// #if !defined(RASPBERRYPIOS)
// __FACTORY_EXPORT void windowing_wayland_factory(::factory::factory * pfactory);
// #endif


__FACTORY_EXPORT void windowing_kde5_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_kde_factory(::factory::factory * pfactory)
{


   //windowing_kde5_factory(pfactory);


//   __FACTORY_EXPORT void windowing_x11_factory(::factory::factory * pfactory);
//
//
//   __FACTORY_EXPORT void node_gtk_factory(::factory::factory * pfactory)
//   {

//    auto edisplaytype = ::nano::user::get_display_type();
//
// #if !defined(RASPBERRYPIOS) && !defined(FREEBSD) && !defined(__XFCE) && !defined(OPENBSD)
//
//    if(edisplaytype == e_display_type_wayland)
//    {
//
//       //windowing_x11_factory(pfactory);
//
//       windowing_wayland_factory(pfactory);
//       pfactory->add_factory_item<::wayland::windowing_system, ::windowing_system::windowing_system>();
//    }
//    else
// #endif
//    {
//
// // #if defined(OPENBSD)
// //
// //       windowing_xcb_factory(pfactory);
// //
// // #else
//
//       windowing_xcb_factory(pfactory);
//       pfactory->add_factory_item<::xcb::windowing_system, ::windowing_system::windowing_system>();
// // #endif
//
//    }
   //pfactory->add_factory_item<::windowing_system_kde5::windowing_system, ::windowing_system::windowing_system>();
//   ::string strSessionType = getenv("XDG_SESSION_TYPE");
//
//   strSessionType.make_lower();
//
//   printf("XDG_SESSION_TYPE %s\n", strSessionType.c_str());
//
//   if(strSessionType == "x11")
//   {
//
//      windowing_xcb_factory(pfactory);
//
//   }
//   else
//   {
//
//      //windowing_x11_factory(pfactory);
//
//      windowing_xcb_factory(pfactory);
//
//   }

   printf("node_kde factory\n");

   //pfactory->add_factory_item < ::node_kde::display, ::windowing::display > ();

   //pfactory->add_factory_item < ::node_kde::monitor, ::windowing::monitor > ();
   pfactory->add_factory_item < ::node_kde5::copydesk, ::user::copydesk > ();
   pfactory->add_factory_item < ::node_kde5::notify_icon, ::user::notify_icon > ();
   pfactory->add_factory_item < ::node_kde5::appindicator, ::aura_posix::appindicator >();

   pfactory->add_factory_item < ::node_kde5::desktop_environment, ::windowing::desktop_environment >();

   pfactory->add_factory_item < ::node_kde5::node, ::acme::node > ();

}



