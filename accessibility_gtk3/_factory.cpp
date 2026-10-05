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

      ::pointer<::accessibility::automation::menu_selection_result> select_application_menu(
         const ::accessibility::automation::menu_selection_request &request) override
      {
         // Serialize full transactions in the application process. Ambient's
         // ambient-change callbacks already run on ca2 worker tasks.
         return accessibility_gtk3::select_application_menu(request);
      }
   };
}

IMPLEMENT_FACTORY(accessibility_gtk3)
{
   pfactory->add_factory_item<::accessibility_gtk3::accessibility, ::accessibility::accessibility>();
}
