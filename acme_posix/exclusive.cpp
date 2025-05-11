//
// Created by camilo on 2022-10-28 23:54 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "exclusive.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
////#include "acme/prototype/prototype/object.h"
//#include "exclusive.h"


#include "acme/_operating_system.h"
//#ifdef FREEBSD
//#define __XSI_VISIBLE 1
//#endif
#if defined(LINUX) || defined(__ANDROID__) || defined(__APPLE__) || defined(__BSD__)
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif


#include <stdio.h>


namespace acme_posix
{


//#ifdef WINDOWS
//

//   exclusive::exclusive(::particle * pparticle, string strId ARG_SEC_ATTRS)
//   //exclusive::exclusive()
//   {
//
//      //m_strId = strId;
//
//      //m_bResourceException = false;
//
//      //try
//      //{
//
//      //   m_pmutex = pparticle->node()->create_global_named_mutex(pparticle, false, strId);
//
//      //   //m_pmutex = //__allocate ::pointer < ::mutex >(pparticle, false, strId ADD_PARAM_SEC_ATTRS);
//
//      //   //m_dwLastError = ::GetLastError();
//
//      //}
//      //catch (const ::exception &)
//      //{
//
//      //   m_bResourceException = true;
//
//      //   //try
//      //   //{
//
//      //   //   m_pmutex = __allocate ::pointer < ::mutex >(pparticle, false, strId);
//
//      //   //   m_dwLastError = ::GetLastError();
//
//      //   //}
//      //   //catch (const ::exception &)
//      //   //{
//
//      //   //   m_bResourceException = true;
//
//      //   //}
//
//      //}
//
//   }


//#else
//
//
   exclusive::exclusive(::particle * pparticle, const string & strId)
   {

      initialize(pparticle);

      m_strId = strId;

      ::file::path path;

      ::string str = strId;

      if(str.case_insensitive_begins_eat("Local\\"))
      {

         path = pparticle->directory_system()->home() / ".config/acme";

      }
      else if(str.case_insensitive_begins_eat("Global\\"))
      {

         path = "/var/tmp/acme";

      }
      else
      {

         path = "/var/tmp/acme";

      }

      path /= str;

      m_path = path;

      directory_system()->create(path.folder());

      const char * pszPath = path.c_str();

      pparticle->informationf("exclusive::exlusive Going to create exclusive at path : %s", pszPath);

      m_iFile = open(pszPath, O_WRONLY | O_CREAT | O_CLOEXEC, 0777);

      if(m_iFile >= 0)
      {

         m_iLock = lockf(m_iFile, F_TLOCK, 0);

         pparticle->informationf("exclusive::exlusive file %d lock %d", m_iFile, m_iLock);

      }
      else
      {

         pparticle->informationf("exclusive::exlusive Failed to create lock file");

         m_iLock = -1;

      }

      pparticle->informationf("exclusive::exlusive end");

   }
//
//
//#endif
//

   exclusive::~exclusive()
   {

      if(m_iFile >= 0)
      {

         if(m_iLock >= 0)
         {

            int iUnlockError = lockf(m_iFile, F_ULOCK, 0);
            
            if(iUnlockError)
            {
             
               warningf("exclusive::~exclusive Unlocking the file lock(F_ULOCK) Failed...");
               
            }

            print_line("exclusive::~exclusive Unlock m_iLock");

         }

         ::close(m_iFile);

         if(m_iLock >= 0)
         {

            if(m_path.has_character() && file_exists(m_path))
            {

               ::remove(m_path);

            }

         }

      }

   }


   bool exclusive::exclusive_fails() const
   {

      //return m_pmutex->already_exists();

      //return false;

//#ifdef WINDOWS
//
//      return m_dwLastError == ERROR_ALREADY_EXISTS || m_bResourceException;
//
//#else
//
      return m_iLock < 0;
//
//#endif

   }


} // namespace acme_posix



