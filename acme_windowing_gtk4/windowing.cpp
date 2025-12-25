//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
#include "windowing.h"
#include "acme/constant/windowing2.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/integrate/cairo.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/handler/request.h"
#include "acme_windowing_g/gdk_3_and_4.h"
#include "acme/platform/system.h"
#include "acme/operating_system/summary.h"
//#include <X11/Xatom.h>
//#include <xkbcommon/xkbcommon.h>
//#include <X11/XKBlib.h>
//#include <X11/Xutil.h>
bool wouldnt_create_gl_context();
//extern "C" int jail_getid(const char *name);
#include <stdio.h>
#include <unistd.h>
//#include <sys/param.h>
//#include <sys/jail.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_dbus_session_running(void)
{
    //FILE *fp = popen("ps -axo comm", "r");
    FILE *fp = popen("ps -aux comm", "r");
    if (!fp) return 0;

    char buf[256];
    int found = 0;
    while (fgets(buf, sizeof(buf), fp))
    {
        // Remove trailing newline
        buf[strcspn(buf, "\n")] = 0;
        if (strcmp(buf, "dbus-daemon") == 0)
        {
            found = 1;
            break;
        }
    }
    pclose(fp);
    return found;
}


CLASS_DECL_ACME void set_main_user_thread();
//extern int __argc;
//extern char ** __argv;
//#include "acme/graphics/image/pixmap.h"
//#include <gtk/gtk.h>
//
// Function to convert GdkPixbuf to cairo_surface_t
cairo_surface_t* cairo_surface_from_gdk_pixbuf(GdkPixbuf* pixbuf)
{
   cairo_format_t format;
   int width, height, stride;
   GdkPixbuf* pixbuf_with_alpha = NULL;
   cairo_surface_t* surface;
   cairo_t* cr;

   width = gdk_pixbuf_get_width(pixbuf);
   height = gdk_pixbuf_get_height(pixbuf);
   stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, width);

   // Create an empty cairo surface to hold the image
   surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

   // Create a Cairo context
   cr = cairo_create(surface);

   // Create GdkPixbuf with alpha if it's not present
   if (!gdk_pixbuf_get_has_alpha(pixbuf))
   {
      pixbuf_with_alpha = gdk_pixbuf_add_alpha(pixbuf, FALSE, 0, 0, 0);
      pixbuf = pixbuf_with_alpha;
   }

   // Paint the GdkPixbuf onto the Cairo surface
   //cairo_set_so
   gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
   cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
   cairo_paint(cr);

   // Cleanup
   cairo_destroy(cr);
   if (pixbuf_with_alpha)
      g_object_unref(pixbuf_with_alpha);

   return surface;
}


// Sample JPEG data in memory (you would typically load this from a file or network)
//const unsigned char jpeg_data[] = { /* ... your JPEG data here ... */ };
//gsize jpeg_data_size = sizeof(jpeg_data);
cairo_surface_t* cairo_surface_from_file_in_memory(const void* p, memsize size)
{
   // Load JPEG image from memory into GdkPixbuf
   GdkPixbufLoader* loader = gdk_pixbuf_loader_new();
   GError * pgerror = NULL;

   if (!gdk_pixbuf_loader_write(loader, (const guchar*)p, size, &pgerror))
   {
      if (pgerror)
      {
         g_printerr("Error loading image: %s\n", pgerror->message);
         g_error_free(pgerror);
         pgerror = nullptr;
      }
      g_object_unref(loader);
      throw ::exception(error_failed);
   }
   if (pgerror)
   {
      g_error_free(pgerror);
      pgerror = nullptr;
   }

   gdk_pixbuf_loader_close(loader, NULL);

   // Get the GdkPixbuf from the loader
   GdkPixbuf* pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);

   if (!pixbuf)
   {
      g_printerr("Failed to load image.\n");
      g_object_unref(loader);
      throw ::exception(error_failed);
   }

   auto psurface = cairo_surface_from_gdk_pixbuf(pixbuf);

   // Cleanup
   g_object_unref(loader);

   return psurface;

}


namespace gtk4
{


   namespace acme
   {


      namespace windowing
      {


         windowing::windowing()
         {

            m_pgtkapplication = nullptr;

            m_pGtkSettingsDefault = nullptr;

m_bMessageThread=true;
            //m_pGtkSettingsDefault = nullptr;
gtk_init();
            if (wouldnt_create_gl_context())
            {

               g_setenv("GDK_GL", "disable", TRUE);

            }

         }


         windowing::~windowing()
         {


            if (m_pGtkSettingsDefault)
            {

               g_object_unref(m_pGtkSettingsDefault);

               m_pGtkSettingsDefault = nullptr;

            }

         }


         // ::e_status windowing::defer_initialize_windowing()
         // {
         //
         //    //      if (m_estatusInitializeX11 == error_not_initialized)
         //    //      {
         //    //
         //    //         m_estatusInitializeX11 = initialize_windowing();
         //    //
         //    //      }
         //    //
         //    //      return m_estatusInitializeX11;
         //
         //    return ::success;
         //
         // }


         void windowing::initialize_windowing()
         {

            informationf("node_gtk3::node::x11_initialize");

            informationf("node_gtk3::node::x11_initialize going to call x11_init_threads");

            if (!system()->acme_windowing()->init_threads())
            {

               //return ::error_failed;

               return;

            }

            // gdk_x11 does error handling?!?!?!
            //XSetErrorHandler(_c_XErrorHandler);

            //g_pmutexX11 = ___new ::pointer < ::mutex >();

            //return ::success;

         }


         void windowing::destroy()
         {

            m_procedurelist.clear();

            m_procedurelistPriority.clear();

            m_callbackOnActivateGtkApplication.clear();

            m_phappeningCreatingWGtk4Display.defer_destroy();

            ::acme::windowing::windowing::destroy();

         }






         // void* windowing::get_display()
         // {
         //
         //    //return ::platform::node::x11_get_display();
         //
         //    //defer_initialize_windowing();
         //
         //    //      if(m_pvoidX11Display == NULL)
         //    //      {
         //    //
         //    //         m_pvoidX11Display = fetch_windowing_display();
         //    //
         //    //      }
         //    //
         //    //      return m_pvoidX11Display;
         //
         //    return nullptr;
         //
         // }


         bool windowing::is_branch_current() const
         {

            auto itaskCurrent = ::current_itask();

            return itaskCurrent == m_itask;


         }


         gboolean gtk_application_quit_callback(gpointer p)
         {

            auto* pgapplication = (GApplication*)p;

            g_application_quit(pgapplication);

            return FALSE;

         }


         void windowing::windowing_post_quit()
         {

            g_idle_add(gtk_application_quit_callback, G_APPLICATION(m_pgtkapplication));

         }


         void windowing::_user_send(const ::procedure& procedure)
         {

            if (::is_main_thread())
            {

               procedure();

               return;

            }

            //__matter_send_procedure(this, this, &node::node_post, procedure);

            //      CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
            //      {

            auto pevent = øallocate manual_reset_happening();

            _user_post([ procedure, pevent ]
            {

               procedure();

               pevent->set_happening();

            });

            if (!pevent->wait(procedure.timeout()))
            {

               if (::task_get_run())
               {
                  throw ::exception(error_timeout);
               }
               else
               {

                  information() << "thread terminating?!?!";

               }
               //pevent.release();

               //return false;

            }

            ///return true;
            //
            //      }


         }


         // The function to be called in the main thread
         static gboolean execute_on_main_thread(gpointer data)
         {

            auto* pprocedure = (::procedure*)data;

            (*pprocedure)();

            delete pprocedure;

            return FALSE;
         }


         void windowing::_user_post(const ::procedure& procedure)
         {

            // Safely update the GTK label in the main thread
            g_main_context_invoke(NULL, execute_on_main_thread, øraw_new ::procedure(procedure));

         }


         void windowing::_main_send(const ::procedure& procedure)
         {

            _user_send(procedure);

         }


         void windowing::_main_post(const ::procedure& procedure)
         {

            _user_post(procedure);

         }

         // void windowing::main_post(const ::procedure& procedure)
         // {
         //
         //
         //    // Safely update the GTK label in the main thread
         //    g_main_context_invoke(NULL, execute_on_main_thread, ___new ::procedure(procedure));
         //
         // }


         void windowing::display_error_trap_push(int i)
         {


            //node()->windowing_display_error_trap_push(i);

            //      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
            //      {
            //
            //         GdkDisplay *gdkdisplay;
            //
            //         gdkdisplay = gdk_display_get_default ();
            //         gdk_x11_display_error_trap_push (gdkdisplay);
            //
            //      }

         }


         void windowing::display_error_trap_pop_ignored(int i)
         {

            //node()->windowing_display_error_trap_pop_ignored(i);
            //      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
            //      {
            //
            //         GdkDisplay *gdkdisplay;
            //         gdkdisplay = gdk_display_get_default ();
            //         gdk_x11_display_error_trap_pop_ignored (gdkdisplay);
            //
            //      }

         }


         //
         //    void node::sync(const ::procedure & procedure)
         //    {
         //
         //        system()->acme_windowing()->x11_sync(procedure);
         //
         //    }
         //
         //
         //    void node::async(const ::procedure & procedure)
         //    {
         //
         //        system()->acme_windowing()->x11_async(procedure);
         //
         //    }
         //
         //
         //    void node::display_error_trap_push(int i)
         //    {
         //
         //
         //    }
         //
         //
         //    void node::display_error_trap_pop_ignored(int i)
         //    {
         //
         //
         //    }


         extern "C" void on_activate_gtk_application(GtkApplication*, gpointer p)
         {

            auto* pgtk4windowingsystem = (::gtk4::acme::windowing::windowing*)p;
            
            ::information() << "gtk4::acme::windowing::on_activate_gtk_application";

            pgtk4windowingsystem->_hook_system_theme_change_callbacks();

            pgtk4windowingsystem->fetch_dark_mode();

            pgtk4windowingsystem->_on_activate_gtk_application();

         }


         extern "C" void on_open_gtk_application(
                                              GApplication* self,
                                              gpointer files,
                                              gint n_files,
                                              gchar* hint,
                                              gpointer p
                                            )
         {

            auto* pgtk4windowingsystem = (::gtk4::acme::windowing::windowing*)p;

            ::information() << "gtk4::acme::windowing::on_open_gtk_application";

            pgtk4windowingsystem->_hook_system_theme_change_callbacks();

            pgtk4windowingsystem->fetch_dark_mode();

            pgtk4windowingsystem->_on_activate_gtk_application();

         }


         void windowing::windowing_application_main_loop()
         {

            __task_init();

            main();

         }


         bool windowing::handle_messages()
         {

            return true;

            // auto pgmaincontext = g_main_context_default();
            //
            // g_main_context_iteration(pgmaincontext, FALSE);
            //
            // return true;

         }


         void windowing::run()
         {



             //int main(void) {
                 //int jid = jail_getid(".");
                 //if (jid < 0) {
                   //  //perror("jail_getid");
                    // information() << "Process is not in a jail?!?";
                 //} else {
                   //  informationf("Process is in jail ID: %d\n", jid);
                 //}
               //  return 0;
             //}



			   information() << "gtk4::acme::windowing::windowing::run";

            ::string strId = application()->m_strAppId;

            strId.find_replace("/", ".");

            strId.find_replace("_", "-");

            //gtk_init();
            
            information() << "application id: " << strId;

            ::set_main_user_thread();

            //if (!g_dbus_is_address("unix:path=/tmp")) // or more properly:
            int iExtraFlags = 0;
            ::string strDbusSessionBusAddress(node()->get_environment_variable("DBUS_SESSION_BUS_ADDRESS"));
            ::string strDbusFile;
            if(strDbusSessionBusAddress.begins_eat("unix:path="))
            {
                strDbusFile = strDbusSessionBusAddress.get_word(",");
                warning() <<  "D-Bus file should be: " << strDbusFile;
            }
            bool bDbusFileExists = file()->exists(strDbusFile);
            if(bDbusFileExists)
            {
               information("D-Bus file exists (path=\"{}\")", strDbusFile);
            }
            else
            {
                warning("D-Bus file doesn't exist (path=\"{}\")", strDbusFile);
            }
            bool bDbusSessionRunning =is_dbus_session_running();
            if(bDbusSessionRunning)
            {
               information("D-Bus session is running (dbus-daemon process found)");
            }
            else
            {
                warning("D-Bus session isn't running (dbus-daemon process not found)");
            }
            if(!bDbusFileExists || !bDbusSessionRunning)
            {
                warning() <<  "No D-Bus session detected — falling back to non-unique mode";
                iExtraFlags = G_APPLICATION_NON_UNIQUE;
            }

#if GLIB_CHECK_VERSION(2,74,0)

            m_pgtkapplication = gtk_application_new(strId,(GApplicationFlags)( iExtraFlags|G_APPLICATION_HANDLES_OPEN));

#else

            m_pgtkapplication = gtk_application_new(strId, (GApplicationFlags)( iExtraFlags|G_APPLICATION_HANDLES_OPEN));

#endif

            g_signal_connect(m_pgtkapplication, "activate", G_CALLBACK(on_activate_gtk_application), this);

            g_signal_connect(m_pgtkapplication, "open", G_CALLBACK(on_open_gtk_application), this);

            // // Retrieve system settings and listen for changes in dark mode preference
            // GtkSettings *settings = gtk_settings_get_default();
            // //update_theme_based_on_system(settings, NULL); // Check initial state
            // //g_signal_connect(settings, "notify::gtk-application-prefer-dark-theme", G_CALLBACK(update_theme_based_on_system), NULL);
            //
            // // Get the current GTK theme name (or any other available property)
            // //gboolean b=1;
            // g_object_set(settings, "gtk-application-prefer-dark-theme", TRUE, NULL);
            // //g_print("Current theme: %s\n", theme_name);
            //
            // // Free the allocated string after use
            // //g_free(theme_name);
            //
            // ///GtkSettings *settings = gtk_settings_get_default();
            // g_object_set(settings, "gtk-enable-animations", FALSE, NULL);

            g_application_hold(G_APPLICATION(m_pgtkapplication));


            // if(m_pdisplay->is_wayland())
            // {
            //
            //
            //
            // }

            information() << "gtk4::acme::windowing::windowing::run g_application_run";

            auto pplatform = ::system();

            auto argc = pplatform->get_argc();

            auto args = pplatform->get_args();

            information() << "gtk4::acme::windowing::windowing::run argc " << argc;

            for(int i = 0; i <= argc; i++)
            {

                if(!args[i])
                {
                    information("gtk4::acme::windowing::windowing::run args[{}] = (nullptr) ", i);
                    }
                    else
                    {
                    information("gtk4::acme::windowing::windowing::run args[{}] = ({}){} ", i, (iptr)args[i], args[i]);
                    }

            }

            //information() << "gtk4::acme::windowing::windowing::run __argc " << __argc;

            //for(int i = 0; i < __argc; i++)
            //{

            //    information("gtk4::acme::windowing::windowing::run args[{}] = ({}){} ", i, (iptr)__argv[i],__argv[i]);

            //}

            g_application_run(G_APPLICATION(m_pgtkapplication), argc, args);

            //g_application_run(G_APPLICATION(m_pgtkapplication), __argc, __argv);

            // //g_application_run (G_APPLICATION(m_pgtkapplication), ::system()->get_argc(), ::system()->get_args());
            // //aaa_x11_main();
            //
            //
            // while(::task_get_run())
            // {
            //
            //    preempt(1_s);
            //
            // }

            // if(::system()->m_pmanualresethappeningMainLoopEnd)
            // {
            //
            //    ::system()->m_pmanualresethappeningMainLoopEnd->set_happening();
            //
            // }

         }


         void windowing::__task_suffix()
         {

            windowing_post_quit();

         }


         void windowing::_on_activate_gtk_application()
         {

            if (m_callbackOnActivateGtkApplication)
            {

               m_callbackOnActivateGtkApplication();

               return;

            }

            //system()->defer_post_initial_request();

            ::information() << "gtk4::acme::windowing::_on_activate_gtk_application";

            system()->post_application_start();
            system()->defer_post_application_start_file_open_request();
            system()->post_application_started();

         }


         void windowing::process_messages()
         {

            GMainContext* context = g_main_context_default();

            g_main_context_iteration(context, FALSE);

         }


         void windowing::windowing_application_on_system_start()
         {

            system()->on_branch_system_from_main_thread_startup(this);

         }


         // Function to resize the cairo_surface_t to 1x1 with the average color
         ::color::color cairo_surface_average_color(cairo_surface_t* original_surface)
         {

            int width = cairo_image_surface_get_width(original_surface);

            int height = cairo_image_surface_get_height(original_surface);

            if (cairo_image_surface_get_format(original_surface) != CAIRO_FORMAT_ARGB32)
            {

               throw ::exception(error_bad_argument);

            }

            unsigned char* data = cairo_image_surface_get_data(original_surface);

            int stride = cairo_image_surface_get_stride(original_surface);

            unsigned long long sum_r = 0, sum_g = 0, sum_b = 0, sum_a = 0;

            for (int y = 0; y < height; ++y)
            {

               unsigned char* row = data + y * stride;

               for (int x = 0; x < width; ++x)
               {

                  unsigned char b = row[x * 4 + 0];
                  unsigned char g = row[x * 4 + 1];
                  unsigned char r = row[x * 4 + 2];
                  unsigned char a = row[x * 4 + 3];

                  sum_r += r;
                  sum_g += g;
                  sum_b += b;
                  sum_a += a;

               }

            }

            int num_pixels = width * height;

            unsigned char avg_r = sum_r / num_pixels;
            unsigned char avg_g = sum_g / num_pixels;
            unsigned char avg_b = sum_b / num_pixels;
            unsigned char avg_a = sum_a / num_pixels;

            return ::argb(avg_a, avg_r, avg_g, avg_b);

         }


         void gtk_settings_gtk_theme_name_callback(GObject* object, GParamSpec* pspec, gpointer data);


         void gtk_settings_gtk_icon_theme_name_callback(GObject* object, GParamSpec* pspec, gpointer data);


         void color_scheme_change(GSettings* settings, const gchar* pszKey, gpointer pdata)
         {

            auto* pgtk4windowingsystem = (::gtk4::acme::windowing::windowing*)pdata;

            pgtk4windowingsystem->_on_color_scheme_change();

         }


         void windowing::_on_color_scheme_change()
         {

            fetch_dark_mode();

         }


         void windowing::_hook_system_theme_change_callbacks()
         {

            auto pgtksettingsDefault = gtk_settings_get_default();

            if (pgtksettingsDefault)
            {

               m_pGtkSettingsDefault = G_OBJECT(pgtksettingsDefault);

               g_object_ref(m_pGtkSettingsDefault);

               if (!m_pactionColorScheme)
               {

                  GSettings* settings = g_settings_new("org.gnome.desktop.interface");

                  if (settings)
                  {

                     m_pactionColorScheme = g_settings_create_action(settings, "color-scheme");

                     g_object_unref(settings);

                     if (m_pactionColorScheme)
                     {

                        g_signal_connect(m_pactionColorScheme, "notify::state", G_CALLBACK(color_scheme_change), this);

                     }

                  }

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


            }

         }


         ::color::color windowing::get_operating_system_background_color()
         {

            int width = 32;

            int height = 32;

            GtkWidget * widget = gtk_application_window_new(m_pgtkapplication);

            gtk_window_set_decorated(GTK_WINDOW(widget), false);

            gtk_widget_set_size_request(widget, width, height);

            GtkStyleContext * style_context = gtk_widget_get_style_context(widget);

            cairo_surface_t * surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

            cairo_t * cr = cairo_create(surface);

            gtk_render_background(style_context, cr, 0, 0, width, height);

            auto color = cairo_surface_average_color(surface);

            cairo_surface_destroy(surface);

            return color;
         }


         void windowing::fetch_dark_mode()
         {

            information() << "::::gtk4::acme::windowing::windowing::_fetch_dark_mode";

            ::string strColorScheme;

            auto estatus = ::gdk::gsettings_get(strColorScheme, "org.gnome.desktop.interface", "color-scheme");

            if (strColorScheme.case_insensitive_equals("prefer-dark"))
            {

               g_object_set(m_pGtkSettingsDefault, "gtk-application-prefer-dark-theme", TRUE, NULL);

            }
            else
            {

               g_object_set(m_pGtkSettingsDefault, "gtk-application-prefer-dark-theme", FALSE, NULL);

            }

            auto color = get_operating_system_background_color();

            on_system_dark_mode_change(color.get_luminance() <= 0.5, color);

            // auto psystem = system();

            // psystem->background_color(color);

            // gtk_widget_realize(widget);

            // GdkPaintable *paintable = gtk_widget_paintable_new (GTK_WIDGET(widget));
            // GtkSnapshot *snapshot = gtk_snapshot_new();
            // graphene_rect_t bounds{{0.f, 0.f}, {(float)width, (float)height}};
            // gdk_paintable_snapshot (paintable, snapshot, width, height);
            // gtk_snapshot_append_cairo(snapshot, &bounds);
            // GskRenderNode *node = gtk_snapshot_free_to_node(snapshot);
            // auto surface = gsk_cairo_node_get_surface(node);

            //cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
            //cairo_t *cr = cairo_create(surface);

            // // Create a GskRenderNode to hold the widget's snapshot
            // GtkSnapshot *snapshot = gtk_snapshot_new();
            //
            // // Set the size of the widget before rendering
            // gtk_widget_set_size_request(widget, width, height);
            //
            // // Ensure the widget is realized (prepared for rendering)
            // gtk_widget_realize(widget);
            //
            // // Use the widget's class's snapshot method to take a snapshot of the widget
            // GtkWidgetClass *widget_class = GTK_WIDGET_GET_CLASS(widget);
            // widget_class->snapshot(widget, snapshot);
            //
            // // Retrieve the render node from the snapshot
            // GskRenderNode *node = gtk_snapshot_free_to_node(snapshot);

            // Draw the render node into the cairo surface
            //gsk_render_node_draw(node, cr);

            //   GtkStyleContext *style_context = gtk_widget_get_style_context(widget);
            //
            //     // Set the background color according to the label CSS style
            // gtk_render_background(style_context, cr, 0, 0, width, height);


            // Optionally save the Cairo surface as an image (e.g., PNG)
            //    cairo_surface_write_to_png(surface, "widget_snapshot.png");

            //       ::string strFile;
            // int i = 0;
            //       do
            //       {
            //          i++;
            // strFile.formatf("/home/camilo/test%02d.png", i);
            //
            //       }while (file_exists(strFile));
            //
            //       cairo_surface_write_to_png(surface, strFile);
            //
            //       print_line("Wrote: " + strFile);
            //       print_line("Wrote: " + strFile);

            // Clean up
            //cairo_destroy(cr);
            //cairo_surface_destroy(surface);
            //gsk_render_node_unref(node);

            ////GtkWidget *label = GTK_WIDGET(user_data);

            // // Get the style context of the label (to fetch CSS properties)
            // GtkStyleContext *style_context = gtk_widget_get_style_context(label);
            // cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
            // cairo_t *cr = cairo_create(surface);
            //
            // // Save the current state of the Cairo context
            // cairo_save(cr);
            //
            // // Set the background color according to the label CSS style      ::string strFile;
            // //      int i = 0;
            // //            do
            // //            {
            // //               i++;
            // //      strFile.formatf("/home/camilo/test%02d.png", i);
            // //
            // //            }while (file_exists(strFile));
            // //
            // //            cairo_surface_write_to_png(surface, strFile);
            // //
            // //            print_line("Wrote: " + strFile);
            // //            print_line("Wrote: " + strFile);
            // gtk_render_background(style_context, cr, 0, 0, width, height);
            //
            // // Restore the state of the Cairo context
            // cairo_restore(cr);


            //auto css_provider = gtk_css_provider_new ();
            // gtk_css_provider_load_from_string (
            //     css_provider,
            //     // rbga, `a` set to 0.0 makes the window background transparent
            //     ".window { background-color: rgba(0, 0, 0, 0.0); }");
            //
            // gtk_style_context_add_provider_for_display (
            //     gtk_widget_get_display (m_pgtkwidget),
            //     (GtkStyleProvider *) css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
            //
            // gtk_widget_add_css_class (m_pgtkwidget, "window");

            //       //gtk_box_append(GTK_BOX(box), label);
            //       //gtk_widget_set_size_request(t,32, 32);
            //       //gtk_widget_set_size_request(box,32, 32);
            //       gtk_widget_set_size_request(label,32, 32);
            //       //gtk_widget_set_visible(label, true);
            //       //gtk_widget_set_visible(box, true);
            //       //gtk_widget_realize(box);
            //       //gtk_widget_realize(label);
            //       //gtk_widget_set_visible(t, true);
            //
            //       //cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
            //       //cairo_t *cr = cairo_create(surface);
            //
            //       // Create a snapshot
            //       //GtkSnapshot *snapshot = gtk_snapshot_new();
            //
            //       ////graphene_rect_t bounds{{0.f, 0.f}, {(float)width, (float)height}};
            //
            //       ///gtk_snapshot_append_cairo(snapshot, &bounds);
            //
            //       // Render the label onto the surface
            //       //gtk_widget_snapshot_child(box, label, snapshot);
            //
            //       int cx1 = gtk_widget_get_width(label);
            //       int cy1 = gtk_widget_get_height(label);
            //
            // //      GskRenderNode *node = gtk_snapshot_free_to_node(snapshot);
            //       // int width = gtk_widget_get_width (GTK_WIDGET(label));
            //       // int height = gtk_widget_get_height (GTK_WIDGET(label));
            //
            //        int width = cx;
            //        int height = cy;
            //       // Get to the PNG image file from paintable
            //       GdkPaintable *paintable = gtk_widget_paintable_new (GTK_WIDGET(label));
            //       GtkSnapshot *snapshot = gtk_snapshot_new ();
            //       gdk_paintable_snapshot (paintable, snapshot, width, height);
            //       GskRenderNode *node = gtk_snapshot_free_to_node (snapshot);
            //
            //
            //       //snapshot = gtk_snapshot_new ();
            //       gtk_css_boxes_init_border_box (&boxes, style, 1, 1, w, h);
            //       gtk_css_style_snapshot_background (&boxes, snapshot);
            //       gtk_css_style_snapshot_border (&boxes, snapshot);
            //
            //       node = gtk_snapshot_free_to_node (snapshot);
            //       // GskRenderer *renderer = gsk_cairo_renderer_new ();
            //       // gsk_renderer_realize (renderer, NULL, NULL);
            //       // GdkTexture *texture = gsk_renderer_render_texture (renderer, node, NULL);
            //       // gdk_texture_save_to_png (texture, filename);
            //
            // Cleanup
            // g_object_unref(texture);
            // gsk_renderer_unrealize(renderer);
            // g_object_unref(renderer);
            // gsk_render_node_unref(node);
            // g_object_unref(paintable);

            //auto surface = gsk_cairo_node_get_surface(node);
            // //gsk_render_node_draw(node, cr);
            //        cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
            // //
            // //       // Create a cairo context for the surface
            //        cairo_t *cr = cairo_create(surface);
            // //
            // //       // Draw the render node to the Cairo context
            //       gsk_render_node_draw(node, cr);

            // graphene_rect_t bounds{{0.f, 0.f}, {(float)width, (float)height}};
            //
            // auto paitable = gtk_snapshot_free_to_paintable(snapshot, &r);

            // Save the surface as an image or manipulate it as needed
            //
            //       ::string strFile;
            // int i = 0;
            //       do
            //       {
            //          i++;
            // strFile.formatf("/home/camilo/test%02d.png", i);
            //
            //       }while (file_exists(strFile));
            //
            //       cairo_surface_write_to_png(surface, strFile);
            //
            //       print_line("Wrote: " + strFile);
            //       print_line("Wrote: " + strFile);
            //       // Clean up
            //       //cairo_destroy(cr);
            //       //cairo_surface_destroy(surface);
            // //       //gtk_widget_set_visible(window, true);
            // //       auto *paintable = gtk_widget_paintable_new(window);
            // //       GtkSnapshot *snapshot = gtk_snapshot_new();
            // //
            // //       int width = 32;
            // //       int height = 32;
            // //
            // //       // Render the GdkPaintable into the snapshot at the given size
            //       gdk_paintable_snapshot(GDK_PAINTABLE(paintable), snapshot, width, height);
            //
            //       // Get the GskRenderNode from the snapshot
            //       GskRenderNode *node = gtk_snapshot_free_to_node(snapshot);
            //       cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
            //
            //       // Create a cairo context for the surface
            //       cairo_t *cr = cairo_create(surface);
            //
            //       // Draw the render node to the Cairo context
            // //      gsk_render_node_draw(node, cr);
            //
            //       // Clean up
            //   //    g_object_unref(node);
            // //
            // //
            // //   //    Gtk
            // //
            //       int width = 32;
            //       int height = 32;
            //       gtk_window_set_default_size(GTK_WINDOW(t), width, height);
            //       // Create a ___new GtkBox (vertical layout)
            //       GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);  // 10px spacing between widgets
            //       gtk_window_set_child(GTK_WINDOW(t), box);
            //       gtk_box_append(GTK_BOX(box), window);
            //       gtk_widget_set_size_request(window,32, 32);
            //       gtk_widget_set_visible(window, true);
            //       gtk_widget_set_visible(t, true);
            //          //gtk_window_get_default_size(GTK_WINDOW(window), &width, &height);
            //
            //          // Create a ___new GtkSnapshot to capture the window contents
            //          GtkSnapshot *snapshot = gtk_snapshot_new();
            //
            //          // Create a rectangle of the same size as the window
            //          //graphene_rect_t bounds = GRAPHENE_RECT_INIT(0, 0, width, height);
            //
            //          // Render the window into the snapshot
            //          gtk_widget_snapshot_child(box, GTK_WIDGET(window), snapshot);

            // Get the GdkTexture from the snapshot
            //GskRenderNode *node = gtk_snapshot_free_to_node(snapshot);


            // // Paint the texture onto the cairo context
            // gsk_render_node_draw(node, cr);
            //
            // // Write the cairo surface to a PNG file
            // cairo_surface_write_to_png(surface, "/home/camilo/test.png");
            //
            // // Cleanup
            // cairo_destroy(cr);
            // cairo_surface_destroy(surface);
            //}

            // if(gsettings_schema_exists("org.gnome.desktop.interface"))
            // {
            //
            //    information() << "org.gnome.desktop.interface exists";
            //
            //    if(gsettings_schema_contains_key("org.gnome.desktop.interface", "color-scheme"))
            //    {
            //
            //       information() << "org.gnome.desktop.interface contains \"color-scheme\"";
            //
            //       ::string strColorScheme;
            //
            //       if (gsettings_get(strColorScheme, "org.gnome.desktop.interface", "color-scheme"))
            //       {
            //
            //          information() << "color-scheme=\"" + strColorScheme + "\"";
            //
            //          strColorScheme.trim();
            //
            //          if (strColorScheme.case_insensitive_contains("dark"))
            //          {
            //
            //             node()->m_bOperatingSystemDarkMode = true;
            //
            //          }
            //          else
            //          {
            //
            //             node()->m_bOperatingSystemDarkMode = false;
            //
            //          }
            //
            //       }
            //       else
            //       {
            //
            //          node()->m_bOperatingSystemDarkMode = false;
            //
            //       }
            //
            //    }
            //    else
            //    {
            //
            //       node()->_fetch_user_color();
            //
            //       //            {
            //       //
            //       //               m_bOperatingSystemDarkMode = false;
            //       //
            //       //            }
            //
            //    }
            //
            // }

         }


         ::string windowing::_get_os_user_theme()
         {

            gchar* theme_name = nullptr;

            g_object_get(m_pGtkSettingsDefault, "gtk-theme-name", &theme_name, NULL);

            string strTheme = theme_name;

            information("gtk_settings_gtk_theme_name_callback: \"" + strTheme + "\"\n");

            g_free(theme_name);

            return strTheme;

         }


         ::string windowing::_get_os_user_icon_theme()
         {

            gchar* icon_theme_name = nullptr;

            g_object_get(m_pGtkSettingsDefault, "gtk-icon-theme-name", &icon_theme_name, NULL);

            string strIconTheme = icon_theme_name;

            information(
               "gtk_settings_gtk_icon_theme_name_callback: \"" + strIconTheme + "\"\n");

            g_free(icon_theme_name);

            return strIconTheme;

         }


         void gtk_settings_gtk_theme_name_callback(GObject* object, GParamSpec* pspec, gpointer data)
         {

            auto* pgtk4windowingsystem = (::gtk4::acme::windowing::windowing*)data;

            if (!pgtk4windowingsystem)
            {

               return;

            }

            pgtk4windowingsystem->_on_os_user_theme_change();

         }


         void gtk_settings_gtk_icon_theme_name_callback(GObject* object, GParamSpec* pspec, gpointer data)
         {

            auto* pgtk4windowingsystem = (::gtk4::acme::windowing::windowing*)data;

            if (!pgtk4windowingsystem)
            {

               return;

            }

            pgtk4windowingsystem->_on_os_user_icon_theme_change();

         }


         void windowing::_on_os_user_theme_change()
         {

            fetch_dark_mode();

         }


         void windowing::_on_os_user_icon_theme_change()
         {

            fetch_dark_mode();

         }


         //
         // void windowing::_set_os_user_theme(const ::scoped_string &strOsUserTheme)
         // {
         //
         //    m_strOsUserTheme = strOsUserTheme;
         //
         //    if (!m_ptaskOsUserTheme)
         //    {
         //
         //       m_ptaskOsUserTheme = fork([this]()
         //                                 {
         //
         //                                    preempt(1_s);
         //
         //                                    m_ptaskOsUserTheme = nullptr;
         //
         //                                    _apply_os_user_theme();
         //
         //                                 });
         //
         //    }
         //
         // }

         //
         // void windowing::_set_os_user_icon_theme(const ::scoped_string &strOsUserIconTheme)
         // {
         //
         //    m_strOsUserIconTheme = strOsUserIconTheme;
         //
         //    if (!m_ptaskOsUserTheme)
         //    {
         //
         //       m_ptaskOsUserIconTheme = fork([this]()
         //                                 {
         //
         //                                    preempt(1_s);
         //
         //                                    m_ptaskOsUserIconTheme = nullptr;
         //
         //                                    _apply_os_user_icon_theme();
         //
         //                                 });
         //
         //    }
         //
         // }
         //
         //


         // void windowing::_apply_os_user_theme()
         // {
         //
         //    informationf("applying os user theme: \"" + m_strOsUserTheme + "\"\n");
         //
         //    _os_process_user_theme(m_strOsUserTheme);
         //
         // }
         //
         //
         // // ::string windowing::_get_os_user_theme()
         // // {
         // //
         // //    ::string strGtkTheme;
         // //
         // //    if(gsettings_schema_contains_key("org.gnome.desktop.interface", "gtk-theme"))
         // //    {
         // //
         // //       information() << "org.gnome.desktop.interface schema contains \"gtk-theme\"";
         // //
         // //       if (gsettings_get(strGtkTheme, "org.gnome.desktop.interface", "gtk-theme"))
         // //       {
         // //
         // //          information() << "gtk-theme=\"" + strGtkTheme + "\"";
         // //
         // //       }
         // //
         // //    }
         // //
         // //    return strGtkTheme;
         // //
         // // }
         //
         //
         // void windowing::_apply_os_user_icon_theme()
         // {
         //
         //    informationf("applying os user icon theme: \"" + m_strOsUserIconTheme + "\"\n");
         //
         //    _os_process_user_icon_theme(m_strOsUserIconTheme);
         //
         // }
         //
         //
         //
         // void windowing::_os_process_user_theme(const ::scoped_string & scopedstrOsTheme)
         // {
         //
         //    informationf(
         //            "os_process_user_theme: is strTheme(" + strOsTheme + ") same as m_strTheme(" + node()->m_strTheme + ")\n");
         //
         //    if (strOsTheme == node()->m_strTheme)
         //    {
         //
         //       informationf(
         //               "os_process_user_theme: same theme as before [___new(" + strOsTheme + ") - old(" + node()->m_strTheme + ")]\n");
         //
         //       return;
         //
         //    }
         //
         //    informationf(
         //            "os_process_user_theme: different theme [___new(" + strOsTheme + ") - old(" +node()-> m_strTheme + ")]\n");
         //
         //    node()->m_strTheme = strOsTheme;
         //
         //    informationf("os_process_user_theme m_strTheme = \"" +node()-> m_strTheme + "\"\n");
         //
         //    try
         //    {
         //
         //       system()->signal(id_operating_system_user_theme_change);
         //
         //    }
         //    catch (...)
         //    {
         //
         //
         //    }
         //
         //    node()->_fetch_user_color();
         //
         //    //      if(!gsettings_schema_contains_key("org.gnome.desktop.interface", "color-scheme"))
         //    //      {
         //    //
         //    //         _os_process_user_theme_color(m_strTheme);
         //    //
         //    //         fetch_user_color();
         //    //
         //    //      }
         //
         // }
         //
         //
         //
         //
         // void windowing::_os_process_user_icon_theme(const ::scoped_string & scopedstrOsUserIconTheme)
         // {
         //
         //    informationf(
         //            "os_process_user_icon_theme: is strIconTheme(" + strOsUserIconTheme + ") same as m_strIconTheme(" + m_strOsUserIconTheme + ")\n");
         //
         //    if (strOsUserIconTheme == m_strOsUserIconTheme)
         //    {
         //
         //       informationf(
         //               "os_process_user_icon_theme: same theme as before [___new(" + strOsUserIconTheme + ") - old(" + m_strOsUserIconTheme + ")]\n");
         //
         //       return;
         //
         //    }
         //
         //    informationf(
         //            "os_process_user_icon_theme: different theme [___new(" + strOsUserIconTheme + ") - old(" + m_strOsUserIconTheme + ")]\n");
         //
         //    m_strOsUserIconTheme = strOsUserIconTheme;
         //
         //    informationf("os_process_user_icon_theme m_strIconTheme = \"" + m_strOsUserIconTheme + "\"\n");
         //
         //    try
         //    {
         //
         //       system()->signal(id_operating_system_user_icon_theme_change);
         //
         //    }
         //    catch (...)
         //    {
         //
         //
         //    }
         //
         //    //      if(!gsettings_schema_contains_key("org.gnome.desktop.interface", "color-scheme"))
         //    //      {
         //    //
         //    //         _os_process_user_theme_color(m_strTheme);
         //    //
         //    //         fetch_user_color();
         //    //
         //    //      }
         //
         // }


         ::pixmap windowing::get_pixmap_from_file(memory& memoryHost, const void* psourceFile, memsize sizeSourceFile)
         {


            auto psurface = cairo_surface_from_file_in_memory(psourceFile, sizeSourceFile);

            if (::is_null(psurface))
            {

               throw ::exception(error_failed);

            }

            auto pixmap = get_raw_data_from_cairo_surface(memoryHost, psurface);

            cairo_surface_destroy(psurface);

            return pixmap;

         }


         // ::acme::windowing::display * windowing::_defer_get_display(bool bBranch, ::GdkDisplay * pgdkdisplay)
         // {
         //
         //    critical_section_lock lock(platform::get()->globals_critical_section());
         //
         //    if(m_phappeningCreatingWGtk4Display)
         //    {
         //
         //       auto pevent = m_phappeningCreatingWGtk4Display;
         //
         //       pevent->wait(1_min);
         //
         //    }
         //    else if (!m_pacmedisplay)
         //    {
         //
         //       m_phappeningCreatingWGtk4Display = øallocate manual_reset_happening();
         //
         //       m_phappeningCreatingWGtk4Display->reset_happening();
         //
         //       auto p = ___new ::gtk4::acme::windowing::display();
         //
         //       p->initialize(this);
         //
         //       p->open_display();
         //
         //       //p->add_listener(p);
         //
         //       p->m_pgdkdisplay = pgdkdisplay;
         //
         //       m_pacmedisplay = p;
         //
         //       lock.unlock();
         //
         //
         //       // if(bBranch)
         //       // {
         //       //
         //       //    p->branch_synchronously();
         //       //
         //       // }
         //       // else
         //       {
         //
         //          p->init_task();
         //
         //       }
         //
         //       lock.lock();
         //
         //       m_phappeningCreatingWGtk4Display->set_happening();
         //
         //       m_phappeningCreatingWGtk4Display.release();
         //
         //    }
         //
         //    return m_pacmedisplay;
         //
         // }


         ::windowing::enum_windowing windowing::calculate_ewindowing()
         {

            ::windowing::enum_windowing ewindowing = ::windowing::e_windowing_none;

            ::pointer < ::gtk4::acme::windowing::display > pdisplay = acme_display();

#if !defined(FREEBSD) && !defined(OPENBSD)

            if(pdisplay->is_wayland())
            {

               ewindowing = ::windowing::e_windowing_wayland;

            }
            else

#endif
            {

               // auto edesktop = ::windowing::get_eoperating_ambient();
               //
               // if (edesktop & ::windowing::e_operating_ambient_kde && pdisplay->has_xcb())
               // {
               //
               //    ewindowing = ::windowing::e_windowing_xcb;
               //
               // }
               // else
               {

                  ewindowing = ::windowing::e_windowing_x11;

               }

            }

            return ewindowing;

         }


         bool windowing::has_resizing()
         {

            return false;

         }


         void windowing::set_dark_mode(bool bDarkMode)
         {

            main_post([this, bDarkMode]()
            {

               if(bDarkMode)
               {

                  ::gdk::gsettings_set("org.gnome.desktop.interface", "color-scheme", "prefer-dark");

               }
               else
               {

                  // auto psummary = node()->operating_system_summary();
                  //
                  // if(psummary->m_strDistro.case_insensitive_equals("ubuntu"))
                  // {

                     ::gdk::gsettings_set("org.gnome.desktop.interface", "color-scheme", "default");

                  // }
                  // else
                  // {
                  //
                  //    ::gdk::gsettings_set("org.gnome.desktop.interface", "color-scheme", "prefer-light");
                  //
                  // }

               }

               //_os_set_user_theme(m_strTheme);

               //_os_set_user_icon_theme(m_strIconTheme);

               //::aura_posix::node::set_dark_mode(bDarkMode);

            });

         }

         bool windowing::dark_mode()
         {

            bool bDarkMode = false;

            main_send([this, &bDarkMode]()
            {

                  ::string str;

                  if (::gdk::gsettings_get(str,"org.gnome.desktop.interface", "color-scheme").succeeded())
                  {

                     bDarkMode = str.contains("dark");

                  }



            });

            return bDarkMode;

         }


      } // namespace windowing


   } // namespace acme


} // namespace gtk4
