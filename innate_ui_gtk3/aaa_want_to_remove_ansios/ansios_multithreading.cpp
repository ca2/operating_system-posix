#include "framework.h"


CLASS_DECL_ACME void thread_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);

CLASS_DECL_ACME void process_get_os_priority(int32_t * piOsPolicy, sched_param * pparam, int32_t iCa2Priority);

CLASS_DECL_ACME int32_t thread_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);

CLASS_DECL_ACME int32_t process_get_scheduling_priority(int iOsPolicy, const sched_param * pparam);


unsigned int MsgWaitForMultipleObjectsEx(unsigned int dwSize, sync_object * * pobjectptra, unsigned int tickTimeout, unsigned int dwWakeMask, unsigned int dwFlags)
{

   unsigned int start = 0;

   if(tickTimeout != (unsigned int) U32_INFINITE_TIMEOUT)
   {

      start= ::duration::now();

   }

   ::pointer<message_queue>pmq;

   if(dwWakeMask > 0)
   {

      pmq = __get_mq(GetCurrentThreadId(), false);

   }

   int_bool bWaitForAll        = dwFlags & MWMO_WAITALL;

   timespec delay;

   delay.tv_sec = 0;

   delay.tv_nsec = 1000000;

   if(bWaitForAll)
   {

      while(true)
      {

         int32_t i;

         int32_t j;

         i = 0;

         for(; comparison::lt(i, dwSize);)
         {

            if(pmq != nullptr)
            {

               synchronous_lock synchronouslock(&pmq->m_mutex);

               if(pmq->ma.get_count() > 0)
               {

                  return WAIT_OBJECT_0 + dwSize;

               }

            }

            if(tickTimeout != (unsigned int) U32_INFINITE_TIMEOUT && start.elapsed() >= tickTimeout)
            {

               for(j = 0; j < i; j++)
               {

                  pobjectptra[j]->unlock();

               }

               return WAIT_TIMEOUT;

            }

            if(pobjectptra[i]->lock(::duration(1)))
            {

               i++;

            }
            else
            {

               nanosleep(&delay, nullptr);

            }

         }

         return WAIT_OBJECT_0;

      }

   }
   else
   {

      int32_t i;

      while(true)
      {

         for(i = 0; comparison::lt(i, dwSize); i++)
         {

            if(pmq != nullptr)
            {

               synchronous_lock synchronouslock(&pmq->m_mutex);

               if(pmq->ma.get_count() > 0)
               {

                  return WAIT_OBJECT_0 + dwSize;

               }

            }

            if(tickTimeout != (unsigned int) U32_INFINITE_TIMEOUT && start.elapsed() >= tickTimeout)
            {

               return WAIT_TIMEOUT;

            }

            if(pobjectptra[i]->lock(::duration(0)))
            {

               return WAIT_OBJECT_0 + i;

            }

         }

         nanosleep(&delay, nullptr);

      }

   }

}


unsigned int MsgWaitForMultipleObjects(unsigned int dwSize, sync_object ** pobjectptra, int_bool bWaitForAll, unsigned int tickTimeout, unsigned int dwWakeMask)
{

   return MsgWaitForMultipleObjectsEx(dwSize, pobjectptra, tickTimeout, dwWakeMask, (bWaitForAll ?  MWMO_WAITALL : 0));

}


unsigned int WaitForMultipleObjectsEx(unsigned int dwSize, sync_object ** pobjectptra, int_bool bWaitForAll, unsigned int tickTimeout, int_bool bAlertable)
{

   return MsgWaitForMultipleObjectsEx(dwSize, pobjectptra, tickTimeout, 0, (bWaitForAll ?  MWMO_WAITALL : 0) | (bAlertable ?  MWMO_ALERTABLE : 0));

}


unsigned int WaitForMultipleObjects(unsigned int dwSize, sync_object ** pobjectptra, int_bool bWaitForAll, unsigned int tickTimeout)
{

   return WaitForMultipleObjectsEx(dwSize, pobjectptra, bWaitForAll, tickTimeout, false);

}


unsigned int WaitForSingleObjectEx(sync_object * pobject, unsigned int tickTimeout, int_bool bAlertable)
{

   return WaitForMultipleObjectsEx(1, &pobject, true, tickTimeout, bAlertable);

}


unsigned int WaitForSingleObject(sync_object * pobject, unsigned int tickTimeout)
{

   return WaitForSingleObjectEx(pobject, tickTimeout, false);

}


thread_data::thread_data()
{

   pthread_key_create(&m_key, nullptr);

}


thread_data::~thread_data()
{

}

void * thread_data::get()
{

   return pthread_getspecific(m_key);

}


void thread_data::set(void * p)
{

   pthread_setspecific(m_key,p);

}


CLASS_DECL_ACME htask_t current_htask()
{

   return ::GetCurrentThread();

}


CLASS_DECL_ACME itask_t current_itask()
{

   return ::GetCurrentThreadId();

}


// void __node_init_multithreading()
// {

//    __node_init_cross_windows_threading();

// }


// void __node_term_multithreading()
// {

//    __node_term_cross_windows_threading();

// }


#if defined(LINUX) // || defined(ANDROID)

bool (* g_pfn_defer_process_x_message)(htask_t htask,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek) = nullptr;

bool aura_defer_process_x_message(htask_t htask,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek)
{

   if(g_pfn_defer_process_x_message == nullptr)
      return false;

   return (*g_pfn_defer_process_x_message)(htask, lpMsg, oswindow, bPeek);

}

void set_defer_process_x_message(bool (* pfn)(htask_t htask,LPMESSAGE lpMsg,oswindow oswindow,bool bPeek))
{

   g_pfn_defer_process_x_message = pfn;

}

#endif


extern "C"
void * os_thread_thread_proc(LPVOID lpparameter);


int_bool WINAPI SetThreadPriority(htask_t htask,int32_t nCa2Priority)
{

   int32_t iPolicy;

   sched_param schedparam;

   thread_get_os_priority(&iPolicy,&schedparam,nCa2Priority);

   pthread_setschedparam((pthread_t) htask,iPolicy,&schedparam);

   return true;

}


int32_t WINAPI GetThreadPriority(htask_t  htask)
{

   int iOsPolicy = SCHED_OTHER;

   sched_param schedparam;

   schedparam.sched_priority = 0;

   pthread_getschedparam((itask_t) htask,&iOsPolicy,&schedparam);

   return thread_get_scheduling_priority(iOsPolicy,&schedparam);

}


static htask_t g_hMainThread = nullptr;

static itask_t g_iMainThread = (itask_t) -1;


CLASS_DECL_ACME void set_main_hthread(htask_t htask)
{

   g_hMainThread = htask;

}


CLASS_DECL_ACME void set_main_ithread(itask_t itask)
{

   g_iMainThread = itask;

}


CLASS_DECL_ACME htask_t get_main_hthread()
{

   return g_hMainThread;

}


CLASS_DECL_ACME itask_t get_main_ithread()
{

   return g_iMainThread;

}



// LPVOID WINAPI thread_get_data(htask_t htask,unsigned int dwIndex);

// int_bool WINAPI thread_set_data(htask_t htask,unsigned int dwIndex,LPVOID lpTlsValue);

unsigned int g_dwDebug_post_thread_msg_time;

int g_iDebug_post_thread_msg_time;

CLASS_DECL_ACME int_bool WINAPI PostThreadMessage(itask_t iThreadId,unsigned int Msg,WPARAM wParam,LPARAM lParam)
{

   ::pointer<message_queue>pmq = __get_mq(iThreadId);

   if(pmq == nullptr)
   {

      return false;

   }

   synchronous_lock ml(&pmq->m_mutex);

   MESSAGE msg;

   if(Msg == e_message_quit)
   {

      ::output_debug_string("\n\n\nWM_QUIT posted to thread " + ::as_string((uint64_t)iThreadId) + "\n\n\n");

   }

   msg.message = Msg;
   msg.wParam  = wParam;
   msg.lParam  = lParam;
   msg.pt.x()    = I32_MINIMUM;
   msg.pt.y()    = I32_MINIMUM;
   msg.hwnd    = nullptr;

   pmq->ma.add(msg);

   pmq->m_happeningNewMessage.set_event();

   return true;

}


CLASS_DECL_ACME htask_t GetCurrentThread()
{

   return pthread_self();

}


CLASS_DECL_ACME itask_t GetCurrentThreadId()
{

   return pthread_self();

}


namespace parallelization
{


   CLASS_DECL_ACME bool set_priority(::enum_priority epriority)
   {

      return (::SetThreadPriority(::GetCurrentThread(),priority) != 0);

   }


   CLASS_DECL_ACME int32_t priority()
   {

      return ::GetThreadPriority(::GetCurrentThread());

   }


} // namespace acme


bool on_init_thread()
{

   if(!__os_init_thread())
   {

      return false;

   }

   return true;

}


bool on_term_thread()
{

   bool bOk1 = __os_term_thread();

   return bOk1;

}


CLASS_DECL_ACME huge_natural translate_processor_affinity(int iOrder)
{

   return 1 << iOrder;

}



