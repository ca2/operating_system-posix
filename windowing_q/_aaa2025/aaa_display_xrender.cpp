//
// Created by camilo on 17/02/2021. 23:08 BRT <3TBS_!!
//
#include "../framework.h"
#include "windowing_q.h"
#include "../cursor.h"
#include "../display.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"
#include "windowing_system_x11/display_lock.h"
#include "../_q.h"


namespace windowing_q
{

//
//    /// should be run at user_thread (x11_thread)
//    ::wl_cursor * display::create_alpha_cursor(::image::image *pimage, int xHotSpot, int yHotSpot)
//    {
//
//       //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
// //      windowing_output_debug_string("::CreateAlphaCursor 1");
// //
// //      //display_lock displaylock(Display());
// //
// //      Picture picture = xrender_create_picture(pimage);
// //
// //      auto cursor = XRenderCreateCursor(Display(), picture, xHotSpot, yHotSpot);
//
//    auto pcursor = øcreate_new< ::windowing_q::cursor>();
//
//    pcursor->m_szHotspotOffset.cx = xHotSpot;
//    pcursor->m_szHotspotOffset.cy = yHotSpot;
//    pcursor->m_pimage = pimage;
//    //update_wayland_buffer(pcursor->m_waylandbuffer, pimage);
//
//       return nullptr;
//
//    }


} // namespace windowing_q



