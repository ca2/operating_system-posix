//
// Created by camilo on 17/02/2021. 00:32 BRT <3TBS_!!
//
#include "framework.h"
#ifdef WITH_SN
#include "sn.h"



int g_iIgnoreXDisplayError = 0;


//void on_sn_launch_context(void * pSnContext , xcb_window_t window)
//{
//
//   SnLauncheeContext * pcontext = (SnLauncheeContext *) pSnContext;
//
//   sn_launchee_context_setup_window(pcontext, window);
//
//}


//void on_sn_launch_complete(void * pSnContext)
//{
//
//   SnLauncheeContext * pcontext = (SnLauncheeContext *) pSnContext;
//
//   sn_launchee_context_complete(pcontext);
//
//}


//void x_display_error_trap_push(SnDisplay * sndisplay, xcb_connection_t * display)
//{
//
//   g_iIgnoreXDisplayError++;
//
//}


//void x_display_error_trap_pop(SnDisplay * sndisplay, xcb_connection_t * display)
//{
//
//   synchronous_lock sl(user_mutex());
//
//   g_iIgnoreXDisplayError--;
//
//   if(g_iIgnoreXDisplayError == 0)
//   {
//
//      XSync(display, false);
//
//   }
//
//}


namespace windowing_xcb
{


   void windowing::_libsn_start_context()
   {

//      xcb_connection_t * pdisplay = m_pdisplay->xcb_connection();
//
//      SnDisplay * psndisplay = sn_display_new(pdisplay, &x_display_error_trap_push, &x_display_error_trap_pop);
//
//      int iScreen = DefaultScreen(pdisplay);
//
//      m_pSnLauncheeContext = sn_launchee_context_new(psndisplay, iScreen, System.m_strProgName);

   }


} // namespace windowing_xcb


#endif



