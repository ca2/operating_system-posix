#pragma once


#include "acme/operating_system/pipe.h"


namespace acme_posix
{


   class CLASS_DECL_ACME pipe :
      virtual public ::operating_system::pipe
   {
   public:


      //__creatable_from_library(pipe, ::operating_system::pipe, "acme_posix");


      char *               m_pchBuf;
      string               m_strRead;

      i32                  m_fd[2];


      pipe();
       ~pipe() override;


      bool create(bool bBlock = true, bool bInherit = false) override;


      bool not_inherit_read() override;
      bool not_inherit_write() override;

      bool write(const char * psz) override;
      string read() override;
      string one_pass_read() override;

      
   };


} // namespace acme_posix



