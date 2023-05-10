#include "framework.h"
#include "os_context.h"
#include <sys/stat.h>
#include <unistd.h>


namespace apex_posix
{


   os_context::os_context()
   {


   }


   os_context::~os_context()
   {


   }


   bool os_context::is_alias(const ::file::path & path)
   {

      if (::is_empty(path))
      {

         return false;

      }

      struct stat st;

      if (lstat(path, &st) == -1)
      {

         return false;

      }

      if (S_ISLNK(st.st_mode))
      {

         return true;

      }

      return false;

   }


   ::process_identifier os_context::current_process_identifier()
   {

      return ::getpid();

   }



} // namespace apex_posix




