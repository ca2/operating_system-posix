// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Soerensen MY ONLY LORD
// recreated by Camilo 2021-02-01 20:19
#include "framework.h"
#include "cursor.h"
#include "windowing.h"
#include "display.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
//#include "aura_posix/_x11.h"


namespace windowing_xcb
{


   cursor::cursor()
   {

      m_cursor = 0;

   }


   cursor::~cursor()
   {


   }


//   ::e_status cursor::initialize_system_default()
//   {
//
//      return ::success;
//
//   }

   
   ::e_status cursor::_create_from_image(const ::image * pimage, ::i32 xHotspot, ::i16 yHotspot)
   {

      throw ::interface_only();
      
   }


   ::e_status cursor::_load_default_cursor(enum_cursor ecursor)
   {

      int iCursor;

      iCursor = ::x11::get_default_system_cursor_glyph(ecursor);

      if(iCursor < 0)
      {

         return ::error_failed;

      }

      //_synchronous_lock sl(user_synchronization());

      windowing_output_debug_string("::x11_GetWindowRect 1");

      auto psystem = system();

      auto psession = psystem->session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = (windowing_xcb::display *) pwindowing->display()->m_pDisplay;

      auto cursor = pdisplay->_create_font_cursor(iCursor);

      if(!cursor)
      {

         return error_failed;

      }

      m_cursor = cursor;

      return ::success;

   }


   void cursor::_create_os_cursor()
   {

      if(m_cursor)
      {

         //return ::success;

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


   xcb_cursor_t cursor::get_os_cursor()
   {

      if(!m_cursor)
      {

         //if(m_bLoadSystemDefaultCursorHint)
         //{

//            load_default_cursor(m_ecursor);

  //       }

         _create_os_cursor();

      }

      return m_cursor;


   }

} // namespace windowing_xcb




