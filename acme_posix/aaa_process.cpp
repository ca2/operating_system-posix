//
// Created by camilo on 2021-05-16 19:47 BRT  <3ThomasBorregaardSoerensen!!
//
#include "framework.h"
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

CLASS_DECL_ACME void dll_processes(unsigned_int_array & dwa, string_array & straProcesses, const ::scoped_string & scopedstrDll)
{

   __UNREFERENCED_PARAMETER(dwa);
   __UNREFERENCED_PARAMETER(straProcesses);
   __UNREFERENCED_PARAMETER(scopedstrDll);

}


namespace acme
{


   namespace posix
   {


      void node::call_async(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay,
         bool bPrivileged, unsigned int * puiPid)
      {

         string strCmdLine;

         strCmdLine = pszPath;

         if (ansi_length(scopedstrParam) > 0)
         {

            strCmdLine += " ";

            strCmdLine += pszParam;

         }

         unsigned int processId;

         create_process(strCmdLine, &processId);

         if (puiPid != nullptr)
         {

            *puiPid = processId;

         }

      }


      void node::call_sync(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDir, ::e_display edisplay,
         const ::duration & durationTimeout, ::property_set & set)
      {

         string strCmdLine;

         strCmdLine = pszPath;

         if (ansi_length(scopedstrParam) > 0)
         {

            strCmdLine += " ";

            strCmdLine += pszParam;

         }

         unsigned int processId;

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


      void node::create_process(const ::scoped_string & scopedstrCommandLine, unsigned int * pprocessId)
      {

         string_array stra;

         stra = get_c_args_for_c(scopedstrCommandLine);

         address_array < char * > argv;

         for(auto & str : stra)
         {

            argv.add((char *) str.c_str());

         }

         argv.add(nullptr);
         
         auto envp = system()->m_envp;

         pid_t pid = 0;

         string strExe = argv[0];

         int status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv.get_data(), envp);

         if (status == 0)
         {

            if(strExe.case_insensitive_ends("_app_core_clockverse"))
            {

               informationf("app-core/clockverse");

            }

            if(pprocessId != nullptr)
            {

               *pprocessId = pid;

            }

            return;

         }
         else
         {

            if(strExe.case_insensitive_ends("_app_core_clockverse"))
            {

               informationf("app-core/clockverse");

            }

            throw ::exception(error_failed, "posix::acme_posix::create_process");

         }

      }


      int node::_create_process3(const ::string & _cmd_line, int * pprocessId)
      {

         //char *   exec_path_name;

         char *   cmd_line;

         //char *   cmd_line2;

         cmd_line = strdup(_cmd_line);

         if(cmd_line == nullptr)
         {

            return 0;

         }

         char *      argv[1024 + 1];

         int      argc = 0;

         prepare_argc_argv(argc, argv, cmd_line);

         pid_t pid;

         int status;
         
         auto envp = system()->m_envp;

         status = posix_spawn(&pid, argv[0], nullptr, nullptr, argv, envp);

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

         unsigned int processId;

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


      //::e_status node::shell_execute_sync(const ::scoped_string & scopedstrFile, const ::scoped_string & scopedstrParams, ::duration durationTimeout)
      //{

      //   ::property_set set;

      //   call_sync(scopedstrFile, pszParams, ::file::path(scopedstrFile).folder(), e_display_none, durationTimeout, set);

      //   return ::success;

      //}


      string node::module_path_from_pid(unsigned int iPid)
      {

         struct stat sb;

         int iSize;

         string str;

#if defined(FREEBSD)

         str = "/proc/" + as_string(iPid) + "/file";

#else

         str = "/proc/" + as_string(iPid) + "/exe";

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


      //      ::int_array node::module_path_get_pid(const ::scoped_string & scopedstrPath)
      //      {
      //
      //         ::int_array ia;
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


      atom_array node::module_path_get_pid(const ::scoped_string & scopedstr, bool bModuleNameIsPropertyFormatted)
      {

         informationf("os/linux_process.cpp app_get_pid (" + string(scopedstr) + ")");

         atom_array ia;

         ::file::listing listing;

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
               ::file::path path = module_path_from_pid(iPid);

               if (path.has_character())
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

         str = "/proc/" + as_string(iPid) + "/cmdline";

         memory mem = file_system()->as_memory(str);

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

               strArg.empty();

            }
            else
            {

               strArg += ch;

            }


         }

         if (strArg.has_character())
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


      bool node::is_shared_library_busy(unsigned int processid, const string_array & stra)
      {

         return false;

      }


      bool node::is_shared_library_busy(const string_array & stra)
      {

         return false;

      }


   } // namespace posix


} // namespace amce


#ifdef LINUX

int daemonize_process(const ::scoped_string & scopedstrCommandLine, int * pprocessId)
{

   string_array stra;

   stra = get_c_args_for_c(scopedstrCommandLine);

   char ** argv = (char **) malloc(sizeof(char *) * (stra.get_size() + 1));

   int argc = 0;

   for(auto & str : stra)
   {

      argv[argc] = strdup((char *) str.c_str());

      argc++;

   }

   argv[argc] = nullptr;

   pid_t pid;

   pid = fork();

   if (pid == -1)
   {

      printf("fork error\n");

      char ** pargv = argv;

      while(*pargv != nullptr)
      {

         free(*pargv);

         pargv++;

      }

      free(argv);

      return 0;

   }
   else if(pid > 0)
   {

      return 1;

   }

   daemon(0, 0);

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

   while(*pargv != nullptr)
   {

      free(*pargv);

      pargv++;

   }

   free(argv);

   exit(iExitCode);


   return 0;

}


#endif


int create_process4(const ::scoped_string & scopedstrCommandLine, int * pprocessId)
{

   string_array stra;

   stra = get_c_args_for_c(scopedstrCommandLine);

   char ** argv = (char **) malloc(sizeof(char *) * (stra.get_size() + 1));

   int argc = 0;

   for(auto & str : stra)
   {

      argv[argc] = strdup((char *) str.c_str());

      argc++;

   }

   argv[argc] = nullptr;

   if((*pprocessId = fork()) == 0)
   {

      execv(argv[0], argv);

      int status = 0;
      char ** pargv = argv;

      while(*pargv != nullptr)
      {

         free(*pargv);

         pargv++;

      }

      free(argv);

      exit(status);

   }
   else if(*pprocessId == -1)
   {

      *pprocessId = 0;

      char ** pargv = argv;

      while(*pargv != nullptr)
      {

         free(*pargv);

         pargv++;

      }

      free(argv);

      return 0;

   }

   return 1;

}


namespace acme
{


   namespace posix
   {




   } // namespace posix


} // namespace acme







CLASS_DECL_ACME int ca2_main();



int create_process2(const ::scoped_string & scopedstrCommandLine, int * pprocessId)
{

   string_array stra;

   stra = get_c_args_for_c(scopedstrCommandLine);

   char ** argv = (char **) malloc(sizeof(char *) * (stra.get_size() + 1));

   int argc = 0;

   for(auto & str : stra)
   {

      argv[argc] = strdup((char *) str.c_str());

      argc++;

   }

   argv[argc] = nullptr;

   pid_t pid = 0;

   if((pid = fork()) == 0) // child
   {

      int iExitCode = execv(argv[0], argv);

      char ** pargv = argv;

      while(*pargv != nullptr)
      {

         free(*pargv);

         pargv++;

      }

      free(argv);

      exit(iExitCode);

   }
   else if(pid == -1) // in parent, but error
   {

      char ** pargv = argv;

      while(*pargv != nullptr)
      {

         free(*pargv);

         pargv++;

      }

      free(argv);

      return 0;

   }

   if(pprocessId != nullptr)
   {

      *pprocessId = pid;

   }

   return 1;

}


CLASS_DECL_ACME ::file::path core_app_path(string strApp)
{

   strApp.find_replace("-", "_");

   strApp.find_replace("/", "_");

   return "/xcore/time/x64/basis/" + strApp;

}


unsigned int get_current_process_id()
{

   return getpid();

}



