//
// Created by camilo on 2022-10-24 08:47 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "windowing_system_gtk3/_.h"


#if defined(_nano_user_gtk3_project)
   #define CLASS_DECL_NANO_USER_GTK3  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NANO_USER_GTK3  CLASS_DECL_IMPORT
#endif



namespace gtk3
{

namespace nano
{
   namespace  user
   {
   class display;
   }
}

} // namespace gtk3



