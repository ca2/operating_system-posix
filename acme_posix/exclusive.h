//
// Created by camilo on 2022-10-28 23:52 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/exclusive.h"


namespace acme_posix
{


   class CLASS_DECL_ACME exclusive :
      virtual public ::acme::exclusive
   {
      public:


   //   string                  m_strId;

   // #ifdef WINDOWS

   //       unsigned int                   m_dwLastError;
   //       bool                    m_bResourceException;

   // #else

          int                     m_iFile;
          int                     m_iLock;

          ::file::path           m_path;

   // #endif

      // ::pointer < ::mutex >     m_pmutex;


      exclusive(::particle * pparticle, const ::scoped_string & scopedstr);
      //exclusive();
      ~exclusive() override;


      bool exclusive_fails() const override;


   };


} // namespace acme_posix



