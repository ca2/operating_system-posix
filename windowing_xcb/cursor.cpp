// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard S�rensen MY ONLY LORD
// recreated by Camilo 2021-02-01 20:19
#include "framework.h"
#include "_windowing.h"


namespace windowing_xcb
{


   cursor::cursor()
   {

   }


   cursor::~cursor()
   {


   }


   ::e_status cursor::initialize_system_default()
   {

      return ::success;

   }

   
   ::e_status cursor::create_from_image(const ::image * pimage, ::i32 xHotspot, ::i16 yHotspot)
   {

      __throw(error_interface_only);
      
      return error_interface_only;

   }

   
   ::e_status cursor::load_default_cursor(enum_cursor ecursor)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


} // namespace windowing_xcb




