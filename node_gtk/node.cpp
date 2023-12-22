//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/constant/id.h"
#include "acme/operating_system/ansi/pmutex_lock.h"
#include "acme/operating_system/parallelization.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/handler/topic.h"
#include "acme/operating_system/summary.h"
#include "acme/user/user/os_theme_colors.h"
#include "acme/user/user/theme_colors.h"
#include "apex/input/input.h"
#include "apex/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "windowing_x11/windowing_x11.h"
#include "aura/windowing/windowing.h"
#include "aura_posix/x11/windowing.h"


#include <gio/gio.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <gdk/gdkdisplay.h>
#include <gdk/gdkwayland.h>
#include <gdk/gdkx.h>


bool aaa_x11_message_loop_step();


gboolean gtk_quit_callback(gpointer data);

void gtk_defer_do_main_tasks();

//void gio_open_url(const char * pszUrl);
///int gtk_launch (const char * pszDesktopFileTitle);


void copy(::color::color &color, const GdkRGBA &rgba)
{

   color.set(rgba.red, rgba.green, rgba.blue, rgba.alpha);

}


bool __gtk_style_context_get_color(GtkStyleContext *context, GtkStateFlags state, const char *pszProperty, ::color::color & color)
{

   GdkRGBA *prgba = nullptr;

   gtk_style_context_get(context, state, pszProperty, &prgba, NULL);

   copy(color, *prgba);

   gdk_rgba_free(prgba);

   return true;

}


void x11_add_idle_source(::node_gtk::node *pnode);


void gtk_settings_gtk_theme_name_callback(GObject *object, GParamSpec *pspec, gpointer data)
{

   node_gtk::node *pnode = (node_gtk::node *) data;

   if (!pnode)
   {

      return;

   }

   gchar *theme_name = nullptr;

   g_object_get(pnode->m_pGtkSettingsDefault, "gtk-theme-name", &theme_name, NULL);

   string strTheme = theme_name;

   ::acme::get()->platform()->informationf("gtk_settings_gtk_theme_name_callback: \"" + strTheme + "\"\n");

   g_free(theme_name);

//   pnode->fork([pnode, strTheme]()
//               {

   pnode->_set_os_user_theme(strTheme);

//                  ::preempt(400_ms);
//
//                  pnode->_apply_os_user_theme(strTheme);
//
//                  //_os_user_theme(strTheme);
//
//               });

}


void gtk_settings_gtk_icon_theme_name_callback(GObject *object, GParamSpec *pspec, gpointer data)
{

   node_gtk::node *pnode = (node_gtk::node *) data;

   if (!pnode)
   {

      return;

   }

   gchar *icon_theme_name = nullptr;

   g_object_get(pnode->m_pGtkSettingsDefault, "gtk-icon-theme-name", &icon_theme_name, NULL);

   string strIconTheme = icon_theme_name;

   ::acme::get()->platform()->informationf("gtk_settings_gtk_icon_theme_name_callback: \"" + strIconTheme + "\"\n");

   g_free(icon_theme_name);

//   pnode->fork([pnode, strTheme]()
//               {

   pnode->_set_os_user_icon_theme(strIconTheme);

//                  ::preempt(400_ms);
//
//                  pnode->_apply_os_user_theme(strTheme);
//
//                  //_os_user_theme(strTheme);
//
//               });

}


//void aaa_x11_add_idle_source();


void x11_add_filter();


//void x11_main();


//::particle *user_synchronization();


gboolean node_gtk_source_func(gpointer pUserdata);


namespace node_gtk
{

   class appindicator;

   void appindicator_destroy(appindicator *pindicator);

} // namespace node_gtk



void os_post_quit();

void apex_application_run(const char *pszAppName, const char *pszProgName);

namespace node_gtk
{


   CLASS_DECL_ACME void _os_process_user_theme(string strTheme);


   node::node()
   {

      m_pNodeGtk = this;

      defer_initialize_x11();

      m_pGtkSettingsDefault = nullptr;

      m_pgdkapplaunchcontext = nullptr;

   }


   node::~node()
   {

      m_pGtkSettingsDefault = nullptr;

      for (auto &pair: m_mapGDesktopAppInfo)
      {

         g_object_unref(pair.m_element2);

      }

      if (m_pgdkapplaunchcontext)
      {

         g_object_unref(m_pgdkapplaunchcontext);

      }

   }


   int node::node_init_check(int *pi, char ***ppz)
   {

      if (!os_defer_init_gtk(this))
      {

         return 0;

      }

      return 1;

   }


   void node::defer_notify_startup_complete()
   {

      auto psystem = system()->m_papexsystem;

      string strApplicationServerName = psystem->get_application_server_name();

      gdk_notify_startup_complete_with_id(strApplicationServerName);

      gdk_notify_startup_complete();

   }


   void node::on_start_system()
   {

      system()->on_branch_system_from_main_thread_startup();

   }


   void node::on_system_main()
   {

      //   ::e_status estatus = psystem->begin_synch();
      //
      //   if(!estatus)
      //   {
      //
      //      return estatus;
      //
      //   }
      //

//      const char *pszName = m_XstrAppId;

//       g_set_application_name(pszName);

//      const char *pszPrgName = m_strProgName;

//      g_set_prgname(pszPrgName);

      //auto idle_source = g_idle_source_new();

      //g_source_set_callback(idle_source, &linux_start_system, (::apex::system *) system(), nullptr);

      //g_source_attach(idle_source, g_main_context_default());

      //int c = 2;

      //const char * argv[]={"app", "--g-fatal-warnings"};

#if !defined(__SANITIZE_ADDRESS__)

      {

         node_init_check(platform()->get_pargc(),
                         platform()->get_pargv());

      }

#endif

//      if (m_bUser)
//      {
//
//         estatus = defer_initialize_x11();
//
//         if(!estatus)
//         {
//
//            return estatus;
//
//         }
//
//      }


//
//      auto psystem = system();
//
//      auto pnode = psystem->node();
//
//      m_pcontext->branch(pnode);
//
//      return ::success;

      auto psystem = system()->m_papexsystem;

      if (psystem->application()->m_bGtkApp)
      {

         //apex_application_run(psystem->m_strAppId, psystem->m_strProgName);

      }
      else
      {

         information() << "node_gtk::system_main going to user_post";

         user_post([this]()
                   {

                      // This seems not to work with "foreign" windows
                      // (X11 windows not created with Gdk)
                      //x11_add_filter();

                      information() << "node_gtk::system_main on user_post";


                      auto pgtksettingsDefault = gtk_settings_get_default();

                      if (pgtksettingsDefault)
                      {

                         m_pGtkSettingsDefault = G_OBJECT(pgtksettingsDefault);

                         g_object_ref (m_pGtkSettingsDefault);

                         {

                            gchar *theme_name = nullptr;

                            g_object_get(m_pGtkSettingsDefault, "gtk-theme-name", &theme_name, NULL);

                            m_strTheme = theme_name;

                            g_free(theme_name);

                         }

                         {

                            gchar *icon_theme_name = nullptr;

                            g_object_get(m_pGtkSettingsDefault, "gtk-icon-theme-name", &icon_theme_name, NULL);

                            m_strIconTheme = icon_theme_name;

                            g_free(icon_theme_name);

                         }


                         auto preturnTheme = g_signal_connect_data(
                                 m_pGtkSettingsDefault,
                                 "notify::gtk-theme-name",
                                 //"gtk-private-changed",
                                 G_CALLBACK(gtk_settings_gtk_theme_name_callback),
                                 this,
                                 NULL,
                                 G_CONNECT_AFTER);

                         auto preturnIconTheme = g_signal_connect_data(
                                 m_pGtkSettingsDefault,
                                 "notify::gtk-icon-theme-name",
                                 //"gtk-private-changed",
                                 G_CALLBACK(gtk_settings_gtk_icon_theme_name_callback),
                                 this,
                                 NULL,
                                 G_CONNECT_AFTER);

                         //g_object_ref(preturn);

                         //printf("return %" PRIiPTR, preturn);

                         //printf("return %" PRIiPTR, preturn);

                      }

                      x11_add_idle_source(this);

                      auto psystem = system()->m_papexsystem;

                      psystem->defer_post_initial_request();

                   });


         //x11_add_filter();
//
//         System.fork([this]()
//         {
//
//            //m_pwindowing->windowing_main();
//
//         });

         //aaa_x11_add_idle_source(this);

         //aaa_x11_add_idle_source(this);

         gtk_main();

         //aaa_x11_main();

      }

      //return ::success;

   }


   void node::start_node()
   {


      throw ::exception(error_failed, "deprecated");
      //
      //::parallelization::post_quit_and_wait(get_context_system(), one_minute());

      //return ::success;

   }


   void node::initialize(::particle *pparticle)
   {

      ::node_gtk::g_defer_init();

      //return ::success;

   }


//   void node::fetch_user_color()
//   {
//
//      ::aura::posix::node::fetch_user_color();
//
//   }


   bool node::windowing_message_loop_step()
   {

      //information() << "node::windowing_message_loop_step";

      auto psession = session();

      if (::is_null(psession))
      {

         //information() << "node::windowing_message_loop_step NO SESSION";

         return true;

      }

      auto paurasession = psession->m_paurasession;

      if (::is_null(paurasession))
      {

         //information() << "node::windowing_message_loop_step NO AURA SESSION";

         return true;

      }

      auto puser = paurasession->user();

      if (::is_null(puser))
      {

         //information() << "node::windowing_message_loop_step NO SESSION USER";

         return true;

      }

      auto pwindowing = puser->windowing();

      if (::is_null(pwindowing))
      {

         //information() << "node::windowing_message_loop_step NO USER WINDOWING";

         return true;

      }

      //information() << "node::windowing_message_loop_step at windowing";

      bool bRet = pwindowing->message_loop_step();

      return bRet;

   }


   string node::os_get_user_theme()
   {

      return m_strTheme;

   }


//   string node::_on_user_theme_changed()
//   {
//
//      system()->m_papexsystem->signal(id_os_user_theme);
//
//   }

   void node::_dark_mode()
   {

      information() << "::node_gtk::node::_dark_mode";

      if(gsettings_schema_exists("org.gnome.desktop.interface"))
      {

         information() << "org.gnome.desktop.interface exists";

         if(gsettings_schema_contains_key("org.gnome.desktop.interface", "color-scheme"))
         {

            information() << "org.gnome.desktop.interface contains \"color-scheme\"";

            ::string strColorScheme;

            if (gsettings_get(strColorScheme, "org.gnome.desktop.interface", "color-scheme"))
            {

               information() << "color-scheme=\"" + strColorScheme + "\"";

               strColorScheme.trim();

               if (strColorScheme.case_insensitive_contains("dark"))
               {

                  m_bDarkMode = true;

               }
               else
               {

                  m_bDarkMode = false;

               }

            }
            else
            {

               m_bDarkMode = false;

            }

         }
         else if(gsettings_schema_contains_key("org.gnome.desktop.interface", "gtk-theme"))
         {

            information() << "org.gnome.desktop.interface schema contains \"gtk-theme\"";

            ::string strGtkTheme;

            if (gsettings_get(strGtkTheme, "org.gnome.desktop.interface", "gtk-theme"))
            {

               information() << "gtk-theme=\"" + strGtkTheme + "\"";

               ::os_theme_colors * posthemecolor = _new_os_theme_colors(strGtkTheme);

               auto dLuminance = posthemecolor->m_colorBack.get_luminance();

               informationf("luminance=%0.2f", dLuminance);

               m_bDarkMode = dLuminance < 0.5;

            }
            else
            {

               m_bDarkMode = false;

            }

         }

      }

   }


   bool node::dark_mode() const
   {

      ((node*)this)->_dark_mode();

      return ::aura_posix::node::dark_mode();

   }


   void node::set_dark_mode(bool bDarkMode)
   {

      post_procedure([this, bDarkMode]()
                     {

      if(bDarkMode)
      {

         gsettings_set("org.gnome.desktop.interface", "color-scheme", "prefer-dark");

      }
      else
      {

         auto psummary = operating_system_summary();

         if(psummary->m_strDistro.case_insensitive_equals("ubuntu"))
         {

            gsettings_set("org.gnome.desktop.interface", "color-scheme", "default");

         }
         else
         {

            gsettings_set("org.gnome.desktop.interface", "color-scheme", "prefer-light");

         }

      }

      _os_set_user_theme(m_strTheme);

      _os_set_user_icon_theme(m_strIconTheme);

      ::aura_posix::node::set_dark_mode(bDarkMode);

      });

   }


   void node::os_set_user_theme(const ::string &strUserTheme)
   {

      //auto estatus =
      //
      //
      _os_set_user_theme(strUserTheme);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   ::e_status node::_os_set_user_theme(const ::string &strUserTheme)
   {

      // https://ubuntuforums.org/showthread.php?t=2140488
      // gsettings set org.gnome.desktop.interface gtk-theme your_theme

      // indirect wall-changer sourceforge.net contribution

      auto psystem = system()->m_papexsystem;

      auto pnode = psystem->node();

      auto edesktop = pnode->get_edesktop();

      if (edesktop & ::user::e_desktop_gnome)
      {

         bool bOk1 = gsettings_set("org.gnome.desktop.interface", "gtk-theme", strUserTheme).ok();

         bool bOk2 = true;

         //if(::file::system_short_name().case_insensitive_contains("manjaro"))
         {

            bOk2 = gsettings_set("org.gnome.desktop.wm.preferences", "theme", strUserTheme).ok();

         }

         sleep(300_ms);

         ::node_gtk::gsettings_sync();

         sleep(300_ms);

         if (!bOk1 || !bOk2)
         {

            return error_failed;

         }

      }
      else if (edesktop & ::user::e_desktop_mate)
      {

         //return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);

      }
      else if (edesktop & ::user::e_desktop_lxde)
      {


         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

      }
      else if (edesktop & ::user::e_desktop_xfce)
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

         warning() <<"Failed to set operating system theme wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";

         return error_failed;

      }

      return ::success;

   }


   ::e_status node::_os_set_user_icon_theme(const ::string &strUserIconTheme)
   {

      // https://ubuntuforums.org/showthread.php?t=2140488
      // gsettings set org.gnome.desktop.interface gtk-theme your_theme

      // indirect wall-changer sourceforge.net contribution

      auto psystem = system()->m_papexsystem;

      auto pnode = psystem->node();

      auto edesktop = pnode->get_edesktop();

      if (edesktop & ::user::e_desktop_gnome)
      {

         bool bOk1 = gsettings_set("org.gnome.desktop.interface", "icon-theme", strUserIconTheme).ok();

         //bool bOk2 = true;

//         //if(::file::system_short_name().case_insensitive_contains("manjaro"))
//         {
//
//            bOk2 = gsettings_set("org.gnome.desktop.wm.preferences", "theme", strUserTheme);
//
//         }

         sleep(300_ms);

         ::node_gtk::gsettings_sync();

         sleep(300_ms);

         //if (!bOk1 || !bOk2)
         if (!bOk1)
         {

            return error_failed;

         }

      }
      else if (edesktop & ::user::e_desktop_mate)
      {

         //return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);

      }
      else if (edesktop & ::user::e_desktop_lxde)
      {


         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

      }
      else if (edesktop & ::user::e_desktop_xfce)
      {
         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
         //          if(entry.contains("image-path") || entry.contains("last-image")){
         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
         //      }
         //}

         warning() <<"Failed to set operating system theme wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";

         return error_failed;

      }

      return ::success;

   }


//   void node::os_process_user_theme(string strTheme)
//   {
//
//      _os_process_user_theme(strTheme);
//
//   }


   bool node::set_wallpaper(index iScreen, string strLocalImagePath)
   {

      // wall-changer sourceforge.net contribution

      auto psystem = system()->m_papexsystem;

      auto pnode = psystem->node();

      auto edesktop = pnode->get_edesktop();

      switch (edesktop)
      {

         case ::user::e_desktop_gnome:
         case ::user::e_desktop_ubuntu_gnome:
         case ::user::e_desktop_unity_gnome:

            return ::node_gtk::gsettings_set("org.gnome.desktop.background", "picture-uri",
                                             "file://" + strLocalImagePath).ok();

         case ::user::e_desktop_mate:

            return ::node_gtk::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath).ok();

         case ::user::e_desktop_lxde:

            call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);

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

            warning() <<"Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
            return false;

      }

      return true;

   }


   void node::enable_wallpaper_change_notification()
   {

      auto psystem = system()->m_papexsystem;

      auto pnode = psystem->node();

      auto edesktop = pnode->get_edesktop();

      switch (edesktop)
      {

         case ::user::e_desktop_gnome:
         case ::user::e_desktop_ubuntu_gnome:
         case ::user::e_desktop_unity_gnome:

            node_enable_wallpaper_change_notification(this, "org.gnome.desktop.background", "picture-uri");

            break;

         case ::user::e_desktop_mate:

            node_enable_wallpaper_change_notification(this, "org.mate.background", "picture-filename");

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

            break;
         default:

            warning() <<"Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
            //return "";

      }

   }


   string node::get_file_icon_path(const ::string &strPath, int iSize)
   {

      return ::node_gtk::g_get_file_icon_path(strPath, iSize);

   }


   string node::get_file_content_type(const ::string &strPath)
   {

      return ::node_gtk::g_get_file_content_type(strPath);

   }


   string node::get_wallpaper(index iScreen)
   {

      return "";

   }


   void node::user_post(const ::procedure &procedure)
   {

      gdk_branch(procedure);

   }


   void node::defer_do_main_tasks()
   {

      gtk_defer_do_main_tasks();

   }


   void node::user_post_quit()
   {

      ::os_post_quit();

   }


//   void * node::node_wrap_window(void * pvoidDisplay, i64 window)
//   {
//
//      Display * pdisplay = (Display *) pvoidDisplay;
//
//      GdkDisplay * pd = gdk_x11_lookup_xdisplay (pdisplay);
//
//      auto pwindow = gdk_x11_window_foreign_new_for_display(GDK_DISPLAY(pd), (Window) window);
//
//      return pwindow;
//
//   }

   bool node::should_launch_on_node(::topic *ptopic)
   {

      if (::is_null(ptopic))
      {

         return false;

      }

      if (ptopic->m_atom == id_operating_system_user_color_change)
      {

         return false;

      }

      return false;

   }


   bool node::launch_on_node(::topic *ptopic)
   {

      // TODO check if ptopic below is own topic or what else?
      ::pointer<::topic> ptopicHold = ptopic;

      user_post([ptopicHold]()
                {

                   auto ret = g_timeout_add(300, (GSourceFunc) &node_gtk_source_func, ptopicHold.m_p);

                   printf("ret %d", ret);

                   printf("ret %d", ret);

                   g_idle_add(&node_gtk_source_func, ptopicHold.m_p);

                });

      return true;

   }

//
//   int node::os_launch_uri(const ::string & strUri, char * pszError, int iBufferSize)
//   {
//
//      int iRet = gdk_launch_uri(strUri, pszError, iBufferSize);
//
//      return iRet;
//
//   }




   bool g_bInitializedUserTheme = false;

   string node::_os_get_user_theme()
   {

      if (!g_bInitializedUserTheme)
      {

         g_bInitializedUserTheme = true;

         //auto psystem = system()->m_papexsystem;

         //psystem->start_subject_handling(id_os_user_theme);

      }

      // https://ubuntuforums.org/showthread.php?t=2140488
      // gsettings set org.gnome.desktop.interface gtk-theme your_theme

      // indirect wall-changer sourceforge.net contribution

      string strTheme;

      bool bOk = false;

      auto psystem = system()->m_papexsystem;

      auto pnode = psystem->node();

      auto edesktop = pnode->get_edesktop();

      switch (edesktop)
      {

         case ::user::e_desktop_gnome:
         case ::user::e_desktop_ubuntu_gnome:
         case ::user::e_desktop_unity_gnome:

            bOk = gsettings_get(strTheme, "org.gnome.desktop.interface", "gtk-theme").ok();

            break;

         case ::user::e_desktop_mate:

            bOk = gsettings_get(strTheme, "org.mate.background", "picture-filename").ok();

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

            warningf(
                    "Failed to get user theme setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
            //return "";

      }

      return strTheme;

   }


   ::os_theme_colors *node::_new_os_theme_colors(string strTheme)
   {

      auto pthemecolors = __new< ::os_theme_colors >();

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

         double dAlpha = pthemecolors->m_colorFace.f64_opacity();

         if (dAlpha < 0.95)
         {

            pthemecolors->m_colorFace.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_PRELIGHT,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorFaceHover);

         dAlpha = pthemecolors->m_colorFaceHover.f64_opacity();

         if (dAlpha < 0.95)
         {

            pthemecolors->m_colorFaceHover.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);

         }

         __gtk_style_context_get_color(
                 pstylecontext,
                 GTK_STATE_FLAG_ACTIVE,
                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
                 pthemecolors->m_colorFacePress);

         dAlpha = pthemecolors->m_colorFacePress.f64_opacity();

         if (dAlpha < 0.95)
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


   void node::_set_os_theme_colors(::os_theme_colors *posthemecolors)
   {

      ::acme::get()->platform()->informationf("_set_os_theme_colors\n");

      ::user::os_set_theme_colors(posthemecolors);

      background_color(posthemecolors->m_colorBack);

   }


   void node::_set_os_user_theme(const ::scoped_string &strOsUserTheme)
   {

      m_strOsUserTheme = strOsUserTheme;

      if (!m_ptaskOsUserTheme)
      {

         m_ptaskOsUserTheme = fork([this]()
                                   {

                                      preempt(1_s);

                                      m_ptaskOsUserTheme = nullptr;

                                      _apply_os_user_theme();

                                   });

      }

   }



   void node::_set_os_user_icon_theme(const ::scoped_string &strOsUserIconTheme)
   {

      m_strOsUserIconTheme = strOsUserIconTheme;

      if (!m_ptaskOsUserTheme)
      {

         m_ptaskOsUserIconTheme = fork([this]()
                                   {

                                      preempt(1_s);

                                      m_ptaskOsUserIconTheme = nullptr;

                                      _apply_os_user_icon_theme();

                                   });

      }

   }



   void node::_apply_os_user_theme()
   {

      ::acme::get()->platform()->informationf("applying os user theme: \"" + m_strOsUserTheme + "\"\n");

      os_process_user_theme(m_strOsUserTheme);

   }


   void node::_apply_os_user_icon_theme()
   {

      ::acme::get()->platform()->informationf("applying os user icon theme: \"" + m_strOsUserIconTheme + "\"\n");

      os_process_user_icon_theme(m_strOsUserIconTheme);

   }


   void node::os_process_user_theme(string strOsTheme)
   {

      ::acme::get()->platform()->informationf(
              "os_process_user_theme: is strTheme(" + strOsTheme + ") same as m_strTheme(" + m_strTheme + ")\n");

      if (strOsTheme == m_strTheme)
      {

         ::acme::get()->platform()->informationf(
                 "os_process_user_theme: same theme as before [new(" + strOsTheme + ") - old(" + m_strTheme + ")]\n");

         return;

      }

      ::acme::get()->platform()->informationf(
              "os_process_user_theme: different theme [new(" + strOsTheme + ") - old(" + m_strTheme + ")]\n");

      m_strTheme = strOsTheme;

      ::acme::get()->platform()->informationf("os_process_user_theme m_strTheme = \"" + m_strTheme + "\"\n");

      try
      {

         system()->m_papexsystem->signal(id_operating_system_user_theme_change);

      }
      catch (...)
      {


      }

      if(!gsettings_schema_contains_key("org.gnome.desktop.interface", "color-scheme"))
      {

         _os_process_user_theme_color(m_strTheme);

         fetch_user_color();

      }

   }


   void node::os_process_user_icon_theme(string strOsIconTheme)
   {

      ::acme::get()->platform()->informationf(
              "os_process_user_icon_theme: is strIconTheme(" + strOsIconTheme + ") same as m_strIconTheme(" + m_strIconTheme + ")\n");

      if (strOsIconTheme == m_strIconTheme)
      {

         ::acme::get()->platform()->informationf(
                 "os_process_user_icon_theme: same theme as before [new(" + strOsIconTheme + ") - old(" + m_strIconTheme + ")]\n");

         return;

      }

      ::acme::get()->platform()->informationf(
              "os_process_user_icon_theme: different theme [new(" + strOsIconTheme + ") - old(" + m_strIconTheme + ")]\n");

      m_strIconTheme = strOsIconTheme;

      ::acme::get()->platform()->informationf("os_process_user_icon_theme m_strIconTheme = \"" + m_strIconTheme + "\"\n");

      try
      {

         system()->m_papexsystem->signal(id_operating_system_user_icon_theme_change);

      }
      catch (...)
      {


      }

//      if(!gsettings_schema_contains_key("org.gnome.desktop.interface", "color-scheme"))
//      {
//
//         _os_process_user_theme_color(m_strTheme);
//
//         fetch_user_color();
//
//      }

   }


   void node::_os_process_user_theme_color(string strTheme)
   {

      auto pthemecolors = _new_os_theme_colors(strTheme);

      auto pthemecolorsOld = ::user::os_get_theme_colors();

      if (!pthemecolorsOld || memcmp(pthemecolors, pthemecolorsOld, sizeof(::os_theme_colors)))
      {

         _set_os_theme_colors(pthemecolors);

         //system()->m_papexsystem->signal(id_operating_system_user_color_change);

      }
      else
      {

         ::acme::del(pthemecolors);

      }

   }


   void node::fetch_user_color()
   {

      _dark_mode();

//      auto pthemecolors = ::user::os_get_theme_colors();
//
//      if (!pthemecolors)
//      {
//
//         string strTheme = _os_get_user_theme();
//
//         information() << "node::fetch_user_color _os_get_user_theme(): " << strTheme;
//
//         pthemecolors = _new_os_theme_colors(strTheme);
//
//         _set_os_theme_colors(pthemecolors);
//
//      }

   }


   bool node::is_branch_current() const
   {

      return current_itask() == main_user_itask();

   }


   int node::os_launch_uri(const ::string &strUri, char *pszError, int iBufferSize)
   {

      int iRet = gdk_launch_uri(strUri, pszError, iBufferSize);

      return iRet;

   }


   void node::shell_launch(const ::string &strAppId)
   {

      string strDesktopFileTitle(strAppId);

      strDesktopFileTitle.find_replace("/", ".");

      ::file::path pathDesktop;

      pathDesktop = acmedirectory()->home() / ".local/share/applications" / (strDesktopFileTitle + ".desktop");

      user_post([this, pathDesktop]()
                        {

                           GError *pgerror = NULL;
                           GDesktopAppInfo *pgdesktopappinfo;
                           GList *plistFiles = NULL;

                           pgdesktopappinfo = g_desktop_app_info_new_from_filename(pathDesktop);

                           if (!pgdesktopappinfo)
                           {

                              throw exception(error_failed);

                           }

                           m_mapGDesktopAppInfo[pathDesktop] = pgdesktopappinfo;

                           if (!m_pgdkapplaunchcontext)
                           {

                              m_pgdkapplaunchcontext = gdk_display_get_app_launch_context(gdk_display_get_default());

                           }

                           if (!g_app_info_launch(G_APP_INFO(pgdesktopappinfo), plistFiles,
                                                  G_APP_LAUNCH_CONTEXT(m_pgdkapplaunchcontext), &pgerror))
                           {

                              throw exception(error_failed);

                           }

                        });

   }


   void node::open_url(const ::string &strUrl)
   {

      const char *pszUrl = strUrl;

      GError *perror = nullptr;

      if (!g_app_info_launch_default_for_uri(pszUrl, nullptr, &perror))
      {

         fprintf(stderr, "Unable to read file: %s\n", perror->message);

         g_error_free(perror);

      }

   }


   ::e_status node::_allocate_Display_and_connection()
   {

      if(!os_defer_init_gtk(this))
      {

         return ::error_failed;

      }

      if(m_edisplaytype == e_display_type_x11)
      {

         ::aura_posix::node::_allocate_Display_and_connection();

      }

      return ::success;

   }

   void node::_on_gtk_init()
   {

      if(m_edisplaytype == e_display_type_none)
      {

         GdkDisplay * pgdkdisplay = gdk_display_get_default();

         information() << "Display name : " << gdk_display_get_name(pgdkdisplay);

         if (GDK_IS_X11_DISPLAY (pgdkdisplay))
         {

            m_edisplaytype = e_display_type_x11;

            information() << "e_display_type_x11";

         }
         else if (GDK_IS_WAYLAND_DISPLAY (pgdkdisplay))
         {

            m_edisplaytype = e_display_type_wayland;

            information() << "e_display_type_wayland";

         }

      }

   }


   ::wl_display * node::get_wayland_display()
   {

      GdkDisplay * pgdkdisplay = gdk_display_get_default();

      auto pwldisplay = gdk_wayland_display_get_wl_display   (pgdkdisplay);

      return pwldisplay;

   }


   bool node::defer_windowing_post(const ::procedure & procedure)
   {

      user_post(procedure);

      return true;

   }


   ::pointer<::input::input > node::create_input()
   {

      auto & pfactory = platform()->factory("input", "libinput");

      auto pinput = __create<::input::input>(pfactory);

      return pinput;

   }


   void node::launch_app_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion)
   {

//      information() << "node::launch_app_by_app_id : " << scopedstrAppId;
//
//      auto pathDesktopFile = get_desktop_file_path_by_app_id(scopedstrAppId);
//
//      if(!acmefile()->exists(pathDesktopFile))
//      {
//
//         information() << "Desktop file (\"" << pathDesktopFile << "\") doesn't exist. Going to try to launch with executable path.";

         ::aura_posix::node::launch_app_by_app_id(scopedstrAppId, bSingleExecutableVersion);

//         return;
//
//      }
//
//      ::string strAppId = scopedstrAppId;
//
//      strAppId.find_replace("/", ".");
//
//      ::string strCommand = "sh -c \"nohup gtk-launch " + strAppId + " &\"";
//
//      int iExitCode = acmenode()->command_system(strCommand, 10_minutes);
//
//      if(iExitCode == 0)
//      {
//
//         information() << "Successfully launched \"" << scopedstrAppId << "\"";
//
//         return;
//
//      }
//
//      warning() << "Failed to launch application \"" + scopedstrAppId + "\" using gtk-launch";
//
//      information() << "Going to try to launch with executable path.";
//
//      ::aura_posix::node::launch_app_by_app_id(scopedstrAppId);

   }


} // namespace node_gtk


gboolean node_gtk_source_func(gpointer pUserdata)
{

   ::topic *ptopic = (::topic *) pUserdata;

   if (!ptopic->topic_step())
   {

      return false;

   }

   return true;

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
//         x11_kick_idle();
//
//      }
//
//   }







#ifdef LINUX

static void
log_handler(const gchar *log_domain,
            GLogLevelFlags log_level,
            const gchar *message,
            gpointer user_data)
{
   g_log_default_handler(log_domain, log_level, message, user_data);

   g_on_error_query(nullptr);
}


#endif


//::particle *user_synchronization();


::e_status run_runnable(::particle *pobjectTask);


gboolean x11_source_func(gpointer p)
{

   ::node_gtk::node *pnode = (::node_gtk::node *) p;

   if (!pnode->windowing_message_loop_step())
   {

      return FALSE;

   }

   return TRUE;

}


void x11_add_idle_source(::node_gtk::node *pnode)
{

   gdk_threads_add_idle(&x11_source_func, pnode);

}


bool x11_message_handler(XEvent *pevent);


GdkFilterReturn x11_event_func(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{

   XEvent *pevent = (XEvent *) xevent;

   ::node_gtk::node *pnode = (::node_gtk::node *) data;

   auto pwindowing = pnode->windowing();

   pwindowing->_message_handler(pevent);

   return GDK_FILTER_CONTINUE;

}


// This seems not to work with "foreign" windows
// (X11 windows not created with Gdk)
void x11_add_filter()
{

   // This seems not to work with "foreign" windows
   // (X11 windows not created with Gdk)
   gdk_window_add_filter(nullptr, &x11_event_func, nullptr);

}


//int gdk_launch_uri(const char * pszUri, char * pszError, int iBufferSize)
//{
//
//   gboolean ret;
//
//   GError * error = NULL;
//
//   ret = g_app_info_launch_default_for_uri(pszUri, NULL, &error);
//
//   if(ret)
//   {
//
//      return true;
//
//   }
//
//   if(pszError != nullptr)
//   {
//
//      strncpy(pszError, error->message, iBufferSize);
//
//   }
//
//   return 0;
//
//}



void os_post_quit()
{

   auto idle_source = g_idle_source_new();

   g_source_set_callback(idle_source, &gtk_quit_callback, nullptr, nullptr);

   g_source_attach(idle_source, g_main_context_default());

}


