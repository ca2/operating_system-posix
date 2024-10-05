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
#include "acme/platform/context.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing_base.h"
#ifdef WITH_SN
#define SN_API_NOT_YET_FROZEN
#include <libsn/sn.h>
#include "aura/windowing/display.h"


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

   ::platform::get()->system()->windowing_base()->display_error_trap_push(g_iIgnoreXDisplayError);

}


void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display)
{

   //synchronous_lock sl(user_synchronization());

   g_iIgnoreXDisplayError--;

   ::platform::get()->system()->windowing_base()->display_error_trap_pop_ignored(g_iIgnoreXDisplayError);

   // if(g_iIgnoreXDisplayError == 0)
   // {
   //
   //    XSync(display, false);
   //
   // }


}


namespace windowing_posix
{


   void windowing::_libsn_start_context()
   {

      auto ewindowing = system()->m_ewindowing;

      if(ewindowing == e_windowing_x11 && ewindowing == e_windowing_xcb)
      {

         information() << "_libsn_start_context Starting";

         Display *pdisplay = (Display *) system()->windowing_base()->get_display();

         if (::is_null(pdisplay))
         {

            information() << "Couldn't start startup notification context. Display is not set!!";

            return;

         }

         informationf("_libsn_start_context Starting : %llX", (::uptr) pdisplay);

         SnDisplay *psndisplay = sn_display_new(pdisplay, &x_display_error_trap_push, &x_display_error_trap_pop);

         int iScreen = DefaultScreen(pdisplay);

         auto papp = application();

         string strWMClass = papp->m_strAppId;

         strWMClass.find_replace("/", ".");

         m_pSnLauncheeContext = sn_launchee_context_new(psndisplay, iScreen, strWMClass);

         informationf("_libsn_start_context Starting m_pSnLauncheeContext: %llX", (::uptr) m_pSnLauncheeContext);

      }

   }


} // namespace windowing_posix


#endif



