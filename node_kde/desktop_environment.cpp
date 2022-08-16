// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// recreated by Camilo 2021-04-27 06:39 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
//#include "windowing.h"
#include <QtX11Extras/QX11Info>
#include <X11/Xlib-xcb.h>
#include <QScreen>

mutex * user_mutex();


namespace node_kde
{


   desktop_environment::desktop_environment()
   {

      //m_pWindowing2 = this;

   }


   desktop_environment::~desktop_environment()
   {


   }


   ::e_status desktop_environment::_get_monitor_rectangle(::index iIndex, ::RECTANGLE_I32 *prectangle)
   {

      synchronous_lock sl(user_mutex());

      auto screens = QGuiApplication::screens();

      if (iIndex < 0 || iIndex >= screens.size())
      {

         return ::error_failed;

      }

      auto pscreen = screens.at(iIndex);

      if (pscreen == nullptr)
      {

         return error_failed;

      }

      int left             = 0;
      int top              = 0;
      int right            = 0;
      int bottom           = 0;

      pscreen->geometry().getCoords(&left, &top, &right, &bottom);

      prectangle->left     = left;
      prectangle->top      = top;
      prectangle->right    = right;
      prectangle->bottom   = bottom;

      return ::success;

   }


   ::e_status desktop_environment::_get_workspace_rectangle(::index iIndex, ::RECTANGLE_I32 *prectangle)
   {

      synchronous_lock sl(user_mutex());

      auto screens = QGuiApplication::screens();

      if (iIndex < 0 || iIndex >= screens.size())
      {

         return ::error_failed;

      }

      auto pscreen = screens.at(iIndex);

      if (pscreen == nullptr)
      {

         return error_failed;

      }

      int left             = 0;
      int top              = 0;
      int right            = 0;
      int bottom           = 0;

      pscreen->availableGeometry().getCoords(&left, &top, &right, &bottom);

      prectangle->left     = left;
      prectangle->top      = top;
      prectangle->right    = right;
      prectangle->bottom   = bottom;

      return ::success;

   }


   void desktop_environment::get_monitor_rectangle(::index iIndex, ::RECTANGLE_I32 *prectangle)
   {

      _get_monitor_rectangle(iIndex, prectangle);
      //auto estatus =
      //
      //m_pwindowing->windowing_send([this, iIndex, prectangle]() { _get_monitor_rectangle(iIndex, prectangle); });

   }


   void desktop_environment::get_workspace_rectangle(::index iIndex, ::RECTANGLE_I32 *prectangle)
   {

      _get_workspace_rectangle(iIndex, prectangle);
      //auto estatus =
      //
      //m_pwindowing->windowing_send([this, iIndex, prectangle]() { _get_workspace_rectangle(iIndex, prectangle); });

   }


   void desktop_environment::windowing_post(const ::procedure & procedure)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto pnode = psystem->node()->cast < node >();

      auto pqapplication = pnode->m_pqapplication;

      // invoke on the main thread
      QMetaObject::invokeMethod(
         pqapplication,
         [procedure]
         {

            procedure();

         });


      //return success;

   }


   bool desktop_environment::message_loop_step()
   {

      auto psystem = m_psystem->m_paurasystem;

      auto psession = psystem->session()->m_paurasession;

      auto puser = psession->user();

      auto pwindowing = puser->windowing1();

      if(!pwindowing->xcb_message_loop_step())
      {

         return false;

      }

      return true;

   }


} // namespace node_kde



