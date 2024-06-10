// From nano_dynamic_library_dl on 2024-06-02 18:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "nano_account_posix.h"


IMPLEMENT_FACTORY(nano_account_posix)
{

   pfactory->add_factory_item < ::posis::nano::account::account, ::nano::account::account >();

}



