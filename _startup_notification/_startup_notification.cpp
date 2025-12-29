//
// Created by camilo on 17/04/22. 03:36 <3ThomasBorregaardSorensen!!
//
//
// Created by camilo on 17/02/2021. 00:32 BRT <3TBS_!!
//
#include "framework.h"
#include "startup-notification.h"
#include "windowing.h"
#include "acme/platform/application.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing.h"
#ifdef WITH_SN
#define SN_API_NOT_YET_FROZEN
#include <libsn/sn.h>
#include "aura/windowing/display.h"
#include "acme/constant/windowing2.h"


static int g_iIgnoreXDisplayError = 0;


void on_sn_launch_context(void * pSnContext , Window window)
{

   SnLauncheeContext * pcontext = (SnLauncheeContext *) pSnContext;

   sn_launchee_context_setup_window(pcontext, window);

}


void on_sn_launch_complete(void * pSnContext)
{

   SnLauncheeContext * pcontext = (SnLauncheeContext *) pSnContext;

   sn_launchee_context_complete(pcontext);

}


// static void
// sn_error_trap_push (SnDisplay *display,
// 		    Display   *xdisplay)
// {
// 	GdkDisplay *gdkdisplay;
//
// 	gdkdisplay = gdk_display_get_default ();
// 	gdk_x11_display_error_trap_push (gdkdisplay);
// }
//
// static void
// sn_error_trap_pop (SnDisplay *display,
// 		   Display   *xdisplay)
// {
// 	GdkDisplay *gdkdisplay;
//
// }

void x_display_error_trap_push(SnDisplay * sndisplay, Display * display)
{

   g_iIgnoreXDisplayError++;

   ::platform::get()->system()->acme_windowing()->display_error_trap_push(g_iIgnoreXDisplayError);

}


void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display)
{

   //synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   g_iIgnoreXDisplayError--;

   ::platform::get()->system()->acme_windowing()->display_error_trap_pop_ignored(g_iIgnoreXDisplayError);

   // if(g_iIgnoreXDisplayError == 0)
   // {
   //
   //    XSync(display, false);
   //
   // }


}


   void windowing_libsn_start_context(::windowing::windowing * pwindowing)
   {

      auto ewindowing = system()->acme_windowing()->get_ewindowing();

      if(ewindowing == ::windowing::e_windowing_x11 && ewindowing == ::windowing::e_windowing_xcb)
      {

         information() << "_libsn_start_context Starting";

         Display *pdisplay = (Display *) system()->acme_windowing()->acme_display();

         if (::is_null(pdisplay))
         {

            information() << "Couldn't start startup notification context. Display is not set!!";

            return;

         }

         informationf("_libsn_start_context Starting : %llX", (::uptr) pdisplay);

         SnDisplay *psndisplay = sn_display_new(pdisplay, &x_display_error_trap_push, &x_display_error_trap_pop);

         int iScreen = DefaultScreen(pdisplay);

         auto papp = pwindowing->application();

         string strWMClass = papp->m_strAppId;

         strWMClass.find_replace("/", ".");

         pwindowing->m_pSnLauncheeContext = sn_launchee_context_new(psndisplay, iScreen, strWMClass);

         informationf("_libsn_start_context Starting m_pSnLauncheeContext: %llX", (::uptr) pwindowing->m_pSnLauncheeContext);

      }

   }


#endif



