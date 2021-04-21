// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard S�rensen MY ONLY LORD
// recreated by Camilo 2021-02-01 20:19
#include "framework.h"
#include "_windowing.h"
#include <X11/cursorfont.h>


namespace windowing_x11
{


   cursor::cursor()
   {

   }


   cursor::~cursor()
   {


   }


   ::e_status cursor::initialize_system_default()
   {

      auto estatus = load_default_cursor(m_ecursor);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }

   
   ::e_status cursor::create_from_image(const ::image * pimage, ::i32 xHotspot, ::i16 yHotspot)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }

   
   ::e_status cursor::load_default_cursor(enum_cursor ecursor)
   {

      int iCursor = 0;

      if(ecursor == e_cursor_size_top_left)
      {

         iCursor = XC_top_left_corner;

      }
      else if(ecursor == e_cursor_size_top_right)
      {

         iCursor = XC_top_right_corner;

      }
      else if(ecursor == e_cursor_size_top)
      {

         iCursor = XC_top_side;

      }
      else if(ecursor == e_cursor_size_right)
      {

         iCursor = XC_right_side;

      }
      else if(ecursor == e_cursor_size_left)
      {

         iCursor = XC_left_side;

      }
      else if(ecursor == e_cursor_size_bottom)
      {

         iCursor = XC_bottom_side;

      }
      else if(ecursor == e_cursor_size_bottom_left)
      {

         iCursor = XC_bottom_left_corner;

      }
      else if(ecursor == e_cursor_size_bottom_right)
      {

         iCursor = XC_bottom_right_corner;

      }
      else if(ecursor == e_cursor_arrow)
      {

         iCursor = XC_arrow;

      }

      if(iCursor == 0)
      {

         return ::error_failed;

      }

      synchronous_lock sl(user_mutex());

      windowing_output_debug_string("\n::x11_GetWindowRect 1");

      auto psystem = m_psystem;

      auto psession = psystem->get_session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      auto px11display = (::windowing_x11::display *) pwindowing->display()->m_pDisplay;

      display_lock lock(px11display);

      auto cursor = XCreateFontCursor(px11display->Display(), iCursor);

      if(!cursor)
      {

         return error_failed;

      }

      m_cursor = cursor;

      return ::success;

   }


} // namespace windowing_x11




