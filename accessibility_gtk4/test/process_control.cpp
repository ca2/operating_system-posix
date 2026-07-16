#include "acme/framework.h"
#include "operating_system/operating_system-posix/accessibility_gtk4/process_control.h"
#include <csignal>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>


namespace
{


   class child_process
   {
   public:


      pid_t m_pid = -1;
      std::thread m_threadReaper;


      explicit child_process(bool bIgnoreTermination)
      {

         int pipeReady[2];

         if (::pipe(pipeReady) != 0)
         {

            return;

         }

         m_pid = ::fork();

         if (m_pid == 0)
         {

            ::close(pipeReady[0]);

            if (bIgnoreTermination)
            {

               ::signal(SIGTERM, SIG_IGN);

            }

            char chReady = 1;
            (void) ::write(pipeReady[1], &chReady, 1);
            ::close(pipeReady[1]);

            for (;;)
            {

               ::pause();

            }

         }

         ::close(pipeReady[1]);

         char chReady = 0;
         (void) ::read(pipeReady[0], &chReady, 1);
         ::close(pipeReady[0]);

         if (m_pid > 0)
         {

            m_threadReaper = std::thread([this]()
            {

               int iStatus = 0;
               (void) ::waitpid(m_pid, &iStatus, 0);

            });

         }

      }


      ~child_process()
      {

         if (m_pid > 0)
         {

            (void) ::kill(m_pid, SIGKILL);

         }

         if (m_threadReaper.joinable())
         {

            m_threadReaper.join();

         }

      }


   };


} // namespace


int main()
{

   using namespace accessibility_gtk4::process_control;

   child_process graceful(false);

   if (graceful.m_pid <= 0 || send_signal(graceful.m_pid, SIGTERM) != success)
   {

      return 1;

   }

   if (wait_for_exit(graceful.m_pid, 2_s) != success)
   {

      return 2;

   }

   child_process resistant(true);

   if (resistant.m_pid <= 0 || send_signal(resistant.m_pid, SIGTERM) != success)
   {

      return 3;

   }

   if (wait_for_exit(resistant.m_pid, 100_ms) != error_timeout)
   {

      return 4;

   }

   if (send_signal(resistant.m_pid, SIGKILL) != success)
   {

      return 5;

   }

   if (wait_for_exit(resistant.m_pid, 2_s) != success)
   {

      return 6;

   }

   return 0;

}
