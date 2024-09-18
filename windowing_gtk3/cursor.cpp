// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sorensen MY ONLY LORD
// recreated by Camilo 2021-02-01 20:19
#include "framework.h"
#include "cursor.h"
#include "window.h"
#include "windowing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "aura/graphics/image/image.h"
//#include "aura_posix/_x11.h"
#include "windowing_system_x11/display_lock.h"
//#include <X11/cursorfont.h>
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "display.h"



CLASS_DECL_ACME ::particle * user_synchronization();


namespace windowing_gtk3
{


   cursor::cursor()
   {

      m_pgdkcursor = nullptr;

   }


   cursor::~cursor()
   {

      g_object_unref(m_pgdkcursor);

   }



   void cursor::_create_os_cursor()
   {

      if(m_pgdkcursor)
      {

         return;

      }

      _load_default_cursor(m_ecursor);


   }

   
   ::e_status cursor::_load_default_cursor(enum_cursor ecursor)
   {

      auto psystem = system();

      auto psession = psystem->session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      ::pointer < ::windowing_gtk3::display> pwaylanddisplay =  pdisplay;


      //GdkWindow *gdk_window = gtk_widget_get_window(widget);

//      GdkCursor *cursor = NULL;
//      if (edge & RESIZE_LEFT || edge & RESIZE_RIGHT)
//         cursor = gdk_cursor_new_for_display(display, GDK_SB_H_DOUBLE_ARROW);
//      else if (edge & RESIZE_TOP || edge & RESIZE_BOTTOM)
//         cursor = gdk_cursor_new_for_display(display, GDK_SB_V_DOUBLE_ARROW);

      GdkCursorType cursor_type = GDK_ARROW;

      switch(ecursor)
      {
         case e_cursor_system: cursor_type = GDK_ARROW; break;
         case e_cursor_arrow: cursor_type = GDK_ARROW; break;
         case e_cursor_hand: cursor_type = GDK_HAND1; break;
         case e_cursor_text_select: cursor_type =GDK_XTERM; break;
         case e_cursor_size_top_left: cursor_type = GDK_TOP_LEFT_CORNER; break;
         case e_cursor_size_top: cursor_type = GDK_SB_UP_ARROW; break;
         case e_cursor_size_top_right: cursor_type = GDK_TOP_RIGHT_CORNER; break;
         case e_cursor_size_right: cursor_type = GDK_SB_RIGHT_ARROW; break;
         case e_cursor_size_bottom_right: cursor_type = GDK_BOTTOM_RIGHT_CORNER; break;
         case e_cursor_size_bottom: cursor_type = GDK_SB_DOWN_ARROW; break;
         case e_cursor_size_bottom_left: cursor_type = GDK_BOTTOM_LEFT_CORNER; break;
         case e_cursor_size_left: cursor_type = GDK_SB_LEFT_ARROW; break;
         case e_cursor_size_vertical: cursor_type = GDK_SB_V_DOUBLE_ARROW; break;
         case e_cursor_size_horizontal: cursor_type = GDK_SB_H_DOUBLE_ARROW; break;
         case e_cursor_move: cursor_type = GDK_HAND2; break;
         case e_cursor_wait: cursor_type = GDK_WATCH; break;
         case e_cursor_wait_arrow: cursor_type = GDK_WATCH; break;
         default:
            break;
      }

      if(m_pgdkcursor)
      {

         g_object_unref(m_pgdkcursor);

      }

      GdkDisplay *display = gdk_display_get_default();


      m_pgdkcursor = gdk_cursor_new_for_display(display, cursor_type);

      //information() << "_load_default_cursor cursor_name : " << cursor_name;

      // auto pwlcursortheme = wl_cursor_theme_load(NULL, 32, pwaylanddisplay->m_pwlshm);
      //
      // information() << "_load_default_cursor pwlcursortheme : " << (::iptr) pwlcursortheme;
      //
      // auto pwlcursor = wl_cursor_theme_get_cursor(pwlcursortheme, cursor_name);
      //
      // information() << "_load_default_cursor pwlcursor : " << (::iptr) pwlcursor;
      //
      // m_pwlcursor = pwlcursor;
      // m_pwlcursorimage = m_pwlcursor->images[0];
      // m_waylandbuffer.m_pwlbuffer = wl_cursor_image_get_buffer(m_pwlcursorimage);
      //
      // information() << "_load_default_cursor m_pwlbuffer : " << (::iptr) m_waylandbuffer.m_pwlbuffer;
      // m_waylandbuffer.m_size.cx() = m_pwlcursor->images[0]->width;
      // m_waylandbuffer.m_size.cy() = m_pwlcursor->images[0]->height;
      // information() << "_load_default_cursor size : " << m_waylandbuffer.m_size;
      //
      // m_szHotspotOffset.cx() = m_pwlcursor->images[0]->hotspot_x;
      // m_szHotspotOffset.cy() = m_pwlcursor->images[0]->hotspot_y;

      //information() << "_load_default_cursor hotspot : " << m_szHotspotOffset;

      //m_pwlbuffer

      //iCursor = ::x11::get_default_system_cursor_glyph(ecursor);
//
//      if(iCursor == 0)
//      {
//
//         return ::error_failed;
//
//      }
//
////      if(ecursor == e_cursor_size_top_left)
////      {
////
////         iCursor = XC_top_left_corner;
////
////      }
////      else if(ecursor == e_cursor_size_top_right)
////      {
////
////         iCursor = XC_top_right_corner;
////
////      }
////      else if(ecursor == e_cursor_size_top)
////      {
////
////         iCursor = XC_top_side;
////
////      }
////      else if(ecursor == e_cursor_size_right)
////      {
////
////         iCursor = XC_right_side;
////
////      }
////      else if(ecursor == e_cursor_size_left)
////      {
////
////         iCursor = XC_left_side;
////
////      }
////      else if(ecursor == e_cursor_size_bottom)
////      {
////
////         iCursor = XC_bottom_side;
////
////      }
////      else if(ecursor == e_cursor_size_bottom_left)
////      {
////
////         iCursor = XC_bottom_left_corner;
////
////      }
////      else if(ecursor == e_cursor_size_bottom_right)
////      {
////
////         iCursor = XC_bottom_right_corner;
////
////      }
////      else if(ecursor == e_cursor_arrow)
////      {
////
////         iCursor = XC_arrow;
////
////      }
////
////      if(iCursor < 0)
////      {
////
////         return ::error_failed;
////
////      }
//
//      synchronous_lock sl(user_synchronization());
//
//      windowing_output_debug_string("::x11_GetWindowRect 1");
//
//      auto psystem = system();
//
//      auto psession = psystem->session()->m_paurasession;
//
//      auto puser = psession->user();
//
//      auto pwindowing = puser->windowing();
//
//      auto pdisplay = pwindowing->display();
//
//      auto px11display = (::windowing_gtk3::display *) pwindowing->display()->m_pDisplay;
//
//      //display_lock lock(px11display->Display());
//
//      auto cursor = XCreateFontCursor(px11display->Display(), iCursor);
//
//      if(!cursor)
//      {
//
//         return error_failed;
//
//      }
//
//      m_cursor = cursor;

      return ::success;

   }


} // namespace windowing_gtk3




