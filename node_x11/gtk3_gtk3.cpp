// Changed by camilo on 2021-12-09 13:40 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "node.h"
#include "__standard_type.h"
#include "apex/message/global.h"
#include "acme/constant/id.h"
#include "acme/operating_system/process.h"
#include "acme/platform/system.h"


#include <gtk/gtk.h>
#include <limits.h>

//// apt-get install libgtk2.0-dev
//// and restart codeblocks/IDE
//#include <gtk/gtk.h>
//#include <sys/utsname.h>
//#include <gdk/gdkwayland.h>

platform_char *** process_get_pargv();

//namespace nano
//{
//   namespace user
//   {
//      void initialize_display_type(enum_display_type edisplaytype);
//   }// namespace user
//} // namespace nano

////int uname(struct utsname *buf);
//#ifndef RASPBERRYPIOS
////#ifndef MANJARO
//// Manjaro libappindicator-gtk3
////#include <libappindicator3-0.1/libappindicator/app-indicator.h>
//#ifdef DEBIAN_LINUX
//#include <libayatana-appindicator/app-indicator.h>
//#else
//#include <libappindicator/app-indicator.h>
//#endif
////#include <libappindicator-0.1/libappindicator/app-indicator.h>
////#else // MANJARO
////#include <libappindicator-0.1/libappindicator/app-indicator.h>
////#endif
//#endif

//#include <malloc.h>

#include <time.h>

#include <new>

#include <gio/gio.h>

#include <string.h>

#include <sys/stat.h>

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"


namespace node_gtk3
{


   void node::initialize_window_manager()
   {


   }


//   ::e_status g_estatusInitGtk = error_not_initialized;
//
//
//   void initialize_gtk()
//   {
//
//      if (g_estatusInitGtk == error_not_initialized)
//      {
//
//         auto pargc = ::platform::get()->get_pargc();
//
//         auto pargs = ::platform::get()->get_pargs();
//
//         if (!gtk_init_check(pargc, pargs))
//         {
//
//            g_estatusInitGtk = ::error_failed;
//
//         }
//         else
//         {
//
//            g_estatusInitGtk = ::success;
//
//         }
//
//         ::windowing::initialize_display_type(calculate_display_type());
//
//      }
//
//   }


} // namespace node_gtk3
