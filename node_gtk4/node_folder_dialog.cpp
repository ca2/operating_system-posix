//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"
#include "acme/constant/id.h"
#include "acme/operating_system/ansi/pmutex_lock.h"
#include "acme/operating_system/parallelization.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
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

namespace node_gtk4
{


//
//   void on_folder_chooser_destroy_event(GtkWidget *w, GdkEvent * pevent, gpointer data)
//   {
//
//      auto *pdialog = (::file::folder_dialog *) data;
//
//
//   }
//
//
//   void on_folder_chooser_delete_event(GtkWidget *w, GdkEvent * pevent, gpointer data)
//   {
//
//      auto *pdialog = (::file::folder_dialog *) data;
//
//      ::release(pdialog);
//
//   }


//   void on_folder_chooser_response(GtkDialog *pgtkdialog, int response_id, gpointer data)
//   {
//
//      if(response_id == GTK_RESPONSE_ACCEPT)
//      {
//
//         auto *pdialog = (::file::folder_dialog *) data;
//
//
//
//         auto pfile = gtk_file_chooser_get_file(GTK_FILE_CHOOSER(pgtkdialog));
//
//         auto g_file_get_path(pfile);
//
//         pdialog->m_path = path;
//
//         pdialog->m_function(pdialog);
//
//      }
//
//      gtk_widget_destroy(GTK_WIDGET(pgtkdialog));
//
//   }


   void node::_node_folder_dialog(::file::folder_dialog *pdialog)
   {

      pdialog->increment_reference_count();

      user_post([pdialog]()
                        {

                           //GtkWidget *widget;

//                           if (directory_chooser) {
//                              gtk_widget_destroy(directory_chooser);
//                              directory_chooser = NULL;
//                           }




                   //auto active_window = gtk_application_get_active_window(GTK_APPLICATION(self->data->application));

                   auto pgtkfiledialog = gtk_file_dialog_new();


                   pdialog->m_posdata = pgtkfiledialog;

                   //gtk_file_dialog_set_title(dialog, _("Import APO Preset File"));
                   //gtk_file_dialog_set_accept_label(dialog, _("Open"));

                   //GListStore* filters = g_list_store_new(GTK_TYPE_FILE_FILTER);

                   //auto* filter = gtk_file_filter_new();

                   //gtk_file_filter_add_pattern(filter, "*.txt");
                   //gtk_file_filter_set_name(filter, _("APO Presets"));

                   //g_list_store_append(filters, filter);

                   //g_object_unref(filter);

                   //gtk_file_dialog_set_filters(dialog, G_LIST_MODEL(filters));

                   //g_object_unref(filters);
                   //pdialog
                   gtk_file_dialog_select_folder(
                           pgtkfiledialog, nullptr, nullptr,
                           [](GObject* source_object, GAsyncResult* result, gpointer user_data)
                           {

                              ::pointer < ::file::folder_dialog > pdialog(transfer_t{}, (::file::folder_dialog *) user_data);

                              auto pgtkfiledialog = GTK_FILE_DIALOG(source_object);

                              auto pgfile = gtk_file_dialog_select_folder_finish(pgtkfiledialog, result, nullptr);

                              if (pgfile != nullptr)
                              {

                                 auto path = g_file_get_path(pgfile);

                                 pdialog->m_path = path;

                                 pdialog->m_function(pdialog);

                                 g_free(path);

                                 g_object_unref(pgfile);

                              }

                           },
                           pdialog);

//                           widget = gtk_file_chooser_dialog_new("Open",
//                                                                NULL,
//                                                               pdialog->m_bCanCreateFolders ? GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER
//                                                               : GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
//                                                                "_Cancel", GTK_RESPONSE_CANCEL,
//                                                                "_Open", GTK_RESPONSE_ACCEPT,
//                                                                (void *) nullptr);
//
//                           pdialog->m_posdata = widget;
//                           //g_return_if_fail(NULL != widget);
//                           //directory_chooser = widget;
//
//                           //gtk_file_chooser_set_local_only(GTK_FILE_CHOOSER(widget), TRUE);
//
////                           if(pdialog->m_filetypes.has_element())
////                           {
////
////                              GtkFileFilter *filter = gtk_file_filter_new();
////
////                              for (auto &filetype: pdialog->m_filetypes)
////                              {
////
////                                 auto ppattern = filetype.element1().c_str();
////
////                                 gtk_file_filter_add_pattern(filter, ppattern);
////
////                                 auto pname = filetype.element2().c_str();
////
////                                 gtk_file_filter_set_name(filter, pname);
////
////                              }
////
////                              gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(widget),
////                                                          filter);   /* Display only directories */
////
////                           }
//
//                           //if (NULL != current_directory) {
//                           // gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(widget),
//                           //current_directory);
//                           //}
//
//                           g_signal_connect(G_OBJECT(widget), "destroy-event", G_CALLBACK(&on_folder_chooser_destroy_event), pdialog);
//                           g_signal_connect(G_OBJECT(widget), "delete-event", G_CALLBACK(&on_folder_chooser_delete_event), pdialog);
//                           g_signal_connect(G_OBJECT(widget), "response", G_CALLBACK(&on_folder_chooser_response), pdialog);

                           //gtk_widget_show(widget);
//      GtkWidget *pfilechooserdialog;
//
//      pfilechooserdialog = create_filechooser_dialog(GTK_FILE_CHOOSER_ACTION_OPEN);
//
//      if (gtk_dialog_run(GTK_DIALOG(pfilechooserdialog)) == GTK_RESPONSE_OK)
//      {
//
//         ::file::path_array patha;
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


} // namespace node_gtk4



