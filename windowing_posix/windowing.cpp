// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-05-22 03:07 <3TBS, Mummi and bilbo!!
// more content added: "_position_message" and "_size_message" by camilo <3ThomasBorregaardSorensen!!
// more content added: "_on_wm_state_change" by camilo on 2023-09-01 08:05 <3ThomasBorregaardSorensen!!
// hi5 contribution...
#include "framework.h"
#include "windowing.h"
#include "window.h"
#include "apex/input/input.h"
//#include "aura/user/user/interaction_impl.h"
#if !defined(HAS_GTK3) && !defined(HAS_GTK4) && !defined(HAS_KDE5) && !defined(HAS_KDE6)
#include <X11/Xutil.h>
#endif


namespace windowing_posix
{


   windowing::windowing()
   {


   }


   windowing::~windowing()
   {


   }


   //   void windowing::_defer_position_and_size_message(oswindow oswindow)
//   {
//
//      //::int_rectangle rectangle;
//
//      //::x11_get_window_rect(m_pdisplay->Display(), (Window) oswindow->get_os_data(), &rectangle);
//
//      //_defer_position_message(oswindow, rectangle.top_left());
//
//      //_defer_size_message(oswindow, rectangle.size());
//
//   }


   void windowing::_configure_message(::windowing::window * pwindow, const ::int_rectangle & rectangle)
   {

      // ::user::prototype_impl * pimpl = pwindow->m_pwindow;
      //
      // if (pimpl != nullptr)
      // {
      //
      //    ::user::interaction * pinteraction = pimpl->m_puserinteraction;
      //
      //    if (pinteraction != nullptr)
      //    {
      //
      //       pinteraction->m_pprimitiveimpl->on_configure(rectangle);
      //
      //    }
      //
      // }

      pwindow->on_configure(rectangle);

   }


//   void windowing::_size_message(::windowing::window * pwindow, const ::int_size & size)
//   {
//
//      //if(pwindow->m_size != size)
//      {
//
//         pwindow->m_size = size;
//
//         ::user::prototype_impl * pimpl = pwindow->m_pwindow;
//
//         if (pimpl != nullptr)
//         {
//
//            ::user::interaction * pinteraction = pimpl->m_puserinteraction;
//
//            if (pinteraction != nullptr)
//            {
//
////               auto sizeDesign = pinteraction->const_layout().design().size();
////
////               information() << "const_layout().design().size() : " << sizeDesign;
////
////               information() << "sizeNew                        : " << size;
////
////               bool bSizeFix = sizeDesign != size;
////
////               if (bSizeFix)
//               {
//
//                  information() << "calling on_resize...";
//
//                  pinteraction->m_pprimitiveimpl->on_resize(size);
//
//               }
//
//            }
//
//         }
//
//      }
//
//   }

} // namespace windowing_posix



