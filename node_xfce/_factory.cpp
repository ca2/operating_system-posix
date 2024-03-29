#include "framework.h"
//#include "display.h"
//#include "monitor.h"
//#include "appindicator.h"
//#include "notify_icon.h"
//#include "windowing.h"
#include "node.h"

__FACTORY_IMPORT void node_gtk_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_xfce_factory(::factory::factory * pfactory)
{

   node_gtk_factory(pfactory);

//   pfactory->add_factory_item < ::node_xfce::display, ::windowing::display > ();
//
//   pfactory->add_factory_item < ::node_xfce::monitor, ::windowing::monitor > ();
//
//   pfactory->add_factory_item < ::node_xfce::windowing, ::windowing::windowing >();

   pfactory->add_factory_item < ::node_xfce::node, ::acme::node > ();


}



