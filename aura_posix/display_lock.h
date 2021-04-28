//
// Created by camilo on 16/02/2021. 22:00 BRT <3TBS_!!
//
#pragma once


namespace windowing_x11
{


   class CLASS_DECL_WINDOWING_X11 display_lock
   {
   public:


      __pointer(::windowing_x11::display)          m_pdisplay;
      bool                                         m_bLocked;


      display_lock(::windowing_x11::display * pdisplay, bool bInitialLock = true);
      ~display_lock();


      void lock();
      void unlock();


      inline ::windowing::display * display() { return m_pdisplay;  }


   };


} // namespace windowing_x11



