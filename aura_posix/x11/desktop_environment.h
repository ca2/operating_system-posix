//
// Created by camilo on 24/09/22.
//

// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-05-22 03:05 <3TBS, Mummi and bilbo!!
// hi5 contribution...
// From windowing.h by camilo on 2022-09-22 22:33 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/windowing/desktop_environment.h"


namespace windowing_posix
{


   class CLASS_DECL_AURA_POSIX desktop_environment :
      virtual public ::windowing::desktop_environment
   {
   public:


      desktop_environment();
      ~desktop_environment() override;



   };


} // namespace windowing_posix



