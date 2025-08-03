// from interprocess_communication.cpp by Camilo 2021-10-19 18:58 BRT <3ThomasBorregaardSoerensen
#include "framework.h"
#include "interprocess_target.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/operating_system/shared_posix/c_error_number.h"
#include "acme/platform/application.h"
#include "acme/prototype/prototype/memory.h"


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>


namespace system_5
{


   interprocess_target::interprocess_target()
   {

      m_key = -1;

      m_iQueue = -1;

   }


   interprocess_target::~interprocess_target()
   {

      destroy();

   }


   void interprocess_target::create(const ::scoped_string & scopedstrChannel)
   {

      information() << "interprocess_target::create";

      if (!file_exists(scopedstrChannel))
      {

         information() << "interprocess_target::create file doesnt exist, going to create : " << scopedstrChannel;

         file_system()->put_contents(scopedstrChannel, scopedstrChannel);

         m_strCreatedFile = scopedstrChannel;

      }

      m_key = ftok(scopedstrChannel, 'c');

      if (m_key == -1)
      {

         information() << "interprocess_target::create ftok failed";

         auto cerrornumber = c_error_number();

         auto estatus = cerrornumber.estatus();

         throw ::exception(estatus, "ftok(\"" + scopedstrChannel + "\", 'c') has failed");

      }

      information() << "interprocess_target::create ftok succeeded";

      //if((m_iQueue = msgget(m_key,IPC_CREAT | IPC_EXCL | 0660)) == -1)
      if ((m_iQueue = msgget(m_key, IPC_CREAT | IPC_EXCL | 0660)) == -1)
      {

         information() << "interprocess_target::create msgget failed (1)";

         auto cerrornumber = c_error_number();

         if(cerrornumber.m_iErrorNumber == EEXIST)
         {

            if ((m_iQueue = msgget(m_key,  0660)) == -1)
            {

               information() << "interprocess_target::create msgget failed(2)";

               auto cerrornumber = c_error_number();

               auto estatus = cerrornumber.estatus();

               throw ::exception(estatus, "msgget has failed (2) channel : " + scopedstrChannel);

            }

         }
         else
         {

            if(cerrornumber.m_iErrorNumber == ENOSPC)
            {

               information() << "interprocess_target::create msgget failed (3) : ENOSPC - A message queue has to be created but the system limit for the maximum number of message queues (MSGMNI) would be exceeded.";

            }
            else
            {

               information() << "interprocess_target::create msgget failed (3) : " << cerrornumber.m_iErrorNumber << " (" << cerrornumber.name() << ", " << cerrornumber.get_error_description() << ")";

            }

            auto estatus = cerrornumber.estatus();

            throw ::exception(estatus, {cerrornumber},  "msgget has failed (3) channel : " + scopedstrChannel);

         }

      }

      start_receiving();

      //return true;

   }


   void interprocess_target::destroy()
   {

      int iRetry = 23;

      while (m_bRunning && iRetry > 0)
      {

         m_bRun = false;

         preempt(100_ms);

         iRetry--;

      }

      if(m_iQueue > 0)
      {

         auto rc = msgctl(m_iQueue, IPC_RMID, nullptr);

         if(rc < 0)
         {

            warning("interprocess_target::~interprocess_target failed to remove message queue");

         }

         m_iQueue = -1;

      }

      if (file_exists(m_strCreatedFile))
      {

         information() << "interprocess_target::~interprocess_target file exist, going to delete it : " << m_strCreatedFile;

         bool bOk = false;

         try
         {

            file_system()->erase(m_strCreatedFile);

            bOk = true;

         }
         catch(...)
         {

            bOk = true;

         }

         if(bOk)
         {

            information() << "interprocess_target::~interprocess_target deleted file : " << m_strCreatedFile;

            m_strCreatedFile.empty();

         }
         else
         {

            information() << "interprocess_target::~interprocess_target failed to delete file : " << m_strCreatedFile;

         }

      }

   }


   bool interprocess_target::start_receiving()
   {

      m_bRunning = true;

      m_bRun = true;

      get_app()->_post([this]()
      {

         m_pthread = get_app()->fork([this]()
                          {

                             information() << "interprocess_target receiving";

                             receive();

                          });

      });

      return true;

   }


//      void interprocess_handler::receiver::on_ipc_receive(interprocess_handler * prx,const ::scoped_string & scopedstrMessage)
//      {
//
//      }
//
//
//      void interprocess_handler::receiver::on_ipc_receive(interprocess_handler * prx,int message,void * pdata,memsize len)
//      {
//
//      }
//

//      void interprocess_handler::receiver::on_ipc_post(interprocess_handler * prx, long long a, long long b)
//      {
//
//      }


//   void interprocess_target::on_interprocess_receive(::string &&strMessage)
//   {
//
//      if (m_preceiver != nullptr)
//      {
//
//         m_preceiver->on_interprocess_receive(this, ::transfer(strMessage));
//
//      }
//
//      // ODOW - on date of writing : return ignored by this windows implementation
//
//      //return nullptr;
//
//   }


//   void interprocess_target::on_interprocess_receive(int message, ::memory &&memory)
//   {
//
//      if (m_preceiver != nullptr)
//      {
//
//         m_preceiver->on_interprocess_receive(this, message, ::transfer(memory));
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
//   void interprocess_target::on_interprocess_post(long long a, long long b)
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

         task_iteration();

         ssize_t result;

         int length;

         data_struct *pdata = (data_struct *) m.data();

         length = m.size() - sizeof(long);

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

            _handle_uri(mem.get_string());

//            if (lRequest == 1024)
//            {
//
//               dispatch_message(::transfer(as_string(mem)));
//
//            } else
//            {
//
//               ::memory memoryCopy(mem);
//               //on_interprocess_receive(lRequest, ::transfer(m2));
//               dispatch_message(lRequest, ::transfer(memoryCopy));
//
//            }

            //});
         }

      }

      m_bRunning = false;

      return nullptr;

   }


} // namespace system_5



