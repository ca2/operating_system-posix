//
// Created by camilo on 20/01/2021. <3ThomasBS!!
//
#include "framework.h"
#include "clipboard_data.h"
//#include <gtk/gtk.h>

//
//void clipboard_targets_func(GtkClipboard *clipboard, GdkAtom *atoms, gint n_atoms, gpointer data)
//{
//
//   clipboard_data * pdata = (clipboard_data *) data;
//
//   GdkAtom target = gdk_atom_intern("x-special/gnome-copied-files", false);
//
//   pdata->m_nTargets = 0;
//
//   for(int i = 0; i < n_atoms; i++)
//   {
//
//      if(atoms[i] == target)
//      {
//
//         pdata->m_nTargets = 1;
//
//         break;
//
//      }
//
//   }
//
//   pdata->m_event.SetEvent();
//
//}
//
//void clipboard_image_received_func(GtkClipboard * clipboard, GdkPixbuf * pixbuf,	gpointer data)
//{
//
//   clipboard_data * pdata = (clipboard_data *) data;
//
//   int iBitsPerSample = gdk_pixbuf_get_bits_per_sample(pixbuf);
//
//   int iChannels = gdk_pixbuf_get_n_channels (pixbuf);
//
//   GdkColorspace space = gdk_pixbuf_get_colorspace (pixbuf);
//
//   bool bHasAlpha = gdk_pixbuf_get_has_alpha (pixbuf);
//
//   if(iBitsPerSample == 8
//      && (iChannels == 4 || iChannels == 3)
//      && (space == GDK_COLORSPACE_RGB)
//      && (bHasAlpha || !bHasAlpha))
//   {
//
//      int w = gdk_pixbuf_get_width(pixbuf);
//
//      int h = gdk_pixbuf_get_height(pixbuf);
//
//      color32_t * pcolorrefSrc = (color32_t *) gdk_pixbuf_read_pixels(pixbuf);
//
//      int iSrcScan = gdk_pixbuf_get_rowstride(pixbuf);
//
//      pdata->m_pimage->create({w, h});
//
//      if(pdata->m_pimage)
//      {
//
//         pdata->m_pimage->map();
//
//         ::copy_colorref_swap_red_blue(
//            pdata->m_pimage->colorref(),
//            pdata->m_pimage->width(),
//            pdata->m_pimage->height(),
//            pdata->m_pimage->scan_size(),
//            pcolorrefSrc,
//            iSrcScan);
//
//         if(!bHasAlpha)
//         {
//
//            pdata->m_pimage->fill_channel(255, ::color::channel_alpha);
//
//         }
//
//      }
//
//   }
//
//   pdata->m_event.SetEvent();
//
//}
//
//
//
//void clipboard_received_func(GtkClipboard * clipboard, GtkSelectionData * selection_data, gpointer data)
//{
//
//   clipboard_data * pdata = (clipboard_data *) data;
//
//   string str = (const char *)gtk_selection_data_get_data(selection_data);
//
//   string_array stra;
//
//   stra.add_lines(str);
//
//   if(stra.is_empty())
//   {
//
//      pdata->m_eclipboard = e_clipboard_error;
//
//      pdata->m_event.SetEvent();
//
//      return;
//
//   }
//
//   string strOp = stra[0];
//
//   if(strOp.compare_ci("copy") == 0)
//   {
//
//      pdata->m_eop = ::user::copydesk::op_copy;
//
//   }
//   else if(strOp.compare_ci("cut") == 0)
//   {
//
//      pdata->m_eop = ::user::copydesk::op_cut;
//
//   }
//   else
//   {
//
//      pdata->m_eclipboard = e_clipboard_error;
//
//      pdata->m_event.SetEvent();
//
//      return;
//
//   }
//
//   for(index i = 1; i < stra.get_size(); i++)
//   {
//
//      string strItem = stra[i];
//
//      ::str::begins_eat_ci(strItem, "file://");
//
//      pdata->m_patha.add(::file::path(strItem));
//
//   }
//
//   pdata->m_event.SetEvent();
//
//}
//
//
//void clipboard_get_func(GtkClipboard * clipboard, GtkSelectionData * selection_data, guint info, gpointer user_data)
//{
//
//   clipboard_data * pdata = (clipboard_data *) user_data;
//
//   //payload temp = _action + "\n" + _source; _action "cut"/"copy"
//
//   string strAction;
//
//   if(pdata->m_eop == ::user::copydesk::op_copy)
//   {
//
//      strAction = "copy";
//
//   }
//   else if(pdata->m_eop == ::user::copydesk::op_cut)
//   {
//
//      strAction = "cut";
//
//   }
//   else
//   {
//
//      pdata->m_eclipboard = e_clipboard_error;
//
//      return;
//
//   }
//
//   string str;
//
//   if(info == 1)
//   {
//
//      str = "# ";
//
//   }
//
//   str += strAction;
//
//   for(auto & path : pdata->m_patha)
//   {
//
//      str += "\n";
//
//      str += "file://" + path;
//
//   }
//
//   GdkAtom target = gtk_selection_data_get_target(selection_data);
//
//   gtk_selection_data_set(selection_data, target, 8, (const guchar *) (const char *) str, str.get_length());
//
//
//}
//
//
//void clipboard_clear_func(GtkClipboard * clipboard, gpointer user_data)
//{
//
//   clipboard_data * pdata = (clipboard_data *) user_data;
//
//   ::release(pdata);
//
//}
//
//void clipboard_text_request_callback(GtkClipboard *clipboard, const gchar * text, gpointer data)
//{
//
//   clipboard_data * pdata = (clipboard_data *) data;
//
//   if(text != nullptr)
//   {
//
//      pdata->m_str = text;
//
//   }
//
//   pdata->m_event.SetEvent();
//
//}
//
//
//gboolean clipboard_callback(gpointer data)
//{
//
//   clipboard_data * pdata = (clipboard_data *) data;
//
//   GtkClipboard* clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
//
//   if(pdata->m_eclipboard == e_clipboard_get_plain_text)
//   {
//
//
//      gtk_clipboard_request_text(clipboard, &clipboard_text_request_callback, pdata);
//
//   }
//   else if(pdata->m_eclipboard == e_clipboard_set_patha)
//   {
//
//      //_source = _fileCopy.Uri;
//      //     _action = _radioMove.Active ? "cut" : "copy";
//
//      GtkTargetEntry entrya[2];
//
//      entrya[0].target = (char *) "x-special/gnome-copied-files";
//      entrya[0].flags = 0;
//      entrya[0].info = 0;
//
//      entrya[1].target = (char *) "text/uri-list";
//      entrya[1].flags = 0;
//      entrya[1].info = 1;
//
//      gtk_clipboard_set_with_data(clipboard, entrya, 2, &clipboard_get_func, &clipboard_clear_func, pdata);
//
//      pdata->m_event.SetEvent();
//
//   }
//   else if(pdata->m_eclipboard == e_clipboard_get_patha)
//   {
//
//      GdkAtom target = gdk_atom_intern("x-special/gnome-copied-files", false);
//
//      gtk_clipboard_request_contents(clipboard, target, &clipboard_received_func, pdata);
//
//   }
//   else if(pdata->m_eclipboard == e_clipboard_get_file_target_count)
//   {
//
//      gtk_clipboard_request_targets(clipboard, &clipboard_targets_func, pdata);
//
//   }
//   else if(pdata->m_eclipboard == e_clipboard_get_image)
//   {
//
//      if(gtk_clipboard_wait_is_image_available(clipboard))
//      {
//
//         gtk_clipboard_request_image (clipboard, &clipboard_image_received_func, pdata);
//
//         return false;
//
//      }
//
//      clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY);
//
//      if(gtk_clipboard_wait_is_image_available(clipboard))
//      {
//
//         gtk_clipboard_request_image (clipboard, &clipboard_image_received_func, pdata);
//
//         return false;
//
//      }
//
//      clipboard = gtk_clipboard_get(GDK_SELECTION_SECONDARY);
//
//      if(gtk_clipboard_wait_is_image_available(clipboard))
//      {
//
//         gtk_clipboard_request_image (clipboard, &clipboard_image_received_func, pdata);
//
//         return false;
//
//      }
//
//      pdata->m_event.SetEvent();
//
////      GdkPixbuf * pixbuf = gtk_clipboard_wait_for_image(clipboard);
////
////      if(pixbuf == nullptr)
////      {
////
////         clipboard = gtk_clipboard_get(GDK_SELECTION_PRIMARY);
////
////         pixbuf = gtk_clipboard_wait_for_image(clipboard);
////
////      }
////
////      if(pixbuf != nullptr)
////      {
////
////         clipboard_data * pdata = (clipboard_data *) data;
////
////         int iBitsPerSample = gdk_pixbuf_get_bits_per_sample(pixbuf);
////
////         int iChannels = gdk_pixbuf_get_n_channels (pixbuf);
////
////         GdkColorspace space = gdk_pixbuf_get_colorspace (pixbuf);
////
////         bool bHasAlpha = gdk_pixbuf_get_has_alpha (pixbuf);
////
////         if(iBitsPerSample == 8
////            && (iChannels == 4 || iChannels == 3)
////            && (space == GDK_COLORSPACE_RGB)
////            && (bHasAlpha || !bHasAlpha))
////         {
////
////            int w = gdk_pixbuf_get_width(pixbuf);
////
////            int h = gdk_pixbuf_get_height(pixbuf);
////
////            color32_t * pcolorrefSrc = (color32_t *) gdk_pixbuf_read_pixels(pixbuf);
////
////            int iSrcScan = gdk_pixbuf_get_rowstride(pixbuf);
////
////            if(pdata->m_pimage = create_image({w,  h)})
////            {
////
////               ::copy_colorref(
////                  pdata->m_pimage->width(),
////                  pdata->m_pimage->height(),
////                  pdata->m_pimage->m_pcolorref,
////                  pdata->m_pimage->m_iScan,
////                  pcolorrefSrc,
////                  iSrcScan);
////
////               if(!bHasAlpha)
////               {
////
////                  pdata->m_pimage->fill_channel(255, ::color::channel_alpha);
////
////               }
////
////            }
////
////         }
////
////      }
////
////      pdata->m_event.SetEvent();
//
//
//   }
//   else
//   {
//
//      __throw(invalid_argument_exception());
//
//   }
//
//   return false;
//
//}
