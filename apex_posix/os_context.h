#pragma once


#include "apex/platform/os_context.h"


namespace apex_posix
{


   class CLASS_DECL_APEX os_context :
      virtual public ::os_context
   {
   public:


      os_context();
      ~os_context() override;


      bool is_alias(const ::file::path & path) override;
      
      
      ::process_identifier current_process_identifier() override;


   };


} // namespace apex_posix



