// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sorensen MY ONLY LORD
// recreated by Camilo 2021-02-01 20:19
#include "framework.h"
#include "cursor.h"
#include "windowing.h"
#include "acme_windowing_x11/display_lock.h"
#include <X11/cursorfont.h>
#include "aura/platform/session.h"
#include "aura/windowing/cursor_manager.h"
#include "display.h"


CLASS_DECL_ACME ::particle * user_synchronization();


namespace windowing_x11
{


   cursor::cursor()
   {

   }


   cursor::~cursor()
   {


   }


   void cursor::_create_os_cursor()
   {

      if(m_cursor)
      {

         return;

      }

      _load_default_cursor(m_ecursor);


   }

   
   ::e_status cursor::_load_default_cursor(enum_cursor ecursor)
   {

      auto iCursor = ::x11::get_default_system_cursor_glyph(ecursor);

      information() << "_load_default_cursor glyph index : " << iCursor;

      if(iCursor < 0)
      {

         return ::error_failed;

      }

      auto pcursormanager = m_pcursormanager;

      auto pwindowing = pcursormanager->m_pwindowing;

      auto pdisplay = pwindowing->display();

      ::cast < ::windowing_x11::display > px11display = pwindowing->display();

      ::x11::display_lock lock(px11display->__x11_display());

      auto cursor = XCreateFontCursor(px11display->__x11_display(), iCursor);

      if(iCursor == XC_bottom_right_corner)
      {

         information() << "XC_bottom_right_corner";

      }

      if(!cursor)
      {

         warning() << "_load_default_cursor XCreateFontCursor failed";

         return error_failed;

      }

      m_cursor = cursor;

      information() << "_load_default_cursor cursor : " << cursor;

      return ::success;

   }


} // namespace windowing_x11




