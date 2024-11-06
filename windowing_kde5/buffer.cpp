// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
//#include "windowing_kde5.h"
#include "buffer.h"
#include "window.h"
#include "display.h"
#include "windowing.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/scoped_restore.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "apex/platform/system.h"
#include "aura/graphics/image/image.h"
#include "aura/user/user/interaction_graphics_thread.h"
//#include "aura/user/user/interaction_impl.h"
#include "windowing_system_x11/display_lock.h"

//#define VERI_BASIC_TEST
#define MORE_LOG
#undef MORE_LOG

namespace windowing_kde5
{



   //static const struct wl_callback_listener frame_listener;

   static void
   window_redraw(void *data, struct wl_callback *pwlcallback, uint32_t time)
   {
      // fprintf(stderr, "Redrawing\n");
      auto pbuffer = (buffer *) data;
      pbuffer->__handle_window_redraw(pwlcallback, time);
   }


   static const struct wl_callback_listener frame_listener = {
      window_redraw
   };

   buffer::buffer()
   {

      m_bXShmPutImagePending = false;

      m_bUseXShmIfAvailable = true;

      m_bXShm = false;
      m_bXShmChecked = false;

      //m_gc = nullptr;

      //m_pximage = nullptr;

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

      //map_shared_memory(size.cx() * size.cy() * 4);

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


   ::windowing_kde5::window * buffer::x11_window()
   {

      return (::windowing_kde5::window *) (m_pwindow ? m_pwindow->m_pWindow4 : nullptr);

   }


   void buffer::initialize_graphics_graphics(::windowing::window * pimpl)
   {

      double_buffer::initialize_graphics_graphics(pimpl);

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(x11_window()->x11_display()->Display());

      //XGCValues gcvalues = {};

      //m_gc = XCreateGC(x11_window()->Display(), x11_window()->Window(), 0, &gcvalues);

   }


   void buffer::destroy()
   {

      if (!x11_window())
      {

         throw ::exception(error_wrong_state);

      }

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(x11_window()->x11_display()->Display());

//      if (m_gc != nullptr)
//      {
//
//         XFreeGC(x11_window()->Display(), m_gc);
//
//         m_gc = nullptr;
//
//      }

   }


   bool buffer::update_buffer(::graphics::buffer_item * pbufferitem)
   {

//      auto pwindowing = m_pimpl->m_puserinteraction->windowing();
//
//      auto pdisplay = pwindowing->display();
//
//      auto sizeLargeInternalBitmap = pdisplay->get_monitor_union_size();
//
//      if (pbufferitem->m_size.cx() > sizeLargeInternalBitmap.cx())
//      {
//
//         sizeLargeInternalBitmap.cx() = pbufferitem->m_size.cx();
//
//      }
//
//      if (pbufferitem->m_size.cy() > sizeLargeInternalBitmap.cy())
//      {
//
//         sizeLargeInternalBitmap.cy() = pbufferitem->m_size.cy();
//
//      }
//
//      if (pbufferitem->m_sizeInternal.cx() > sizeLargeInternalBitmap.cx())
//      {
//
//         sizeLargeInternalBitmap.cx() = pbufferitem->m_sizeInternal.cx();
//
//      }
//
//      if (pbufferitem->m_sizeInternal.cy() > sizeLargeInternalBitmap.cy())
//      {
//
//         sizeLargeInternalBitmap.cy() = pbufferitem->m_sizeInternal.cy();
//
//      }
//
//      if (pbufferitem->m_sizeInternal.cx() < sizeLargeInternalBitmap.cx()
//          || pbufferitem->m_sizeInternal.cy() < sizeLargeInternalBitmap.cy())
//      {
//
//         _map_shared_memory(sizeLargeInternalBitmap);
//
//         if (m_shmaddr)
//         {
//
//            pbufferitem->m_sizeInternal = sizeLargeInternalBitmap;
//
//         }
//
//      }

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

//
//   bool buffer::update_screen()
//   {
//
//      if (m_pimpl == nullptr)
//      {
//
//         warningf("windowing_kde5::buffer::update_screen !m_pimpl!!");
//
//         return false;
//
//      }
//
//      if (!m_pimpl->m_pwindow)
//      {
//
//         warningf("windowing_kde5::buffer::update_screen !m_pimpl->m_pwindow!!");
//
//         return false;
//
//      }
//
//      if (!m_pimpl->m_puserinteraction->is_window_screen_visible())
//      {
//
//         information() << "windowing_kde5::buffer::update_screen XPutImage not called. Ui is not visible.";
//
//         return false;
//
//      }
//
//      if (!m_pwindow)
//      {
//
//         warningf("windowing_kde5::buffer::update_screen !m_pwindow!");
//
//         return false;
//
//      }
//
//      //synchronous_lock synchronouslock(user_synchronization());
//
//      //display_lock displayLock(x11_window()->x11_display()->Display());
//
//      //return _update_screen_lesser_lock();
//      return _post_update_screen();
//
//   }


//   bool buffer::_update_screen_lesser_lock()
//   {
//
////      synchronous_lock slGraphics(synchronization());
////
////      auto pitem = get_screen_item();
////
////      synchronous_lock slImage(pitem->m_pmutex);
////
////      slGraphics.unlock();
////
////      return _update_screen_unlocked(pitem);
//
//      return _update_screen_unlocked(nullptr);
//
//   }

//   static void
//   redraw(void *data, struct wl_callback *pwlcallback, uint32_t time)
//   {
//      auto pbuffer = (buffer *) data;
//      pbuffer->redraw(pwlcallback, time);
//   }
//   static const struct wl_callback_listener frame_listener = {
//      redraw
//   };

   void buffer::__redraw(struct wl_callback *pwlcallback, uint32_t time)
   {

   }



   void buffer::__handle_window_redraw(::wl_callback *pwlcallback, uint32_t time)
   {

//       fprintf(stdout, "Redrawing\n");
//      //auto pbuffer = (buffer *) data;
//      //pbuffer->__handle_window_redraw(pwlcallback, time);
//      wl_callback_destroy(m_pwlcallbackFrame);
//      ::pointer < ::windowing_kde5::window > pwaylandwindow = m_pimpl->m_pwindow;
//      //paint_pixels();
//      //frame_callback = wl_surface_frame(surface);
//
//      {
//         synchronous_lock slGraphics(synchronization());
//
//         auto pitem = get_screen_item();
//
//         synchronous_lock slImage(pitem->m_pmutex);
//
//         slGraphics.unlock();
//         wl_surface_damage(pwaylandwindow->m_pwlsurface, 0, 0, pitem->m_size.cx(), pitem->m_size.cy());
//         ::copy_image32((::image32_t *) pwaylandwindow->m_waylandbuffer.m_pdata,
//                        pwaylandwindow->m_waylandbuffer.m_size,
//                        pwaylandwindow->m_waylandbuffer.m_stride,
//                        pitem->m_pimage2->data(), pitem->m_pimage2->scan_size());
//
//      }
////      wl_surface_attach(surface, buffer, 0, 0);
//      //wl_callback_add_listener(frame_callback, &frame_listener, NULL);
//      //wl_surface_commit(surface);
//
//
//
//      information() << "_update_screen_unlocked data : " << (::iptr) pwaylandwindow->m_waylandbuffer.m_pdata;
//      //memset(pwindow->m_waylandbuffer.m_pdata, 127,pitem->m_size.cx() * 4 * pitem->m_size.cy());
////      m_pwlcallbackFrame = wl_surface_frame(pwindow->m_pwlsurface);
//      wl_surface_attach(pwaylandwindow->m_pwlsurface, pwaylandwindow->m_waylandbuffer.m_pwlbuffer, 0, 0);
//      //       wl_callback_add_listener(m_pwlcallbackFrame, &frame_listener, NULL);
//      wl_surface_commit(pwaylandwindow->m_pwlsurface);
//
//      information() << "wl_surface_commit";
//
//      if (!pwaylandwindow->m_bDoneFirstMapping)
//      {
//
//         pwaylandwindow->m_bDoneFirstMapping = true;
//
//         information() << "DOING FIRST Mapping...";
//
//         pwaylandwindow->configure_window_unlocked();
//
//         wl_display_dispatch(pwaylandwindow->wayland_display()->m_pwldisplay);
//
//         wl_display_roundtrip(pwaylandwindow->wayland_display()->m_pwldisplay);
//
//      }
//
//      if (!pwaylandwindow->wayland_windowing()->m_bFirstWindowMap)
//      {
//
//         pwaylandwindow->wayland_windowing()->m_bFirstWindowMap = true;
//
//         //auto psystem = system();
//
//         //string strApplicationServerName = psystem->get_application_server_name();
//
//         //::pointer < ::windowing_kde5::display > pwaylanddisplay = pwaylandwindow->m_pdisplay;
//
//         //gtk_shell1_set_startup_id(pwaylanddisplay->m_pgtkshell1, strApplicationServerName);
//
//         ///information() << "gtk_shell1_set_startup_id : " << strApplicationServerName;
//
//         //auto psystem = system();
//
//         //auto pnode = psystem->node();
//
//         //pnode->defer_notify_startup_complete();
//
//         //on_sn_launch_complete(pwindowing->m_pSnLauncheeContext);
//
//         //pwindowing->m_pSnLauncheeContext = nullptr;
//
//      }
//
//      ::minimum(pwaylandwindow->m_sizeConfigure.cx());
//
//      ::minimum(pwaylandwindow->m_sizeConfigure.cy());
//
   }


//   bool buffer::_update_screen_unlocked(::graphics::buffer_item * pitem)
//   bool buffer::_update_screen_unlocked(::graphics::buffer_item * pitem)
   //bool buffer::_post_update_screen()
   //{
   bool buffer::update_screen()
   {

      if (m_pimpl == nullptr)
      {

         warningf("windowing_kde5::buffer::update_screen !m_pimpl!!");

         return false;

      }

      if (!m_pimpl->m_pwindow)
      {

         warningf("windowing_kde5::buffer::update_screen !m_pimpl->m_pwindow!!");

         return false;

      }

//      if (!m_pimpl->m_puserinteraction->is_window_screen_visible())
//      {
//
//         information() << "windowing_kde5::buffer::update_screen XPutImage not called. Ui is not visible.";
//
//         return false;
//
//      }

//      if (!m_pwindow)
//      {
//
//         warningf("windowing_kde5::buffer::update_screen !m_pwindow!");
//
//         return false;
//
//      }

//      auto sizeBitBlitting = pitem->m_size;
//
//      if (sizeBitBlitting.is_empty())
//      {
//
//         return false;
//
//      }


//
//      uint32_t pixel_value = 0x0; // black
//
//      static void
//      paint_pixels() {
//         int n;
//         uint32_t *pixel = shm_data;
//
//         for (n =0; n < WIDTH*HEIGHT; n++) {
//            *pixel++ = pixel_value;
//         }
//
//         // increase each RGB component by one
//         pixel_value += 0x10101;
//
//         // if it's reached 0xffffff (white) reset to zero
//         if (pixel_value > 0xffffff) {
//            pixel_value = 0x0;
//         }
//      }

      //static const struct wl_callback_listener frame_listener;

      //int ht;

      //::pointer < ::windowing_kde5::window > pwaylandwindow = m_pimpl->m_pwindow;

      //static void
      //redraw(void *data, struct wl_callback *callback, uint32_t time)
      //{
         // fprintf(stderr, "Redrawing\n");
    //     wl_callback_destroy(m_pwlcallbackFrame);
        // if (ht == 0) ht = HEIGHT;

//      if((pwaylandwindow->m_sizeConfigure.cx() == I32_MINIMUM
//          || pwaylandwindow->m_sizeConfigure.cy() == I32_MINIMUM)
//          && (pwaylandwindow->m_timeLastConfigureRequest.elapsed() > 5_s
//         || pwaylandwindow->m_uLastConfigureSerial > pwaylandwindow->m_uLastRequestSerial))
//      {

      ::pointer<::windowing_kde5::window> pwaylandwindow = m_pimpl->m_pwindow;

      ::string strType = ::type(pwaylandwindow->m_pwindow->m_puserinteraction).name();

//       if(pwaylandwindow->m_pxdgtoplevel == nullptr
//       && pwaylandwindow->m_pxdgpopup == nullptr)
//       {
//
//          auto edisplay = pwaylandwindow->m_pwindow->m_puserinteraction->const_layout().design().display();
//
//          if(!pwaylandwindow->windowing()->is_screen_visible(edisplay) && edisplay != e_display_iconic)
//          {
//
//             information()
//                << "::windowing_kde5::buffer::update_screen this is not visible";
//
//             return false;
//
//          }
//
//          //auto x = m_pointWindowBestEffort.x();
//
//       }
//
//       auto pevent = __create_new < manual_reset_event >();
//
//       pevent->ResetEvent();
//
//       user_post([this, pevent]()
//       {
//
//          at_end_of_scope
//          {
//
//             pevent->SetEvent();
//
//          };
//
//          try {
//
//             ::pointer<::windowing_kde5::window> pwaylandwindow = m_pimpl->m_pwindow;
//
//             ::string strType = ::type(pwaylandwindow->m_pwindow->m_puserinteraction).name();
//
//             //::pointer<::windowing_kde5::window> pwaylandwindow = m_pimpl->m_pwindow;
//             if (::is_null(pwaylandwindow->m_pxdgtoplevel)
//                 && ::is_null(pwaylandwindow->m_pxdgpopup)) {
//
//                auto edisplay = pwaylandwindow->m_pwindow->m_puserinteraction->const_layout().design().display();
//
//                if (!pwaylandwindow->windowing()->is_screen_visible(edisplay) && edisplay != e_display_iconic) {
//
//                   information() << "::windowing_kde5::buffer::update_screen this is not visible (2)";
//
//                   return;
//
//                }
//
//                //auto x = m_pointWindowBestEffort.x();
//
//                pwaylandwindow->__map();
//
//             } else {
//
//                auto edisplay = pwaylandwindow->m_pwindow->m_puserinteraction->const_layout().design().display();
//
//                if (!pwaylandwindow->windowing()->is_screen_visible(edisplay) && edisplay != e_display_iconic) {
//
//                   pwaylandwindow->__unmap();
//
//                   return;
//
//                }
//
//             }
//
//             //          auto pimpl = m_pwindow;
//
//             //if(pwaylandwindow->m_bDoneFirstMapping && ::is_set(pwaylandwindow->m_pxdgtoplevel))
//             if (::is_set(pwaylandwindow->m_pxdgtoplevel)) {
//
//                pwaylandwindow->configure_window_unlocked();
//
//             }
//
// //                                       ::pointer<buffer> pbuffer = pimpl->m_pgraphics;
// //
// //                                       pbuffer->_update_screen_lesser_lock();
//
// //                                    }
//
//
//             bool bChangedPosition = false;
//
//             bool bChangedSize = pwaylandwindow->m_sizeConfigure != pwaylandwindow->m_sizeWindow;
//
// //               information() << "(1) m_sizeConfigure : " << pwaylandwindow->m_sizeConfigure
// //                             << " m_sizeWindow : " << pwaylandwindow->m_sizeWindow
// //                             << " pitem->m_size : " << pitem->m_size;
// //
// //               information() << "(1) m_pxdgtoplevel : " << (::iptr) pwaylandwindow->m_pxdgtoplevel;
// //
// //               information() << "(1) m_uLastConfigureSerial : " << pwaylandwindow->m_uLastConfigureSerial;
//
//             if ((::is_set(pwaylandwindow->m_pxdgtoplevel)
//                  || ::is_set(pwaylandwindow->m_pxdgpopup))
//                 //                      && (pwaylandwindow->m_sizeConfigure.cx() == I32_MINIMUM
//                 //                    || pwaylandwindow->m_sizeConfigure.cy() == I32_MINIMUM)
//                 && (pwaylandwindow->m_timeLastConfigureRequest.elapsed() > 5_s
//                     || pwaylandwindow->m_uLastConfigureSerial > pwaylandwindow->m_uLastRequestSerial)) {
//
//                try {
// #ifdef MORE_LOG
//                   information()
//
//                      << "pwaylandwindow->strict_set_window_position_unlocked";
// #endif
//                   pwaylandwindow->strict_set_window_position_unlocked(bChangedPosition, bChangedSize);
//
//                }
//                catch (...) {
//
//                }
//
//             }
//
//             //}
//
//             _synchronous_lock slGraphics(synchronization());
//
//             auto pitem = get_screen_item();
//
//             _synchronous_lock slImage(pitem->m_pmutex);
//
//             slGraphics.unlock();
//
// #ifdef MORE_LOG
//
//             information()
//
//                << "m_sizeConfigure : " << pwaylandwindow->m_sizeConfigure
//                << " m_sizeWindow : " << pwaylandwindow->m_sizeWindow
//                << " pitem->m_size : " << pitem->m_size;
//
//             information()
//                << "lastConfigure.sec" << pwaylandwindow->m_timeLastConfigureRequest.elapsed().m_iSecond
//                << "lastConfigure.nansec" << pwaylandwindow->m_timeLastConfigureRequest.elapsed().m_iNanosecond
//                << "lastConfigure.serial" << pwaylandwindow->m_uLastConfigureSerial
//                << "lastRequest.serial" << pwaylandwindow->m_uLastRequestSerial;
//
//             information()
//
//                << "m_pxdgtoplevel : " << (::iptr) pwaylandwindow->m_pxdgtoplevel
//                << ", m_pxdgpopup : " << (::iptr) pwaylandwindow->m_pxdgpopup;
//
// #endif
//
//             //if(pwaylandwindow->m_sizeWindow == pwaylandwindow->m_waylandbuffer.m_size
//             if ((::is_set(pwaylandwindow->m_pxdgtoplevel)
//                  || ::is_set(pwaylandwindow->m_pxdgpopup))
//                 && pwaylandwindow->m_sizeWindow == pitem->m_size
//                 && ((pwaylandwindow->m_sizeConfigure.cx() == I32_MINIMUM
//                      || pwaylandwindow->m_sizeConfigure.cy() == I32_MINIMUM)
//                     || pwaylandwindow->m_sizeWindow == pwaylandwindow->m_sizeConfigure)
//                 &&
//                 (pwaylandwindow->m_timeLastConfigureRequest.elapsed() > 5_s
//                  || pwaylandwindow->m_uLastConfigureSerial > pwaylandwindow->m_uLastRequestSerial))
//             {
//
// #ifdef MORE_LOG
//
//                information() << "__defer_update_wayland_buffer";
//
// #endif
//
//                pwaylandwindow->__defer_update_wayland_buffer();
//
//
//
// //         m_pwlcallbackFrame = wl_surface_frame(pwaylandwindow->m_pwlsurface);
// //         wl_callback_add_listener(m_pwlcallbackFrame, &frame_listener, this);
//
//                auto & pimage = pitem->m_pimage2;
//
//                pimage->map();
//
//
//                ::copy_image32((::image32_t *) pwaylandwindow->m_buffer.m_pdata,
//                               pwaylandwindow->m_buffer.m_size,
//                               pwaylandwindow->m_buffer.m_stride,
//                               pitem->m_pimage2->data(), pitem->m_pimage2->scan_size());
//
// #ifdef MORE_LOG
//                information()
//
//                   << "_update_screen_unlocked data : "
//                   << (::iptr) pwaylandwindow->m_buffer.m_pdata;
//
// #else
//                // information()
//                //
//                //    << "_update_screen_unlocked data : "
//                //    << (::iptr) pwaylandwindow->m_buffer.m_pdata;
//
// #endif
//
//
//                //memset(pwindow->m_waylandbuffer.m_pdata, 127,pitem->m_size.cx() * 4 * pitem->m_size.cy());
// //      m_pwlcallbackFrame = wl_surface_frame(pwindow->m_pwlsurface);
//                wl_surface_attach(pwaylandwindow->m_pwlsurface,
//                                  pwaylandwindow->m_buffer.m_pwlbuffer, 0, 0);
//                //       wl_callback_add_listener(m_pwlcallbackFrame, &frame_listener, NULL);
//                wl_surface_damage(pwaylandwindow->m_pwlsurface, 0, 0, pitem->m_size.cx(),
//                                  pitem->m_size.cy());
//
//
//                pwaylandwindow->__defer_xdg_surface_ack_configure();
//                wl_surface_commit(pwaylandwindow->m_pwlsurface);
//
// #ifdef MORE_LOG
//
//                information()
//
//                   << "wl_surface_commit";
//
// #endif
//
//                if (!pwaylandwindow->m_bDoneFirstMapping) {
//
//                   pwaylandwindow->m_bDoneFirstMapping = true;
// //
// //                                                information() << "DOING FIRST Mapping...";
// //
// //                                                pwaylandwindow->configure_window_unlocked();
// //
// //                                                wl_display_dispatch(pwaylandwindow->wayland_display()->m_pwldisplay);
// //
// //                                                wl_display_roundtrip(pwaylandwindow->wayland_display()->m_pwldisplay);
// //
//                }
//
// //                                             if (!pwaylandwindow->wayland_windowing()->m_bFirstWindowMap)
// //                                             {
// //
// //                                                pwaylandwindow->wayland_windowing()->m_bFirstWindowMap = true;
// //
// //                                                //auto psystem = system();
// //
// //                                                //string strApplicationServerName = psystem->get_application_server_name();
// //
// //                                                //::pointer < ::windowing_kde5::display > pwaylanddisplay = pwaylandwindow->m_pdisplay;
// //
// //                                                //gtk_shell1_set_startup_id(pwaylanddisplay->m_pgtkshell1, strApplicationServerName);
// //
// //                                                ///information() << "gtk_shell1_set_startup_id : " << strApplicationServerName;
// //
// //                                                //auto psystem = system();
// //
// //                                                //auto pnode = psystem->node();
// //
// //                                                //pnode->defer_notify_startup_complete();
// //
// //                                                //on_sn_launch_complete(pwindowing->m_pSnLauncheeContext);
// //
// //                                                //pwindowing->m_pSnLauncheeContext = nullptr;
// //
// //                                             }
//
// //                  ::minimum(pwaylandwindow->m_sizeConfigure.cx());
//
// //                  ::minimum(pwaylandwindow->m_sizeConfigure.cy());
//
//                //}
//
//             }
//
//             }
//             catch(...)
//             {
//
//
//             }
//
//
//             try {
//
//                ::pointer<::windowing_kde5::window> pwaylandwindow = m_pimpl->m_pwindow;
//
//                if (pwaylandwindow) {
//
//                   auto pimpl = pwaylandwindow->m_pwindow;
//
//                   if (pimpl) {
//
//                      auto pgraphicsthread = pimpl->m_pgraphicsthread;
//
//                      if (pgraphicsthread) {
//
//                         pgraphicsthread->on_graphics_thread_iteration_end();
//
//                      }
//
//                   }
//
//                }
//
//             }
//             catch (...) {
//
//
//             }
//
//
//                                     });
//
//
//       if(pevent->wait(20_s).ok())
//       {
//
// #ifdef MORE_LOG
//          information() << "buffer::update_screen end";
// #endif
//
//       }
//       else
//       {
//
//          information() << "buffer::update_screen timeout";
//
//       }
//
//       //}
//
//       //});
//
//
// //      try
// //      {
// //
// //         x11_window()->strict_set_window_position_unlocked();
// //
// //      }
// //      catch (...)
// //      {
// //
// //      }
//
// //      int iWindowDepth = x11_window()->m_iDepth;
// //
// //      if (m_bUseXShmIfAvailable)
// //      {
// //
// //         if (!m_bXShmChecked)
// //         {
// //
// //            //m_bXShm = XShmQueryExtension(x11_window()->Display());
// //
// //            m_bXShm = false;
// //
// //            m_bXShmChecked = true;
// //
// //         }
// //
// //      }
// //
// //      if (m_bXShm && m_shmid >= 0 && m_shmaddr)
// //      {
// //
// //         if (!m_pximage
// //             || m_pximage->width != pitem->m_sizeInternal.cx()
// //             || m_pximage->height != pitem->m_sizeInternal.cy())
// //         {
// //
// //            if (m_pximage)
// //            {
// //
// //               XShmDetach(x11_window()->Display(), &m_xshmsegmentinfo);
// //
// //               m_pximage->data = nullptr;
// //
// //               XDestroyImage(m_pximage);
// //
// //            }
// //
// //            m_pximage = XShmCreateImage(
// //               x11_window()->Display(),
// //               x11_window()->Visual(),
// //               iWindowDepth,
// //               ZPixmap,
// //               NULL,
// //               &m_xshmsegmentinfo,
// //               pitem->m_sizeInternal.cx(),
// //               pitem->m_sizeInternal.cy());
// //
// //            pitem->m_iScan = pitem->m_sizeInternal.cx() * 4;
// //
// //            m_xshmsegmentinfo.shmid = m_shmid;
// //
// //            m_xshmsegmentinfo.shmaddr = (char *) m_shmaddr;
// //
// //            m_pximage->data = m_xshmsegmentinfo.shmaddr;
// //
// //            m_xshmsegmentinfo.readOnly = False;
// //
// //            XShmAttach(x11_window()->Display(), &m_xshmsegmentinfo);
// //
// //         }
// //
// //      }
// //      else
// //      {
// //
// //         if (!m_pximage
// //             || m_pximage->width != sizeBitBlitting.cx()
// //             || m_pximage->height != sizeBitBlitting.cy()
// //             || m_pximage->data != (char *) pimage->get_data())
// //         {
// //
// //            if (m_pximage)
// //            {
// //
// //               m_pximage->data = nullptr;
// //
// //               XDestroyImage(m_pximage);
// //
// //            }
// //
// //            m_pximage =
// //               XCreateImage(
// //                  x11_window()->Display(),
// //                  x11_window()->Visual(),
// //                  iWindowDepth,
// //                  ZPixmap,
// //                  0,
// //                  (char *) pimage->get_data(),
// //                  sizeBitBlitting.cx(),
// //                  sizeBitBlitting.cy(),
// //                  sizeof(color32_t) * 8,
// //                  pimage->scan_size());
// //
// //         }
// //
// //      }
// //
// //      if (!m_pximage || !m_pximage->data || m_pximage->width <= 0 || m_pximage->height <= 0)
// //      {
// //
// //         warningf("windowing_kde5::buffer::update_screen X11 image null or empty!!");
// //
// //         return false;
// //
// //      }
// //
// //      if (m_gc == nullptr)
// //      {
// //
// //         warningf("windowing_kde5::buffer::update_screen m_gc nullptr!!");
// //
// //         return false;
// //
// //      }
// //
// //      ::size_i32 sizeDesign = m_pimpl->m_puserinteraction->const_layout().design().size();
// //
// //      if (sizeDesign != sizeBitBlitting)
// //      {
// //
// //         warning() << "What!! Drawn Buffer different from window design size";
// //
// //      }
// //
// //      if (sizeBitBlitting.any_gt(pitem->m_sizeInternal))
// //      {
// //
// //         warning() << "What!! Drawn Buffer doesn't fit internal buffer (that should be at least same size as the buffer size)";
// //
// //      }
// //
// //      try
// //      {
// //
// //         if (m_bXShm)
// //         {
// //
// //            if (!pitem->m_manualresetevent._wait(200_ms))
// //            {
// //
// //               x11_window()->_on_end_paint();
// //
// //               information() << "XShmCompletionEvent timeout";
// //
// //               ::pointer<::windowing_kde5::window> px11window = m_pimpl->m_pwindow;
// //
// //               try
// //               {
// //
// //                  px11window->strict_set_window_position_unlocked();
// //
// //               }
// //               catch (...)
// //               {
// //
// //               }
// //
// //            }
// //
// //            copy_image32((::image32_t *) m_pximage->data, sizeBitBlitting,
// //                         pitem->m_iScan, pimage->get_data(), pimage->scan_size());
// //
// //            pitem->m_manualresetevent.ResetEvent();
// //
// //            m_sizeLastBitBlitting = sizeBitBlitting;
// //
// //            x11_window()->m_rectangleXShm = x11_window()->m_pwindow->m_puserinteraction->const_layout().parent_raw_rectangle(::user::e_layout_design);
// //
// //            m_bXShmPutImagePending = true;
// //
// //            XShmPutImage(
// //               x11_window()->Display(),
// //               x11_window()->Window(),
// //               m_gc, m_pximage,
// //               0, 0, 0, 0,
// //               sizeBitBlitting.cx(),
// //               sizeBitBlitting.cy(), true);
// //
// //            information() << "XShmPutImage : " << sizeBitBlitting;
// //
// //         }
// //         else
// //         {
// //
// //            ::pointer<::windowing_kde5::window> px11window = m_pimpl->m_pwindow;
// //
// //            try
// //            {
// //
// //               px11window->strict_set_window_position_unlocked();
// //
// //            }
// //            catch (...)
// //            {
// //
// //            }
// //
// //            m_sizeLastBitBlitting = sizeBitBlitting;
// //
// //            XPutImage(
// //               x11_window()->Display(),
// //               x11_window()->Window(),
// //               m_gc, m_pximage,
// //               0, 0, 0, 0,
// //               sizeBitBlitting.cx(),
// //               sizeBitBlitting.cy());
// //
// //            information() << "XPutImage : " << sizeBitBlitting;
// //
// //            //information() << node()->get_callstack();
// //
// ////            try
// ////            {
// ////
// ////               x11_window()->strict_set_window_position_unlocked();
// ////
// ////            }
// ////            catch (...)
// ////            {
// ////
// ////            }
// //
// //            //x11_window()->m_pwindow->m_puserinteraction->_set_size(sizeBitBlitting, ::user::e_layout_window);
// //
// //            x11_window()->_on_end_paint();
// //
// //            XFlush(x11_window()->Display());
// //
// //            XSync(x11_window()->Display(), false);
// //
// //         }
// //
// //      }
// //      catch (...)
// //      {
// //
// //      }
// //
// //#ifdef VERI_BASIC_TEST
// //
// //      XColor xcolour;
// //
// //      // I guess XParseColor will work here
// //
// //      xcolour.red = 32000; xcolour.green = 65000; xcolour.blue = 32000;
// //
// //      xcolour.flags = DoRed | DoGreen | DoBlue;
// //
// //      XAllocColor(x11_window()->Display(), x11_window()->x11_display()->m_colormap, &xcolour);
// //
// //      XSetForeground(x11_window()->Display(), m_gc, xcolour.pixel);
// //
// //      XFillRectangle(x11_window()->Display(), x11_window()->Window(), m_gc, 0, 0, iWidth, iHeight);
// //
// //      informationf("windowing_kde5::buffer::update_screen BASIC_TEST FillRectangle(%d, %d)", iWidth, iHeight);
// //
// //#endif
// //
// //      // pximage->data = nullptr;
// //
// //      // if(m_pimpl->m_puserinteraction->m_ewindowflag & e_window_flag_arbitrary_positioning)
// //      // {
// //
// //// //     x11_window()->m_pwindow->m_puserinteraction->_set_size({ iWidth, iHeight }, ::user::e_layout_window);
// //
// //      // }

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

            return false;

         }

      }

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



} // namespace windowing_kde5




