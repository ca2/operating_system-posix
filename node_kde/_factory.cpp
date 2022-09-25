#include "framework.h"
#include "copydesk.h"
#include "notify_icon.h"
#include "appindicator.h"
#include "desktop_environment.h"
#include "node.h"


__FACTORY_EXPORT void windowing_xcb_factory(::factory::factory * pfactory);
__FACTORY_EXPORT void windowing_x11_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_kde_factory(::factory::factory * pfactory)
{


   ::string strSessionType = getenv("XDG_SESSION_TYPE");

   strSessionType.make_lower();

   if(strSessionType == "x11")
   {

      windowing_xcb_factory(pfactory);

   }
   else
   {

      windowing_x11_factory(pfactory);

   }

   //pfactory->add_factory_item < ::node_kde::display, ::windowing::display > ();

   //pfactory->add_factory_item < ::node_kde::monitor, ::windowing::monitor > ();
   pfactory->add_factory_item < ::node_kde::copydesk, ::user::copydesk > ();
   pfactory->add_factory_item < ::node_kde::notify_icon, ::user::notify_icon > ();
   pfactory->add_factory_item < ::node_kde::appindicator, ::aura_posix::appindicator >();

   pfactory->add_factory_item < ::node_kde::desktop_environment, ::windowing::desktop_environment >();

   pfactory->add_factory_item < ::node_kde::node, ::acme::node > ();

}



