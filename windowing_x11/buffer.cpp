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
#include "aura/user/user/interaction_impl.h"
#include "aura/graphics/image/image.h"
#include "aura_posix/x11/display_lock.h"

#include <sys/ipc.h>
#include <sys/shm.h>
//#define VERI_BASIC_TEST


namespace windowing_x11
{


   buffer::buffer()
   {


      //m_bXShm = false;
      //m_bXShmChecked = false;

      m_gc = nullptr;

      //m_pximage = nullptr;
      //m_shmid = shmget(IPC_PRIVATE,
                       //1920 * 1080 * 4 * 4 * 4, IPC_CREAT | 0777);      /* kernel id */
      //m_shmaddr = (char *) shmat(m_shmid, 0, 0);   /* address in client */

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

      if (!x11_window())
      {

         throw ::exception(error_wrong_state);

      }

      synchronous_lock synchronouslock(user_synchronization());

      display_lock displaylock(x11_window()->x11_display()->Display());

      if (m_gc != nullptr)
      {

         XFreeGC(x11_window()->Display(), m_gc);

         m_gc = nullptr;

      }

      //return ::success;

   }


   bool buffer::update_buffer(::graphics::buffer_item * pbufferitem)
   {

      return ::graphics::double_buffer::update_buffer(pbufferitem);

////      if (is_single_buffer_mode() && m_ptaskUpdateScreen)
////      {
////
////         m_ptaskUpdateScreen->set_finish();
////
////         m_ptaskUpdateScreen.release();
////
////      }
////      else if (!is_single_buffer_mode() && !m_ptaskUpdateScreen)
////      {
////
////         m_ptaskUpdateScreen = fork([this]()
////                                    {
////
////                                       update_screen_task();
////
////                                    });
////
////      }
//
////      if (get_hwnd() == nullptr || ::is_null(m_pimpl))
////      {
////
////         return false;
////
////      }
//
//      if (::is_null(m_pimpl))
//      {
//
//         return false;
//
//      }
//
////      auto & pparticleData = pbufferitem->m_pparticleData;
////
////      if (!pparticleData)
////      {
////
////         pparticleData = __create_new < layered_window_buffer >();
////
////      }
////
////      ::pointer < layered_window_buffer > playeredwindowbuffer = pparticleData;
////
////      if (pbufferitem->m_size == playeredwindowbuffer->m_pixmap.size())
////      {
////
////         return false;
////
////      }
//
//      //::image32_t * pimage32 = (::image32_t *) m_shmaddr;
//
//      //int iScan = -1;
//
////      auto pwindowing = m_pimpl->m_puserinteraction->windowing();
////
////      auto pdisplay = pwindowing->display();
////
////      auto sizeLargeInternalBitmap = pdisplay->get_monitor_union_size();
////
////      if (pbufferitem->m_size.cx() > sizeLargeInternalBitmap.cx())
////      {
////
////         sizeLargeInternalBitmap.cx() = pbufferitem->m_size.cx();
////
////      }
////
////      if (pbufferitem->m_size.cy() > sizeLargeInternalBitmap.cy())
////      {
////
////         sizeLargeInternalBitmap.cy() = pbufferitem->m_size.cy();
////
////      }
////
////      if (playeredwindowbuffer->m_pixmap.m_sizeRaw.cx() > sizeLargeInternalBitmap.cx())
////      {
////
////         sizeLargeInternalBitmap.cx() = playeredwindowbuffer->m_pixmap.m_sizeRaw.cx();
////
////      }
////
////      if (playeredwindowbuffer->m_pixmap.m_sizeRaw.cy() > sizeLargeInternalBitmap.cy())
////      {
////
////         sizeLargeInternalBitmap.cy() = playeredwindowbuffer->m_pixmap.m_sizeRaw.cy();
////
////      }
////
////      if (playeredwindowbuffer->m_pixmap.m_sizeRaw.cx() < sizeLargeInternalBitmap.cx()
////          || playeredwindowbuffer->m_pixmap.m_sizeRaw.cy() < sizeLargeInternalBitmap.cy())
////      {
////
////         HBITMAP hbitmap = ::windows::create_windows_dib(sizeLargeInternalBitmap, &iScan, &pimage32);
////
////         if (hbitmap == nullptr || pimage32 == nullptr || iScan == 0)
////         {
////
////            if (hbitmap != nullptr)
////            {
////
////               ::DeleteObject(hbitmap);
////
////            }
////
////            return false;
////
////         }
//
////      if (m_pixmap.m_sizeRaw.cx() != pbufferitem->m_size.cx()
////          || m_pixmap.m_sizeRaw.cy() != pbufferitem->m_size.cy())
////      {
////
////         m_pixmap.init(pbufferitem->m_size, pimage32, pbufferitem->m_size.cx() * 4);
////
//////         if (playeredwindowbuffer->m_hbitmap != nullptr)
//////         {
//////
//////            ::DeleteObject(playeredwindowbuffer->m_hbitmap);
//////
//////         }
////
//////         playeredwindowbuffer->m_hbitmap = hbitmap;
//////
//////         bool bCreatedCompatibleDC = false;
//////
//////         if (playeredwindowbuffer->m_hdc == nullptr)
//////         {
//////
//////            playeredwindowbuffer->m_hdc = ::CreateCompatibleDC(nullptr);
//////
//////            bCreatedCompatibleDC = true;
//////
//////         }
//////
//////         if (playeredwindowbuffer->m_hdc == nullptr)
//////         {
//////
//////            destroy_buffer();
//////
//////            throw ::exception(error_null_pointer);
//////
//////         }
//////
//////         HBITMAP hbitmapPrevious = (HBITMAP) ::SelectObject(playeredwindowbuffer->m_hdc, playeredwindowbuffer->m_hbitmap);
//////
//////         if (bCreatedCompatibleDC)
//////         {
//////
//////            playeredwindowbuffer->m_hbitmapOld = hbitmapPrevious;
//////
//////         }
//////
//////      }
////
////         //playeredwindowbuffer->m_pixmap.m_size = pbufferitem->m_size;
////         m_pixmap.m_size = pbufferitem->m_size;
//
////         if (pbufferitem->m_pimage2->host(&m_pixmap))
////         {
////
////            m_bDibIsHostingBuffer = true;
////
////         } else
////         {
//
//            try
//            {
//
//               //pbufferitem->m_pimage2->create(m_pixmap.m_sizeRaw);
//               pbufferitem->m_pimage2->create(pbufferitem->m_size);
//
//            }
//            catch (...)
//            {
//
//               return false;
//
//            }
//
//            m_bDibIsHostingBuffer = false;
////
////         }
////
////      }
////
//      return true;

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

      if (m_pimpl == nullptr)
      {

         warning("windowing_x11::buffer::update_screen !m_pimpl!!");

         return false;

      }

      if (!m_pimpl->m_pwindow)
      {

         warning("windowing_x11::buffer::update_screen !m_pimpl->m_pwindow!!");

         return false;

      }

      if (!m_pimpl->m_puserinteraction->is_window_screen_visible())
      {

         information() << "windowing_x11::buffer::update_screen XPutImage not called. Ui is not visible.";

         return false;

      }

      if (!m_pwindow)
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

      int iWidth = pitem->m_size.cx();

      int iHeight = pitem->m_size.cy();

      if (iWidth <= 0 || iHeight <= 0)
      {

         return false;

      }

      auto & pimage = pitem->m_pimage2;

      pimage->map();

      //XImage * pximage = nullptr;

      try
      {

         x11_window()->strict_set_window_position_unlocked();

         //x11_window()->_window_request_presentation_unlocked();

      }
      catch (...)
      {

      }

//      static int s_i =0;
//
//      s_i++;
//
//      if(s_i > 20)
//      {
//
//         return;
//
//      }

      int iDefaultDepth = DefaultDepth(x11_window()->Display(), x11_window()->Screen());

      int iWindowDepth = x11_window()->m_iDepth;

//      if (!m_bXShmChecked)
//      {
//
//         m_bXShm = XShmQueryExtension(x11_window()->Display());
////
////         XShmAttach(x11_window()->Display(), &m_xshmsegmentinfo);
////         m_bXShm = true;
//
//         m_bXShmChecked = true;
//
//      }

      //if(m_bXShm)
      //{

//      if (m_bXShm)
//      {
//
//         if (!m_pximage
//             || m_pximage->width != iWidth
//             || m_pximage->height != iHeight
//             || m_pximage->data != (char *) pimage->get_data())
//         {
//
//
//            if (m_pximage)
//            {
//               XShmDetach(x11_window()->Display(), &m_xshmsegmentinfo);
//               m_pximage->data = nullptr;
//               XDestroyImage(m_pximage);
//
//            }
//
//            m_pximage = XShmCreateImage(
//               x11_window()->Display(),
//               x11_window()->Visual(),
//               iWindowDepth,
//               ZPixmap,
//               //0,
//               NULL,
//               &m_xshmsegmentinfo,
//               iWidth, iHeight);
//
//            //assert(image);
//
//            m_xshmsegmentinfo.shmid = m_shmid;
//
//            //assert(xshmseg.shmid != -1);
//            m_xshmsegmentinfo.shmaddr = m_pximage->data = m_shmaddr;
//
////            copy_image32((const ::image32_t *)m_pximage->data,
////                         )
//
//            m_xshmsegmentinfo.readOnly = False;
//
//            XShmAttach(x11_window()->Display(), &m_xshmsegmentinfo);
//            //iWidth,
//            //iHeight);
//
//            //X
//         } else
//         {
//
//            //printf("XShmImage optimized");
//
//         }
//      } else
//      {
//
//         if (!m_pximage
//             || m_pximage->width != iWidth
//             || m_pximage->height != iHeight
//             || m_pximage->data != (char *) pimage->get_data())
//         {
//
//
//            if (m_pximage)
//            {
//
//               m_pximage->data = nullptr;
//
//               XDestroyImage(m_pximage);
//
//            }

           XImage * pximage =
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

         //}


      //}
      ///}
//      pximage =
////              XCreateImage(
////                      x11_window()->Display(),
////                      x11_window()->Visual(),
////                      iWindowDepth,
////                      ZPixmap,
////                      0,
////                      (char *) pimage->get_data(),
////                      iWidth,
////                      iHeight,
////                      sizeof(color32_t) * 8,
////                      pimage->scan_size());
//              XShmCreateImage(
//                      x11_window()->Display(),
//                      x11_window()->Visual(),
//                      iWindowDepth,
//                      ZPixmap,
//                      0,
//                      (char *) pimage->get_data(),
//                      &m_xshmsegmentinfo,
//
//                      iWidth,
//                      iHeight;

      if (!pximage || pximage->width <= 0 || pximage->height <= 0)
      {

         warning("windowing_x11::buffer::update_screen X11 image null or empty!!");

         return false;

      }

      if (m_gc == nullptr)
      {

         warning("windowing_x11::buffer::update_screen m_gc nullptr!!");

         return false;

      }

//::point_i32 p1 = m_pimpl->m_puserinteraction->const_layout().design().origin();
      ::size_i32 s1 = m_pimpl->m_puserinteraction->const_layout().design().size();

      if (s1.

         cx()

          != iWidth || s1.

         cy()

                       != iHeight)
      {

         printf("What!!");
         fflush(stdout);

      }
//      if (
//         m_bXShm && m_pximage
//         && m_pximage->data && !m_bDibIsHostingBuffer)
//      {
//         copy_image32((::image32_t *) m_pximage->data, ::size_i32{
//                         iWidth, iHeight},
//                      iWidth * 4,
//                      pimage->
//
//                         get_data(),
//                      pimage
//
//                         ->
//
//                            scan_size()
//
//         );
//
//      }


      try
      {

//         if (m_bXShm)
//         {
//
//            m_bXShmComplete = false;
//
//            m_interlockedXShmPutImage++;
//
//            XShmPutImage(x11_window()->Display(), x11_window()->Window(),
//                         m_gc, m_pximage, 0, 0, 0, 0, iWidth, iHeight, true);
//
////            while(!m_pimpl->m_pwindow->presentation_complete())
////            {
////
////               preempt(2_ms);
////
////            }
//
//            int iXShmEventBase = XShmGetEventBase(x11_window()->Display());
//
//            int iXShmEvent = iXShmEventBase + ShmCompletion;
//
//            while (true)
//            {
//
//               XEvent e;
//
//               if (XCheckTypedEvent(x11_window()->Display(), iXShmEvent, &e))
//               {
//
//                  auto pcompletionevent = (XShmCompletionEvent *) &e;
//
//                  if (pcompletionevent->drawable == x11_window()->Window())
//                  {
//
//                     printf("found window for XShmCompletionEvent");
//
//                  } else
//                  {
//
//                     printf("No matching window for XShmCompletionEvent");
//
//                  }
//
//                  break;
//
//               }
//
//               preempt(2_ms);
//
//            }
//
//            if (m_pximage)
//            {
//               XShmDetach(x11_window()->Display(), &m_xshmsegmentinfo);
//               m_pximage->data = nullptr;
//               XDestroyImage(m_pximage);
//               m_pximage = nullptr;
//            }
//
//
//         } else
//         {

            XPutImage(x11_window()

                         ->

                            Display(), x11_window()

                         ->

                            Window(), m_gc, pximage,

                      0, 0, 0, 0, iWidth, iHeight);

            XFlush(x11_window()

                      ->

                         Display());

            //);

            XSync(x11_window()

                     ->

                        Display(),

                  false);


//         }


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
      catch (...)
      {

      }





//      pximage->data = nullptr;

//if(m_pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning)
//{



      x11_window()->m_puserinteractionimpl->m_puserinteraction->_set_size({
                                                                             iWidth, iHeight},
                                                                          ::user::e_layout_window);

//}

      return true;

   }


   bool buffer::on_update_screen(::graphics::buffer_item * pitem)
   {

      throw ("use update_window(void)");

      return true;

   }


   ::graphics::buffer_item * buffer::on_begin_draw()
   {

      auto pbufferitem = get_buffer_item();

      buffer_size_and_position(pbufferitem);

      auto pimageBuffer = pbufferitem->m_pimage2;

      if (pimageBuffer->m_size != pbufferitem->m_size)
      {

         update_buffer(pbufferitem);

      }

      return double_buffer::on_begin_draw();

   }


//   bool buffer::presentation_complete()
//   {
//
//      if (x11_window()->m_interlockedXShmPutImage <= 0)
//      {
//
//         return true;
//
//      }
//
//      return x11_window()->m_bXShmComplete;
//
//   }


} // namespace windowing_x11




