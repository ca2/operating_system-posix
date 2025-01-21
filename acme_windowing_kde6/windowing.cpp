//
// Created by camilo on 2024-05-26 22:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing.h"
#include "acme/integrate/qt/image.h"
#include "acme/nano/nano.h"
#include "acme/windowing/display.h"
#include "acme/user/micro/user.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include <QImage>
#include <QByteArray>
//#include <X11/Xatom.h>
//#include <xkbcommon/xkbcommon.h>
//#include <X11/XKBlib.h>
//#include <X11/Xutil.h>




namespace kde6
{


   namespace acme
   {


      namespace windowing
      {


         windowing::windowing()
         {

            m_pqapplication = nullptr;


         }


         windowing::~windowing()
         {

            //if(m_pqapplication)


         }


//   ::e_status windowing::defer_initialize_windowing()
//   {
//
////      if (m_estatusInitializeX11 == error_not_initialized)
////      {
////
////         m_estatusInitializeX11 = initialize_windowing();
////
////      }
////
////      return m_estatusInitializeX11;
//
//         return ::success;
//
//   }


         void windowing::initialize_windowing()
         {

            informationf("node_gtk3::node::x11_initialize");

//      informationf("node_gtk3::node::x11_initialize going to call x11_init_threads");
//
//      if (!system()->acme_windowing()->init_threads())
//      {
//
//         return ::error_failed;
//
//      }

            // gdk_x11 does error handling?!?!?!
            //XSetErrorHandler(_c_XErrorHandler);

            //g_pmutexX11 = ___new ::pointer < ::mutex >();

//      return ::success;

         }


         ::acme::windowing::display * windowing::acme_display()
         {

            if(!m_pacmedisplay)
            {


               __øconstruct(m_pacmedisplay);


            }

//      //return ::platform::node::x11_get_display();
//
//      defer_initialize_windowing();
//
////      if(m_pvoidX11Display == NULL)
////      {
////
////         m_pvoidX11Display = fetch_windowing_display();
////
////      }
////
////      return m_pvoidX11Display;

            return m_pacmedisplay;

         }


         void windowing::_user_send(const ::procedure & procedure)
         {

            if (::is_main_thread()) {

               procedure();

               return;

            }

            //__matter_send_procedure(this, this, &node::node_post, procedure);

//      CLASS_DECL_ACME bool main_synchronous(const class time & time, const ::procedure & function)
//      {

            auto pevent = __allocate manual_reset_happening();

            user_post([procedure, pevent]
                      {

                         procedure();

                         pevent->set_happening();

                      });

            if (!pevent->wait(procedure.timeout())) {

               throw ::exception(error_timeout);
               //pevent.release();

               //return false;

            }

            ///return true;
//
//      }


         }


   void windowing::_main_post(const ::procedure & procedure)
   {

      _user_post(procedure);

   }


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


         void windowing::_on_activate_kde_application()
         {

            //g_object_ref(m_pgtkapplication);

            // auto pdisplay = __øcreate<::windowing::display>();
            //
            //
            //
            // pdisplay->initialize_display(this);
            //

            auto pdisplay = this->acme_display();

            if (!pdisplay) {

               throw ::exception(error_no_interface,
                                 "Failed to cast pdisplay to m_pdisplay at windowing_kde5::windowing::initialize");

            }

            information() << "node_kde5::_on_activate_gtk_application going to user_post";

            // This seems not to work with "foreign" windows
            // (X11 windows not created with Gdk)
            //x11_add_filter();

            information() << "node_kde5::_on_activate_gtk_application on user_post";


            // auto pgtksettingsDefault = gtk_settings_get_default();
            //
            // if (pgtksettingsDefault)
            // {
            //
            //    m_pGtkSettingsDefault = G_OBJECT(pgtksettingsDefault);
            //
            //    g_object_ref (m_pGtkSettingsDefault);
            //
            //    {
            //
            //       gchar *theme_name = nullptr;
            //
            //       g_object_get(m_pGtkSettingsDefault, "gtk-theme-name", &theme_name, NULL);
            //
            //       m_strOsUserTheme = theme_name;
            //
            //       g_free(theme_name);
            //
            //    }
            //
            //    {
            //
            //       gchar *icon_theme_name = nullptr;
            //
            //       g_object_get(m_pGtkSettingsDefault, "gtk-icon-theme-name", &icon_theme_name, NULL);
            //
            //       m_strOsUserIconTheme = icon_theme_name;
            //
            //       g_free(icon_theme_name);
            //
            //    }
            //
            //
            //    auto preturnTheme = g_signal_connect_data(
            //            m_pGtkSettingsDefault,
            //            "notify::gtk-theme-name",
            //            //"gtk-private-changed",
            //            G_CALLBACK(gtk_settings_gtk_theme_name_callback),
            //            this,
            //            NULL,
            //            G_CONNECT_AFTER);
            //
            //    auto preturnIconTheme = g_signal_connect_data(
            //            m_pGtkSettingsDefault,
            //            "notify::gtk-icon-theme-name",
            //            //"gtk-private-changed",
            //            G_CALLBACK(gtk_settings_gtk_icon_theme_name_callback),
            //            this,
            //            NULL,
            //            G_CONNECT_AFTER);
            //
            //    //g_object_ref(preturn);
            //
            //    //printf("return %" PRIiPTR, preturn);
            //
            //    //printf("return %" PRIiPTR, preturn);
            //
            // }

            //gtk_add_idle_source(this);

            auto psystem = system();

            psystem->defer_post_initial_request();

         }


         void windowing::on_start_system()
         {

            auto * psystem = this->system();

            psystem->on_branch_system_from_main_thread_startup();

         }


         void windowing::windowing_application_main_loop()
         {

            ::string strId = application()->m_strAppId;

            strId.find_replace("/", ".");
            strId.find_replace("-", "_");

            //gtk_init();

            int argc = platform()->get_argc();

            m_pqapplication = ___new QApplication(argc, platform()->get_args());

            m_pqapplication->setQuitOnLastWindowClosed(false);

            _on_activate_kde_application();

            //m_pgtkapplication = gtk_application_new (strId, G_APPLICATION_DEFAULT_FLAGS);

            //g_signal_connect (m_pgtkapplication, "activate", G_CALLBACK(on_activate_gtk_application), this);


            // Retrieve system settings and listen for changes in dark mode preference
            //GtkSettings *settings = gtk_settings_get_default();
            //update_theme_based_on_system(settings, NULL); // Check initial state
            //g_signal_connect(settings, "notify::gtk-application-prefer-dark-theme", G_CALLBACK(update_theme_based_on_system), NULL);

            // Get the current GTK theme name (or any other available property)
            //gboolean b=1;
            //g_object_set(settings, "gtk-application-prefer-dark-theme", TRUE, NULL);
            //g_print("Current theme: %s\n", theme_name);

            // Free the allocated string after use
            //g_free(theme_name);

            ///GtkSettings *settings = gtk_settings_get_default();
            //g_object_set(settings, "gtk-enable-animations", FALSE, NULL);

            //g_application_hold(G_APPLICATION(m_pgtkapplication));


            // if(m_pdisplay->is_wayland())
            // {
            //
            //
            //
            // }

            m_pqapplication->exec();


            //g_application_run (G_APPLICATION(m_pgtkapplication), platform()->get_argc(), platform()->get_args());
            //aaa_x11_main();

            //
            // while(::task_get_run())
            // {
            //
            //    preempt(1_s);
            //
            // }

         }


         void windowing::windowing_post_quit()
         {

            auto quitApplication = [this]()
            {

               m_pqapplication->quit();

            };

            main_post(quitApplication);

         }


         void windowing::_user_post(const ::procedure & procedure)
         {

            // invoke on the main thread
            QMetaObject::invokeMethod(
               m_pqapplication,
               [procedure]
               {

                  procedure();

               },
               Qt::QueuedConnection);


         }


         ::pixmap windowing::get_pixmap_from_file(memory & memoryHost, const void * psourceFile, memsize sizeSourceFile)
         {


            QByteArray imageData = QByteArray::fromRawData((const char *) psourceFile,
                                                           sizeSourceFile);  // Replace with actual image bytes and size

            // Create a QImage object
            QImage image;

            // Load the image from the QByteArray
            if (!image.loadFromData(imageData)) {

               return {};

            }

            QImage image32;

            image32 = image.convertToFormat(QImage::Format_ARGB32_Premultiplied);

            memoryHost.assign(image32.bits(), image32.bytesPerLine() * image32.height());

            ::pixmap pixmap;

            pixmap.initialize({image32.width(), image32.height()}, (::image32_t *) memoryHost.data(),
                              image32.bytesPerLine());

            return pixmap;

         }


         bool windowing::dark_mode()
         {

            //_fetch_user_color();

//            auto pthemecolors = _get_os_theme_colors();
//
//            auto bDarkMode = pthemecolors->m_colorBack.get_luminance() < 0.5;
//
//            return bDarkMode;

            return false;

         }


      } // namespace windowing


   } //namespace acme


} // namespace kde6



