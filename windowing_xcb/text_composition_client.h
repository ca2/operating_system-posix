//
// Created by camilo on 25/02/2021. 21:30 BRT <3TBS_!!
//
#pragma once


#include "aura/user/user/text_composition_client.h"


namespace windowing_xcb
{


   class CLASS_DECL_WINDOWING_XCB text_composition_client :
      virtual public ::user::text_composition_client
   {
   public:


      text_composition_client();
      ~text_composition_client() override;


   };


} // namespace windowing_xcb



