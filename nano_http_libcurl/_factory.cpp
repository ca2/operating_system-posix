#include "framework.h"
#include "http.h"


IMPLEMENT_FACTORY(nano_http_libcurl)
{

   pfactory->add_factory_item < ::curl::nano::http::http, ::nano::http::http >();

}



