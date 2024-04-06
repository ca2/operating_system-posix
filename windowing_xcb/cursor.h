// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-02-01 20:16
#pragma once


#include "aura/windowing/cursor.h"
#include <xcb/xcb.h>


namespace windowing_xcb
{


   class CLASS_DECL_WINDOWING_XCB cursor :
      virtual public ::windowing::cursor
   {
   public:


      xcb_cursor_t               m_cursor;


      cursor();
      ~cursor() override;


      //virtual ::e_status initialize_system_default();

      virtual ::e_status _create_from_image(const ::image * pimage, ::i32 xHotspot, ::i16 yHotspot);

      virtual ::e_status _load_default_cursor(enum_cursor ecursor);

      void _create_os_cursor() override;


      xcb_cursor_t get_os_cursor();


   };


} // namespace windowing_xcb



