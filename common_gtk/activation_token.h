//
// Created by camilo on 2024-12-21 <3ThomasBorregaardSorensen!!
//

#pragma once


#include "acme/user/user/activation.h"
#include <gdk/gdk.h>


namespace common_gtk
{


   class activation_token :
   virtual public ::user::activation_token
   {
   public:


      guint32 m_time;


      activation_token(guint32 time);


      bool matches(const ::user::activation_token* pactivationtoken) const override;


   };


} // namespace common_gtk



