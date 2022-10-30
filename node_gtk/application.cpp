#include "framework.h"
#include "application.h"
#include "acme/primitive/string/string.h"
#include "apex/platform/application.h"
#include "apex/platform/application_menu.h"
#include <glib.h>


void sn_start_context();


GtkWindow * g_pmainwindow = nullptr;


G_DEFINE_TYPE (NodeGtkApplication, node_gtk_application, GTK_TYPE_APPLICATION)


NodeGtkApplication * g_pnodegtkapplication = nullptr;


NodeGtkApplication * node_gtk_application_new (const char * pszAppName, const char * pszProgName)
{

   NodeGtkApplication * pnodegtkapplication;

   //g_set_application_name (pszAppName);

   pnodegtkapplication = (NodeGtkApplication *) g_object_new (node_gtk_application_get_type (),
                                          "application-atom", pszProgName,
                                          "flags", G_APPLICATION_FLAGS_NONE,
                                          "inactivity-timeout", 30000,
                                          "register-session", TRUE,
                                          nullptr);

   return pnodegtkapplication;

}


void node_gtk_application_application_menu_activate_callback(GSimpleAction *action, GVariant * parameter, gpointer user_data)
{

   ::apex::application * papp = (::apex::application *) user_data;

   const gchar * name = g_action_get_name (G_ACTION(action));

   string strName(name);

   if(strName.has_char())
   {

      papp->on_application_menu_action(strName);

   }

}



void node_gtk_application_set_application_menu(::application_menu * pappmenu, ::apex::application * papp)
{

   GApplication * pgapplication = G_APPLICATION(g_pnodegtkapplication);

   GMenu * pmenu = g_menu_new ();

   for(::index i = 0; i < pappmenu->get_count(); i++)
   {

      string strId = pappmenu->element_at(i).m_strId;

      string strName = pappmenu->element_at(i).m_strName;

      auto ptopic = g_simple_action_new (strId, NULL);

      g_signal_connect (
         papp,
         "activate",
         G_CALLBACK (node_gtk_application_application_menu_activate_callback),
         papp);

      g_action_map_add_action(G_ACTION_MAP(pgapplication), G_ACTION (ptopic));

      g_menu_append (pmenu, strName, strId);

   }

   gtk_application_set_app_menu (GTK_APPLICATION (pgapplication), G_MENU_MODEL (pmenu));

}



gboolean linux_start_system(gpointer data)
{

   GApplication * papp = g_application_get_default();

   ::apex::system * psystem = (::apex::system *) data;

   //psystem->m_XstrAppId = psystem->m_pmaindata->m_XstrAppId;

   //psystem->startup_command(psystem->m_pmaindata);

   //psystem->request(psystem->m_pcommand);

   return FALSE;

}


void node_gtk_application_activate(GApplication * application)
{

   //GCancellable * pc = g_cancellable_new();

   //GError * perror = nullptr;

   //g_application_register(application, pc, &perror);
   //new_window(application, nullptr);

#ifndef RASPBIAN

      throw ::exception(todo);

//   auto psystem = acmesystem()->m_papexsystem;
//
//   auto pnode = psystem->node();
//
//   auto pwindowing = pnode->windowing();
//
//   pwindowing->_libsn_start_context();

#endif

}


void node_gtk_application_run_mainloop(GApplication * pgapplication)
{

   NodeGtkApplication * pnodegtkapplication = (NodeGtkApplication *) pgapplication;

   GtkApplication * pgtkapplication = GTK_APPLICATION (pgapplication);

   G_APPLICATION_CLASS (node_gtk_application_parent_class)->run_mainloop(pgapplication);

}


void node_gtk_application_init (NodeGtkApplication * pnodegtkapplication)
{

}


void node_gtk_application_startup (GApplication *application)
{

   NodeGtkApplication * papexapplication = (NodeGtkApplication *) application;

   GtkApplication * app = GTK_APPLICATION (application);

   //if(System.m_bGtkApp)
   throw ::exception(todo);


   {

      G_APPLICATION_CLASS (node_gtk_application_parent_class)->startup (application);

      g_pmainwindow = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));

      gtk_application_add_window(app, g_pmainwindow);

   }

   //::apex::system * psystem = papexapplication->get_system();

   //psystem->m_XstrAppId = psystem->m_pmaindata->m_XstrAppId;

   //psystem->startup_command(psystem->m_pmaindata);

   //psystem->request(psystem->m_pcommand);


   g_application_hold(application);

}


void node_gtk_application_open(GApplication * application, GFile ** files, gint n_files, const gchar * hint)
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


void node_gtk_application_finalize (GObject *object)
{

   G_OBJECT_CLASS (node_gtk_application_parent_class)->finalize (object);

}


void node_gtk_application_shutdown(GApplication *application)
{

   NodeGtkApplication * papexapplication = (NodeGtkApplication *) application;

   /*

   if (papexapplication->timeout)
   {

      g_source_remove (papexapplication->timeout);

      papexapplication->timeout = 0;

   }

   */

   G_APPLICATION_CLASS (node_gtk_application_parent_class)->shutdown (application);

}


void node_gtk_application_class_init (NodeGtkApplicationClass * pclass)
{

   GApplicationClass *pappclass    = G_APPLICATION_CLASS (pclass);

   GObjectClass *pobjectclass      = G_OBJECT_CLASS (pclass);

   pappclass->startup              = node_gtk_application_startup;
   pappclass->shutdown             = node_gtk_application_shutdown;
   pappclass->activate             = node_gtk_application_activate;
   pappclass->open                 = node_gtk_application_open;

   pappclass->run_mainloop         = node_gtk_application_run_mainloop;

   pobjectclass->finalize          = node_gtk_application_finalize;

}


//void apex_application_run(const char * pszAppName, const char * pszProgName)
//{
//
//   g_papexapplication = apex_application_new(pszAppName, pszProgName);
//
//   if(g_papexapplication == nullptr)
//   {
//
//      output_debug_string("Failed to initialize GtkApplication (gtk_application_new return nullptr)");
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





gboolean gtk_quit_callback(gpointer data)
{

   gtk_main_quit();

   return FALSE;

}



namespace node_gtk
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


} // namespace node_gtk



