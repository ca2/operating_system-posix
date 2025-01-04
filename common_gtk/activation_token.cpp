//
// Created by camilo on 2024-12-21 01:37 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "activation_token.h"


namespace common_gtk
{


   activation_token::activation_token(guint32 time) :
      m_time(time)
   {


   }


   bool activation_token::matches(const ::user::activation_token* pactivationtoken) const
   {

      ::cast<activation_token> ptoken = (::user::activation_token *)pactivationtoken;

      if (!ptoken)
      {

        return false;

      }

      return ptoken->m_time == m_time;

   }


} // namespace common_gtk