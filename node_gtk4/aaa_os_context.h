// Created by camilo on 2024-01-27 20:38 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex_posix/os_context.h"


namespace node_gtk4
{


   class CLASS_DECL_APEX os_context :
      virtual public ::apex_posix::os_context
   {
      public:


      os_context();
      ~os_context() override;


//      void set_file_extension_mime_type(string_array & straExtension, string_array & straMimeType) override;
//
//      void _set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);
//
//      void _defer_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);
//
//      bool _system_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);
//
//      bool _user_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType);

   };


} // namespace node_gtk4



