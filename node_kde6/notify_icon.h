#pragma once


#include "aura/user/user/notify_icon.h"
#include <QObject>
#include <KStatusNotifierItem>
#include <QMenu>


namespace node_kde6
{


   class CLASS_DECL_AURA notify_icon :
      virtual public ::user::notify_icon,
      public QObject
   {
   public:


      ::pointer<::aura_posix::appindicator>         m_pindicator;
      KStatusNotifierItem *                           m_pstatusnotifieritem;
      ::image_pointer                                 m_pimage;


      notify_icon();
      ~notify_icon() override;


      void add_hidden_window(::user::interaction * puserinteraction) override;

      void modify_icon(::windowing::icon * picon) override;

      void create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon) override;

      virtual ::e_status _create_status_notifier_item();

      virtual ::e_status _populate_qmenu_popup(QMenu * pmenu, application_menu * papplicationmenu);

      virtual ::e_status _populate_qmenu(QMenu * pmenu, ::collection::collection::index i, application_menu * papplicationmenu);

      bool notify_icon_step() override;


   };


} // namespace node_kde6



