#include "framework.h"
#include "application.h"
#include "../accessibility_posix/process_control.h"
#include "acme/platform/node.h"
#include <cerrno>
#include <csignal>
#include <unistd.h>


namespace accessibility_kde6
{


    application::application() //:
   //    m_bTargetProcessConfirmedAbsent(false)
   {

   }


   application::~application()
   {


   }

   //
   // void application::open_by_app_id(const ::scoped_string & scopedstrRepos,
   //                                  const ::scoped_string & scopedstrApp)
   // {
   //
   //    ::accessibility::application::open_by_app_id(scopedstrRepos, scopedstrApp);
   //
   //    m_pathModule = node()->get_executable_path_by_app_id(
   //       scopedstrRepos, scopedstrApp, false);
   //
   //    m_processidentifier = -1;
   //    m_processidentifiera.erase_all();
   //    m_bTargetProcessConfirmedAbsent = false;
   //
   //    if (!m_pathModule.has_character())
   //    {
   //
   //       return;
   //
   //    }
   //
   //    auto processidentifiera = node()->module_path_processes_identifiers(
   //       m_pathModule, false);
   //
   //    for (auto processidentifier : processidentifiera)
   //    {
   //
   //       if (processidentifier > 0 && processidentifier != (::process_identifier) ::getpid())
   //       {
   //
   //          m_processidentifiera.add(processidentifier);
   //
   //       }
   //
   //    }
   //
   //    if (m_processidentifiera.has_element())
   //    {
   //
   //       m_processidentifier = m_processidentifiera.first();
   //
   //    }
   //    else
   //    {
   //
   //       m_bTargetProcessConfirmedAbsent =
   //          !node()->is_application_running_good_effort(scopedstrRepos, scopedstrApp);
   //
   //    }
   //
   // }
   //
   //
   // ::e_status application::validate_target(
   //    ::process_identifier processidentifier, bool & bTargetGone)
   // {
   //
   //    bTargetGone = false;
   //
   //    if (processidentifier <= 0)
   //    {
   //
   //       return error_invalid_parameter;
   //
   //    }
   //
   //    if (processidentifier == (::process_identifier) ::getpid())
   //    {
   //
   //       return error_invalid_parameter;
   //
   //    }
   //
   //    if (::kill((pid_t) processidentifier, 0) != 0)
   //    {
   //
   //       if (errno == ESRCH)
   //       {
   //
   //          bTargetGone = true;
   //          return success;
   //
   //       }
   //
   //       if (errno == EPERM)
   //       {
   //
   //          return error_operation_not_permitted;
   //
   //       }
   //
   //       return error_failed;
   //
   //    }
   //
   //    auto pathProcessModule = node()->process_identifier_module_path(processidentifier);
   //
   //    ::string strProcessModule(pathProcessModule);
   //    ::string strExpectedModule(m_pathModule);
   //
   //    strProcessModule.ends_eat(" (deleted)");
   //    strExpectedModule.ends_eat(" (deleted)");
   //
   //    if (!strProcessModule.has_character())
   //    {
   //
   //       return error_failed;
   //
   //    }
   //
   //    if (strProcessModule != strExpectedModule)
   //    {
   //
   //       // The PID was reused after discovery. The original target is gone,
   //       // and signalling this new process would be unsafe.
   //       bTargetGone = true;
   //       return success;
   //
   //    }
   //
   //    return success;
   //
   // }
   //
   //
   // ::e_status application::signal_targets(int iSignal)
   // {
   //
   //    if (!m_processidentifiera.has_element())
   //    {
   //
   //       return m_bTargetProcessConfirmedAbsent ? success : error_failed;
   //
   //    }
   //
   //    bool bAnyTargetAlive = false;
   //
   //    for (auto processidentifier : m_processidentifiera)
   //    {
   //
   //       bool bTargetGone = false;
   //       auto estatus = validate_target(processidentifier, bTargetGone);
   //
   //       if (estatus.failed())
   //       {
   //
   //          return estatus;
   //
   //       }
   //
   //       if (bTargetGone)
   //       {
   //
   //          continue;
   //
   //       }
   //
   //       bAnyTargetAlive = true;
   //       estatus = process_control::send_signal(processidentifier, iSignal);
   //
   //       if (estatus.failed())
   //       {
   //
   //          return estatus;
   //
   //       }
   //
   //    }
   //
   //    if (!bAnyTargetAlive)
   //    {
   //
   //       m_bTargetProcessConfirmedAbsent = true;
   //       m_processidentifier = -1;
   //
   //    }
   //
   //    return success;
   //
   // }
   //
   //
   // ::e_status application::wait_for_targets(const class ::time & timeTimeout)
   // {
   //
   //    auto timeStart = ::time::now();
   //
   //    for (auto processidentifier : m_processidentifiera)
   //    {
   //
   //       auto timeElapsed = timeStart.elapsed();
   //
   //       if (timeElapsed >= timeTimeout)
   //       {
   //
   //          return error_timeout;
   //
   //       }
   //
   //       auto estatus = process_control::wait_for_exit(
   //          processidentifier, timeTimeout - timeElapsed);
   //
   //       if (estatus.failed())
   //       {
   //
   //          return estatus;
   //
   //       }
   //
   //    }
   //
   //    m_bTargetProcessConfirmedAbsent = true;
   //    m_processidentifier = -1;
   //
   //    return success;
   //
   // }
   //
   //
   // void application::post_exit()
   // {
   //
   //    auto estatus = signal_targets(SIGTERM);
   //
   //    if (estatus.failed())
   //    {
   //
   //       throw ::exception(estatus);
   //
   //    }
   //
   // }
   //
   //
   // ::e_status application::post_and_wait_to_exit(const class ::time & timeTimeout)
   // {
   //
   //    auto estatus = signal_targets(SIGTERM);
   //
   //    if (estatus.failed() || m_bTargetProcessConfirmedAbsent)
   //    {
   //
   //       return estatus;
   //
   //    }
   //
   //    return wait_for_targets(timeTimeout);
   //
   // }
   //
   //
   // ::e_status application::force_exit(const class ::time & timeTimeout)
   // {
   //
   //    auto estatus = signal_targets(SIGKILL);
   //
   //    if (estatus.failed() || m_bTargetProcessConfirmedAbsent)
   //    {
   //
   //       return estatus;
   //
   //    }
   //
   //    return wait_for_targets(timeTimeout);
   //
   // }


} // namespace accessibility_kde6
