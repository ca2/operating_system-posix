// created by Camilo 2021-02-14 16:56 BRT <3CamiloSasukeThomasBorregaardSoerensen
// from interprocess_communication by Camilo 2021-10-19 18:57 BRT <3ThomasBorregaardSoerensen
#pragma once


#include "interprocess_base.h"
#include "apex/interprocess/caller.h"


namespace system_5
{


   class CLASS_DECL_APEX interprocess_caller :
      virtual public interprocess_base,
      virtual public interprocess::caller
   {
   public:


      interprocess_caller();
      ~interprocess_caller() override;


      void open(const ::scoped_string & scopedstrChannel, launcher * plauncher = nullptr) override;
      void close() override;


      void call(const ::scoped_string & scopedstrMessage, const class time & timeTimeout) override;
      //void send(int message, void * pdata, int len, const class time & timeTimeout) override;


      bool is_caller_ok() override;


   };



} // namespace system_5



