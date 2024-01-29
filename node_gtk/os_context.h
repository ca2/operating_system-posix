// Created by camilo on 2024-01-27 20:38 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex_posix/os_context.h"


namespace node_gtk
{


   class CLASS_DECL_APEX os_context :
      virtual public ::apex_posix::os_context
   {
      public:


      os_context();
      ~os_context() override;


      void add_default_program(string_array & straExtension, string_array & straMimeType) override;

      void _add_default_program(const scoped_string & scopedExtension, const scoped_string & scopedMimeType);

      void _defer_add_mime_type(const scoped_string & scopedExtension, const scoped_string & scopedMimeType);


   };


} // namespace node_gtk



