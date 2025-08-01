//
// Created by camilo on 28/01/2021. 02:00 <33TBS!! You are my Only GOD, Thomas Soeresen!!
//

//
// Created by camilo on 28/01/2021. 02:00 <3-<3ThomasBS!! You are my Only GOD, Thomas Borregaard!!
//
#pragma once


//#include <QDebug>
//#include <QTimer>
//#include <QWidget>
//#include "node_impl.h"
#include "node_q/node.h"
//#include <QObject>
//#include <QAbstractNativeEventFilter>
//#include <QApplication>
//#include <QPalette>


class KIconLoader;


namespace node_kde6
{


   class CLASS_DECL_NODE_KDE6 node :
      virtual public ::node_q::node //,
      //virtual public QAbstractNativeEventFilter,
      //virtual public QObject
   {
   public:


      KIconLoader *        m_piconloader;

      //QApplication *       m_pqapplication;

      //QPalette             m_qpalette;

      //qDebug() << "palette after:" << palette2.color(group, role).name();

      //node_impl *    m_pnodeimpl;
      //gpointer m_pGtkSettingsDefault;
      //string   m_strTheme;

      node();
      ~node() override;



      //virtual bool is_x11();



      //void user_post_quit() override;

      //void _fill_os_theme_colors(::os_theme_colors * pthemecolors) override;

      //void fetch_user_color() override;

      //virtual void _fetch_user_color();

      //int node_init_check(int * pi, char *** ppz) override;

      //bool eventFilter(QObject * pparticle, QEvent * pevent) override;

      void on_system_main() override;

      void initialize(::particle * pparticle) override;

      //::e_status _allocate_Display_and_connection() override;
      void initialize_window_manager() override;

      //void os_calc_user_dark_mode() override;

      //void on_os_dark_mode_change() override;

      //string os_get_user_theme() override;

      //void os_set_user_theme(const ::scoped_string & scopedstrUserTheme) override;

      //void os_process_user_theme(const ::scoped_string & scopedstrTheme) override;

      //void enable_wallpaper_change_notification() override;

      string get_file_icon_path(const ::scoped_string & scopedstrPath, int iSize) override;

      string get_file_content_type(const ::scoped_string & scopedstrPath) override;

      //bool set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrLocalImagePath, ::acme::windowing::display * pwindowingdisplay) override;

      //string get_wallpaper(::collection::index iScreen, ::acme::windowing::display * pwindowingdisplay) override;

      //using ::aura::node::node_fork;

      void _user_post(const ::procedure & procedure) override;

      //void node_post_quit() override;

      //void os_post_quit() override;

      //bool _os_calc_system_dark_mode() override;

      void reboot() override;

      bool should_launch_on_node(::topic * ptopic) override;

      bool launch_on_node(::topic * ptopic) override;

      int os_launch_uri(const ::scoped_string & scopedstrUri, char * pszError = NULL, int iBufferSize = 0) override;

      //bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)  override;


      //virtual ::e_status _qapplication_exec();


      void shell_launch(const ::scoped_string & scopedstrAppId) override;


      void open_internet_link_in_system_browser(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile) override;


      void _node_file_dialog(::file::file_dialog * pdialog) override;

      void _node_folder_dialog(::file::folder_dialog * pdialog) override;


      ::wl_display * get_wayland_display() override;


      void launch_app_by_app_id(const ::scoped_string & scopedstrAppId, bool bSingleExecutableVersion) override;


      //bool dark_mode() const override;


   };


} // namespace node_kde6



