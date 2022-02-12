//
// Created by camilo on 15/02/2021 <3ThomasBS_!!.
//
#include "framework.h"
#include "aura/user/_user.h"


namespace node_kde
{


   notify_icon::notify_icon()
   {


      m_pstatusnotifieritem = nullptr;

      m_pindicator = nullptr;

      m_bCreated = false;

   }


   notify_icon::~notify_icon()
   {


   }


   void notify_icon::create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon)
   {

      if (m_bCreated)
      {

         //return ::success_none;

         return;

      }

      string strNotifyIcon;

      strNotifyIcon = "notify_icon_" + atom.to_string();

      m_strId = "ca2-" + picon->get_tray_icon_name() + "-" + strNotifyIcon;

      m_atom = atom;

      m_piconCurrent = picon;

      m_puserinteractionNotify = puserinteractionNotify;

      auto pnode = m_psystem->m_pnode->m_pNodeKDE;

      QObject::setParent(pnode->m_pqapplication);

      auto estatus = _create_status_notifier_item();

      if(!estatus)
      {

         //return estatus;

         throw ::exception(estatus);

      }

      m_bCreated = true;

      //return ::success;

   }


   ::e_status notify_icon::_create_status_notifier_item()
   {

      m_pstatusnotifieritem = new KStatusNotifierItem();

      string strTrayIconName = m_piconCurrent->get_tray_icon_name();

      auto papplication = get_application();

      ::file::path pathIcon = papplication->dir().matter("main/icon-256.png");

      m_pstatusnotifieritem->setIconByName(pathIcon.c_str());

      string strFriendlyName = papplication->get_app_user_friendly_task_bar_name();

      auto pmenu = new QMenu();

      for (index i = 0; i < _get_notification_area_action_count(); i++)
      {

         string strLabel = _get_notification_area_action_label(i);

         string strId = _get_notification_area_action_id(i);

         string strName = _get_notification_area_action_name(i);

         if (strId == "separator")
         {

            if (i + 1 < _get_notification_area_action_count() && string(_get_notification_area_action_id(i + 1)) == "app_exit")
            {


            }
            else
            {

               pmenu->addSeparator();

            }

         }
         else
         {

            auto paction = new QAction(strName.c_str(), pmenu);

            connect(paction, &QAction::triggered, this, [this, strId]()
            {

               call_notification_area_action(strId);

            });

            pmenu->addAction(paction);

         }

      }

      m_pstatusnotifieritem->setTitle(strFriendlyName.c_str());

      m_pstatusnotifieritem->setCategory(KStatusNotifierItem::ApplicationStatus);

      m_pstatusnotifieritem->setStatus(KStatusNotifierItem::Active);

      m_pstatusnotifieritem->setContextMenu(pmenu);

      m_pstatusnotifieritem->setStandardActionsEnabled(false);

      m_pstatusnotifieritem->setParent(this);

      return ::success;

   }


   void notify_icon::modify_icon(::windowing::icon * picon)
   {

      if(!m_bCreated)
      {

         //return ::error_failed;

         throw ::exception(error_failed);

      }

      //auto estatus =
      //
      ::user::notify_icon::modify_icon(picon);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   void notify_icon::add_hidden_window(::user::interaction * puserinteraction)
   {

      //auto estatus =
      //
      ::user::notify_icon::add_hidden_window(puserinteraction);

//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;

   }


   bool notify_icon::step()
   {

      //return ::success;

      return true;

   }


} // namespace node_kde



