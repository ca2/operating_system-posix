//
// Created by camilo on 2022-10-24 08:49 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "windowing_system_kde5/_.h"


#if defined(_nano_user_kde5_project)
   #define CLASS_DECL_NANO_USER_KDE5 CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NANO_USER_KDE5 CLASS_DECL_IMPORT
#endif


namespace kde5
{


   namespace nano
   {


      namespace user
      {


         class display;


         class window;


      } // namespace user


   } // namespace nano


} // namespace kde5



