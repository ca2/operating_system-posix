#include "framework.h"
#include "g_application.h"

#include "apex/platform/application.h"
#include "apex/platform/application_menu.h"
//#include <glib.h>


void sn_start_context();

//
////GtkWindow * g_pmainwindow = nullptr;
//
//
//G_DEFINE_TYPE (NodeGApplication, node_g_application, G_TYPE_APPLICATION)
//
//
//NodeGApplication * g_pnodegapplication = nullptr;
//
//
//NodeGApplication * node_g_application_new (const char * pszAppName, const char * pszProgName)
//{
//
//   NodeGApplication * pnodegapplication;
//
//   //g_set_application_name (scopedstrAppName);
//
//   pnodegapplication = (NodeGApplication *) g_object_new(node_g_application_get_type (),
//                                          "application-atom", pszProgName,
//
//                                          #if GLIB_CHECK_VERSION(2, 74, 0)
//                                            "flags", G_APPLICATION_DEFAULT_FLAGS,
//                                          #else
//                                            "flags", G_APPLICATION_FLAGS_NONE,
//                                          #endif
//                                          "inactivity-timeout", 30000,
//                                          "register-session", TRUE,
//                                          nullptr);
//
//   return pnodegapplication;
//
//}


void node_g_application_application_menu_activate_callback(GSimpleAction *action, GVariant * parameter, gpointer p)
{

   auto * pcallback = (::application_menu_callback *) p;

   const gchar * name = g_action_get_name (G_ACTION(action));

   string strName(name);

   if(strName.has_character())
   {

      pcallback->on_application_menu_action(strName);

   }

}


GMenu * g_menu_from_application_menu(GApplication * pgapplication, ::application_menu * papplicationmenu, ::application_menu_callback * pcallback)
{

   GMenu * pmenu = g_menu_new();

   for(::collection::index i = 0; i < papplicationmenu->get_count(); i++)
   {

      auto pitem = papplicationmenu->element_at(i);

      string strName = pitem->m_strName;

      if(pitem->is_popup())
      {

         auto pmenuSub = g_menu_from_application_menu(pgapplication, pitem, pcallback);

         g_menu_append_submenu(pmenu, strName, G_MENU_MODEL(pmenuSub));

      }
      else
      {

         string strId = pitem->id();

         auto psimpleaction = g_simple_action_new (strId, NULL);

         g_signal_connect (
            pcallback,
            "activate",
            G_CALLBACK (node_g_application_application_menu_activate_callback),
            pcallback);

         g_action_map_add_action(G_ACTION_MAP(pgapplication), G_ACTION (psimpleaction));

         g_menu_append (pmenu, strName, strId);

      }

   }

   return pmenu;

}


//void node_gtk_application_set_application_menu(GApplication * pgapplication, ::application_menu * papplicationmenu, ::application_menu_callback * pcallback)
//{
//
//   GMenu * pmenu = g_menu_from_application_menu (pgapplication, papplicationmenu, pcallback);
//
//   g_application_set_app_menu (pgapplication, G_MENU_MODEL (pmenu));
//
//}


gboolean linux_start_system(gpointer data)
{

   GApplication * papp = g_application_get_default();

   ::apex::system * psystem = (::apex::system *) data;

   //psystem->m_XstrAppId = psystem->m_pmaindata->m_XstrAppId;

   //psystem->startup_command(psystem->m_pmaindata);

   //psystem->request(psystem->m_pcommand);

   return FALSE;

}


void node_g_application_activate(GApplication * application)
{

   //GCancellable * pc = g_cancellable_new();

   //GError * pgerror = nullptr;

   //g_application_register(application, pc, &perror);
   //new_window(application, nullptr);

#ifndef RASPBERRYPIOS

      throw ::exception(todo);

//   auto psystem = system();
//
//   auto pnode = psystem->node();
//
//   auto pwindowing = pnode->windowing();
//
//   pwindowing->_libsnx_start_context();

#endif

}


void node_g_application_run_mainloop(GApplication * pgapplication)
{

   //NodeGtkApplication * pnodegtkapplication = (NodeGtkApplication *) pgapplication;

   //GtkApplication * pgtkapplication = GTK_APPLICATION (pgapplication);

   G_APPLICATION_CLASS (pgapplication)->run_mainloop(pgapplication);

}


void node_g_application_init (GApplication * pgapplication)
{

}


void node_g_application_startup (GApplication *application)
{

//   NodeGtkApplication * papexapplication = (NodeGtkApplication *) application;
//
//   GtkApplication * app = GTK_APPLICATION (application);
//
//   //if(System.m_bGtkApp)
//   throw ::exception(todo);
//
//
//   {
//
//      G_APPLICATION_CLASS (node_gtk_application_parent_class)->startup (application);
//
//      g_pmainwindow = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
//
//      gtk_application_add_window(app, g_pmainwindow);
//
//   }

   //::apex::system * psystem = papexapplication->system();

   //psystem->m_XstrAppId = psystem->m_pmaindata->m_XstrAppId;

   //psystem->startup_command(psystem->m_pmaindata);

   //psystem->request(psystem->m_pcommand);


   g_application_hold(application);

}


void node_g_application_open(GApplication * application, GFile ** files, gint n_files, const gchar * hint)
{

//   gint i;
//
//   for (i = 0; i < n_files; i++)
//   {
//
//      new_window (application, files[i]);
//
//   }

}


void node_g_application_finalize (GObject *object)
{

   //G_OBJECT_CLASS (node_g_application_parent_class)->finalize (object);

}


void node_g_application_shutdown(GApplication *application)
{

   //NodeGtkApplication * papexapplication = (NodeGtkApplication *) application;

   /*

   if (papexapplication->timeout)
   {

      g_source_remove (papexapplication->timeout);

      papexapplication->timeout = 0;

   }

   */

   //G_APPLICATION_CLASS (node_gtk_application_parent_class)->shutdown (application);

}


void node_g_application_class_init (GApplicationClass * pclass)
{

   GApplicationClass *pappclass    = G_APPLICATION_CLASS (pclass);

   GObjectClass *pobjectclass      = G_OBJECT_CLASS (pclass);

   pappclass->startup              = node_g_application_startup;
   pappclass->shutdown             = node_g_application_shutdown;
   pappclass->activate             = node_g_application_activate;
   pappclass->open                 = node_g_application_open;

   pappclass->run_mainloop         = node_g_application_run_mainloop;

   pobjectclass->finalize          = node_g_application_finalize;

}


//void apex_application_run(const char * pszAppName, const char * pszProgName)
//{
//
//   g_papexapplication = apex_application_new(scopedstrAppName, pszProgName);
//
//   if(g_papexapplication == nullptr)
//   {
//
//      informationf("Failed to initialize GtkApplication (gtk_application_new return nullptr)");
//
//      return;
//
//   }
//
//   int status = g_application_run (G_APPLICATION (g_papexapplication), 0, nullptr);
//
//   g_object_unref(g_papexapplication);
//
//   g_papexapplication = nullptr;
//
//}








namespace node_gtk3
{

//
//   void node::node_post_quit()
//   {
//
//      //auto idle_source = g_idle_source_new();
//
//      //g_source_set_callback(idle_source, &gtk_quit_callback, nullptr, nullptr);
//
//      //g_source_attach(idle_source, g_main_context_default());
//
//
//   }


} // namespace node_gtk3



