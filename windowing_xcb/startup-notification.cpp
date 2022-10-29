//
// Created by camilo on 17/02/2021. 00:32 BRT <3TBS_!!
//
#include "framework.h"
#ifdef WITH_SN
#define SN_API_NOT_YET_FROZEN
#include <libsn/sn.h>



int g_iIgnoreXDisplayError = 0;


void on_sn_launch_context(void * pSnContext , Window window)
{

   SnLauncheeContext * pcontext = (SnLauncheeContext *) pSnContext;

//   string str;
//
//   str.format("Is this the window id %08x?\n", window);
//
//   output_debug_string(str);

   sn_launchee_context_setup_window(pcontext, window);

}


void on_sn_launch_complete(void * pSnContext)
{

   SnLauncheeContext * pcontext = (SnLauncheeContext *) pSnContext;

   sn_launchee_context_complete(pcontext);

}


void x_display_error_trap_push(SnDisplay * sndisplay, Display * display)
{

   g_iIgnoreXDisplayError++;

}


void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display)
{

   synchronous_lock sl(user_synchronization());

   g_iIgnoreXDisplayError--;

   if(g_iIgnoreXDisplayError == 0)
   {

      XSync(display, false);

   }

}


namespace windowing_xcb
{


   void windowing::_libsn_start_context()
   {

      Display * pdisplay = m_pdisplay->m_pX11Display;

      SnDisplay * psndisplay = sn_display_new(pdisplay, &x_display_error_trap_push, &x_display_error_trap_pop);

      int iScreen = DefaultScreen(pdisplay);

      auto papp = m_pcontext->m_pacmeapplicationMain ? m_pcontext->m_pacmeapplicationMain : m_pcontext->m_pacmeapplicationStartup;

      string strAppId = papp->m_strAppId;

      strAppId.find_replace("/", ".");

      m_pSnLauncheeContext = sn_launchee_context_new(psndisplay, iScreen, strAppId);

   }


} // namespace windowing_xcb


#endif



