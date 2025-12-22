//
// Created by camilo on 2022-10-24 08:49 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "windowing_system_xcb/_.h"


#if defined(_nano_user_xcb_project)
   #define CLASS_DECL_NANO_USER_XCB CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NANO_USER_XCB CLASS_DECL_IMPORT
#endif



namespace xcb
{


   namespace nano
   {


      namespace user
      {


         class display;


      } // namespace user


   } // namespace nano


} // namespace xcb



