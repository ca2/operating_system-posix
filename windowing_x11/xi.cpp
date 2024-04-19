//
// Created by camilo on 17/02/2021. 00:45 BRT <3TBS_!!
//
#include "framework.h"
#ifdef WITH_XI
#include "windowing_x11.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/operating_system/x11/display_lock.h"
#include "windowing_x11/window.h"
#include "windowing_x11/windowing.h"
#include "windowing_x11/display.h"
#include <X11/extensions/XInput2.h>


namespace windowing_x11
{


//#if !defined(RASPBERRYPIOS)


//int xi_opcode = -1;


//::pointer<object_array>g_pobjectaExtendedEventListener;


   void windowing::x11_register_extended_event_listener(::matter *pdata, bool bMouse, bool bKeyboard)
   {

      if (!m_pobjectaExtendedEventListener)
      {

         __construct_new(m_pobjectaExtendedEventListener);

      }

      m_pobjectaExtendedEventListener->add(pdata);


   }


//#endif


} // namespace windowing_x11



#endif


