#include "automation.h"
#include "accessibility_atspi/automation.h"

namespace accessibility_gtk3
{
   accessibility::automation::element_pointer desktop()
   {
      return accessibility_atspi::desktop();
   }
}
