#include "platform.h"
#include "notify_icon.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/application_menu.h"
#include "acme/platform/system.h"
#include "acme/prototype/string/str.h"
#include "apex/platform/application.h"
#include "aura/windowing/icon.h"
#include <atomic>
#include <unistd.h>


namespace node_gtk4
{


   static std::atomic<unsigned int> g_uNotifyIconCounter{0};


   static const gchar g_szStatusNotifierItemXml[] =
      "<node>"
      "  <interface name='org.kde.StatusNotifierItem'>"
      "    <property name='Category' type='s' access='read'/>"
      "    <property name='Id' type='s' access='read'/>"
      "    <property name='Title' type='s' access='read'/>"
      "    <property name='Status' type='s' access='read'/>"
      "    <property name='WindowId' type='u' access='read'/>"
      "    <property name='IconName' type='s' access='read'/>"
      "    <property name='IconThemePath' type='s' access='read'/>"
      "    <property name='IconPixmap' type='a(iiay)' access='read'/>"
      "    <property name='OverlayIconName' type='s' access='read'/>"
      "    <property name='OverlayIconPixmap' type='a(iiay)' access='read'/>"
      "    <property name='AttentionIconName' type='s' access='read'/>"
      "    <property name='AttentionIconPixmap' type='a(iiay)' access='read'/>"
      "    <property name='AttentionMovieName' type='s' access='read'/>"
      "    <property name='ToolTip' type='(sa(iiay)ss)' access='read'/>"
      "    <property name='ItemIsMenu' type='b' access='read'/>"
      "    <property name='Menu' type='o' access='read'/>"
      "    <method name='ContextMenu'>"
      "      <arg name='x' type='i' direction='in'/>"
      "      <arg name='y' type='i' direction='in'/>"
      "    </method>"
      "    <method name='Activate'>"
      "      <arg name='x' type='i' direction='in'/>"
      "      <arg name='y' type='i' direction='in'/>"
      "    </method>"
      "    <method name='SecondaryActivate'>"
      "      <arg name='x' type='i' direction='in'/>"
      "      <arg name='y' type='i' direction='in'/>"
      "    </method>"
      "    <method name='Scroll'>"
      "      <arg name='delta' type='i' direction='in'/>"
      "      <arg name='orientation' type='s' direction='in'/>"
      "    </method>"
      "    <signal name='NewTitle'/>"
      "    <signal name='NewIcon'/>"
      "    <signal name='NewAttentionIcon'/>"
      "    <signal name='NewOverlayIcon'/>"
      "    <signal name='NewToolTip'/>"
      "    <signal name='NewStatus'>"
      "      <arg name='status' type='s'/>"
      "    </signal>"
      "  </interface>"
      "</node>";


   static const gchar g_szDBusMenuXml[] =
      "<node>"
      "  <interface name='com.canonical.dbusmenu'>"
      "    <property name='Version' type='u' access='read'/>"
      "    <property name='TextDirection' type='s' access='read'/>"
      "    <property name='Status' type='s' access='read'/>"
      "    <property name='IconThemePath' type='as' access='read'/>"
      "    <method name='GetLayout'>"
      "      <arg name='parentId' type='i' direction='in'/>"
      "      <arg name='recursionDepth' type='i' direction='in'/>"
      "      <arg name='propertyNames' type='as' direction='in'/>"
      "      <arg name='revision' type='u' direction='out'/>"
      "      <arg name='layout' type='(ia{sv}av)' direction='out'/>"
      "    </method>"
      "    <method name='GetGroupProperties'>"
      "      <arg name='ids' type='ai' direction='in'/>"
      "      <arg name='propertyNames' type='as' direction='in'/>"
      "      <arg name='properties' type='a(ia{sv})' direction='out'/>"
      "    </method>"
      "    <method name='GetProperty'>"
      "      <arg name='id' type='i' direction='in'/>"
      "      <arg name='name' type='s' direction='in'/>"
      "      <arg name='value' type='v' direction='out'/>"
      "    </method>"
      "    <method name='Event'>"
      "      <arg name='id' type='i' direction='in'/>"
      "      <arg name='eventId' type='s' direction='in'/>"
      "      <arg name='data' type='v' direction='in'/>"
      "      <arg name='timestamp' type='u' direction='in'/>"
      "    </method>"
      "    <method name='EventGroup'>"
      "      <arg name='events' type='a(isvu)' direction='in'/>"
      "      <arg name='idErrors' type='ai' direction='out'/>"
      "    </method>"
      "    <method name='AboutToShow'>"
      "      <arg name='id' type='i' direction='in'/>"
      "      <arg name='needUpdate' type='b' direction='out'/>"
      "    </method>"
      "    <method name='AboutToShowGroup'>"
      "      <arg name='ids' type='ai' direction='in'/>"
      "      <arg name='updatesNeeded' type='ai' direction='out'/>"
      "      <arg name='idErrors' type='ai' direction='out'/>"
      "    </method>"
      "    <signal name='ItemsPropertiesUpdated'>"
      "      <arg name='updatedProps' type='a(ia{sv})'/>"
      "      <arg name='removedProps' type='a(ias)'/>"
      "    </signal>"
      "    <signal name='LayoutUpdated'>"
      "      <arg name='revision' type='u'/>"
      "      <arg name='parent' type='i'/>"
      "    </signal>"
      "    <signal name='ItemActivationRequested'>"
      "      <arg name='id' type='i'/>"
      "      <arg name='timestamp' type='u'/>"
      "    </signal>"
      "  </interface>"
      "</node>";


   static GVariant * build_empty_pixmap_array()
   {

      GVariantBuilder builder;

      g_variant_builder_init(&builder, G_VARIANT_TYPE("a(iiay)"));

      return g_variant_builder_end(&builder);

   }


   static void sni_handle_method_call(
      GDBusConnection * connection,
      const gchar * sender,
      const gchar * object_path,
      const gchar * interface_name,
      const gchar * method_name,
      GVariant * parameters,
      GDBusMethodInvocation * invocation,
      gpointer user_data)
   {

      auto * picon = static_cast<notify_icon *>(user_data);

      if (g_strcmp0(method_name, "Activate") == 0
         || g_strcmp0(method_name, "SecondaryActivate") == 0)
      {

         picon->_dispatch_command("notify_icon_topic");

         g_dbus_method_invocation_return_value(invocation, nullptr);

         return;

      }

      if (g_strcmp0(method_name, "ContextMenu") == 0
         || g_strcmp0(method_name, "Scroll") == 0)
      {

         g_dbus_method_invocation_return_value(invocation, nullptr);

         return;

      }

      g_dbus_method_invocation_return_dbus_error(
         invocation,
         "org.freedesktop.DBus.Error.UnknownMethod",
         "Unknown method");

   }


   static GVariant * sni_handle_get_property(
      GDBusConnection * connection,
      const gchar * sender,
      const gchar * object_path,
      const gchar * interface_name,
      const gchar * property_name,
      GError ** error,
      gpointer user_data)
   {

      auto * picon = static_cast<notify_icon *>(user_data);

      if (g_strcmp0(property_name, "Category") == 0)
      {

         return g_variant_new_string("ApplicationStatus");

      }

      if (g_strcmp0(property_name, "Id") == 0)
      {

         return g_variant_new_string(picon->m_strSniId.c_str());

      }

      if (g_strcmp0(property_name, "Title") == 0)
      {

         return g_variant_new_string(picon->m_strTitle.c_str());

      }

      if (g_strcmp0(property_name, "Status") == 0)
      {

         return g_variant_new_string("Active");

      }

      if (g_strcmp0(property_name, "WindowId") == 0)
      {

         return g_variant_new_uint32(0);

      }

      if (g_strcmp0(property_name, "IconName") == 0)
      {

         return g_variant_new_string(picon->m_strIconName.c_str());

      }

      if (g_strcmp0(property_name, "IconThemePath") == 0)
      {

         return g_variant_new_string(picon->m_strIconThemePath.c_str());

      }

      if (g_strcmp0(property_name, "IconPixmap") == 0)
      {

         GVariantBuilder builder;

         g_variant_builder_init(&builder, G_VARIANT_TYPE("a(iiay)"));

         if (picon->m_iIconWidth > 0 && picon->m_iIconHeight > 0 && !picon->m_baIconArgb.empty())
         {

            GVariant * pbytes = g_variant_new_fixed_array(
               G_VARIANT_TYPE_BYTE,
               picon->m_baIconArgb.data(),
               picon->m_baIconArgb.size(),
               sizeof(unsigned char));

            g_variant_builder_add(&builder, "(ii@ay)", picon->m_iIconWidth, picon->m_iIconHeight, pbytes);

         }

         return g_variant_builder_end(&builder);

      }

      if (g_strcmp0(property_name, "OverlayIconName") == 0
         || g_strcmp0(property_name, "AttentionIconName") == 0
         || g_strcmp0(property_name, "AttentionMovieName") == 0)
      {

         return g_variant_new_string("");

      }

      if (g_strcmp0(property_name, "OverlayIconPixmap") == 0
         || g_strcmp0(property_name, "AttentionIconPixmap") == 0)
      {

         return build_empty_pixmap_array();

      }

      if (g_strcmp0(property_name, "ToolTip") == 0)
      {

         return g_variant_new(
            "(s@a(iiay)ss)",
            "",
            build_empty_pixmap_array(),
            picon->m_strTitle.c_str(),
            "");

      }

      if (g_strcmp0(property_name, "ItemIsMenu") == 0)
      {

         return g_variant_new_boolean(FALSE);

      }

      if (g_strcmp0(property_name, "Menu") == 0)
      {

         return g_variant_new_object_path("/MenuBar");

      }

      return nullptr;

   }


   static void menu_handle_method_call(
      GDBusConnection * connection,
      const gchar * sender,
      const gchar * object_path,
      const gchar * interface_name,
      const gchar * method_name,
      GVariant * parameters,
      GDBusMethodInvocation * invocation,
      gpointer user_data)
   {

      auto * picon = static_cast<notify_icon *>(user_data);

      if (g_strcmp0(method_name, "GetLayout") == 0)
      {

         gint32 iParentId = 0;
         gint32 iRecursionDepth = -1;
         gchar ** ppPropertyNames = nullptr;

         g_variant_get(parameters, "(ii^as)", &iParentId, &iRecursionDepth, &ppPropertyNames);
         g_strfreev(ppPropertyNames);

         picon->_rebuild_menu_snapshot();

         GVariant * playout = picon->_build_menu_layout_variant(iParentId, iRecursionDepth);

         g_dbus_method_invocation_return_value(
            invocation,
            g_variant_new("(u@(ia{sv}av))", picon->m_uMenuRevision, playout));

         return;

      }

      if (g_strcmp0(method_name, "GetGroupProperties") == 0)
      {

         GVariantIter * piterIds = nullptr;
         gchar ** ppPropertyNames = nullptr;

         g_variant_get(parameters, "(ai^as)", &piterIds, &ppPropertyNames);
         g_strfreev(ppPropertyNames);

         GVariantBuilder builder;

         g_variant_builder_init(&builder, G_VARIANT_TYPE("a(ia{sv})"));

         gint32 iId = 0;

         while (g_variant_iter_loop(piterIds, "i", &iId))
         {

            auto it = picon->m_mapMenuEntries.find(iId);

            if (it != picon->m_mapMenuEntries.end())
            {

               g_variant_builder_add(&builder, "(i@a{sv})", iId, picon->_build_item_properties_variant(it->second));

            }

         }

         g_variant_iter_free(piterIds);

         g_dbus_method_invocation_return_value(
            invocation,
            g_variant_new("(@a(ia{sv}))", g_variant_builder_end(&builder)));

         return;

      }

      if (g_strcmp0(method_name, "GetProperty") == 0)
      {

         gint32 iId = 0;
         const gchar * pszName = nullptr;

         g_variant_get(parameters, "(i&s)", &iId, &pszName);

         auto it = picon->m_mapMenuEntries.find(iId);

         if (it != picon->m_mapMenuEntries.end())
         {

            if (g_strcmp0(pszName, "label") == 0)
            {

               g_dbus_method_invocation_return_value(
                  invocation,
                  g_variant_new("(v)", g_variant_new_string(it->second.m_strLabel.c_str())));

               return;

            }
            else if (g_strcmp0(pszName, "type") == 0)
            {

               g_dbus_method_invocation_return_value(
                  invocation,
                  g_variant_new("(v)", g_variant_new_string(it->second.m_bSeparator ? "separator" : "standard")));

               return;

            }
            else if (g_strcmp0(pszName, "visible") == 0 || g_strcmp0(pszName, "enabled") == 0)
            {

               g_dbus_method_invocation_return_value(
                  invocation,
                  g_variant_new("(v)", g_variant_new_boolean(TRUE)));

               return;

            }

         }

         g_dbus_method_invocation_return_value(
            invocation,
            g_variant_new("(v)", g_variant_new_string("")));

         return;

      }

      if (g_strcmp0(method_name, "Event") == 0)
      {

         gint32 iId = 0;
         const gchar * pszEventId = nullptr;
         GVariant * pdata = nullptr;
         guint32 uTimestamp = 0;

         g_variant_get(parameters, "(i&svu)", &iId, &pszEventId, &pdata, &uTimestamp);

         if (pdata)
         {

            g_variant_unref(pdata);

         }

         if (g_strcmp0(pszEventId, "clicked") == 0)
         {

            auto it = picon->m_mapMenuEntries.find(iId);

            if (it != picon->m_mapMenuEntries.end() && !it->second.m_bSeparator && !it->second.m_bSubmenu)
            {

               picon->_dispatch_command(it->second.m_atomCommand);

            }

         }

         g_dbus_method_invocation_return_value(invocation, nullptr);

         return;

      }

      if (g_strcmp0(method_name, "EventGroup") == 0)
      {

         GVariantIter * piter = nullptr;

         g_variant_get(parameters, "(a(isvu))", &piter);

         gint32 iId = 0;
         const gchar * pszEventId = nullptr;
         GVariant * pdata = nullptr;
         guint32 uTimestamp = 0;

         while (g_variant_iter_loop(piter, "(i&svu)", &iId, &pszEventId, &pdata, &uTimestamp))
         {

            if (g_strcmp0(pszEventId, "clicked") == 0)
            {

               auto it = picon->m_mapMenuEntries.find(iId);

               if (it != picon->m_mapMenuEntries.end() && !it->second.m_bSeparator && !it->second.m_bSubmenu)
               {

                  picon->_dispatch_command(it->second.m_atomCommand);

               }

            }

         }

         g_variant_iter_free(piter);

         GVariantBuilder builderErrors;
         g_variant_builder_init(&builderErrors, G_VARIANT_TYPE("ai"));

         g_dbus_method_invocation_return_value(
            invocation,
            g_variant_new("(@ai)", g_variant_builder_end(&builderErrors)));

         return;

      }

      if (g_strcmp0(method_name, "AboutToShow") == 0)
      {

         gint32 iId = 0;

         g_variant_get(parameters, "(i)", &iId);

         if (iId == 0)
         {

            picon->_rebuild_menu_snapshot();

         }

         g_dbus_method_invocation_return_value(invocation, g_variant_new("(b)", FALSE));

         return;

      }

      if (g_strcmp0(method_name, "AboutToShowGroup") == 0)
      {

         GVariantBuilder builderUpdates;
         GVariantBuilder builderErrors;

         g_variant_builder_init(&builderUpdates, G_VARIANT_TYPE("ai"));
         g_variant_builder_init(&builderErrors, G_VARIANT_TYPE("ai"));

         g_dbus_method_invocation_return_value(
            invocation,
            g_variant_new("(@ai@ai)", g_variant_builder_end(&builderUpdates), g_variant_builder_end(&builderErrors)));

         return;

      }

      g_dbus_method_invocation_return_dbus_error(
         invocation,
         "org.freedesktop.DBus.Error.UnknownMethod",
         "Unknown method");

   }


   static GVariant * menu_handle_get_property(
      GDBusConnection * connection,
      const gchar * sender,
      const gchar * object_path,
      const gchar * interface_name,
      const gchar * property_name,
      GError ** error,
      gpointer user_data)
   {

      auto * picon = static_cast<notify_icon *>(user_data);

      if (g_strcmp0(property_name, "Version") == 0)
      {

         return g_variant_new_uint32(3);

      }

      if (g_strcmp0(property_name, "TextDirection") == 0)
      {

         return g_variant_new_string("ltr");

      }

      if (g_strcmp0(property_name, "Status") == 0)
      {

         return g_variant_new_string("normal");

      }

      if (g_strcmp0(property_name, "IconThemePath") == 0)
      {

         GVariantBuilder builder;

         g_variant_builder_init(&builder, G_VARIANT_TYPE("as"));

         if (!picon->m_strIconThemePath.empty())
         {

            g_variant_builder_add(&builder, "s", picon->m_strIconThemePath.c_str());

         }

         return g_variant_builder_end(&builder);

      }

      return nullptr;

   }


   static const GDBusInterfaceVTable g_sniVTable =
   {
      sni_handle_method_call,
      sni_handle_get_property,
      nullptr
   };


   static const GDBusInterfaceVTable g_menuVTable =
   {
      menu_handle_method_call,
      menu_handle_get_property,
      nullptr
   };


   static void on_bus_name_acquired(GDBusConnection * connection, const gchar * name, gpointer user_data)
   {

      auto * picon = static_cast<notify_icon *>(user_data);

      picon->_register_with_watcher();

   }


   static void on_watcher_appeared(GDBusConnection * connection, const gchar * name, const gchar * name_owner, gpointer user_data)
   {

      auto * picon = static_cast<notify_icon *>(user_data);

      picon->_register_with_watcher();

   }


   notify_icon::notify_icon()
   {

      m_bCreated = false;

   }


   notify_icon::~notify_icon()
   {

      destroy_notify_icon();

   }


   void notify_icon::initialize(::particle * pparticle)
   {

      ::user::notify_icon::initialize(pparticle);

   }


   void notify_icon::_load_icon_pixmap(const ::file::path & pathIcon)
   {

      m_iIconWidth = 0;
      m_iIconHeight = 0;
      m_baIconArgb.clear();

      GError * perror = nullptr;

      GdkPixbuf * ppixbuf = gdk_pixbuf_new_from_file(pathIcon.c_str(), &perror);

      if (perror)
      {

         g_error_free(perror);

      }

      if (!ppixbuf)
      {

         return;

      }

      int iWidth = gdk_pixbuf_get_width(ppixbuf);
      int iHeight = gdk_pixbuf_get_height(ppixbuf);
      int iChannels = gdk_pixbuf_get_n_channels(ppixbuf);
      int iRowstride = gdk_pixbuf_get_rowstride(ppixbuf);
      const guchar * pPixels = gdk_pixbuf_get_pixels(ppixbuf);

      if (iWidth > 0 && iHeight > 0 && (iChannels == 3 || iChannels == 4) && pPixels)
      {

         m_iIconWidth = iWidth;
         m_iIconHeight = iHeight;
         m_baIconArgb.resize(static_cast<size_t>(iWidth) * static_cast<size_t>(iHeight) * 4);

         unsigned char * pDest = m_baIconArgb.data();

         for (int y = 0; y < iHeight; y++)
         {

            const guchar * pRow = pPixels + y * iRowstride;

            for (int x = 0; x < iWidth; x++)
            {

               const guchar * pSrc = pRow + x * iChannels;

               unsigned char r = pSrc[0];
               unsigned char g = pSrc[1];
               unsigned char b = pSrc[2];
               unsigned char a = (iChannels == 4) ? pSrc[3] : 255;

               // StatusNotifierItem IconPixmap uses ARGB32 in network byte order.
               *pDest++ = a;
               *pDest++ = r;
               *pDest++ = g;
               *pDest++ = b;

            }

         }

      }

      g_object_unref(ppixbuf);

   }


   gint32 notify_icon::_add_menu_recursive(::application_menu * pmenu, gint32 & iNextId)
   {

      gint32 iMyId = iNextId++;

      menu_entry entry;
      entry.m_iId = iMyId;

      if (iMyId == 0)
      {

         entry.m_bSubmenu = true;

      }
      else if (pmenu->is_separator())
      {

         entry.m_bSeparator = true;

      }
      else
      {

         entry.m_strLabel = pmenu->m_strName.c_str();
         entry.m_bSubmenu = pmenu->is_popup();
         entry.m_atomCommand = pmenu->m_atomMenu;

      }

      if (iMyId == 0 || entry.m_bSubmenu)
      {

         auto iCount = pmenu->get_count();

         for (::collection::index i = 0; i < iCount; i++)
         {

            auto pchild = pmenu->element_at(i);

            if (pchild)
            {

               gint32 iChildId = _add_menu_recursive(pchild, iNextId);

               entry.m_iaChildren.push_back(iChildId);

            }

         }

      }

      m_mapMenuEntries[iMyId] = std::move(entry);

      return iMyId;

   }


   void notify_icon::_rebuild_menu_snapshot()
   {

      m_mapMenuEntries.clear();

      auto pmenu = this->menu();

      if (!pmenu)
      {

         menu_entry root;
         root.m_iId = 0;
         root.m_bSubmenu = true;
         m_mapMenuEntries[0] = std::move(root);

         return;

      }

      gint32 iNextId = 0;

      _add_menu_recursive(pmenu, iNextId);

   }


   GVariant * notify_icon::_build_item_properties_variant(const menu_entry & entry)
   {

      GVariantBuilder builder;

      g_variant_builder_init(&builder, G_VARIANT_TYPE("a{sv}"));

      if (entry.m_iId == 0)
      {

         g_variant_builder_add(&builder, "{sv}", "children-display", g_variant_new_string("submenu"));

         return g_variant_builder_end(&builder);

      }

      if (entry.m_bSeparator)
      {

         g_variant_builder_add(&builder, "{sv}", "type", g_variant_new_string("separator"));
         g_variant_builder_add(&builder, "{sv}", "visible", g_variant_new_boolean(TRUE));

      }
      else
      {

         g_variant_builder_add(&builder, "{sv}", "label", g_variant_new_string(entry.m_strLabel.c_str()));
         g_variant_builder_add(&builder, "{sv}", "enabled", g_variant_new_boolean(TRUE));
         g_variant_builder_add(&builder, "{sv}", "visible", g_variant_new_boolean(TRUE));

         if (entry.m_bSubmenu)
         {

            g_variant_builder_add(&builder, "{sv}", "children-display", g_variant_new_string("submenu"));

         }

      }

      return g_variant_builder_end(&builder);

   }


   GVariant * notify_icon::_build_menu_layout_variant(gint32 iId, gint32 iRecursionDepth)
   {

      auto it = m_mapMenuEntries.find(iId);

      GVariantBuilder builderChildren;
      g_variant_builder_init(&builderChildren, G_VARIANT_TYPE("av"));

      if (it == m_mapMenuEntries.end())
      {

         GVariantBuilder builderEmptyProps;
         g_variant_builder_init(&builderEmptyProps, G_VARIANT_TYPE("a{sv}"));

         return g_variant_new("(i@a{sv}@av)", iId, g_variant_builder_end(&builderEmptyProps), g_variant_builder_end(&builderChildren));

      }

      const auto & entry = it->second;

      if (iRecursionDepth != 0)
      {

         gint32 iChildDepth = (iRecursionDepth > 0) ? (iRecursionDepth - 1) : -1;

         for (gint32 iChildId : entry.m_iaChildren)
         {

            GVariant * pchild = _build_menu_layout_variant(iChildId, iChildDepth);

            g_variant_builder_add(&builderChildren, "v", pchild);

         }

      }

      return g_variant_new("(i@a{sv}@av)", entry.m_iId, _build_item_properties_variant(entry), g_variant_builder_end(&builderChildren));

   }


   void notify_icon::_register_with_watcher()
   {

      if (!m_pdbusconnection || m_strBusName.empty())
      {

         return;

      }

      g_dbus_connection_call(
         m_pdbusconnection,
         "org.kde.StatusNotifierWatcher",
         "/StatusNotifierWatcher",
         "org.kde.StatusNotifierWatcher",
         "RegisterStatusNotifierItem",
         g_variant_new("(s)", m_strBusName.c_str()),
         nullptr,
         G_DBUS_CALL_FLAGS_NO_AUTO_START,
         2000,
         nullptr,
         nullptr,
         nullptr);

   }


   void notify_icon::_unregister_dbus()
   {

      if (m_uWatcherId)
      {

         g_bus_unwatch_name(m_uWatcherId);
         m_uWatcherId = 0;

      }

      if (m_pdbusconnection)
      {

         if (m_uSniRegistrationId)
         {

            g_dbus_connection_unregister_object(m_pdbusconnection, m_uSniRegistrationId);
            m_uSniRegistrationId = 0;

         }

         if (m_uMenuRegistrationId)
         {

            g_dbus_connection_unregister_object(m_pdbusconnection, m_uMenuRegistrationId);
            m_uMenuRegistrationId = 0;

         }

      }

      if (m_uOwnerId)
      {

         g_bus_unown_name(m_uOwnerId);
         m_uOwnerId = 0;

      }

      if (m_pnodeinfoSni)
      {

         g_dbus_node_info_unref(m_pnodeinfoSni);
         m_pnodeinfoSni = nullptr;

      }

      if (m_pnodeinfoMenu)
      {

         g_dbus_node_info_unref(m_pnodeinfoMenu);
         m_pnodeinfoMenu = nullptr;

      }

      if (m_pdbusconnection)
      {

         g_object_unref(m_pdbusconnection);
         m_pdbusconnection = nullptr;

      }

   }


   void notify_icon::_dispatch_command(const ::atom & atom)
   {

      if (atom.is_empty())
      {

         return;

      }

      auto atomCopy = atom;

      if (m_puserinteractionNotify)
      {

         m_puserinteractionNotify->post([this, atomCopy]()
         {

            handle_command(atomCopy, nullptr);

         });

      }
      else
      {

         handle_command(atomCopy, nullptr);

      }

   }


   void notify_icon::create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon)
   {

      if (m_bCreated)
      {

         return;

      }

      information() << "node_gtk4::notify_icon::create_notify_icon";

      m_strId = atom;

      id() = atom;

      m_piconCurrent = picon;

      m_puserinteractionNotify = puserinteractionNotify;

      string strAppId = m_piconCurrent->get_tray_icon_name();

      string strId(strAppId);

      string strMatterRoot = ::str::token(strId, "/");

      if (strMatterRoot.is_empty())
      {

         strMatterRoot = "app";

      }

      auto pSlash = strAppId.find('/');

      string strAppName = pSlash ? string(strAppId.substr(pSlash + 1)) : strAppId;

      ::file::path pathFolder = directory_system()->roaming() / strMatterRoot / "matter/icon/128";

      ::file::path pathRoamingIcon = pathFolder / (strAppName + ".png");

      try
      {

         get_app()->file()->copy(pathRoamingIcon, "matter://main/icon-128.png");

      }
      catch (...)
      {

      }

      m_strSniId = strAppId.c_str();
      m_strTitle = get_app()->application_title().c_str();

      if (m_strTitle.empty())
      {

         m_strTitle = strAppName.c_str();

      }

      m_strIconName = strAppName.c_str();
      m_strIconThemePath = pathFolder.c_str();

      _load_icon_pixmap(pathRoamingIcon);

      _rebuild_menu_snapshot();

      unsigned int uCounter = ++g_uNotifyIconCounter;

      m_strBusName = "org.kde.StatusNotifierItem-" + std::to_string(static_cast<long>(getpid())) + "-" + std::to_string(uCounter);

      bool bRegistered = false;

      main_send([this, &bRegistered]()
      {

         GError * perror = nullptr;

         m_pdbusconnection = g_bus_get_sync(G_BUS_TYPE_SESSION, nullptr, &perror);

         if (perror)
         {

            warning() << "node_gtk4::notify_icon: failed to connect to session bus: " << perror->message;
            g_error_free(perror);
            perror = nullptr;

         }

         if (!m_pdbusconnection)
         {

            return;

         }

         m_pnodeinfoSni = g_dbus_node_info_new_for_xml(g_szStatusNotifierItemXml, &perror);

         if (perror)
         {

            warning() << "node_gtk4::notify_icon: SNI XML error: " << perror->message;
            g_error_free(perror);
            perror = nullptr;

         }

         m_pnodeinfoMenu = g_dbus_node_info_new_for_xml(g_szDBusMenuXml, &perror);

         if (perror)
         {

            warning() << "node_gtk4::notify_icon: DBusMenu XML error: " << perror->message;
            g_error_free(perror);
            perror = nullptr;

         }

         if (!m_pnodeinfoSni || !m_pnodeinfoMenu)
         {

            _unregister_dbus();

            return;

         }

         m_uSniRegistrationId = g_dbus_connection_register_object(
            m_pdbusconnection,
            "/StatusNotifierItem",
            m_pnodeinfoSni->interfaces[0],
            &g_sniVTable,
            this,
            nullptr,
            &perror);

         if (perror)
         {

            warning() << "node_gtk4::notify_icon: failed to register /StatusNotifierItem: " << perror->message;
            g_error_free(perror);
            perror = nullptr;

         }

         m_uMenuRegistrationId = g_dbus_connection_register_object(
            m_pdbusconnection,
            "/MenuBar",
            m_pnodeinfoMenu->interfaces[0],
            &g_menuVTable,
            this,
            nullptr,
            &perror);

         if (perror)
         {

            warning() << "node_gtk4::notify_icon: failed to register /MenuBar: " << perror->message;
            g_error_free(perror);
            perror = nullptr;

         }

         if (!m_uSniRegistrationId || !m_uMenuRegistrationId)
         {

            _unregister_dbus();

            return;

         }

         m_uOwnerId = g_bus_own_name_on_connection(
            m_pdbusconnection,
            m_strBusName.c_str(),
            G_BUS_NAME_OWNER_FLAGS_NONE,
            on_bus_name_acquired,
            nullptr,
            this,
            nullptr);

         m_uWatcherId = g_bus_watch_name_on_connection(
            m_pdbusconnection,
            "org.kde.StatusNotifierWatcher",
            G_BUS_NAME_WATCHER_FLAGS_NONE,
            on_watcher_appeared,
            nullptr,
            this,
            nullptr);

         bRegistered = true;

      });

      if (!bRegistered)
      {

         throw ::exception(error_failed, "Failed to register GTK4 StatusNotifierItem");

      }

      m_bCreated = true;

   }


   void notify_icon::modify_icon(::windowing::icon * picon)
   {

      if (!m_bCreated)
      {

         throw ::exception(error_wrong_state);

      }

      m_piconCurrent = picon;

   }


   void notify_icon::add_hidden_window(::user::interaction * puserinteraction)
   {

      ::user::notify_icon::add_hidden_window(puserinteraction);

   }


   void notify_icon::destroy_notify_icon()
   {

      if (!m_bCreated && !m_pdbusconnection)
      {

         return;

      }

      m_bCreated = false;

      main_send([this]()
      {

         _unregister_dbus();

      });

   }


   bool notify_icon::notify_icon_step()
   {

      if (m_bCreated && m_pdbusconnection)
      {

         main_post([this]()
         {

            if (!m_bCreated || !m_pdbusconnection)
            {

               return;

            }

            _rebuild_menu_snapshot();
            m_uMenuRevision++;

            g_dbus_connection_emit_signal(
               m_pdbusconnection,
               nullptr,
               "/MenuBar",
               "com.canonical.dbusmenu",
               "LayoutUpdated",
               g_variant_new("(ui)", m_uMenuRevision, 0),
               nullptr);

         });

      }

      return true;

   }


} // namespace node_gtk4
