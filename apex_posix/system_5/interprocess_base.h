// created by Camilo 2021-02-14 16:56 BRT <3CamiloSasukeThomasBorregaardSoerensen
// from interprocess_communication by Camilo 2021-10-19 18:57 BRT <3ThomasBorregaardSoerensen
#pragma once


#include "apex/interprocess/base.h"


namespace system_5
{


   class CLASS_DECL_APEX interprocess_base  :
      virtual public interprocess::base
   {
      public:

   #if defined(APPLEOS)


      CFMessagePortRef     m_port;


   #else

      key_t m_key;
      int m_iQueue;

      struct data_struct
      {


         long mtype;
         long request;
         int size;
         char data[0];


      };


   #endif


      string m_strBaseChannel;


      interprocess_base();

      ~interprocess_base() override;


   };


} // namespace system_5



