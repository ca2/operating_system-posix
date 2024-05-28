//
// Created by camilo on 2024-05-27 15:32 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/nano/compress/compress.h"


namespace command_line
{


   namespace nano
   {


      namespace compress
      {


         class CLASS_DECL_ACME compress :
            virtual public ::nano::compress::compress
         {
         public:


         compress();
            ~compress() override;


         void unzip(const ::file::path & pathFolder, const ::payload & payloadZip) override;


         };


      } // namespace http


   } // namespace nano


} // namespace apple





