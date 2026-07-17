#pragma once


//#include "../accessibility_gtk4/_.h"


namespace accessibility_posix::process_control
{


   CLASS_DECL_ACCESSIBILITY_POSIX ::e_status send_signal(
      ::process_identifier processidentifier, int iSignal);

   CLASS_DECL_ACCESSIBILITY_POSIX ::e_status wait_for_exit(
      ::process_identifier processidentifier, const class ::time & timeTimeout);


} // namespace accessibility_posix::process_control
