//
// Created by camilo on 17/02/2021. 23:08 BRT <3TBS_!!
//
#include "framework.h"
#include "windowing_wayland.h"
#include "cursor.h"
#include "display.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"
#include "aura_posix/x11/display_lock.h"
#include "_x11.h"


namespace windowing_wayland
{


   /// should be run at user_thread (x11_thread)
   ::wl_cursor * display::create_alpha_cursor(::image *pimage, int xHotSpot, int yHotSpot)
   {

      synchronous_lock synchronouslock(user_synchronization());

//      windowing_output_debug_string("::CreateAlphaCursor 1");
//
//      //display_lock displaylock(Display());
//
//      Picture picture = xrender_create_picture(pimage);
//
//      auto cursor = XRenderCreateCursor(Display(), picture, xHotSpot, yHotSpot);

   auto pcursor = __create_new< ::windowing_wayland::cursor>();

   pcursor->m_szHotspotOffset.cx() = xHotSpot;
   pcursor->m_szHotspotOffset.cy() = yHotSpot;
   pcursor->m_pimage = pimage;
   pcursor->m_waylandbuffer = create_wayland_buffer(pimage);

      return nullptr;

   }


} // namespace windowing_wayland



