// Created on 2021-04-29 1:03 PM BRT <3TBS_!! Second celebration of Mummis Birthday 70!!
#include "framework.h"
//#if defined(FREEBSD) || defined(OPENBSD)
//#define __XSI_VISIBLE 1
//#endif
#include "exception_translator.h"
//#include "acme/exception/standard.h"
//#include "acme/platform/sequencer.h"
//#include "acme/user/user/conversation.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#if defined(LINUX)
#include "acme/operating_system/linux/standard_exception.h"
#elif defined(FREEBSD)
#include "acme/operating_system/freebsd/standard_exception.h"
#elif defined(OPENBSD)
#include "acme/operating_system/openbsd/standard_exception.h"
#elif defined(NETBSD)
#include "acme/operating_system/openbsd/standard_exception.h"
#elif defined(__APPLE__)
#include "acme/operating_system/apple/standard_exception.h"
#elif defined(__ANDROID__)
#include "acme/operating_system/android/standard_exception.h"
#endif


namespace acme_posix
{


   exception_translator::exception_translator()
   {

      m_bSet = false;

   }


   exception_translator::~exception_translator()
   {


   }


   void exception_translator::initialize(::particle *pparticle)
   {

      ::exception_translator::initialize(pparticle);

   }


   void exception_translator::sigsegv_handler(int signal, siginfo_t *psiginfo, void *pc)
   {

      sigset_t set;
      sigemptyset(&set);
      sigaddset(&set, SIGSEGV);
      pthread_sigmask(SIG_UNBLOCK, &set, nullptr);

      throw standard_access_violation(signal, psiginfo, pc);

   }


   void exception_translator::sigfpe_handler(int signal, siginfo_t *psiginfo, void *pc)
   {

      //sigset_t set;
      //sigemptyset(&set);
      //sigaddset(&set, SIGSEGV);
      //sigprocmask(SIG_UNBLOCK, &set, nullptr);

      //throw standard_sigfpe(signal, psiginfo, pc);

      output_debug_string("We are now here (with lowluds) inspecting exception_translator::sigfpe_handler");

   }


   void exception_translator::sigpipe_handler(int signal, siginfo_t *psiginfo, void *pc)
   {

      //      sigset_t set;
      //      sigemptyset(&set);
      //      sigaddset(&set, SIGSEGV);
      //      sigprocmask(SIG_UNBLOCK, &set, nullptr);

      ///throw standard_sigfpe(signal, psiginfo, pc);

   }


   bool exception_translator::attach()
   {

      if (m_bSet)
      {

         return true;

      }

      //informationf("exception standard translator");

#if defined(__SANITIZE_ADDRESS__) || defined(__FOR_PERF__)

      INFO("sanitize address compilation, not going to install standard exception translator");

#else

//#if !defined(__ANDROID__)

      install_sigsegv_handler();

      install_sigfpe_handler();

#if !defined(__APPLE__) && !defined(FREEBSD) || defined(__arm__)

      install_sigsegv_handler();

      install_sigfpe_handler();

      install_sigpipe_handler();

#endif

#endif

//#endif // !defined(__ANDROID__)

      m_bSet = true;

      return true;

   }


   void exception_translator::install_sigsegv_handler()
   {

      zero(m_sig.m_saSeg);

      m_sig.m_saSeg.sa_flags = SA_SIGINFO;

      m_sig.m_saSeg.sa_sigaction = &sigsegv_handler;

      int iSigactionResult = sigaction(SIGSEGV, &m_sig.m_saSeg, &m_sigOld.m_saSeg);

      if (iSigactionResult != 0)
      {

         informationf("failed to install segmentation fault signal handler");

         auto pmessagebox = message_box("failed to install segmentation fault signal handler",
                                               "failed to install segmentation fault signal handler",
                                               e_message_box_ok);

         pmessagebox->async();


      }

   }


   void exception_translator::install_sigfpe_handler()
   {

      zero(m_sig.m_saFpe);

      m_sig.m_saSeg.sa_flags = SA_SIGINFO;

      m_sig.m_saFpe.sa_sigaction = &sigfpe_handler;

      if (sigaction(SIGFPE, &m_sig.m_saFpe, &m_sigOld.m_saFpe) < 0)
      {

         informationf("failed to install floating point exception signal handler");

      }

   }


   void exception_translator::install_sigpipe_handler()
   {

      zero(m_sig.m_saPipe);

      //m_sig.m_saSeg.sa_flags = SA_SIGINFO;
      
      //m_sig.m_saSeg.sa_flags = SA_SIGINFO;
      //m_sig.m_saSeg.sa_flags = 0;
      //sigemptyset(&m_sig.m_saPipe.sa_mask);
      //m_sig.m_saPipe.sa_sigaction = &sigpipe_handler;
      //m_sig.m_saPipe.sa_sigaction = SIG_IGN;
      //m_sig.m_saPipe.sa_handler = SIG_IGN;

    //  if (sigaction(SIGPIPE, &m_sig.m_saPipe, &m_sigOld.m_saPipe) < 0)
  //    {
//
  //       informationf("failed to install pipe signal handler");
//
      //}
    //  else
  //    {
      
//		printf_line("Installed SIG PIPE handler");
		
//	  }
	
//	  preempt(5_s);

   }


   bool exception_translator::detach()
   {

      if (!m_bSet)
      {

         return false;

      }

#if defined(__SANITIZE_ADDRESS__) || defined(__FOR_PERF__)

      sigaction(SIGSEGV,&m_sigOld.m_saSeg, nullptr);

      sigaction(SIGFPE,&m_sigOld.m_saFpe,nullptr);

#endif

      m_bSet = false;

      return true;

   }


} // namespace acme_translator



