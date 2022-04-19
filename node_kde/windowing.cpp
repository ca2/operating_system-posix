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


   void windowing::windowing_post(const ::procedure & procedure)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto pnode = psystem->node()->cast < node >();

      auto pqapplication = pnode->m_pqapplication;

      // invoke on the main thread
      QMetaObject::invokeMethod(
         pqapplication,
         [routine]
         {

            routine();

         });


      //return success;

   }



   bool windowing::message_loop_step()
   {

      if(!xcb_message_loop_step())
      {

         return false;

      }

      return true;

   }


} // namespace node_kde



