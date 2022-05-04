//
// Created by camilo on 13/02/2021.
//
#pragma once


#include "acme/filesystem/file/memory_map.h"


namespace acme_posix
{


   class CLASS_DECL_ACME file_memory_map :
      virtual public ::file::memory_map
   {
   public:


      //__creatable_from_library(file_memory_map, ::file::memory_map, "acme_posix");


      int                        m_iFile;


      file_memory_map();
      ~file_memory_map() override;


      virtual bool open() override;
      virtual bool close() override;

      virtual bool is_mapped() override;


      virtual string calculate_path_from_name(const string & strName) override;


   };


} // namespace acme_posix



