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
#include "acme/platform/node.h"
#include "acme/prototype/geometry2d/_text_stream.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/graphics/image/image.h"
#include "windowing_system_x11/display_lock.h"

//#define VERI_BASIC_TEST


namespace windowing_x11
{


   buffer::buffer()
   {

      m_bXShmPutImagePending = false;

      m_bUseXShmIfAvailable = true;

      m_bXShm = false;
      m_bXShmChecked = false;

      m_gc = nullptr;

      m_pximage = nullptr;

      //m_pimage = nullptr;

      m_iGoodStride = 0;

   }


   buffer::~buffer()
   {

//      _destroy_shared_memory();
//
      destroy_os_buffer();

   }


   void buffer::_map_shared_memory(const ::size_i32 & size)
   {

      if(!m_bUseXShmIfAvailable)
      {

         return;

      }

      map_shared_memory(size.cx() * size.cy() * 4);

   }


//   void buffer::_destroy_shared_memory()
//   {
//
//      if (m_shmaddr)
//      {
//
//         shmdt(m_shmaddr);
//
//         m_shmaddr = nullptr;
//
//      }
//
//      if (m_shmid >= 0)
//      {
//
//         shmctl(m_shmid, IPC_RMID, NULL);
//
//         m_shmid = -1;
//
//      }
//
//   }


   ::windowing_x11::window * buffer::x11_window()
   {

      return (::windowing_x11::window *) (m_pwindow ? m_pwindow->m_pWindow4 : nullptr);

   }


   void buffer::initialize_graphics_graphics(::windowing::window * pimpl)
   {

      double_buffer::initialize_graphics_graphics(pimpl);

      //synchronous_lock synchronouslock(user_synchronization());

      ::x11::display_lock displaylock(x11_window()->x11_display()->Display());

      XGCValues gcvalues = {};

      m_gc = XCreateGC(x11_window()->Display(), x11_window()->Window(), 0, &gcvalues);

   }


   void buffer::destroy()
   {

      if (!x11_window())
      {

         throw ::exception(error_wrong_state);

      }

      //synchronous_lock synchronouslock(user_synchronization());

      ::x11::display_lock displaylock(x11_window()->x11_display()->Display());

      if (m_gc != nullptr)
      {

         XFreeGC(x11_window()->Display(), m_gc);

         m_gc = nullptr;

      }

   }


   bool buffer::update_buffer(::graphics::buffer_item * pbufferitem)
   {

      debug() << "x11 buffer::update_buffer";

      auto pwindowing = m_pimpl->m_puserinteraction->windowing();

      auto pdisplay = pwindowing->display();

      auto sizeLargeInternalBitmap = pdisplay->get_monitor_union_rectangle().size();

      if (pbufferitem->m_size.cx() > sizeLargeInternalBitmap.cx())
      {

         sizeLargeInternalBitmap.cx() = pbufferitem->m_size.cx();

      }

      if (pbufferitem->m_size.cy() > sizeLargeInternalBitmap.cy())
      {

         sizeLargeInternalBitmap.cy() = pbufferitem->m_size.cy();

      }

      if (pbufferitem->m_sizeInternal.cx() > sizeLargeInternalBitmap.cx())
      {

         sizeLargeInternalBitmap.cx() = pbufferitem->m_sizeInternal.cx();

      }

      if (pbufferitem->m_sizeInternal.cy() > sizeLargeInternalBitmap.cy())
      {

         sizeLargeInternalBitmap.cy() = pbufferitem->m_sizeInternal.cy();

      }

      if (pbufferitem->m_sizeInternal.cx() < sizeLargeInternalBitmap.cx()
          || pbufferitem->m_sizeInternal.cy() < sizeLargeInternalBitmap.cy())
      {

         _map_shared_memory(sizeLargeInternalBitmap);

         if (m_shmaddr)
         {

            pbufferitem->m_sizeInternal = sizeLargeInternalBitmap;

         }

      }

      debug() << "x11 buffer::update_buffer sizeLargeInternalBitmap : " << sizeLargeInternalBitmap;

      return ::graphics::double_buffer::update_buffer(pbufferitem);

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
//   //      m_pdc = ___new device_context();
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
//         if(m_mem.get_data() == (unsigned char *) m_pimage->data)
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


//   bool buffer::create_os_buffer(::image::image *pimage)
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


//   void buffer::destroy_os_buffer(::image::image *pimage)
//   {
//
//      if(m_pimage != nullptr)
//      {
//
//         if((unsigned char *) m_pimage->data == (unsigned char *) pimage->get_data())
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

      information() << "x11 buffer::update_screen";

      if (m_pimpl == nullptr)
      {

         warningf("windowing_x11::buffer::update_screen !m_pimpl!!");

         return false;

      }

      if (!m_pimpl->m_pwindow)
      {

         warningf("windowing_x11::buffer::update_screen !m_pimpl->m_pwindow!!");

         return false;

      }

      if (!m_pimpl->m_puserinteraction->is_window_screen_visible())
      {

         information() << "windowing_x11::buffer::update_screen XPutImage not called. Ui is not visible.";

         return false;

      }

      if (!m_pwindow)
      {

         warningf("windowing_x11::buffer::update_screen !m_pwindow!");

         return false;

      }

      //synchronous_lock synchronouslock(user_synchronization());

      ::x11::display_lock displayLock(x11_window()->x11_display()->Display());

      return _update_screen_lesser_lock();

   }


   bool buffer::_update_screen_lesser_lock()
   {

      _synchronous_lock slGraphics(synchronization());

      auto pitem = get_screen_item();

      slGraphics.unlock();

      _synchronous_lock slImage(pitem->m_pmutex);

      return _update_screen_unlocked(pitem);

   }


   bool buffer::_update_screen_unlocked(::graphics::buffer_item * pitem)
   {

      debug() << "x11 buffer::_update_screen_unlocked";

      auto sizeBitBlitting = pitem->m_size;

      if (sizeBitBlitting.is_empty())
      {

         return false;

      }

      debug() << "x11 buffer::_update_screen_unlocked sizeBitBlitting : " << sizeBitBlitting;

      auto & pimage = pitem->m_pimage2;

      pimage->map();

//      try
//      {
//
//         x11_window()->strict_set_window_position_unlocked();
//
//      }
//      catch (...)
//      {
//
//      }

      int iWindowDepth = x11_window()->m_iDepth;

      if (m_bUseXShmIfAvailable)
      {

         debug() << "x11 buffer::_update_screen_unlocked m_bUseXShmIfAvailable";

         if (!m_bXShmChecked)
         {

            //m_bXShm = XShmQueryExtension(x11_window()->Display());

            m_bXShm = false;

            m_bXShmChecked = true;

         }

      }

      if (m_bXShm && m_shmid >= 0 && m_shmaddr)
      {

         if (!m_pximage
             || m_pximage->width != pitem->m_sizeInternal.cx()
             || m_pximage->height != pitem->m_sizeInternal.cy())
         {

            if (m_pximage)
            {

               XShmDetach(x11_window()->Display(), &m_xshmsegmentinfo);

               m_pximage->data = nullptr;

               XDestroyImage(m_pximage);

            }

            m_pximage = XShmCreateImage(
               x11_window()->Display(),
               x11_window()->Visual(),
               iWindowDepth,
               ZPixmap,
               NULL,
               &m_xshmsegmentinfo,
               pitem->m_sizeInternal.cx(),
               pitem->m_sizeInternal.cy());

            pitem->m_iScan = pitem->m_sizeInternal.cx() * 4;

            m_xshmsegmentinfo.shmid = m_shmid;

            m_xshmsegmentinfo.shmaddr = (char *) m_shmaddr;

            m_pximage->data = m_xshmsegmentinfo.shmaddr;

            m_xshmsegmentinfo.readOnly = False;

            XShmAttach(x11_window()->Display(), &m_xshmsegmentinfo);

            information() << "x11 buffer::_update_screen_unlocked Created SHM!!";

         }

      }
      else
      {

         if (!m_pximage
             || m_pximage->width != sizeBitBlitting.cx()
             || m_pximage->height != sizeBitBlitting.cy()
             || m_pximage->data != (char *) pimage->get_data())
         {

            if (m_pximage)
            {

               m_pximage->data = nullptr;

               XDestroyImage(m_pximage);

            }

            m_pximage =
               XCreateImage(
                  x11_window()->Display(),
                  x11_window()->Visual(),
                  iWindowDepth,
                  ZPixmap,
                  0,
                  (char *) pimage->get_data(),
                  sizeBitBlitting.cx(),
                  sizeBitBlitting.cy(),
                  sizeof(color32_t) * 8,
                  pimage->scan_size());


            information() << "x11 buffer::_update_screen_unlocked Created XImage!!";

         }

      }

      if (!m_pximage || !m_pximage->data || m_pximage->width <= 0 || m_pximage->height <= 0)
      {

         warningf("windowing_x11::buffer::update_screen X11 image null or empty!!");

         return false;

      }

      if (m_gc == nullptr)
      {

         warningf("windowing_x11::buffer::update_screen m_gc nullptr!!");

         return false;

      }

      ::size_i32 sizeDesign = m_pimpl->m_puserinteraction->const_layout().design().size();

      if (sizeDesign != sizeBitBlitting)
      {

         warning() << "What!! Drawn Buffer different from window design size";

      }

      if (sizeBitBlitting.any_gt(pitem->m_sizeInternal))
      {

         warning() << "What!! Drawn Buffer doesn't fit internal buffer (that should be at least same size as the buffer size)";

      }

      try
      {

         bool bChangedPosition = false;

         bool bChangedSize = false;

         if (m_bXShm)
         {

            if (!pitem->m_manualresetevent._wait(200_ms))
            {

               x11_window()->_on_end_paint();

               information() << "XShmCompletionEvent timeout";

               ::pointer<::windowing_x11::window> px11window = m_pimpl->m_pwindow;

               try
               {

                  px11window->strict_set_window_position_unlocked(bChangedPosition, bChangedSize);

               }
               catch (...)
               {

               }

            }

            copy_image32((::image32_t *) m_pximage->data, sizeBitBlitting,
                         pitem->m_iScan, pimage->get_data(), pimage->scan_size());

            pitem->m_manualresetevent.ResetEvent();

            m_sizeLastBitBlitting = sizeBitBlitting;

            x11_window()->m_rectangleXShm = x11_window()->m_pwindow->m_puserinteraction->const_layout().parent_raw_rectangle(::user::e_layout_design);

            m_bXShmPutImagePending = true;

            XShmPutImage(
               x11_window()->Display(),
               x11_window()->Window(),
               m_gc, m_pximage,
               0, 0, 0, 0,
               sizeBitBlitting.cx(),
               sizeBitBlitting.cy(), true);

            information() << "XShmPutImage : " << sizeBitBlitting;

         }
         else
         {

            ::pointer<::windowing_x11::window> px11window = m_pimpl->m_pwindow;

            try
            {

               ::x11::display_lock displayLock(x11_window()->Display());

               px11window->strict_set_window_position_unlocked(bChangedPosition, bChangedSize);

            }
            catch (...)
            {

            }

            m_sizeLastBitBlitting = sizeBitBlitting;

            if(!bChangedSize)
            {

               ::x11::display_lock displayLock(x11_window()->Display());

               XPutImage(
                  x11_window()->Display(),
                  x11_window()->Window(),
                  m_gc, m_pximage,
                  0, 0, 0, 0,
                  sizeBitBlitting.cx(),
                  sizeBitBlitting.cy());

               //information() << "XPutImage : " << sizeBitBlitting;

               //information() << node()->get_callstack();

//            try
//            {
//
//               x11_window()->strict_set_window_position_unlocked();
//
//            }
//            catch (...)
//            {
//
//            }

               //x11_window()->m_pwindow->m_puserinteraction->_set_size(sizeBitBlitting, ::user::e_layout_window);

               x11_window()->_on_end_paint();

               XFlush(x11_window()->Display());

               XSync(x11_window()->Display(), false);

            }

         }

      }
      catch (...)
      {

      }

#ifdef VERI_BASIC_TEST

      XColor xcolour;

      // I guess XParseColor will work here

      xcolour.red = 32000; xcolour.green = 65000; xcolour.blue = 32000;

      xcolour.flags = DoRed | DoGreen | DoBlue;

      XAllocColor(x11_window()->Display(), x11_window()->x11_display()->m_colormap, &xcolour);

      XSetForeground(x11_window()->Display(), m_gc, xcolour.pixel);

      XFillRectangle(x11_window()->Display(), x11_window()->Window(), m_gc, 0, 0, iWidth, iHeight);

      informationf("windowing_x11::buffer::update_screen BASIC_TEST FillRectangle(%d, %d)", iWidth, iHeight);

#endif

      // pximage->data = nullptr;

      // if(m_pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning)
      // {

// //     x11_window()->m_pwindow->m_puserinteraction->_set_size({ iWidth, iHeight }, ::user::e_layout_window);

      // }

      return true;

   }


   bool buffer::on_update_screen(::graphics::buffer_item * pitem)
   {

      throw ("use update_window(void)");

      return true;

   }


   bool buffer::_on_begin_draw(::graphics::buffer_item * pbufferitem)
   {

//      auto pbufferitem = get_buffer_item();
//
//      buffer_size_and_position(pbufferitem);

      auto pimageBuffer = pbufferitem->m_pimage2;

      if (pimageBuffer->m_size != pbufferitem->m_size)
      {

         if(!update_buffer(pbufferitem))
         {

            information() << "::windowing_x11::buffer::_on_begin_draw !update_buffer";

            return false;

         }

      }

      debug() << "going to call double_buffer::_on_begin_draw";

      if(!double_buffer::_on_begin_draw(pbufferitem))
      {

         return false;

      }

      return true;

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




