//
// Created by camilo on 17/02/2021. 23:08 BRT <3TBS_!!
//
#include "framework.h"
#include "display.h"
#include <xcb/xcb.h>


namespace windowing_xcb
{


   /// should be run at user_thread (xcb_thread)
   xcb_cursor_t display::_create_alpha_cursor(const ::image *pimage, int xHotSpot, int yHotSpot)
   {

      synchronous_lock synchronouslock(user_synchronization());

      windowing_output_debug_string("\n::CreateAlphaCursor 1");

      //display_lock displaylock(this);

      xcb_render_picture_t picture = _create_picture(pimage);

      xcb_cursor_t cursor = xcb_generate_id(m_pxcbdisplay->m_pconnection);

      auto cookie = xcb_render_create_cursor(m_pxcbdisplay->m_pconnection, cursor, picture, xHotSpot, yHotSpot);

      auto estatus = _request_check(cookie);

      xcb_render_free_picture(m_pxcbdisplay->m_pconnection, picture);

      if(!estatus)
      {

         return 0;

      }

      return cursor;

   }


} // namespace windowing_xcb



