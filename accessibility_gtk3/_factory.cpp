#include "automation.h"
#include "acme/_start.h"
#include "acme/_.h"
#include "acme/accessibility/accessibility.h"

namespace accessibility_gtk3
{
   class accessibility : public ::accessibility::accessibility
   {
   public:
      ::accessibility::automation::element_pointer automation_desktop() override
      {
         return accessibility_gtk3::desktop();
      }
   };
}

IMPLEMENT_FACTORY(accessibility_gtk3)
{
   pfactory->add_factory_item<::accessibility_gtk3::accessibility, ::accessibility::accessibility>();
}
