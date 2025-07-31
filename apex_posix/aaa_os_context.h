#pragma once


#include "apex/platform/node.h"
//#include "apex/platform/os_context.h"



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

      virtual ::file::path _get_auto_start_desktop_file_path(const ::scoped_string & scopedstrAppId);

      void register_user_auto_start(const ::scoped_string & scopedstrAppId, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments,
                                    bool bRegister) override;

      bool is_user_auto_start(const ::scoped_string & scopedstrAppId) override;

   };


} // namespace apex_posix



