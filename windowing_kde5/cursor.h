// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-02-01 20:16
#pragma once


#include "nano_user_wayland/_.h"
#include "aura/windowing/cursor.h"
#include "_kde5.h"


namespace windowing_kde5
{


   class CLASS_DECL_WINDOWING_KDE5 cursor :
      virtual public ::windowing::cursor
   {
   public:


      //::Cursor                   m_cursor;
      // ::wl_cursor *m_pwlcursor;
      // ::wayland::nano::user::buffer m_waylandbuffer;
      // ::wl_cursor_image * m_pwlcursorimage;


      cursor();
      ~cursor() override;

//      virtual ::e_status initialize_system_default();

      //virtual ::e_status create_from_image(const ::image::image *pimage, ::i32 xHotspot, ::i16 yHotspot);

      //virtual ::e_status load_default_cursor(enum_cursor ecursor);

      void _create_os_cursor() override;

      ::e_status _load_default_cursor(enum_cursor ecursor);


   };


} // namespace windowing_kde5



