#include "framework.h"
#include "display.h"
#include "monitor.h"
#include "copydesk.h"
#include "notify_icon.h"
#include "appindicator.h"
#include "windowing.h"
#include "node.h"
#include "desktop_environment.h"


__FACTORY_EXPORT void node_gtk_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_gnome_factory(::factory::factory * pfactory)
{

   node_gtk_factory(pfactory);

   pfactory->add_factory_item < ::node_gnome::display, ::windowing::display > ();

   pfactory->add_factory_item < ::node_gnome::monitor, ::windowing::monitor > ();
   pfactory->add_factory_item < ::node_gnome::copydesk, ::user::copydesk > ();
   pfactory->add_factory_item < ::node_gnome::notify_icon, ::user::notify_icon > ();
   pfactory->add_factory_item < ::node_gnome::appindicator, ::aura_posix::appindicator >();

   pfactory->add_factory_item < ::node_gnome::windowing, ::windowing::windowing >();

   pfactory->add_factory_item < ::node_gnome::node, ::acme::node > ();

   pfactory->add_factory_item < ::node_gnome::desktop_environment, ::windowing::desktop_environment > ();

}



