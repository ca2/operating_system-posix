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

// apt-get install libgtk2.0-dev
// and restart codeblocks/IDE
#include <gtk/gtk.h>
#include <sys/utsname.h>

platform_char *** process_get_pargv();


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

#include <malloc.h>

#include <time.h>

#include <new>

#include <gio/gio.h>

#include <string.h>

#include <sys/stat.h>

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"


namespace node_gtk
{


   bool g_bInitGtk = false;


   ::e_status g_estatusInitGtk = ::error_none;


   ::e_status os_defer_init_gtk(::node_gtk::node * pgtknode)
   {

      if (!g_bInitGtk)
      {

         g_bInitGtk = true;

         if (!gtk_init_check(pgtknode->acmesystem()->platform()->get_pargc(),
                             pgtknode->acmesystem()->platform()->get_pargv()))
         {

            g_estatusInitGtk = ::error_failed;

         }
         else
         {

            g_estatusInitGtk = ::success;

         }

         pgtknode->_on_gtk_init();

      }

      return g_estatusInitGtk;


   }


} // namespace node_gtk