// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once
//#include <X11/extensions/Xrender.h>


#include "aura/graphics/graphics/_.h"
#include "aura/graphics/graphics/_graphics.h"


namespace windowing_xcb
{


   class CLASS_DECL_AURA buffer :
      virtual public ::graphics::double_buffer,
      virtual public ::graphics::bitmap_source_buffer
   {
   public:


      ::rectangle_i32                              m_rectangleLast;
      ::pointer<windowing_xcb::display>      m_pdisplay;
      xcb_gcontext_t                               m_gcontext;


      buffer();
      ~buffer() override;


      ::windowing_xcb::window * xcb_window();


      void initialize_graphics_graphics(::user::interaction_impl * pimpl) override;
      void destroy() override;



      virtual bool create_os_buffer(const ::size_i32 & size, int iStride = -1) ;
      virtual void destroy_os_buffer() ;


      bool update_screen() override;
      bool update_screen(::image * pimage) override;


      bool buffer_lock_round_swap_key_buffers() override;

      //void update_window();

      ::draw2d::graphics * on_begin_draw() override;


   };


} // namespace windowing_xcb



