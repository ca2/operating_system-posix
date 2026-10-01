// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "platform.h"
#include "windowing_gtk3.h"
#include "graphics.h"
#include "window.h"
#include "display.h"
#include "windowing.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/scoped_restore.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "apex/platform/system.h"
#include "aura/graphics/graphics/buffer_item.h"
#include "aura/graphics/image/image.h"
#include "aura/user/user/interaction_graphics_thread.h"
//#include "aura/user/user/interaction_impl.h"
//#include "windowing_system_x11/display_lock.h"

//#define VERI_BASIC_TEST
#define MORE_LOG
#undef MORE_LOG

namespace windowing_gtk3
{



   //static const struct wl_callback_listener frame_listener;

//   static void
//   window_redraw(void *data, struct wl_callback *pwlcallback, uint32_t time)
//   {
//      // fprintf(stderr, "Redrawing\n");
//      auto pbuffer = (graphics *) data;
//      pbuffer->__handle_window_redraw(pwlcallback, time);
//   }
//
//
//   static const struct wl_callback_listener frame_listener = {
//      window_redraw
//   };

   graphics::graphics()
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


   graphics::~graphics()
   {

//      _destroy_shared_memory();
//
      destroy_os_buffer();

   }


   void graphics::_map_shared_memory(const ::i32_size & size)
   {

      if(!m_bUseXShmIfAvailable)
      {

         return;

      }

      //map_shared_memory(size.cx * size.cy * 4);

   }


//   void graphics::_destroy_shared_memory()
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


   ::windowing_gtk3::window * graphics::gtk3_window()
   {

      ::cast < ::windowing_gtk3::window > pwindow = m_pwindow;

      return pwindow;

   }


   void graphics::initialize_graphics_graphics(::windowing::window * pimpl)
   {

      double_buffer_graphics::initialize_graphics_graphics(pimpl);

      //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //display_lock displaylock(x11_window()->x11_display()->__x11_display());

      //XGCValues gcvalues = {};

      //m_gc = XCreateGC(x11_window()->Display(), x11_window()->Window(), 0, &gcvalues);

   }


   void graphics::destroy()
   {

      if (!gtk3_window())
      {

         throw ::exception(error_wrong_state);

      }

      //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      //display_lock displaylock(x11_window()->x11_display()->__x11_display());

//      if (m_gc != nullptr)
//      {
//
//         XFreeGC(x11_window()->Display(), m_gc);
//
//         m_gc = nullptr;
//
//      }

   }


   bool graphics::update_buffer(::graphics::buffer_item * pbufferitem)
   {

//      auto pwindowing = m_pimpl->m_puserinteraction->windowing();
//
//      auto pdisplay = pwindowing->display();
//
//      auto sizeLargeInternalBitmap = pdisplay->get_monitor_union_size();
//
//      if (pbufferitem->m_size.cx > sizeLargeInternalBitmap.cx)
//      {
//
//         sizeLargeInternalBitmap.cx = pbufferitem->m_size.cx;
//
//      }
//
//      if (pbufferitem->m_size.cy > sizeLargeInternalBitmap.cy)
//      {
//
//         sizeLargeInternalBitmap.cy = pbufferitem->m_size.cy;
//
//      }
//
//      if (pbufferitem->m_sizeInternal.cx > sizeLargeInternalBitmap.cx)
//      {
//
//         sizeLargeInternalBitmap.cx = pbufferitem->m_sizeInternal.cx;
//
//      }
//
//      if (pbufferitem->m_sizeInternal.cy > sizeLargeInternalBitmap.cy)
//      {
//
//         sizeLargeInternalBitmap.cy = pbufferitem->m_sizeInternal.cy;
//
//      }
//
//      if (pbufferitem->m_sizeInternal.cx < sizeLargeInternalBitmap.cx
//          || pbufferitem->m_sizeInternal.cy < sizeLargeInternalBitmap.cy)
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

      return ::graphics::double_buffer_graphics::update_buffer(pbufferitem);

   }


   bool graphics::create_os_buffer(const ::i32_size & size, int iStrideParam)
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
//      m_mem.set_size((m_iGoodStride * size.cy) * sizeof(color32_t));
//
//      m_pixmap.init(size, (color32_t *) m_mem.get_data(), m_iGoodStride);
//
//      //::acme::del(m_pdc);
//
//      {
//
//         xdisplay d(m_pacmewindowingwindow->display());
//
//         m_pimage = XCreateImage(d, m_pacmewindowingwindow->visual(), m_pacmewindowingwindow->m_iDepth, ZPixmap, 0, (char *) m_mem->get_data(), m_pixmap->width(), m_pixmap->height(), sizeof(color32_t) * 8, m_iGoodStride);
//
//         XGCValues gcvalues;
//
//   //      m_pdc = ___new device_context();
//
//         m_gc = XCreateGC(d, m_pacmewindowingwindow->window(), 0, &gcvalues);
//
//      }
//
//      //m_pdc->m_pdisplay = m_pimpl->m_pacmewindowingwindow->display();
//
      return true;

   }


   void graphics::destroy_os_buffer()
   {

//      synchronous_lock sl(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//      xdisplay d(m_pacmewindowingwindow->display());
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


//   bool graphics::create_os_buffer(::image::image *pimage)
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
////         //xdisplay d(m_pacmewindowingwindow->display());
////
////         m_pimage =
////            XCreateImage(
////               m_pacmewindowingwindow->display(),
////               m_pacmewindowingwindow->visual(),
////               m_pacmewindowingwindow->m_iDepth,
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


//   void graphics::destroy_os_buffer(::image::image *pimage)
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

   bool graphics::buffer_lock_round_swap_key_buffers()
   {

      bool bOk1 = double_buffer_graphics::buffer_lock_round_swap_key_buffers();

      bool bOk2 = bitmap_source_buffer_graphics::buffer_lock_round_swap_key_buffers();

      return bOk1 && bOk2;

   }

//
//   bool graphics::update_screen()
//   {
//
//      if (m_pimpl == nullptr)
//      {
//
//         warningf("windowing_gtk3::graphics::update_screen !m_pimpl!!");
//
//         return false;
//
//      }
//
//      if (!m_pimpl->m_pwindow)
//      {
//
//         warningf("windowing_gtk3::graphics::update_screen !m_pimpl->m_pwindow!!");
//
//         return false;
//
//      }
//
//      if (!m_pimpl->m_puserinteraction->is_window_screen_visible())
//      {
//
//         information() << "windowing_gtk3::graphics::update_screen XPutImage not called. Ui is not visible.";
//
//         return false;
//
//      }
//
//      if (!m_pwindow)
//      {
//
//         warningf("windowing_gtk3::graphics::update_screen !m_pwindow!");
//
//         return false;
//
//      }
//
//      //synchronous_lock synchronouslock(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
//
//      //display_lock displayLock(x11_window()->x11_display()->__x11_display());
//
//      //return _update_screen_lesser_lock();
//      return _post_update_screen();
//
//   }


//   bool graphics::_update_screen_lesser_lock()
//   {
//
////      synchronous_lock slGraphics(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
////
////      auto pitem = get_screen_item();
////
////      synchronous_lock slImage(pitem->m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
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
//      auto pbuffer = (graphics *) data;
//      pbuffer->redraw(pwlcallback, time);
//   }
//   static const struct wl_callback_listener frame_listener = {
//      redraw
//   };

   void graphics::__redraw(struct wl_callback *pwlcallback, uint32_t time)
   {

   }



//   void graphics::__handle_window_redraw(::wl_callback *pwlcallback, uint32_t time)
//   {
//
////       fprintf(stdout, "Redrawing\n");
////      //auto pbuffer = (graphics *) data;
////      //pbuffer->__handle_window_redraw(pwlcallback, time);
////      wl_callback_destroy(m_pwlcallbackFrame);
////      ::pointer < ::windowing_gtk3::window > pwaylandwindow = m_pimpl->m_pwindow;
////      //paint_pixels();
////      //frame_callback = wl_surface_frame(surface);
////
////      {
////         synchronous_lock slGraphics(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
////
////         auto pitem = get_screen_item();
////
////         synchronous_lock slImage(pitem->m_pmutex, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
////
////         slGraphics.unlock();
////         wl_surface_damage(pwaylandwindow->m_pwlsurface, 0, 0, pitem->m_size.cx, pitem->m_size.cy);
////         ::copy_image32((::image32_t *) pwaylandwindow->m_waylandbuffer.m_pdata,
////                        pwaylandwindow->m_waylandbuffer.m_size,
////                        pwaylandwindow->m_waylandbuffer.m_stride,
////                        pitem->m_pimage2->data(), pitem->m_pimage2->scan_size());
////
////      }
//////      wl_surface_attach(surface, graphics, 0, 0);
////      //wl_callback_add_listener(frame_callback, &frame_listener, NULL);
////      //wl_surface_commit(surface);
////
////
////
////      information() << "_update_screen_unlocked data : " << (::iptr) pwaylandwindow->m_waylandbuffer.m_pdata;
////      //memset(pwindow->m_waylandbuffer.m_pdata, 127,pitem->m_size.cx * 4 * pitem->m_size.cy);
//////      m_pwlcallbackFrame = wl_surface_frame(pwindow->m_pwlsurface);
////      wl_surface_attach(pwaylandwindow->m_pwlsurface, pwaylandwindow->m_waylandbuffer.m_pwlbuffer, 0, 0);
////      //       wl_callback_add_listener(m_pwlcallbackFrame, &frame_listener, NULL);
////      wl_surface_commit(pwaylandwindow->m_pwlsurface);
////
////      information() << "wl_surface_commit";
////
////      if (!pwaylandwindow->m_bDoneFirstMapping)
////      {
////
////         pwaylandwindow->m_bDoneFirstMapping = true;
////
////         information() << "DOING FIRST Mapping...";
////
////         pwaylandwindow->configure_window_unlocked();
////
////         wl_display_dispatch(pwaylandwindow->wayland_display()->m_pwldisplay);
////
////         wl_display_roundtrip(pwaylandwindow->wayland_display()->m_pwldisplay);
////
////      }
////
////      if (!pwaylandwindow->wayland_windowing()->m_bFirstWindowMap)
////      {
////
////         pwaylandwindow->wayland_windowing()->m_bFirstWindowMap = true;
////
////         //auto psystem = system();
////
////         //string strApplicationServerName = psystem->get_application_server_name();
////
////         //::pointer < ::windowing_gtk3::display > pwaylanddisplay = pwaylandwindow->m_pdisplay;
////
////         //gtk_shell1_set_startup_id(pwaylanddisplay->m_pgtkshell1, strApplicationServerName);
////
////         ///information() << "gtk_shell1_set_startup_id : " << strApplicationServerName;
////
////         //auto psystem = system();
////
////         //auto pnode = psystem->node();
////
////         //pnode->defer_notify_startup_complete();
////
////         //on_sn_launch_complete(pwindowing->m_pSnLauncheeContext);
////
////         //pwindowing->m_pSnLauncheeContext = nullptr;
////
////      }
////
////      ::minimum(pwaylandwindow->m_sizeConfigure.cx);
////
////      ::minimum(pwaylandwindow->m_sizeConfigure.cy);
////
//   }


//   bool graphics::_update_screen_unlocked(::graphics::buffer_item * pitem)
//   bool graphics::_update_screen_unlocked(::graphics::buffer_item * pitem)
   //bool graphics::_post_update_screen()
   //{
   void graphics::update_screen()
   {

      if (!m_pwindow)
      {

         warningf("windowing_gtk3::graphics::update_screen !m_pimpl!!");

         return;

      }
      
      m_pwindow->window_update_screen();

   }


   void graphics::on_update_screen(::graphics::buffer_item * pitem)
   {

      throw ("use update_window(void)");

      //return true;

   }


   bool graphics::_on_begin(::graphics::buffer_item * pbufferitem)
   {

//      auto pbufferitem = get_buffer_item();
//
//      buffer_size_and_position(pbufferitem);

      //~ auto pimageBuffer = pbufferitem->m_pimageBufferItem;

      //~ if (pimageBuffer->m_size != pbufferitem->m_sizeBufferItemWindow)
      //~ {

         //~ if(!update_buffer(pbufferitem))
         //~ {

            //~ return false;

         //~ }

      //~ }

      if(!double_buffer_graphics::_on_begin(pbufferitem))
      {

         return false;

      }

      return true;

   }


//   bool graphics::presentation_complete()
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



} // namespace windowing_gtk3




