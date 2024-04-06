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

   //       ::u32                   m_dwLastError;
   //       bool                    m_bResourceException;

   // #else

          int                     m_iFile;
          int                     m_iLock;

   // #endif

      // ::pointer < ::mutex >     m_pmutex;


      exclusive(::particle * pparticle, const string & str);
      //exclusive();
      ~exclusive() override;


      bool exclusive_fails() const override;


   };


} // namespace acme_posix



