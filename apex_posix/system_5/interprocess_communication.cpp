#include "framework.h"
#include "interprocess_communication.h"


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


namespace system_5
{


   interprocess_communication_base::interprocess_communication_base()
   {

      m_key = 0;
      m_iQueue = -1;

   }


   interprocess_communication_base::~interprocess_communication_base()
   {

   }


   interprocess_communication_tx::interprocess_communication_tx()
   {

      //mutex() = new ::mutex(pobject);

   }


   interprocess_communication_tx::~interprocess_communication_tx()
   {

   }


   void interprocess_communication_tx::open(const ::string & strChannel,launcher * plauncher)
   {

      if(m_iQueue >= 0)
      {

         close();

      }

      if(!file_exists(strChannel))
      {

         m_psystem->m_pacmefile->put_contents(strChannel, strChannel);

      }

      m_key = ftok(strChannel,'c');

      if(m_key == 0)
      {

         throw ::exception(error_failed);

      }

      if((m_iQueue = msgget(m_key,IPC_CREAT | 0660)) == -1)
      {

         throw ::exception(error_failed);

      }

      m_strBaseChannel = strChannel;

      //return true;

   }


   void interprocess_communication_tx::close()
   {

      if(m_iQueue < 0)
      {

         return;

      }

      m_iQueue = -1;

      m_strBaseChannel = "";

      //return true;

   }


   void interprocess_communication_tx::send(const ::string & pszMessage, const duration &durationTimeout)
   {

      memory m;

      int iLen = ansi_length(pszMessage);

      m.set_size(sizeof(data_struct) + iLen);

      data_struct * pdata  = (data_struct *)m.get_data();

      pdata->mtype         = 20170101;

      pdata->request       = 1024;

      pdata->size          = iLen;

      ::memcpy_dup(pdata->data, pszMessage, iLen);

      int result = 0;

      msqid_ds b;

      __zero(b);

      if((result = msgsnd(m_iQueue, pdata, m.get_size() - sizeof(long), 0)) == -1)
      {

         int iError = errno;

         throw ::exception(error_failed);

      }

      ::output_debug_string("functon: \"interprocess_communication_tx::send\"\n");

      ::output_debug_string("channel: \"" +m_strBaseChannel+ "\"\n");

      ::output_debug_string("message: \"" +string(pszMessage)+ "\"\n");

      //return true;

   }


   void interprocess_communication_tx::send(i32 message,void * p,i32 iLen,const duration & durationTimeout)
   {

      if(message == 1024)
      {

         throw ::exception(error_failed);

      }

      if(!is_tx_ok())
      {

         throw ::exception(error_failed);

      }

      memory m;

      m.set_size(sizeof(data_struct) + iLen);

      data_struct * pdata = (data_struct *)m.get_data();
      pdata->mtype        = 20170101;
      pdata->request      = 1024;
      pdata->size         = iLen;
      //if(data.size_i32 > 512)
      // return false;

      /* The length is essentially the size_i32 of the structure minus sizeof(mtype) */
      /*         i32 length = sizeof(data_struct) - sizeof(long);

               i32 result;

               ::memcpy_dup(data.data, pszMessage, data.size_i32);

               if((result = msgsnd(m_iQueue,&data,length,0)) == -1)
               {
                  return false;
               }
               */

      //const ::string & pszMessage = (const ::string &)pdata;

      ::memcpy_dup(pdata->data,p,iLen);

      int result = 0;

      if((result = msgsnd(m_iQueue,pdata,m.get_size() - sizeof(long),0)) == -1)
      {

         throw ::exception(error_failed);

      }

      //return true;

   }


   bool interprocess_communication_tx::is_tx_ok()
   {

      return m_iQueue != -1;

   }


   interprocess_communication_rx::interprocess_communication_rx()
   {

      m_preceiver    = nullptr;

   }


   interprocess_communication_rx::~interprocess_communication_rx()
   {

   }


   void interprocess_communication_rx::create(const ::string & strChannel)
   {

      if(!file_exists(strChannel))
      {

         m_psystem->m_pacmefile->put_contents(strChannel, strChannel);

      }

      m_key = ftok(strChannel,'c');

      if(m_key == 0)
      {

         throw ::exception(error_failed);

      }

      //if((m_iQueue = msgget(m_key,IPC_CREAT | IPC_EXCL | 0660)) == -1)
      if((m_iQueue = msgget(m_key,IPC_CREAT | 0660)) == -1)
      {

         throw ::exception(error_failed);

      }

      start_receiving();

      //return true;

   }


   void interprocess_communication_rx::destroy()
   {

      i32 iRetry = 23;

      while(m_bRunning && iRetry > 0)
      {

         m_bRun = false;

         sleep(1_ms);

         iRetry--;

      }

      if(m_iQueue < 0)
      {

         //return true;

         return;

      }

      if(msgctl(m_iQueue,IPC_RMID,0) == -1)
      {

         throw ::exception(error_failed);

      }

      m_iQueue = -1;

      //return ::success;

   }


      bool interprocess_communication_rx::start_receiving()
      {

         m_bRunning = true;

         m_bRun = true;

         m_pthread = fork([&]()
         {

            receive();

         });

         return true;

      }


//      void interprocess_communication_rx::receiver::on_ipc_receive(interprocess_communication_rx * prx,const ::string & pszMessage)
//      {
//
//      }
//
//
//      void interprocess_communication_rx::receiver::on_ipc_receive(interprocess_communication_rx * prx,i32 message,void * pdata,memsize len)
//      {
//
//      }
//

//      void interprocess_communication_rx::receiver::on_ipc_post(interprocess_communication_rx * prx, i64 a, i64 b)
//      {
//
//      }


      void interprocess_communication_rx::on_interprocess_receive(::string && strMessage)
      {

         if(m_preceiver != nullptr)
         {

            m_preceiver->on_interprocess_receive(this, ::move(strMessage));

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         //return nullptr;

      }


      void interprocess_communication_rx::on_interprocess_receive(i32 message, ::memory && memory)
      {

         if(m_preceiver != nullptr)
         {

            m_preceiver->on_interprocess_receive(this, message, ::move(memory));

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         //return nullptr;

      }


      void interprocess_communication_rx::on_interprocess_post(i64 a, i64 b)
      {

         if(m_preceiver != nullptr)
         {

            m_preceiver->on_interprocess_post(this,a,b);

         }

         // ODOW - on date of writing : return ignored by this windows implementation

         //return nullptr;

      }


      bool interprocess_communication_rx::on_idle()
      {

         return false;

      }


      bool interprocess_communication_rx::is_rx_ok()
      {

         return m_iQueue != -1;

      }


      void * interprocess_communication_rx::receive()
      {

         memory mem;

         memory m;

         m.set_size(10000000);

         while(task_get_run())
         {

            m_bRunning = true;

            ssize_t  result;

            i32 length;

            data_struct * pdata = (data_struct *) m.get_data();

            length = m.get_size() - sizeof(long);

            if((result = msgrcv(m_iQueue, pdata, length, 20170101, IPC_NOWAIT)) == -1)
            {

               if(errno == ENOMSG)
               {

                  sleep(100_ms);

                  continue;

               }
               else
               {

                  return (void *)-1;

               }

            }

            mem.assign(pdata->data,pdata->size);

            long lRequest = pdata->request;

            //fork([this, mem, lRequest]()
            {

               //

               if(lRequest == 1024)
               {

                  dispatch_message(::move(__string(mem)));

               }
               else
               {

                  ::memory memoryCopy(mem);
                  //on_interprocess_receive(lRequest, ::move(m2));
                  dispatch_message(lRequest, ::move(memoryCopy));

               }

               //});
            }

         }

         m_bRunning = false;

         return nullptr;

      }


//      interprocess_communication::interprocess_communication()
//      {
//
//         m_millisTimeout = (5000) * 11;
//
//      }
//
//
//      interprocess_communication::~interprocess_communication()
//      {
//
//
//      }
//
//      bool interprocess_communication::open_ab(const ::string & pszChannel,launcher * plauncher)
//      {
//
//         m_strChannel = pszChannel;
//
//         m_rx.m_preceiver = this;
//
//         string strChannelRx = m_strChannel + "-a";
//         string strChannelTx = m_strChannel + "-b";
//
//
//         if(!m_rx.create(strChannelRx))
//         {
//            return false;
//         }
//
//         if(!interprocess_communication_tx::open(strChannelTx,plauncher))
//         {
//            return false;
//         }
//
//         return true;
//
//      }


//      bool interprocess_communication::open_ba(const ::string & pszChannel,launcher * plauncher)
//      {
//
//         m_strChannel = pszChannel;
//
//         m_rx.m_preceiver = this;
//
//         string strChannelRx = m_strChannel + "-b";
//         string strChannelTx = m_strChannel + "-a";
//
//
//         if(!m_rx.create(strChannelRx))
//         {
//            return false;
//         }
//
//         if(!interprocess_communication_tx::open(strChannelTx,plauncher))
//         {
//            return false;
//         }
//
//         return true;
//
//      }



//      bool interprocess_communication::is_rx_tx_ok()
//      {
//
//         return m_prx->is_rx_ok() && m_ptx->is_tx_ok();
//
//      }


} // namespace interprocess_intercommunication





