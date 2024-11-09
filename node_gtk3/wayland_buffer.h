//
// Created by camilo on 2024-09-14 13:29 <3ThomasBorregaardSorensen!!
//

#pragma once


#include "windowing_system_wayland/_.h"
//#include "aura/graphics/graphics/_graphics.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "aura/graphics/graphics/bitmap_source_buffer.h"
#include "aura/graphics/graphics/double_buffer.h"
#include "acme/graphics/image/pixmap.h"
#include "acme_posix/shmem.h"

namespace node_gtk3
{


   class CLASS_DECL_NODE_GTK3 wayland_buffer :
      virtual public ::graphics::double_buffer,
      virtual public ::graphics::bitmap_source_buffer//,
      //virtual public ::acme_posix::shmem
   {
   public:

      ::pixmap             m_pixmap;
      //XImage *             m_pximage;
      bool                 m_bXShmChecked;
      bool                 m_bXShm;
      //XShmSegmentInfo      m_xshmsegmentinfo;
      ::int_size           m_sizeLastBitBlitting;
      bool                 m_bUseXShmIfAvailable;
      bool                 m_bXShmPutImagePending;
      //::pointer < ::mutex >                         m_pmutexPixmap;
      //pixmap                        m_pixmap;
      //GC                   m_gc;
      //memory                        m_mem;
      //XImage *                      m_pimage;
      //bool                          m_bMapped;
      ::int_rectangle      m_rectangleLast;
      ::wl_callback*m_pwlcallbackFrame;
      //::image::image_pointer                         m_pimage;
      //interlocked_huge_integer                              m_interlockedPostedScreenUpdate;
//manual_reset_happening m_happeningXshm;
      //bool m_bXShmComplete;
      //interlocked_huge_integer                              m_interlockedXShmPutImage;


      wayland_buffer();
      ~wayland_buffer() override;


      virtual ::windowing_wayland::window * x11_window();


      void initialize_graphics_graphics(::windowing::window * pimpl) override;
      void destroy() override;
      virtual void __handle_window_redraw(::wl_callback *pwlcallback, uint32_t time);

      bool update_buffer(::graphics::buffer_item * pbufferitem) override;

      virtual bool create_os_buffer(const ::int_size & size, int iStride = -1);
      virtual void destroy_os_buffer();


      virtual void _map_shared_memory(const ::int_size & size);


//      virtual bool create_os_buffer(::image::image *pimage);
//      virtual void destroy_os_buffer(::image::image *pimage);

      bool update_screen() override;
      //virtual bool _post_update_screen();
      //virtual bool _update_screen_unlocked(::graphics::buffer_item * pitem);
      bool on_update_screen(::graphics::buffer_item * pitem) override;


      bool buffer_lock_round_swap_key_buffers() override;

      //void update_window();

      bool _on_begin_draw(::graphics::buffer_item * pbufferitem) override;

      //bool presentation_complete() override;

      void __redraw(struct wl_callback *pwlcallback, uint32_t time);

   };



} // namespace node_gtk3