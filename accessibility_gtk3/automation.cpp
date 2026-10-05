#include "automation.h"
#include "accessibility_atspi/automation.h"
#include "acme/parallelization/critical_section.h"

namespace accessibility_gtk3
{
   accessibility::automation::element_pointer desktop()
   {
      return accessibility_atspi::desktop();
   }

   ::pointer<::accessibility::automation::menu_selection_result> select_application_menu(
      const ::accessibility::automation::menu_selection_request &request)
   {
      static ::critical_section transactions;
      ::critical_section_lock lock(&transactions);
      return ::accessibility::automation::select_application_menu(desktop(), request);
   }
}
