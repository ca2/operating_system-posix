//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "file_system.h"
#include "directory_system.h"
#include "mutex.h"
#include "exclusive.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/file/exception.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/operating_system/posix/_.h"
#include "acme/parallelization/single_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/prototype/string/command_line.h"
#include "acme/prototype/string/str.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/windowing/windowing.h"
#include "acme/constant/windowing2.h"

#include "acme/_operating_system.h"
#include "acme/operating_system/ansi/_pthread.h"


#define DEEP_LOG_HERE 0

template < typename POINTER_TYPE >
class array_of_malloced_pointer_base :
virtual public ::numeric_array_base < POINTER_TYPE >
	{
	public:
	
	array_of_malloced_pointer_base()
	{
	}
	~array_of_malloced_pointer_base()
	{
	deallocate();
	}
	
	void	deallocate()
	{
		for(auto & p : *this)
		{
			if(::is_set(p)) 
			{
				::free(p);
				p=nullptr;
			}
		}
	}
	
	
	};


template < typename POINTER_TYPE >
using array_of_malloced_pointer = ::array_particle < array_of_malloced_pointer_base< POINTER_TYPE > >;


::string __expand_environment_variables(const ::scoped_string & scopedstr);
	
::pointer < ::array_of_malloced_pointer < char * > > strdupa_from_command_arguments(const ::string_array_base & stra)
{

	::pointer < ::array_of_malloced_pointer < char * > > p;
	
	p = øallocate ::array_of_malloced_pointer < char * > ();
	
	for(auto & str:stra)
	{
	
		p->add_item(::c::strdup(str));
		
	}
	
	return p;
	
}

#include <signal.h>

#if defined(__BSD__)


#include <sys/types.h>
#include <sys/sysctl.h>
#include <errno.h>

#endif


#if defined(__APPLE__) || defined(NETBSD) || defined(FREEBSD)

#define HOST_NAME_MAX _POSIX_HOST_NAME_MAX

#endif


#include <sys/wait.h>
#include <unistd.h>
//#if !defined(__ANDROID__)
//#if defined(OPENBSD)
//#include <glob.h>
//#else
//#include <wordexp.h>
//#endif
//#endif
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

#if defined(__clang__) && !defined(__ANDROID__)
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


void apex_application_run(const_char_pointer pszAppName, const_char_pointer pszProgName);


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

CLASS_DECL_ACME void dll_processes(unsigned_int_array & dwa, string_array_base & straProcesses, const ::scoped_string & scopedstrDll)
{

   __UNREFERENCED_PARAMETER(dwa);
   __UNREFERENCED_PARAMETER(straProcesses);
   __UNREFERENCED_PARAMETER(scopedstrDll);

}


namespace acme_posix
{


   node::node()
   {

      //m_pAcmePosix = this;

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


//      ::e_status node::call_async(const_char_pointer pszPath, const_char_pointer pszParam, const_char_pointer pszDir, ::e_display edisplay, bool bPrivileged, unsigned int * puiPid)
//      {
//
//         throw ::interface_only();
//
//         throw ::interface_only();
//
//      }


//      ::e_status node::call_sync(const_char_pointer pszPath, const_char_pointer pszParam, const_char_pointer pszDir, ::e_display edisplay, const class time & timeTimeout, ::property_set & set)
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
      ::platform::node::initialize(pparticle);

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

      return ::platform::node::is_process_running(pid);

   }


   ::file::path_array_base node::process_identifier_modules_paths(::process_identifier processidentifier)
   {

      printf_line("node::process_identifier_modules_paths THROW INTERFACE ONLY");

      throw ::interface_only();

      return {};

   }


   bool node::load_modules_diff(string_array_base& straOld, string_array_base& straNew, const ::scoped_string & scopedstrExceptDir)
   {

      throw ::interface_only();

      return false;

   }


   ::process_identifier_array node::processes_identifiers()
   {
      
      information() << "acme_posix::node::processes_identifiers THROW INTERFACE ONLY";

      throw ::interface_only();

      return {};

   }

   /// by camilo on 2023-11-01 06:17 <3ThomasBorregaardSorensen!!
   ::process_identifier node::current_process_identifier()
   {

      return ::getpid();

   }


   ::pointer < ::mutex > node::create_local_named_mutex(::particle * pparticleContext, bool bInitialOwner, const ::scoped_string & scopedstrName, security_attributes * psecurityattributes)
   {

      return øallocate mutex(pparticleContext, bInitialOwner, "Local\\" + scopedstrName);

   }


   ::pointer < ::mutex > node::create_global_named_mutex(::particle * pparticleContext, bool bInitialOwner, const ::scoped_string & scopedstrName, security_attributes * psecurityattributes)
   {

      return øallocate mutex(pparticleContext, bInitialOwner, "Global\\" + scopedstrName);

   }



   ::pointer<::mutex>node::open_named_mutex(::particle * pparticle, const_char_pointer lpszName)
{

#ifdef WINDOWS

   HANDLE h = ::OpenMutexW(SYNCHRONIZE, false, utf8_to_unicode(lpszName));

   if (h == nullptr || h == INVALID_HANDLE_VALUE)
   {

      return nullptr;

   }

   auto pmutex = øallocate mutex(e_create_new, lpszName, h);

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

   auto pmutex = øallocate mutex(strName, psem, isCreator);

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

//   auto pdirectorysystem = pparticle->directory_system();
//
//   auto pathFolder = path.folder();
//
//   pdirectorysystem->create(pathFolder);
//
//   if(!pdirectorysystem->is(pathFolder))
//   {
//
//      throw ::exception(error_failed, "Could not create folder for the named mutex: " + path.folder());
//
//   }

   int iFd = open(path, O_RDWR | O_CLOEXEC);

   if (iFd < 0)
   {

      throw_file_errno_exception(path, ::file::e_open_none, "open, O_RDWR, S_IRWXU");

   }

   //m_pszName = strdup(path);

   //pthread_mutexattr_t attr;

   //pthread_mutexattr_init(&attr);

   //pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

   //pthread_mutex_init(m_pmutex, &attr);

   auto pmutex = øallocate mutex(e_create_new, lpszName, iFd, false);

   return pmutex;

#elif defined(POSIX_NAMED_VSEM)

   if(pstrName == nullptr || *pstrName == '\0')
      return nullptr;

   string strName = pstrName;

   key_t key = ftok(strName, 0); //Generate a unique key or supply a value

   int semid = semget(
               key, // a unique identifier to identify semaphore set
               1,  // number of semaphore in the semaphore set
               0666 // permissions (rwxrwxrwx) on the ___new
               //semaphore set and creation flag
               );
   if(semid < 0)
   {

      return nullptr;

   }

   auto pmutex = øallocate mutex(strName, key, semid);

   return pmutex;

#endif

}


   ::pointer < ::mutex > node::open_local_named_mutex(::particle * pparticleContext, const ::scoped_string & scopedstrName)
   {

      return open_named_mutex(pparticleContext, "Local/" + scopedstrName);

   }


   ::pointer < ::mutex > node::open_global_named_mutex(::particle * pparticleContext, const ::scoped_string & scopedstrName)
   {

      return open_named_mutex(pparticleContext, "Global/" + scopedstrName);

   }


   ::pointer < ::acme::exclusive > node::get_exclusive(::particle * pparticleContext, const ::scoped_string & scopedstrName, security_attributes * psecurityattributes)
   {

      return øallocate exclusive(pparticleContext, scopedstrName);

   }

//      atom_array node::module_path_get_pid(const_char_pointer pszModulePath, bool bModuleNameIsPropertyFormatted)
//      {
//
//         return ::platform::node::module_path_get_pid(scopedstrModulePath, bModuleNameIsPropertyFormatted);
//
//
//      }




   

   bool node::process_contains_module(string& strImage, ::process_identifier processID, const ::scoped_string & scopedstrLibrary)
   {

      return ::platform::node::process_contains_module(strImage, processID, scopedstrLibrary);

   }


::process_identifier_array node::shared_library_process(string_array_base& straProcesses, const ::scoped_string & scopedstrLibrary)
   {

      throw ::interface_only();

   }


   string node::get_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable)
   {

      return ::getenv(scopedstrEnvironmentVariable);

   }


   void node::set_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable, const ::scoped_string & scopedstrPayload)
   {
      
      ::string strKey(scopedstrEnvironmentVariable);
      
      ::string strPayload(scopedstrPayload);

      ::setenv(strKey, strPayload, 1);

   }

   void node::unset_environment_variable(const ::scoped_string & scopedstrEnvironmentVariable)
   {
   
      ::unsetenv(scopedstrEnvironmentVariable);
      
   }


   string node::expand_environment_variables(const ::scoped_string & scopedstr)
   {

      return ::__expand_environment_variables(scopedstr);

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

/*#ifdef LINUX

      dbus_do_power_off("Reboot");

#endif*/
#if !defined(APPLE_IOS)


   int iErrorCode =  ::system("systemctl reboot");

      if(iErrorCode)
      {

         throw ::exception(error_failed);


      }

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

      string str = file_system()->as_string("/proc/stat");

      string_array_base stra;

      stra.add_lines(str);

      return (int) stra.predicate_get_count([](auto str) { return str.begins("cpu"); });

#endif

   }


//   void node::aaa_user_post(const ::procedure & procedure)
//   {
//
//      ::platform::node::aaa_node_post(procedure);
//
//   }



   void node::call_async(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay,
      bool bPrivileged, unsigned int * puiPid)
   {

      string strCmdLine;

      strCmdLine = scopedstrParam;

      if (ansi_length(scopedstrParam) > 0)
      {

         strCmdLine += " ";

         strCmdLine += scopedstrParam;

      }

      auto processId = create_process(strCmdLine);

      if (puiPid != nullptr)
      {

         *puiPid = (unsigned int) processId;

      }

   }


   void node::call_sync(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay,
      const class time & timeTimeout, ::property_set & set, int * piExitCode)
   {

      string strCmdLine;

      strCmdLine = scopedstrPath;

      if (ansi_length(scopedstrParam) > 0)
      {

         strCmdLine += " ";

         strCmdLine += scopedstrParam;

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


::process_identifier node::create_process(const ::scoped_string & scopedstrCommandLine)
   {

      string_array_base stra;

      stra = get_c_args_for_c(scopedstrCommandLine);

      address_array_base < char * > argv;

      for (auto & str : stra)
      {

         argv.add((char *)str.c_str());

      }

      argv.add(nullptr);

      auto envp = ::system()->m_envp;

      pid_t pid = 0;

      string strExe = argv[0];

#ifdef __ANDROID__

      int status = -1;

      throw ::exception(todo);

#else

      int status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv.data(), envp);

#endif

      if (status == 0)
      {

         if (strExe.case_insensitive_ends("_app_core_clockverse"))
         {

            informationf("app-core/clockverse");

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

            informationf("app-core/clockverse");

         }

         throw ::exception(error_failed, "posix::acme_posix::create_process");

      }

   }


   int node::_create_process3(const ::string & _cmd_line, int * pprocessId)
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

      int      argc = 0;

      prepare_argc_argv(argc, argv, cmd_line);

      pid_t pid;

      int status;

      auto envp = ::system()->m_envp;

#ifdef __ANDROID__

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


   void node::run_silent(const ::scoped_string & scopedstrFunct, const ::scoped_string & scopedstrstrParams)
   {

#if defined(UNIVERSAL_WINDOWS)

      throw ::interface_only();

#elif defined(WINDOWS_DESKTOP)

      STARTUPINFO StartupInfo;

      PROCESS_INFORMATION ProcessInfo;

      char Args[4096];

      char * pEnvCMD = nullptr;

      const ::scoped_string & scopedstrDefaultCMD = "CMD.EXE";

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

      strCmdLine = scopedstrFunct;

      if (scopedstrstrParams.has_character())
      {

         strCmdLine += " ";

         strCmdLine += scopedstrstrParams;

      }

      //unsigned int processId;

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


   //::e_status node::shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, ::time timeTimeout)
   //{

   //   ::property_set set;

   //   call_sync(scopedstrFile, pszParams, ::file::path(scopedstrFile).folder(), e_display_none, timeTimeout, set);

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

      return (const_char_pointer )mem.data();

   }


   //      ::int_array_base node::module_path_get_pid(const ::scoped_string & scopedstrPath)
   //      {
   //
   //         ::int_array_base ia;
   //
   //         ::file::path_array_base stra;
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


::process_identifier_array node::module_path_processes_identifiers(const ::scoped_string & scopedstr, bool bModuleNameIsPropertyFormatted)
   {

      information("os/linux_process.cpp app_get_pid (" + string(scopedstr) + ")");

   ::process_identifier_array ia;

      ::file::listing_base listing;

      listing.set_folder_listing("/proc");

      directory_system()->enumerate(listing);

      string str(scopedstr);

      str = "app=" + str;

      string strApp(scopedstr);

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

            if (path.has_character())
            {

               //information(path + "\n");

            }

            //string strTitle = path.title();

            string strPath = path;

            strPath.case_insensitive_ends_eat(" (deleted)");

            //if (strTitle == strApp ||
               //  strTitle == strApp2)
            if (strPath == scopedstr)
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

      string_array_base stra;

      string str;

      str = "/proc/" + ::as_string(iPid) + "/cmdline";

      memory mem = file_system()->as_memory(str);

      if(mem.is_empty())
      {

         return {};

      }

      const_ansi_range rangeArgument;

      //char ch;

      rangeArgument.m_begin = (const_char_pointer )mem.begin();

      rangeArgument.m_end = (const_char_pointer )mem.data();

      bool bHasSpace = false;

      while(true)
      {

         if (rangeArgument.m_end >= (const_char_pointer )mem.end() || *rangeArgument.m_end == '\0')
         {

            if(rangeArgument.has_character())
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

            if(rangeArgument.m_end >= (const_char_pointer )mem.end())
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


//   bool node::is_shared_library_busy(::process_identifier processid, const string_array_base & stra)
//   {
//
//      return false;
//
//   }
//
//
//   bool node::is_shared_library_busy(const string_array_base & stra)
//   {
//
//      return false;
//
//   }

//#if defined(__clang__) && !defined(__ANDROID__)
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

         int iGetChar = getchar();

         if(iGetChar == EOF)
         {

            break;

         }

      }

   }


   bool node::set_process_priority(::enum_priority epriority)
{
      
//#ifdef LINUX
      
//#error "please transfer the code commented below to linux-operating_system"
//
//#else
      
      return ::platform::node::set_process_priority(epriority);
      
///#endif
      
      
   }
//   {
//
//      int iPolicy = SCHED_OTHER;
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


   //void node::command_system(string_array_base & straOutput, int& iExitCode, const scoped_string & scopedstr, enum_command_system ecommandsystem, const class time & timeTimeout, ::particle * pparticleSynchronization, ::file::file * pfileLog)
   int node::__command_system(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrPipe, const ::trace_function & functionTrace)
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

      if(scopedstrPipe.has_character())
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

         if(scopedstrPipe.has_character())
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

#if defined(__ANDROID__) || defined(APPLE_IOS)

         throw ::exception(todo);

#else

// defined(OPENBSD)

         auto pszCommandLine = ansi_dup(scopedstr);

         int iErrNo = 0;
         
	auto stra = command_arguments_from_command_line(pszCommandLine);

//         glob_t gl{};

//	 ::glob(scopedstrCommandLine, 0, nullptr, &gl);

//         char **argv = __allocate_array< char * >(gl.gl_pathc + 1);

	auto p = strdupa_from_command_arguments(stra);

//         memory_copy(argv, gl.gl_pathv, gl.gl_pathc * sizeof(char *));

         p->add(nullptr);

         int iChildExitCode = execvp(p->element_at(0), (char **) p->data());

         if (iChildExitCode == -1)
         {

            iErrNo = errno;

         }

//         delete[]argv;

//	for(auto p :arga) if(::is_set(p)) ::free(p);

//         ::globfree(&gl);

         free(pszCommandLine);

         //_exit(iErrNo);
         
         exit(iErrNo);

//#else
/*
         auto pszCommandLine = ansi_dup(scopedstr);

         int iErrNo = 0;

         wordexp_t we{};

         wordexp(scopedstrCommandLine, &we, 0);

         char **argv = __allocate_array< char * >(we.we_wordc + 1);

         memory_copy(argv, we.we_wordv, we.we_wordc * sizeof(char *));

         int iChildExitCode = execvp(argv[0], &argv[0]);

         if (iChildExitCode == -1)
         {

            iErrNo = errno;

         }

         delete[]argv;

         wordfree(&we);

         free(scopedstrCommandLine);

         _exit(iErrNo);
*/
#endif

      }

      close(stdout_fds[1]);

      close(stderr_fds[1]);

      if(scopedstrPipe.has_character())
      {

         close(stdin_fds[0]);

      }

      fcntl(stdout_fds[0], F_SETFL, fcntl(stdout_fds[0], F_GETFL) | O_NONBLOCK);

      fcntl(stderr_fds[0], F_SETFL, fcntl(stderr_fds[0], F_GETFL) | O_NONBLOCK);

      if(scopedstrPipe.has_character())
      {

         fcntl(stdin_fds[1], F_SETFL, fcntl(stdin_fds[1], F_GETFL) | O_NONBLOCK);

      }

      const int buf_size = 4096;

      char buffer[buf_size];

      char chExitCode = 0;

      bool bExit = false;

      if (scopedstrPipe.has_character())
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

                  ::str::get_lines(strOutput, false, [&](auto & str, bool bCarriage)
                  {

                     functionTrace(e_trace_level_information, str, bCarriage);

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

                  ::str::get_lines(strError, false, [&](auto &str, bool bCarriage)
                  {

                     functionTrace(e_trace_level_error, str, bCarriage);

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

//      if (scopedstrPipe.has_character())
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

      ::str::get_lines(strOutput, true, [&](auto &str, bool bCarriage)
      {

         functionTrace(e_trace_level_information, str, bCarriage);

      });

      ::str::get_lines(strError, true, [&](auto &str, bool bCarriage)
      {

         functionTrace(e_trace_level_error, str, bCarriage);

      });

      //::str::get_lines(straOutput, strOutput, "I: ", true, &singlelock, pfileLog);

      //::str::get_lines(straOutput, strError, "E: ", true, &singlelock, pfileLog);

   }

      return iExitCode;

   }


   int node::command_system(const ::scoped_string & scopedstr,  const ::trace_function & functionTrace, const ::file::path & pathWorkingDirectory, ::e_display edisplay)
   {
   
#if DEEP_LOG_HERE > 6
   
      information() << "acme_posix::node::command_system (1)";
   
#endif

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
   
#if DEEP_LOG_HERE > 6
   
      information() << "acme_posix::node::command_system (2)";
   
#endif

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
//#if !defined(_APPLE_IOS_)
//   char **argv;
//#endif

#if DEEP_LOG_HERE > 6

      information() << "acme_posix::node::command_system (3): executable: " << strExecutable;
   
#endif
   
#if defined(APPLE_IOS)
   
      //argv = nullptr;
   
#else

      auto pszExecutable = ::c::strdup(strExecutable);
  
//  printf("\n\n");
  
//  printf("pszExecutable : %s\n", pszExecutable);
   
      auto pszCommandLine = ansi_dup(scopedstr);
  
#if DEEP_LOG_HERE > 6
  
      information() << "acme_posix::node::command_system (3): command_line: " << pszCommandLine;
  
#endif
 
//  printf("pszCommandLine : %s\n", pszCommandLine);

      int iErrNo = 0;
  
      auto stra = command_arguments_from_command_line(pszCommandLine);

//         glob_t gl{};

//	 ::glob(scopedstrCommandLine, 0, nullptr, &gl);

//         char **argv = __allocate_array< char * >(gl.gl_pathc + 1);

      auto p = strdupa_from_command_arguments(stra);
	
#ifdef _DEBUG

#if DEEP_LOG_HERE > 6
      
      printf("command count: %lld\n", p->size());

      for(int i = 0; i < p->size(); i++)
      {

         printf("command[%d] = : \"%s\"\n", i, p->element_at(i));

      }	
   
#endif

#endif

//         memory_copy(argv, gl.gl_pathv, gl.gl_pathc * sizeof(char *));

      p->add(nullptr);

      __refdbg_add_referer;
	
      p->increment_reference_count();

//         int iChildExitCode = execvp(arga[0], arga.data());

  //       if (iChildExitCode == -1)
    //     {

      //      iErrNo = errno;

        // }

//         delete[]argv;


  
// #if defined(OPENBSD)
/*
   glob_t gl{};

   ::glob(scopedstrCommandLine, 0, nullptr, &gl);

   argv = ___new char * [gl.gl_pathc + 1];

   printf("glob count : %lu\n", gl.gl_pathc);
   
   for(::collection::index i = 0; i < gl.gl_pathc; i++)
   {
      
      auto arg = gl.gl_pathv[i];
      
      argv[i] = arg;
      
      printf("glob path[%lld] : %s\n", i, arg);
      
   }
   
   argv[gl.gl_pathc] = nullptr;
*/
//#else
/*
   auto pszExecutable = ::c::strdup(strExecutable);
   
   auto pszCommandLine = ansi_dup(scopedstr);

   int iErrNo = 0;
   
   wordexp_t we{};

   wordexp(scopedstrCommandLine, &we, 0);

   argv = ___new char * [we.we_wordc + 1];
   
   for(::collection::index i = 0; i < we.we_wordc; i++)
   {
      
      auto arg = we.we_wordv[i];
      
      argv[i] = arg;
      
   }
   
   argv[we.we_wordc] = nullptr;
   
   */
   
//#endif
   
#endif

//   if(scopedstrPipe.has_character())
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
         {
            
         }
   
         while ((dup2(stderr_fds[1], STDERR_FILENO) == -1) && (errno == EINTR))
         {
            
         }

//      if(scopedstrPipe.has_character())
//      {
//
//         while ((dup2(stdin_fds[0], STDIN_FILENO) == -1) && (errno == EINTR))
//         {}
//
//      }

         close(stdout_fds[0]);

         close(stdout_fds[1]);

         close(stderr_fds[0]);

         close(stderr_fds[1]);
//
//      close(stdin_fds[0]);

      //close(stdin_fds[1]);

#if defined(__ANDROID__) || defined(APPLE_IOS)

         throw ::exception(todo);

#else

//printf("executable: %s\n", pszExecutable);

////auto pIter = p;

//for(auto pIter : *p)
//{
   
//   if(pIter)
//   {
   
//      printf("arguments: %s\n", pIter);
      
//   }
   
//}

         int iChildExitCode = execvp(pszExecutable, (char **) p->data());

         if (iChildExitCode == -1)
         {

            iErrNo = errno;

         }

         p.release();

  //    delete[]argv;
/*      
#if defined(OPENBSD)
      
      globfree(&gl);

#else      

      wordfree(&we);

#endif
*/
         free(pszCommandLine);
      
         free(pszExecutable);

         //_exit(iErrNo);
         
         exit(iErrNo);

#endif

      }

      close(stdout_fds[1]);

      close(stderr_fds[1]);

//   if(scopedstrPipe.has_character())
//   {
//
//      close(stdin_fds[0]);
//
//   }
//
   
      fcntl(stdout_fds[0], F_SETFL, fcntl(stdout_fds[0], F_GETFL) | O_NONBLOCK);

      fcntl(stderr_fds[0], F_SETFL, fcntl(stderr_fds[0], F_GETFL) | O_NONBLOCK);

//   if(scopedstrPipe.has_character())
//   {
//
//      fcntl(stdin_fds[1], F_SETFL, fcntl(stdin_fds[1], F_GETFL) | O_NONBLOCK);
//
//   }

      const int buf_size = 4096;

      char buffer[buf_size];

      char chExitCode = 0;

      bool bExit = false;

//   if (scopedstrPipe.has_character())
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
            
#if DEEP_LOG_HERE > 6
    
#ifdef _DEBUG
            
               information() << "partial stdout output: \"" << strOutput << "\""; 
            
#endif

#endif

               if(functionTrace)
               {

                  ::str::get_lines(strOutput, false, [&](auto & str, bool bCarriage)
                  {

                     functionTrace(e_trace_level_information, str, bCarriage);

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
            
#if DEEP_LOG_HERE > 6
            
#ifdef _DEBUG            
            
               information() << "partial stderr output: \"" << strOutput << "\""; 

#endif

#endif


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

                  ::str::get_lines(strError, false, [&](auto &str, bool bCarriage)
                  {

                     functionTrace(e_trace_level_error, str, bCarriage);

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

#if DEEP_LOG_HERE > 6
         
            informationf("waitpid: exiting waitpid loop (1)");
         
#endif

            break;

         }

         {

            int status = 0;

            int iWaitPid = waitpid(pid, &status, WNOHANG | WUNTRACED | WCONTINUED);

            if(iWaitPid == -1)
            {
               
   #if DEEP_LOG_HERE > 6
               
               int iErrorNo = errno;

               information("waitpid -1 error errno={} (\"{}\")", iErrorNo, strerror(iErrorNo));
               
   #endif

               //if(iErrorNo != ECHILD)
               //{

                  //break;

                  bExit = true;

               //}

            }
            else if(iWaitPid == 0)
            {
				
	#if DEEP_LOG_HERE > 6
               
               information("waitpid 0  child didn't exit yet");
               
   #endif
			
			}
            else
            {
               
   #if DEEP_LOG_HERE > 6
               
               informationf("waitpid: iWaitPid=%d, pid=%d", iWaitPid, pid);
               
   #endif

               if (WIFEXITED(status))
               {

                  chExitCode = WEXITSTATUS(status);

                  iExitCode = chExitCode;
                  
   #if DEEP_LOG_HERE > 6
                  
                  informationf("exit_code: status=%d, iExitCode=%d", status, iExitCode);
                  
   #endif

                  //break;

               }

               bExit = true;

            }

         }

         if(!bRead && !bExit)
         {
            
   #if DEEP_LOG_HERE > 6
            
            informationf("waitpid: preempting for 25_ms");
            
   #endif

            preempt(25_ms);

         }

      }
   
#if DEEP_LOG_HERE > 6
         
      informationf("waitpid: preempting for 25_ms");
         
#endif
   

      close(stdout_fds[0]);

      close(stderr_fds[0]);

//      if (scopedstrPipe.has_character())
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

         ::str::get_lines(strOutput, true, [&](auto &str, bool bCarriage)
         {

            functionTrace(e_trace_level_information, str, bCarriage);

         });

         ::str::get_lines(strError, true, [&](auto &str, bool bCarriage)
         {

            functionTrace(e_trace_level_error, str, bCarriage);

         });

         //::str::get_lines(straOutput, strOutput, "I: ", true, &singlelock, pfileLog);

         //::str::get_lines(straOutput, strError, "E: ", true, &singlelock, pfileLog);

      }

      return iExitCode;

   }


   void node::launch_process(const ::scoped_string & scopedstr)
   {
   
#if DEEP_LOG_HERE > 6
   
      information() << "acme_posix::node::launch_process (1)";
   
#endif

      
      auto range = scopedstr();
      
      ::string strExecutable(range.consume_command_line_argument());

#if DEEP_LOG_HERE > 6

      information() << "acme_posix::node::launch_process (2): executable: " << strExecutable;
   
#endif
   
      auto pszExecutable = ::c::strdup(strExecutable);

      auto stra = command_arguments_from_command_line(scopedstr);

      auto p = strdupa_from_command_arguments(stra);
	
#ifdef _DEBUG

#if DEEP_LOG_HERE > 6
      
      printf("command count: %lld\n", p->size());

      for(int i = 0; i < p->size(); i++)
      {

         printf("command[%d] = : \"%s\"\n", i, p->element_at(i));

      }	
   
#endif

#endif

      p->add(nullptr);

      __refdbg_add_referer;
	
      p->increment_reference_count();

      const pid_t pid = ::fork();

      if (!pid)
      {

#if defined(__ANDROID__) || defined(APPLE_IOS)

         __UNREFERENCED_PARAMETER(pszExecutable);
         
         throw ::exception(todo);

#else

         setsid();

         int iChildExitCode = execvp(pszExecutable, (char **) p->data());

         if (iChildExitCode == -1)
         {

            iChildExitCode = errno;

         }
         
         p.release();
         
         free(pszExecutable);

         //_exit(iChildExitCode);
         
         exit(iChildExitCode);

#endif

      }

   }


   ::file::path node::library_file_name(const ::scoped_string& scopedstr)
   {

      return "lib" + scopedstr + ".so";

   }


   int node::posix_shell_command(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell, const trace_function& tracefunction)
   {

      try
      {

         ::string strUnixShell;

#if defined(FREEBSD)

		strUnixShell = "/usr/local/bin/bash";

#elif defined(OPENBSD)

        strUnixShell = "/bin/ksh";

#elif defined(NETBSD)

         strUnixShell = "/bin/sh";

#else

         strUnixShell = "/bin/bash";

#endif

         ::string strCommand;

         ::string strCommandInner;

         strCommandInner = scopedstrCommand.as_string().c_str();

         strCommandInner.find_replace("\\", "\\\\");

         strCommandInner.find_replace("\"", "\\\"");

         strCommand.formatf("\"%s\" -c \"%s\"", strUnixShell.c_str(), strCommandInner.c_str());
         
#ifdef _DEBUG
         
         informationf("acme_posix::node::unix_shell_command command: %s", strCommand.c_str());
         
#endif

         auto iExitCode = this->command_system(strCommand, tracefunction);

         return iExitCode;

      }
      catch (...)
      {

      }

      return -1;

   }

   
   bool node::is_executable_in_path(const ::scoped_string &scopedstr)
   {
      
      ::string strPath;
   
      int iExitCode = get_posix_shell_command_output(strPath, "command -v " + scopedstr, e_posix_shell_system_default);
      
      information() << "command -v : " << scopedstr << " output => " << strPath;
      
      if(iExitCode != 0 || strPath.is_empty())
      {
         
         return false;
         
      }
      
      return true;
      
   }


   bool node::has_command(const ::scoped_string& scopedstrCommand)
   {

      return has_posix_shell_command(scopedstrCommand);

   }



   void node::detached_command(const ::scoped_string & scopedstrCommand, const ::file::path & pathLog)
   {

      ::string strCommand;

      ::string strCommandToDetach(scopedstrCommand);

      if(pathLog.has_character())
      {

         strCommand.formatf("/bin/sh -c \"nohup %s > \\\"%s\\\"\"",
                             strCommandToDetach.c_str(),
                             pathLog.c_str());
      }
      else
      {

         strCommand.formatf("/bin/sh -c \"nohup %s\"", strCommandToDetach.c_str());

      }


      printf_line("Going to execute command: \"%s\"", strCommand.c_str());

      auto log = std_inline_log();

      log.set_timeout(5_min);

      auto iExitCode = this->command_system(strCommand, log);

      if(iExitCode != 0) {

         throw ::exception(error_failed);

      }

   }


   bool node::_is_code_exe_user_path_environment_variable_ok(::string* pstrCorrectPath, const_char_pointer pszPath)
   {

      information() << "_is_code_exe_user_path_environment_variable_ok";

      ::string strEnvironmentVariable;

      if(::is_null(pszPath))
      {

         strEnvironmentVariable = get_environment_variable("PATH");

         pszPath = strEnvironmentVariable.c_str();

      }

      information() << "PATH : " << pszPath;

      bool bChanged = false;

      auto pathHomeBin = directory_system()->home() / "bin";

      auto pathToolBin = path_system()->tool_folder_path() / "bin";

// #if defined(MACOS)

//       auto pathToolBin = directory_system()->home() / "workspace/operating_system/tool-macos/bin";

// #else

//       auto pathToolBin = directory_system()->home() / "cmake/operating_system/tool-" OPERATING_SYSTEM_NAME "/bin";

// #endif

      ::string_array_base straPath;

      straPath.explode(":", pszPath);

      ::string strPath = pszPath;

      if (!straPath.contains(pathHomeBin))
      {

         strPath += ":" + pathHomeBin;

         bChanged = true;

      }

      if (!straPath.contains(pathToolBin))
      {

         strPath += ":" + pathToolBin;

         bChanged = true;

      }

      if (!bChanged)
      {

         return true;

      }

      if (::is_set(pstrCorrectPath))
      {

         *pstrCorrectPath = strPath;

      }

      return false;

   }




   bool node::_is_jetbrains_clion_installed()
   {

      ::file::listing_base listing;

      auto pathJetbrains = directory_system()->home() / ".config/JetBrains";

      listing.set_folder_listing(pathJetbrains);

      directory_system()->enumerate(listing);

      for(auto & path : listing)
      {
         if(path.name().case_insensitive_begins("CLion"))
         {

            return true;

         }
      }

      return false;

   }


   bool node::_is_git_credential_manager_installed()
   {

      if(!node().has_posix_shell_command("git-credential-manager"))
      {

         return false;

      }

      return true;

   }

#if defined(WINDOWS_DESKTOP) || defined(MACOS) || defined(LINUX)


   bool node::_is_smart_git_installed()
   {

      ::file::listing_base listing;

      auto pathJetbrains = directory_system()->home() / ".config/smartgit";

      listing.set_folder_listing(pathJetbrains);

      directory_system()->enumerate(listing);

      for(auto & path : listing)
      {
         auto pathPreferences = path / "preferences.yml";

         if(file_system()->exists(pathPreferences))
         {

            return true;

         }
      }

      return false;

   }


#endif


   int node::synchronous_posix_terminal(const ::scoped_string& scopedstrCommand, enum_posix_shell eposixshell, const trace_function& tracefunction)
   {

      auto edesktop = ::windowing::get_eoperating_ambient();

      ::string strCommand(scopedstrCommand);

      int iExitCode = -1;

      if(edesktop == ::windowing::e_operating_ambient_xfce
              || edesktop == ::windowing::e_operating_ambient_kde)
      {

         strCommand.find_replace("\\", "\\\\");

         strCommand.find_replace("\"", "\\\"");

         strCommand.find_replace("\n", "\\n");

         iExitCode = this->command_system(
                 "xterm -e bash -c \"" + strCommand+"\"",
                 tracefunction);

      }
//      else if(edesktop == ::user::e_operating_ambient_kde)
//      {
//
//         strCommand.find_replace("\\", "\\\\");
//
//         strCommand.find_replace("\"", "\\\"");
//
//         iExitCode = this->command_system(
//                 "konsole -e /bin/bash -c \"" + strCommand + "\"",
//                 tracefunction);
//
//      }
      else
      {

         strCommand.find_replace("\\", "\\\\");

         strCommand.find_replace("\"", "\\\"");

          strCommand.find_replace("\n", "\\n");

          iExitCode = this->command_system(
                 "gnome-terminal --wait -- /bin/bash -c \"" + strCommand + "\"",
                 tracefunction);

      }

      return iExitCode;

   }


   bool node::_is_google_chrome_installed()
   {

      bool bInstalled = has_posix_shell_command("google-chrome");

      return bInstalled;

   }


   bool node::_is_visual_studio_code_installed()
   {

      bool bInstalled = has_posix_shell_command("code");

      return bInstalled;

   }


   // bool node::_is_dropbox_installed()
   // {
   //
   //    if (!m_bDropboxCalculated)
   //    {
   //
   //       calculate_dropbox_installed();
   //
   //    }
   //
   //    return m_bDropbox;
   //
   // }

//    void node::do_windowing_factory()
//    {
//
//       ::platform::node::do_windowing_factory();
//
// //       auto edesktop = get_eoperating_ambient();
// //
// //       if(edesktop == user::e_operating_ambient_kde)
// //       {
// //
// //          auto pfactory = system()->factory("windowing_system", "kde5");
// //
// //          pfactory->merge_to_global_factory();
// //
// //       }
// //       else
// //       {
// //
// // #ifdef HAS_GTK3
// //
// //          auto pfactory = system()->factory("windowing_system", "gtk3");
// //
// //          pfactory->merge_to_global_factory();
// //
// // #else
// //
// //          auto pfactory = system()->factory("windowing_system", "gtk4");
// //
// //          pfactory->merge_to_global_factory();
// //
// // #endif
// //
// //       }
//
//    }


   void node::on_system_main()
   {
      if (::system()->is_console())
      {

         application()->main();

      }
      else
      {

         // if(system()->m_htask == ::current_htask())
         // {
         //
         //    system()->m_htask = nullptr;
         //
         // }
         //
         // if(system()->m_itask == ::current_itask())
         // {
         //
         //    system()->m_itask = nullptr;
         //
         // }
         //
         // system()->branch_synchronously();

         system()->acme_windowing()->windowing_application_main_loop();


      }
   }

   ::string node::default_component_implementation(const ::scoped_string & scopedstrComponentName)
   {

      if(scopedstrComponentName == "nano_graphics")
      {
         
#if defined(__APPLE__)
         
         return "quartz2d";
         
#else

         return "cairo";
         
#endif

      }
      else if(scopedstrComponentName == "nano_http")
      {
         
#ifdef CUBE

#if defined(LINUX) || defined(__BSD__)

         return "command_line";
         
#endif

#endif
         
         return "libcurl";

      }
      else if(scopedstrComponentName == "nano_idn")
      {
         
         return "libidn";

      }
      else if(scopedstrComponentName == "nano_compress")
      {
         
#ifdef CUBE

#if defined(LINUX) || defined(__BSD__)

         return "command_line";
         
#endif

#endif
         
         return "zlib";

      }

      return ::platform::node::default_component_implementation(scopedstrComponentName);

   }

   //https://stackoverflow.com/questions/27914311/get-computer-name-and-logged-user-name
//#include <unistd.h>
//#include <limits.h>
   ::string node::get_computer_name()
   {
      char hostname[HOST_NAME_MAX * 4];
      //char username[LOGIN_NAME_MAX];
      int error = gethostname(hostname, sizeof(hostname));

      if (error)
      {

return{};

      }

      return hostname;

   }


   ::string node::system_name()
   {

      return _uname_system();

   }
   
   
   ::string node::system_release()
   {

      return _uname_release();

   }


   ::string node::system_architecture()
   {

      return _uname_machine();

   }


   ::string node::dynamic_library_prefix()
   {

      return "lib";

   }


   ::string node::dynamic_library_suffix()
   {

      return ".so";

   }


   bool node::posix_try_open_internet_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::string_array_base & straBrowsers)
   {

      ::string strUrl(scopedstrUrl);

      printf_line("posix_try_open_internet_link trying to open url : %s", strUrl.c_str());

      for (auto &browser : straBrowsers)
      {

         printf_line("trying browser : %s", browser.c_str());

         auto path = command_find_path(browser);

         if (path.has_character())
         {

            printf_line("found browser : %s at path : %s", browser.c_str(), path.c_str());

            if (command_system(::string(path) + " " + strUrl) == 0)
            {

               return true;

            }

         }
         else
         {

            printf_line("Couldn't find browser : %s", browser.c_str());

         }


      }

      printf_line("posix_try_open_internet_link failed to find browser to open internet link");

         return false;

   }


} // namespace acme_posix


::string string_expand_environment_variables(const ::scoped_string & scopedstr);


::string __expand_environment_variables(const ::scoped_string & scopedstr)
{
 
   ::string str(scopedstr);
   
   auto strExpanded = string_expand_environment_variables(str);
   
   return strExpanded;

}


