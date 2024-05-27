#include "framework.h"
#include "message_box.h"


IMPLEMENT_FACTORY(message_box_motif)
{


   pfactory->add_factory_item < ::motif::message_box, ::operating_system::message_box >();

}



