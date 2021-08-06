// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:42 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once
//#include <X11/extensions/Xrender.h>


//#include "app/base/graphics/graphics_window_buffer.h"
namespace windowing_xcb
{


   class CLASS_DECL_AURA buffer :
      virtual public ::graphics::double_buffer,
      virtual public ::graphics::bitmap_source_buffer
   {
   public:


      ::rectangle_i32                              m_rectLast;
      __pointer(windowing_xcb::display)       m_pdisplay;
      xcb_gcontext_t                               m_gcontext;


      buffer();
      ~buffer() override;


      ::windowing_xcb::window * xcb_window() { return (::windowing_xcb::window *) (m_pwindow ? m_pwindow->m_pWindow : nullptr); }


      ::e_status initialize_graphics_graphics(::user::interaction_impl * pimpl) override;
      ::e_status destroy() override;



      virtual bool create_os_buffer(const ::size_i32 & size, int iStride = -1) ;
      virtual void destroy_os_buffer() ;


      virtual bool update_window() override;
      virtual bool update_window(::image * pimage) override;


      virtual bool buffer_lock_round_swap_key_buffers() override;

      //void update_window();

      ::draw2d::graphics * on_begin_draw() override;


   };


} // namespace windowing_xcb



