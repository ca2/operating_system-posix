// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// recreated by Camilo 2021-04-27 06:39 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing.h"
#include <QtX11Extras/QX11Info>
#include <X11/Xlib-xcb.h>


namespace node_kde
{


   windowing::windowing()
   {

      m_pWindowing2 = this;

   }


   windowing::~windowing()
   {


   }


   ::e_status windowing::windowing_branch(const ::routine & routine)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto pnode = psystem->node()->cast < node >();

      // invoke on the main thread
      QMetaObject::invokeMethod(
         pnode->m_pqapplication,
         [routine]
         {

            routine();

         });


      return success;

   }



   bool windowing::message_loop_step()
   {

      if(!xcb_message_loop_step())
      {

         return false;

      }

      return true;

   }


   xcb_connection_t * windowing::_get_connection()
   {

      XGetXCBConnection

      return QX11Info::display();

   }


} // namespace node_kde



