//
// Created by camilo on 26/04/2021. 00:02 BRT <3TBS_!!
//
#include "framework.h"
#include "file_context.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/operating_system/shared_posix/c_error_number.h"
#include <sys/stat.h>

#if defined(__APPLE__) || defined(LINUX) || defined(__BSD__)
#include <unistd.h>
#include <errno.h>
#endif


namespace acme_posix
{


   ::payload file_context::length(const ::file::path &path, ::payload *pvarQuery)
   {

      if (path.m_iSize != -1)
      {

         return maximum(0, path.m_iSize);

      }

      ::payload payloadLength;

   //#ifdef WINDOWS
   //
   //   WIN32_FILE_ATTRIBUTE_DATA data;
   //
   //   if (!GetFileAttributesExW(utf8_to_unicode(path), GetFileExInfoStandard, &data))
   //   {
   //
   //      varRet.set_type(::e_type_null);
   //
   //      ((::file::path &) path).m_iSize = -2;
   //
   //   }
   //   else
   //   {
   //
   //      varRet = (((unsigned long long) data.nFileSizeHigh) << 32) | (unsigned long long) data.nFileSizeLow;
   //
   //      ((::file::path &) path).m_iSize = varRet.m_hi;
   //
   //   }
   //
   //#else
   //
      struct stat stat;

      if (::stat(path, &stat) == -1)
      {

         payloadLength.set_type(::e_type_null);

         ((::file::path &) path).m_iSize = -2;

      }
      else
      {

         payloadLength = (iptr)stat.st_size;

         ((::file::path &)path).m_iSize = payloadLength.m_hi;

      }

   //#endif

      return payloadLength;

   }


   bool file_context::is_read_only(const ::file::path &psz)
   {

      struct stat st;

      if (stat(psz, &st) != 0)
         return true;

      return !(st.st_mode & S_IWUSR);

   }


   void file_context::erase(const ::file::path &psz)
   {

      if (unlink(psz) != 0)
      {
      
         auto cerrornumber = c_error_number();
      
         if (cerrornumber.m_iErrorNumber != ENOENT) // already does not exist - consider removal successful - does not issue an exception
         {
         
            string strError;
         
            strError.formatf("Failed to delete file error=%d", cerrornumber.m_iErrorNumber);
         
            throw ::exception(error_failed, strError);
      
         }
         
      }

      //return ::success;

   }


   // file::path file_context::dropbox_client()
   // {
   //
   //    return directory()->dropbox_client()/ "dropbox";
   //
   // }


} // namespace acme_posix



