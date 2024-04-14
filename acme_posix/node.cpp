//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme_file.h"
#include "acme_directory.h"
#include "mutex.h"
#include "exclusive.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/parallelization/single_lock.h"
#include "acme/platform/system.h"
#include "acme/primitive/string/command_line.h"
#include "acme/primitive/string/str.h"
#include "acme/primitive/primitive/memory.h"


#include "acme/_operating_system.h"
#include "acme/operating_system/ansi/_pthread.h"


#include <signal.h>

#if defined(FREEBSD) || defined(OPENBSD)


#include <sys/types.h>
#include <sys/sysctl.h>
#include <errno.h>

#endif


#include <sys/wait.h>
#include <unistd.h>
#if !defined(ANDROID)
#include <wordexp.h>
#endif
#include <fcntl.h>


//
//struct sigaction g_sigactionFpe;
//
//struct sigaction g_sigactionFpeOld;



#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/select.h>
//#include <sched.h>

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
//   zero(g_sigactionFpe);
//
//   zero(g_sigactionFpeOld);
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

   UNREFERENCED_PARAMETER(dwa);
   UNREFERENCED_PARAMETER(straProcesses);
   UNREFERENCED_PARAMETER(pszDll);

}


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


//      ::e_status node::call_sync(const char * pszPath, const char * pszParam, const char * pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set)
//      {
//
//         throw ::interface_only();
//
//         throw ::interface_only();
//
//      }


   void node::dbus_init()
   {



   }

   void node::initialize(::particle * pparticle)
   {

      //auto estatus =
      //
      //
      ::acme::node::initialize(pparticle);

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
//         zero(sa);
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

   bool node::is_process_running(::process_identifier pid)
   {

      return ::acme::node::is_process_running(pid);

   }


   ::file::path_array node::process_identifier_modules_paths(::process_identifier processidentifier)
   {

      throw ::interface_only();

      return {};

   }


   bool node::load_modules_diff(string_array& straOld, string_array& straNew, const ::string & strExceptDir)
   {

      throw ::interface_only();

      return false;

   }


   ::process_identifier_array node::processes_identifiers()
   {

      throw ::interface_only();

      return {};

   }

   /// by camilo on 2023-11-01 06:17 <3ThomasBorregaardSorensen!!
   ::process_identifier node::current_process_identifier()
   {

      return ::getpid();

   }


   ::pointer < ::mutex > node::create_local_named_mutex(::particle * pparticleContext, bool bInitialOwner, const ::string & strName, security_attributes * psecurityattributes)
   {

      return __allocate< mutex >(pparticleContext, bInitialOwner, "Local\\" + strName);

   }


   ::pointer < ::mutex > node::create_global_named_mutex(::particle * pparticleContext, bool bInitialOwner, const ::string & strName, security_attributes * psecurityattributes)
   {

      return __allocate< mutex >(pparticleContext, bInitialOwner, "Global\\" + strName);

   }



   ::pointer<::mutex>node::open_named_mutex(::particle * pparticle, const char * lpszName)
{

#ifdef WINDOWS

   HANDLE h = ::OpenMutexW(SYNCHRONIZE, false, utf8_to_unicode(lpszName));

   if (h == nullptr || h == INVALID_HANDLE_VALUE)
   {

      return nullptr;

   }

   auto pmutex  = __allocate< mutex >(e_create_new, lpszName, h);

   return pmutex;

#elif defined(MUTEX_NAMED_POSIX)

   string strName = pstrName;

   sem_t * psem;

   int isCreator = 0;

   if ((psem = sem_open(strName, O_CREAT | O_EXCL, 0666, 1)) != SEM_FAILED)
   {

      isCreator = 1;

   }
   else
   {

      psem = sem_open(strName, 0);

      if (psem == SEM_FAILED)
      {

         //throw ::exception(resource_exception(papp,"failed to create named mutex"));
         throw ::exception(error_resource);

      }

   }

   auto pmutex = __allocate< mutex >(strName, psem, isCreator);

   return pmutex;

#elif defined(MUTEX_NAMED_FD)

   if (lpszName == nullptr || *lpszName == '\0')
   {

      return nullptr;

   }

   set_last_status(::success);

   ::file::path path;

   string strName(lpszName);

   strName.find_replace(":", "_");

   if (strName.case_insensitive_begins("Global"))
   {

      path = "/var/tmp/ca2/lock/mutex/named";

   }
   else
   {

#ifdef __APPLE__

      path = getenv("HOME");

      path /= "Library/ca2/lock/mutex/named";

#else

      path = getenv("HOME");

      path /= ".config/ca2/lock/mutex/named";

#endif

   }

   path /= strName;

//   auto pacmedirectory = pparticle->acmedirectory();
//
//   auto pathFolder = path.folder();
//
//   pacmedirectory->create(pathFolder);
//
//   if(!pacmedirectory->is(pathFolder))
//   {
//
//      throw ::exception(error_failed, "Could not create folder for the named mutex: " + path.folder());
//
//   }

   int iFd = open(path, O_RDWR | O_CLOEXEC, S_IRWXU);

   if (iFd < 0)
   {

      throw_file_errno_exception(path, ::file::e_open_none, "open, O_RDWR, S_IRWXU");

   }

   //m_pszName = strdup(path);

   //pthread_mutexattr_t attr;

   //pthread_mutexattr_init(&attr);

   //pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

   //pthread_mutex_init(m_pmutex, &attr);

   auto pmutex = __allocate< mutex >(e_create_new, lpszName, iFd, false);

   return pmutex;

#elif defined(POSIX_NAMED_VSEM)

   if(pstrName == nullptr || *pstrName == '\0')
      return nullptr;

   string strName = pstrName;

   key_t key = ftok(strName, 0); //Generate a unique key or supply a value

   i32 semid = semget(
               key, // a unique identifier to identify semaphore set
               1,  // number of semaphore in the semaphore set
               0666 // permissions (rwxrwxrwx) on the new
               //semaphore set and creation flag
               );
   if(semid < 0)
   {

      return nullptr;

   }

   auto pmutex = __allocate< mutex >(strName, key, semid);

   return pmutex;

#endif

}


   ::pointer < ::mutex > node::open_local_named_mutex(::particle * pparticleContext, const ::string & strName)
   {

      return open_named_mutex(pparticleContext, "Local/" + strName);

   }


   ::pointer < ::mutex > node::open_global_named_mutex(::particle * pparticleContext, const ::string & strName)
   {

      return open_named_mutex(pparticleContext, "Global/" + strName);

   }


   ::pointer < ::acme::exclusive > node::get_exclusive(::particle * pparticleContext, const ::string & strName, security_attributes * psecurityattributes)
   {

      return __allocate< exclusive >(pparticleContext, strName);

   }

//      atom_array node::module_path_get_pid(const char * pszModulePath, bool bModuleNameIsPropertyFormatted)
//      {
//
//         return ::acme::node::module_path_get_pid(pszModulePath, bModuleNameIsPropertyFormatted);
//
//
//      }




   

   bool node::process_contains_module(string& strImage, ::process_identifier processID, const ::string & strLibrary)
   {

      return ::acme::node::process_contains_module(strImage, processID, strLibrary);

   }


::process_identifier_array node::shared_library_process(string_array& straProcesses, const ::string & strLibrary)
   {

      throw ::interface_only();

   }


   string node::get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable)
   {

      return ::getenv(scopedstrEnvironmentVariable);

   }


   void node::set_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable, const ::scoped_string & scopedstrPayload)
   {

      ::setenv(scopedstrEnvironmentVariable, scopedstrPayload, 1);

   }

   void node::unset_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable)
   {
   
      ::unsetenv(scopedstrEnvironmentVariable);
      
   }


   string node::expand_environment_variables(const ::scoped_string & scopedstr)
   {

      return ::acme::node::expand_environment_variables(scopedstr);

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

#if defined(FREEBSD) || defined(OPENBSD)

      int mib[4];
      int numCPU;
      std::size_t len = sizeof(numCPU);

/* set the mib for hw.ncpu */
      mib[0] = CTL_HW;
#if defined(FREEBSD)  || defined(OPENBSD)
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

      string str = acmefile()->as_string("/proc/stat");

      string_array stra;

      stra.add_lines(str);

      return (int) stra.predicate_get_count([](auto str) { return str.begins("cpu"); });

#endif

   }


//   void node::aaa_user_post(const ::procedure & procedure)
//   {
//
//      ::acme::node::aaa_node_post(procedure);
//
//   }



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

      auto processId = create_process(strCmdLine);

      if (puiPid != nullptr)
      {

         *puiPid = (unsigned int) processId;

      }

   }


   void node::call_sync(const ::string & pszPath, const ::string & pszParam, const ::string & pszDir, ::e_display edisplay,
      const class time & timeTimeout, ::property_set & set, int * piExitCode)
   {

      string strCmdLine;

      strCmdLine = pszPath;

      if (ansi_length(pszParam) > 0)
      {

         strCmdLine += " ";

         strCmdLine += pszParam;

      }

      auto processId = create_process(strCmdLine);
      
      pid_t pid = (pid_t) processId;

      while (true)
      {

         if (kill(pid, 0) == -1)
         {

            auto cerrornumber = c_error_number();

            if (cerrornumber == ESRCH) // No process can be found corresponding to processId
            {

               break;

            }

         }

         sleep(1_ms);

      }

      set["pid"] = processId;

   }


::process_identifier node::create_process(const ::string & pszCommandLine)
   {

      string_array stra;

      stra = get_c_args_for_c(pszCommandLine);

      address_array < char * > argv;

      for (auto & str : stra)
      {

         argv.add((char *)str.c_str());

      }

      argv.add(nullptr);

      auto envp = platform()->m_envp;

      pid_t pid = 0;

      string strExe = argv[0];

#ifdef ANDROID

      int status = -1;

      throw ::exception(todo);

#else

      int status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv.data(), envp);

#endif

      if (status == 0)
      {

         if (strExe.case_insensitive_ends("_app_core_clockverse"))
         {

            ::acme::get()->platform()->informationf("app-core/clockverse");

         }

//         if (pprocessId != nullptr)
//         {
//
//            *pprocessId = pid;
//
//         }

         return pid;

      }
      else
      {

         if (strExe.case_insensitive_ends("_app_core_clockverse"))
         {

            ::acme::get()->platform()->informationf("app-core/clockverse");

         }

         throw ::exception(error_failed, "posix::acme_posix::create_process");

      }

   }


   i32 node::_create_process3(const ::string & _cmd_line, i32 * pprocessId)
   {

      //char *   exec_path_name;

      char * cmd_line;

      //char *   cmd_line2;

      cmd_line = ansi_dup(_cmd_line);

      if (cmd_line == nullptr)
      {

         return 0;

      }

      char * argv[1024 + 1];

      i32      argc = 0;

      prepare_argc_argv(argc, argv, cmd_line);

      pid_t pid;

      int status;

      auto envp = platform()->m_envp;

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

#if defined(UNIVERSAL_WINDOWS)

      throw ::interface_only();

#elif defined(WINDOWS_DESKTOP)

      STARTUPINFO StartupInfo;

      PROCESS_INFORMATION ProcessInfo;

      char Args[4096];

      char * pEnvCMD = nullptr;

      const ::string & pDefaultCMD = "CMD.EXE";

      ULONG rc;

      memory_set(&StartupInfo, 0, sizeof(StartupInfo));

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

      //u32 processId;

      auto processId = create_process(strCmdLine);
      //         {
      //
      //            return -1;
      //
      //         }
      
      pid_t pid = (pid_t) processId;

      while (true)
      {

         if (kill(pid, 0) == -1 && errno == ESRCH) // No process can be found corresponding to processId
         {

            break;

         }

         preempt(100_ms);

      }

      //return 0;

#endif

   }


   //::e_status node::shell_execute_sync(const ::string & pszFile, const ::string & pszParams, ::time timeTimeout)
   //{

   //   property_set set;

   //   call_sync(pszFile, pszParams, ::file::path(pszFile).folder(), e_display_none, timeTimeout, set);

   //   return ::success;

   //}


   ::file::path node::process_identifier_module_path(::process_identifier iPid)
   {

      struct stat sb;

      int iSize;

      string str;

#if defined(FREEBSD) || defined(OPENBSD)

      str = "/proc/" + ::as_string(iPid) + "/file";

#else

      str = "/proc/" + ::as_string(iPid) + "/exe";

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

      s = readlink(str, (char *)mem.data(), iSize);

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

      mem.data()[s] = '\0';

      return (const char *)mem.data();

   }


   //      ::i32_array node::module_path_get_pid(const ::string & pszPath)
   //      {
   //
   //         ::i32_array ia;
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


::process_identifier_array node::module_path_processes_identifiers(const ::string & psz, bool bModuleNameIsPropertyFormatted)
   {

      ::acme::get()->platform()->informationf("os/linux_process.cpp app_get_pid (" + string(psz) + ")");

   ::process_identifier_array ia;

      ::file::listing listing;

      listing.set_folder_listing("/proc");

      acmedirectory()->enumerate(listing);

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
            //informationf("22912");
            //}
            ::file::path path = process_identifier_module_path(iPid);

            if (path.has_char())
            {

               //information(path + "\n");

            }

            //string strTitle = path.title();

            string strPath = path;

            strPath.case_insensitive_ends_eat(" (deleted)");

            //if (strTitle == strApp ||
               //  strTitle == strApp2)
            if (strPath == psz)
            {

               ia.add(iPid);

            }
//            else
//            {
//
//               string strCmdLine = command_line_from_pid(iPid);
//
//               auto args = get_c_args_from_string(strCmdLine);
//
//               if (args.find_first(str) > 0)
//               {
//
//                  ia.add(iPid);
//
//               }
//
//            }

         }

      }

      return ia;

   }


   string node::process_identifier_command_line(::process_identifier iPid)
   {

      string_array stra;

      string str;

      str = "/proc/" + ::as_string(iPid) + "/cmdline";

      memory mem = acmefile()->as_memory(str);

      if(mem.is_empty())
      {

         return {};

      }

      const_ansi_range rangeArgument;

      //char ch;

      rangeArgument.m_begin = (const char *) mem.begin();

      rangeArgument.m_end = (const char *) mem.data();

      bool bHasSpace = false;

      while(true)
      {

         if (rangeArgument.m_end >= (const char*) mem.end() || *rangeArgument.m_end == '\0')
         {

            if(rangeArgument.has_char())
            {

               if (bHasSpace)
               {

                  stra.add("\"" + rangeArgument + "\"");

               }
               else
               {

                  stra.add(rangeArgument);

               }

            }

            if(rangeArgument.m_end >= (const char *) mem.end())
            {

               break;

            }

            rangeArgument.m_end++;

            rangeArgument.m_begin = rangeArgument.m_end;

            bHasSpace = false;

         }
         else if(!bHasSpace)
         {

            bHasSpace = character_isspace(*rangeArgument.m_end);

         }

         rangeArgument.m_end++;

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


//   bool node::is_shared_library_busy(::process_identifier processid, const string_array & stra)
//   {
//
//      return false;
//
//   }
//
//
//   bool node::is_shared_library_busy(const string_array & stra)
//   {
//
//      return false;
//
//   }

//#if defined(__clang__) && !defined(ANDROID)
//   ::string node::get_callstack()
//   {
//
//      return clang_backtrace();
//
//   }
//
//#endif


   bool node::stdin_has_input_events()
   {


      // cc.byexamples.com calls this int kbhit(), to mirror the Windows console
      //  function of the same name.  Otherwise, the code is the same.
      struct timeval tv;
      fd_set fds;
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      FD_ZERO(&fds);
      FD_SET(STDIN_FILENO, &fds);
      select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
      return (FD_ISSET(0, &fds));
   }


//   bool node::stdin_wait_char(void)
//   {
//      struct timeval tv;
//      fd_set fds;
//      tv.tv_sec = INT_MAX; // Almost infinite wait
//      tv.tv_usec = 0;
//      FD_ZERO(&fds);
//      FD_SET(STDIN_FILENO, &fds);
//      select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
//      return (FD_ISSET(0, &fds));
//   }


   void node::flush_stdin()
   {

      while (stdin_has_input_events())
      {

         getchar();

      }

   }


   bool node::set_process_priority(::enum_priority epriority)
{
      
//#ifdef LINUX
      
//#error "please transfer the code commented below to linux-operating_system"
//
//#else
      
      return ::acme::node::set_process_priority(epriority);
      
///#endif
      
      
   }
//   {
//
//      i32 iPolicy = SCHED_OTHER;
//
//      sched_param schedparam;
//
//      schedparam.sched_priority = 0;
//
//      get_os_priority(&iPolicy, &schedparam, epriority);
//
//      sched_setscheduler(0, iPolicy, &schedparam);
//
//      return true;
//
//   }


   //void node::command_system(string_array & straOutput, int& iExitCode, const scoped_string & scopedstr, enum_command_system ecommandsystem, const class time & timeTimeout, ::particle * pparticleSynchronization, ::file::file * pfileLog)
   int node::__command_system(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPipe, const ::function < void(enum_trace_level, const ::scoped_string & ) > & functionTrace)
   {

      ::e_status estatus = success;

      int stdout_fds[2] = {};

      int iExitCode = 0;

      int iError = pipe(stdout_fds);

      if (iError != 0)
      {

         auto cerrornumber = c_error_number();

         estatus = cerrornumber.estatus();

         throw ::exception(estatus);

      }

      int stderr_fds[2] = {};

      iError = pipe(stderr_fds);

      if (iError != 0)
      {

         auto cerrornumber = c_error_number();

         estatus = cerrornumber.estatus();

         throw ::exception(estatus);

      }

      int stdin_fds[2] = {};

      if(scopedstrPipe.has_char())
      {

         iError = pipe(stdin_fds);

         if (iError != 0)
         {

            auto cerrornumber = c_error_number();

            estatus = cerrornumber.estatus();

            throw ::exception(estatus);

         }

      }

      string strOutput;

      string strError;

      const pid_t pid = ::fork();

      if (!pid)
      {

         while ((dup2(stdout_fds[1], STDOUT_FILENO) == -1) && (errno == EINTR))
         {}

         while ((dup2(stderr_fds[1], STDERR_FILENO) == -1) && (errno == EINTR))
         {}

         if(scopedstrPipe.has_char())
         {

            while ((dup2(stdin_fds[0], STDIN_FILENO) == -1) && (errno == EINTR))
            {}

         }

         close(stdout_fds[0]);

         close(stdout_fds[1]);

         close(stderr_fds[0]);

         close(stderr_fds[1]);

         close(stdin_fds[0]);

         close(stdin_fds[1]);

#if defined(ANDROID) || defined(APPLE_IOS)

         throw ::exception(todo);

#else

         auto pszCommandLine = ansi_dup(scopedstr);

         int iErrNo = 0;

         wordexp_t we{};

         wordexp(pszCommandLine, &we, 0);

         char **argv = __new_array< char * >(we.we_wordc + 1);

         memory_copy(argv, we.we_wordv, we.we_wordc * sizeof(char *));

         int iChildExitCode = execvp(argv[0], &argv[0]);

         if (iChildExitCode == -1)
         {

            iErrNo = errno;

         }

         delete[]argv;

         wordfree(&we);

         free(pszCommandLine);

         _exit(iErrNo);

#endif

      }

      close(stdout_fds[1]);

      close(stderr_fds[1]);

      if(scopedstrPipe.has_char())
      {

         close(stdin_fds[0]);

      }

      fcntl(stdout_fds[0], F_SETFL, fcntl(stdout_fds[0], F_GETFL) | O_NONBLOCK);

      fcntl(stderr_fds[0], F_SETFL, fcntl(stderr_fds[0], F_GETFL) | O_NONBLOCK);

      if(scopedstrPipe.has_char())
      {

         fcntl(stdin_fds[1], F_SETFL, fcntl(stdin_fds[1], F_GETFL) | O_NONBLOCK);

      }

      const int buf_size = 4096;

      char buffer[buf_size];

      char chExitCode = 0;

      bool bExit = false;

      if (scopedstrPipe.has_char())
      {

         preempt(2_s);

         auto iWrittenByteCount = ::write(stdin_fds[1],  scopedstrPipe.data(), scopedstrPipe.size());

         if(iWrittenByteCount != scopedstrPipe.size())
         {

            warning() <<"Written amount of bytes different from requested one (::acme_posix::node::command_system)";

         }

         ::close(stdin_fds[1]);

      }

      while(true)
      {

         bool bRead = false;

         while(true)
         {

            const ssize_t iOutRead = read(stdout_fds[0], buffer, buf_size);

            if (iOutRead > 0)
            {

               bRead = true;

               string strMessage(buffer, iOutRead);

               strOutput += strMessage;

               if(functionTrace)
               {

                  ::str::get_lines(strOutput, false, [&](auto & str)
                  {

                     functionTrace(e_trace_level_information, str);

                  });
                 // functionTrace(e_trace_level_information, strMessage);

               }

               //::str::get_lines(straOutput, strOutput, "I: ", false, &singlelock, pfileLog);

            }

            const ssize_t iErrRead = read(stderr_fds[0], buffer, buf_size);

            if (iErrRead > 0)
            {

               bRead = true;

               string strMessage(buffer, iErrRead);

               strError += strMessage;

//               if(ecommandsystem & e_command_system_inline_log)
//               {
//
//                  fprintf(stderr, "%s", strMessage.c_str());
//
//               }
//
//               ::str::get_lines(straOutput, strError, "E: ", false, &singlelock, pfileLog);

               if(functionTrace)
               {

                  ::str::get_lines(strError, false, [&](auto &str)
                  {

                     functionTrace(e_trace_level_error, str);

                  });

               }

            }

            if(iOutRead > 0 || iErrRead > 0)
            {

               bRead = true;

            }
            else
            {

               break;

            }

         }

         if(bRead)
         {

            {

               int status = 0;

               int iWaitPid = waitpid(pid, &status, WNOHANG | WUNTRACED | WCONTINUED);

               if (iWaitPid == -1)
               {

                  int iErrorNo = errno;

                  if (iErrorNo != ECHILD)
                  {

                     //break;

                     bExit = true;

                  }

               }
               else if (iWaitPid == pid)
               {

                  if (WIFEXITED(status))
                  {

                     chExitCode = WEXITSTATUS(status);

                     iExitCode = chExitCode;

                     //break;

                     bExit = true;

                  }

               }

            }

            if (!::task_get_run() && !bExit)
            {

               close(stdout_fds[0]);

               close(stderr_fds[0]);

               //close(stdin_fds[1]);

               kill(pid, SIGKILL);

               int iStatus = 0;

               waitpid(pid, &iStatus, 0);

               break;

            }

            if (bExit)
            {

               break;

            }

            if (!bRead && !bExit)
            {

               preempt(25_ms);

            }

         }

      }

      close(stdout_fds[0]);

      close(stderr_fds[0]);

//      if (scopedstrPipe.has_char())
//      {
//
//         ::close(stdin_fds[1]);
//
//      }



//   if(iExitCode != 0)
//   {
//
//      auto estatus = failed_errno_status(iExitCode);
//
//      throw ::exception(estatus);
//
//   }

   if(functionTrace)
   {

      ::str::get_lines(strOutput, true, [&](auto &str)
      {

         functionTrace(e_trace_level_information, str);

      });

      ::str::get_lines(strError, true, [&](auto &str)
      {

         functionTrace(e_trace_level_error, str);

      });

      //::str::get_lines(straOutput, strOutput, "I: ", true, &singlelock, pfileLog);

      //::str::get_lines(straOutput, strError, "E: ", true, &singlelock, pfileLog);

   }

      return iExitCode;

   }


int node::command_system(const ::scoped_string & scopedstr,  const ::function < void(enum_trace_level, const ::scoped_string & ) > & functionTrace)
{

   ::e_status estatus = success;

   int stdout_fds[2] = {};

   int iExitCode = 0;

   int iError = pipe(stdout_fds);

   if (iError != 0)
   {

      auto cerrornumber = c_error_number();

      estatus = cerrornumber.estatus();

      throw ::exception(estatus);

   }

   int stderr_fds[2] = {};

   iError = pipe(stderr_fds);

   if (iError != 0)
   {

      auto cerrornumber = c_error_number();

      estatus = cerrornumber.estatus();

      throw ::exception(estatus);

   }

   int stdin_fds[2] = {};
   
   auto range = scopedstr();
   
   ::string strExecutable(range.consume_command_line_argument());
   
   char **argv;
   
#if defined(APPLE_IOS)
   
   argv = nullptr;
   
#else

   auto pszExecutable = ::c::strdup(strExecutable);
   
   auto pszCommandLine = ansi_dup(scopedstr);

   int iErrNo = 0;
   
   wordexp_t we{};

   wordexp(pszCommandLine, &we, 0);

   argv = __new_array< char * >(we.we_wordc + 1);
   
   for(::index i = 0; i < we.we_wordc; i++)
   {
      
      auto arg = we.we_wordv[i];
      
      argv[i] = arg;
      
   }
   
   argv[we.we_wordc] = nullptr;
   
#endif

//   if(scopedstrPipe.has_char())
//   {
//
//      iError = pipe(stdin_fds);
//
//      if (iError != 0)
//      {
//
//         auto cerrornumber = c_error_number();
//
//         estatus = errno_status(iErrNo);
//
//         throw ::exception(estatus);
//
//      }
//
//   }
   
   fcntl(stdout_fds[0], F_SETFL, fcntl(stdout_fds[0], F_GETFL) | O_CLOEXEC);
   fcntl(stdout_fds[1], F_SETFL, fcntl(stdout_fds[1], F_GETFL) | O_CLOEXEC);
   fcntl(stderr_fds[0], F_SETFL, fcntl(stderr_fds[0], F_GETFL) | O_CLOEXEC);
   fcntl(stderr_fds[1], F_SETFL, fcntl(stderr_fds[1], F_GETFL) | O_CLOEXEC);
   fcntl(stdin_fds[0], F_SETFL, fcntl(stdin_fds[0], F_GETFL) | O_CLOEXEC);
   fcntl(stdin_fds[1], F_SETFL, fcntl(stdin_fds[1], F_GETFL) | O_CLOEXEC);

   string strOutput;

   string strError;

   const pid_t pid = ::fork();

   if (!pid)
   {

      while ((dup2(stdout_fds[1], STDOUT_FILENO) == -1) && (errno == EINTR))
      {}

      while ((dup2(stderr_fds[1], STDERR_FILENO) == -1) && (errno == EINTR))
      {}

//      if(scopedstrPipe.has_char())
//      {
//
//         while ((dup2(stdin_fds[0], STDIN_FILENO) == -1) && (errno == EINTR))
//         {}
//
//      }

      //close(stdout_fds[0]);

//      close(stdout_fds[1]);
//
//      //close(stderr_fds[0]);
//
//      close(stderr_fds[1]);
//
//      close(stdin_fds[0]);

      //close(stdin_fds[1]);

#if defined(ANDROID) || defined(APPLE_IOS)

      throw ::exception(todo);

#else

      int iChildExitCode = execvp(pszExecutable, argv);

      if (iChildExitCode == -1)
      {

         iErrNo = errno;

      }

      delete[]argv;

      wordfree(&we);

      free(pszCommandLine);
      
      free(pszExecutable);

      _exit(iErrNo);

#endif

   }

   close(stdout_fds[1]);

   close(stderr_fds[1]);

//   if(scopedstrPipe.has_char())
//   {
//
//      close(stdin_fds[0]);
//
//   }
//
   fcntl(stdout_fds[0], F_SETFL, fcntl(stdout_fds[0], F_GETFL) | O_NONBLOCK);

   fcntl(stderr_fds[0], F_SETFL, fcntl(stderr_fds[0], F_GETFL) | O_NONBLOCK);

//   if(scopedstrPipe.has_char())
//   {
//
//      fcntl(stdin_fds[1], F_SETFL, fcntl(stdin_fds[1], F_GETFL) | O_NONBLOCK);
//
//   }

   const int buf_size = 4096;

   char buffer[buf_size];

   char chExitCode = 0;

   bool bExit = false;

//   if (scopedstrPipe.has_char())
//   {
//
//      preempt(2_s);
//
//      auto iWrittenByteCount = ::write(stdin_fds[1],  scopedstrPipe.data(), scopedstrPipe.size());
//
//      if(iWrittenByteCount != scopedstrPipe.size())
//      {
//
//         warning() <<"Written amount of bytes different from requested one (::acme_posix::node::command_system)";
//
//      }
//
//      ::close(stdin_fds[1]);
//
//   }

   while(true)
   {

      if(!::task_get_run() && !bExit)
      {

         close(stdout_fds[0]);

         close(stderr_fds[0]);

         //close(stdin_fds[1]);

         kill(pid, SIGKILL);

         int iStatus = 0;

         waitpid(pid, &iStatus, 0);

         break;

      }

      bool bRead = false;

      while(true)
      {

         const ssize_t iOutRead = read(stdout_fds[0], buffer, buf_size);

         if (iOutRead > 0)
         {

            bRead = true;

            string strMessage(buffer, iOutRead);

            strOutput += strMessage;

            if(functionTrace)
            {

               ::str::get_lines(strOutput, false, [&](auto & str)
               {

                  functionTrace(e_trace_level_information, str);

               });
              // functionTrace(e_trace_level_information, strMessage);

            }

            //::str::get_lines(straOutput, strOutput, "I: ", false, &singlelock, pfileLog);

         }

         const ssize_t iErrRead = read(stderr_fds[0], buffer, buf_size);

         if (iErrRead > 0)
         {

            bRead = true;

            string strMessage(buffer, iErrRead);

            strError += strMessage;

//               if(ecommandsystem & e_command_system_inline_log)
//               {
//
//                  fprintf(stderr, "%s", strMessage.c_str());
//
//               }
//
//               ::str::get_lines(straOutput, strError, "E: ", false, &singlelock, pfileLog);

            if(functionTrace)
            {

               ::str::get_lines(strError, false, [&](auto &str)
               {

                  functionTrace(e_trace_level_error, str);

               });

            }

         }

         if(iOutRead > 0 || iErrRead > 0)
         {

            bRead = true;

         }
         else
         {

            break;

         }

      }

      if(bExit)
      {


         break;

      }

      {

         int status = 0;

         int iWaitPid = waitpid(pid, &status, WNOHANG | WUNTRACED | WCONTINUED);

         if(iWaitPid == -1)
         {

            int iErrorNo = errno;

            if(iErrorNo != ECHILD)
            {

               //break;

               bExit = true;

            }

         }
         else if(iWaitPid == pid)
         {

            if (WIFEXITED(status))
            {

               chExitCode = WEXITSTATUS(status);

               iExitCode = chExitCode;

               //break;

               bExit = true;

            }

         }

      }

      if(!bRead && !bExit)
      {

         preempt(25_ms);

      }

   }

   close(stdout_fds[0]);

   close(stderr_fds[0]);

//      if (scopedstrPipe.has_char())
//      {
//
//         ::close(stdin_fds[1]);
//
//      }



//   if(iExitCode != 0)
//   {
//
//      auto estatus = failed_errno_status(iExitCode);
//
//      throw ::exception(estatus);
//
//   }

if(functionTrace)
{

   ::str::get_lines(strOutput, true, [&](auto &str)
   {

      functionTrace(e_trace_level_information, str);

   });

   ::str::get_lines(strError, true, [&](auto &str)
   {

      functionTrace(e_trace_level_error, str);

   });

   //::str::get_lines(straOutput, strOutput, "I: ", true, &singlelock, pfileLog);

   //::str::get_lines(straOutput, strError, "E: ", true, &singlelock, pfileLog);

}

   return iExitCode;

}


   ::file::path node::library_file_name(const ::scoped_string& scopedstr)
   {

      return "lib" + scopedstr + ".so";

   }


   int node::unix_shell_command(const ::scoped_string& scopedstrCommand, const trace_function & tracefunction)
   {

      try
      {

         ::string strUnixShell;

#if defined(FREEBSD) || defined(OPENBSD)

         strUnixShell = "/usr/local/bin/bash";

#else

         strUnixShell = "/bin/bash";

#endif

         ::string strCommand;

         ::string strCommandInner;

         strCommandInner = scopedstrCommand.c_str();

         strCommandInner.find_replace("\"", "\\\"");

         strCommand.formatf("\"%s\" -c \"%s\"", strUnixShell.c_str(), strCommandInner.c_str());

         auto iExitCode = this->command_system(strCommand, tracefunction);

         return iExitCode;

      }
      catch (...)
      {

      }

      return -1;

   }

//
//   ::user::enum_desktop node::calculate_edesktop()
//   {
//
//      return get_edesktop();
//
//   }

   
   bool node::is_executable_in_path(const ::scoped_string &scopedstr)
   {
      
      ::string strPath;
   
      get_unix_shell_command_output(strPath, "command -v " + scopedstr);
      
      information() << "command -v : " << scopedstr << " output => " << strPath;
      
      if(strPath.is_empty())
      {
         
         return false;
         
      }
      
      return true;
      
   }


} // namespace acme_posix



