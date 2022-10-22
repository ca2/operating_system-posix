// from interprocess_communication.cpp by Camilo 2021-10-19 18:57 BRT <3ThomasBorregaardSoerensen
#include "framework.h"
#include "interprocess_base.h"
//#include "acme/filesystem/filesystem/acme_file.h"


//#include <sys/types.h>
//#include <sys/ipc.h>
//#include <sys/msg.h>


namespace system_5
{


   interprocess_base::interprocess_base()
   {

      m_key = 0;
      m_iQueue = -1;

   }


   interprocess_base::~interprocess_base()
   {

   }


} // namespace system_5



