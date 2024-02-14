//
// Created by camilo on 15/02/2021 <3ThomasBS_!!.
//
#include "framework.h"
#include "notify_icon.h"
#include "node.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "apex/platform/application.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/context_image.h"
#include "aura/platform/context.h"
#include "aura/windowing/icon.h"
#include <QMenu>


namespace node_kde
{


   notify_icon::notify_icon()
   {


      m_pstatusnotifieritem = nullptr;

      //m_pindicator = nullptr;

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

      strNotifyIcon = "notify_icon_" + atom.as_string();

      m_strId = "ca2-" + picon->get_tray_icon_name() + "-" + strNotifyIcon;

      m_atom = atom;

      m_piconCurrent = picon;

      m_puserinteractionNotify = puserinteractionNotify;

      ::pointer < ::node_kde::node > pnode = system()->node();

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

      m_pstatusnotifieritem = __new< KStatusNotifierItem >();

      string strTrayIconName = m_piconCurrent->get_tray_icon_name();

      auto pathHome = dir()->home();

      auto papp = get_app();

      auto pathIcon24 = pathHome / ".config" / papp->m_strAppId / "main/icon-24-resized.png";

      auto pimage = m_pcontext->context_image()->get_image("matter://main/icon-256.png");

      auto pimage24 = m_pcontext->m_pauracontext->create_image({24, 24});

      image_source imagesource(pimage);

      auto rectangle = rectangle_f64_dimension(0., 0., 24., 24.);

      image_drawing_options imagedrawingoptions(rectangle);

      image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pimage24->g()->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);

      pimage24->g()->draw(imagedrawing);

      m_pcontext->context_image()->save_image(pathIcon24, pimage24);

      m_pstatusnotifieritem->setIconByName(pathIcon24.c_str());

      string strFriendlyName = papp->m_papexapplication->get_app_user_friendly_task_bar_name();

      auto pmenu = __new< QMenu >();

      for (index i = 0; i < m_papplicationmenu->get_count(); i++)
      {

         auto pitem = m_papplicationmenu->element_at(i);

         string strLabel = pitem->m_strLabel;

         string strId = pitem->m_atom;

         string strName = pitem->m_strLabel;

         if (strId == "separator")
         {

            if (i + 1 < m_papplicationmenu->get_count() && string(m_papplicationmenu->element_at(i + 1)->m_atom) == "app_exit")
            {


            }
            else
            {

               pmenu->addSeparator();

            }

         }
         else
         {

            auto paction = __new< QAction >(strName.c_str(), pmenu);

            connect(paction, &QAction::triggered, this, [this, strId]()
            {

               application()->on_application_menu_action(strId);

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

//    }


   }


   bool notify_icon::notify_icon_step()
   {

        //return ::success;

        return true;

    }


} // namespace node_kde



