#pragma once


#include "_.h"


namespace accessibility_gtk4::process_control
{


   CLASS_DECL_ACCESSIBILITY_GTK4 ::e_status send_signal(
      ::process_identifier processidentifier, int iSignal);

   CLASS_DECL_ACCESSIBILITY_GTK4 ::e_status wait_for_exit(
      ::process_identifier processidentifier, const class ::time & timeTimeout);


} // namespace accessibility_gtk4::process_control
