#include "framework.h"
//#include "platform/platform_setup.h"
//#include <limits.h>
//#include "acme/operating_system/x11/_x11.h"
//#include "__standard_type.h"
//#include "gnome.h"
//#include "gnome_gnome.h"
//#include "gnome_internal_glue.h"
//#include "apex/message/global.h"
//#include "aura/const/_const.h"
//#include "acme/constant/id.h"
////#include "platform/_.h"
//#include "aura/os/freebsd/appindicator.h"
//
//
//// apt-get install libgtk2.0-dev
//// and restart codeblocks/IDE
//#include <gtk/gtk.h>
//#include <sys/utsname.h>
//
//
//
//
//
//#include <malloc.h>
//
//#include <time.h>
//
//#include <___new>
//
//#include <gio/gio.h>
//
//#include <string.h>
//
////#include <dirent.h>
//#include <sys/stat.h>
//
////
////#endif
//
////bool linux_g_direct_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge);
//// /void linux_g_direct_app_indicator_term(AppIndicator * pindicator);
////void linux_g_direct_app_indicator_step(void * pvoidInd);
//
//
//
//#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
//
////class pmutex_lock
////{
////public:
////
////   pthread_mutex_t * m_pmutex;
////
////   bool m_bLock;
////
////   pmutex_lock(pthread_mutex_t * pmutex, bool bStartLocked = true) :
////      m_pmutex(pmutex)
////   {
////
////      if(bStartLocked)
////      {
////
////         lock();
////
////
////      }
////
////
////   }
////
////   ~pmutex_lock()
////   {
////
////
////   }
////
////
////   void lock()
////   {
////
////      pthread_mutex_lock(m_pmutex);
////
////   }
////
////
////   void unlock()
////   {
////
////      pthread_mutex_unlock(m_pmutex);
////
////   }
////
////};
//
//
//void os_post_quit();
//
//#ifndef RASPBERRYPIOS
//
//GtkWidget * linux_g_direct_app_indicator_init(AppIndicator * pindicator, user_notify_icon_bridge * pbridge);
//
//
//
//
//
//
//#ifndef RASPBERRYPIOS
//
//
//class gnome_appindicator :
//   virtual public ::freebsd::appindicator
//{
//public:
//
//
//   AppIndicator * m_pindicator;
//
//
//   gnome_appindicator();
//   virtual ~gnome_appindicator();
//
//
//   virtual bool create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge) override;
//   virtual bool init(user_notify_icon_bridge * pbridge);
//   virtual void close();
//
//
//   //virtual bool step() override;
//
//
//};
//
//
//gnome_appindicator::gnome_appindicator()
//{
//
//}
//
//
//gnome_appindicator::~gnome_appindicator()
//{
//
//   close();
//
//}
//
//
//void gnome_appindicator::close()
//{
//
//
//   if(m_pindicator == NULL)
//   {
//
//      return;
//
//   }
//
//   auto pindicator = m_pindicator;
//
//   gdk_fork([pindicator]()
//   {
//
//      app_indicator_set_status(pindicator, APP_INDICATOR_STATUS_PASSIVE);
//
//   });
//
//   m_pindicator = NULL;
//
//}
//
//namespace freebsd
//{
//
//
//   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);
//
//
//   appindicator * allocate_appindicator()
//   {
//
//      return ___new ::gnome_appindicator();
//
//   }
//
//
//} // namespace freebsd
//
//
//bool gnome_appindicator::create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge)
//{
//
//   m_pindicator = app_indicator_new_with_path(scopedstrId, pszIcon, APP_INDICATOR_CATEGORY_APPLICATION_STATUS, pszFolder);
//
//   if(m_pindicator == nullptr)
//   {
//
//      return false;
//
//   }
//
//   if(!init(pbridge))
//   {
//
//      close();
//
//      return false;
//
//   }
//
//   return true;
//
//}
//
//
//
//
//#endif
//
//#endif
//
//
//void safe_free(void * pfree)
//{
//
//   if(pfree == nullptr)
//   {
//
//      return;
//
//   }
//
//   ::free(pfree);
//
//}
//
//
//#ifndef RASPBERRYPIOS
//
//
//bool gnome_appindicator::init(user_notify_icon_bridge * pbridge)
//{
//
//   int iCount = pbridge->_get_notification_area_action_count();
//
//   GtkWidget *  indicator_menu = nullptr;
//
//   if(iCount > 0)
//   {
//
//
//      GError * error = nullptr;
//
//      GtkActionGroup * action_group = gtk_action_group_new ("AppActions");
//
//      if(action_group != nullptr)
//      {
//
//         GtkActionEntry * entries = __allocate< GtkActionEntry[pbridge->_get_notification_area_action_count >()];
//
//         string strInfo;
//
//         strInfo += "<ui>";
//
//         strInfo += "  <popup name='IndicatorPopup'>";
//
//         int iEntry = 0;
//
//         for(int i = 0; i < iCount; i++)
//         {
//
//            int iIndex = i;
//
//            const char * pszName = pbridge->_get_notification_area_action_name(iIndex);
//            const char * pszId = pbridge->_get_notification_area_action_id(iIndex);
//            const char * pszLabel = pbridge->_get_notification_area_action_label(iIndex);
//            const char * pszAccelerator = pbridge->_get_notification_area_action_accelerator(iIndex);
//            const char * pszDescription = pbridge->_get_notification_area_action_description(iIndex);
//
//            memset(&entries[iEntry], 0, sizeof(GtkActionEntry));
//
//            if(strcasecmp(scopedstrName, "separator") == 0)
//            {
//
//               strInfo += "<separator/>\n";
//
//            }
//            else
//            {
//
//               entries[iEntry].name = g_strdup(scopedstrLabel);
//
//               strInfo += "    <menuitem action='";
//               strInfo += pszLabel;
//               strInfo += "' />";
//
//               entries[iEntry].stock_id = g_strdup(scopedstrId);
//
//               entries[iEntry].label = g_strdup(scopedstrName);
//
//               //entries[iEntry].accelerator = g_strdup(scopedstrAccelerator);
//
//               entries[iEntry].accelerator = nullptr;
//
//               entries[iEntry].tooltip = g_strdup(scopedstrDescription);
//
//               entries[iEntry].callback = G_CALLBACK (__extra_action);
//
//               iEntry++;
//
//            }
//
//         }
//
//         strInfo += "  </popup>";
//         strInfo += "</ui>";
//
//         gtk_action_group_add_actions (action_group, entries, iEntry, pbridge);
//
//         GtkUIManager * uim = gtk_ui_manager_new ();
//
//         bool bOk = false;
//
//         gchar * ui_info = (gchar *) g_strdup(strInfo);
//
//         if(uim != nullptr)
//         {
//
//            gtk_ui_manager_insert_action_group (uim, action_group, 0);
//
//            bOk = gtk_ui_manager_add_ui_from_string (uim, ui_info, -1, &error) != FALSE;
//
//            if(!bOk)
//            {
//
//               g_message ("Failed to build menus: %s\n", error->message);
//
//               g_error_free (error);
//
//               error = nullptr;
//
//            }
//
//         }
//
//         for(int i = 0; i < iEntry; i++)
//         {
//
//            g_safe_free((void *) entries[i].name);
//            g_safe_free((void *) entries[i].stock_id);
//            g_safe_free((void *) entries[i].label);
//            g_safe_free((void *) entries[i].accelerator);
//            g_safe_free((void *) entries[i].tooltip);
//
//         }
//
//         delete [] entries;
//
//         g_safe_free(ui_info);
//
//         if(bOk)
//         {
//
//            indicator_menu = gtk_ui_manager_get_widget (uim, "/ui/IndicatorPopup");
//
//            app_indicator_set_menu(m_pindicator, GTK_MENU (indicator_menu));
//
//         }
//
//      }
//
//   }
//
//   app_indicator_set_status(m_pindicator, APP_INDICATOR_STATUS_ACTIVE);
//
//   return true;
//
//}
//
//
//#endif
//
//
//namespace aaa_node_gnome
//{
//
//
//   bool g_bGInitialized = false;
//
//
//   pthread_mutex_t g_mutexG;
//
//
//   bool aaa_gsettings_set(const char * pszSchema, const char * pszKey, const char * pszValue)
//   {
//
//      if(scopedstrSchema == nullptr)
//      {
//
//         return false;
//
//      }
//
//      if(scopedstrKey == nullptr)
//      {
//
//         return false;
//
//      }
//
//      if(scopedstrValue == nullptr)
//      {
//
//         return false;
//
//      }
//
//      GSettings *settings = g_settings_new(scopedstrSchema);
//
//      if(settings == nullptr)
//      {
//
//         return false;
//
//      }
//
//      gboolean bOk = g_settings_set_string(settings, pszKey, pszValue);
//
//      if (settings != nullptr)
//      {
//
//         g_object_unref (settings);
//
//      }
//
//      return bOk;
//
//   }
//
//
//   bool gsettings_sync()
//   {
//
//      g_settings_sync ();
//
//      return true;
//
//   }
//
//
//   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey)
//   {
//
//      if(scopedstrSchema == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      if(scopedstrKey == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      GSettings *settings = g_settings_new(scopedstrSchema);
//
//      if(settings == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      gchar * pgchar = g_settings_get_string (settings, pszKey);
//
//      if(pgchar == nullptr)
//      {
//
//         g_object_unref (settings);
//
//         return nullptr;
//
//      }
//
//      char * psz = strdup(pgchar);
//
//      g_free (pgchar);
//
//      g_object_unref (settings);
//
//      return psz;
//
//   }
//
//
//
//
//   void wallpaper_change_notification (GSettings   *settings,             const gchar *key,             gpointer     data)
//   {
//
//      c_post_system_happening(id_wallpaper_change);
//
//   }
//
//
//   GAction * g_pactionWallpaper = nullptr;
//
//
//   bool g_enable_wallpaper_change_notification(const char * pszSchema, const char * pszKey)
//   {
//
//      if(!g_bGInitialized)
//      {
//
//         return false;
//
//      }
//
//      pmutex_lock lock(&g_mutexG);
//
//      if(g_pactionWallpaper != nullptr)
//      {
//
//         return true;
//
//      }
//
//      GSettings * settings = g_settings_new(scopedstrSchema);
//
//      if(settings == nullptr)
//      {
//
//         return false;
//
//      }
//
//      g_pactionWallpaper = g_settings_create_action (settings, pszKey);
//
//      g_object_unref (settings);
//
//      g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK (wallpaper_change_notification), nullptr);
//
//      return true;
//
//   }
//
//
//   void g_defer_init()
//   {
//
//      if(g_bGInitialized)
//      {
//
//         return;
//
//      }
//
//      g_bGInitialized = true;
//
//      pthread_mutex_init(&g_mutexG, nullptr);
//
//   }
//
//
//   void g_defer_term()
//   {
//
//      if(!g_bGInitialized)
//      {
//
//         return;
//
//      }
//
//      g_bGInitialized = false;
//
//      if(g_pactionWallpaper != nullptr)
//      {
//
//         g_object_unref(g_pactionWallpaper);
//
//         g_pactionWallpaper = nullptr;
//
//      }
//
//      pthread_mutex_destroy(&g_mutexG);
//
//   }
//
//
//} // namespace node_gtk_based
//
//
//const char * linux_g_direct_get_file_icon_path(const char * pszPath, int iSize)
//{
//
//   GFile * pfile = g_file_new_for_path (scopedstrPath);
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
//   GFile * pfile = g_file_new_for_path (scopedstrPath);
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
//   if(scopedstrContentType != nullptr)
//   {
//
//      point = strdup(scopedstrContentType);
//
//   }
//
//   return point;
//
//}
//
//
//int gdk_launch_uri(const char * pszUri, char * pszError, int iBufferSize)
//{
//
//   gboolean ret;
//
//   GError * error = NULL;
//
//   g_type_init();
//
//   ret = g_app_info_launch_default_for_uri(scopedstrUri, NULL, &error);
//
//   if(ret)
//   {
//
//      return true;
//
//   }
//
//   if(scopedstrError != nullptr)
//   {
//
//      strncpy(scopedstrError, error->message, iBufferSize);
//
//   }
//
//   return 0;
//
//}
//
//bool x11_on_event(XEvent * pevent);
//
//GdkFilterReturn x11_gdk_filter(GdkXEvent *xevent, GdkEvent *happening, gpointer data)
//{
//
//   XEvent *pevent = (XEvent *) xevent;
//
//   try
//   {
//
//      if (x11_on_event(pevent))
//      {
//
//         return GDK_FILTER_REMOVE;
//
//      }
//
//   }
//   catch(...)
//   {
//
//
//   }
//   return GDK_FILTER_CONTINUE;
//
////   return GDK_FILTER_REMOVE;
//
//}
//
//
//
//
//
//
////      osdisplay_data * pdisplaydata = (osdisplay_data *) x11_main_display();
////
////   Display * pdisplay = pdisplaydata->display();
//////
//////   if(pdisplay == nullptr)
//////   {
//////
//////      return true;
//////
//////   }
//////
////////   if(!g_bInitX11Thread)
////////   {
////////
////////      g_bInitX11Thread = true;
////////
////////      synchronous_lock sl(user_synchronization());
////////
////////      xdisplay d(pdisplay);
////////
////////      g_atomKickIdle = XInternAtom(pdisplay, "__WM_KICKIDLE", False);
////////
////////      g_windowX11Client = XCreateSimpleWindow(pdisplay, DefaultRootWindow(pdisplay), 10, 10, 10, 10, 0, 0, 0);
////////
////////      XSelectInput(pdisplay, g_windowX11Client, StructureNotifyMask);
////////
////////      g_oswindowDesktop = oswindow_get(pdisplay, DefaultRootWindow(pdisplay));
////////
////////      g_oswindowDesktop->m_pimpl = nullptr;
////////
////////      XSelectInput(pdisplay, g_oswindowDesktop->window(), StructureNotifyMask | PropertyChangeMask);
////////
////////   }
//////
//////
//////   try
//////   {
//////
//////      synchronous_lock sl(user_synchronization());
//////
//////      xdisplay d(pdisplay);
//////
//////      while(XPending(pdisplay) && !g_bFinishX11Thread)
//////      {
////
//////         try
//////         {
//////
//////            XEvent e = {};
//////
//////#if !defined(RASPBERRYPIOS)
//////
//////            XGenericEventCookie * cookie;
//////
//////#endif
//////
//////#if !defined(RASPBERRYPIOS)
//////
//////            if(g_pobjectaExtendedEventListener)
//////            {
//////
//////               cookie = &e.xcookie;
//////
//////            }
//////            else
//////            {
//////
//////               cookie = nullptr;
//////
//////            }
//////
//////#endif
////
////   //         XNextEvent(pdisplay, &e);
////
////   if(!__x11_hook_process_event(pdisplaydata->display(), e, cookie))
////   {
////
////#if !defined(RASPBERRYPIOS)
////
////      if(!x11_process_event(pdisplaydata, e, cookie))
////
////#else
////
////         if(!x11_process_event(pdisplaydata, e))
////
////#endif
////      {
////
////
////      }
//
//
