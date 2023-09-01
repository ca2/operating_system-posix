//
// Created by camilo on 01/Sep/2023 02:20 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "shmem.h"

#include <sys/ipc.h>
#include <sys/shm.h>



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

      m_shmid = shmget(IPC_PRIVATE, size, IPC_CREAT | 0777); /* kernel id */

      m_shmaddr = shmat(m_shmid, 0, 0); /* address in client */

   }


   void shmem::destroy_shared_memory()
   {

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

   }


} // namespace acme_posix



