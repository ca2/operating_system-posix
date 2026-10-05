#pragma once
#include "acme/accessibility/selection.h"

namespace accessibility_gtk3
{
   // Cross-process GTK accessibility uses AT-SPI. Call from an automation
   // worker/helper, outside the application's GTK main thread.
   accessibility::automation::element_pointer desktop();
   ::pointer<::accessibility::automation::menu_selection_result> select_application_menu(
      const ::accessibility::automation::menu_selection_request &request);
}
