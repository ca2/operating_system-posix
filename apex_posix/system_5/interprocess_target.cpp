// from interprocess_communication.cpp by Camilo 2021-10-19 18:58 BRT <3ThomasBorregaardSoerensen
#include "framework.h"
#include "interprocess_target.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/primitive/primitive/memory.h"


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


namespace system_5
{


   interprocess_target::interprocess_target()
   {

      //m_preceiver = nullptr;

   }


   interprocess_target::~interprocess_target()
   {

   }


   void interprocess_target::create(const ::string &strChannel)
   {

      if (!file_exists(strChannel))
      {

         acmefile()->put_contents(strChannel, strChannel);

      }

      m_key = ftok(strChannel, 'c');

      if (m_key == 0)
      {

         int iErrorNumber = errno;

         auto estatus = errno_status(iErrorNumber);

         throw ::exception(estatus, "ftok(\"" + strChannel + "\", 'c') has failed");

      }

      //if((m_iQueue = msgget(m_key,IPC_CREAT | IPC_EXCL | 0660)) == -1)
      if ((m_iQueue = msgget(m_key, IPC_CREAT | IPC_EXCL | 0660)) == -1)
      {

         int iErrorNumber = errno;

         if(iErrorNumber == EEXIST)
         {

            if ((m_iQueue = msgget(m_key,  0660)) == -1)
            {

               int iErrorNumber = errno;

               auto estatus = errno_status(iErrorNumber);

               throw ::exception(estatus, "msgget has failed");

            }

         }
         else
         {

            auto estatus = errno_status(iErrorNumber);

            throw ::exception(estatus, "msgget has failed");

         }

      }

      start_receiving();

      //return true;

   }


   void interprocess_target::destroy()
   {

      i32 iRetry = 23;

      while (m_bRunning && iRetry > 0)
      {

         m_bRun = false;

         sleep(1_ms);

         iRetry--;

      }

      if (m_iQueue < 0)
      {

         //return true;

         return;

      }

      if (msgctl(m_iQueue, IPC_RMID, 0) == -1)
      {

         throw ::exception(error_failed);

      }

      m_iQueue = -1;

      //return ::success;

   }


   bool interprocess_target::start_receiving()
   {

      m_bRunning = true;

      m_bRun = true;

      m_pthread = fork([&]()
                       {

                          receive();

                       });

      return true;

   }


//      void interprocess_handler::receiver::on_ipc_receive(interprocess_handler * prx,const ::string & pszMessage)
//      {
//
//      }
//
//
//      void interprocess_handler::receiver::on_ipc_receive(interprocess_handler * prx,i32 message,void * pdata,memsize len)
//      {
//
//      }
//

//      void interprocess_handler::receiver::on_ipc_post(interprocess_handler * prx, i64 a, i64 b)
//      {
//
//      }


//   void interprocess_target::on_interprocess_receive(::string &&strMessage)
//   {
//
//      if (m_preceiver != nullptr)
//      {
//
//         m_preceiver->on_interprocess_receive(this, ::move(strMessage));
//
//      }
//
//      // ODOW - on date of writing : return ignored by this windows implementation
//
//      //return nullptr;
//
//   }


//   void interprocess_target::on_interprocess_receive(i32 message, ::memory &&memory)
//   {
//
//      if (m_preceiver != nullptr)
//      {
//
//         m_preceiver->on_interprocess_receive(this, message, ::move(memory));
//
//      }
//
//      // ODOW - on date of writing : return ignored by this windows implementation
//
//      //return nullptr;
//
//   }
//
//
//   void interprocess_target::on_interprocess_post(i64 a, i64 b)
//   {
//
//      if (m_preceiver != nullptr)
//      {
//
//         m_preceiver->on_interprocess_post(this, a, b);
//
//      }
//
//      // ODOW - on date of writing : return ignored by this windows implementation
//
//      //return nullptr;
//
//   }


   bool interprocess_target::on_idle()
   {

      return false;

   }


   bool interprocess_target::is_target_ok()
   {

      return m_iQueue != -1;

   }


   void *interprocess_target::receive()
   {

      memory mem;

      memory m;

      m.set_size(10000000);

      while (task_get_run())
      {

         m_bRunning = true;

         ssize_t result;

         i32 length;

         data_struct *pdata = (data_struct *) m.get_data();

         length = m.get_size() - sizeof(long);

         if ((result = msgrcv(m_iQueue, pdata, length, 20170101, IPC_NOWAIT)) == -1)
         {

            if (errno == ENOMSG)
            {

               preempt(100_ms);

               continue;

            } else
            {

               return (void *) -1;

            }

         }

         mem.assign(pdata->data, pdata->size);

         long lRequest = pdata->request;

         //fork([this, mem, lRequest]()
         {

            //

            _handle_uri(mem);

//            if (lRequest == 1024)
//            {
//
//               dispatch_message(::move(as_string(mem)));
//
//            } else
//            {
//
//               ::memory memoryCopy(mem);
//               //on_interprocess_receive(lRequest, ::move(m2));
//               dispatch_message(lRequest, ::move(memoryCopy));
//
//            }

            //});
         }

      }

      m_bRunning = false;

      return nullptr;

   }


} // namespace system_5



