// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sørensen MY ONLY LORD
// recreated by Camilo 2021-02-01 20:19
#include "framework.h"
#include "cursor.h"
#include "windowing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "aura_posix/_x11.h"
#include "aura_posix/x11/display_lock.h"
#include <X11/cursorfont.h>
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
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


//   ::e_status cursor::initialize_system_default()
//   {
//
//      auto estatus = load_default_cursor(m_ecursor);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
//   }

   
//   ::e_status cursor::create_from_image(const ::image * pimage, ::i32 xHotspot, ::i16 yHotspot)
//   {
//
//      throw ::interface_only();
//
//      throw ::interface_only();
//
//   }


   void cursor::_create_os_cursor()
   {

      if(m_cursor)
      {

         return;

      }

      //auto estatus =
      //
      _load_default_cursor(m_ecursor);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }

   
   ::e_status cursor::_load_default_cursor(enum_cursor ecursor)
   {

      int iCursor;

      iCursor = ::x11::get_default_system_cursor_glyph(ecursor);

      if(iCursor == 0)
      {

         return ::error_failed;

      }

//      if(ecursor == e_cursor_size_top_left)
//      {
//
//         iCursor = XC_top_left_corner;
//
//      }
//      else if(ecursor == e_cursor_size_top_right)
//      {
//
//         iCursor = XC_top_right_corner;
//
//      }
//      else if(ecursor == e_cursor_size_top)
//      {
//
//         iCursor = XC_top_side;
//
//      }
//      else if(ecursor == e_cursor_size_right)
//      {
//
//         iCursor = XC_right_side;
//
//      }
//      else if(ecursor == e_cursor_size_left)
//      {
//
//         iCursor = XC_left_side;
//
//      }
//      else if(ecursor == e_cursor_size_bottom)
//      {
//
//         iCursor = XC_bottom_side;
//
//      }
//      else if(ecursor == e_cursor_size_bottom_left)
//      {
//
//         iCursor = XC_bottom_left_corner;
//
//      }
//      else if(ecursor == e_cursor_size_bottom_right)
//      {
//
//         iCursor = XC_bottom_right_corner;
//
//      }
//      else if(ecursor == e_cursor_arrow)
//      {
//
//         iCursor = XC_arrow;
//
//      }
//
//      if(iCursor < 0)
//      {
//
//         return ::error_failed;
//
//      }

      synchronous_lock sl(user_synchronization());

      windowing_output_debug_string("\n::x11_GetWindowRect 1");

      auto psystem = acmesystem();

      auto psession = psystem->get_session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing1();

      auto pdisplay = pwindowing->display();

      auto px11display = (::windowing_x11::display *) pwindowing->display()->m_pDisplay;

      display_lock lock(px11display->Display());

      auto cursor = XCreateFontCursor(px11display->Display(), iCursor);

      if(!cursor)
      {

         return error_failed;

      }

      m_cursor = cursor;

      return ::success;

   }


} // namespace windowing_x11




