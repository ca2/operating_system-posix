#include "framework.h"
#include "acme/operating_system.h"
#include "file_lock.h"
#include "acid_posix/file.h"
//#include <fcntl.h>
//#include <sys/file.h>
//#undef USE_MISC
//#include <unistd.h>


//#ifdef MACOS
//#include <sys/fcntl.h>
//#define   LOCK_SH   1    /* shared lock */
//#define   LOCK_EX   2    /* exclusive lock */
//#define   LOCK_NB   4    /* don't block when locking */
//#define   LOCK_UN   8    /* unlock */
//#endif

namespace posix
{


    file_lock::file_lock()
    {

       m_iFileDescriptor = -1;

    }


    file_lock::file_lock(const char * pszName)
    {

       m_iFileDescriptor = -1;

       set_name(scopedstrName);

    }


    file_lock::~file_lock()
    {

       close_file();

    }


    bool file_lock::set_name(const char * pszName)
    {

       close_file();

       m_strName = pszName;

       m_strPath = _get_file_name(scopedstrName);

       return true;

    }


    bool file_lock::is_active()
    {

       if(lock())
       {

          unlock();

          return false;

       }

       return true;

    }


    bool file_lock::lock()
    {

       if(!create_file())
       {

          return false;

       }

       if(posix_file_lock(m_iFileDescriptor) == -1)
       {

          if(errno == EWOULDBLOCK)
          {

             close_file();

             errno = EWOULDBLOCK;

             return 0;

          }
          else
          {

             posi::x_close(m_iFileDescriptor);

             return 0;

          }

       }

       return 1;

    }


    bool file_lock::unlock()
    {

       if(m_iFileDescriptor < 0)
       {

          return false;

       }


       if(posix_file_unlock(m_iFileDescriptor) == -1)
       {

          close_file();

          return false;

       }

       close_file();

       return 1;

    }


    bool file_lock::create_file()
    {

       if(m_iFileDescriptor >= 0)
       {

          return true;

       }

       m_iFileDescriptor = open(m_strPath, O_CREAT | O_RDWR | O_CLOEXEC, 0777);

       if(m_iFileDescriptor < 0)
       {

          return false;

       }

       return true;

    }


    bool file_lock::close_file()
    {

       if(m_iFileDescriptor < 0)
       {

          return true;

       }

       close(m_iFileDescriptor);

       m_iFileDescriptor = -1;

       return true;

    }


   string file_lock::_get_file_name(const char * lpszName)
   {

      string str;

      str.replace("\\", "-");

      str.replace("::", "_");

      str = "/var/lib/ca2/" + str;

      return str;

   }


} // namespace posix



