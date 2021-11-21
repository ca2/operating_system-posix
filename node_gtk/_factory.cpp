#include "framework.h"


__FACTORY_EXPORT void windowing_x11_factory(::factory::factory * pfactory);


__FACTORY_EXPORT void node_gtk_factory(::factory::factory * pfactory)
{

   windowing_x11_factory(pfactory);

//   pfactory->add_factory_item < ::node_gtk::display, ::windowing::display > ();
//
//   pfactory->add_factory_item < ::node_gtk::monitor, ::windowing::monitor > ();
//   pfactory->add_factory_item < ::node_gtk::copydesk, ::user::copydesk > ();
//   pfactory->add_factory_item < ::node_gtk::notify_icon, ::user::notify_icon > ();
//   pfactory->add_factory_item < ::node_gtk::appindicator, ::aura::posix::appindicator >();
//
//   pfactory->add_factory_item < ::node_gtk::windowing, ::windowing::windowing >();

   pfactory->add_factory_item < ::node_gtk::node, ::acme::node > ();


}



