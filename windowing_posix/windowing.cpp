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
#include <X11/Xutil.h>


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

      // ::user::primitive_impl * pimpl = pwindow->m_pwindow;
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
//         ::user::primitive_impl * pimpl = pwindow->m_pwindow;
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


   void windowing::_on_wm_state_change(::windowing::window * pwindow)
   {

      ::pointer<::windowing_posix::window> pposixwindow = pwindow;

      long lState = -1;

      if (!pposixwindow->_get_wm_state_unlocked(lState))
      {

         return;

      }

      bool bNormal = lState == NormalState;

      bool bIconic = lState == IconicState;

      information() << "_on_wm_state_change lState : " << lState;

      information() << "_on_wm_state_change is_normal : " << bNormal;

      information() << "_on_wm_state_change is_iconic : " << bIconic;

      auto pinteraction = pposixwindow->user_interaction();

      if (pinteraction != nullptr)
      {

         //auto pimpl = pinteraction->m_pprimitiveimpl;

         bool bHandled = false;

         //if (pimpl != nullptr)
         {

            if (bIconic)
            {

               if (pinteraction->const_layout().design().display() == ::e_display_iconic
                   || pinteraction->const_layout().design().display() == ::e_display_notify_icon)
               {

//                                 //file_put_contents("/home/camilo/xxx.txt", "");
//
//                                 // 1111111111111111111111111111111111111111111
//
//                                 //pinteraction->hide();
//
                  pinteraction->main_post([pinteraction]()
                                               {

///                                                  auto edisplayPrevious = pinteraction->window_previous_display();

                                                  pinteraction->display_previous(nullptr);

                                               });

//                                 bHandled = true;

               }
               else
               {
////                           else if (pinteraction->const_layout().sketch().display() == ::e_display_full_screen
////                                       && pinteraction->const_layout().design().display() != ::e_display_full_screen)
////                              {
//
//                  pinteraction->display(::e_display_full_screen);
//
//                  // maybe todo: remove x11 window iconic state
//                  // as there seems to be a request to set to non-iconic state
//                  // to the user::interaction associated with this window at this point

               }

            }
            else
            {

//               if (pinteraction->const_layout().design().display() != ::e_display_iconic
//                   && pinteraction->const_layout().design().display() != ::e_display_notify_icon
//                   && windowing().is_screen_visible(pinteraction->const_layout().design().display()))
//               {
//
//                  information() << "X11::ConfigureNotify trying to fix state to iconic state";
//                  pinteraction->post_procedure([pinteraction]()
//                                                  {
//
//                                                     pinteraction->display(::e_display_iconic);
//
//                                                  });
//
//               }

            }

         }

      }

   }


//   ::pointer <::input::input> windowing::_get_input()
//   {
//
//      return nullptr;
//
//   }


} // namespace windowing_posix



