// From idn on 2024-06-02 19:42 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "nano_dynamic_library_dl.h"


IMPLEMENT_FACTORY(nano_dynamic_library_dl)
{

   pfactory->add_factory_item < ::dl::nano::dynamic_library::dynamic_library, ::nano::dynamic_library::dynamic_library >();

}

typedef void FUNCTION_FACTORY(::factory::factory * pfactory);
using PFN_FACTORY = FUNCTION_FACTORY *;


PFN_FACTORY g_pnanodynamiclibrarydl __attribute((strong)) = &nano_dynamic_library_dl_factory;