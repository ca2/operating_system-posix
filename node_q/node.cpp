//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "appindicator.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/user/user/os_theme_colors.h"
#include "acme/user/user/theme_colors.h"
#include "apex/platform/system.h"
//#include "acme/platform/ini.h"
#include "aura/windowing/windowing.h"
// #include <kworkspace6/kworkspace.h>
// #include <KColorScheme>
// #include <KFileItem>
// #include <KIconLoader>
//#include <QX11Info>
#include <QtGui/QDesktopServices>
#include <QFileDialog>
#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QIcon>
#include <QDir>
//#include <LXQt/Settings>
//#include <LXQt/IconCache>
#include <QIconEngine>
#include <QTextStream>
//#include <QDBusInterface>
//#include <qpa/qplatformnativeinterface.h>
#include <xcb/xcb.h>
#include "windowing_q/windowing.h"
//#include <KPackage/Package>
//#include <KPackage/PackageLoader>
//#include <KF5/plasma/applet.h>
//#include <KF5/plasma/containment.h>

#include <QApplication>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QIcon>
#include <QPixmap>
#include <QDir>
#include <QDebug>

// Function to get the full icon path for a given file at a specific size
QString getFileIconPath(const QString &filePath, int size = 64) {
   QFileInfo fileInfo(filePath);
   QFileIconProvider iconProvider;
   QIcon fileIcon = iconProvider.icon(fileInfo); // Get file icon

   if (fileIcon.isNull()) {
      return QString(); // No icon found
   }

   // Get the icon name from the system theme
   QString iconName = fileIcon.name();
   if (!iconName.isEmpty()) {
      QString iconPath = QIcon::fromTheme(iconName).name();
      if (!iconPath.isEmpty()) {
         return iconPath; // Return theme icon path if found
      }
   }


   // Fallback: Save icon to a temporary file and return its path
   QString iconTempPath = QDir::tempPath() + filePath + "/icon"+QString::number(size)+".png";
   if (fileIcon.pixmap(size, size).save(iconTempPath)) {
      return iconTempPath;
   }

   return QString(); // Return empty if no valid icon was found
}



void initialize_x11_display(::particle * pparticle, void * pX11Display);
void * initialize_x11_display(::particle * pparticle);

//void kde_open_local_file(QApplication * papplication, const_char_pointer psz, const_char_pointer pszMimeType);



void copy(::color::color * pcolor, const QColor * pqcolor)
{

   *pcolor = rgba(pqcolor->redF(), pqcolor->greenF(), pqcolor->blueF(), pqcolor->alphaF());

}

//
// void kde_update_os_theme_colors(::os_theme_colors * pthemecolors)
// {
//
//    KColorScheme colorscheme;
//
//    auto pbrushBackground = colorscheme.background();
//
//    copy(&pthemecolors->m_colorBack, &pbrushBackground.color());
//
// }
//


namespace node_q
{


   node::node()
   {

//      //m_pNodeLXQ2 = this;
//
//      //m_pqapplication = nullptr;
//
//      m_piconloader = nullptr;
//
//      //m_qpalette = QApplication::palette();

   }


   node::~node()
   {


      // if(m_pqapplication != nullptr)
      // {
      //
      //    delete m_pqapplication;
      //
      // }

//
//      _destroy_node_kde();

//      if (m_pGtkSettingsDefault)
//      {
//
//         g_object_unref(m_pGtkSettingsDefault);
//
//      }

//      if(m_pnodeimpl)
//      {
//
//         del_node_impl(m_pnodeimpl);
//
//         m_pnodeimpl = nullptr;
//
//      }

      //os_post_quit();



   }


//    void node::user_post_quit()
//    {
//
//       m_pqapplication->quit();
//
//    }
//
//
//    bool node::eventFilter(QObject * pparticle, QEvent * pevent)
//    {
//
// //      if(pevent->type() == QEvent::ApplicationPaletteChange)
// //      {
// //
// //         auto pthemecolors = ::user::os_get_theme_colors();
// //
// //         if(!pthemecolors)
// //         {
// //
// //            pthemecolors = new_os_theme_colors();
// //
// //            ::user::os_set_theme_colors(pthemecolors);
// //
// //         }
// //
// //         kde_update_os_theme_colors(pthemecolors);
// //
// //         fetch_user_color();
// //
// //         return false;
// //
// //      }
//
// //      if(pevent->type() == QEvent::ThemeChange)
// //      {
// //
// //
// //
// //
// //      }
//
//       return false;
//
//    }
//
//
//    int node::node_init_check(int *pi, char ***ppz)
//    {
//
//       m_qpalette = QApplication::palette();
//
//       return 1;
//
//    }


   // void node::_fill_os_theme_colors(::os_theme_colors * pthemecolors)
   // {
   //
   //    kde_update_os_theme_colors(pthemecolors);
   //
   // }


   void node::on_system_main()
   {

      //auto estatus =
      //

      //system()->m_itask = nullptr;

      //system()->m_htask = nullptr;

      //system()->m_taskindex.m_i = 0;

      //system()->branch();

      /// ___new:platform_create_system:decrement_reference_count
      /// begin_synch starts ___new thread
      /// the framework will hold a reference to the system as this
      /// ___new started thread
      /// now it is safe to release the platform_create_system
      /// creation reference.

      //system()->decrement_reference_count();

//      if (!estatus)
//      {
//
//         informationf("Failed to begin_synch the system (::apex::system or ::apex::system derived)");
//
//         return estatus;
//
//      }

      //   ::e_status estatus = psystem->begin_synch();
      //
      //   if(!estatus)
      //   {
      //
      //      return estatus;
      //
      //   }
      //

//      const ::string &pszName = m_XstrAppId;

//       g_set_application_name(scopedstrName);

//      const ::string &pszPrgName = m_strProgName;

//      g_set_prgname(scopedstrPrgName);

      //auto idle_source = g_idle_source_new();

      //g_source_set_callback(idle_source, &linux_start_system, (::apex::system *) system(), nullptr);

      //g_source_attach(idle_source, g_main_context_default());

      //int c = 2;

      //const ::string & argv[]={"app", "--g-fatal-warnings"};

//#if !defined(__SANITIZE_ADDRESS__)
//
//      {
//
//         node_init_check(&::system()->m_argc, &::system()->m_args);
//
//      }
//
//#endif
//
//      auto psystem = system();
//
//      psystem->defer_post_initial_request();
//
//      //_qapplication_exec();

      system()->windowing()->windowing_application_main_loop();

   }




   void node::initialize(::particle * pparticle)
   {

      information() << "node_kde::node initialize";

      auto psystem = pparticle->system();

      // m_pqapplication = ___new QApplication(psystem->m_argc, psystem->m_args);
      //
      // if(!m_pqapplication)
      // {
      //
      //    printf("%s", "Failed to create QApplication");
      //
      //    throw ::exception(error_failed);
      //
      // }
      //
      // information() << "node_kde::node initialize QApplication : " << (::iptr) m_pqapplication;
      //
      // m_pqapplication->setQuitOnLastWindowClosed(false);
      //
      //main_asynchronous([])

      //m_pqapplication->installEventFilter(this);

      //auto estatus =
      //
      ::aura_posix::node::initialize(pparticle);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      //::node_kde::g_defer_init();
//
//      return estatus;

   }


   // ::e_status node::_allocate_Display_and_connection()
   // {
   //
   //    information() << "node_kde _allocate_Display_and_connection";
   //
   //    if(QX11Info::isPlatformX11())
   //    {
   //
   //       void *p = (void *) QX11Info::display();
   //
   //       informationf("qx11info::display : " + hex::lower_case_from((iptr) p));
   //
   //       m_pAuraPosixX11Display = p;
   //
   //       if (!m_pAuraPosixX11Display)
   //       {
   //
   //          return error_failed;
   //
   //       }
   //
   //       m_pAuraPosixXcbConnection = QX11Info::connection();
   //
   //       informationf("qx11info::connection : " + hex::lower_case_from((iptr) m_pAuraPosixXcbConnection));
   //
   //       //      if(!m_pxcbconnection)
   //       //      {
   //       //
   //       //         return error_failed;
   //       //
   //       //      }
   //
   //
   //       ::x11::acme::windowing::display_get(this, false, (Display *)p);
   //
   //       return ::success;
   //
   //    }
   //    else
   //    {
   //
   //       m_bUnhookX = false;
   //
   //       m_pAuraPosixX11Display = ::x11::acme::windowing::display_get(this);
   //
   //       return ::success;
   //
   //    }
   //
   // }


   void node::initialize_window_manager()
   {

//#if !defined(HAS_GTK3) && !defined(HAS_GTK4) && !defined(HAS_KDE5) && !defined(HAS_LXQ2)
//
//      information() << "node_kde _allocate_Display_and_connection";
//
//      if(is_x11())
//      {
//
//         //auto px11Application = m_pqapplication->nativeInterface<QNativeInterface::QX11Application>();
//
//  //       auto pDisplay = px11Application->display();
////
//    //     informationf("qx11info::display : " + hex::lower_case_from((iptr) pDisplay));
//
//         m_pAuraPosixX11Display = pDisplay;
//
//         if (!m_pAuraPosixX11Display)
//         {
//
//            throw ::exception(error_failed);
//
//            return;
//
//         }
//
//         m_pAuraPosixXcbConnection = px11Application->connection();
//
//         informationf("qx11info::connection : " + hex::lower_case_from((iptr) m_pAuraPosixXcbConnection));
//
////      if(!m_pxcbconnection)
////      {
////
////         return error_failed;
////
////      }
//
//         initialize_x11_display(this, pDisplay);
//
//         //return ::success;
//
//      }
//      else
//      {
//
//         m_bUnhookX = false;
//
//         m_pAuraPosixX11Display = initialize_x11_display(this);
//
////         return ::success;
//
//      }
//
//#endif

   }



   // string node::os_get_user_theme()
   // {
   //
   //    ::file::path pathKdeGlobals;
   //
   //    pathKdeGlobals = directory_system()->home() /".config/kdeglobals";
   //
   //    auto lines = file()->lines(pathKdeGlobals);
   //
   //    ::string str;
   //
   //    lines.case_insensitive_find_first_begins_eat(str, "LookAndFeelPackage");
   //
   //    if(str.is_empty())
   //    {
   //
   //       return {};
   //
   //    }
   //
   //    str.trim_left(" =");
   //    str.trim_right();
   //    str.trim();
   //
   //    auto strTheme = str;
   //
   //    information() << "Current LookAndFeelPackage is : " << strTheme;
   //
   //    return strTheme;
   //
   // }
   //
   //
   // void node::os_set_user_theme(const ::scoped_string & scopedstrUserTheme)
   // {
   //
   //    command_system("lookandfeeltool -a " + strUserTheme);
   //
   // }


   // void node::os_process_user_theme(string strTheme)
   // {
   //
   //    //_os_process_user_theme(strTheme);
   //
   // }



   string node::get_file_icon_path(const ::scoped_string & scopedstrPath, int iSize)
   {


      auto path = getFileIconPath(strPath.c_str(), iSize);

      return path.toUtf8().data();

//       tring getIconFullPath(const QString &filePath) {
//          LXQt::IconCache *iconCache = LXQt::IconCache::instance();
//          QFileInfo fileInfo(filePath);
//
//          if (!iconCache) {
//             return QString();
//          }
//
//          QIcon icon = iconCache->icon(fileInfo);
//
//          if (icon.isNull()) {
//             return QString();
//          }
//
//          // Attempt to get the actual icon name
//          QString iconName = icon.name();
//
//          // Get the theme-based icon path
//          QString themeIconPath = QIcon::fromTheme(iconName).name();
//
//          if (!themeIconPath.isEmpty()) {
//             return themeIconPath;
//          }
//
//          // If theme path is not found, save the icon as a temporary file
//          QString iconTempPath = QDir::tempPath() + "/lxqt_icon.png";
//          icon.pixmap(64, 64).save(iconTempPath);
//
//          return iconTempPath.toUtf8().data();
//
// //       QUrl url((const_char_pointer ) ("file://"+strPath));
// //
// //       KFileItem fileitem(url, KFileItem::NormalMimeTypeDetermination);
// //
// //       auto name = fileitem.iconName();
// //
// // //      if(::is_null(m_piconloader))
// // //      {
// // //
// // //         m_piconloader = ___new KIconLoader();
// // //
// // //      }
// //
// //       auto path = KIconLoader::global()->iconPath(name, -iSize);
// //
// //       //return ::linux_g_direct_get_file_icon_path(scopedstrPath, iSize);
// //
// //       QByteArray bytea = path.toUtf8();
// //
// //       const_char_pointer pathData = bytea.constData();
// //
// //       return pathData;
//

   }


   string node::get_file_content_type(const ::scoped_string & scopedstrPath)
   {

      //return ::linux_g_direct_get_file_content_type(scopedstrPath);

      return "";

   }


   // string node::get_wallpaper(::collection::index iScreen)
   // {
   //
   //    return "";
   //
   // }
   //

   void node::_user_post(const ::procedure & procedure)
   {

      system()->acme_windowing()->_user_post(procedure);

      // // invoke on the main thread
      // QMetaObject::invokeMethod(
      //    m_pqapplication,
      //    [procedure]
      //    {
      //
      //       procedure();
      //
      //    });
      //
      // //return success;

   }


//   void node::os_post_quit()
//   {
//
//      //os_post_quit();
//
//      //m_pqapplication->quit();
//
//   }


//   void node::os_post_quit()
//   {
//
//      m_pqapplication->quit();
//
//   }


   void node::reboot()
   {

      ::aura_posix::node::reboot();

      ///KWorkSpace::requestShutDown(KWorkSpace::ShutdownConfirmYes, KWorkSpace::ShutdownTypeReboot, KWorkSpace::ShutdownModeInteractive);

      //return ::success;

   }

//   void * node::node_wrap_window(void * pvoidDisplay, long long window)
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

      if (ptopic->id() == id_operating_system_user_color_change)
      {

         return false;

      }

      return false;

   }


   bool node::launch_on_node(::topic *ptopic)
   {

      ::matter *pmatter = ptopic;

//      node_fork([pmatter]()
//                {
//
//                   auto ret = g_timeout_add(300, (GSourceFunc) &node_gnome_source_func, pmatter);
//
//                   printf("ret %d", ret);
//
//                   printf("ret %d", ret);
//
////      g_idle_add(&node_gnome_source_func, pmatter);
//
//                });

      return false;

   }


   int node::os_launch_uri(const ::scoped_string & scopedstrUri, char * pszError, int iBufferSize)
   {

      QDesktopServices::openUrl(QUrl((const_char_pointer ) strUri));

      return 0;

   }

//   os_theme_colors * node::new_os_theme_colors()
//   {
//
//      auto pthemecolors = ::new_os_theme_colors();
//
//      pthemecolors->m_colorBack.color32 = m_qpalette.color(QPalette::Window).rgba();
//      pthemecolors->m_colorFore.color32 = m_qpalette.color(QPalette::WindowText).rgba();
//      pthemecolors->m_colorFace.color32 = m_qpalette.color(QPalette::Button).rgba();
//
//      return pthemecolors;
//
//   }

   //
   // bool node::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)
   // {
   //
   //    if(eventType == "xcb_generic_event_t")
   //    {
   //
   //       xcb_generic_event_t * pevent = (xcb_generic_event_t *) message;
   //
   //       auto pwindowing = m_pwindowingAuraNode;
   //
   //       if(!pwindowing)
   //       {
   //
   //          return false;
   //
   //       }
   //
   //       if(pwindowing->_xcb_process_event(pevent))
   //       {
   //
   //          return false;
   //
   //       }
   //
   //    }
   //    else
   //    {
   //
   //       information(string(eventType.constData()) + " unhandled!!\n");
   //
   //    }
   //
   //    return false;
   //
   // }
   //
   //
   // ::e_status node::_qapplication_exec()
   // {
   //
   //    m_pqapplication->installNativeEventFilter(this);
   //
   //    m_pqapplication->exec();
   //
   //    return ::success;
   //
   // }


//   bool node::_os_calc_system_dark_mode()
//   {
//
//      auto pthemecolors = ::user::os_get_theme_colors();
//
//      if(!pthemecolors)
//      {
//
//         pthemecolors = new_os_theme_colors();
//
//         ::user::os_set_theme_colors(pthemecolors);
//
//      }
//
//      ::color::color colorBack(pthemecolors->m_colorBack);
//
//      auto dLuminance = colorBack.get_luminance();
//
//      return dLuminance < 0.5;
//
//   }

   void node::shell_launch(const ::scoped_string & scopedstrAppId)
   {

      string strDesktopFileTitle(strAppId);

      strDesktopFileTitle.find_replace("/", ".");

      ::file::path pathDesktop;

      pathDesktop = directory_system()->home() / ".local/share/applications" / (strDesktopFileTitle + ".desktop");

      ::cast < ::windowing_q::windowing > plxq2windowing = system()->acme_windowing();

      //kde_open_local_file(plxq2windowing->m_pqapplication, pathDesktop, "application/x-desktop");

   }


   void node::open_internet_link_in_system_browser(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile)
   {

      QUrl url(strUrl.c_str());

      QDesktopServices::openUrl(url);

   }


   void node::_node_file_dialog(::file::file_dialog * pdialog)
   {

      pdialog->increment_reference_count();

      user_post([pdialog]()
                {

                   auto pqfiledialog = new QFileDialog();

                   if (pdialog->m_bSave)
                   {

                      pqfiledialog->setAcceptMode(QFileDialog::AcceptMode::AcceptSave);

                   }
                   else
                   {

                      pqfiledialog->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);

                      if (pdialog->m_bMultiple)
                      {

                         pqfiledialog->setFileMode(QFileDialog::FileMode::ExistingFiles);

                      }
                      else
                      {

                         pqfiledialog->setFileMode(QFileDialog::FileMode::ExistingFile);

                      }

                   }

                   if(pdialog->m_pathStartFolder.has_character())
                   {

                      pqfiledialog->setDirectory(pdialog->m_pathStartFolder.c_str());

                   }

                   pqfiledialog->show();


                   QObject::connect(pqfiledialog, &QDialog::finished,
                                    [pdialog, pqfiledialog](int finished)
                                    {

                                       ::pointer<::file::file_dialog> pdialogTransfer(transfer_t{}, pdialog);

                                       pdialog->m_pathStartFolder = (const_char_pointer ) pqfiledialog->directory().absolutePath().toUtf8().data();

                                       if(finished)
                                       {


                                          for(auto & file : pqfiledialog->selectedFiles())
                                          {

                                             pdialog->m_patha.add((const_char_pointer ) file.toUtf8().data());

                                          }

                                       }

                                       pdialog->m_function(::transfer(pdialogTransfer));

                                       delete pqfiledialog;

                                    });




                });

   }


   void node::_node_folder_dialog(::file::folder_dialog * pdialog)
   {

      pdialog->increment_reference_count();

      user_post([pdialog]()
                {

                   auto pqfiledialog = new QFileDialog();

                   pqfiledialog->setAcceptMode(QFileDialog::AcceptMode::AcceptOpen);

                   pqfiledialog->setFileMode(QFileDialog::FileMode::Directory);

                   pqfiledialog->setOption(QFileDialog::Option::ShowDirsOnly);

                   if(pdialog->m_path.has_character())
                   {

                      pqfiledialog->setDirectory(pdialog->m_path.c_str());

                   }

                   QObject::connect(pqfiledialog, &QDialog::finished,
                                    [pdialog, pqfiledialog](int finished)
                                    {

                                       ::pointer<::file::folder_dialog> pdialogTransfer(transfer_t{}, pdialog);

                                       if(finished)
                                       {

                                           pdialog->m_path = (const_char_pointer ) pqfiledialog->directory().absolutePath().toUtf8().data();

                                       }

                                       pdialog->m_function(::transfer(pdialogTransfer));

                                       delete pqfiledialog;

                                    });


                   pqfiledialog->show();


                });

   }

   //
   // ::wl_display * node::get_wayland_display()
   // {
   //
   //    QPlatformNativeInterface *native =  QGuiApplication::platformNativeInterface();
   //
   //    auto pwldisplay = (::wl_display *) native->nativeResourceForWindow("display", NULL);
   //
   //    return pwldisplay;
   //
   // }


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
//      ::string strCommand = "sh -c \"nohup kioclient exec " + pathDesktopFile + " &\"";
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
//      warning() << "Failed to launch application \"" + scopedstrAppId + "\" using kioclient exec";
//
//      information() << "Going to try to launch with executable path.";
//
//      ::aura_posix::node::launch_app_by_app_id(scopedstrAppId);

   }


   // bool node::dark_mode() const
   // {
   //
   //    auto pnodeThisMutable = (node *) this;
   //
   //    pnodeThisMutable->_fetch_user_color();
   //
   //    auto pthemecolors = pnodeThisMutable->_get_os_theme_colors();
   //
   //    auto bDarkMode = pthemecolors->m_colorBack.get_luminance() < 0.5;
   //
   //    return bDarkMode;
   //
   // }


} // namespace node_q



