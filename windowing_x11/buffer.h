// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


//#include "aura/graphics/graphics/_.h"
//#include "aura/graphics/graphics/_graphics.h"
#include "aura/graphics/graphics/bitmap_source_buffer.h"
#include "aura/graphics/graphics/double_buffer.h"
//#include "acme/primitive/geometry2d/rectangle.h"
#include <X11/Xlib.h>
//#include <X11/extensions/Xrender.h>

//#include "app/base/graphics/graphics_window_buffer.h"
namespace windowing_x11
{


   class CLASS_DECL_AURA buffer :
      virtual public ::graphics::double_buffer,
      virtual public ::graphics::bitmap_source_buffer
   {
   public:


      //::pointer < ::mutex >                         m_pmutexPixmap;
      //pixmap                        m_pixmap;
      GC                            m_gc;
      //memory                        m_mem;
      //XImage *                      m_pimage;
      //bool                          m_bMapped;
      ::rectangle_i32                 m_rectangleLast;
      //::image_pointer                         m_pimage;


      buffer();
      ~buffer() override;


      virtual ::windowing_x11::window * x11_window();


      void initialize_graphics_graphics(::user::interaction_impl * pimpl) override;
      void destroy() override;


      virtual bool create_os_buffer(const ::size_i32 & size, int iStride = -1);
      virtual void destroy_os_buffer();


//      virtual bool create_os_buffer(::image::image * pimage);
//      virtual void destroy_os_buffer(::image::image * pimage);

      bool update_screen() override;
      bool update_screen(::image * pimage) override;


      bool buffer_lock_round_swap_key_buffers() override;

      //void update_window();

      ::draw2d::graphics * on_begin_draw() override;


   };


} // namespace windowing_x11



