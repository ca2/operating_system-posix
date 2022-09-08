// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing.h"


namespace node_gnome
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


} // namespace node_gnome



