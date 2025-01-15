// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// recreated by Camilo 2021-04-27 06:39 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "desktop_environment.h"
#include "node.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/windowing/windowing.h"
#include "aura/platform/node.h"
#include "aura/platform/session.h"
#include "aura/platform/system.h"
#include "aura/user/user/user.h"
#include <qdatastream.h>
#include <QtX11Extras/QX11Info>
#include <QScreen>
#include <QApplication>
#include <X11/Xlib-xcb.h>


//::particle * user_synchronization();


namespace node_kde5
{


   desktop_environment::desktop_environment()
   {

      //m_pWindowing2 = this;

      m_bX11 = QX11Info::isPlatformX11();

   }


   desktop_environment::~desktop_environment()
   {


   }


   // ::e_status desktop_environment::_get_monitor_rectangle(::collection::index iIndex, ::int_rectangle & rectangle)
   // {
   //
   //    //synchronous_lock sl(user_synchronization());
   //
   //    auto screens = QGuiApplication::screens();
   //
   //    if (iIndex < 0 || iIndex >= screens.size())
   //    {
   //
   //       return ::error_failed;
   //
   //    }
   //
   //    auto pscreen = screens.at(iIndex);
   //
   //    if (pscreen == nullptr)
   //    {
   //
   //       return error_failed;
   //
   //    }
   //
   //    int left             = 0;
   //    int top              = 0;
   //    int right            = 0;
   //    int bottom           = 0;
   //
   //    pscreen->geometry().getCoords(&left, &top, &right, &bottom);
   //
   //    rectangle.left()     = left;
   //    rectangle.top()      = top;
   //    rectangle.right()    = right + 1;
   //    rectangle.bottom()   = bottom + 1;
   //
   //    return ::success;
   //
   // }
   //
   //
   // ::e_status desktop_environment::_get_workspace_rectangle(::collection::index iIndex, ::int_rectangle & rectangle)
   // {
   //
   //    //synchronous_lock sl(user_synchronization());
   //
   //    auto screens = QGuiApplication::screens();
   //
   //    if (iIndex < 0 || iIndex >= screens.size())
   //    {
   //
   //       return ::error_failed;
   //
   //    }
   //
   //    auto pscreen = screens.at(iIndex);
   //
   //    if (pscreen == nullptr)
   //    {
   //
   //       return error_failed;
   //
   //    }
   //
   //    int left             = 0;
   //    int top              = 0;
   //    int right            = 0;
   //    int bottom           = 0;
   //
   //    pscreen->availableGeometry().getCoords(&left, &top, &right, &bottom);
   //
   //    rectangle.left()     = left;
   //    rectangle.top()      = top;
   //    rectangle.right()    = right + 1;
   //    rectangle.bottom()   = bottom + 1;
   //
   //    return ::success;
   //
   // }
   //
   //
   // bool desktop_environment::get_monitor_rectangle(::collection::index iIndex, ::int_rectangle & rectangle)
   // {
   //
   //    if(m_bX11)
   //    {
   //
   //       //synchronous_lock sl(user_synchronization());
   //
   //       if(_get_monitor_rectangle(iIndex, rectangle).failed())
   //       {
   //
   //          return false;
   //
   //       }
   //
   //       //m_pwindowing->windowing_send([this, iIndex, prectangle]() { _get_monitor_rectangle(iIndex, prectangle); });
   //
   //    }
   //    else
   //    {
   //
   //       if(_get_monitor_rectangle(iIndex, rectangle).failed())
   //       {
   //
   //          return false;
   //
   //       }
   //
   //    }
   //
   //    return true;
   //
   // }
   //
   //
   // bool desktop_environment::get_workspace_rectangle(::collection::index iIndex, ::int_rectangle & rectangle)
   // {
   //
   //    if(m_bX11)
   //    {
   //
   //       //synchronous_lock sl(user_synchronization());
   //
   //       if(_get_workspace_rectangle(iIndex, rectangle).failed())
   //       {
   //
   //          return false;
   //
   //       }
   //
   //       //m_pwindowing->windowing_send([this, iIndex, prectangle]() { _get_workspace_rectangle(iIndex, prectangle); });
   //
   //    }
   //    else
   //    {
   //
   //       if(_get_workspace_rectangle(iIndex, rectangle).failed())
   //       {
   //
   //          return false;
   //
   //       }
   //
   //    }
   //
   //    return true;
   //
   // }
   //
   //
   // void desktop_environment::user_post(const ::procedure & procedure)
   // {
   //
   //    user()->windowing()->main_post(procedure);
   //
   //    //return success;
   //
   // }
   //
   //
   // bool desktop_environment::message_loop_step()
   // {
   //
   //    auto psystem = system();
   //
   //    auto psession = psystem->session();
   //
   //    auto puser = user();
   //
   //    auto pwindowing = system()->windowing();
   //
   //    if(!pwindowing->xcb_message_loop_step())
   //    {
   //
   //       return false;
   //
   //    }
   //
   //    return true;
   //
   // }


} // namespace node_kde5



