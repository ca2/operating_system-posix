//
// Created by camilo on 16/02/2021. 22:05 BRT <3TBS_!!
//
#include "framework.h"


namespace windowing_xcb
{


   display_lock::display_lock(::windowing_xcb::display * pdisplay, bool bInitialLock) :
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

         m_pdisplay->lock_display();

      }

   }


   void display_lock::unlock()
   {

      if(m_bLocked && ::is_set(m_pdisplay))
      {

         m_pdisplay->unlock_display();

         m_bLocked = false;

      }

   }


} // namespace windowing_xcb



