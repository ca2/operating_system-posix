#include "framework.h"

#include "pipe.h"
#include <stdlib.h>


#if defined(LINUX) || defined(__ANDROID__) || defined(__APPLE__) || defined(__BSD__)
#include <fcntl.h>
#undef USE_MISC

#endif

#if defined(RASPBERRYPIOS)
#include <sys/types.h>
#include <unistd.h>
#endif

#if defined(__APPLE__) || defined(LINUX) || defined(__BSD__)
#include <unistd.h>
#endif


namespace acme_posix
{


   pipe::pipe()
   {

      m_pchBuf = nullptr;

      m_fd[0] = -1;

      m_fd[1] = -1;

   }


   pipe::~pipe()
   {

      if (m_pchBuf != nullptr)
      {
         free(m_pchBuf);
      }

      if (m_fd[0] != -1)
      {
          
         ::close(m_fd[0]);
          
      }

      if (m_fd[1] != -1)
      {
          
         ::close(m_fd[1]);
          
      }

   }


   bool pipe::create(bool bBlock, bool bInherit)
   {

      if (!::operating_system::pipe::create(bBlock, bInherit))
      {

         return false;

      }

      int iFlags = bBlock ? 0 : O_NONBLOCK;

      if (::pipe(m_fd))
      {

         // errno
         return false;

      }

      if (fcntl(m_fd[0], F_SETFL, iFlags))
      {
         close(m_fd[0]);
         close(m_fd[1]);
         return false;
      }

      if (fcntl(m_fd[1], F_SETFL, iFlags))
      {
         close(m_fd[0]);
         close(m_fd[1]);
         return false;
      }

      return true;

   }


   bool pipe::not_inherit_read()
   {

      return true;

   }

   bool pipe::not_inherit_write()
   {


      return true;

   }


   bool pipe::write(const ::scoped_string & scopedstr)
   {

      auto dwLen = scopedstr.size();

      bool bSuccess = false;

      size_t dwWritten;

      dwWritten = ::write(m_fd[1], (const_char_pointer )scopedstr.begin(), dwLen);

      return bSuccess != false && dwWritten == dwLen;

   }


   string pipe::read()
   {
      string str;
      const int BUFSIZE = 1024 * 8;

      size_t dwRead;

      bool bSuccess = false;

      char chBuf[BUFSIZE];

      for (;;)
      {
         memory_set(chBuf, 0, BUFSIZE);

         try
         {

            dwRead = ::read(m_fd[0], chBuf, BUFSIZE);

            if (!m_bBlock && dwRead == (size_t)-1)
               return "";

            bSuccess = true;

         }
         catch (...)
         {

            bSuccess = false;

         }

         if (!bSuccess || dwRead == 0)
            break;

         str += chBuf;

         if (dwRead < BUFSIZE)
            break;

      }

      return str;

   }


   string pipe::one_pass_read()
   {

      string str;

      const int BUFSIZE = 1024 * 8;

      size_t dwRead;

      bool bSuccess = false;

      char chBuf[BUFSIZE];

      memory_set(chBuf, 0, BUFSIZE);

      try
      {

         dwRead = ::read(m_fd[0], chBuf, BUFSIZE);

         bSuccess = true;

      }
      catch (...)
      {

         bSuccess = false;

      }

      if (!bSuccess || dwRead == 0)
         return str;

      str += chBuf;

      return str;

   }


} // namespace acme_posix



