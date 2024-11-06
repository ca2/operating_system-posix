//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/constant/id.h"
#include "acme/operating_system/ansi/pmutex_lock.h"
#include "acme/operating_system/parallelization.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/node.h"
#include "acme/prototype/prototype/type.h"
#include "apex/operating_system/freedesktop/desktop_file.h"
#include "acme/handler/topic.h"
#include "acme/operating_system/summary.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/user/user/os_theme_colors.h"
#include "acme/user/user/theme_colors.h"
#include "acme/windowing/windowing_base.h"
#include "apex/input/input.h"
#include "apex/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura/windowing/display.h"
#include "windowing_x11/windowing_x11.h"
#include "aura/windowing/windowing.h"
//#include "windowing_x11/windowing.h"
#include "node_gdk/windowing_system.h"


#include <gio/gio.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <gdk/gdkdisplay.h>
#include <gdk/gdkwayland.h>
#include <gdk/gdkx.h>

#include <sys/stat.h>
#include <unistd.h>


#include <cairo/cairo.h>


//namespace x11
//{
//   namespace nano
//   {
//      namespace user
//      {
//         CLASS_DECL_ACME void set_thread();
//         CLASS_DECL_ACME int init_threads();
//      }
//   }
//}
namespace nano
{
   namespace user
   {


enum_display_type calculate_display_type();
   }
}



bool aaa_x11_message_loop_step();


gboolean gtk_quit_callback(gpointer data);


//void gio_open_url(const char * pszUrl);
///int gtk_launch (const char * pszDesktopFileTitle);


void copy(::color::color &color, const GdkRGBA &rgba)
{

   color.set(rgba.red, rgba.green, rgba.blue, rgba.alpha);

}


void __cairo_create_image_argb32_surface_from_surface(::memory & m, int & w, int & h, cairo_surface_t * psurface)
{

   h = cairo_image_surface_get_height(psurface);

   w = cairo_image_surface_get_width(psurface);

   m.set_size(w * h * 4);

   auto pimagesurfaceArgb32 = cairo_image_surface_create_for_data(m.data(),
                                                       CAIRO_FORMAT_ARGB32, w, h, w * 4);

   auto cr = cairo_create(pimagesurfaceArgb32);
   cairo_set_source_surface (cr, psurface, 0, 0);
   cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);
   cairo_rectangle (cr, 0, 0, w, h);
   cairo_fill (cr);
   cairo_surface_flush(pimagesurfaceArgb32);
   cairo_destroy(cr);
   cairo_surface_destroy(pimagesurfaceArgb32);

}


cairo_surface_t * __cairo_create_image_argb32_surface(::memory & m, int w, int h)
{

   m.set_size(w * h * 4);

   auto pimagesurface = cairo_image_surface_create_for_data(m.data(),
                                                                  CAIRO_FORMAT_ARGB32, w, h, w * 4);

   return pimagesurface;

}


::color::color __cairo_image_argb32_surface_get_average_color(cairo_surface_t * psurface)
{

   auto h = cairo_image_surface_get_height(psurface);

   auto w = cairo_image_surface_get_width(psurface);

   auto s = cairo_image_surface_get_stride(psurface);

   auto data = (unsigned char *) cairo_image_surface_get_data(psurface);

   long long int r = 0;
   long long int g = 0;
   long long int b = 0;
   long long int a = 0;

   for (int n = 0; n < h; n++)
   {

      auto pline = data + s * n;

      for (int l = 0; l < w; l++)
      {

         a+= pline[3];
         r+= pline[2];
         g+= pline[1];
         b+= pline[0];

         pline += 4;

      }

   }

   if(a == 0)
   {

      return ::color::transparent;

   }
   else
   {

      auto area = w * h;

      double dA = ((double)a) / (double) (area);

      double dR = ((double)r) / (double)a;

      double dG = ((double)g) / (double)a;

      double dB = ((double)b) / (double)a;

      return argb(dA / 255.0, dR, dG, dB);

   }

}


::color::color __gtk_style_context_get_background_color(GtkStyleContext * pstylecontext)
{

   auto w = 32;

   auto h = 32;

   auto surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);

   auto cr = cairo_create (surface);

   cairo_set_source_rgba(cr, 0, 0, 0, 0);

   cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);

   cairo_paint(cr);

   cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

   gtk_render_background (pstylecontext, cr, 0., 0., w, h);

   auto color = __cairo_image_argb32_surface_get_average_color(surface);

   cairo_destroy (cr);

   cairo_surface_destroy (surface);

   return color ;

}


::color::color __gtk_widget_get_background_color(GtkWidget *pwidget)
{

   auto w = gtk_widget_get_allocated_width(GTK_WIDGET(pwidget));

   auto h = gtk_widget_get_allocated_height(GTK_WIDGET(pwidget));

   auto surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, w, h);

   auto cr = cairo_create (surface);

   auto style = gtk_widget_get_style_context(pwidget);

   cairo_set_source_rgba(cr, 0, 0, 0, 1.0);

   cairo_paint(cr);

   cairo_set_operator(cr, CAIRO_OPERATOR_OVER);

   gtk_render_background (style, cr, 0., 0., w, h);

   auto color = __cairo_image_argb32_surface_get_average_color(surface);

   cairo_destroy (cr);

   cairo_surface_destroy (surface);

   return color ;

}


::color::color __gtk_child_widget_get_background_color1(GtkWidget * pwidget)
{

   ::color::color color;

//   gtk_snapshot_new
   auto pwindow = gtk_offscreen_window_new();

   gtk_container_add(GTK_CONTAINER(pwindow), pwidget);

   gtk_widget_show_all(GTK_WIDGET(pwindow));

   GtkStyleContext *pstylecontext = gtk_widget_get_style_context(pwidget);

   int w = gtk_widget_get_allocated_width(GTK_WIDGET(pwidget));

   int h = gtk_widget_get_allocated_height(GTK_WIDGET(pwidget));

   if(w > 0 && h > 0)
   {

      ::memory m;

      //auto cairo_surface = __cairo_create_image_argb32_surface(m, w, h);

      // gtk_snapshot_append_cairo

      auto cairo_surface = gtk_offscreen_window_get_surface(GTK_OFFSCREEN_WINDOW(pwindow));

      if (cairo_surface)
      {

         auto cairo_context = cairo_create(cairo_surface);

         //cairo_set_source_rgba(cairo_context, 0., 0., 0., 0.);

         //cairo_paint(cairo_context);

         gtk_render_background(pstylecontext, cairo_context, 0., 0., w, h);

         //gtk_widget_draw(GTK_WIDGET(pwindow), cairo_context);

         color = __cairo_image_argb32_surface_get_average_color(cairo_surface);

         cairo_destroy(cairo_context);

         cairo_surface_destroy(cairo_surface);

      }


   }

   gtk_container_remove(GTK_CONTAINER(pwindow), pwidget);

   gtk_widget_destroy(GTK_WIDGET(pwindow));

   return color;

}


//::color::color __gtk_widget_get_background_color(GtkWidget * pwidget)
//{
//
//   ::color::color color;
//
//   GtkWidgetPath *ppath = gtk_widget_get_path(pwidget);
//
//   auto pwindow = gtk_offscreen_window_new();
//
//   gtk_container_add(GTK_CONTAINER(pwindow), pwidget);
//
//   gtk_widget_show_all(GTK_WIDGET(pwindow));
//
//   int w = gtk_widget_get_allocated_width(GTK_WIDGET(pwidget));
//
//   int h = gtk_widget_get_allocated_height(GTK_WIDGET(pwidget));
//
//   GtkStyleContext *pstylecontext = gtk_style_context_new();
//
//   gtk_style_context_set_path(pstylecontext, ppath);
//
//   auto cairo_surface = gtk_offscreen_window_get_surface(GTK_OFFSCREEN_WINDOW(pwindow));
//
//   if(cairo_surface)
//   {
//
//      auto cairo_context = cairo_create(cairo_surface);
//
//      cairo_set_source_rgba(cairo_context, 0., 0., 0., 0.);
//
//      cairo_paint(cairo_context);
//
//      int w2 = cairo_image_surface_get_width(cairo_surface);
//
//      int h2 = cairo_image_surface_get_height(cairo_surface);
//
//      gtk_render_background(pstylecontext, cairo_context, 0., 0., w2, h2);
//
//      color = __cairo_image_argb32_surface_get_average_color(cairo_surface);
//
//      cairo_destroy(cairo_context);
//
//      cairo_surface_destroy(cairo_surface);
//
//   }
//
//   gtk_container_remove(GTK_CONTAINER(pwindow), pwidget);
//
//   gtk_widget_destroy(GTK_WIDGET(pwindow));
//
//   return color;
//
//}


bool __gtk_style_context_get_color(GtkStyleContext *context, GtkStateFlags state, const char *pszProperty, ::color::color & color)
{

   GdkRGBA *prgba = nullptr;

   gtk_style_context_get(context, state, pszProperty, &prgba, NULL);

   copy(color, *prgba);

   gdk_rgba_free(prgba);

   return true;

}


//void windowing_message_loop_add_idle_source(::node_gtk3::node *pnode);


void gtk_settings_gtk_theme_name_callback(GObject *object, GParamSpec *pspec, gpointer data)
{

   node_gtk3::node *pnode = (node_gtk3::node *) data;

   if (!pnode)
   {

      return;

   }

   gchar *theme_name = nullptr;

   g_object_get(pnode->m_pGtkSettingsDefault, "gtk-theme-name", &theme_name, NULL);

   string strTheme = theme_name;

   informationf("gtk_settings_gtk_theme_name_callback: \"" + strTheme + "\"\n");

   g_free(theme_name);

//   pnode->fork([pnode, strTheme]()
//               {

   //pnode->_set_os_user_theme(strTheme);

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

   node_gtk3::node *pnode = (node_gtk3::node *) data;

   if (!pnode)
   {

      return;

   }

   gchar *icon_theme_name = nullptr;

   g_object_get(pnode->m_pGtkSettingsDefault, "gtk-icon-theme-name", &icon_theme_name, NULL);

   string strIconTheme = icon_theme_name;

   informationf("gtk_settings_gtk_icon_theme_name_callback: \"" + strIconTheme + "\"\n");

   g_free(icon_theme_name);

//   pnode->fork([pnode, strTheme]()
//               {

   //pnode->_set_os_user_icon_theme(strIconTheme);

//                  ::preempt(400_ms);
//
//                  pnode->_apply_os_user_theme(strTheme);
//
//                  //_os_user_theme(strTheme);
//
//               });

}


//void aaa_x11_add_idle_source();


void x11_add_filter(void * p);


//void x11_main();


//::particle *user_synchronization();


gboolean node_gtk_source_func(gpointer pUserdata);


namespace node_gtk3
{

   class appindicator;

   void appindicator_destroy(appindicator *pindicator);

} // namespace node_gtk3



void os_post_quit();

void apex_application_run(const char *pszAppName, const char *pszProgName);

namespace node_gtk3
{


   CLASS_DECL_ACME void _os_process_user_theme(string strTheme);
   void gtk_defer_do_main_tasks();



   node::node()
   {

      m_pNodeGtk3 = this;

      m_pGtkSettingsDefault = nullptr;

      //m_pgdkapplaunchcontext = nullptr;

   }


   node::~node()
   {

      m_pGtkSettingsDefault = nullptr;

//      for (auto &pair: m_mapGDesktopAppInfo)
//      {
//
//         g_object_unref(pair.m_element2);
//
//      }

//      if (m_pgdkapplaunchcontext)
//      {
//
//         g_object_unref(m_pgdkapplaunchcontext);
//
//      }

   }


//   int node::node_init_check(int *pi, char ***ppz)
//   {
//
//      if (!::node_gtk3::os_defer_init_gtk(this))
//      {
//
//         return 0;
//
//      }
//
//      return 1;
//
//   }
//
//
//   bool node::os_defer_init_gtk()
//   {
//
//      return ::node_gtk3::os_defer_init_gtk(this);
//
//   }


   // void node::defer_notify_startup_complete()
   // {
   //
   //    // auto psystem = system();
   //    //
   //    // string strApplicationServerName = psystem->get_application_server_name();
   //    //
   //    // gdk_notify_startup_complete_with_id(strApplicationServerName);
   //    //
   //    // gdk_notify_startup_complete();
   //
   // }


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
                         platform()->get_pargs());

      }

#endif

      ::windowing::get_ewindowing() = calculate_ewindowing();

      // system()->__construct(system()->m_pwindowingsystem);
      //
      // ::pointer < ::node_gdk::windowing_system> pnodegdkwindowingsystem = system()->m_pwindowingsystem;
      //
      // if(pnodegdkwindowingsystem)
      // {
      //
      //    pnodegdkwindowingsystem->m_pgdknode = this;
      //
      // }
      //
      // information() << "windowing_system type : " << ::type(system()->m_pwindowingsystem).name() ;

//      if (m_bUser)
//      {
//
//         estatus = deferx_initializex_x11();
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
//      m_papplication->branch(pnode);
//
//      return ::success;

      auto psystem = system();

      if (psystem->application()->m_bGtkApp)
      {

         //apex_application_run(psystem->m_strAppId, psystem->m_strProgName);

      }
      else
      {

         information() << "node_gtk3::system_main going to user_post";

         user_post([this]()
                   {

                      // This seems not to work with "foreign" windows
                      // (X11 windows not created with Gdk)
                      x11_add_filter(this);

                      information() << "node_gtk3::system_main on user_post";


                      auto pgtksettingsDefault = gtk_settings_get_default();

                      if (pgtksettingsDefault)
                      {

                         m_pGtkSettingsDefault = pgtksettingsDefault;

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

                      information() << "node_gtk3::system_main going to windowing_message_loop_add_idle_source";

                      //windowing_message_loop_add_idle_source(this);

                      //_g_idle_add_windowing_message_loop();

                      auto psystem = system();

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

         ::set_main_user_thread(::current_htask());

//#if defined(WITH_X11)
//
//         ::x11::micro::set_thread();
//
//#endif

         information() << "node_gtk3::system_main GTK_MAIN";

         ::task_set_name("Main Thread");

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

      ::aura_posix::node::initialize(pparticle);

      //initialize_window_manager();

      //::node_gtk3::g_defer_init();

      //return ::success;

   }


//   void node::fetch_user_color()
//   {
//
//      ::aura::posix::node::fetch_user_color();
//
//   }


//   bool node::windowing_message_loop_step()
//   {
//
//      information() << "node::windowing_message_loop_step";
//
//      auto psession = session();
//
//      if (::is_null(psession))
//      {
//
//         information() << "node::windowing_message_loop_step NO SESSION";
//
//         return true;
//
//      }
//
//      auto paurasession = psession;
//
//      if (::is_null(paurasession))
//      {
//
//         information() << "node::windowing_message_loop_step NO AURA SESSION";
//
//         return true;
//
//      }
//
//      auto puser = paurasession->user();
//
//      if (::is_null(puser))
//      {
//
//         information() << "node::windowing_message_loop_step NO SESSION USER";
//
//         return true;
//
//      }
//
//      auto pwindowing = system()->windowing();
//
//      if (::is_null(pwindowing))
//      {
//
//         information() << "node::windowing_message_loop_step NO USER WINDOWING";
//
//         return true;
//
//      }
//
//      information() << "node::windowing_message_loop_step at windowing";
//
//      bool bRet = pwindowing->message_loop_step();
//
//      return bRet;
//
//   }


//   string node::os_get_user_theme()
//   {
//
//      return m_strTheme;
//
//   }


//   string node::_on_user_theme_changed()
//   {
//
//      system()->signal(id_os_user_theme);
//
//   }


//   void node::_fill_os_theme_colors(::os_theme_colors * pthemecolors)
//   {
//
//      ::string strGtkTheme;
//
//      strGtkTheme = _get_os_user_theme();
//
//      if(strGtkTheme.has_char())
//      {
//
//         _fill_os_theme_colors(pthemecolors, strGtkTheme, dark_mode());
//
//      }
//      else
//      {
//
//         ::acme_posix::node::_fill_os_theme_colors(pthemecolors);
//
//      }
//
//   }


//   void node::_fetch_dark_mode()
//   {
//
//      information() << "::node_gtk3::node::_dark_mode";
//
//      if(gsettings_schema_exists("org.gnome.desktop.interface"))
//      {
//
//         information() << "org.gnome.desktop.interface exists";
//
//         if(gsettings_schema_contains_key("org.gnome.desktop.interface", "color-scheme"))
//         {
//
//            information() << "org.gnome.desktop.interface contains \"color-scheme\"";
//
//            ::string strColorScheme;
//
//            if (gsettings_get(strColorScheme, "org.gnome.desktop.interface", "color-scheme"))
//            {
//
//               information() << "color-scheme=\"" + strColorScheme + "\"";
//
//               strColorScheme.trim();
//
//               if (strColorScheme.case_insensitive_contains("dark"))
//               {
//
//                  m_bOperatingSystemDarkMode = true;
//
//               }
//               else
//               {
//
//                  m_bOperatingSystemDarkMode = false;
//
//               }
//
//            }
//            else
//            {
//
//               m_bOperatingSystemDarkMode = false;
//
//            }
//
//         }
//         else
//         {
//
//            _fetch_user_color();
//
////            {
////
////               m_bOperatingSystemDarkMode = false;
////
////            }
//
//         }
//
//      }
//
//   }


//   bool node::dark_mode() const
//   {
//
//      auto pnodeThisMutable = (node *) this;
//
//      pnodeThisMutable->_fetch_dark_mode();
//
//      return ::aura_posix::node::dark_mode();
//
//   }
//
//
//   void node::set_dark_mode(bool bDarkMode)
//   {
//
//      post_procedure([this, bDarkMode]()
//                     {
//
//      if(bDarkMode)
//      {
//
//         gsettings_set("org.gnome.desktop.interface", "color-scheme", "prefer-dark");
//
//      }
//      else
//      {
//
//         auto psummary = operating_system_summary();
//
//         if(psummary->m_strDistro.case_insensitive_equals("ubuntu"))
//         {
//
//            gsettings_set("org.gnome.desktop.interface", "color-scheme", "default");
//
//         }
//         else
//         {
//
//            gsettings_set("org.gnome.desktop.interface", "color-scheme", "prefer-light");
//
//         }
//
//      }
//
//      _os_set_user_theme(m_strTheme);
//
//      _os_set_user_icon_theme(m_strIconTheme);
//
//      ::aura_posix::node::set_dark_mode(bDarkMode);
//
//      });
//
//   }
//
//
//   void node::os_set_user_theme(const ::string &strUserTheme)
//   {
//
//      //auto estatus =
//      //
//      //
//      _os_set_user_theme(strUserTheme);
//
////      if(!estatus)
////      {
////
////         return estatus;
////
////      }
////
////      return estatus;
//
//   }
//
//
//   ::e_status node::_os_set_user_theme(const ::string &strUserTheme)
//   {
//
//      // https://ubuntuforums.org/showthread.php?t=2140488
//      // gsettings set org.gnome.desktop.interface gtk-theme your_theme
//
//      // indirect wall-changer sourceforge.net contribution
//
//      auto psystem = system();
//
//      auto pnode = psystem->node();
//
//      auto edesktop = pnode->get_edesktop();
//
//      if (edesktop & ::user::e_desktop_gnome)
//      {
//
//         bool bOk1 = gsettings_set("org.gnome.desktop.interface", "gtk-theme", strUserTheme).ok();
//
//         bool bOk2 = true;
//
//         //if(::file::system_short_name().case_insensitive_contains("manjaro"))
//         {
//
//            bOk2 = gsettings_set("org.gnome.desktop.wm.preferences", "theme", strUserTheme).ok();
//
//         }
//
//         sleep(300_ms);
//
//         ::node_gtk3::gsettings_sync();
//
//         sleep(300_ms);
//
//         if (!bOk1 || !bOk2)
//         {
//
//            return error_failed;
//
//         }
//
//      }
//      else if (edesktop & ::user::e_desktop_mate)
//      {
//
//         //return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);
//
//      }
//      else if (edesktop & ::user::e_desktop_lxde)
//      {
//
//
//         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
//
//      }
//      else if (edesktop & ::user::e_desktop_xfce)
//      {
//         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
//         //          if(entry.contains("image-path") || entry.contains("last-image")){
//         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
//         //      }
//         //}
//
//         warning() <<"Failed to set operating system theme wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
//
//         return error_failed;
//
//      }
//
//      return ::success;
//
//   }
//
//
//   ::e_status node::_os_set_user_icon_theme(const ::string &strUserIconTheme)
//   {
//
//      // https://ubuntuforums.org/showthread.php?t=2140488
//      // gsettings set org.gnome.desktop.interface gtk-theme your_theme
//
//      // indirect wall-changer sourceforge.net contribution
//
//      auto psystem = system();
//
//      auto pnode = psystem->node();
//
//      auto edesktop = pnode->get_edesktop();
//
//      if (edesktop & ::user::e_desktop_gnome)
//      {
//
//         bool bOk1 = gsettings_set("org.gnome.desktop.interface", "icon-theme", strUserIconTheme).ok();
//
//         //bool bOk2 = true;
//
////         //if(::file::system_short_name().case_insensitive_contains("manjaro"))
////         {
////
////            bOk2 = gsettings_set("org.gnome.desktop.wm.preferences", "theme", strUserTheme);
////
////         }
//
//         sleep(300_ms);
//
//         ::node_gtk3::gsettings_sync();
//
//         sleep(300_ms);
//
//         //if (!bOk1 || !bOk2)
//         if (!bOk1)
//         {
//
//            return error_failed;
//
//         }
//
//      }
//      else if (edesktop & ::user::e_desktop_mate)
//      {
//
//         //return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);
//
//      }
//      else if (edesktop & ::user::e_desktop_lxde)
//      {
//
//
//         //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
//
//      }
//      else if (edesktop & ::user::e_desktop_xfce)
//      {
//         //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
//         //          if(entry.contains("image-path") || entry.contains("last-image")){
//         //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
//         //      }
//         //}
//
//         warning() <<"Failed to set operating system theme wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
//
//         return error_failed;
//
//      }
//
//      return ::success;
//
//   }
//
//
////   void node::os_process_user_theme(string strTheme)
////   {
////
////      _os_process_user_theme(strTheme);
////
////   }
//
//
//
//   bool node::set_wallpaper(::collection::index iScreen, string strLocalImagePath, ::windowing::display * pwindowingdisplay)
//   {
//
//      // wall-changer sourceforge.net contribution
//
//      auto psystem = system();
//
//      auto pnode = psystem->node();
//
//      auto edesktop = pnode->get_edesktop();
//
//      bool bDark = pwindowingdisplay->m_strDarkModeAnnotation.case_insensitive_contains("dark");
//
//      switch (edesktop)
//      {
//
//         case ::user::e_desktop_gnome:
//         case ::user::e_desktop_ubuntu_gnome:
//         case ::user::e_desktop_unity_gnome:
//         {
//
//            if(bDark)
//            {
//
//               return ::node_gtk3::gsettings_set("org.gnome.desktop.background", "picture-uri-dark",
//                                                "file://" + strLocalImagePath).ok();
//
//            }
//            else
//            {
//
//               return ::node_gtk3::gsettings_set("org.gnome.desktop.background", "picture-uri",
//                                                "file://" + strLocalImagePath).ok();
//
//            }
//
//         }
//         case ::user::e_desktop_mate:
//
//            return ::node_gtk3::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath).ok();
//
//         case ::user::e_desktop_lxde:
//
//            call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
//
//            break;
//
//         case ::user::e_desktop_xfce:
//         {
//            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
//            //          if(entry.contains("image-path") || entry.contains("last-image")){
//            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
//            //      }
//            //}
//
//         }
//
//            //break;
//
//         default:
//
//            warning() <<"Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
//            return false;
//
//      }
//
//      return true;
//
//   }
//
//
//   void node::enable_wallpaper_change_notification()
//   {
//
//      auto psystem = system();
//
//      auto pnode = psystem->node();
//
//      auto edesktop = pnode->get_edesktop();
//
//      switch (edesktop)
//      {
//
//         case ::user::e_desktop_gnome:
//         case ::user::e_desktop_ubuntu_gnome:
//         case ::user::e_desktop_unity_gnome:
//
//            node_enable_wallpaper_change_notification(this, "org.gnome.desktop.background", "picture-uri");
//
//            break;
//
//         case ::user::e_desktop_mate:
//
//            node_enable_wallpaper_change_notification(this, "org.mate.background", "picture-filename");
//
//            break;
//
//         case ::user::e_desktop_lxde:
//
//            //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
//
//            break;
//
//         case ::user::e_desktop_xfce:
//         {
//            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
//            //          if(entry.contains("image-path") || entry.contains("last-image")){
//            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
//            //      }
//            //}
//
//         }
//
//            break;
//         default:
//
//            warning() <<"Failed to get wallpaper setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
//            //return "";
//
//      }
//
//   }
//
//
//   string node::get_file_icon_path(const ::string &strPath, int iSize)
//   {
//
//      return ::node_gtk3::g_get_file_icon_path(strPath, iSize);
//
//   }
//
//
//   string node::get_file_content_type(const ::string &strPath)
//   {
//
//      return ::node_gtk3::g_get_file_content_type(strPath);
//
//   }
//
//
//   string node::get_wallpaper(::collection::index iScreen)
//   {
//
//      return "";
//
//   }
//
//
//   void node::user_post(const ::procedure &procedure)
//   {
//
//      gdk_branch(procedure);
//
//   }
//
//
   void node::defer_do_main_tasks()
   {

      gtk_defer_do_main_tasks();

   }
//
//
////   void node::user_post_quit()
////   {
////
////      ::os_post_quit();
////
////   }

//
//void node::on_user_system_quit()
//{
//
//     gtk_main_quit();
//
//}


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




//   bool g_bInitializedUserTheme = false;
//
//   string node::_os_get_user_theme()
//   {
//
//      if (!g_bInitializedUserTheme)
//      {
//
//         g_bInitializedUserTheme = true;
//
//         //auto psystem = system();
//
//         //psystem->start_subject_handling(id_os_user_theme);
//
//      }
//
//      // https://ubuntuforums.org/showthread.php?t=2140488
//      // gsettings set org.gnome.desktop.interface gtk-theme your_theme
//
//      // indirect wall-changer sourceforge.net contribution
//
//      string strTheme;
//
//      bool bOk = false;
//
//      auto psystem = system();
//
//      auto pnode = psystem->node();
//
//      auto edesktop = pnode->get_edesktop();
//
//      switch (edesktop)
//      {
//
//         case ::user::e_desktop_gnome:
//         case ::user::e_desktop_ubuntu_gnome:
//         case ::user::e_desktop_unity_gnome:
//
//            bOk = gsettings_get(strTheme, "org.gnome.desktop.interface", "gtk-theme").ok();
//
//            break;
//
//         case ::user::e_desktop_mate:
//
//            bOk = gsettings_get(strTheme, "org.mate.background", "picture-filename").ok();
//
//            break;
//
//         case ::user::e_desktop_lxde:
//
//            //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
//
//            break;
//
//         case ::user::e_desktop_xfce:
//         {
//            //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
//            //          if(entry.contains("image-path") || entry.contains("last-image")){
//            //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
//            //      }
//            //}
//
//         }
//
//            //break;
//
//         default:
//
//            warningf(
//                    "Failed to get user theme setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
//            //return "";
//
//      }
//
//      return strTheme;
//
//   }


   GtkStyleContext * __get_style_context_for_theme(const char * pszTheme, bool bDarkMode)
   {

      GtkStyleContext* pstylecontext = gtk_style_context_new();

      const char * pszVariant = nullptr;

      if(bDarkMode)
      {

         pszVariant = "dark";

      }

      GtkCssProvider *pprovider = gtk_css_provider_get_named(pszTheme, pszVariant);

      gtk_style_context_add_provider(pstylecontext, GTK_STYLE_PROVIDER(pprovider), GTK_STYLE_PROVIDER_PRIORITY_USER);

      return pstylecontext;

   }


//   void node::_fill_os_theme_colors(::os_theme_colors * pthemecolors, const ::scoped_string & scopedstrTheme, bool bDarkMode)
//   {
//
//      ::string strTheme(scopedstrTheme);
//
//      auto pszTheme = strTheme.c_str();
//
//      information() << "_fill_os_theme_colors with theme : " << pszTheme;
//
//
//      {
//
//         //auto pdialog = gtk_dialog_new();
//
////         auto pdialog = gtk_dialog_new();
////
////         gdk_window_begin_draw_frame
////
////         gtk_window_set_default_size(GTK_WINDOW(pdialog), 256, 256);
////
////         gtk_window_set_resizable(GTK_WINDOW(pdialog), FALSE);
////
////         gtk_widget_show_all(GTK_WIDGET(pdialog));
//         //GtkCssProvider *pprovider = gtk_css_provider_get_named(pszTheme, nullptr);
//
//         //gtk_style_context_add_provider(pstylecontext, GTK_STYLE_PROVIDER(pprovider), GTK_STYLE_PROVIDER_PRIORITY_USER);
//
//         //GtkWidget *pdialog = gtk_dialog_new();
//
//         //GtkWidgetPath *ppath = gtk_widget_get_path(pdialog);
//
//         //gtk_style_context_set_path(pstylecontext, ppath);
//
//         // Foreground color is taken from 'tooltip label' css node
//         //GtkStyleContext* styleContextLabel = gtk_style_context_new();
//         //{
//
//            // Background color is taken from 'window.background' css node
//
//         auto pstylecontext = __get_style_context_for_theme(pszTheme, bDarkMode);
//
//         {
//
//            GtkWidgetPath* pwidgetpath = gtk_widget_path_new();
//            gtk_widget_path_append_type(pwidgetpath, 0);
//            gtk_widget_path_iter_set_object_name(pwidgetpath, -1, "window");
//            gtk_widget_path_iter_add_class(pwidgetpath, -1, GTK_STYLE_CLASS_BACKGROUND);
//            gtk_style_context_set_path(pstylecontext, pwidgetpath);
//            pthemecolors->m_colorBack = __gtk_style_context_get_background_color(pstylecontext);
//            gtk_widget_path_free(pwidgetpath);
//
//         }
//
//
//         // Destroy temporary style context
//         g_object_unref(pstylecontext);
//
////            GtkWidgetPath* widgetPath = gtk_widget_path_new();
////            gtk_widget_path_append_type(widgetPath, 0);
////            gtk_widget_path_iter_set_object_name(widgetPath, -1, "window");
////            gtk_widget_path_iter_add_class(widgetPath, -1, GTK_STYLE_CLASS_BACKGROUND);
////            gtk_widget_path_append_type(widgetPath, GTK_TYPE_DIALOG);
////            gtk_style_context_set_path(pstylecontext, widgetPath);
////
////            gtk_widget_path_free(widgetPath);
////         }
////
////
//////         informationf( "r%d, g%d, b%d, a%d",
//////                       pthemecolors->m_colorBack.m_uchRed,
//////                       pthemecolors->m_colorBack.m_uchGreen,
//////                       pthemecolors->m_colorBack.m_uchBlue,
//////                       pthemecolors->m_colorBack.m_uchOpacity);
//////
////         gtk_widget_destroy(GTK_WIDGET(pdialog));
//
//      }
//
//
//            {
//
//         //auto pdialog = gtk_dialog_new();
//
////         auto pdialog = gtk_dialog_new();
////
////         gdk_window_begin_draw_frame
////
////         gtk_window_set_default_size(GTK_WINDOW(pdialog), 256, 256);
////
////         gtk_window_set_resizable(GTK_WINDOW(pdialog), FALSE);
////
////         gtk_widget_show_all(GTK_WIDGET(pdialog));
//         //GtkCssProvider *pprovider = gtk_css_provider_get_named(pszTheme, nullptr);
//
//         //gtk_style_context_add_provider(pstylecontext, GTK_STYLE_PROVIDER(pprovider), GTK_STYLE_PROVIDER_PRIORITY_USER);
//
//         //GtkWidget *pdialog = gtk_dialog_new();
//
//         //GtkWidgetPath *ppath = gtk_widget_get_path(pdialog);
//
//         //gtk_style_context_set_path(pstylecontext, ppath);
//
//         // Foreground color is taken from 'tooltip label' css node
//         //GtkStyleContext* styleContextLabel = gtk_style_context_new();
//         //{
//
//            // Background color is taken from 'window.background' css node
//
//         auto pstylecontext = __get_style_context_for_theme(pszTheme, bDarkMode);
//
//         {
//
//            GtkWidgetPath* pwidgetpath = gtk_widget_path_new();
//            gtk_widget_path_append_type(pwidgetpath, 0);
//            gtk_widget_path_iter_set_object_name(pwidgetpath, -1, "button");
//            gtk_style_context_set_path(pstylecontext, pwidgetpath);
//            pthemecolors->m_colorFace = __gtk_style_context_get_background_color(pstylecontext);
//            auto flags = gtk_style_context_get_state(pstylecontext);
//            gtk_style_context_set_state(pstylecontext, (GtkStateFlags) (flags | GTK_STATE_FLAG_PRELIGHT));
//            pthemecolors->m_colorFaceHover = __gtk_style_context_get_background_color(pstylecontext);
//            gtk_style_context_set_state(pstylecontext, (GtkStateFlags) (flags | GTK_STATE_FLAG_ACTIVE));
//            pthemecolors->m_colorFacePress = __gtk_style_context_get_background_color(pstylecontext);
//            gtk_widget_path_free(pwidgetpath);
//
//         }
//
//
//         // Destroy temporary style context
//         g_object_unref(pstylecontext);
//
////            GtkWidgetPath* widgetPath = gtk_widget_path_new();
////            gtk_widget_path_append_type(widgetPath, 0);
////            gtk_widget_path_iter_set_object_name(widgetPath, -1, "window");
////            gtk_widget_path_iter_add_class(widgetPath, -1, GTK_STYLE_CLASS_BACKGROUND);
////            gtk_widget_path_append_type(widgetPath, GTK_TYPE_DIALOG);
////            gtk_style_context_set_path(pstylecontext, widgetPath);
////
////            gtk_widget_path_free(widgetPath);
////         }
////
////
//////         informationf( "r%d, g%d, b%d, a%d",
//////                       pthemecolors->m_colorBack.m_uchRed,
//////                       pthemecolors->m_colorBack.m_uchGreen,
//////                       pthemecolors->m_colorBack.m_uchBlue,
//////                       pthemecolors->m_colorBack.m_uchOpacity);
//////
////         gtk_widget_destroy(GTK_WIDGET(pdialog));
//
//      }
//
//      GtkStyleContext *pstylecontext = gtk_style_context_new();
//
//      GtkCssProvider *pprovider = gtk_css_provider_get_named(pszTheme, nullptr);
//
//      gtk_style_context_add_provider(pstylecontext, GTK_STYLE_PROVIDER(pprovider), GTK_STYLE_PROVIDER_PRIORITY_USER);
//
//      {
//
//         GtkWidget *pbutton = gtk_button_new();
//
//         GtkWidgetPath *ppath = gtk_widget_get_path(pbutton);
//
//         gtk_style_context_set_path(pstylecontext, ppath);
//
////         __gtk_style_context_get_color(
////                 pstylecontext,
////                 GTK_STATE_FLAG_NORMAL,
////                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
////                 pthemecolors->m_colorFace);
////
////         double dAlpha = pthemecolors->m_colorFace.f64_opacity();
////
////         if (dAlpha < 0.95)
////         {
////
////            pthemecolors->m_colorFace.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);
////
////         }
////
////         __gtk_style_context_get_color(
////                 pstylecontext,
////                 GTK_STATE_FLAG_PRELIGHT,
////                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
////                 pthemecolors->m_colorFaceHover);
////
////         dAlpha = pthemecolors->m_colorFaceHover.f64_opacity();
////
////         if (dAlpha < 0.95)
////         {
////
////            pthemecolors->m_colorFaceHover.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);
////
////         }
//
////         __gtk_style_context_get_color(
////                 pstylecontext,
////                 GTK_STATE_FLAG_ACTIVE,
////                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
////                 pthemecolors->m_colorFacePress);
////
////         dAlpha = pthemecolors->m_colorFacePress.f64_opacity();
////
////         if (dAlpha < 0.95)
////         {
////
////            pthemecolors->m_colorFacePress.blend(pthemecolors->m_colorBack, 1.0 - dAlpha);
////
////         }
////
////         __gtk_style_context_get_color(
////                 pstylecontext,
////                 GTK_STATE_FLAG_NORMAL,
////                 GTK_STYLE_PROPERTY_COLOR,
////                 pthemecolors->m_colorButton);
//
////         __gtk_style_context_get_color(
////                 pstylecontext,
////                 GTK_STATE_FLAG_PRELIGHT,
////                 GTK_STYLE_PROPERTY_COLOR,
////                 pthemecolors->m_colorButtonHover);
//
//         __gtk_style_context_get_color(
//                 pstylecontext,
//                 GTK_STATE_FLAG_NORMAL,
//                 GTK_STYLE_PROPERTY_BORDER_COLOR,
//                 pthemecolors->m_colorBorder);
//
//
////         pthemecolors->m_colorBorderHover4 = pthemecolors->m_colorBorderHover;
////
////         pthemecolors->m_colorBorderHover4.blend(pthemecolors->m_colorBack, 0.8);
//
//
//         gtk_widget_destroy(pbutton);
//
//      }
//
//      {
//
//         GtkWidget *pwidget = gtk_list_box_row_new();
//
//         GtkWidgetPath *ppath = gtk_widget_get_path(pwidget);
//
//         gtk_style_context_set_path(pstylecontext, ppath);
//
//         __gtk_style_context_get_color(
//                 pstylecontext,
//                 GTK_STATE_FLAG_SELECTED,
//                 GTK_STYLE_PROPERTY_BACKGROUND_COLOR,
//                 pthemecolors->m_colorBorderHover);
//
//         pthemecolors->m_colorBorderPress = pthemecolors->m_colorBorderHover;
//
//         pthemecolors->m_colorBorderHover1 = pthemecolors->m_colorBorderHover;
//
//         pthemecolors->m_colorBorderHover1.blend(pthemecolors->m_colorBack, 0.3);
//
//         pthemecolors->m_colorBorderHover2 = pthemecolors->m_colorBorderHover;
//
//         pthemecolors->m_colorBorderHover2.blend(pthemecolors->m_colorBack, 0.6);
//
//         pthemecolors->m_colorBorderHover3 = pthemecolors->m_colorBorderHover;
//
//         pthemecolors->m_colorBorderHover3.blend(pthemecolors->m_colorBack, 0.9);
//
//         __gtk_style_context_get_color(
//                 pstylecontext,
//                 GTK_STATE_FLAG_SELECTED,
//                 GTK_STYLE_PROPERTY_COLOR,
//                 pthemecolors->m_colorButtonPress);
//
//         gtk_widget_destroy(pwidget);
//
//      }

//      return pthemecolors;
//
//   }


//   void node::_set_os_theme_colors(::os_theme_colors *posthemecolors)
//   {
//
//      informationf("_set_os_theme_colors\n");
//
//      ::user::os_set_theme_colors(posthemecolors);
//
//      background_color(posthemecolors->m_colorBack);
//
//   }


//   void node::_set_os_user_theme(const ::scoped_string &strOsUserTheme)
//   {
//
//      m_strOsUserTheme = strOsUserTheme;
//
//      if (!m_ptaskOsUserTheme)
//      {
//
//         m_ptaskOsUserTheme = fork([this]()
//                                   {
//
//                                      preempt(1_s);
//
//                                      m_ptaskOsUserTheme = nullptr;
//
//                                      _apply_os_user_theme();
//
//                                   });
//
//      }
//
//   }



//   void node::_set_os_user_icon_theme(const ::scoped_string &strOsUserIconTheme)
//   {
//
//      m_strOsUserIconTheme = strOsUserIconTheme;
//
//      if (!m_ptaskOsUserTheme)
//      {
//
//         m_ptaskOsUserIconTheme = fork([this]()
//                                   {
//
//                                      preempt(1_s);
//
//                                      m_ptaskOsUserIconTheme = nullptr;
//
//                                      _apply_os_user_icon_theme();
//
//                                   });
//
//      }
//
//   }
//
//
//
//   void node::_apply_os_user_theme()
//   {
//
//      informationf("applying os user theme: \"" + m_strOsUserTheme + "\"\n");
//
//      //os_process_user_theme(m_strOsUserTheme);
//
//   }


//   ::string node::_get_os_user_theme()
//   {
//
//      ::string strGtkTheme;
//
//      if(gsettings_schema_contains_key("org.gnome.desktop.interface", "gtk-theme"))
//      {
//
//         information() << "org.gnome.desktop.interface schema contains \"gtk-theme\"";
//
//         if (gsettings_get(strGtkTheme, "org.gnome.desktop.interface", "gtk-theme"))
//         {
//
//            information() << "gtk-theme=\"" + strGtkTheme + "\"";
//
//         }
//
//      }
//
//      return strGtkTheme;
//
//   }


//   void node::_apply_os_user_icon_theme()
//   {
//
//      informationf("applying os user icon theme: \"" + m_strOsUserIconTheme + "\"\n");
//
//      //os_process_user_icon_theme(m_strOsUserIconTheme);
//
//   }


//   void node::os_process_user_theme(string strOsTheme)
//   {
//
//      informationf(
//              "os_process_user_theme: is strTheme(" + strOsTheme + ") same as m_strTheme(" + m_strTheme + ")\n");
//
//      if (strOsTheme == m_strTheme)
//      {
//
//         informationf(
//                 "os_process_user_theme: same theme as before [___new(" + strOsTheme + ") - old(" + m_strTheme + ")]\n");
//
//         return;
//
//      }
//
//      informationf(
//              "os_process_user_theme: different theme [___new(" + strOsTheme + ") - old(" + m_strTheme + ")]\n");
//
//      m_strTheme = strOsTheme;
//
//      informationf("os_process_user_theme m_strTheme = \"" + m_strTheme + "\"\n");
//
//      try
//      {
//
//         system()->signal(id_operating_system_user_theme_change);
//
//      }
//      catch (...)
//      {
//
//
//      }
//
//      _fetch_user_color();
//
////      if(!gsettings_schema_contains_key("org.gnome.desktop.interface", "color-scheme"))
////      {
////
////         _os_process_user_theme_color(m_strTheme);
////
////         fetch_user_color();
////
////      }
//
//   }


//   void node::os_process_user_icon_theme(string strOsIconTheme)
//   {
//
//      informationf(
//              "os_process_user_icon_theme: is strIconTheme(" + strOsIconTheme + ") same as m_strIconTheme(" + m_strIconTheme + ")\n");
//
//      if (strOsIconTheme == m_strIconTheme)
//      {
//
//         informationf(
//                 "os_process_user_icon_theme: same theme as before [___new(" + strOsIconTheme + ") - old(" + m_strIconTheme + ")]\n");
//
//         return;
//
//      }
//
//      informationf(
//              "os_process_user_icon_theme: different theme [___new(" + strOsIconTheme + ") - old(" + m_strIconTheme + ")]\n");
//
//      m_strIconTheme = strOsIconTheme;
//
//      informationf("os_process_user_icon_theme m_strIconTheme = \"" + m_strIconTheme + "\"\n");
//
//      try
//      {
//
//         system()->signal(id_operating_system_user_icon_theme_change);
//
//      }
//      catch (...)
//      {
//
//
//      }
//
////      if(!gsettings_schema_contains_key("org.gnome.desktop.interface", "color-scheme"))
////      {
////
////         _os_process_user_theme_color(m_strTheme);
////
////         fetch_user_color();
////
////      }
//
//   }


//   void node::_os_process_user_theme_color(string strTheme)
//   {
//
//      auto pthemecolors = _new_os_theme_colors(strTheme);
//
//      auto pthemecolorsOld = ::user::os_get_theme_colors();
//
//      if (!pthemecolorsOld || memcmp(pthemecolors, pthemecolorsOld, sizeof(::os_theme_colors)))
//      {
//
//         _set_os_theme_colors(pthemecolors);
//
//         //system()->signal(id_operating_system_user_color_change);
//
//      }
//      else
//      {
//
//         ::acme::del(pthemecolors);
//
//      }
//
//   }


//   void node::fetch_user_color()
//   {
//
//      _fetch_dark_mode();
//
////      auto pthemecolors = ::user::os_get_theme_colors();
////
////      if (!pthemecolors)
////      {
////
////         string strTheme = _os_get_user_theme();
////
////         information() << "node::fetch_user_color _os_get_user_theme(): " << strTheme;
////
////         pthemecolors = _new_os_theme_colors(strTheme);
////
////         _set_os_theme_colors(pthemecolors);
////
////      }
//
//   }


//   bool node::is_branch_current() const
//   {
//
//      return current_itask() == main_user_itask();
//
//   }


//   int node::os_launch_uri(const ::string &strUri, char *pszError, int iBufferSize)
//   {
//
//      int iRet = gdk_launch_uri(strUri, pszError, iBufferSize);
//
//      return iRet;
//
//   }


   void node::shell_launch(const ::string &strAppId)
   {

      string strDesktopFileTitle(strAppId);

      strDesktopFileTitle.find_replace("/", ".");

      ::file::path pathDesktop;

      pathDesktop = directory_system()->home() / ".local/share/applications" / (strDesktopFileTitle + ".desktop");

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

//                           m_mapGDesktopAppInfo[pathDesktop] = pgdesktopappinfo;

//                           if (!m_pgdkapplaunchcontext)
//                           {
//
//                              m_pgdkapplaunchcontext = gdk_display_get_app_launch_context(gdk_display_get_default());
//
//                           }

//                           if (!g_app_info_launch(G_APP_INFO(pgdesktopappinfo), plistFiles,
//                                                  G_APP_LAUNCH_CONTEXT(m_pgdkapplaunchcontext), &pgerror))
//                           {
//
//                              throw exception(error_failed);
//
//                           }

                        });

   }


   void node::open_url_link_at_system_browser(const ::string &strUrl, const ::string & strProfile)
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

//      if(!::node_gtk3::os_defer_init_gtk(this))
//      {
//
//         return ::error_failed;
//
//      }
//
//      if(::node_gtk3::get_display_type() == e_display_type_x11)
//      {
//
//         ::aura_posix::node::_allocate_Display_and_connection();
//
//      }

      return ::success;

   }


//   void node::_on_gtk_init()
//   {
//
////      if(m_edisplaytype == e_display_type_none)
////      {
////
////         m_edisplaytype = calculate_display_type();
////
////      }
//
//   }


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
//      if(!file_system()->exists(pathDesktopFile))
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
//      int iExitCode = node()->command_system(strCommand, 10_minutes);
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



   void node::set_file_extension_mime_type(string_array & straExtension, string_array & straMimeType)
   {

      auto c = minimum(straExtension.size(), straMimeType.size());

      for(::collection::index i = 0; i < c; i++)
      {

         ::string strExtension = straExtension[i];

         ::string strMimeType = straMimeType[i];

         _set_file_extension_mime_type(strExtension, strMimeType);

      }

   }


   void node::_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      _defer_set_file_extension_mime_type(scopedstrExtension, scopedstrMimeType);

   }


   void node::_defer_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      if(_system_is_set_file_extension_mime_type(scopedstrExtension, scopedstrMimeType))
      {

         return;

      }

      if(_user_is_set_file_extension_mime_type(scopedstrExtension, scopedstrMimeType))
      {

         return;

      }

      ::string strNewTypeFileName;

      strNewTypeFileName = scopedstrMimeType;

      strNewTypeFileName.find_replace("/", "-");

      ::string strXml = R"====(
<?xml version="1.0" encoding="UTF-8"?>
<mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
   <mime-type type="#mime_type#">
      <comment>#comment#</comment>
      <glob pattern="#glob_pattern#"/>
   </mime-type>
</mime-info>
)====";

      strXml.find_replace("#mime_type#", scopedstrMimeType);
      strXml.find_replace("#comment#", "\"" + scopedstrMimeType + "\" Mime Type recognized by \"" + scopedstrExtension + "\" file extension.");
      strXml.find_replace("#glob_pattern#", "*." + scopedstrExtension);

      ::file::path path;

      path = directory_system()->home();

      path /= ".local/share/mime/packages";

      path /= (strNewTypeFileName + ".xml");

      file()->put_text(path, strXml);

      int iUpdateMimeDatabaseError = ::system("update-mime-database \"" + path + "\"");

      if(iUpdateMimeDatabaseError)
      {

         information() << "Error while update-mime-database \"" << path << "\".";

      }

   }


   bool node::_system_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      ::string_array straMimeTypes;

      straMimeTypes = file()->lines("/etc/mime.types");

      ::collection::index iLine = 0;

      while(true)
      {

         ::string strExtensions;

         iLine = straMimeTypes.find_first_with_starting_word_eat(strExtensions, scopedstrMimeType, iLine);

         if (iLine < 0)
         {

            break;

         }

         information() << "strExtensions : \"" << strExtensions << "\"";

         ::string_array straExtensions;

         straExtensions.add_words(strExtensions);

         for(auto & str1 : straExtensions)
         {

            information() << "a extension : \"" << str1 << "\"";

         }

         if(straExtensions.contains(scopedstrExtension))
         {

            return true;

         }

         iLine++;

      }

      return false;

//      ::string strNewTypeFileName;
//
//      strNewTypeFileName = scopedstrMimeType;
//
//      strNewTypeFileName.find_replace("/", "-");
//
//      ::string strXml = R"====(
//<?xml version="1.0" encoding="UTF-8"?>
//<mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
//   <mime-type type="#mime_type#">
//      <comment>#comment#</comment>
//      <glob pattern="#glob_pattern#"/>
//   </mime-type>
//</mime-info>
//)====";
//
//      strXml.find_replace("#mime_type#", scopedstrMimeType);
//      strXml.find_replace("#comment#", "\"" + scopedstrMimeType + "\" Mime Type recognized by \"" + scopedstrExtension + "\" file extension.");
//      strXml.find_replace("#glob_pattern#", "*." + scopedstrExtension);
//
//      ::file::path path;
//
//      path = directory_system()->home();
//
//      path /= ".local/share/mime/packages";
//
//      path /= (strNewTypeFileName + ".xml");
//
//      file()->put_text(path, strXml);

   }


   bool node::_user_is_set_file_extension_mime_type(const scoped_string & scopedstrExtension, const scoped_string & scopedstrMimeType)
   {

      return false;

   }


//   void * node::fetch_windowing_system_display()
//   {
//
//      GdkDisplay *gdkdisplay;
//
//      gdkdisplay = gdk_display_get_default();
//
//      void * pvoidX11Display = gdk_x11_display_get_xdisplay(gdkdisplay);
//
//      printf("Got this Display from gdk_x11 display : %lX", (::uptr) pvoidX11Display);
//
//      return pvoidX11Display;
//
//   }


//   void node::windowing_system_async(const ::procedure &procedure)
//   {
//
//      gdk_branch(procedure);
//
//   }


//   void node::windowing_system_display_error_trap_push(int i)
//   {
//
//      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
//      {
//
//         GdkDisplay *gdkdisplay;
//
//         gdkdisplay = gdk_display_get_default ();
//         gdk_x11_display_error_trap_push (gdkdisplay);
//
//      }
//
//   }


//   void node::windowing_system_display_error_trap_pop_ignored(int i)
//   {
//
//      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
//      {
//
//         GdkDisplay *gdkdisplay;
//         gdkdisplay = gdk_display_get_default ();
//         gdk_x11_display_error_trap_pop_ignored (gdkdisplay);
//
//      }
//
//   }


//
//
//bool node::_g_defer_get_default_theme_icon(::string & strIconPath, GIcon * picon, int iSize)
//{
//
//   if(G_IS_THEMED_ICON(G_OBJECT(picon)))
//   {
//
//   GtkIconTheme *pGtkIconTheme= gtk_icon_theme_get_default();
//
//   if(pGtkIconTheme != nullptr) {
//
//      GtkIconInfo *pGtkIconInfo = gtk_icon_theme_lookup_by_gicon(pGtkIconTheme, picon, (gint) iSize,
//                                                                 GTK_ICON_LOOKUP_USE_BUILTIN);
//
//      if (pGtkIconInfo != nullptr)
//      {
//
//         const char *p = gtk_icon_info_get_filename(pGtkIconInfo);
//
//         if (p)
//         {
//
//            strIconPath = p;
//
//            return true;
//
//         }
//
//      }
//
//   }
//
//
//}
//
//   return false;
//
//}
//


//
//   ::logic::boolean g_bitLastDarkMode;
//
//
//   char *gsettings_get_malloc(const ::string & strSchema, const ::string & strKey);
//

   //CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme);

//   ::string_array node::_gsettings_schema_keys(const ::string & strSchema)
//   {
//
//      GSettingsSchema * pschema = g_settings_schema_source_lookup (
//              g_settings_schema_source_get_default(),
//              strSchema, FALSE);
//
//      if (::is_null(pschema))
//      {
//
//         return {};
//
//      }
//
//      auto ppchar = g_settings_schema_list_keys (pschema);
//
//      if(::is_null(ppchar))
//      {
//
//         g_settings_schema_unref (pschema);
//
//         return {};
//
//      }
//
//      ::string_array stra;
//
//      auto pp = ppchar;
//
//      while(*pp)
//      {
//
//         stra.add(*pp);
//
//         g_free(*pp);
//
//         pp++;
//
//      }
//
//      g_free(ppchar);
//
//      g_settings_schema_unref (pschema);
//
//      return ::transfer(stra);
//
//   }
//
//
//   bool node::gsettings_schema_contains_key(const ::string & strSchema, const ::string & strKey)
//   {
//
//      auto stra = gsettings_schema_keys(strSchema);
//
//      return stra.contains(strKey);
//
//   }
//
//
//   bool node::gsettings_schema_exists(const ::string & strSchema)
//   {
//
//      GSettingsSchema * pschema = g_settings_schema_source_lookup (
//              g_settings_schema_source_get_default(),
//              strSchema, FALSE);
//
//      if (::is_null(pschema))
//      {
//
//         return false;
//
//      }
//
//      g_settings_schema_unref (pschema);
//
//      return true;
//
//   }
//
//
//   ::e_status node::gsettings_get(string &str, const ::string & strSchema, const ::string & strKey)
//   {
//
//      char *psz = gsettings_get_malloc(strSchema, strKey);
//
//      if (psz == nullptr)
//      {
//
//         return ::error_failed;
//
//      }
//
//      try
//      {
//
//         str = psz;
//
//      }
//      catch (...)
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
//      catch (...)
//      {
//
//      }
//
//      return ::success;
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
//   ::e_status node::gsettings_set(const ::string & strSchema, const ::string & strKey, const ::string & strValue)
//   {
//
//      if (strSchema.is_empty())
//      {
//
//         return error_bad_argument;
//
//      }
//
//      if (strKey.is_empty())
//      {
//
//         return error_bad_argument;
//
//      }
//
////      ::pointer < ::node_gtk3::node > pgtknode = ::platform::get()->system()->node();
////
////      if (!os_defer_init_gtk(pgtknode))
////      {
////
////         return ::error_failed;
////
////      }
//
//      GSettings *settings = g_settings_new(strSchema);
//
//      if (settings == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      gboolean bOk = g_settings_set_string(settings, strKey, strValue);
//
//      g_object_unref(settings);
//
//      if(!bOk)
//      {
//
//         return error_failed;
//
//      }
//
//      return ::success;
//
//   }
//
//
//   ::e_status gsettings_sync()
//   {
//
////      ::pointer < ::node_gtk3::node > pgtknode = ::platform::get()->system()->node();
////
////      if (!os_defer_init_gtk(pgtknode))
////      {
////
////         return ::error_failed;
////
////      }
//
//      ::g_settings_sync();
//
//      return ::success;
//
//   }
//
//
//   char * gsettings_get_malloc(const ::string & strSchema, const ::string & strKey)
//   {
//
//      if (strSchema.is_empty())
//      {
//
//         return nullptr;
//
//      }
//
//      if (strKey.is_empty())
//      {
//
//         return nullptr;
//
//      }
//
////      ::pointer < ::node_gtk3::node > pgtknode = ::platform::get()->system()->node();
////
////      if (!os_defer_init_gtk(pgtknode))
////      {
////
////         return nullptr;
////
////      }
//
//      GSettings *settings = g_settings_new(strSchema);
//
//      if (settings == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      gchar *pgchar = g_settings_get_string(settings, strKey);
//
//      if (pgchar == nullptr)
//      {
//
//         g_object_unref(settings);
//
//         return nullptr;
//
//      }
//
//      char *psz = strdup(pgchar);
//
//      g_free(pgchar);
//
//      g_object_unref(settings);
//
//      return psz;
//
//   }


//   void wallpaper_change_notification(GSettings *settings, const gchar *pszKey, gpointer pdata)
//   {
//
//      ::node_gdk::node * pnode = (::node_gdk::node *) pdata;
//
//      pnode->system()->signal(id_wallpaper_change);
//
//   }
//
//
//   GAction *g_pactionWallpaper = nullptr;
//
//
//   ::e_status node_enable_wallpaper_change_notification(::node_gdk::node * pnode, const ::string & strSchema, const ::string & strKey)
//   {
//
////      if (!g_bGInitialized)
////      {
////
////         return error_not_initialized;
////
////      }
////
////      pmutex_lock lock(&g_mutexG);
//
//      if (g_pactionWallpaper != nullptr)
//      {
//
//         return ::success;
//
//      }
//
//      GSettings *settings = g_settings_new(strSchema);
//
//      if (settings == nullptr)
//      {
//
//         return error_failed;
//
//      }
//
//      g_pactionWallpaper = g_settings_create_action(settings, strKey);
//
//      g_object_unref(settings);
//
//      g_signal_connect (g_pactionWallpaper, "notify::state", G_CALLBACK(wallpaper_change_notification), pnode);
//
//      return ::success;
//
//   }

//
//   void g_defer_init()
//   {
////
////      if (g_bGInitialized)
////      {
////
////         return;
////
////      }
////
////      g_bGInitialized = true;
////
////      pthread_mutex_init(&g_mutexG, nullptr);
//
//   }
//
//
//   void g_defer_term()
//   {
//
////      if (!g_bGInitialized)
////      {
////
////         return;
////
////      }
////
////      g_bGInitialized = false;
//
//      if (g_pactionWallpaper != nullptr)
//      {
//
//         g_object_unref(g_pactionWallpaper);
//
//         g_pactionWallpaper = nullptr;
//
//      }
//
//      //pthread_mutex_destroy(&g_mutexG);
//
//   }


//   ::string node::_g_get_file_icon_path(const char * pszPath, int iSize)
//   {
//
//      GFile * pfile = g_file_new_for_path (pszPath);
//
//      if(pfile == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      GError * perror = nullptr;
//
//      GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);
//
//      if(pfileinfo == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      /* you'd have to use g_loadable_icon_load to get the actual icon */
//      GIcon * picon = g_file_info_get_icon (pfileinfo);
//
//      if(picon == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      if(G_IS_FILE_ICON(G_OBJECT(picon)))
//      {
//
//         GFileIcon * pfileicon = G_FILE_ICON(G_OBJECT(picon));
//
//         if(pfileicon == nullptr)
//         {
//
//            return nullptr;
//
//         }
//
//         GFile * pfileIcon = g_file_icon_get_file(pfileicon);
//
//         if(pfileIcon == nullptr)
//         {
//
//            return nullptr;
//
//         }
//
//         char * psz = strdup(g_file_get_path(pfileIcon));
//
//         return psz;
//
//      }
//      else
//      {
//
//         ::string strIconPath;
//
//         if(_g_defer_get_default_theme_icon(strIconPath, picon, iSize))
//         {
//
//            return strIconPath;
//
//         }
//
//      }
//
//      return {};
//
//   }
//
//
//   bool node::_g_defer_get_default_theme_icon(::string & strIconPath, GIcon * picon, int iSize)
//   {
//
//      return false;
//
//   }


//   const char * g_get_file_content_type(const char * pszPath)
//   {
//
//      GFile * pfile = g_file_new_for_path (pszPath);
//
//      if(pfile == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      GError * perror = nullptr;
//
//      GFileInfo * pfileinfo = g_file_query_info (pfile, "standard::*", G_FILE_QUERY_INFO_NONE, nullptr, &perror);
//
//      if(pfileinfo == nullptr)
//      {
//
//         return nullptr;
//
//      }
//
//      const char * pszContentType = g_file_info_get_content_type (pfileinfo);
//
//      const char * point = nullptr;
//
//      if(pszContentType != nullptr)
//      {
//
//         point = strdup(pszContentType);
//
//      }
//
//      return point;
//
//   }



//   int gdk_launch_uri(const char * pszUri, char * pszError, int iBufferSize)
//   {
//
//      gboolean ret;
//
//      GError * error = nullptr;
//
//      //g_type_init();
//
//      ret = g_app_info_launch_default_for_uri(pszUri, nullptr, &error);
//
//      if(ret)
//      {
//
//         return true;
//
//      }
//
//      if(pszError != nullptr)
//      {
//
//         strncpy(pszError, error->message, iBufferSize);
//
//      }
//
//      return 0;
//
//   }

//
//   gboolean gdk_callback_run_runnable(gpointer pdata)
//   {
//
//      auto pparticle = (::subparticle *) pdata;
//
//      try
//      {
//
//         pparticle->run();
//
//      }
//      catch(...)
//      {
//
//      }
//
//      ::release(pparticle);
//
//      return FALSE;
//
//   }
//
//
//   void gdk_branch(const ::procedure & procedure)
//   {
//
//      ::subparticle * pbase = procedure.m_pbase;
//
//      ::increment_reference_count(pbase);
//
//      //synchronous_lock synchronouslock (user_synchronization());
//
//      auto psource = g_idle_source_new();
//
//      g_source_set_priority(psource, G_PRIORITY_DEFAULT);
//
//      g_source_set_callback(psource, &gdk_callback_run_runnable, pbase, nullptr);
//
//      g_source_attach(psource, g_main_context_default());
//
//   }
//
//
//   void g_safe_free(void * pfree)
//   {
//
//      if(pfree == nullptr)
//      {
//
//         return;
//
//      }
//
//      ::g_free(pfree);
//
//   }
//

   void gtk_defer_do_main_tasks()
   {

      if(!::is_main_thread())
      {

         return;

      }

      for(int i = 0; i < 10 && gtk_events_pending(); i++)
      {

         gtk_main_iteration();

      }

   }


   void node::defer_innate_ui()
   {

      auto pfactory = system()->factory("innate_ui", "gtk3");

      pfactory->merge_to_global_factory();

   }


   void node::defer_show_system_menu(::user::mouse * pmouse)
   {

      //::node_gdk::node::defer_show_system_menu(pmouse);

//      // Create a popup menu
//      auto menu = gtk_menu_new();
//
//      // Create and add menu items
//      auto item = gtk_menu_item_new_with_label("Menu Item 1");
//      gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
//      gtk_widget_show(item);
//
//      item = gtk_menu_item_new_with_label("Menu Item 2");
//      gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
//      gtk_widget_show(item);
//
//      // Show the menu
//      gtk_menu_popup_at_pointer(GTK_MENU(menu), NULL);
//      //::pointer < ::windows::micro::user >pnanouserWindows = system()->acme_windowing();
//
//      //pnanouserWindows->_defer_show_system_menu(m_hwnd, &m_hmenuSystem, pointAbsolute);
//
//      //_defer_show_system_menu(pointAbsolute);


   }


   //gdk_branch(procedure);
   // Function to be run in the GTK main thread
   gboolean __g_callback(gpointer data)
   {

      auto pprocedure = (procedure*)(data);

      try
      {

         (*pprocedure)();

      }
      catch(...)
      {

      }

      try
      {

         delete pprocedure;

      }
      catch(...)
      {

      }

      return FALSE;  // Returning FALSE so it is only called once

   }


   void node::user_post(const ::procedure &procedure)
   {

      auto pprocedure = ___new ::procedure(procedure);

      // Call update_label in the GTK main thread
      g_idle_add(__g_callback, pprocedure);

   }


} // namespace node_gtk3


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


//gboolean windowing_message_loop_source_function(gpointer p)
//{
//
//   ::node_gtk3::node *pnode = (::node_gtk3::node *) p;
//
//   try
//   {
//
//      if (!pnode->windowing_message_loop_step())
//      {
//
//         return FALSE;
//
//      }
//
//   }
//   catch(...)
//   {
//
//
//   }
//
//   return TRUE;
//
//}
//
//
//void windowing_message_loop_add_idle_source(::node_gtk3::node *pnode)
//{
//
//   gdk_threads_add_idle(&windowing_message_loop_source_function, pnode);
//
//}


bool x11_message_handler(XEvent *pevent);


GdkFilterReturn x11_event_func(GdkXEvent *xevent, GdkEvent *event, gpointer data)
{

   XEvent *pevent = (XEvent *) xevent;

   ::node_gtk3::node *pnode = (::node_gtk3::node *) data;

   auto pwindowing = pnode->windowing();

   if(::is_set(pwindowing))
   {

      pwindowing->_message_handler(pevent);

   }

   return GDK_FILTER_CONTINUE;

}


// This seems not to work with "foreign" windows
// (X11 windows not created with Gdk)
void x11_add_filter(void * p)
{

   // This seems not to work with "foreign" windows
   // (X11 windows not created with Gdk)
   gdk_window_add_filter(nullptr, &x11_event_func, p);

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
//
//
//
//void os_post_quit()
//{
//
//   auto idle_source = g_idle_source_new();
//
//   g_source_set_callback(idle_source, &gtk_quit_callback, nullptr, nullptr);
//
//   g_source_attach(idle_source, g_main_context_default());
//
//}
//
//


