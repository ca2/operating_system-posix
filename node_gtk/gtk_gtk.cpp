// Changed by camilo on 2021-12-09 13:40 BRT <3ThomasBorregaardSorensen!!
#include "framework.h"
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
//#ifndef RASPBIAN
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

//#include <dirent.h>
#include <sys/stat.h>

//
//#endif

//bool linux_g_direct_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge);
// /void linux_g_direct_app_indicator_term(AppIndicator * pindicator);
//void linux_g_direct_app_indicator_step(void * pvoidInd);


#pragma GCC diagnostic ignored "-Wdeprecated-declarations"


//class pmutex_lock
//{
//public:
//
//   pthread_mutex_t * m_pmutex;
//
//   bool m_bLock;
//
//   pmutex_lock(pthread_mutex_t * pmutex, bool bStartLocked = true) :
//      m_pmutex(pmutex)
//   {
//
//      if(bStartLocked)
//      {
//
//         lock();
//
//
//      }
//
//
//   }
//
//   ~pmutex_lock()
//   {
//
//
//   }
//
//
//   void lock()
//   {
//
//      pthread_mutex_lock(m_pmutex);
//
//   }
//
//
//   void unlock()
//   {
//
//      pthread_mutex_unlock(m_pmutex);
//
//   }
//
//};
//
//
//void os_post_quit();

//const char * linux_g_direct_get_file_icon_path(const char * pszPath, int iSize)
//{
//
//   GFile * pfile = g_file_new_for_path (pszPath);
//
//   if(pfile == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   GError * perror = nullptr;
//
//   GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);
//
//   if(pfileinfo == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   /* you'd have to use g_loadable_icon_load to get the actual icon */
//   GIcon * picon = g_file_info_get_icon (pfileinfo);
//
//   if(picon == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   if(G_IS_FILE_ICON(G_OBJECT(picon)))
//   {
//
//      GFileIcon * pfileicon = G_FILE_ICON(G_OBJECT(picon));
//
//      if(pfileicon == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      GFile * pfileIcon = g_file_icon_get_file(pfileicon);
//
//      if(pfileIcon == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      char * psz = strdup(g_file_get_path(pfileIcon));
//
//      return psz;
//
//   }
//   else if(G_IS_THEMED_ICON(G_OBJECT(picon)))
//   {
//
//      GtkIconInfo *pGtkIconInfo;
//
//      GtkIconTheme *pGtkIconTheme= gtk_icon_theme_get_default();
//
//      if(pGtkIconTheme == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      pGtkIconInfo = gtk_icon_theme_lookup_by_gicon(pGtkIconTheme,picon,(gint)iSize,GTK_ICON_LOOKUP_USE_BUILTIN);
//
//      if(pGtkIconInfo == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      const char * point = gtk_icon_info_get_filename(pGtkIconInfo);
//
//      char * psz = nullptr;
//
//      if(point != nullptr)
//      {
//
//         psz = strdup(point);
//
//      }
//
//      return psz;
//
//   }
//
//   return nullptr;
//
//}
//
//
//const char * linux_g_direct_get_file_content_type(const char * pszPath)
//{
//
//   GFile * pfile = g_file_new_for_path (pszPath);
//
//   if(pfile == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   GError * perror = nullptr;
//
//   GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);
//
//   if(pfileinfo == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   const char * pszContentType = g_file_info_get_content_type (pfileinfo);
//
//   const char * point = nullptr;
//
//   if(pszContentType != nullptr)
//   {
//
//      point = strdup(pszContentType);
//
//   }
//
//   return point;
//
//}
//

namespace node_gtk
{

bool g_bInitGtk = false;


::e_status g_estatusInitGtk = ::error_none;


::e_status os_defer_init_gtk(::acme::system * psystem)
{

   if (!g_bInitGtk)
   {

      g_bInitGtk = true;

      if (!gtk_init_check(psystem->subsystem()->get_pargc(),
                          psystem->subsystem()->get_pargv()))
      {

         g_estatusInitGtk = ::error_failed;

      }
      else
      {

         g_estatusInitGtk = ::success;

      }

   }

   return g_estatusInitGtk;


}


} // namespace node_gtk