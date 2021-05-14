//
// Created by camilo on 26/04/2021. 00:02 BRT <3TBS_!!
//
#include "framework.h"
#include "file_context.h"
#include <sys/stat.h>


namespace posix
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
   //   if (!GetFileAttributesExW(::str::international::utf8_to_unicode(path), GetFileExInfoStandard, &data))
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
   //      varRet = (((u64) data.nFileSizeHigh) << 32) | (u64) data.nFileSizeLow;
   //
   //      ((::file::path &) path).m_iSize = varRet.m_i64;
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

         ((::file::path &)path).m_iSize = payloadLength.m_i64;

      }

   //#endif

      return payloadLength;

   }


} // namespace posix



