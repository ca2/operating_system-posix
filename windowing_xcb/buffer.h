// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once
//#include <X11/extensions/Xrender.h>


//#include "aura/graphics/graphics/_.h"
#include "aura/graphics/graphics/double_buffer.h"
#include "aura/graphics/graphics/bitmap_source_buffer.h"
#include "acme_posix/shmem.h"
#include <xcb/shm.h>
#include <xcb/xcb_image.h>


namespace windowing_xcb
{


   class CLASS_DECL_AURA buffer :
      virtual public ::graphics::double_buffer,
      virtual public ::graphics::bitmap_source_buffer,
      virtual public ::acme_posix::shmem
   {
   public:



      xcb_image_t *                                m_pxcbimage;
      bool                                         m_bXShmChecked;
      bool                                         m_bXShm;
      xcb_shm_seg_t                                m_xcbshmseg;
      ::int_size                                   m_sizeXcbShm;
      ::int_rectangle                              m_rectangleLast;
      ::int_size                                   m_sizeLastBitBlitting;
      bool                                         m_bUseXShmIfAvailable;
      ::pointer<windowing_xcb::display>            m_pdisplay;
      xcb_gcontext_t                               m_gcontext;
      bool                                         m_bShmAttached;

      //::int_size                                   m_sizeImage;
      //::memory                                     m_memoryImage;

      buffer();
      ~buffer() override;


      ::windowing_xcb::window * xcb_window();


      void initialize_graphics_graphics(::windowing::window * pimpl) override;
      void destroy() override;


      virtual void _map_shared_memory(const ::int_size & size);

      bool attach_shm();
      bool query_shm();
      bool detach_shm();
      int shm_completion_type_id();

      bool update_buffer(::graphics::buffer_item * pbufferitem) override;


      virtual bool create_os_buffer(const ::int_size & size, int iStride = -1) ;
      virtual void destroy_os_buffer() ;


      //bool update_screen() override;
      bool update_screen() override;
      virtual bool _update_screen_lesser_lock();
      virtual bool _update_screen_unlocked(::graphics::buffer_item * pitem);
      bool on_update_screen(::graphics::buffer_item * pitem) override;


      bool buffer_lock_round_swap_key_buffers() override;

      //void update_window();

      bool _on_begin_draw(::graphics::buffer_item * pbufferitem) override;


   };


} // namespace windowing_xcb



