// From node_gtk/windowing by camilo on 2023-02-23 05:05 BRT <3ThomasBorregaardSOrensen!!
#include "framework.h"
#include "windowing.h"


namespace node_kde
{


   windowing::windowing()
   {

      //m_pWindowing4 = this;

   }


   windowing::~windowing()
   {


   }


//   ::e_status windowing::windowing_post(const ::procedure & procedure)
//   {
//
//      gdk_fork([routine]()
//               {
//
//                  routine();
//
//               });
//
//      return success;
//
//   }


   bool windowing::message_loop_step()
   {

      return ::node_gtk::windowing::message_loop_step();

//      if(!x11_message_loop_step())
//      {
//
//         return false;
//
//      }
//
//      return true;

   }


} // namespace node_kde



