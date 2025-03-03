#include "framework.h"
#include "copydesk.h"
#include "notify_icon.h"
#include "appindicator.h"
#include "desktop_environment.h"
#include "node.h"
//#include "windowing.h"


// __FACTORY_EXPORT void windowing_xcb_factory(::factory::factory * pfactory);
// __FACTORY_EXPORT void windowing_x11_factory(::factory::factory * pfactory);
// #if !defined(RASPBERRYPIOS)
// __FACTORY_EXPORT void windowing_wayland_factory(::factory::factory * pfactory);
// #endif

__FACTORY_EXPORT void node_q_factory(::factory::factory * pfactory)
{
//
////   __FACTORY_EXPORT void windowing_x11_factory(::factory::factory * pfactory);
////
////
////   __FACTORY_EXPORT void node_gtk_factory(::factory::factory * pfactory)
////   {
//
//   ::string strSessionType = getenv("XDG_SESSION_TYPE");
//
//   strSessionType.make_lower();
//
//   printf("XDG_SESSION_TYPE %s\n", strSessionType.c_str());
//
//// #if !defined(RASPBERRYPIOS) && !defined(FREEBSD) && !defined(OPENBSD)
////
////    if(strSessionType == "wayland")
////    {
////
////       //windowing_x11_factory(pfactory);
////
////       windowing_wayland_factory(pfactory);
////
////    }
////    else
////    #endif
////    {
////
////       //windowing_xcb_factory(pfactory);
////
////       windowing_xcb_factory(pfactory);
////
////    }
//// //   ::string strSessionType = getenv("XDG_SESSION_TYPE");
//// //
//// //   strSessionType.make_lower();
//// //
//// //   printf("XDG_SESSION_TYPE %s\n", strSessionType.c_str());
//// //
//// //   if(strSessionType == "x11")
//// //   {
//// //
//// //      windowing_xcb_factory(pfactory);
//// //
//// //   }
//// //   else
//// //   {
//// //
//// //      //windowing_x11_factory(pfactory);
//// //
//// //      windowing_xcb_factory(pfactory);
//// //
//// //   }
////
////    printf("node_kde factory\n");

   ////pfactory->add_factory_item < ::node_kde::display, ::windowing::display > ();

   ////pfactory->add_factory_item < ::node_kde::monitor, ::windowing::monitor > ();
   pfactory->add_factory_item < ::node_q::copydesk, ::user::copydesk > ();
   ////pfactory->add_factory_item < ::node_lxq2::notify_icon, ::user::notify_icon > ();
   //pfactory->add_factory_item < ::node_lxq2::appindicator, ::aura_posix::appindicator >();

   ////pfactory->add_factory_item < ::node_lxq2::desktop_environment, ::windowing::desktop_environment >();

   pfactory->add_factory_item < ::node_q::node, ::platform::node > ();

}



