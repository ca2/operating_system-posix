// from interprocess_communication.cpp by Camilo 2021-10-19 18:58 BRT <3ThomasBorregaardSoerensen
#include "framework.h"
#include "interprocess_caller.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/primitive/primitive/memory.h"


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


namespace system_5
{


   interprocess_caller::interprocess_caller()
   {

      //mutex() = memory_new ::pointer < ::mutex >(pparticle);

   }


   interprocess_caller::~interprocess_caller()
   {

   }


   void interprocess_caller::open(const ::string &strChannel, launcher *plauncher)
   {

      if (m_iQueue >= 0)
      {

         close();

      }

      if (!file_exists(strChannel))
      {

         acmefile()->put_contents(strChannel, strChannel);

      }

      m_key = ftok(strChannel, 'c');

      if (m_key == 0)
      {

         throw ::exception(error_failed);

      }

      if ((m_iQueue = msgget(m_key, 0)) == -1)
      {

         throw ::exception(error_failed);

      }

      m_strBaseChannel = strChannel;

      //return true;

   }


   void interprocess_caller::close()
   {

      if (m_iQueue < 0)
      {

         return;

      }

      m_iQueue = -1;

      m_strBaseChannel = "";

      //return true;

   }


   void interprocess_caller::call(const ::string &pszMessage, const class ::time &timeTimeout)
   {

      memory m;

      int iLen = ansi_length(pszMessage);

      m.set_size(sizeof(data_struct) + iLen);

      data_struct *pdata = (data_struct *) m.get_data();

      pdata->mtype = 20170101;

      pdata->request = 1024;

      pdata->size = iLen;

      ::memcpy_dup(pdata->data, pszMessage, iLen);

      int result = 0;

      msqid_ds b;

      zero(b);

      if ((result = msgsnd(m_iQueue, pdata, m.get_size() - sizeof(long), 0)) == -1)
      {

         int iError = errno;

         throw ::exception(error_failed);

      }

      ::output_debug_string("functon: \"interprocess_caller::send\"\n");

      ::output_debug_string("channel: \"" + m_strBaseChannel + "\"\n");

      ::output_debug_string("message: \"" + string(pszMessage) + "\"\n");

      //return true;

   }


//   void interprocess_caller::send(i32 message, void *p, i32 iLen, const time &timeTimeout)
//   {
//
//      if (message == 1024)
//      {
//
//         throw ::exception(error_failed);
//
//      }
//
//      if (!is_tx_ok())
//      {
//
//         throw ::exception(error_failed);
//
//      }
//
//      memory m;
//
//      m.set_size(sizeof(data_struct) + iLen);
//
//      data_struct *pdata = (data_struct *) m.get_data();
//      pdata->mtype = 20170101;
//      pdata->request = 1024;
//      pdata->size = iLen;
//      //if(data.size_i32 > 512)
//      // return false;
//
//      /* The length is essentially the size_i32 of the structure minus sizeof(mtype) */
//      /*         i32 length = sizeof(data_struct) - sizeof(long);
//
//               i32 result;
//
//               ::memcpy_dup(data.data, pszMessage, data.size_i32);
//
//               if((result = msgsnd(m_iQueue,&data,length,0)) == -1)
//               {
//                  return false;
//               }
//               */
//
//      //const ::string & pszMessage = (const ::string &)pdata;
//
//      ::memcpy_dup(pdata->data, p, iLen);
//
//      int result = 0;
//
//      if ((result = msgsnd(m_iQueue, pdata, m.get_size() - sizeof(long), 0)) == -1)
//      {
//
//         throw ::exception(error_failed);
//
//      }
//
//      //return true;
//
//   }


   bool interprocess_caller::is_caller_ok()
   {

      return m_iQueue != -1;

   }


} // namespace system_5



