//
// Created by camilo on 2023-04-14 21:28 <3ThomasBorregaardSorensen!!
//
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

      argv[argc] = ansi_dup((char *)str.c_str());

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

      argv[argc] = ansi_dup((char *)str.c_str());

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



