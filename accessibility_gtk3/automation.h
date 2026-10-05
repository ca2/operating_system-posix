#pragma once
#include "acme/accessibility/automation.h"

namespace accessibility_gtk3
{
   // Cross-process GTK accessibility uses AT-SPI. Call from an automation
   // worker/helper, outside the application's GTK main thread.
   accessibility::automation::element_pointer desktop();
}
