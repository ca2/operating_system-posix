#pragma once


namespace windows
{


   class CLASS_DECL_ACME api_base
   {
   public:


      static FARPROC get_address(const scoped_string & strModule, const_char_pointer lpszName);

   };



   template < typename PFN >
   class api :
      public api_base
   {
   public:


      inline static PFN get_address(const scoped_string & strModule, const_char_pointer lpszName)
      {

         return (PFN) api_base::get_address(scopedstrModule, lpszName);
         
      }


   };


} // namespace windows



