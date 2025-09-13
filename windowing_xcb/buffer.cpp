// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "buffer.h"
#include "display.h"
#include "window.h"
#include "windowing.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/graphics/image/image.h"
//#include "aura/user/user/interaction_impl.h"

//#define VERI_BASIC_TEST

namespace windowing_xcb
{


   buffer::buffer()
   {

      m_gcontext = 0;

      m_bUseXShmIfAvailable = true;

      m_bShmAttached = false;

      m_bXShmChecked = false;

      m_bXShm = false;
//      m_gc = nullptr;

//      m_pimage = nullptr;

      m_iGoodStride = 0;

   }


   buffer::~buffer()
   {

      destroy_os_buffer();

   }


   ::windowing_xcb::window * buffer::xcb_window()
   {

      return (::windowing_xcb::window *) (m_pwindow ? m_pwindow->m_pWindow4 : nullptr);

   }


   void buffer::initialize_graphics_graphics(::windowing::window * pimpl)
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

      //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      m_pdisplay = xcb_window()->xcb_display();

      m_gcontext = xcb_generate_id(xcb_window()->xcb_connection());

      auto cookie = xcb_create_gc(xcb_window()->xcb_connection(), m_gcontext, xcb_window()->xcb_window(), 0, nullptr);

      //estatus =
      //
      xcb_window()->xcb_display()->_request_check(cookie);

      //return estatus;

   }


   void buffer::destroy()
   {

      if (!xcb_window())
      {

         //return error_failed;

         return;

      }

      //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

//      display_lock displaylock(xcb_window()->xcb_display());

//      if(m_gc != nullptr)
//      {
//
//         XFreeGC(xcb_window()->xcb_connection(), m_gc);
//
//         m_gc = nullptr;
//
//      }

      //return ::success;

   }


   bool buffer::create_os_buffer(const ::int_size & size, int iStrideParam)
   {

//      synchronous_lock sl(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
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

//      synchronous_lock sl(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
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


   void buffer::_map_shared_memory(const ::int_size & size)
   {

      if (!m_bUseXShmIfAvailable)
      {

         return;

      }

      map_shared_memory(size.cx() * size.cy() * 4);

   }


   bool buffer::update_buffer(::graphics::buffer_item * pbufferitem)
   {

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

      return ::graphics::double_buffer::update_buffer(pbufferitem);

   }


//   bool buffer::create_os_buffer(::image::image *pimage)
//   {
//
//      //synchronous_lock sl(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
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

      //informationf("windowing_x11::buffer::update_screen");

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

      //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

//      display_lock displayLock(x11_window()->x11_display()->Display());

      return _update_screen_lesser_lock();

   }


   bool buffer::_update_screen_lesser_lock()
   {

      synchronous_lock slGraphics(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto pitem = get_screen_item();

      synchronous_lock slImage(pitem->m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      slGraphics.unlock();

      return _update_screen_unlocked(pitem);

   }


   bool buffer::query_shm()
   {

      xcb_shm_query_version_reply_t * rep;

      xcb_shm_query_version_cookie_t ck;

      ck = xcb_shm_query_version(m_pdisplay->xcb_connection());

      rep = xcb_shm_query_version_reply(m_pdisplay->xcb_connection(), ck, NULL);

      if (!rep)
      {

         warning() << "Failed to get SHM reply";

         return false;

      }

      warningf("SHM verision %i.%i\n", rep->major_version, rep->minor_version);

      if (rep->shared_pixmaps)
      {

         warningf("Pixmaps are shared\n");

      }

      if (rep->major_version < 1 || rep->major_version == 1 && rep->minor_version == 0)
      {

         return false;

      }

      return true;

   }

   bool buffer::attach_shm()
   {
      //size_t size = w * h * bpp_by_depth(c, depth);
      //int shm_id;

//      shm_id  = shmget(IPC_PRIVATE, size, IPC_CREAT | 0600);
//      if (shm_id == -1) {
//         perror("shmget()");
//         return 0;
//      }
//
//      *addr = shmat(shm_id, 0, 0);
//      if (*addr == (void*)-1) {
//         perror("shmat()");
//         shmctl(shm_id, IPC_RMID, 0);
//         return 0;
//      }

      m_xcbshmseg = xcb_generate_id(m_pdisplay->xcb_connection());

      xcb_void_cookie_t cookie;
      xcb_generic_error_t * err;

      cookie = xcb_shm_attach_checked(m_pdisplay->xcb_connection(), m_xcbshmseg, m_shmid, 0);
      err = xcb_request_check(m_pdisplay->xcb_connection(), cookie);

//      shmctl(shm_id, IPC_RMID, 0);

      if (err)
      {
         warning() << "xcb_shm_attach_checked() failed";
         //free(err);
         return false;
      }

      information() << "xcb_shm_attach_checked succeeded!!";

      return true;

   }


   bool buffer::detach_shm()
   {
      //size_t size = w * h * bpp_by_depth(c, depth);
      //int shm_id;

//      shm_id  = shmget(IPC_PRIVATE, size, IPC_CREAT | 0600);
//      if (shm_id == -1) {
//         perror("shmget()");
//         return 0;
//      }
//
//      *addr = shmat(shm_id, 0, 0);
//      if (*addr == (void*)-1) {
//         perror("shmat()");
//         shmctl(shm_id, IPC_RMID, 0);
//         return 0;
//      }

      //m_xcbshmseg = xcb_generate_id(m_pdisplay->xcb_connection());

      xcb_void_cookie_t cookie;
      xcb_generic_error_t * err;

      cookie = xcb_shm_detach_checked(m_pdisplay->xcb_connection(), m_xcbshmseg);
      err = xcb_request_check(m_pdisplay->xcb_connection(), cookie);

//      shmctl(shm_id, IPC_RMID, 0);

      if (err)
      {
         warning() << "xcb_shm_detach_checked() failed";
         //free(err);
         return false;
      }

      return true;

   }


   bool buffer::_update_screen_unlocked(::graphics::buffer_item * pitem)
   {

      if (m_pimpl == nullptr)
      {

         return false;

      }

      if (!m_pimpl->m_pwindow)
      {

         return false;

      }

      string strType = ::type(m_pimpl->m_puserinteraction).name();

      bool bComboList = strType.case_insensitive_contains("combo_list");

      if (bComboList)
      {

         //informationf("combo_list update_window");

      }

      if (!m_pimpl->m_puserinteraction->is_window_screen_visible())
      {

         //bool bReallyNotVisible = !(m_pimpl->m_puserinteraction->GetStyle() & WS_VISIBLE);

         information() << "XPutImage not called. Ui is not visible.";

         return false;

      }

      if (!m_pwindow)
      {

         return false;

      }

//      if(m_gc == nullptr)
//      {
//
//         return false;
//
//      }



      synchronous_lock slGraphics(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto pbufferitem = get_screen_item();

      synchronous_lock sl(pbufferitem->m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      if (pbufferitem->m_pmutex)
      {

         //information() << "the buffer item has synchronization";

      }
      else
      {

         information() << "the buffer item doesn't have synchronization";

      }


      auto & pimage = pbufferitem->m_pimage2;

      auto sizeBitBlitting = pbufferitem->m_size;

//      if(pimage.nok())
//      {
//
//         return false;
//
//      }
//
//      slGraphics.unlock();
//
//      pimage->map_base();

      //    synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

//      m_memoryImage.set_size(pimage->scan_area_in_bytes());
//
//      m_sizeImage.cx() = pimage->width();
//
//      m_sizeImage.cy() = pimage->height();
//
//      memory_copy(m_memoryImage.data(), pimage->data(), m_memoryImage.size());

      //display_lock displayLock(xcb_window()->xcb_display());

      //xcb_image_t * pximage = (xcb_image_t *)pimage->payload("pximage").long_long;

//      xcb_image_t * pximage;
//
//      //if(!pximage)
//      {
//
//         color32_t colora[8];
//
//         memory_copy(colora, pimage->get_data(), sizeof(colora));
//
//         //int iDefaultDepth = DefaultDepth(xcb_window()->xcb_connection(), xcb_window()->m_iScreen);
//
//         //int iWindowDepth = xcb_window()->m_iDepth;
//
//         pximage =
//            xcb_image_create (pimage->width(),
//                              pimage->height(),
//                              XCB_IMAGE_FORMAT_XY_BITMAP,
//            0,
//            1,
//            32,
//            0,
//                              XCB_IMAGE_ORDER_LSB_FIRST,
//                              XCB_IMAGE_ORDER_LSB_FIRST,
//            nullptr,
//            pimage->width() * pimage->height() * 4,
//                              (uint8_t *) pimage->get_data());
////            xcb_image_create(
////               xcb_window()->xcb_connection(),
////               xcb_window()->Visual(),
////               iWindowDepth,
////               ZPixmap,
////               0,
////               (char *) pimage->get_data(),
////               pimage->width(),
////               pimage->height(),
////               sizeof(color32_t) * 8,
////               pimage->scan_size());
////
//         //pimage->payload("pximage") = (long long) pximage;
//
//      }

      auto pxcbconnection = m_pdisplay->xcb_connection();

      //auto pixmap = m_pdisplay->_xcb_create_pixmap(pimage);

      //printf("pimage (%d, %d, %d)\n", pimage->width(), pimage->height(), pimage->get_pixel(100, 600));

      //if(!pximage || pximage->width <= 0 || pximage->height <= 0)
      //{

      // return false;

      //}

      if (m_bUseXShmIfAvailable && !m_bXShmChecked)
      {

         information() << "m_bUseXShmIfAvailable set!!";

         if (!m_bXShmChecked)
         {

            m_bXShm = query_shm();

            information() << "xcb_shm : " << m_bXShm;

            m_bXShmChecked = true;

         }

      }


      if (m_bXShm && m_shmid >= 0 && m_shmaddr)
      {

         auto sizeInternal = pitem->m_sizeInternal;

         if (m_sizeXcbShm.cx() != sizeInternal.cx()
             || m_sizeXcbShm.cy() != sizeInternal.cy())
            //  || m_pximage->width != pitem->m_sizeInternal.cx()
            //|| m_pximage->height != pitem->m_sizeInternal.cy())
         {

            if (m_bShmAttached)
            {

               detach_shm();

               //m_pximage->data = nullptr;

               //XDestroyImage(m_pximage);

               m_bShmAttached = false;

            }

//            m_pximage = XShmCreateImage(
//               x11_window()->Display(),
//               x11_window()->Visual(),
//               iWindowDepth,
//               ZPixmap,
//               NULL,
//               &m_xshmsegmentinfo,
//               pitem->m_sizeInternal.cx(),
//               pitem->m_sizeInternal.cy());

//            m_xshmsegmentinfo.shmid = m_shmid;
//
//            m_xshmsegmentinfo.shmaddr = (char *) m_shmaddr;
//
//            m_pximage->data = m_xshmsegmentinfo.shmaddr;
//
//            m_xshmsegmentinfo.readOnly = False;

            m_bShmAttached = attach_shm();

            if (m_bShmAttached)
            {

               m_sizeXcbShm = sizeInternal;

               pitem->m_iScan = pitem->m_sizeInternal.cx() * 4;

               if (m_pdisplay->m_iXcbShmCompletionTypeId < 0)
               {
                  m_pdisplay->m_iXcbShmCompletionTypeId = shm_completion_type_id();

               }

            }

//         }

         }

      }

      bool bChangedPosition = false;

      bool bChangedSize = false;

      try
      {

         xcb_window()->strict_set_window_position_unlocked(bChangedPosition, bChangedSize);

      }
      catch (...)
      {

      }

      if (m_bUseXShmIfAvailable && m_bXShm && m_shmaddr)
      {


         try
         {


            if (!pitem->m_manualresethappening._wait(200_ms))
            {

               xcb_window()->_on_end_paint();

               information() << "XShmCompletionEvent timeout";

            }

            copy_image32((::image32_t *) m_shmaddr, sizeBitBlitting,
                         pitem->m_iScan, pimage->get_data(), pimage->scan_size());

            pitem->m_manualresethappening.reset_happening();

            m_sizeLastBitBlitting = sizeBitBlitting;

            //auto pixmap =

            //XGCValues gcvalues = {};

//       auto gc = XCreateGC(m_oswindow->display(), m_oswindow->window(), 0, &gcvalues);

            //int iWidth = m_sizeImage.cx();

            //int iHeight = m_sizeImage.cy();

//            int iWidth = pimage->width();
//
//            int iHeight = pimage->height();
            //if(!bComboList)
            //{
            int xTotalOffsetInBytes = 0;
            //buffer.pixels +
            //buffer.bytes_per_row * y

            auto pxcbwindow = xcb_window();

            auto xcbwindow = pxcbwindow->xcb_window();

//            auto pdata = pimage->data();
//
//            if (::is_null(pdata))
//            {
//
//               return false;
//
//            }

            auto cookie = xcb_shm_put_image_checked(
               pxcbconnection,
               xcbwindow,
               m_gcontext,
               pitem->m_sizeInternal.cx(),
               pitem->m_sizeInternal.cy(),
               0, 0,
               sizeBitBlitting.width(),
               sizeBitBlitting.height(),
               0, 0, 32,
               XCB_IMAGE_FORMAT_Z_PIXMAP,
               TRUE,
               m_xcbshmseg,
               0);

            auto errorp = xcb_request_check(pxcbconnection, cookie);

            if (errorp)
            {

               information() << "error during xcb_shm_put_image";

            }

            xcb_flush(pxcbconnection);

            //XPutImage(xcb_window()->xcb_connection(), xcb_window()->xcb_window(), m_gc, pximage, 0, 0, 0, 0, iWidth, iHeight);

            //}

            //     XFreeGC(m_oswindow->display(), gc);

//         if(bComboList)
//         {
//
//            XColor xcolour;
//
//            // I guess XParseColor will work here
//
//            xcolour.red = 32000;
//
//            xcolour.green = 65000;
//
//            xcolour.blue = 32000;
//
//            xcolour.flags = DoRed | DoGreen | DoBlue;
//
//            XAllocColor(m_oswindow->display(), m_oswindow->m_colormap, &xcolour);
//
//            XSetForeground(m_oswindow->display(), m_gc, xcolour.pixel);
//
//            XFillRectangle(m_oswindow->display(), m_oswindow->window(), m_gc, 0, 0, iWidth, iHeight);
//
//         }

#ifdef VERI_BASIC_TEST

            XColor xcolour;

            // I guess XParseColor will work here

            xcolour.red = 32000; xcolour.green = 65000; xcolour.blue = 32000;

            xcolour.flags = DoRed | DoGreen | DoBlue;

            XAllocColor(m_oswindow->display(), m_oswindow->m_colormap, &xcolour);

            XSetForeground(m_oswindow->display(), m_gc, xcolour.pixel);

            XFillRectangle(m_oswindow->display(), m_oswindow->window(), m_gc, 0, 0, iWidth, iHeight);

#endif

         }
         catch (...)
         {

         }

      }
      else
      {

         try
         {

            //auto pixmap =

            //XGCValues gcvalues = {};

//       auto gc = XCreateGC(m_oswindow->display(), m_oswindow->window(), 0, &gcvalues);

            //int iWidth = m_sizeImage.cx();

            //int iHeight = m_sizeImage.cy();

            int iWidth = pimage->width();

            int iHeight = pimage->height();
            //if(!bComboList)
            //{
            int xTotalOffsetInBytes = 0;
            //buffer.pixels +
            //buffer.bytes_per_row * y

            auto pxcbwindow = xcb_window();

            auto xcbwindow = pxcbwindow->xcb_window();

            auto pdata = pimage->data();

            if (::is_null(pdata))
            {

               return false;

            }

            auto cookie = xcb_put_image_checked(
               pxcbconnection,
               XCB_IMAGE_FORMAT_Z_PIXMAP,
               xcbwindow,
               m_gcontext,
               iWidth,
               iHeight,
               0, 0, 0, 32,
               iWidth * iHeight * 4,
               (uint8_t *) pdata);

            auto errorp = xcb_request_check(pxcbconnection, cookie);
            if (errorp)
            {
               information() << "error during xcb_put_image";
            }

            xcb_flush(pxcbconnection);

            //XPutImage(xcb_window()->xcb_connection(), xcb_window()->xcb_window(), m_gc, pximage, 0, 0, 0, 0, iWidth, iHeight);

            //}

            //     XFreeGC(m_oswindow->display(), gc);

//         if(bComboList)
//         {
//
//            XColor xcolour;
//
//            // I guess XParseColor will work here
//
//            xcolour.red = 32000;
//
//            xcolour.green = 65000;
//
//            xcolour.blue = 32000;
//
//            xcolour.flags = DoRed | DoGreen | DoBlue;
//
//            XAllocColor(m_oswindow->display(), m_oswindow->m_colormap, &xcolour);
//
//            XSetForeground(m_oswindow->display(), m_gc, xcolour.pixel);
//
//            XFillRectangle(m_oswindow->display(), m_oswindow->window(), m_gc, 0, 0, iWidth, iHeight);
//
//         }

#ifdef VERI_BASIC_TEST

            XColor xcolour;

            // I guess XParseColor will work here

            xcolour.red = 32000; xcolour.green = 65000; xcolour.blue = 32000;

            xcolour.flags = DoRed | DoGreen | DoBlue;

            XAllocColor(m_oswindow->display(), m_oswindow->m_colormap, &xcolour);

            XSetForeground(m_oswindow->display(), m_gc, xcolour.pixel);

            XFillRectangle(m_oswindow->display(), m_oswindow->window(), m_gc, 0, 0, iWidth, iHeight);

#endif

         }
         catch (...)
         {

         }

      }

      //pximage->data = nullptr;

      //xcb_free_pixmap(pxcbconnection, pixmap);

      if (m_pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning)
      {

         //XFlush(m_oswindow->display());

         //XSync(m_oswindow->display(), false);

      }

      return true;

   }


   bool buffer::on_update_screen(::graphics::buffer_item * pitem)
   {

      throw ("use update_window(void)");

      return true;

   }


   bool buffer::_on_begin_draw(::graphics::buffer_item * pbufferitem)
   {

////      m_iGoodStride = maximum(m_iGoodStride, window_size().cx());
//
//      bitmap_source_buffer::on_begin_draw();
//
//      auto pitem = double_buffer::on_begin_draw();
//
//      m_iGoodStride = pitem->m_pimage2->scan_size();
//
//      return pitem;

//      auto pbufferitem = get_buffer_item();
//
//      buffer_size_and_position(pbufferitem);

      auto pimageBuffer = pbufferitem->m_pimage2;

      if (pimageBuffer->m_size != pbufferitem->m_size)
      {

         if(!update_buffer(pbufferitem))
         {

            return false;

         }

      }

      if(!double_buffer::_on_begin_draw(pbufferitem))
      {

         return false;

      }

      return true;

   }


   int buffer::shm_completion_type_id()
   {
      return xcb_get_extension_data(m_pdisplay->xcb_connection(), &xcb_shm_id)->first_event + XCB_SHM_COMPLETION;
   }


} // namespace windowing_xcb




