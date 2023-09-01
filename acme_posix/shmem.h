//
// Created by camilo on 01/Sep/2023 02:20 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace acme_posix
{


   class CLASS_DECL_ACME_POSIX shmem :
      virtual public ::particle
   {
      public:


      int                  m_shmid;		/* kernel id */
      void *               m_shmaddr;	/* address in client */


      shmem();
      ~shmem() override;


      virtual void map_shared_memory(memsize size);
      virtual void destroy_shared_memory();


   };


} // namespace acme_posix



