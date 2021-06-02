//
// Created by camilo on 26/04/2021. 00:02 BRT <3TBS_!!
//
#pragma once


namespace posix
{


   class CLASS_DECL_ACME_POSIX file_context :
      virtual public ::file_context
   {
   public:


      ::payload length(const ::file::path & path, ::payload * pvarQuery) override;
      
      bool is_read_only(const ::file::path &psz) override;

      ::extended::status del(const ::file::path & path) override;


   };


} // namespace posix



