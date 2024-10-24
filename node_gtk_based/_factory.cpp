#include "framework.h"
//#include "display.h"
//#include "monitor.h"
#include "windowing.h"
#include "node.h"
#include "desktop_environment.h"


__FACTORY_EXPORT void node_gtk_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_gtk_based_factory(::factory::factory * pfactory)
{

   node_gtk_factory(pfactory);

   //pfactory->add_factory_item < ::node_gtk_based::display, ::windowing::display > ();

   //pfactory->add_factory_item < ::node_gtk_based::monitor, ::windowing::monitor > ();
   //pfactory->add_factory_item < ::node_gtk_based::copydesk, ::user::copydesk > ();
   //pfactory->add_factory_item < ::node_gtk_based::notify_icon, ::user::notify_icon > ();
   //pfactory->add_factory_item < ::node_gtk_based::appindicator, ::aura_posix::appindicator >();

   //pfactory->add_factory_item < ::node_gtk_based::windowing, ::windowing::windowing >();

   pfactory->add_factory_item < ::node_gtk_based::node, ::platform::node > ();

   pfactory->add_factory_item < ::node_gtk_based::desktop_environment, ::windowing::desktop_environment > ();

}



