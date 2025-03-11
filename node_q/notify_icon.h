#pragma once


#include "aura/user/user/notify_icon.h"
#include <QObject>
#include <QSystemTrayIcon>
#include <QMenu>


namespace node_q
{


   class CLASS_DECL_AURA notify_icon :
      virtual public ::user::notify_icon
   {
   public:

      QSystemTrayIcon * m_pqsystemtrayicon;
//QIcon * m_pqicon;
      // Create context menu
      QMenu  * m_pqmenu;

      ::array < QObject * > m_qobjecta;


      ::pointer<::aura_posix::appindicator>         m_pindicator;
      ::image::image_pointer                                 m_pimage;


      notify_icon();
      ~notify_icon() override;


      void add_hidden_window(::user::interaction * puserinteraction) override;

      void modify_icon(::windowing::icon * picon) override;

      void create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon) override;

      //virtual ::e_status _create_status_notifier_item();

      virtual ::e_status _populate_qmenu_popup(QMenu * pmenu, application_menu * papplicationmenu);

      virtual ::e_status _populate_qmenu(QMenu * pmenu, ::collection::index i, application_menu * papplicationmenu);

      bool notify_icon_step() override;

      //virtual void _on_menu_action(const ::scoped_string & scopedstrMenuActionId);


   };


} // namespace node_q



