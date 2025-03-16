#include "framework.h"
#include "http.h"


IMPLEMENT_FACTORY(nano_http_command_line)
{

   printf_line("IMPLEMENT FACTORY nano_http_command_line");

   pfactory->add_factory_item < ::command_line::nano::http::http, ::nano::http::http >();

}



