//
// Created by camilo on 20/01/2021. ThomasBS!!
//
#include "framework.h"
#include "acme/platform/system.h"
#include "apex/user/notify_icon_bridge.h"
//int uname(struct utsname *buf);
//#ifndef RASPBIAN
//#ifndef MANJARO
// Manjaro libappindicator-gtk3
//#include <libappindicator3-0.1/libappindicator/app-indicator.h>
#ifdef AYATANA_APPINDICATOR
#include <libayatana-appindicator/app-indicator.h>
#else
#include <libappindicator/app-indicator.h>
#endif
//#include <libappindicator-0.1/libappindicator/app-indicator.h>
//#else // MANJARO
//#include <libappindicator-0.1/libappindicator/app-indicator.h>
//#endif
//#endif



#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

//void g_safe_free(void * pfree);
//{
//
//   if(pfree == nullptr)
//   {
//
//      return;
//
//   }
//
//   ::g_free(pfree);
//
//}

#include "aura_posix/user_notify_icon_bridge.h"


static void ___extra_action(GtkAction * action, void * data)
{

   ::user_notify_icon_bridge * pi = (::user_notify_icon_bridge *) data;

   pi->call_notification_area_action(gtk_action_get_stock_id(action));

}


extern "C"
{


   static void __extra_action(GtkAction * action, gpointer data)
   {

      ___extra_action(action, data);

   }


} // extern "C"


#include "appindicator.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"


namespace node_gnome
{


   appindicator::appindicator()
   {


   }


   appindicator::~appindicator()
   {

      //close();

   }


   bool appindicator::create(const char * pszId, const char * pszIcon, const char * pszFolder, user_notify_icon_bridge * pbridge)
   {

      m_pindicator = app_indicator_new_with_path(pszId, pszIcon, APP_INDICATOR_CATEGORY_APPLICATION_STATUS, pszFolder);

      if(m_pindicator == nullptr)
      {

         return false;

      }

      if(!init(pbridge))
      {

         close();

         return false;

      }

      return true;

   }


   bool appindicator::init(user_notify_icon_bridge * pbridge)
   {

      int iCount = pbridge->_get_notification_area_action_count();

      GtkWidget *  indicator_menu = nullptr;

      if(iCount > 0)
      {


         GError * error = nullptr;

         GtkActionGroup * action_group = gtk_action_group_new ("AppActions");

         if(action_group != nullptr)
         {

            GtkActionEntry * entries = memory_new GtkActionEntry[pbridge->_get_notification_area_action_count()];

            string strInfo;

            strInfo += "<ui>";

            strInfo += "  <popup name='IndicatorPopup'>";

            int iEntry = 0;

            for(int i = 0; i < iCount; i++)
            {

               int iIndex = i;

               const char * pszName = pbridge->_get_notification_area_action_name(iIndex);
               const char * pszId = pbridge->_get_notification_area_action_id(iIndex);
               const char * pszLabel = pbridge->_get_notification_area_action_label(iIndex);
               const char * pszAccelerator = pbridge->_get_notification_area_action_accelerator(iIndex);
               const char * pszDescription = pbridge->_get_notification_area_action_description(iIndex);

               memset(&entries[iEntry], 0, sizeof(GtkActionEntry));

               if(strcasecmp(pszName, "separator") == 0)
               {

                  strInfo += "<separator/>\n";

               }
               else
               {

                  entries[iEntry].name = g_strdup(pszLabel);

                  strInfo += "    <menuitem action='";
                  strInfo += pszLabel;
                  strInfo += "' />";

                  entries[iEntry].stock_id = g_strdup(pszId);

                  entries[iEntry].label = g_strdup(pszName);

                  //entries[iEntry].accelerator = g_strdup(pszAccelerator);

                  entries[iEntry].accelerator = nullptr;

                  entries[iEntry].tooltip = g_strdup(pszDescription);

                  entries[iEntry].callback = G_CALLBACK (__extra_action);

                  iEntry++;

               }

            }

            strInfo += "  </popup>";
            strInfo += "</ui>";

            gtk_action_group_add_actions (action_group, entries, iEntry, pbridge);

            GtkUIManager * uim = gtk_ui_manager_new ();

            bool bOk = false;

            gchar * ui_info = (gchar *) g_strdup(strInfo);

            if(uim != nullptr)
            {

               gtk_ui_manager_insert_action_group (uim, action_group, 0);

               bOk = gtk_ui_manager_add_ui_from_string (uim, ui_info, -1, &error) != FALSE;

               if(!bOk)
               {

                  g_message ("Failed to build menus: %s\n", error->message);

                  g_error_free (error);

                  error = nullptr;

               }

            }

            for(int i = 0; i < iEntry; i++)
            {

               ::node_gtk::g_safe_free((void *) entries[i].name);
               ::node_gtk::g_safe_free((void *) entries[i].stock_id);
               ::node_gtk::g_safe_free((void *) entries[i].label);
               ::node_gtk::g_safe_free((void *) entries[i].accelerator);
               ::node_gtk::g_safe_free((void *) entries[i].tooltip);

            }

            delete [] entries;

            ::node_gtk::g_safe_free(ui_info);

            if(bOk)
            {

               indicator_menu = gtk_ui_manager_get_widget (uim, "/ui/IndicatorPopup");

               app_indicator_set_menu(m_pindicator, GTK_MENU (indicator_menu));

            }

         }

      }

      app_indicator_set_status(m_pindicator, APP_INDICATOR_STATUS_ACTIVE);

      return true;

   }


   void appindicator::close()
   {


      if(m_pindicator == NULL)
      {

         return;

      }

      auto pindicator = m_pindicator;

      acmesystem()->windowing_post([pindicator]()
               {

                  app_indicator_set_status(pindicator, APP_INDICATOR_STATUS_PASSIVE);

               });

      m_pindicator = NULL;

   }


} // namespace node_gnome



