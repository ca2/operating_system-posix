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

      virtual ::file::path _get_auto_start_desktop_file_path(const ::string & strAppId);

      void register_user_auto_start(const string & strAppId, const ::file::path & pathExecutable, const string & strArguments,
                                    bool bRegister) override;

      bool is_user_auto_start(const string & strAppId) override;

   };


} // namespace apex_posix



