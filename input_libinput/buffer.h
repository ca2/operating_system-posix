// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


//#include "aura/graphics/graphics/_.h"
//#include "aura/graphics/graphics/_graphics.h"
#include "acme/primitive/geometry2d/rectangle.h"
#include "aura/graphics/graphics/bitmap_source_buffer.h"
#include "aura/graphics/graphics/double_buffer.h"
#include "aura/graphics/image/pixmap.h"
#include "acme_posix/shmem.h"
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
//#include <X11/extensions/Xrender.h>

//#include "app/base/graphics/graphics_window_buffer.h"
namespace windowing_x11
{


   class CLASS_DECL_AURA buffer :
      virtual public ::graphics::double_buffer,
      virtual public ::graphics::bitmap_source_buffer,
      virtual public ::acme_posix::shmem
   {
   public:

      ::pixmap             m_pixmap;
      XImage *             m_pximage;
      bool                 m_bXShmChecked;
      bool                 m_bXShm;
      XShmSegmentInfo      m_xshmsegmentinfo;
      ::size_i32           m_sizeLastBitBlitting;
      bool                 m_bUseXShmIfAvailable;
      bool                 m_bXShmPutImagePending;
      //::pointer < ::mutex >                         m_pmutexPixmap;
      //pixmap                        m_pixmap;
      GC                   m_gc;
      //memory                        m_mem;
      //XImage *                      m_pimage;
      //bool                          m_bMapped;
      ::rectangle_i32      m_rectangleLast;
      //::image_pointer                         m_pimage;
      //interlocked_i64                              m_interlockedPostedScreenUpdate;
//manual_reset_event m_evXshm;
      //bool m_bXShmComplete;
      //interlocked_i64                              m_interlockedXShmPutImage;


      buffer();
      ~buffer() override;


      virtual ::windowing_x11::window * x11_window();


      void initialize_graphics_graphics(::user::interaction_impl * pimpl) override;
      void destroy() override;


      bool update_buffer(::graphics::buffer_item * pbufferitem) override;

      virtual bool create_os_buffer(const ::size_i32 & size, int iStride = -1);
      virtual void destroy_os_buffer();


      virtual void _map_shared_memory(const ::size_i32 & size);


//      virtual bool create_os_buffer(::image::image * pimage);
//      virtual void destroy_os_buffer(::image::image * pimage);

      bool update_screen() override;
      virtual bool _update_screen_lesser_lock();
      virtual bool _update_screen_unlocked(::graphics::buffer_item * pitem);
      bool on_update_screen(::graphics::buffer_item * pitem) override;


      bool buffer_lock_round_swap_key_buffers() override;

      //void update_window();

      ::graphics::buffer_item * on_begin_draw() override;

      //bool presentation_complete() override;



   };


} // namespace windowing_x11



