#include "framework.h"
#include "accessibility.h"
#include "application.h"
#include "main_window.h"
#include "acme/accessibility/accessibility.h"


IMPLEMENT_FACTORY(accessibility_kde6)
{


   pfactory->add_factory_item <
      ::accessibility_kde6::accessibility,
      ::accessibility::accessibility >();

   pfactory->add_factory_item <
      ::accessibility_kde6::application,
      ::accessibility::application >();

   pfactory->add_factory_item <
      ::accessibility_kde6::main_window,
      ::accessibility::main_window >();


}
