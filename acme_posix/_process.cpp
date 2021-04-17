//
// Created by camilo on 14/04/2021. 00:23 BRT <3TBS_!!
//
#include "framework.h"
#include "acme/platform/static_start.h"


extern char **environ;


struct chldstatus
{

   bool m_bRet;
   int  m_iExitCode;

};


typedef iptr_map < chldstatus > chldstatus_map;


critical_section * g_pcsPid2 = nullptr;


chldstatus_map * g_ppid = nullptr;


critical_section * get_pid_cs()
{

   critical_section_lock cs(::acme::get_global_critical_section());

   if(g_pcsPid2 == nullptr)
   {

      g_pcsPid2 = new critical_section();

      g_ppid = new chldstatus_map();


   }

   return g_pcsPid2;

}


chldstatus get_chldstatus(int iPid)
{

   critical_section_lock synchronouslock(get_pid_cs());

   return g_ppid->operator[](iPid);

}

// must be called under get_pid_cs lock
void init_chldstatus(int iPid)
{

   auto & s = g_ppid->operator[](iPid);

   s.m_bRet = false;

   s.m_iExitCode = 0;

}


void ansios_sigchld_handler(int sig)
{

   int saved_errno = errno;

   int iExitCode;

   int iPid;

   while((iPid = waitpid(-1, &iExitCode,
                         WUNTRACED
#ifdef WNOHANG
      | WNOHANG
#endif
#ifdef WCONTINUED
      | WCONTINUED
#endif
   )) > 0)
   {

      {

         critical_section_lock synchronouslock(get_pid_cs());

         auto ppair = g_ppid->plookup(iPid);

         if(ppair != nullptr)
         {

            ppair->element2().m_bRet = true;

            ppair->element2().m_iExitCode = iExitCode;

         }

      }

   }

   errno = saved_errno;

}

