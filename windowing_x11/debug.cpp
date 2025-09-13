#include "framework.h"
#include "windowing_x11.h"
////#include "sn/sn.h"


#ifdef OPENBSD

#include <stdio.h>

#endif


extern ::particle * user_synchronization();


//int g_iIgnoreXDisplayError = 0;

//
//void x_display_error_trap_push(SnDisplay * sndisplay, Display * display)
//{
//
//   g_iIgnoreXDisplayError++;
//
//}
//
//
//void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display)
//{
//
//   synchronous_lock sl(user_synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
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
//
//


