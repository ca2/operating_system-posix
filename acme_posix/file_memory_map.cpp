//
// Created by camilo on 13/02/2021. 22:55 BRT <3TBS_!!
//
#include "framework.h"
#include "acme/node/operating_system/ansi/file_c.h"
#include "file_memory_map.h"


#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#undef USE_MISC
#include <unistd.h>


namespace posix
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

         ::munmap(m_pdata, m_psystem->m_pacmefile->get_size_fd(m_iFile));

         m_pdata = (void *)MAP_FAILED;

      }

      if (m_iFile != -1)
      {

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

      m_psystem->m_pacmedir->create(path.folder());

      m_iFile = ::open(path, iOpen, S_IRUSR | S_IWUSR);

      if (m_iFile == -1)
      {

         close();

         return false;

      }

      m_psystem->m_pacmefile->set_size(m_iFile, m_size);

      m_pdata = (color32_t *)mmap(nullptr, m_size, (m_bRead ? PROT_READ : 0) | (m_bWrite ? PROT_WRITE : 0), MAP_SHARED, m_iFile, 0);

      if (m_pdata == (void *)MAP_FAILED)
      {

         close();

         return false;

      }

      string strMutex;

      strMutex = m_strName + "-mutex";

      set_mutex(new ::mutex(m_psystem, false, strMutex));

      return true;

   }


   string file_memory_map::calculate_path_from_name(const string & strName)
   {

      string strPath;

      strPath = "/var/tmp/ca2/";

      strPath += strName;

      return strPath;

   }


} // namespace file



