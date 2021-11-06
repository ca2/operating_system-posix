#include "framework.h"
#include "acme/id.h"
#include "_.h"
#include "gdk.h"
//#include "acme/node/operating_system/x11/_x11.h"
//#include <gio/gio.h>
//#include <gtk/gtk.h>
//#include <glib.h>


bool x11_message_loop_step();


//gboolean gtk_quit_callback(gpointer data);
//
//
//void __copy(::color & color, const GdkRGBA & rgba)
//{
//
//   color.set(rgba.red, rgba.green, rgba.blue, rgba.alpha);
//
//}

//void __gtk_style_context_get_color(GtkStyleContext *context, GtkStateFlags state, const char * pszProperty, ::color & color)
//{
//
//   GdkRGBA * prgba = nullptr;
//
//   gtk_style_context_get (context, state, pszProperty, &prgba, NULL);
//
//   __copy(color, *prgba);
//
//   gdk_rgba_free (prgba);
//
//}
//

namespace node_kde{

//   ::boolean g_bitLastDarkMode;
//
//   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);
//
//   CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme);
//
//   bool gsettings_get(string & str, const char * pszSchema, const char * pszKey)
//   {
//
//      char * psz = gsettings_get_malloc(pszSchema, pszKey);
//
//      if(psz == nullptr)
//      {
//
//         return false;
//
//      }
//
//      try
//      {
//
//         str = psz;
//
//      }
//      catch(...)
//      {
//
//      }
//
//      try
//      {
//
//         ::free(psz);
//
//      }
//      catch(...)
//      {
//
//      }
//
//      return true;
//
//   }
//
//
//   bool g_bGInitialized = false;
//
//
//   pthread_mutex_t g_mutexG;
//
//
//   bool gsettings_set(const char * pszSchema, const char * pszKey, const char * pszValue)
//   {
//
//      if(pszSchema == nullptr)
//      {
//
//         return false;
//
//      }
//
//      if(pszKey == nullptr)
//      {
//
//         return false;
//
//      }
//
//      if(pszValue == nullptr)
//      {
//
//         return false;
//
//      }
//
////      if(!os_defer_init_gtk())
////      {
////
////         return false;
////
////      }
////
////      GSettings *settings = g_settings_new(pszSchema);
////
////      if(settings == nullptr)
////      {
////
////         return false;
////
////      }
////
////      gboolean bOk = g_settings_set_string(settings, pszKey, pszValue);
////
////      if (settings != nullptr)
////      {
////
////         g_object_unref (settings);
////
////      }
//
//bool bOk = true;
//
//      return bOk;
//
//   }
//
//
////   bool gsettings_sync()
////   {
////
//////      if(!os_defer_init_gtk())
//////      {
//////
//////         return false;
//////
//////      }
//////
//////      g_settings_sync ();
////
////      return true;
////
////   }
//
//
////   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey)
////   {
////
////      if(pszSchema == nullptr)
////      {
////
////         return nullptr;
////
////      }
////
////      if(pszKey == nullptr)
////      {
////
////         return nullptr;
////
////      }
////
////      if(!os_defer_init_gtk())
////      {
////
////         return nullptr;
////
////      }
////
////      GSettings *settings = g_settings_new(pszSchema);
////
////      if(settings == nullptr)
////      {
////
////         return nullptr;
////
////      }
////
////      gchar * pgchar = g_settings_get_string (settings, pszKey);
////
////      if(pgchar == nullptr)
////      {
////
////         g_object_unref (settings);
////
////         return nullptr;
////
////      }
////
////      char * psz = strdup(pgchar);
////
////      g_free (pgchar);
////
////      g_object_unref (settings);
////
////      return psz;
////
////   }
////
////
////   void wallpaper_change_notification (GSettings * settings, const gchar * key, gpointer data)
////   {
////
////      System.process_subject(id_wallpaper_change);
////
////   }
////
////
////   GAction * g_pactionWallpaper = nullptr;
////
////
////   bool g_enable_wallpaper_change_notification(const char * pszSchema, const char * pszKey)
////   {
////
////      if(!g_bGInitialized)
////      {
////
////         return false;
////
////      }
////
////      pmutex_lock lock(&g_mutexG);
////
////      if(g_pactionWallpaper != nullptr)
////      {
////
////         return true;
////
////      }
////
////      GSettings * settings = g_settings_new(pszSchema);
////
////      if(settings == nullptr)
////      {
////
////         return false;
////
////      }
////
////      g_pactionWallpaper = g_settings_create_action (settings, pszKey);
////
////      g_object_unref (settings);
////
////      g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK (wallpaper_change_notification), nullptr);
////
////      return true;
////
////   }
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
////      if(g_pactionWallpaper != nullptr)
////      {
////
////         g_object_unref(g_pactionWallpaper);
////
////         g_pactionWallpaper = nullptr;
////
////      }
//
//      pthread_mutex_destroy(&g_mutexG);
//
//   }
//
//
//
//
//
//
//   //void os_calc_user_theme()
//   //{
//
////      string strTheme = _os_calc_user_theme();
////
////      if(System.m_strOsUserTheme != strTheme)
////      {
////
////         System.m_strOsUserTheme = strTheme;
////
////         System.set_modified(id_os_user_theme);
////
////         x11_kick_idle();
////
////      }
////
////   }
//
//
////   bool g_bInitializedUserTheme = false;
////
////   string _os_get_user_theme()
////   {
////
////      if(!g_bInitializedUserTheme)
////      {
////
////         g_bInitializedUserTheme = true;
////
////         System->start_subject_handling(id_os_user_theme);
////
////      }
////
////      // https://ubuntuforums.org/showthread.php?t=2140488
////      // gsettings set org.gnome.desktop.interface gtk-theme your_theme
////
////      // indirect wall-changer sourceforge.net contribution
////
////      string strTheme;
////
////      bool bOk = false;
////
////      auto edesktop = System->get_edesktop();
////
////      switch (edesktop)
////      {
////
////      case ::user::e_desktop_gnome:
////      case ::user::e_desktop_ubuntu_gnome:
////      case ::user::e_desktop_unity_gnome:
////
////         bOk = gsettings_get(strTheme, "org.gnome.desktop.interface", "gtk-theme");
////
////         break;
////
////      case ::user::e_desktop_mate:
////
////         bOk = gsettings_get(strTheme, "org.mate.background", "picture-filename");
////
////         break;
////
////      case ::user::e_desktop_lxde:
////
////         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
////
////         break;
////
////      case ::user::e_desktop_xfce:
////      {
////         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
////         //          if(entry.contains("image-path") || entry.contains("last-image")){
////         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
////         //      }
////         //}
////
////      }
////
////      //break;
////
////      default:
////
////         output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
////         //return "";
////
////      }
////
////      return strTheme;
////
////   }
//
//
////   string get_wallpaper(::index iIndex)
////   {
////
////      // wall-changer sourceforge.net contribution
////
////      bool bOk = false;
////
////      string strWallpaper;
////
////      auto edesktop = System->get_edesktop();
////
////      switch (edesktop)
////      {
////
////      case ::user::e_desktop_gnome:
////      case ::user::e_desktop_ubuntu_gnome:
////      case ::user::e_desktop_unity_gnome:
////
////         bOk = gsettings_get(strWallpaper, "org.gnome.desktop.background", "picture-uri");
////
////         break;
////
////      case ::user::e_desktop_mate:
////
////         bOk = gsettings_get(strWallpaper, "org.mate.background", "picture-filename");
////
////         break;
////
////      case ::user::e_desktop_lxde:
////
////         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
////
////         break;
////
////      case ::user::e_desktop_xfce:
////      {
////         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
////         //          if(entry.contains("image-path") || entry.contains("last-image")){
////         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
////         //      }
////         //}
////
////      }
////
////      //break;
////
////      default:
////
////         output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
////         //return "";
////
////      }
////
////      ::str::begins_eat_ci(strWallpaper, "file://");
////
////      return strWallpaper;
////
////   }
//
//
////   CLASS_DECL_ACME void _os_process_user_theme(string strTheme)
////   {
////
////      _os_process_user_theme_color(strTheme);
////
////      Node->os_calc_user_dark_mode();
////
////   }
////
////
////   CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme)
////   {
////
////      auto pnode = Node;
////
////      auto pnodekde = dynamic_cast < ::node_kde::node * >(pnode);
////
////      auto pthemecolors = pnodekde->new_os_theme_colors();
////
////      auto pthemecolorsOld = ::user::os_get_theme_colors();
////
////      if(!pthemecolorsOld || memcmp(pthemecolors, pthemecolorsOld, sizeof(::os_theme_colors)))
////      {
////
////         ::user::os_set_theme_colors(pthemecolors);
////
////      }
////      else
////      {
////
////         ::acme::del(pthemecolors);
////
////      }
////
////   }



} // namespace user



