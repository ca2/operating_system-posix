//
// Created by camilo on 17/02/2021. 23:08 BRT <3TBS_!!
//
#include "framework.h"
#include "windowing_x11.h"
#include "display.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"
#include "aura_posix/x11/display_lock.h"
#include "_x11.h"


namespace windowing_x11
{


   /// should be run at user_thread (x11_thread)
   Cursor display::create_alpha_cursor(const ::image *pimage, int xHotSpot, int yHotSpot)
   {

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("\n::CreateAlphaCursor 1");

      display_lock displaylock(Display());

      Picture picture = xrender_create_picture(pimage);

      auto cursor = XRenderCreateCursor(Display(), picture, xHotSpot, yHotSpot);

      return cursor;

   }


} // namespace windowing_x11



