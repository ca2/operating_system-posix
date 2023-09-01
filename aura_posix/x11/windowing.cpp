// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-05-22 03:07 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing.h"
#include "window.h"
#include "aura/user/user/interaction_impl.h"


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
//      //::rectangle_i32 rectangle;
//
//      //::x11_get_window_rect(m_pdisplay->Display(), (Window) oswindow->get_os_data(), &rectangle);
//
//      //_defer_position_message(oswindow, rectangle.top_left());
//
//      //_defer_size_message(oswindow, rectangle.size());
//
//   }


   void windowing::_position_message(::windowing::window * pwindow, const ::point_i32 & point)
   {

      //if(pwindow->m_point != point)
      {

         pwindow->m_point = point;

         ::user::primitive_impl * pimpl = pwindow->m_puserinteractionimpl;

         if (pimpl != nullptr)
         {

            ::user::interaction * pinteraction = pimpl->m_puserinteraction;

            if (pinteraction != nullptr)
            {

//            auto pointWindow = pinteraction->const_layout().window().origin();
//
//            information() << "const_layout().window().origin() : " << pointWindow;
//
//            information() << "pointNew                         : " << point;
//
//            //bool bPositionFix = pointWindow != point;
//
//            //if (bPositionFix)
               {

                  information() << "calling on_reposition...";

                  pinteraction->m_pprimitiveimpl->on_reposition(point);

               }

            }

         }

      }

   }


   void windowing::_size_message(::windowing::window * pwindow, const ::size_i32 & size)
   {

      //if(pwindow->m_size != size)
      {

         pwindow->m_size = size;

         ::user::primitive_impl * pimpl = pwindow->m_puserinteractionimpl;

         if (pimpl != nullptr)
         {

            ::user::interaction * pinteraction = pimpl->m_puserinteraction;

            if (pinteraction != nullptr)
            {

//               auto sizeDesign = pinteraction->const_layout().design().size();
//
//               information() << "const_layout().design().size() : " << sizeDesign;
//
//               information() << "sizeNew                        : " << size;
//
//               bool bSizeFix = sizeDesign != size;
//
//               if (bSizeFix)
               {

                  information() << "calling on_resize...";

                  pinteraction->m_pprimitiveimpl->on_resize(size);

               }

            }

         }

      }

   }


} // namespace windowing_posix



