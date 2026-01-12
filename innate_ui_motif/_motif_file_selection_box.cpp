//
// Created by camilo on 11/01/2026.
//
#include "framework.h"
#include "_motif_file_selection_box.h"


_motif_file_selection_box::_motif_file_selection_box()
{



}


_motif_file_selection_box::~_motif_file_selection_box()
{



}


//       pdialog->m_path = path;
//
//       pdialog->m_function(pdialog);
void _on_motif_file_selection_box_response(Widget widget, XtPointer client_data, XtPointer call_data)
{

   // // Get the file selection widget's current filename (path)
   // char *path = NULL;
   // XtVaGetValues(widget, XtNstring, &path, NULL);
   char *path = NULL;
   XmFileSelectionBoxCallbackStruct *cbs = (XmFileSelectionBoxCallbackStruct *)call_data;

   // Get the selected file or folder path
   XmStringGetLtoR(cbs->value, XmSTRING_DEFAULT_CHARSET, &path);

   if (path != NULL)
   {

      // Example of folder path
      printf("Selected path: %s\n", path);

      // Your logic to handle the path
      auto pdialog = (_motif_file_selection_box *)client_data;
      pdialog->on_chooser_response(path);


      // Free the path if needed
      XtFree(path);

   }

   // Close (destroy) the file selection dialog
   XtDestroyWidget(widget);

}

// Callback for handling the response of the FileSelection dialog
void _motif_file_selection_box::on_chooser_response(const_char_pointer pszPath)
{

   m_pdialogbase->on_chooser_response(pszPath);

}


// Function to open the file selection dialog
void _motif_file_selection_box::file_dialog_base(file::dialog_base *pdialogbase)
{

   m_pdialogbase = pdialogbase;

   // Create the file selection dialog (acts as a folder chooser)
   // Create a FileSelectionBox widget
   m_fileselectionbox = XmCreateFileSelectionBox(m_fileselectionbox, (char *) (const char *) "fileSelectionBox", NULL, 0);

   // Add callback for OK and Cancel actions
   XtAddCallback(
      m_fileselectionbox,
      XmNokCallback,
      _on_motif_file_selection_box_response,
      (XtPointer)this);

   XtAddCallback(
      m_fileselectionbox,
      XmNcancelCallback,
      _on_motif_file_selection_box_response,
      (XtPointer)this);

   // Set additional options like the file type mask to directories only
   XtVaSetValues(m_fileselectionbox, XmNfileTypeMask, XmFILE_DIRECTORY, NULL);

   // Realize the widget (show it on screen)
   XtManageChild(m_fileselectionbox);
}

// // Main function
// int main(int argc, char **argv)
// {
//
//    // XtAppContext app_context;
//    //
//    // topLevel = XtVaAppInitialize(&app_context, "XawFolderDialog", NULL, 0, &argc, argv, NULL, NULL);
//    //
//    //  // Example: Open the folder dialog with a custom function
//    // file::folder_dialog folderDialog;
//    // folderDialog.m_function = [](file::folder_dialog *pdialog) {
//    //     // Custom logic to handle folder selection (for example, print the path)
//    //     printf("Folder selected: %s\n", pdialog->m_path.c_str());
//    // };
//    //
//    // open_folder_dialog(&folderDialog);
//    //
//    // XtAppMainLoop(app_context);
//    //
//    // return 0;
//
// }



