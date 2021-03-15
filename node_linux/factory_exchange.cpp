#include "framework.h"


extern "C"
void node_gnome_factory_exchange()
{

   create_factory < ::node_linux::node, ::acme::node > ();

}



