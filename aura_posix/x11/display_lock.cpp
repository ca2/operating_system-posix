//
// Created by camilo on 16/02/2021. 22:05 BRT <3TBS_!!
//
#include "framework.h"
//#ifdef WITH_X11
//#include <X11/Xlib-xcb.h>
//#endif
#include "display_lock.h"


namespace windowing_x11
{


   display_lock::display_lock(Display * pdisplay, bool bInitialLock) :
      m_pdisplay(pdisplay),
      m_bLocked(false)
   {

      if(bInitialLock)
      {

         lock();

      }

   }


   display_lock::~display_lock()
   {

      unlock();

   }


   void display_lock::lock()
   {

      if(!m_bLocked && ::is_set(m_pdisplay))
      {

         m_bLocked = true;

         XLockDisplay((Display *) m_pdisplay);

      }

   }


   void display_lock::unlock()
   {

      if(m_bLocked && ::is_set(m_pdisplay))
      {

         XUnlockDisplay((Display *) m_pdisplay);

         m_bLocked = false;

      }

   }


} // namespace windowing_x11



