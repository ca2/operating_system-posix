//
// Created by camilo on 15/02/2021.
//

#include "framework.h"
//#include "apex/os/linux/gnome_gnome.h"
#include "aura/user/_user.h"



static ::user::notify_icon * g_pnotifyiconLast = nullptr;


#ifdef LINUX

#include "aura/os/linux/appindicator.h"

#endif


namespace node_kde
{


   notify_icon::notify_icon()
   {

      m_pstatusnotifieritem = nullptr;
      g_pnotifyiconLast = this;

#ifdef WINDOWS_DESKTOP

      //m_nid.cbSize = sizeof(m_nid);

#elif defined(LINUX)

      m_pindicator = nullptr;

#endif

      m_bCreated = false;

   }


   notify_icon::~notify_icon()
   {

      //DestroyWindow();

      if(g_pnotifyiconLast== this)
      {

         g_pnotifyiconLast = nullptr;

      }

   }


   /*void notify_icon::install_message_routing(::channel * pchannel)
   {

#ifdef WINDOWS_DESKTOP

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(MessageNotifyIcon, pchannel, this, &notify_icon::_001OnNotifyIconMessage);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &notify_icon::_001OnDestroy);

#endif

   }*/


   bool notify_icon::create_notify_icon(::u32 uId, ::user::notify_icon_listener * plistener, ::windowing::icon * picon)
   {

      if(m_bCreated)
      {

         return false;

      }

      m_plistener = plistener;


      auto pnode = m_psystem->m_pnode->m_pNodeKDE;

      pnode->node_branch(__routine([this, picon]()
      {

         auto papplication = get_application();

         string strWMClass = papplication->get_wm_class();

         auto pnode = m_psystem->m_pnode->m_pNodeKDE;

         QObject::setParent(pnode->m_pqapplication);

         m_pstatusnotifieritem = new KStatusNotifierItem(this);

         string strTrayIconName = picon->get_tray_icon_name();

         ::file::path pathIcon = papplication->dir().matter("main/icon-256.png");

         m_pstatusnotifieritem->setIconByName(pathIcon.c_str());

         string strFriendlyName = papplication->get_app_user_friendly_task_bar_name();

         auto pmenu = m_pstatusnotifieritem->contextMenu();

//      connect( msmKernel, &QAction::triggered, this, [msmKernel, this]()
//      {
//         QProcess::startDetached( "manjaro-settings-manager", QStringList() << "-m" << "msm_kernel" );
//         m_tray->setStatus( KStatusNotifierItem::Passive );
//      } );
//      connect( msmLanguagePackages, &QAction::triggered, this, [msmLanguagePackages, this]()
//      {
//         QProcess::startDetached( "manjaro-settings-manager", QStringList() << "-m" << "msm_language_packages" );
//         m_tray->setStatus( KStatusNotifierItem::Passive );
//      } );
//
//      connect( optionsAction, &QAction::triggered, this, [optionsAction, this]()
//      {
//         m_settingsDialog = new NotifierSettingsDialog(NULL);
//         m_settingsDialog->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose, true);
//         m_settingsDialog->exec();
//      } );

         for(index i = 0; i < _get_notification_area_action_count(); i++)
         {

            string strLabel = _get_notification_area_action_label(i);

            string strId = _get_notification_area_action_id(i);

            string strName = _get_notification_area_action_name(i);

            if(strId == "app_exit")
            {

            }
            else if(strId == "separator")
            {

               if(i + 1 < _get_notification_area_action_count() && _get_notification_area_action_id(i+1) == "app_exit")
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
   //         QAction* msmLanguagePackages = new QAction(
   //            QIcon( ":/icons/language.png" ),
   //            QString( tr ( "Language packages" ) ),
   //            menu );
   //
   //         QAction* optionsAction = new QAction(
   //            QIcon::fromTheme( "gtk-preferences"  ),
   //            QString( tr ( "Options" ) ),
   //            menu );

               connect(paction, &QAction::triggered, this, [this, strId]()
               {

                  call_notification_area_action(strId);

               });

               pmenu->addAction(paction);


            }


         }


      m_pstatusnotifieritem->setTitle(strFriendlyName.c_str());
      m_pstatusnotifieritem->setCategory(KStatusNotifierItem::ApplicationStatus);
      m_pstatusnotifieritem->setStatus( KStatusNotifierItem::Active );


      //notification->setActions({i18n("Open chat")});
      //const auto groups = contact->groups();
      //for (const QString &group : groups) {
        // notification->addContext("group", group);
      //}
      //connect(notification, QOverload<unsigned int>::of(&KNotification::activated), contact, &Contact::slotOpenChat);
      //m_pstatusnotifieritem->update();
m_pstatusnotifieritem->setStatus(KStatusNotifierItem::ItemStatus::Active);

                                   }));

      m_strId.Format("notify_icon_%d", uId);

      m_strId = "ca2-" + picon->get_tray_icon_name() + "-" + m_strId;

#ifdef WINDOWS_DESKTOP

      if(!create_message_queue(m_strId))
      {

         return false;

      }

#endif

      m_uiId                     = uId;

#ifdef WINDOWS_DESKTOP

      //m_nid.hWnd                 = get_safe_handle();
      //m_nid.uID                  = uId;
      //m_nid.hIcon                = *pvisualicon;
      //m_nid.uFlags               = NIF_ICON | NIF_MESSAGE;
      //m_nid.uCallbackMessage     = MessageNotifyIcon;

#elif defined(LINUX) || defined(FREEBSD)

      m_picon = picon;

#elif defined(MACOS)

      #elif defined(_UWP)

#elif defined(ANDROID)

#elif defined(APPLE_IOS)

#else
      __throw(todo());

#endif

      m_plistener                = plistener;

#ifdef WINDOWS_DESKTOP

      //if(!Shell_NotifyIcon(NIM_ADD, &m_nid))
      //{

      //   m_plistener = nullptr;

      //   DestroyWindow();

      //   return false;

      //}

#elif defined(LINUX) && !defined(RASPBIAN)

      {

         string strAppId = m_picon->get_tray_icon_name();

         string strId(strAppId);

         string strMatterRoot = ::str::token(strId, "/");

         if(strMatterRoot.is_empty())
         {

            strMatterRoot = "app";

         }

         ::file::path pathFolder("appmatter://" + strMatterRoot);

         pathFolder /= "_matter" / strId / "_std/_std/main" ;

         string strNotifyIcon = _002Underscore(strAppId);

         ::file::path path = pathFolder / (strNotifyIcon + "_128.png");

         auto pcontext = m_pcontext->m_papexcontext;

         path = pcontext->defer_process_path(path);

         pathFolder = path.folder();

         auto psystem = m_psystem;

         auto pnode = psystem->node();

         pnode->node_sync(5_s, __routine([this, pnode, strNotifyIcon, pathFolder]()
                                         {

                                            auto estatus = __construct(m_pindicator);

                                            m_pindicator->create(m_strId, strNotifyIcon + "_128", pathFolder, m_plistener);

                                         }));

      }

      if(m_pindicator == nullptr)
      {

         m_plistener = nullptr;

         //DestroyWindow();

         return false;

      }

#elif defined(MACOS)

      //      string strFolder;
//
//      string str1 = pvisualicon->m_strAppTrayIcon;
//
//      str1.replace("-", "_");
//
//      str1.replace("/", "_");
//
//      str1.replace("\\", "_");
//
//      string str(str1);
//
//      if(::str::begins_eat_ci(str, "app_veriwell_"))
//      {
//
//         strFolder+="app-veriwell";
//
//      }
//      else if(::str::begins_eat_ci(str, "app_core_"))
//      {
//
//         strFolder+="app-core";
//
//      }
//      else
//      {
//
//         strFolder+="app";
//
//      }
//
//      //str
//
//      strFolder+= "/appmatter/" + str;
//
//      strFolder += "/_std/_std/main/";
//
//      string strFile = "menubar-icon-22.png";
//
//      string strUrl = "https://server.ca2.cc/matter/" + strFolder + strFile;
//
//      strFile = Context.dir().appdata() / strFolder / strFile;
//
//      int iRetry = 3;
//
//      while(iRetry >= 0 && (!Context.file().exists(strFile) || Context.file().length(strFile) <= 0))
//      {
//
//         ::property_set set;
//
//         set["raw_http"] = true;
//         set["disable_common_name_cert_check"] = true;
//
//         Context.http().download(strUrl, strFile, set);
//
//         iRetry--;
//
//      }

      string strFile;

      strFile = Context.defer_process_matter_path("matter://main/menubar-icon-22.png");

      notify_icon_init(strFile);

#else

#endif

      m_bCreated = true;

      return true;

   }


   bool notify_icon::modify_icon(::windowing::icon * picon)
   {

      if(!m_bCreated)
      {

         return false;

      }


#ifdef WINDOWS_DESKTOP

         //m_nid.hIcon       = (HICON) *hicon;

      //m_nid.uFlags      = NIF_ICON;

      //if(!Shell_NotifyIcon(NIM_MODIFY, &m_nid))
      //{

      //   return false;

      //}

      //m_piconCurrent = hicon;

      return true;

#else

      __throw(todo);

#endif


   }


   void notify_icon::AddHiddenWindow(__pointer(::user::interaction) pwnd)
   {

      m_wndptraHidden.add_unique(pwnd);

   }


#ifdef WINDOWS_DESKTOP


   //void notify_icon::destroy_window()
   //{

   //   m_nid.uFlags = 0;

   //   if (!Shell_NotifyIcon(NIM_DELETE, &m_nid))
   //   {

   //      //return false;

   //   }

   //   ::user::interaction::destroy_window();

   //}


   //void notify_icon::remove_all_routes()
   //{

   //   ::user::interaction::remove_all_routes();

   //}


   //void notify_icon::PostNcDestroy()
   //{

   //   ::user::interaction::PostNcDestroy();


   //}

#endif // defined(WINDOWS_DESKTOP)

//
//   bool notify_icon::DestroyWindow()
//   {
//
//      if(!m_bCreated)
//      {
//
//         return false;
//
//      }
//
//      m_bCreated = false;
//
//#ifdef WINDOWS_DESKTOP
//
//      ::user::interaction::DestroyWindow();
//
//      return true;
//
//
//#elif defined(LINUX) && !defined(RASPBIAN)
//
//      if(m_pindicator)
//      {
//
//         auto pnode = Node;
//
//         pnode->appindicator_destroy(m_pindicator);
//
//         m_pindicator = nullptr;
//
//      }
//
//      return true;
//
//#elif defined(MACOS)
//
//      notify_icon_destroy();
//
//      return true;
//
//#else
//
//
//      __throw(todo());
//
//      return true;
//
//#endif
//
//   }
//
//
//   void notify_icon::_001OnDestroy(::message::message* pmessage)
//   {
//
//      output_debug_string("notify_icon::_001OnDestroy");
//
//   }


   //void notify_icon::_001OnNotifyIconMessage(::message::message * pmessage)
   //{

   //   __pointer(::user::message) pusermessage(pmessage);

   //   if (pusermessage->m_lparam == e_message_left_button_down)
   //   {

   //      while (m_wndptraHidden.get_size() > 0)
   //      {

   //         try
   //         {

   //            __pointer(::user::interaction) pframe = (m_wndptraHidden.element_at(0));

   //            if (pframe != nullptr)
   //            {

   //               pframe->display(e_display_normal);

   //            }
   //            else
   //            {

   //               m_wndptraHidden.element_at(0)->display(e_display_normal);

   //            }

   //         }
   //         catch (...)
   //         {

   //         }

   //         m_wndptraHidden.remove_at(0);

   //      }

   //   }

   //   m_plistener->OnNotifyIconMessage(m_uiId, (::u32) pusermessage->m_lparam);

   //}


   //void notify_icon::notify_icon_play(const char * action)
   //{


   //}


   ::e_status notify_icon::step()
   {

#if defined(LINUX)

//      main_async([&]
//      {
//
//         linux_g_direct_app_indicator_step(m_pindicator);
//
//      });

#endif

      return ::success;

   }


//#if defined(LINUX) || defined(MACOS)


   int notify_icon::_get_notification_area_action_count()
   {

      return m_plistener->_get_notification_area_action_count();

   }


   const char * notify_icon::_get_notification_area_action_name(int iIndex)
   {

      return m_plistener->_get_notification_area_action_name(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_id(int iIndex)
   {

      return m_plistener->_get_notification_area_action_id(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_label(int iIndex)
   {

      return m_plistener->_get_notification_area_action_label(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_accelerator(int iIndex)
   {

      return m_plistener->_get_notification_area_action_accelerator(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_description(int iIndex)
   {

      return m_plistener->_get_notification_area_action_description(iIndex);

   }


   void notify_icon::call_notification_area_action(const char * pszId)
   {

      m_plistener->call_notification_area_action(pszId);

   }


//#endif


} // namespace node_kde



