//
// Created by camilo on 15/02/2021.
//

#include "framework.h"
//#include "apex/os/freebsd/xfce_xfce.h"
#include "aura/user/_user.h"


static ::user::notify_icon * g_pnotifyiconLast = nullptr;


#ifdef LINUX

#include "aura/os/freebsd/appindicator.h"

#endif


namespace node_xfce
{


   notify_icon::notify_icon()
   {

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


   bool notify_icon::create_notify_icon(unsigned int uId, ::user::notify_icon_listener * plistener, ::windowing::icon * picon)
   {

      if(m_bCreated)
      {

         return false;

      }

      m_strId.formatf("notify_icon_%d", uId);

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

#elif defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)

      m_picon = picon;

#elif defined(MACOS)

      #elif defined(UNIVERSAL_WINDOWS)

#elif defined(__ANDROID__)

#elif defined(APPLE_IOS)

#else
      throw ::exception(todo());

#endif

      m_plistener                = plistener;

#ifdef WINDOWS_DESKTOP

      //if(!Shell_NotifyIcon(NIM_ADD, &m_nid))
      //{

      //   m_plistener = nullptr;

      //   DestroyWindow();

      //   return false;

      //}

#elif defined(LINUX) && !defined(RASPBERRYPIOS)

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

         ::file::path path = pathFolder / ("notify_icon_128.png");

         auto pcontext = m_papplication;

         path = pcontext->defer_process_path(path);

         pathFolder = path.folder();

         auto psystem = system();

         auto pnode = psystem->node();

         pnode->node_send(5_s, __routine([this, pnode, pathFolder]()
                                         {


                                            auto estatus = __øconstruct(m_pindicator);

                                            m_pindicator->create(m_strId, "notify_icon_128", pathFolder, this);

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
//      if(str.case_insensitive_begins_eat("app_veriwell_"))
//      {
//
//         strFolder+="app-veriwell";
//
//      }
//      else if(str.case_insensitive_begins_eat("app_core_"))
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
//      string strUrl = "https://ca2.network/matter/" + strFolder + strFile;
//
//      strFile = Context.directory()->appdata() / strFolder / strFile;
//
//      int iRetry = 3;
//
//      while(iRetry >= 0 && (!Context.file()->exists(strFile) || Context.file()->length(strFile) <= 0))
//      {
//
//         ::property_set set;
//
//         set["raw_http"] = true;
//         set["disable_common_name_cert_check"] = true;
//
//         Context.http()->download(strUrl, strFile, set);
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

      throw ::exception(todo);

#endif


   }


   void notify_icon::AddHiddenWindow(::pointer<::user::interaction>pwnd)
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
//#elif defined(LINUX) && !defined(RASPBERRYPIOS)
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
//      throw ::exception(todo());
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
//      informationf("notify_icon::_001OnDestroy");
//
//   }


   //void notify_icon::_001OnNotifyIconMessage(::message::message * pmessage)
   //{

   //   ::pointer<::user::message>pusermessage(pmessage);

   //   if (pusermessage->m_lparam == e_message_left_button_down)
   //   {

   //      while (m_wndptraHidden.get_size() > 0)
   //      {

   //         try
   //         {

   //            ::pointer<::user::interaction>pframe = (m_wndptraHidden.element_at(0));

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

   //         m_wndptraHidden.erase_at(0);

   //      }

   //   }

   //   m_plistener->OnNotifyIconMessage(m_uiId, (unsigned int) pusermessage->m_lparam);

   //}


   //void notify_icon::notify_icon_play(const_char_pointer action)
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


   const_char_pointer notify_icon::_get_notification_area_action_name(int iIndex)
   {

      return m_plistener->_get_notification_area_action_name(iIndex);

   }


   const_char_pointer notify_icon::_get_notification_area_action_id(int iIndex)
   {

      return m_plistener->_get_notification_area_action_id(iIndex);

   }


   const_char_pointer notify_icon::_get_notification_area_action_label(int iIndex)
   {

      return m_plistener->_get_notification_area_action_label(iIndex);

   }


   const_char_pointer notify_icon::_get_notification_area_action_accelerator(int iIndex)
   {

      return m_plistener->_get_notification_area_action_accelerator(iIndex);

   }


   const_char_pointer notify_icon::_get_notification_area_action_description(int iIndex)
   {

      return m_plistener->_get_notification_area_action_description(iIndex);

   }


   void notify_icon::call_notification_area_action(const_char_pointer pszId)
   {

      m_plistener->call_notification_area_action(scopedstrId);

   }


//#endif


} // namespace node_xfce



