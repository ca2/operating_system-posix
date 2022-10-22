//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme_file.h"
#include "acme_directory.h"
#include "acme/primitive/primitive/memory.h"
#include <signal.h>

#ifdef FREEBSD


#include <sys/types.h>
#include <sys/sysctl.h>

#endif

//
//struct sigaction g_sigactionFpe;
//
//struct sigaction g_sigactionFpeOld;



#if defined(__clang__) && !defined(ANDROID)
::string clang_backtrace();
#endif


//void sigfpe_sigaction(int signum, siginfo_t * psiginfo, void * p)
//{
//
//   throw standard_sigfpe(signum, psiginfo, p);
//
//}
//
//
//
//void install_sigfpe_handler()
//{
//
//   __zero(g_sigactionFpe);
//
//   __zero(g_sigactionFpeOld);
//
//   g_sigactionFpe.sa_sigaction = &sigfpe_sigaction;
//
//   sigemptyset(&g_sigactionFpe.sa_mask);
//
//   g_sigactionFpe.sa_flags = SA_SIGINFO | SA_NODEFER;
//
//   sigaction(SIGFPE, &g_sigactionFpe, &g_sigactionFpeOld);
//
//}
//
//
//void uninstall_sigfpe_handler()
//{
//
//   sigaction(SIGFPE, &g_sigactionFpeOld, nullptr);
//
//}



void init_chldstatus_cs();


void term_chldstatus_cs();


void os_post_quit();


void ansios_sigchld_handler(int sig);


void apex_application_run(const char * pszAppName, const char * pszProgName);


namespace acme_posix
{


   node::node()
   {

      m_pAcmePosix = this;

      init_chldstatus_cs();

      //install_sigfpe_handler();

   }


   node::~node()
   {

      //      if(m_pGtkSettingsDefault)
      //      {
      //
      //         g_object_unref(m_pGtkSettingsDefault);
      //
      //      }

      //uninstall_sigfpe_handler();

      term_chldstatus_cs();

   }


//      ::e_status node::call_async(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
//      {
//
//         throw ::interface_only();
//
//         throw ::interface_only();
//
//      }


//      ::e_status node::call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, const ::duration & durationTimeout, ::property_set & set)
//      {
//
//         throw ::interface_only();
//
//         throw ::interface_only();
//
//      }


   int node::node_init_check(int * pi, char *** ppz)
   {

      //auto iResult = gtk_init_check(pi, ppz);

      //return iResult;

      return 0;

   }


   void node::dbus_init()
   {



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

   // void node::call_async see process.cpp
   // void node::call_sync see process.cpp
   // void node::create_process see process.cpp
   // void node::_create_process3 see process.cpp
   // void node::run_silent see process.cpp

   // void node::module_path_from_pid see process.cpp
   // void node::module_path_get_pid see process.cpp
   // void node::command_line_from_pid see process.cpp
   // void node::is_shared_library_busy see process.cpp
   // void node::is_shared_library_busy see process.cpp

   bool node::is_process_running(::u32 pid)
   {

      return ::acme::node::is_process_running(pid);

   }


   bool node::process_modules(string_array& stra, u32 processID)
   {

      throw ::interface_only();

      return false;

   }


   bool node::load_modules_diff(string_array& straOld, string_array& straNew, const ::string & strExceptDir)
   {

      throw ::interface_only();

      return false;

   }


   atom_array node::get_pids()
   {

      throw ::interface_only();

      return atom_array();

   }


//      atom_array node::module_path_get_pid(const char * pszModulePath, bool bModuleNameIsPropertyFormatted)
//      {
//
//         return ::acme::node::module_path_get_pid(pszModulePath, bModuleNameIsPropertyFormatted);
//
//
//      }




   

   bool node::process_contains_module(string& strImage, ::u32 processID, const ::string & strLibrary)
   {

      return ::acme::node::process_contains_module(strImage, processID, strLibrary);

   }


   void node::shared_library_process(dword_array& dwa, string_array& straProcesses, const ::string & strLibrary)
   {

      throw ::interface_only();

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
//         throw ::interface_only();
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

      return (int) stra.predicate_get_count([](auto str) { return ::str().begins(str, "cpu"); });

#endif

   }


   void node::node_post(const ::procedure & procedure)
   {

      ::acme::node::node_post(procedure);

   }


} // namespace acme_posix



//#include "_linux.h"
//#include "acme/platform/app_core.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#undef USE_MISC

#include <sys/wait.h>
#include <spawn.h>
#include <sys/stat.h>
#include <unistd.h>
#include "node.h"


// int create_process6(const ::string & _cmd_line, int * pprocessId);

CLASS_DECL_ACME void dll_processes(u32_array & dwa, string_array & straProcesses, const ::string & pszDll)
{

__UNREFERENCED_PARAMETER(dwa);
__UNREFERENCED_PARAMETER(straProcesses);
__UNREFERENCED_PARAMETER(pszDll);

}


namespace acme_posix
{


   void node::call_async(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay,
      bool bPrivileged, unsigned int * puiPid)
   {

      string strCmdLine;

      strCmdLine = pszPath;

      if (ansi_length(pszParam) > 0)
      {

         strCmdLine += " ";

         strCmdLine += pszParam;

      }

      u32 processId;

      create_process(strCmdLine, &processId);

      if (puiPid != nullptr)
      {

         *puiPid = processId;

      }

   }


   void node::call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay,
      const ::duration & durationTimeout, ::property_set & set)
   {

      string strCmdLine;

      strCmdLine = pszPath;

      if (ansi_length(pszParam) > 0)
      {

         strCmdLine += " ";

         strCmdLine += pszParam;

      }

      u32 processId;

      create_process(strCmdLine, &processId);

      while (true)
      {

         if (kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         {

            break;

         }

         sleep(1_ms);

      }

      set["pid"] = processId;

   }


   void node::create_process(const ::string & pszCommandLine, u32 * pprocessId)
   {

      string_array stra;

      stra = get_c_args_for_c(pszCommandLine);

      address_array < char * > argv;

      for (auto & str : stra)
      {

         argv.add((char *)str.c_str());

      }

      argv.add(nullptr);

      auto envp = m_psystem->m_envp;

      pid_t pid = 0;

      string strExe = argv[0];

#ifdef ANDROID

      int status = -1;

      throw ::exception(todo);

#else

      int status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv.get_data(), envp);

#endif

      if (status == 0)
      {

         if (strExe.ends_ci("_app_core_clockverse"))
         {

            ::output_debug_string("app-core/clockverse");

         }

         if (pprocessId != nullptr)
         {

            *pprocessId = pid;

         }

         return;

      }
      else
      {

         if (strExe.ends_ci("_app_core_clockverse"))
         {

            ::output_debug_string("app-core/clockverse");

         }

         throw ::exception(error_failed, "posix::acme_posix::create_process");

      }

   }


   i32 node::_create_process3(const ::string & _cmd_line, i32 * pprocessId)
   {

      //char *   exec_path_name;

      char * cmd_line;

      //char *   cmd_line2;

      cmd_line = strdup(_cmd_line);

      if (cmd_line == nullptr)
      {

         return 0;

      }

      char * argv[1024 + 1];

      i32      argc = 0;

      prepare_argc_argv(argc, argv, cmd_line);

      pid_t pid;

      int status;

      auto envp = m_psystem->m_envp;

#ifdef ANDROID

      status = -1;

      throw ::exception(todo);

#else

      status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv, envp);

#endif

      free(cmd_line);

      if (status == 0)
      {

         return 1;

      }
      else
      {

         return 0;

      }

   }


   void node::run_silent(const ::string & strFunct, const ::string & strstrParams)
   {

#if defined(_UWP)

      throw ::interface_only();

#elif defined(WINDOWS_DESKTOP)

      STARTUPINFO StartupInfo;

      PROCESS_INFORMATION ProcessInfo;

      char Args[4096];

      char * pEnvCMD = nullptr;

      const ::string & pDefaultCMD = "CMD.EXE";

      ULONG rc;

      __memset(&StartupInfo, 0, sizeof(StartupInfo));

      StartupInfo.cb = sizeof(STARTUPINFO);

      StartupInfo.dwFlags = STARTF_USESHOWWINDOW;

      StartupInfo.wShowWindow = SW_HIDE;

      Args[0] = 0;

      pEnvCMD = getenv("COMSPEC");

      if (pEnvCMD)
      {

         strcpy(Args, pEnvCMD);

      }
      else
      {

         strcpy(Args, pDefaultCMD);

      }

      // "/c" option - Do the command then terminate the command window
      ansi_concatenate(Args, " /c ");
      //the application you would like to run from the command window
      ansi_concatenate(Args, strFunct);
      ansi_concatenate(Args, " ");
      //the parameters passed to the application being run from the command window.
      ansi_concatenate(Args, strstrParams);

      if (!CreateProcessW(nullptr, wstring(Args), nullptr, nullptr, false,
         CREATE_NEW_CONSOLE,
         nullptr,
         nullptr,
         &StartupInfo,
         &ProcessInfo))
      {

         return ::GetLastError();

      }

      WaitForSingleObject(ProcessInfo.hProcess, U32_INFINITE_TIMEOUT);

      if (!GetExitCodeProcess(ProcessInfo.hProcess, &rc))
      {

         rc = 0;

      }

      CloseHandle(ProcessInfo.hThread);

      CloseHandle(ProcessInfo.hProcess);

      return rc;

#else

      string strCmdLine;

      strCmdLine = strFunct;

      if (ansi_length(strstrParams) > 0)
      {

         strCmdLine += " ";

         strCmdLine += strstrParams;

      }

      u32 processId;

      create_process(strCmdLine, &processId);
      //         {
      //
      //            return -1;
      //
      //         }

      while (true)
      {

         if (kill(processId, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         {

            break;

         }

         preempt(100_ms);

      }

      //return 0;

#endif

   }


   //::e_status node::shell_execute_sync(const ::string & pszFile, const ::string & pszParams, ::duration durationTimeout)
   //{

   //   property_set set;

   //   call_sync(pszFile, pszParams, ::file::path(pszFile).folder(), e_display_none, durationTimeout, set);

   //   return ::success;

   //}


   string node::module_path_from_pid(unsigned int iPid)
   {

      struct stat sb;

      int iSize;

      string str;

#if defined(FREEBSD)

      str = "/proc/" + __string(iPid) + "/file";

#else

      str = "/proc/" + __string(iPid) + "/exe";

#endif

      memory mem;

      ssize_t s;

      bool iTry;

      if (lstat(str, &sb) == -1)
      {

      retry:

         iSize = 1024 * 4;

         iTry = 1;

         sb.st_size = iSize - 1;

      }
      else
      {

         iSize = (int)(sb.st_size + 1);

         iTry = 0;

      }
#if MEMDLEAK
      mem.m_strTag = "memory://function=module_path_from_pid";
#endif
      mem.set_size(iSize);

      s = readlink(str, (char *)mem.get_data(), iSize);

      if (s > sb.st_size)
      {

         if (iTry <= 0)
         {

            goto retry;

         }
         else
         {

            return "";

         }

      }

      mem.get_data()[s] = '\0';

      return (const char *)mem.get_data();

   }


   //      int_array node::module_path_get_pid(const ::string & pszPath)
   //      {
   //
   //         int_array ia;
   //
   //         ::file::path_array stra;
   //
   //         ::dir::ls_dir(stra, "/proc/");
   //
   //         for(auto & strPid : stra)
   //         {
   //
   //            int iPid = atoi(strPid.title());
   //
   //            if(iPid > 0)
   //            {
   //
   //               string strPath =module_path_from_pid(iPid);
   //
   //               if(strPath	 == pszPath)
   //               {
   //
   //                  ia.add(iPid);
   //
   //               }
   //
   //            }
   //
   //         }
   //
   //         return ia;
   //
   //      }


   atom_array node::module_path_get_pid(const ::string & psz, bool bModuleNameIsPropertyFormatted)
   {

      ::output_debug_string("os/linux_process.cpp app_get_pid (" + string(psz) + ")");

      atom_array ia;

      ::file::listing listing;

      listing.set_folder_listing("/proc");

      m_psystem->m_pacmedirectory->enumerate(listing);

      string str(psz);

      str = "app=" + str;

      string strApp(psz);

      strApp.find_replace("-", "_");

      strApp.find_replace("/", "_");

      string strApp2;

      strApp2 = "_" + strApp;

      for (auto & pathPid : listing)
      {

         int iPid = atoi(pathPid.title());

         if (iPid > 0)
         {

            //if(iPid == 22912)
            //{
            //output_debug_string("22912");
            //}
            ::file::path path = module_path_from_pid(iPid);

            if (path.has_char())
            {

               //output_debug_string(path + "\n");

            }

            //string strTitle = path.title();

            string strPath = path;

            ::str().ends_eat_ci(strPath, " (deleted)");

            //if (strTitle == strApp ||
               //  strTitle == strApp2)
            if (strPath == psz)
            {

               ia.add(iPid);

            }
            else
            {

               string strCmdLine = command_line_from_pid(iPid);

               auto args = get_c_args_from_string(strCmdLine);

               if (args.find_first(str) > 0)
               {

                  ia.add(iPid);

               }

            }

         }

      }

      return ia;

   }


   string node::command_line_from_pid(unsigned int iPid)
   {

      string_array stra;

      string str;

      str = "/proc/" + __string(iPid) + "/cmdline";

      memory mem = m_psystem->m_pacmefile->as_memory(str);

      string strArg;

      char ch;

      for (int i = 0; i < mem.get_size(); i++)
      {

         ch = (char)mem.get_data()[i];

         if (ch == '\0')
         {

            if (strArg.find_first_in(" \t\n") >= 0)
            {

               stra.add("\"" + strArg + "\"");

            }
            else
            {

               stra.add(strArg);

            }

            strArg.Empty();

         }
         else
         {

            strArg += ch;

         }


      }

      if (strArg.has_char())
      {

         if (strArg.find_first_in(" \t\n") >= 0)
         {

            stra.add("\"" + strArg + "\"");

         }
         else
         {

            stra.add(strArg);

         }

      }

      return stra.implode(" ");

      /* the easiest case: we are in freebsd */
//    ssize_t s = readlink (str, path, iSize);

      //  if(s == -1)
      //{
      // return "";
      //}

      //path[s] = '\0';

      //return path;

   }


   bool node::is_shared_library_busy(u32 processid, const string_array & stra)
   {

      return false;

   }


   bool node::is_shared_library_busy(const string_array & stra)
   {

      return false;

   }

#if defined(__clang__) && !defined(ANDROID)
   ::string node::get_callstack()
   {
   
      return clang_backtrace();
      
   }

#endif


} // namespace acme_posix


#ifdef LINUX

i32 daemonize_process(const ::string & pszCommandLine, i32 * pprocessId)
{

   string_array stra;

   stra = get_c_args_for_c(pszCommandLine);

   char ** argv = (char **)malloc(sizeof(char *) * (stra.get_size() + 1));

   int argc = 0;

   for (auto & str : stra)
   {

      argv[argc] = strdup((char *)str.c_str());

      argc++;

   }

   argv[argc] = nullptr;

   pid_t pid;

   pid = fork();

   if (pid == -1)
   {

      printf("fork error\n");

      char ** pargv = argv;

      while (*pargv != nullptr)
      {

         free(*pargv);

         pargv++;

      }

      free(argv);

      return 0;

   }
   else if (pid > 0)
   {

      return 1;

   }

   // change to the "/" directory
   int nochdir = 0;

   // redirect standard input, output and error to /dev/null
   // this is equivalent to "closing the file descriptors"
   int noclose = 0;

   // glibc call to daemonize this process without a double fork
   int iError = daemon(nochdir, noclose);

   if(iError != 0)
   {

      throw ::exception(error_failed, "could not daemonize");

   }


   //   signal(SIGCHLD, SIG_IGN);
   //
   //   umask(0);
   //
   //   int sid = setsid();
   //
   //   if (sid < 0)
   //   {
   //
   //      exit(EXIT_FAILURE);
   //
   //   }
   //
   //    /* Change the current working directory.  This prevents the current
   //       directory from being locked; hence not being able to erase it. */
   //   if ((chdir("/")) < 0)
   //   {
   //
   //      exit(EXIT_FAILURE);
   //
   //   }
   //
   //   /* Redirect standard files to /dev/null */
   //   freopen( "/dev/null", "r", stdin);
   //   freopen( "/dev/null", "w", stdout);
   //   freopen( "/dev/null", "w", stderr);

   int iExitCode = execv(argv[0], argv);

   char ** pargv = argv;

   while (*pargv != nullptr)
   {

      free(*pargv);

      pargv++;

   }

   free(argv);

   exit(iExitCode);


   return 0;

}


#endif


i32 create_process4(const ::string & pszCommandLine, i32 * pprocessId)
{

   string_array stra;

   stra = get_c_args_for_c(pszCommandLine);

   char ** argv = (char **)malloc(sizeof(char *) * (stra.get_size() + 1));

   int argc = 0;

   for (auto & str : stra)
   {

      argv[argc] = strdup((char *)str.c_str());

      argc++;

   }

   argv[argc] = nullptr;

   if ((*pprocessId = fork()) == 0)
   {

      execv(argv[0], argv);

      int status = 0;
      char ** pargv = argv;

      while (*pargv != nullptr)
      {

         free(*pargv);

         pargv++;

      }

      free(argv);

      exit(status);

   }
   else if (*pprocessId == -1)
   {

      *pprocessId = 0;

      char ** pargv = argv;

      while (*pargv != nullptr)
      {

         free(*pargv);

         pargv++;

      }

      free(argv);

      return 0;

   }

   return 1;

}





CLASS_DECL_ACME i32 ca2_main();



int create_process2(const ::string & pszCommandLine, int * pprocessId)
{

   string_array stra;

   stra = get_c_args_for_c(pszCommandLine);

   char ** argv = (char **)malloc(sizeof(char *) * (stra.get_size() + 1));

   int argc = 0;

   for (auto & str : stra)
   {

      argv[argc] = strdup((char *)str.c_str());

      argc++;

   }

   argv[argc] = nullptr;

   pid_t pid = 0;

   if ((pid = fork()) == 0) // child
   {

      int iExitCode = execv(argv[0], argv);

      char ** pargv = argv;

      while (*pargv != nullptr)
      {

         free(*pargv);

         pargv++;

      }

      free(argv);

      exit(iExitCode);

   }
   else if (pid == -1) // in parent, but error
   {

      char ** pargv = argv;

      while (*pargv != nullptr)
      {

         free(*pargv);

         pargv++;

      }

      free(argv);

      return 0;

   }

   if (pprocessId != nullptr)
   {

      *pprocessId = pid;

   }

   return 1;

}


CLASS_DECL_ACME::file::path core_app_path(string strApp)
{

   strApp.find_replace("-", "_");

   strApp.find_replace("/", "_");

   return "/xcore/time/x64/basis/" + strApp;

}



