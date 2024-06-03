//
// Created by camilo on 2024-06-02 20:06 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace nano
{


   namespace account
   {


      class id :
              virtual public ::particle
      {
      public:


         user();
         ~user() override;


         virtual bool is_equal(id * pid);
         virtual bool is_less(id * pid);

      };


   } // namespace account


} // namespace nano

