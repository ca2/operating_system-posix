#pragma once


//#if defined (__APPLE__)
//#include "notify_icon_mm_bridge.h"
//#endif


//#ifdef LINUX
//#include "apex/user/user/notify_icon_bridge.h"
//#include "apex/plat
//namespace freebsd { class appindicator; }
//#endif
#include "aura/user/user/notify_icon.h"
#include "aura_posix/appindicator.h"


namespace node_gtk3
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


      //unsigned int                                             m_uiId;
      //bool                                              m_bCreated;
      //string                                            m_strId;
//#ifdef WINDOWS_DESKTOP
//      NOTIFYICONDATA m_nid;
//#elif defined(LINUX)
      ::pointer<::aura_posix::appindicator>       m_pindicator;
//#endif
      //::pointer<::user::notify_icon_listener>     m_plistener;
      //pointer_array < ::user::interaction >         m_wndptraHidden;
      //::pointer<::windowing::icon>                m_picon;


      notify_icon();
      ~notify_icon() override;


      void add_hidden_window(::user::interaction * puserinteraction) override;

      //#ifdef WINDOWS_DESKTOP

      //virtual void remove_all_routes() override;

      //virtual bool DestroyWindow() override;

      //virtual void destroy_window() override;

      //virtual void PostNcDestroy() override;


      //#else

      //virtual bool DestroyWindow();

      //#endif

      void initialize(::particle * pparticle) override;

      void modify_icon(::windowing::icon * picon) override;

      void create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon) override;

      void destroy_notify_icon() override;

      //DECLARE_MESSAGE_HANDLER(_001OnNotifyIconMessage);
      //DECLARE_MESSAGE_HANDLER(_001OnDestroy);

      //void install_message_routing(::channel * pchannel) override;

      bool notify_icon_step() override;

//#if defined(APPLE_IOS) || defined(WINDOWS_DESKTOP) || defined(__ANDROID__) || defined(UNIVERSAL_WINDOWS)
//      virtual void notify_icon_play(const_char_pointer action);
//#else
//#if defined(LINUX)
//      virtual void notify_icon_play(const_char_pointer action);
//#else
//      virtual void notify_icon_play(const_char_pointer action) override;
//#endif
//#ifndef WINDOWS_DESKTOP
//      virtual int _get_notification_area_action_count() override;
//      virtual const_char_pointer _get_notification_area_action_name(int iIndex) override;
//      virtual const_char_pointer _get_notification_area_action_id(int iIndex) override;
//      virtual const_char_pointer _get_notification_area_action_label(int iIndex) override;
//      virtual const_char_pointer _get_notification_area_action_accelerator(int iIndex) override;
//      virtual const_char_pointer _get_notification_area_action_description(int iIndex) override;
//      virtual void call_notification_area_action(const_char_pointer pszId) override;
//#endif


//#endif


   };


} // namespace node_gtk3


