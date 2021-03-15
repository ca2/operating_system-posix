//
// Created by camilo on 16/02/2021. 22:00 BRT <3TBS_!!
//
#pragma once

//
//class osdisplay_dataptra;
//class osdisplay_data;
//class ::mutex;


//CLASS_DECL_AURA i32 osdisplay_find(xcb_connection_t * pdisplay);
//CLASS_DECL_AURA osdisplay_data * osdisplay_get(xcb_connection_t * pdisplay);
//CLASS_DECL_AURA bool osdisplay_remove(xcb_connection_t * pdisplay);


namespace windowing_xcb
{


   class CLASS_DECL_WINDOWING_XCB display_lock
   {
   public:


      __pointer(::windowing_xcb::display)        m_pdisplay;
      bool                                            m_bLocked;


      display_lock(::windowing_xcb::display * pdisplay, bool bInitialLock = true);
      ~display_lock();


      void lock();
      void unlock();


      inline ::windowing::display * display() { return m_pdisplay;  }


   };


} // namespace windowing_xcb



