//
// Created by camilo on 15/02/2021 <3ThomasBS_!!.
//
#include "framework.h"
#include "notify_icon.h"
#include "node.h"
#include "acme/constant/id.h"
#include "acme/platform/system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "apex/platform/application.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/context.h"
#include "aura/platform/context.h"
#include "aura/windowing/icon.h"
#include "windowing_q/window.h"
#include <QMenu>
#include "windowing_q/windowing.h"
#include "acme/filesystem/file/memory_file.h"
//#include <QMe>


namespace node_q
{


   notify_icon::notify_icon()
   {


      //m_pstatusnotifieritem = nullptr;

      //m_pindicator = nullptr;

      m_bCreated = false;

      m_pqsystemtrayicon = nullptr;

      m_pqmenu = nullptr;

      //m_pqicon = nullptr;

   }


   notify_icon::~notify_icon()
   {


   }


//    void notify_icon::handleMenuAction()
//    {
//       QAction *action = qobject_cast<QAction *>(sender());
//    if (!action) return;
//
//    // Identify the QAction based on data
//    QVariant actionId = action->data();
//    if (actionId.isValid()) {
//
//       ::string strId = actionId.toString().toUtf8();
//
//       _on_menu_action(strId);
//    }
// }


   // void notify_icon::_on_menu_action(const ::scoped_string & scopedstrMenuActionId)
   // {
   //
   //
   // }
   QIcon createIconFromMemory(void *p, int len) {
      QByteArray byteArray(reinterpret_cast<const_char_pointer  >(p), len);  // Convert to QByteArray
      QPixmap pixmap;
      pixmap.loadFromData(byteArray, "PNG");  // Load as a PNG image
      return QIcon(pixmap);
   }

   void notify_icon::create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * pwindowingicon)
   {
      if (m_bCreated)
      {

         //return ::success_none;

         return;

      }

      auto picon = as_pointer(pwindowingicon);

      _main_send([this, atom, puserinteractionNotify, picon]()
         {

      // Ensure system tray is available
      if (!QSystemTrayIcon::isSystemTrayAvailable())
         {
         throw ::exception(error_wrong_state);
      }


      string strNotifyIcon;

      strNotifyIcon = "notify_icon_" + atom.as_string();

      m_strId = "ca2-" + picon->get_tray_icon_name() + "-" + strNotifyIcon;

m_piconCurrent = picon;
      // //
      // //
      // // // Create tray icon
      // // QSystemTrayIcon trayIcon;
      // m_qsystemtrayicon.setIcon(QIcon::fromTheme(m_strId.c_str())); // Use a system icon




      //m_pstatusnotifieritem = ___new KStatusNotifierItem();

      string strTrayIconName = m_piconCurrent->get_tray_icon_name();

      auto pathHome = directory()->home();

      auto papp = get_app();

      auto pathIcon24 = pathHome / ".config" / papp->m_strAppId / "main/icon-24-resized.png";

      auto pimage = image()->get_image("matter://main/icon-256.png");

      auto pimage24 = image()->create_image({24, 24});

      ::image::image_source imagesource(pimage);

      auto rectangle = double_rectangle_dimension(0., 0., 24., 24.);

      ::image::image_drawing_options imagedrawingoptions(rectangle);

      ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

      pimage24->g()->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);

      pimage24->g()->draw(imagedrawing);

         auto pfileImage = create_memory_file();

      image()->save_image(pfileImage, pimage24);


      m_pqsystemtrayicon = new QSystemTrayIcon();

      QString qstrFilename;

      qstrFilename = pathIcon24.c_str();

      printf_line("notify_icon icon_file path: %s", qstrFilename.toStdString().c_str());

      //m_pqicon = new QIcon(qstrFilename);

      m_pqsystemtrayicon->setIcon(createIconFromMemory(pfileImage->memory().data(), pfileImage->memory().size()));

      string strFriendlyName = papp->get_app_user_friendly_task_bar_name();

      //auto pmenu = ___new QMenu();

      m_pqmenu = new QMenu();

      m_qobjecta.add(m_pqmenu);

      _populate_qmenu_popup(m_pqmenu, m_papplicationmenu);

      m_pqsystemtrayicon->setContextMenu(m_pqmenu);


//       QMenu menu;
//       QAction quitAction("Quit", &menu);
//       QObject::connect(&quitAction, &QAction::triggered, [this]()
//       {
//
// information("what");
//
//       });
//       menu.addAction(&quitAction);
//
//       m_pqsystemtrayicon->setContextMenu(&menu);
      //m_qsystemtrayicon.setTitle(strFriendlyName.c_str());

      //m_qsystemtrayicon.setCategory(KStatusNotifierItem::ApplicationStatus);

      //m_qsystemtrayicon.setStatus(KStatusNotifierItem::Active);

      //m_pstatusnotifieritem->setContextMenu(pmenu);

      //m_qsystemtrayicon.setStandardActionsEnabled(false);

      //m_qsystemtrayicon.setParent(this);


      // Show tray icon
      m_pqsystemtrayicon->show();

      // Show notification
      //trayIcon.showMessage("Hello", "This is a KDE notification", QSystemTrayIcon::Information, 3000);

      //m_pqsystemtrayicon->showMessage(m_papplication->get_app_user_friendly_task_bar_name().c_str(),
         //"Starting...", QSystemTrayIcon::Information, 3000);

      m_atomMatterId = atom;

      m_piconCurrent = picon;

      m_puserinteractionNotify = puserinteractionNotify;

      ::cast < ::windowing_q::windowing > pqwindowing = system()->acme_windowing();

      //QObject::setParent(plxq2windowing->m_pqapplication);

      // auto estatus = _create_status_notifier_item();
      //
      // if(!estatus)
      // {
      //
      //    //return estatus;
      //
      //    throw ::exception(estatus);
      //
      // }

      m_bCreated = true;

      //return ::success;

         });

   }


   ::e_status notify_icon::_populate_qmenu_popup(QMenu * pmenuPopup, application_menu * papplicationmenu)
   {

      for (::collection::index i = 0; i < papplicationmenu->count(); i++)
      {

         auto pitem = papplicationmenu->element_at(i);

         _populate_qmenu(pmenuPopup, i, pitem);

      }

      return ::success;

   }


   ::e_status notify_icon::_populate_qmenu(QMenu * pmenu, ::collection::index i, application_menu * papplicationmenu)
   {

      string strLabel = papplicationmenu->m_strName;

      auto atom = papplicationmenu->m_atomMenu;

      string strName = papplicationmenu->m_strName;

      information() << "Item::name : " << strName;
      information() << "Item::id : " << atom.as_string();
      information() << "Item::label : " << strLabel;

      if(papplicationmenu->m_bPopup)
      {

         pmenu->setTitle(strLabel.c_str());

         QMenu * pmenuPopup = ___new QMenu();

         _populate_qmenu_popup(pmenuPopup, papplicationmenu);

         pmenu->addMenu(pmenuPopup);

      }
      else
      {
//      for (::collection::index i = 0; i < m_papplicationmenu->get_count(); i++)
//      {
//
//         auto pitem = m_papplicationmenu->element_at(i);

         if (atom == id_separator)
         {

            if (i + 1 < m_papplicationmenu->get_count() && string(m_papplicationmenu->element_at(i + 1)->m_atomMenu) == "app_exit")
            {


            }
            else
            {

               pmenu->addSeparator();

            }

         }
         else
         {

            auto paction = pmenu->addAction(strName.c_str());
            //openAct->setShortcut(tr("Ctrl+O"));
            QObject::connect(paction, &QAction::triggered, [this, atom]()
            {

               application()->handle_command(atom, nullptr);

            });

            //rauto paction =
            //auto paction =  pmenu->addAction(strId.c_str(), );

            //paction->setText(strName.c_str());

         }

      }

      return ::success;

   }


   // ::e_status notify_icon::_create_status_notifier_item()
   // {
   //
   //    m_pstatusnotifieritem = ___new KStatusNotifierItem();
   //
   //    string strTrayIconName = m_piconCurrent->get_tray_icon_name();
   //
   //    auto pathHome = directory()->home();
   //
   //    auto papp = get_app();
   //
   //    auto pathIcon24 = pathHome / ".config" / papp->m_strAppId / "main/icon-24-resized.png";
   //
   //    auto pimage = image()->get_image("matter://main/icon-256.png");
   //
   //    auto pimage24 = image()->create_image({24, 24});
   //
   //    ::image::image_source imagesource(pimage);
   //
   //    auto rectangle = double_rectangle_dimension(0., 0., 24., 24.);
   //
   //    ::image::image_drawing_options imagedrawingoptions(rectangle);
   //
   //    ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);
   //
   //    pimage24->g()->set_compositing_quality(::draw2d::e_compositing_quality_high_quality);
   //
   //    pimage24->g()->draw(imagedrawing);
   //
   //    image()->save_image(pathIcon24, pimage24);
   //
   //    m_pstatusnotifieritem->setIconByName(pathIcon24.c_str());
   //
   //    string strFriendlyName = papp->get_app_user_friendly_task_bar_name();
   //
   //    //auto pmenu = ___new QMenu();
   //
   //    auto pmenu = m_pstatusnotifieritem->contextMenu();
   //
   //    _populate_qmenu_popup(pmenu, m_papplicationmenu);
   //
   //    m_pstatusnotifieritem->setTitle(strFriendlyName.c_str());
   //
   //    m_pstatusnotifieritem->setCategory(KStatusNotifierItem::ApplicationStatus);
   //
   //    m_pstatusnotifieritem->setStatus(KStatusNotifierItem::Active);
   //
   //    m_pstatusnotifieritem->setContextMenu(pmenu);
   //
   //    m_pstatusnotifieritem->setStandardActionsEnabled(false);
   //
   //    m_pstatusnotifieritem->setParent(this);
   //
   //    return ::success;
   //
   // }
   //

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


} // namespace node_q



