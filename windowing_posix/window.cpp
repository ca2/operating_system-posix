//
// Created by camilo on 04/05/2021 20:58 BRT <3ThomasBS_!!
// content added: "_get_wm_state_unlocked" by camilo 2023-09-01 08:10 <3ThomasBorregaardSorensen!!
// From windowing_x11 "_is_iconic_unlocked" by camilo 2023-09-01 08:12 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "window.h"
#include "acme/exception/interface_only.h"
//#if !defined(HAS_GTK3) && !defined(HAS_GTK4) && !defined(HAS_KDE5) && !defined(HAS_KDE6)
//#include <X11/Xutil.h>
//#endif


namespace windowing_posix
{


   window::window()
   {

      //m_enetwmsync = e_net_wm_sync_none;
   }


   window::~window()
   {

   }


   // bool window::_get_wm_state_unlocked(long & lState)
   // {

   //    throw interface_only();

   //    return false;

   // }



//    bool window::_is_iconic_unlocked()
//    {

// #ifdef XDISPLAY_LOCK_LOG

//       b_prevent_xdisplay_lock_log = true;

// #endif

//       long lState = -1;

//       if(!_get_wm_state_unlocked(lState))
//       {

//          return false;

//       }

//       bool bIconic = lState == IconicState;

// #ifdef XDISPLAY_LOCK_LOG

//       b_prevent_xdisplay_lock_log = false;

// #endif

//       return lState;

//    }



} // namespace windowing_posix



