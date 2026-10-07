//
// Created by camilo on 01/Sep/2023 02:20 <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "shmem.h"

#if defined(__HAIKU__)
#include <OS.h>
#else
#include <sys/ipc.h>
#include <sys/shm.h>
#endif



namespace acme_posix
{


   shmem::shmem()
   {

      m_shmid = -1;

      m_shmaddr = nullptr;

   }


   shmem::~shmem()
   {

      destroy_shared_memory();

   }


   void shmem::map_shared_memory(memsize size)
   {

      destroy_shared_memory();

#if defined(__HAIKU__)
      if (size <= 0 || size > SIZE_MAX - (B_PAGE_SIZE - 1))
         throw ::exception(error_bad_argument);
      const size_t areaSize = ((size_t)size + B_PAGE_SIZE - 1) / B_PAGE_SIZE * B_PAGE_SIZE;
      m_shmid = ::create_area("acme shared memory", &m_shmaddr, B_ANY_ADDRESS,
         areaSize, B_NO_LOCK, B_READ_AREA | B_WRITE_AREA | B_CLONEABLE_AREA);
      if (m_shmid < B_OK)
      {
         m_shmaddr = nullptr;
         throw ::exception(error_resource);
      }
#else
      m_shmid = shmget(IPC_PRIVATE, size, IPC_CREAT | 0777); /* kernel id */

      m_shmaddr = shmat(m_shmid, 0, 0); /* address in client */
#endif

   }


   void shmem::destroy_shared_memory()
   {

#if defined(__HAIKU__)
      if (m_shmid >= B_OK)
         ::delete_area(m_shmid);
      m_shmid = -1;
      m_shmaddr = nullptr;
#else
      if (m_shmaddr)
      {

         shmdt(m_shmaddr);

         m_shmaddr = nullptr;

      }

      if (m_shmid >= 0)
      {

         shmctl(m_shmid, IPC_RMID, NULL);

         m_shmid = -1;

      }
#endif

   }


} // namespace acme_posix



