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


      virtual ::payload length(const ::file::path & path, ::payload * pvarQuery) override;


   };


} // namespace posix



