/*
 Copyright (ca) 2001
 Author: Konstantin Boukreev
 E-mail: konstantin@mail.primorye.ru
 Created: 25.12.2001 14:47:20
 Version: 1.0.0

 Permission to use, copy, modify, distribute and sell this software
 and its documentation for any purpose is hereby granted without fee,
 provided that the above copyright notice appear in all copies and
 that both that copyright notice and this permission notice appear
 in supporting documentation.  Konstantin Boukreev makes no representations
 about the suitability of this software for any purpose.
 It is provided "as is" without express or implied warranty.

 wrapper class for _set_se_translator API
 maps Win32 exceptions (C structured exceptions) into C++ typed exceptions.
*/
#pragma once


#include <signal.h>


#include "acme/exception/translator.h"


namespace acme_posix
{

class address_to_line :
virtual public ::particle
{
public:
   
   virtual int get_address_line(::string & strFunction, void * addr) = 0;
   
};


struct sig_companion
{

   struct sigaction m_saSeg;
   struct sigaction m_saFpe;
   struct sigaction m_saPipe;
   
};

   class CLASS_DECL_ACME exception_translator :
      virtual public ::exception_translator
   {
   protected:

      bool    m_bSet;

   public:

      ::pointer<address_to_line>      m_paddresstoline;
      sig_companion        m_sig;
      sig_companion        m_sigOld;
      

      exception_translator();
      ~exception_translator() override;
      
      void initialize(::particle * pparticle) override;

      
      static void sigsegv_handler(i32 signal, siginfo_t* psiginfo, void* pc);
      static void sigfpe_handler(i32 signal, siginfo_t* psiginfo, void* pc);
      static void sigpipe_handler(i32 signal, siginfo_t* psiginfo, void* pc);

      
      bool attach() override;
      bool detach() override;
      
      virtual void install_sigsegv_handler();
      virtual void install_sigfpe_handler();
      virtual void install_sigpipe_handler();

      
   };


} // namespace acme_posix



