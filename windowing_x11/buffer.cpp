// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing_x11.h"
#include "buffer.h"
#include "window.h"
#include "display.h"
#include "windowing.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/graphics/image/image.h"
#include "aura_posix/x11/display_lock.h"


//#define VERI_BASIC_TEST


namespace windowing_x11
{


   buffer::buffer()
   {

      m_gc = nullptr;

//      m_pimage = nullptr;

      m_iGoodStride = 0;

   }


   buffer::~buffer()
   {

      destroy_os_buffer();

   }


   ::windowing_x11::window * buffer::x11_window()
   {

      return (::windowing_x11::window *) (m_pwindow ? m_pwindow->m_pWindow4 : nullptr);

   }


   void buffer::initialize_graphics_graphics(::user::interaction_impl * pimpl)
   {

      //auto estatus =
      //
      double_buffer::initialize_graphics_graphics(pimpl);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_window()->x11_display()->Display());

      XGCValues gcvalues = {};

      m_gc = XCreateGC(x11_window()->Display(), x11_window()->Window(), 0, &gcvalues);

      //return estatus;

   }


   void buffer::destroy()
   {

      if(!x11_window())
      {

         throw ::exception(error_wrong_state);

      }

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_window()->x11_display()->Display());

      if(m_gc != nullptr)
      {

         XFreeGC(x11_window()->Display(), m_gc);

         m_gc = nullptr;

      }

      //return ::success;

   }


   bool buffer::create_os_buffer(const ::size_i32 & size, int iStrideParam)
   {

//      synchronous_lock sl(synchronization());
//
//      destroy_os_buffer();
//
//      if(size.is_empty())
//      {
//
//         return false;
//
//      }
//
//      //m_mem.m_bAligned = true;
//
//      m_mem.set_size((m_iGoodStride * size.cy()) * sizeof(color32_t));
//
//      m_pixmap.init(size, (color32_t *) m_mem.get_data(), m_iGoodStride);
//
//      //::acme::del(m_pdc);
//
//      {
//
//         xdisplay d(m_oswindow->display());
//
//         m_pimage = XCreateImage(d, m_oswindow->visual(), m_oswindow->m_iDepth, ZPixmap, 0, (char *) m_mem->get_data(), m_pixmap->width(), m_pixmap->height(), sizeof(color32_t) * 8, m_iGoodStride);
//
//         XGCValues gcvalues;
//
//   //      m_pdc = memory_new device_context();
//
//         m_gc = XCreateGC(d, m_oswindow->window(), 0, &gcvalues);
//
//      }
//
//      //m_pdc->m_pdisplay = m_pimpl->m_oswindow->display();
//
      return true;

   }



   void buffer::destroy_os_buffer()
   {

//      synchronous_lock sl(synchronization());
//
//      xdisplay d(m_oswindow->display());
//
//      //if(m_pdc != nullptr)
//      {
//
//         //if(m_pdc->m_gc != nullptr)
//         if(m_gc != nullptr)
//         {
//
//            XFreeGC(d, m_gc);
//
//            m_gc = nullptr;
//
//         }
//
//         //delete m_pdc;
//
//         //m_pdc = nullptr;
//
//      }
//
//      if(m_pimage != nullptr)
//      {
//
//         if(m_mem.get_data() == (::u8 *) m_pimage->data)
//         {
//
//            m_pimage->data = nullptr;
//
//         }
//
//         XDestroyImage(m_pimage);
//
//         m_pimage = nullptr;
//
//      }
//
   }


//   bool buffer::create_os_buffer(::image * pimage)
//   {
//
//      //synchronous_lock sl(synchronization());
//
////      if(!pimage)
////      {
////
////         return false;
////
////      }
////
////      m_pixmap.init(pimage->size(), (color32_t *) pimage->get_data(), pimage->scan_size());
////
////      {
////
////         //xdisplay d(m_oswindow->display());
////
////         m_pimage =
////            XCreateImage(
////               m_oswindow->display(),
////               m_oswindow->visual(),
////               m_oswindow->m_iDepth,
////               ZPixmap,
////               0,
////               (char *) pimage->get_data(),
////               pimage->width(),
////               pimage->height(),
////               sizeof(color32_t) * 8,
////               pimage->scan_size());
////
////      }
//
//      return true;
//
//   }


//   void buffer::destroy_os_buffer(::image * pimage)
//   {
//
//      if(m_pimage != nullptr)
//      {
//
//         if((::u8 *) m_pimage->data == (::u8 *) pimage->get_data())
//         {
//
//            m_pimage->data = nullptr;
//
//         }
//
//         XDestroyImage(m_pimage);
//
//         m_pimage = nullptr;
//
//      }
//
//   }
//

   bool buffer::buffer_lock_round_swap_key_buffers()
   {

      bool bOk1 = double_buffer::buffer_lock_round_swap_key_buffers();

      bool bOk2 = bitmap_source_buffer::buffer_lock_round_swap_key_buffers();

      return bOk1 && bOk2;

   }


   bool buffer::update_screen()
   {

      //information("windowing_x11::buffer::update_screen");

      if(m_pimpl == nullptr)
      {

         warning("windowing_x11::buffer::update_screen !m_pimpl!!");

         return false;

      }

      if(!m_pimpl->m_pwindow)
      {

         warning("windowing_x11::buffer::update_screen !m_pimpl->m_pwindow!!");

         return false;

      }

      if(!m_pimpl->m_puserinteraction->is_window_screen_visible())
      {

         information() << "windowing_x11::buffer::update_screen XPutImage not called. Ui is not visible.";

         return false;

      }

      if(!m_pwindow)
      {

         warning("windowing_x11::buffer::update_screen !m_pwindow!");

         return false;

      }

      _synchronous_lock synchronouslock(user_synchronization());

      display_lock displayLock(x11_window()->x11_display()->Display());

      return _update_screen_lesser_lock();

   }


   bool buffer::_update_screen_lesser_lock()
   {

      _synchronous_lock slGraphics(synchronization());

      auto pitem = get_screen_item();

      _synchronous_lock slImage(pitem->m_pmutex);

      slGraphics.unlock();

      return _update_screen_unlocked();

   }


   bool buffer::_update_screen_unlocked()
   {

      auto pitem = get_screen_item();

      auto & pimage = pitem->m_pimage;

      pimage->map();

      XImage * pximage = nullptr;

      int iWidth = pitem->m_size.cx();

      int iHeight = pitem->m_size.cy();

      int iDefaultDepth = DefaultDepth(x11_window()->Display(), x11_window()->Screen());

      int iWindowDepth = x11_window()->m_iDepth;

      pximage =
              XCreateImage(
                      x11_window()->Display(),
                      x11_window()->Visual(),
                      iWindowDepth,
                      ZPixmap,
                      0,
                      (char *) pimage->get_data(),
                      iWidth,
                      iHeight,
                      sizeof(color32_t) * 8,
                      pimage->scan_size());

      if(!pximage || pximage->width <= 0 || pximage->height <= 0)
      {

         warning("windowing_x11::buffer::update_screen X11 image null or empty!!");

         return false;

      }

      if(m_gc == nullptr)
      {

         warning("windowing_x11::buffer::update_screen m_gc nullptr!!");

         return false;

      }

      try
      {

         XPutImage(x11_window()->Display(), x11_window()->Window(), m_gc, pximage, 0, 0, 0, 0, iWidth, iHeight);

#ifdef VERI_BASIC_TEST

         XColor xcolour;

         // I guess XParseColor will work here

         xcolour.red = 32000; xcolour.green = 65000; xcolour.blue = 32000;

         xcolour.flags = DoRed | DoGreen | DoBlue;

         XAllocColor(x11_window()->Display(), x11_window()->x11_display()->m_colormap, &xcolour);

         XSetForeground(x11_window()->Display(), m_gc, xcolour.pixel);

         XFillRectangle(x11_window()->Display(), x11_window()->Window(), m_gc, 0, 0, iWidth, iHeight);

         information("windowing_x11::buffer::update_screen BASIC_TEST FillRectangle(%d, %d)", iWidth, iHeight);

#endif

      }
      catch(...)
      {

      }

      pximage->data = nullptr;

      XDestroyImage(pximage);

      //if(m_pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning)
      //{

      XFlush(x11_window()->Display());

      XSync(x11_window()->Display(), false);

      //}

      return true;

   }


   bool buffer::on_update_screen(::graphics::buffer_item * pitem)
   {

      throw("use update_window(void)");

      return true;

   }


   ::graphics::buffer_item * buffer::on_begin_draw()
   {

      //int cx = window_size().cx();

      //m_iGoodStride = maximum(m_iGoodStride, cx);

      //bitmap_source_buffer::on_begin_draw();

      return double_buffer::on_begin_draw();

   }


} // namespace windowing_x11




