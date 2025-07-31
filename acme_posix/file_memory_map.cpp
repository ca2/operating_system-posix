//
// Created by camilo on 13/02/2021. 22:55 BRT <3TBS_!!
//
#include "framework.h"
#include "file_memory_map.h"
#include "mutex.h"
#include "directory_system.h"
#include "acme/operating_system/ansi/file_c.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"


#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#undef USE_MISC
#include <unistd.h>


namespace acme_posix
{


   file_memory_map::file_memory_map()
   {

      m_iFile = -1;
      m_pdata = (void *)MAP_FAILED;

   }


   file_memory_map::~file_memory_map()
   {


   }


   bool file_memory_map::is_mapped()
   {

      return m_pdata != (void *)MAP_FAILED;

   }


   bool file_memory_map::close()
   {

      if (m_pdata != (void *)MAP_FAILED)
      {
         
         if(m_bCreate)
         {
            
            ::msync(m_pdata, m_size, MS_SYNC);
            
         }
         
         auto size = system()->m_pfilesystem->get_size_fd(m_iFile);
         
         ::munmap(m_pdata, size);
            
         m_pdata = (void *)MAP_FAILED;

      }

      if (m_iFile != -1)
      {

         if(m_bCreate)
         {
          
            ::fsync(m_iFile);

         }
         
         ::close(m_iFile);

         m_iFile = -1;

      }

      return true;

   }


   bool file_memory_map::open()
   {

      close();

      int iOpen;

      if (m_bCreate)
      {

         iOpen = O_RDWR | O_CREAT;

      }
      else
      {

         iOpen = O_RDWR;

      }

      ::file::path path(get_path());
      
      if(m_bCreate)
      {
         
         directory_system()->create(path.folder());
         
      }

      m_iFile = ::open(path, iOpen | O_CLOEXEC, S_IRUSR | S_IWUSR);

      if (m_iFile == -1)
      {

         close();

         return false;

      }
      
      if(m_bCreate && m_size > 0)
      {
         
         file_system()->set_size(m_iFile, m_size);
         
      }
      
      if(m_size < 0)
      {
       
         m_size = file_system()->get_size_fd(m_iFile);
         
      }

      m_pdata = (color32_t *)mmap(nullptr, m_size, (m_bRead ? PROT_READ : 0) | (m_bWrite ? PROT_WRITE : 0), MAP_SHARED, m_iFile, 0);

      if (m_pdata == (void *)MAP_FAILED)
      {

         close();

         return false;

      }

      string strMutex;

      strMutex = m_strName + "-mutex";

      set_synchronization(__allocate ::acme_posix::mutex(m_papplication, false, strMutex));

      return true;

   }


   string file_memory_map::calculate_path_from_name(const ::scoped_string & scopedstrName)
   {

      string strPath;

      strPath = "/var/tmp/ca2/";

      strPath += strName;

      return strPath;

   }


} // namespace acme_posix



