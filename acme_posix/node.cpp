//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"

#ifdef FREEBSD


#include <sys/types.h>
#include <sys/sysctl.h>

#endif


void init_pid_cs();


void term_pid_cs();


void os_post_quit();


void ansios_sigchld_handler(int sig);


void apex_application_run(const char * pszAppName, const char * pszProgName);


namespace acme
{


   namespace posix
   {


      node::node()
      {

         m_pAcmePosix = this;

         init_pid_cs();

      }


      node::~node()
      {

         //      if(m_pGtkSettingsDefault)
         //      {
         //
         //         g_object_unref(m_pGtkSettingsDefault);
         //
         //      }

         term_pid_cs();

      }


//      ::e_status node::call_async(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
//      {
//
//         throw ::interface_only_exception();
//
//         throw ::interface_only_exception();
//
//      }


//      ::e_status node::call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
//      {
//
//         throw ::interface_only_exception();
//
//         throw ::interface_only_exception();
//
//      }


      int node::node_init_check(int * pi, char *** ppz)
      {

         //auto iResult = gtk_init_check(pi, ppz);

         //return iResult;

         return 0;

      }


//      ::e_status node::start()
//      {
//
//
//         //      if (psystem->m_bGtkApp)
//         //      {
//         //
//         //         apex_application_run(psystem->m_XstrAppId, psystem->m_strProgName);
//         //
//         //      }
//         //      else
//         //      {
//         //
//         ////      g_set_application_name(psystem->m_XstrAppId);
//         ////
//         ////      g_set_prgname(psystem->m_strProgName);
//         ////
//         ////      //auto idle_source = g_idle_source_new();
//         ////
//         ////      //g_source_set_callback(idle_source, &linux_start_system, (::apex::system *) m_psystem, nullptr);
//         ////
//         ////      //g_source_attach(idle_source, g_main_context_default());
//         ////
//         ////      //int c = 2;
//         ////
//         ////      //const char * argv[]={"app", "--g-fatal-warnings"};
//         ////
//         ////#if !defined(__SANITIZE_ADDRESS__)
//         ////
//         ////      gtk_init_check(&psystem->m_argc, &psystem->m_argv);
//         ////
//         ////#endif
//
//         //         node_fork([this]()
//         //                   {
//         //
//         //                      //x11_add_idle_source();
//         //
//         //                      //x11_add_filter();
//         //
//         //                      auto pgtksettingsDefault = gtk_settings_get_default();
//         //
//         //                      if(pgtksettingsDefault)
//         //                      {
//         //
//         //
//         //                         m_pGtkSettingsDefault = G_OBJECT(pgtksettingsDefault);
//         //
//         //                         g_object_ref (m_pGtkSettingsDefault);
//         //
//         //                         gchar *theme_name = nullptr;
//         //
//         //                         g_object_get(m_pGtkSettingsDefault, "gtk-theme-name", &theme_name, NULL);
//         //
//         //                         m_strTheme = theme_name;
//         //
//         //                         g_free(theme_name);
//         //
//         //                         auto preturn = g_signal_connect_data(
//         //                            m_pGtkSettingsDefault,
//         //                            "notify::gtk-theme-name",
//         //                            G_CALLBACK(gtk_settings_gtk_theme_name_callback),
//         //                            this,
//         //                            NULL,
//         //                            G_CONNECT_AFTER);
//         //
//         //                         //g_object_ref(preturn);
//         //
//         //                         //printf("return %" PRIiPTR, preturn);
//         //
//         //                         //printf("return %" PRIiPTR, preturn);
//         //
//         //                      }
//         //
//         //
//         //                   });
//         //
//         //
//         //         //x11_add_filter();
//         //
//         //psystem->fork([]()
//         //     {
//         //
//         //      x11_main();
//         //
//         //     });
//         //
//         //         gtk_main();
//
//         //x11_main();
//
//         //}
//         //
//         //::parallelization::post_quit_and_wait(get_context_system(), one_minute());
//
//         return ::success;
//
//      }


      void node::initialize(::object * pobject)
      {

         //auto estatus =
         //
         //
         ::acme::node::initialize(pobject);

//         if(!estatus)
//         {
//
//            return estatus;
//
//         }
//
//         return estatus;

      }


      void node::install_sigchld_handler()
      {

//
//
//         struct sigaction sa;
//
//         __zero(sa);
//
//         sa.sa_handler = &ansios_sigchld_handler;
//
//         sigemptyset(&sa.sa_mask);
//
//         sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
//
//         sigaction(SIGCHLD, &sa, nullptr);

         //return ::success;

      }

   

      bool node::process_modules(string_array& stra, u32 processID)
      {

         throw ::interface_only_exception();

         return false;

      }


      bool node::load_modules_diff(string_array& straOld, string_array& straNew, const ::string & strExceptDir)
      {

         throw ::interface_only_exception();

         return false;

      }


      id_array node::get_pids()
      {

         throw ::interface_only_exception();

         return id_array();

      }


//      id_array node::module_path_get_pid(const char * pszModulePath, bool bModuleNameIsPropertyFormatted)
//      {
//
//         return ::acme::node::module_path_get_pid(pszModulePath, bModuleNameIsPropertyFormatted);
//
//
//      }


//      string node::module_path_from_pid(u32 pid)
//      {
//
//         return ::acme::node::module_path_from_pid(pid);
//
//      }


//      string node::command_line_from_pid(u32 pid)
//      {
//
//         return ::acme::node::command_line_from_pid(pid);
//
//      }


//      bool node::is_shared_library_busy(u32 processid, const string_array& stra)
//      {
//
//         return ::acme::node::is_shared_library_busy(processid, stra);
//
//      }

   
//      bool node::is_shared_library_busy(const string_array& stra)
//      {
//
//         return ::acme::node::is_shared_library_busy(stra);
//
//      }


      bool node::process_contains_module(string& strImage, ::u32 processID, const ::string & strLibrary)
      {

         return ::acme::node::process_contains_module(strImage, processID, strLibrary);

      }


      void node::shared_library_process(dword_array& dwa, string_array& straProcesses, const ::string & strLibrary)
      {

         throw ::interface_only_exception();

      }


      bool node::is_process_running(::u32 pid)
      {

         return ::acme::node::is_process_running(pid);

      }


      string node::get_environment_variable(const ::string & strEnvironmentVariable)
      {

         return ::getenv(strEnvironmentVariable);

      }


      string node::expand_environment_variables(const ::string & str)
      {

         return ::acme::node::expand_environment_variables(str);

      }

   
//   
//
//      array <::serial::port_info> node::list_serial_ports()
//      {
//
//         throw ::interface_only_exception();
//
//         return ::array <::serial::port_info>();
//
//      }


      void node::reboot()
      {

#ifdef LINUX

         dbus_do_power_off("Reboot");

#endif

         //return success;

      }

      // http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
      // http://stackoverflow.com/users/1275169/l3x
      int node::_get_proc_stat_core_count()
      {

#ifdef FREEBSD

         int mib[4];
         int numCPU;
         std::size_t len = sizeof(numCPU);

/* set the mib for hw.ncpu */
         mib[0] = CTL_HW;
#ifdef FREEBSD
         mib[1] = HW_NCPU;  // alternatively, try HW_NCPU;
#else
         mib[1] = HW_AVAILCPU;  // alternatively, try HW_NCPU;

#endif

/* get the number of CPUs from the system */
         sysctl(mib, 2, &numCPU, &len, NULL, 0);

         if (numCPU < 1)
         {
            mib[1] = HW_NCPU;
            sysctl(mib, 2, &numCPU, &len, NULL, 0);
            if (numCPU < 1)
               numCPU = 1;
         }

         return numCPU;

#else

         string str = m_psystem->m_pacmefile->as_string("/proc/stat");

         string_array stra;

         stra.add_lines(str);

         return (int) stra.predicate_get_count([](auto str) { return ::str::begins(str, "cpu"); });

#endif

      }



   } // namespace posix


} // namespace acme



