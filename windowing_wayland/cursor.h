// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-02-01 20:16
#pragma once


#include "aura/windowing/cursor.h"
#include "_wayland.h"


namespace windowing_wayland
{


   class CLASS_DECL_WINDOWING_X11 cursor :
      virtual public ::windowing::cursor
   {
   public:


      //::Cursor                   m_cursor;
      ::wl_cursor *m_pwlcursor;
      wayland_buffer m_waylandbuffer;
      ::wl_cursor_image * m_pwlcursorimage;


      cursor();
      ~cursor() override;

//      virtual ::e_status initialize_system_default();

      //virtual ::e_status create_from_image(const ::image * pimage, ::i32 xHotspot, ::i16 yHotspot);

      //virtual ::e_status load_default_cursor(enum_cursor ecursor);

      void _create_os_cursor() override;

      ::e_status _load_default_cursor(enum_cursor ecursor);


   };


} // namespace windowing_wayland



