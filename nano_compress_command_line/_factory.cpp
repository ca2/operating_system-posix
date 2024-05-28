#include "framework.h"
#include "compress.h"


IMPLEMENT_FACTORY(nano_compress_command_line)
{

   pfactory->add_factory_item < ::command_line::nano::compress::compress, ::nano::compress::compress >();

}



