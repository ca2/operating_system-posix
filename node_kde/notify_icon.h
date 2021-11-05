#pragma once


namespace node_kde
{


   class CLASS_DECL_AURA notify_icon :
      virtual public ::user::notify_icon,
      public QObject
   {
   public:


      __pointer(::aura::posix::appindicator)        m_pindicator;
      KStatusNotifierItem *                              m_pstatusnotifieritem;


      notify_icon();
      ~notify_icon() override;


      ::e_status add_hidden_window(::user::interaction * puserinteraction) override;

      ::e_status modify_icon(::windowing::icon * picon) override;

      ::e_status create_notify_icon(const ::id & id, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon) override;

      virtual ::e_status _create_status_notifier_item();

      ::e_status step() override;


   };


} // namespace node_kde



