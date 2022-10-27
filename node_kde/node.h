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
#include "node_impl.h"
#include "aura_posix/node.h"
#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QApplication>
#include <QPalette>


class KIconLoader;


namespace node_kde
{


   class CLASS_DECL_ACME node :
      virtual public ::aura_posix::node,
      virtual public QAbstractNativeEventFilter,
      virtual public QObject
   {
   public:


      KIconLoader *        m_piconloader;

      QApplication *       m_pqapplication;

      QPalette             m_qpalette;

      //qDebug() << "palette after:" << palette2.color(group, role).name();

      //node_impl *    m_pnodeimpl;
      //gpointer m_pGtkSettingsDefault;
      //string   m_strTheme;

      node();
      ~node() override;


      void node_quit() override;

      ::os_theme_colors * new_os_theme_colors();

      void fetch_user_color() override;

      int node_init_check(int * pi, char *** ppz) override;

      bool eventFilter(QObject * pparticle, QEvent * pevent) override;

      void system_main() override;

      void initialize(::particle * pparticle) override;

      ::e_status _allocate_Display_and_connection() override;

      //void os_calc_user_dark_mode() override;

      //void on_os_dark_mode_change() override;

      string os_get_user_theme() override;

      void os_set_user_theme(const string & strUserTheme) override;

      void os_process_user_theme(string strTheme) override;

      void enable_wallpaper_change_notification() override;

      string get_file_icon_path(const ::string & pszPath, int iSize) override;

      string get_file_content_type(const ::string & pszPath) override;

      bool set_wallpaper(index iScreen, string strLocalImagePath) override;

      string get_wallpaper(index iScreen) override;

      //using ::aura::node::node_fork;

      void node_post(const ::procedure & procedure) override;

      //void node_post_quit() override;

      //void os_post_quit() override;

      //bool _os_calc_system_dark_mode() override;

      void reboot() override;

      bool should_launch_on_node(::topic * ptopic) override;

      bool launch_on_node(::topic * ptopic) override;

      int os_launch_uri(const ::string & pszUri, char * pszError = NULL, int iBufferSize = 0) override;

      bool nativeEventFilter(const QByteArray &eventType, void *message, long *result)  override;


      virtual ::e_status _qapplication_exec();


      void shell_launch(const ::string & strAppId);


      void open_url(const ::string & strUrl) override;


   };


} // namespace node_kde



