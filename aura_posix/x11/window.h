//
// Created by camilo on 04/05/2021 20:58 BRT <3ThomasBS_!!
// content added: "_get_wm_state_unlocked" by camilo 2023-09-01 08:10 <3ThomasBorregaardSorensen!!
// From windowing_x11 "_is_iconic_unlocked" by camilo 2023-09-01 08:12 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "aura/windowing/window.h"


namespace windowing_posix
{


   class window :
      virtual public ::windowing::window
   {
   public:


//#if defined(WITH_X11)

      enum enum_net_wm_sync
      {

         e_net_wm_sync_none,
         e_net_wm_sync_wait_configure,
         e_net_wm_sync_wait_paint,

      };

      enum_net_wm_sync                             m_enetwmsync;

      ::pointer<::xim::keyboard>m_pximkeyboard;


//#endif


      window();
      ~window() override;


      virtual bool _get_wm_state_unlocked(long & lState);

      bool _is_iconic_unlocked() override;


   };


} // namespace windowing_posix



