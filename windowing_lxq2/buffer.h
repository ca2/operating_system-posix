// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "windowing_q6/buffer.h"
// //#include "aura/graphics/graphics/_graphics.h"
// #include "acme/prototype/geometry2d/rectangle.h"
// #include "aura/graphics/graphics/bitmap_source_buffer.h"
// #include "aura/graphics/graphics/double_buffer.h"
// #include "acme/graphics/image/pixmap.h"
// #include "acme_posix/shmem.h"
// //#include <X11/Xlib.h>
// //#include <X11/extensions/XShm.h>
// //#include <X11/extensions/Xrender.h>

//#include "berg/graphics/graphics_window_buffer.h"
namespace windowing_lxq2
{


   class CLASS_DECL_AURA buffer :
      virtual public ::windowing_q6::buffer//,
      //virtual public ::graphics::bitmap_source_buffer//,
      //virtual public ::acme_posix::shmem
   {
   public:
//
//       ::pixmap             m_pixmap;
//       //XImage *             m_pximage;
//       bool                 m_bXShmChecked;
//       bool                 m_bXShm;
//       //XShmSegmentInfo      m_xshmsegmentinfo;
//       ::int_size           m_sizeLastBitBlitting;
//       bool                 m_bUseXShmIfAvailable;
//       bool                 m_bXShmPutImagePending;
//       //::pointer < ::mutex >                         m_pmutexPixmap;
//       //pixmap                        m_pixmap;
//       //GC                   m_gc;
//       //memory                        m_mem;
//       //XImage *                      m_pimage;
//       //bool                          m_bMapped;
//       ::int_rectangle      m_rectangleLast;
//       //::wl_callback*m_pwlcallbackFrame;
//       //::image::image_pointer                         m_pimage;
//       //interlocked_long_long                              m_interlockedPostedScreenUpdate;
// //manual_reset_happening m_happeningXshm;
//       //bool m_bXShmComplete;
//       //interlocked_long_long                              m_interlockedXShmPutImage;
//

      buffer();
      ~buffer() override;


      ::windowing_lxq2::window * lxq2_window();


      void initialize_graphics_graphics(::windowing::window * pimpl) override;
      void destroy() override;
      //virtual void __handle_window_redraw(::wl_callback *pwlcallback, uint32_t time);

      bool update_buffer(::graphics::buffer_item * pbufferitem) override;

      virtual bool create_os_buffer(const ::int_size & size, int iStride = -1);
      virtual void destroy_os_buffer();


      virtual void _map_shared_memory(const ::int_size & size);


//      virtual bool create_os_buffer(::image::image *pimage);
//      virtual void destroy_os_buffer(::image::image *pimage);

      void update_screen() override;
      //virtual bool _post_update_screen();
      //virtual bool _update_screen_unlocked(::graphics::buffer_item * pitem);
      void on_update_screen(::graphics::buffer_item * pitem) override;


      bool buffer_lock_round_swap_key_buffers() override;

      //void update_window();

      bool _on_begin_draw(::graphics::buffer_item * pbufferitem) override;

      //bool presentation_complete() override;

      //void __redraw(struct wl_callback *pwlcallback, uint32_t time);

   };


} // namespace windowing_lxq2



