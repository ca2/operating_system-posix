#include "framework.h"
#include "acme/constant/id.h"
#include "_.h"
#include "gdk.h"
#include "acme/operating_system/xcb/_xcb.h"
#include <gio/gio.h>
#include <gtk/gtk.h>
#include <glib.h>


bool xcb_message_loop_step();


gboolean gtk_quit_callback(gpointer data);


void __copy(::color & color, const GdkRGBA & rgba)
{

   color.set(rgba.red, rgba.green, rgba.blue, rgba.alpha);

}

void __gtk_style_context_get_color(GtkStyleContext *context, GtkStateFlags state, const char * pszProperty, ::color & color)
{

   GdkRGBA * prgba = nullptr;

   gtk_style_context_get (context, state, pszProperty, &prgba, NULL);

   __copy(color, *prgba);

   gdk_rgba_free (prgba);

}


namespace node_gnome
{

   ::boolean g_bitLastDarkMode;

   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey);

   CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme);

   bool gsettings_get(string & str, const char * pszSchema, const char * pszKey)
   {

      char * psz = gsettings_get_malloc(pszSchema, pszKey);

      if(psz == nullptr)
      {

         return false;

      }

      try
      {

         str = psz;

      }
      catch(...)
      {

      }

      try
      {

         ::free(psz);

      }
      catch(...)
      {

      }

      return true;

   }


   bool g_bGInitialized = false;


   pthread_mutex_t g_mutexG;


   bool aaa_gsettings_set(const char * pszSchema, const char * pszKey, const char * pszValue)
   {

      if(pszSchema == nullptr)
      {

         return false;

      }

      if(pszKey == nullptr)
      {

         return false;

      }

      if(pszValue == nullptr)
      {

         return false;

      }

      if(!os_defer_init_gtk())
      {

         return false;

      }

      GSettings *settings = g_settings_new(pszSchema);

      if(settings == nullptr)
      {

         return false;

      }

      gboolean bOk = g_settings_set_string(settings, pszKey, pszValue);

      if (settings != nullptr)
      {

         g_object_unref (settings);

      }

      return bOk;

   }


   bool gsettings_sync()
   {

      if(!os_defer_init_gtk())
      {

         return false;

      }

      g_settings_sync ();

      return true;

   }


   char * gsettings_get_malloc(const char * pszSchema, const char * pszKey)
   {

      if(pszSchema == nullptr)
      {

         return nullptr;

      }

      if(pszKey == nullptr)
      {

         return nullptr;

      }

      if(!os_defer_init_gtk())
      {

         return nullptr;

      }

      GSettings *settings = g_settings_new(pszSchema);

      if(settings == nullptr)
      {

         return nullptr;

      }

      gchar * pgchar = g_settings_get_string (settings, pszKey);

      if(pgchar == nullptr)
      {

         g_object_unref (settings);

         return nullptr;

      }

      char * psz = strdup(pgchar);

      g_free (pgchar);

      g_object_unref (settings);

      return psz;

   }


   void wallpaper_change_notification (GSettings * settings, const gchar * key, gpointer data)
   {

      System.process_subject(id_wallpaper_change);

   }


   GAction * g_pactionWallpaper = nullptr;


   bool g_enable_wallpaper_change_notification(const char * pszSchema, const char * pszKey)
   {

      if(!g_bGInitialized)
      {

         return false;

      }

      pmutex_lock lock(&g_mutexG);

      if(g_pactionWallpaper != nullptr)
      {

         return true;

      }

      GSettings * settings = g_settings_new(pszSchema);

      if(settings == nullptr)
      {

         return false;

      }

      g_pactionWallpaper = g_settings_create_action (settings, pszKey);

      g_object_unref (settings);

      g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK (wallpaper_change_notification), nullptr);

      return true;

   }


   void g_defer_init()
   {

      if(g_bGInitialized)
      {

         return;

      }

      g_bGInitialized = true;

      pthread_mutex_init(&g_mutexG, nullptr);

   }


   void g_defer_term()
   {

      if(!g_bGInitialized)
      {

         return;

      }

      g_bGInitialized = false;

      if(g_pactionWallpaper != nullptr)
      {

         g_object_unref(g_pactionWallpaper);

         g_pactionWallpaper = nullptr;

      }

      pthread_mutex_destroy(&g_mutexG);

   }






   //void os_calc_user_theme()
   //{

//      string strTheme = _os_calc_user_theme();
//
//      if(System.m_strOsUserTheme != strTheme)
//      {
//
//         System.m_strOsUserTheme = strTheme;
//
//         System.set_modified(id_os_user_theme);
//
//         xcb_kick_idle();
//
//      }
//
//   }


   bool g_bInitializedUserTheme = false;

   string _os_get_user_theme()
   {

      if(!g_bInitializedUserTheme)
      {

         g_bInitializedUserTheme = true;

         System.start_subject_handling(id_os_user_theme);

      }

      // https://ubuntuforums.org/showthread.php?t=2140488
      // gsettings set org.gnome.desktop.interface gtk-theme your_theme

      // indirect wall-changer sourceforge.net contribution

      string strTheme;

      bool bOk = false;

      auto edesktop = System.get_edesktop();

      switch (edesktop)
      {

      case ::user::e_desktop_gnome:
      case ::user::e_desktop_ubuntu_gnome:
      case ::user::e_desktop_unity_gnome:

         bOk = gsettings_get(strTheme, "org.gnome.desktop.interface", "gtk-theme");

         break;

      case ::user::e_desktop_mate:

         bOk = gsettings_get(strTheme, "org.mate.background", "picture-filename");

         break;

      case ::user::e_desktop_lxde:

         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

         break;

      case ::user::e_desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

      }

      //break;

      default:

         output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         //return "";

      }

      return strTheme;

   }


   string get_wallpaper(::index iIndex)
   {

      // wall-changer sourceforge.net contribution

      bool bOk = false;

      string strWallpaper;

      auto edesktop = System.get_edesktop();

      switch (edesktop)
      {

      case ::user::e_desktop_gnome:
      case ::user::e_desktop_ubuntu_gnome:
      case ::user::e_desktop_unity_gnome:

         bOk = gsettings_get(strWallpaper, "org.gnome.desktop.background", "picture-uri");

         break;

      case ::user::e_desktop_mate:

         bOk = gsettings_get(strWallpaper, "org.mate.background", "picture-filename");

         break;

      case ::user::e_desktop_lxde:

         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

         break;

      case ::user::e_desktop_xfce:
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

      }

      //break;

      default:

         output_debug_string("Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
         //return "";

      }

      strWallpaper.begins_eat_ci("file://");

      return strWallpaper;

   }


   ::user::os_theme_colors * new_os_theme_colors(string strTheme)
   {

      auto pthemecolors = memory_new ::user::os_theme_colors;

      GtkStyleContext *pstylecontext = gtk_style_context_new();

      GtkCssProvider *pprovider = gtk_css_provider_get_named(strTheme, nullptr);

      gtk_style_context_add_provider(pstylecontext, GTK_STYLE_PROVIDER(pprovider), GTK_STYLE_PROVIDER_PRIORITY_USER);

      {

         GtkWidget *pdialog = gtk_dialog_new();

         GtkWidgetPath *ppath = gtk_widget_get_path(pdialog);

         gtk_style_context_set_path(pstylecontext, ppath);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_NORMAL,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorBack);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_NORMAL,
                 GTK_STYLE_PROPERTY_COLOR,
                 pthemecolors->m_colorFore);

         gtk_widget_destroy(pdialog);

      }

      {

         GtkWidget *pbutton = gtk_button_new();

         GtkWidgetPath *ppath = gtk_widget_get_path(pbutton);

         gtk_style_context_set_path(pstylecontext, ppath);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_NORMAL,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorFace);

         double dAlpha = pthemecolors->m_colorFace.get_a_rate();

         if(dAlpha < 0.95)
         {

            pthemecolors->m_colorFace.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_PRELIGHT,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorFaceHover);

         dAlpha = pthemecolors->m_colorFaceHover.get_a_rate();

         if(dAlpha < 0.95)
         {

            pthemecolors->m_colorFaceHover.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_ACTIVE,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorFacePress);

         dAlpha = pthemecolors->m_colorFacePress.get_a_rate();

         if(dAlpha < 0.95)
         {

            pthemecolors->m_colorFacePress.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_NORMAL,
                 GTK_STYLE_PROPERTY_COLOR,
                 pthemecolors->m_colorButton);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_PRELIGHT,
                 GTK_STYLE_PROPERTY_COLOR,
                 pthemecolors->m_colorButtonHover);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_NORMAL,
                 GTK_STYLE_PROPERTY_BORDER_COLOR,
                 pthemecolors->m_colorBorder);


//         pthemecolors->m_colorBorderHover4 = pthemecolors->m_colorBorderHover;
//
//         pthemecolors->m_colorBorderHover4.blend(pthemecolors->m_colorBack, 0.8);


         gtk_widget_destroy(pbutton);

      }

      {

         GtkWidget *pwidget = gtk_list_box_row_new();

         GtkWidgetPath *ppath = gtk_widget_get_path(pwidget);

         gtk_style_context_set_path(pstylecontext, ppath);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_SELECTED,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorBorderHover);

         pthemecolors->m_colorBorderPress = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover1 = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover1.blend(pthemecolors->m_colorBack, 0.3);

         pthemecolors->m_colorBorderHover2 = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover2.blend(pthemecolors->m_colorBack, 0.6);

         pthemecolors->m_colorBorderHover3 = pthemecolors->m_colorBorderHover;

         pthemecolors->m_colorBorderHover3.blend(pthemecolors->m_colorBack, 0.9);

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_SELECTED,
                 GTK_STYLE_PROPERTY_COLOR,
                 pthemecolors->m_colorButtonPress);

         gtk_widget_destroy(pwidget);

      }

      return pthemecolors;

   }


   CLASS_DECL_ACME void _os_process_user_theme(string strTheme)
   {

      _os_process_user_theme_color(strTheme);

      os_calc_dark_mode();

   }


   CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme)
   {

      auto pthemecolors = new_os_theme_colors(strTheme);

      auto pthemecolorsOld = ::user::os_get_theme_colors();

      if(!pthemecolorsOld || memcmp(pthemecolors, pthemecolorsOld, sizeof(::user::os_theme_colors)))
      {

         ::user::os_set_theme_colors(pthemecolors);

//         auto ptopic = System.topic(id_os_user_theme);
//
//         ptopic->m_atom = id_deliver;
//
//         System.process(ptopic);

      }
      else
      {

         ::acme::del(pthemecolors);

      }

   }



   bool _os_calc_dark_mode()
   {

      auto pthemecolors = ::user::os_get_theme_colors();

      if(!pthemecolors)
      {

         string strTheme = _os_get_user_theme();

         pthemecolors = new_os_theme_colors(strTheme);

         ::user::os_set_theme_colors(pthemecolors);

      }

      auto dLuminance = pthemecolors->m_colorBack.get_luminance();

      return dLuminance < 0.5;

   }


} // namespace user





#ifdef LINUX
static void
log_handler (const gchar   *log_domain,
             GLogLevelFlags log_level,
             const gchar   *message,
             gpointer       user_data)
{
   g_log_default_handler (log_domain, log_level, message, user_data);

   g_on_error_query (nullptr);
}


#endif




gboolean xcb_source_func(gpointer)
{

   xcb_message_loop_step();

   return TRUE;

}


void xcb_add_idle_source()
{

   gdk_threads_add_idle(&xcb_source_func, nullptr);

}


bool xcb_message_handler(xcb_generic_event_t * pevent);


GdkFilterReturn xcb_event_func(GdkXEvent *xevent, GdkEvent *event, gpointer  data)
{

   xcb_generic_event_t * pevent = (xcb_generic_event_t *) xevent;

   if(xcb_message_handler(pevent))
   {

      //return GDK_FILTER_REMOVE;

   }

   return GDK_FILTER_CONTINUE;

}








