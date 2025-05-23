//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
#include "window.h"
#include "windowing.h"
#include "acme/integrate/cairo.h"
#include "acme/nano/nano.h"
#include "acme/user/micro/user.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
//#include <X11/Xatom.h>
//#include <xkbcommon/xkbcommon.h>
//#include <X11/XKBlib.h>
//#include <X11/Xutil.h>
#include "gdk_gdk.h"
#include "acme/operating_system/summary.h"
#include "acme/parallelization/synchronous_lock.h"


namespace gtk3
{


   namespace acme
   {


      namespace windowing
      {


         bool g_bGtkInit = false;


         void defer_init_gtk()
         {

            if (g_bGtkInit)
            {

               return;

            }

            gtk_init(nullptr, nullptr);

            g_bGtkInit = true;

         }


         cairo_surface_t* get_cairo_surface_from_pixbuf(GdkPixbuf* pixbuf)
         {
            int width, height, stride;
            cairo_format_t format;
            guchar* pixels;
            cairo_surface_t* surface;

            // Get pixbuf properties
            width = gdk_pixbuf_get_width(pixbuf);
            height = gdk_pixbuf_get_height(pixbuf);
            stride = gdk_pixbuf_get_rowstride(pixbuf);
            pixels = gdk_pixbuf_get_pixels(pixbuf);

            // Determine the format (assuming GdkPixbuf uses 8 bits per channel and alpha)
            if (gdk_pixbuf_get_has_alpha(pixbuf))
            {
               format = CAIRO_FORMAT_ARGB32;
            }
            else
            {
               format = CAIRO_FORMAT_RGB24;
            }

            // Create a Cairo image surface from pixbuf pixel data
            surface = cairo_image_surface_create_for_data(
               pixels, // Pixel data from GdkPixbuf
               format, // Cairo format (ARGB32 or RGB24)
               width, // Width of the image
               height, // Height of the image
               stride // Stride (number of bytes per row)
            );

            if (cairo_surface_status(surface) != CAIRO_STATUS_SUCCESS)
            {
               g_warning("Error creating Cairo surface from GdkPixbuf");
               return NULL;
            }

            return surface;
         }


         // Sample JPEG data in memory (you would typically load this from a file or network)
         //const unsigned char jpeg_data[] = { /* ... your JPEG data here ... */ };
         //gsize jpeg_data_size = sizeof(jpeg_data);
         cairo_surface_t* cairo_surface_from_file_in_memory(const void* p, memsize size)
         {
            // Load JPEG image from memory into GdkPixbuf
            GdkPixbufLoader* loader = gdk_pixbuf_loader_new();
            GError* error = NULL;

            if (!gdk_pixbuf_loader_write(loader, (const guchar *)p, size, &error))
            {
               g_printerr("Error loading image: %s\n", error->message);
               g_error_free(error);
               g_object_unref(loader);
               throw ::exception(error_failed);
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

            auto psurface = get_cairo_surface_from_pixbuf(pixbuf);

            // Cleanup
            g_object_unref(loader);

            return psurface;

         }


         windowing::windowing()
         {


            m_pgtkapplication = nullptr;

            defer_init_gtk();


         }


         windowing::~windowing()
         {


         }


         //~ ::e_status windowing::defer_initialize_windowing_system()
         //~ {

         //~ //      if (m_estatusInitializeX11 == error_not_initialized)
         //~ //      {
         //~ //
         //~ //         m_estatusInitializeX11 = initialize_windowing_system();
         //~ //
         //~ //      }
         //~ //
         //~ //      return m_estatusInitializeX11;

         //~ return ::success;

         //~ }


         void windowing::initialize_windowing()
         {

            //informationf("node_gtk3::node::x11_initialize");

            //informationf("node_gtk3::node::x11_initialize going to call x11_init_threads");

            //if (!system()->acme_windowing()->init_threads())
            //{

            ////return ::error_failed;

            //throw ::exception(error_failed);

            ////return;

            //}

            //// gdk_x11 does error handling?!?!?!
            ////XSetErrorHandler(_c_XErrorHandler);

            ////g_pmutexX11 = ___new ::pointer < ::mutex >();

            ////return ::success;

         }


         ::windowing::enum_bias windowing::calculate_windowing_bias()
         {

            auto psummary = node()->operating_system_summary();

            auto strOperatingSystem = psummary->m_strSystem.lowered();

            auto strOperatingAmbient = psummary->m_strAmbient.lowered();

            auto iMajor = psummary->m_iMajor;

            auto iMinor = psummary->m_iMinor;

            if (strOperatingSystem == "linuxmint")
            {

               if (strOperatingAmbient == "x-cinnamon")
               {

                  if (iMajor == 22)
                  {

                     if (iMinor == 1)
                     {

                        return ::windowing::e_bias_linux_mint_x_cinnamon_22_1;

                     }
                     else
                     {

                        return ::windowing::e_bias_linux_mint_x_cinnamon_22_1;

                     }


                  }
                  else
                  {

                     return ::windowing::e_bias_linux_mint_x_cinnamon_22_1;

                  }

               }
               else
               {

                  return ::windowing::e_bias_linux_mint_x_cinnamon_22_1;

               }

            }
            else
            {

               return ::windowing::e_bias_linux_mint_x_cinnamon_22_1;

            }

         }


         void windowing::on_start_system()
         {

            system()->on_branch_system_from_main_thread_startup(this);

         }


         static void on_activate_gtk_application(GtkApplication*, gpointer p)
         {

            auto* pgtk3windowingsystem = (::gtk3::acme::windowing::windowing *)p;

            //pgtk3windowingsystem->_hook_system_theme_change_callbacks();

            //pgtk3windowingsystem->_fetch_dark_mode();

            pgtk3windowingsystem->_on_activate_gtk_application();

         }


         static gboolean execute_on_main_thread(gpointer data)
         {

            auto* pprocedure = (::procedure *)data;

            (*pprocedure)();

            delete pprocedure;

            return FALSE;

         }


         // Function to be run in the GTK main thread
         gboolean __g_callback(gpointer data)
         {

            auto pprocedure = (procedure *)(data);

            try
            {

               (*pprocedure)();

            }
            catch (...)
            {

            }

            try
            {

               delete pprocedure;

            }
            catch (...)
            {

            }

            return FALSE; // Returning FALSE so it is only called once

         }


         void windowing::_user_post(const ::procedure& procedure)
         {

            //g_main_context_invoke(NULL, execute_on_main_thread, new ::procedure(procedure));

            auto pprocedure = new ::procedure(procedure);

            //// Call update_label in the GTK main thread
            g_idle_add(__g_callback, pprocedure);


         }


         void windowing::windowing_application_main_loop()
         {

            information() << "gtk3::acme::windowing::windowing::windowing_application_main_loop()";

            //signal(SIGCHLD, SIG_IGN);

            __task_init();

            defer_init_gtk();

            task::main();

         }


         void windowing::run()
         {

            information() << "gtk3::acme::windowing::windowing::run";

            ::string strId = application()->m_strAppId;

            strId.find_replace("/", ".");

            strId.find_replace("_", "-");

            m_pgtkapplication = gtk_application_new(strId, G_APPLICATION_DEFAULT_FLAGS);

            g_signal_connect(m_pgtkapplication, "activate", G_CALLBACK(on_activate_gtk_application), this);


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


            // if(m_pacmedisplay->is_wayland())
            // {
            //
            //
            //
            // }

            g_application_run(G_APPLICATION(m_pgtkapplication), 0, nullptr);
            //
            // // //g_application_run (G_APPLICATION(m_pgtkapplication), ::system()->get_argc(), ::system()->get_args());
            // // //aaa_x11_main();
            // //
            // //
            // // while(::task_get_run())
            // // {
            // //
            // //    preempt(1_s);
            // //
            // // }
            // if(::system()->m_pmanualresethappeningMainLoopEnd)
            // {
            //
            //    ::system()->m_pmanualresethappeningMainLoopEnd->set_happening();
            //
            // }


         }


         void windowing::windowing_post_quit()
         {

            main_post([this]()
            {

               g_application_quit(G_APPLICATION(m_pgtkapplication));

            });

         }


         void windowing::_on_activate_gtk_application()
         {

            if (m_callbackOnActivateGtkApplication)
            {

               m_callbackOnActivateGtkApplication();

            }
            else
            {

               //auto prequest = __create_new<::request>();

               //application()->post_request(prequest);

               //system()->defer_post_initial_request();

               system()->post_application_start();
               system()->defer_post_file_open();
               system()->post_application_started();


            }

         }


         ::acme::windowing::display* windowing::acme_display()
         {

            //return ::platform::node::x11_get_display();

            //defer_initialize_windowing_system();

            if (!m_pacmedisplay)
            {

               __øconstruct(m_pacmedisplay);


               // !!! I have removed this call from here:
               // at netbsd (and maybe other systems) open display here is called before
               // the main loop starts running. And Open Display in this platform need to
               // run at the main loop. So open display doesn't run. The call from open_display
               // to the main thread is synchronous, so it wait for something that is not
               // going to run.
               // m_pacmedisplay->open_display();


            }

            //      if(m_pvoidX11Display == NULL)
            //      {
            //
            //         m_pvoidX11Display = fetch_windowing_system_display();
            //
            //      }
            //
            //      return m_pvoidX11Display;

            return m_pacmedisplay;

         }


         ::gtk3::acme::windowing::window* windowing::_window(GtkWindow* pgtkwindow)
         {

            _synchronous_lock synchronouslock(this->synchronization());

            auto pgtk3acmewindowingwindow = m_windowmap[pgtkwindow];

            if (!pgtk3acmewindowingwindow)
            {

               return nullptr;

            }

            return pgtk3acmewindowingwindow;

         }


         void windowing::_set_window(GtkWindow* pgtkwindow, ::gtk3::acme::windowing::window* pgtk3acmewindowingwindow)
         {

            _synchronous_lock synchronouslock(this->synchronization());

            m_windowmap[pgtkwindow] = pgtk3acmewindowingwindow;

         }


         void windowing::_user_send(const ::procedure& procedure)
         {

            if (::is_main_thread())
            {

               information() << "windowing::_user_send main thread";

               procedure();

               return;

            }

            information() << "windowing::_user_send not user thread";

            //__matter_send_procedure(this, this, &node::node_post, procedure);

            //      CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
            //      {

            auto pevent = __allocate manual_reset_happening();

            user_post([ procedure, pevent ]
            {

               procedure();

               pevent->set_happening();

            });

            auto timeout = procedure.timeout();

            if (pevent->wait(timeout).failed())
            {

               if (::task_get_run())
               {
                  throw ::exception(error_timeout);
               }
               //pevent.release();

               //return false;

            }

            ///return true;
            //
            //      }


         }


         //~ void windowing::_user_post(const ::procedure & procedure)
         //~ {

         //~ node()->user_post(procedure);

         //~ }


         //~ void windowing::display_error_trap_push(int i)
         //~ {


         //~ //node()->windowing_system_display_error_trap_push(i);

         //~ //      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
         //~ //      {
         //~ //
         //~ //         GdkDisplay *gdkdisplay;
         //~ //
         //~ //         gdkdisplay = gdk_display_get_default ();
         //~ //         gdk_x11_display_error_trap_push (gdkdisplay);
         //~ //
         //~ //      }

         //~ }


         //~ void windowing::display_error_trap_pop_ignored(int i)
         //~ {

         //~ //node()->windowing_system_display_error_trap_pop_ignored(i);
         //~ //      if(::windowing::get_ewindowing() == ::windowing::e_windowing_x11)
         //~ //      {
         //~ //
         //~ //         GdkDisplay *gdkdisplay;
         //~ //         gdkdisplay = gdk_display_get_default ();
         //~ //         gdk_x11_display_error_trap_pop_ignored (gdkdisplay);
         //~ //
         //~ //      }

         //~ }


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


         bool windowing::shell_open(const ::file::path& path)
         {

            print_line("gtk3::acme::windowing::windowing::shell_open: \"" + path + "\"");

            application()->fork([this,path]()
            {

               _user_post([path]()
               {

                  gdk::open_file_with_default_app_async(path);

               });

            });

            return true;

         }


      } // namespace windowing


   } // namespace acme


} // namespace gtk3
