//
// Created by camilo on 2022-08-17 22:53 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "desktop_environment.h"

////#include "windowing.h"
//#include <QtX11Extras/QX11Info>
//#include <X11/Xlib-xcb.h>
//#include <QScreen>
//
//::particle * user_synchronization();


namespace node_gtk_based
{


   desktop_environment::desktop_environment()
   {

      //m_pWindowing2 = this;

      //m_bX11 = QX11Info::isPlatformX11();

   }


   desktop_environment::~desktop_environment()
   {


   }


//   ::e_status desktop_environment::_get_monitor_rectangle(::collection::index iIndex, ::int_rectangle *prectangle)
//   {
//
//      synchronous_lock sl(user_synchronization());
//
//      auto screens = QGuiApplication::screens();
//
//      if (iIndex < 0 || iIndex >= screens.size())
//      {
//
//         return ::error_failed;
//
//      }
//
//      auto pscreen = screens.at(iIndex);
//
//      if (pscreen == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      int left             = 0;
//      int top              = 0;
//      int right            = 0;
//      int bottom           = 0;
//
//      pscreen->geometry().getCoords(&left, &top, &right, &bottom);
//
//      prectangle->left()     = left;
//      prectangle->top()      = top;
//      prectangle->right()    = right + 1;
//      prectangle->bottom()   = bottom + 1;
//
//      return ::success;
//
//   }
//
//
//   ::e_status desktop_environment::_get_workspace_rectangle(::collection::index iIndex, ::int_rectangle *prectangle)
//   {
//
//      synchronous_lock sl(user_synchronization());
//
//      auto screens = QGuiApplication::screens();
//
//      if (iIndex < 0 || iIndex >= screens.size())
//      {
//
//         return ::error_failed;
//
//      }
//
//      auto pscreen = screens.at(iIndex);
//
//      if (pscreen == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      int left             = 0;
//      int top              = 0;
//      int right            = 0;
//      int bottom           = 0;
//
//      pscreen->availableGeometry().getCoords(&left, &top, &right, &bottom);
//
//      prectangle->left()     = left;
//      prectangle->top()      = top;
//      prectangle->right()    = right + 1;
//      prectangle->bottom()   = bottom + 1;
//
//      return ::success;
//
//   }
//
//
//   void desktop_environment::get_monitor_rectangle(::collection::index iIndex, ::int_rectangle *prectangle)
//   {
//
//      if(m_bX11)
//      {
//
//         m_pwindowing->windowing_send([this, iIndex, prectangle]() { _get_monitor_rectangle(iIndex, prectangle); });
//
//      }
//      else
//      {
//
//         _get_monitor_rectangle(iIndex, prectangle);
//
//      }
//
//   }

//
//   void desktop_environment::get_workspace_rectangle(::collection::index iIndex, ::int_rectangle *prectangle)
//   {
//
//      if(m_bX11)
//      {
//
//         m_pwindowing->windowing_send([this, iIndex, prectangle]() { _get_workspace_rectangle(iIndex, prectangle); });
//
//      }
//      else
//      {
//
//         _get_workspace_rectangle(iIndex, prectangle);
//
//      }
//
//   }


//   void desktop_environment::windowing_post(const ::procedure & procedure)
//   {
//
//      auto psystem = system();
//
//      auto pnode = psystem->node()->cast < node >();
//
//      auto pqapplication = pnode->m_pqapplication;
//
//      // invoke on the main thread
//      QMetaObject::invokeMethod(
//         pqapplication,
//         [procedure]
//         {
//
//            procedure();
//
//         });
//
//
//      //return success;
//
//   }
//
//
//   bool desktop_environment::aaa_message_loop_step()
//   {
//
//      auto psystem = system();
//
//      auto psession = psystem->session();
//
//      auto puser = user();
//
//      auto pwindowing = system()->windowing();
//
//      if(!pwindowing->xcb_message_loop_step())
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }


} // namespace node_gtk_based



