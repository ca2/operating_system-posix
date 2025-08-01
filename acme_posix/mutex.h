//
// Created by camilo on 2022-10-25 13:35 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/parallelization/mutex.h"


#ifdef PARALLELIZATION_PTHREAD
#include <pthread.h>
#endif

//   #ifdef MUTEX_COND_TIMED
//
//#pragma message("MUTEX_COND_TIMED defined")
//
//#else
//
//#pragma message("MUTEX_COND_TIMED not defined")
//
//
//   #endif
//
//   #if defined(MUTEX_NAMED_FD)
//
//#pragma message("MUTEX_NAMED_FD defined")
//
//#else
//
//#pragma message("MUTEX_NAMED_FD not defined")
//
//   #endif
//
//   #if defined(MUTEX_NAMED_POSIX)
//
//      #pragma message("MUTEX_NAMED_POSIX defined")
//
//   #elif defined(MUTEX_NAMED_FD)
//
//      #pragma message("MUTEX_NAMED_FD defined")
//
//   #elif defined(MUTEX_NAMED_VSEM)
//
//      #pragma message("MUTEX_NAMED_VSEM defined")
//
//#else
//
//       #pragma message("NO MUTEX_NAMED_* defined")
//
//   #endif

namespace acme_posix
{


   class CLASS_DECL_ACME mutex :
      virtual public ::mutex
   {
   public:


      pthread_mutex_t   m_mutex;
      string            m_strName;

   #ifdef MUTEX_COND_TIMED

      pthread_cond_t          m_cond;

   #endif

   #if defined(MUTEX_COND_TIMED) || defined(MUTEX_NAMED_FD)

      pthread_t               m_thread;
      int                     m_count;

   #endif

   #if defined(MUTEX_NAMED_POSIX)

      sem_t *                 m_psem; // as of 2016-11-26
         // not implemented (err=38) on android-19
   #elif defined(MUTEX_NAMED_FD)

      int                     m_iFd;

   #elif defined(MUTEX_NAMED_VSEM)

      key_t                   m_key;
         int                     m_semid;

   #endif


   #if defined(MUTEX_NAMED_POSIX)
      mutex(enum_create_new ecreatenew = create_new, const_char_pointer psz = nullptr, const_char_pointer pstrName,sem_t * psem,bool bOwner = true);
   #elif defined(MUTEX_NAMED_FD)
      mutex(enum_create_new ecreatenew, const_char_pointer pstrName, int iFd, bool bOwner = true);
   #elif defined(MUTEX_NAMED_VSEM)
      mutex(enum_create_new ecreatenew, const_char_pointer pstrName,key_t key, int semid, bool bOwner = true);
   #endif
      mutex(::particle
      * pparticle,
      bool bInitiallyOwn,
      const_char_pointer lpszName);

      mutex(enum_create_new
      ecreatenew = e_create_new,
      bool bInitiallyOwn = false
      );
      ~

      mutex()

      override;


   //virtual ::e_status lock() override;

   //virtual ::e_status lock(const class time & timeWait) override;

      virtual void _wait()

      override;

      virtual bool _wait(const class ::time &wait)

      override;

      using ::mutex::unlock;

      virtual void unlock()

      override;


      //bool already_exists();


   ///static ::pointer < ::mutex >open_mutex(::matter * pmatter, const_char_pointer lpszName) {return ::open_mutex(pmatter, lpszName);}


   };


} // namespace acme_posix


//CLASS_DECL_ACME void wait_until_mutex_does_not_exist(const_char_pointer lpszName);
//
//
//
//CLASS_DECL_ACME ::pointer< ::mutex > get_ui_destroyed_mutex();
//



