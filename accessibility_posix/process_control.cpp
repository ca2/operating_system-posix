#include "framework.h"
#include "process_control.h"
#include <cerrno>
#include <csignal>


namespace accessibility_posix::process_control
{


   ::e_status send_signal(::process_identifier processidentifier, int iSignal)
   {

      if (processidentifier <= 0)
      {

         return error_invalid_parameter;

      }

      if (::kill((pid_t) processidentifier, iSignal) == 0)
      {

         return success;

      }

      if (errno == ESRCH)
      {

         return success;

      }

      if (errno == EPERM)
      {

         return error_operation_not_permitted;

      }

      return error_failed;

   }


   ::e_status wait_for_exit(
      ::process_identifier processidentifier, const class ::time & timeTimeout)
   {

      if (processidentifier <= 0)
      {

         return error_invalid_parameter;

      }

      auto timeStart = ::time::now();

      for (;;)
      {

         if (::kill((pid_t) processidentifier, 0) != 0)
         {

            if (errno == ESRCH)
            {

               return success;

            }

            if (errno != EPERM)
            {

               return error_failed;

            }

         }

         auto timeElapsed = timeStart.elapsed();

         if (timeElapsed >= timeTimeout)
         {

            return error_timeout;

         }

         auto timeRemaining = timeTimeout - timeElapsed;

         preempt(timeRemaining < 100_ms ? timeRemaining : 100_ms);

      }

   }


} // namespace accessibility_posix::process_control
