//
// Created by camilo on 2022-10-24 08:47 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "windowing_system_x11/_.h"


#if defined(_nano_user_x11_project)
   #define CLASS_DECL_NANO_USER_X11  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NANO_USER_X11  CLASS_DECL_IMPORT
#endif



namespace x11
{

namespace nano
{
   namespace  user
   {
   class display;
   }
}

} // namespace x11



