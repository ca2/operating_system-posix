//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/constant/id.h"
#include "acme/operating_system/ansi/pmutex_lock.h"
#include "acme/operating_system/parallelization.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/user/user/os_theme_colors.h"
#include "acme/user/user/theme_colors.h"
#include "apex/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "windowing_x11/windowing_x11.h"
#include "aura/windowing/windowing.h"


#include <gio/gio.h>
#include <gtk/gtk.h>
#include <glib.h>





namespace node_gtk3
{



//
//   GtkWidget *create_filechooser_dialog(GtkFileChooserAction action)
//   {
//
//      GtkWidget *pfilechooserdialog = nullptr;
//
//      switch (action)
//      {
//         case GTK_FILE_CHOOSER_ACTION_SAVE:
//            pfilechooserdialog = gtk_file_chooser_dialog_new("Save file", NULL, action,
//                                                             "Cancel", GTK_RESPONSE_CANCEL,
//                                                             "Save", GTK_RESPONSE_OK,
//                                                             NULL);
//            break;
//
//         case GTK_FILE_CHOOSER_ACTION_OPEN:
//            pfilechooserdialog = gtk_file_chooser_dialog_new("Open file", NULL, action,
//                                                             "Cancel", GTK_RESPONSE_CANCEL,
//                                                             "Open", GTK_RESPONSE_OK,
//                                                             NULL);
//            break;
//
//         case GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER:
//         case GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER:
//            break;
//      }
//
//      return pfilechooserdialog;
//
//   }


   void on_file_chooser_destroy_event(GtkWidget *w, GdkEvent * pevent, gpointer data)
   {

      auto *pdialog = (::file::file_dialog *) data;


   }


   void on_file_chooser_delete_event(GtkWidget *w, GdkEvent * pevent, gpointer data)
   {

      auto *pdialog = (::file::file_dialog *) data;

      ::release(pdialog);

   }


   void on_file_chooser_response(GtkDialog *pgtkdialog, int response_id, gpointer data)
   {

      if(response_id == GTK_RESPONSE_ACCEPT)
      {

         auto *pdialog = (::file::file_dialog *) data;

         auto path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pgtkdialog));

         pdialog->m_patha.add(path);

         pdialog->m_procedureResponse(pdialog);

      }

      gtk_widget_destroy(GTK_WIDGET(pgtkdialog));

   }


   void node::_node_file_dialog(::file::file_dialog *pdialog)
   {

      pdialog->increment_reference_count();

      user_post([pdialog]()
                        {

                           GtkWidget *widget;

//                           if (directory_chooser) {
//                              gtk_widget_destroy(directory_chooser);
//                              directory_chooser = NULL;
//                           }

                           widget = gtk_file_chooser_dialog_new("Open",
                                                                NULL,
                                                                GTK_FILE_CHOOSER_ACTION_OPEN,
                                                                "_Cancel", GTK_RESPONSE_CANCEL,
                                                                "_Open", GTK_RESPONSE_ACCEPT,
                                                                (void *) nullptr);

                           pdialog->m_posdata = widget;
                           //g_return_if_fail(NULL != widget);
                           //directory_chooser = widget;

                           //gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(widget), TRUE);

                           if(pdialog->m_filedialogfilter.has_element())
                           {

                              GtkFileFilter *filter = gtk_file_filter_new();

                              for (auto &filetype: pdialog->m_filedialogfilter)
                              {

                                 auto ppattern = filetype.m_strPatternList.c_str();

                                 gtk_file_filter_add_pattern(filter, ppattern);

                                 auto pname = filetype.m_strName.c_str();

                                 gtk_file_filter_set_name(filter, pname);

                              }

                              gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(widget),
                                                          filter);   /* Display only directories */

                           }

                           g_signal_connect(G_OBJECT(widget), "destroy-happening", G_CALLBACK(&on_file_chooser_destroy_event), pdialog);
                           g_signal_connect(G_OBJECT(widget), "delete-happening", G_CALLBACK(&on_file_chooser_delete_event), pdialog);
                           g_signal_connect(G_OBJECT(widget), "response", G_CALLBACK(&on_file_chooser_response), pdialog);

                           //if (NULL != current_directory) {
                           // gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(widget),
                           //current_directory);
                           //}


                           gtk_widget_show(widget);
//      GtkWidget *pfilechooserdialog;
//
//      pfilechooserdialog = create_filechooser_dialog(GTK_FILE_CHOOSER_ACTION_OPEN);
//
//      if (gtk_dialog_run(GTK_DIALOG(pfilechooserdialog)) == GTK_RESPONSE_OK)
//      {
//
//         ::file::path_array_base patha;
//
//         patha.add(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pfilechooserdialog)));
//
//         pdialog->m_function(patha);
//
//      }
//
//
//      gtk_di

                        });


   }


} // namespace node_gtk3



