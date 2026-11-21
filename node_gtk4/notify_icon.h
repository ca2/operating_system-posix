#pragma once


#include "aura/user/user/notify_icon.h"
#include <gio/gio.h>
#include <vector>
#include <unordered_map>
#include <string>


namespace node_gtk4
{


   class CLASS_DECL_NODE_GTK4 notify_icon :
      virtual public ::user::notify_icon
   {
   public:


      struct menu_entry
      {
         gint32                  m_iId = 0;
         bool                    m_bSeparator = false;
         bool                    m_bSubmenu = false;
         std::string             m_strLabel;
         ::atom                  m_atomCommand;
         std::vector<gint32>     m_iaChildren;
      };


      GDBusConnection *                      m_pdbusconnection = nullptr;
      GDBusNodeInfo *                        m_pnodeinfoSni = nullptr;
      GDBusNodeInfo *                        m_pnodeinfoMenu = nullptr;
      guint                                  m_uOwnerId = 0;
      guint                                  m_uWatcherId = 0;
      guint                                  m_uSniRegistrationId = 0;
      guint                                  m_uMenuRegistrationId = 0;
      guint32                                m_uMenuRevision = 1;

      std::string                            m_strBusName;
      std::string                            m_strSniId;
      std::string                            m_strTitle;
      std::string                            m_strIconName;
      std::string                            m_strIconThemePath;

      int                                    m_iIconWidth = 0;
      int                                    m_iIconHeight = 0;
      std::vector<unsigned char>             m_baIconArgb;

      std::unordered_map<gint32, menu_entry> m_mapMenuEntries;


      notify_icon();
      ~notify_icon() override;


      void initialize(::particle * pparticle) override;

      void create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon) override;

      void modify_icon(::windowing::icon * picon) override;

      void add_hidden_window(::user::interaction * puserinteraction) override;

      void destroy_notify_icon() override;

      bool notify_icon_step() override;

      void _load_icon_pixmap(const ::file::path & pathIcon);
      void _rebuild_menu_snapshot();
      gint32 _add_menu_recursive(::application_menu * pmenu, gint32 & iNextId);
      GVariant * _build_menu_layout_variant(gint32 iId, gint32 iRecursionDepth);
      GVariant * _build_item_properties_variant(const menu_entry & entry);
      void _register_with_watcher();
      void _unregister_dbus();
      void _dispatch_command(const ::atom & atom);


   };


} // namespace node_gtk4
