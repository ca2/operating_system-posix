// created by Camilo 2021-02-14 16:56 BRT <3CamiloSasukeThomasBorregaardSoerensen
// from interprocess_communication by Camilo 2021-10-19 18:57 BRT <3ThomasBorregaardSoerensen
#pragma once


#include "interprocess_base.h"
#include "apex/interprocess/caller.h"


namespace system_5
{


   class CLASS_DECL_APEX interprocess_caller :
      virtual public interprocess_communication_base,
      virtual public interprocess_handler::caller
   {
   public:


      interprocess_caller();
      ~interprocess_caller() override;


      void open(const ::string & strChannel, launcher * plauncher = nullptr) override;
      void close() override;


      void send(const ::string & pszMessage, const ::duration & durationTimeout) override;
      void send(int message, void * pdata, int len, const ::duration & durationTimeout) override;


      bool is_caller_ok() override;


   };



} // namespace system_5



