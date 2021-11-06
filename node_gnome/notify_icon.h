#pragma once


//#if defined (__APPLE__)
//#include "notify_icon_mm_bridge.h"
//#endif


//#ifdef LINUX
#include "apex/user/notify_icon_bridge.h"
//namespace linux { class appindicator; }
//#endif


namespace node_gnome
{


   class CLASS_DECL_AURA notify_icon :
      virtual public ::user::notify_icon
   {
   public:


//      enum e_message
//      {
//
//         MessageNotifyIcon = WM_USER + 100,
//
//      };


      //::u32                                             m_uiId;
      //bool                                              m_bCreated;
      //string                                            m_strId;
//#ifdef WINDOWS_DESKTOP
//      NOTIFYICONDATA m_nid;
//#elif defined(LINUX)
      __pointer(::aura::posix::appindicator)        m_pindicator;
//#endif
      //__pointer(::user::notify_icon_listener)      m_plistener;
      //__pointer_array(::user::interaction)         m_wndptraHidden;
      //__pointer(::windowing::icon)                 m_picon;


      notify_icon();
      ~notify_icon() override;


      ::e_status add_hidden_window(::user::interaction * puserinteraction) override;

      //#ifdef WINDOWS_DESKTOP

      //virtual void remove_all_routes() override;

      //virtual bool DestroyWindow() override;

      //virtual void destroy_window() override;

      //virtual void PostNcDestroy() override;


      //#else

      //virtual bool DestroyWindow();

      //#endif

      ::e_status modify_icon(::windowing::icon * picon) override;

      ::e_status create_notify_icon(const ::id & id, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon) override;

      ::e_status destroy_notify_icon() override;

      //DECLARE_MESSAGE_HANDLER(_001OnNotifyIconMessage);
      //DECLARE_MESSAGE_HANDLER(_001OnDestroy);

      //void install_message_routing(::channel * pchannel) override;

      ::e_status step() override;

//#if defined(APPLE_IOS) || defined(WINDOWS_DESKTOP) || defined(ANDROID) || defined(_UWP)
//      virtual void notify_icon_play(const char * action);
//#else
//#if defined(LINUX)
//      virtual void notify_icon_play(const char * action);
//#else
//      virtual void notify_icon_play(const char * action) override;
//#endif
//#ifndef WINDOWS_DESKTOP
//      virtual int _get_notification_area_action_count() override;
//      virtual const char * _get_notification_area_action_name(int iIndex) override;
//      virtual const char * _get_notification_area_action_id(int iIndex) override;
//      virtual const char * _get_notification_area_action_label(int iIndex) override;
//      virtual const char * _get_notification_area_action_accelerator(int iIndex) override;
//      virtual const char * _get_notification_area_action_description(int iIndex) override;
//      virtual void call_notification_area_action(const char * pszId) override;
//#endif


//#endif


   };


} // namespace user


