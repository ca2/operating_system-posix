#pragma once
#include "acme/accessibility/automation.h"

namespace accessibility_atspi
{
   // Invoke from one automation worker/process, outside the GUI thread.
   accessibility::automation::element_pointer desktop();
}
