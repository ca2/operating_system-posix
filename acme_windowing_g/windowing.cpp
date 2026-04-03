//
// Created by camilo on 4/2/26.
//
//
// Created by camilo on 2024-04-02 01:39 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "windowing.h"


namespace g
{


   namespace acme
   {


      namespace windowing
      {


         windowing::windowing()
         {


         }


         windowing::~windowing()
         {


         }


         ::string windowing::get_version()
         {

            ::string str;

            str.format("{}.{}.{}",
               gtk_get_major_version(),
               gtk_get_minor_version(),
               gtk_get_micro_version());

            return str;

         }


      } // namespace windowing


   } // namespace acme


} // namespace g
