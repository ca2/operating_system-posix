// created by Camilo 2021-02-14 16:56 BRT <3CamiloSasukeThomasBorregaardSoerensen
// from interprocess_communication by Camilo 2021-10-19 18:57 BRT <3ThomasBorregaardSoerensen
#pragma once


#include "interprocess_base.h"
#include "apex/interprocess/target.h"


namespace system_5
{


   class CLASS_DECL_APEX interprocess_target :
      virtual public interprocess_base,
      virtual public interprocess::target
   {
   public:


   interprocess_target();
      ~interprocess_target() override;


      void create(const ::string & strChannel) override;
      void destroy() override;



      //bool _handle_uri(const block & blockUri) override;
      //void on_interprocess_receive(::string && strMessage) override;
      //void on_interprocess_receive(int message, ::memory && memory) override;
      //void on_interprocess_post(i64 a, i64 b) override;


      bool on_idle() override;


      virtual bool start_receiving();

      virtual void * receive();


      bool is_target_ok() override;


   };


} // namespace system_5



