// Created by camilo on 2024-06-02 16:49 <3ThomasBorregaardSorensen!!
// From idn by camilo on 2024-06-02 18:09 <3ThomasBorregaardSorensen!!
#pragma once


namespace nano
{


   namespace dynamic_library
   {


      class CLASS_DECL_ACME dynamic_library :
        virtual public ::acme::department
      {
      public:


         inline static const char * represented_component_name()
         {

            return "nano_dynamic_library";

         }


         idn();
         ~idn() override;


         virtual string idn_to_punycode(const ::string & str);
         virtual string idn_from_punycode(const ::string & str);


      };


   } // dynamic_library


} // nano


