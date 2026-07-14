// Created by camilo on 2026-07-14 03:19 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
#include "copydesk.h"
#include "acme/windowing/windowing.h"
#include "aura_posix/clipboard_data.h"
#include "aura/graphics/image/context.h"
#include "aura/platform/system.h"
#include "aura/platform/node.h"

#include <gtk/gtk.h>
#include <gio/gio.h>
#include <cstring>


namespace
{


   constexpr const char * g_pszGnomeCopiedFiles = "x-special/gnome-copied-files";
   constexpr const char * g_pszUriList = "text/uri-list";
   constexpr gsize g_uMaximumClipboardFilePayload = 16 * 1024 * 1024;
   constexpr gsize g_uClipboardReadBlockSize = 64 * 1024;


   GdkClipboard * gtk4_standard_clipboard()
   {

      auto pdisplay = gdk_display_get_default();

      if(!pdisplay)
      {

         return nullptr;

      }

      return gdk_display_get_clipboard(pdisplay);

   }


   GdkClipboard * gtk4_primary_clipboard()
   {

      auto pdisplay = gdk_display_get_default();

      if(!pdisplay)
      {

         return nullptr;

      }

      return gdk_display_get_primary_clipboard(pdisplay);

   }


   bool gtk4_formats_have_plain_text(const GdkContentFormats * pformats)
   {

      if(!pformats)
      {

         return false;

      }

      if(gdk_content_formats_contain_gtype(pformats, G_TYPE_STRING))
      {

         return true;

      }

      gsize cMimeTypes = 0;

      auto ppszMimeTypes = gdk_content_formats_get_mime_types(pformats, &cMimeTypes);

      for(gsize i = 0; i < cMimeTypes; ++i)
      {

         if(ppszMimeTypes[i] && g_str_has_prefix(ppszMimeTypes[i], "text/plain"))
         {

            return true;

         }

      }

      return false;

   }


   bool gtk4_formats_have_file_list(const GdkContentFormats * pformats)
   {

      if(!pformats)
      {

         return false;

      }

      return
         gdk_content_formats_contain_mime_type(pformats, g_pszGnomeCopiedFiles)
         ||
         gdk_content_formats_contain_mime_type(pformats, g_pszUriList);

   }


   bool gtk4_formats_have_image(const GdkContentFormats * pformats)
   {

      if(!pformats)
      {

         return false;

      }

      if(gdk_content_formats_contain_gtype(pformats, GDK_TYPE_TEXTURE))
      {

         return true;

      }

      gsize cMimeTypes = 0;

      auto ppszMimeTypes = gdk_content_formats_get_mime_types(pformats, &cMimeTypes);

      for(gsize i = 0; i < cMimeTypes; ++i)
      {

         if(ppszMimeTypes[i] && g_str_has_prefix(ppszMimeTypes[i], "image/"))
         {

            return true;

         }

      }

      return false;

   }


   void gtk4_clipboard_request_complete(clipboard_data * pdata, bool bSucceeded)
   {

      if(!bSucceeded)
      {

         pdata->m_eclipboard = e_clipboard_error;

      }

      pdata->m_happening.set_happening();

      // Balances the explicit increment_reference_count() performed before
      // starting the GTK asynchronous request.
      //::release(pdata);

   }


   GdkContentProvider * gtk4_content_provider_for_string(
      const char * pszMimeType,
      const ::string & str)
   {

      auto pbytes = g_bytes_new(str.c_str(), (gsize)str.length());

      if(!pbytes)
      {

         return nullptr;

      }

      auto pprovider = gdk_content_provider_new_for_bytes(pszMimeType, pbytes);

      g_bytes_unref(pbytes);

      return pprovider;

   }


   bool gtk4_build_file_payloads(
      const ::file::path_array_base & patha,
      ::user::copydesk::enum_op eop,
      ::string & strGnomeCopiedFiles,
      ::string & strUriList)
   {

      if(patha.is_empty())
      {

         return false;

      }

      if(eop == ::user::copydesk::e_op_copy)
      {

         strGnomeCopiedFiles = "copy";

      }
      else if(eop == ::user::copydesk::e_op_cut)
      {

         strGnomeCopiedFiles = "cut";

      }
      else
      {

         return false;

      }

      for(auto & path : patha)
      {

         GError * perror = nullptr;

         auto pszUri = g_filename_to_uri(path.c_str(), nullptr, &perror);

         if(!pszUri)
         {

            if(perror)
            {

               g_error_free(perror);

            }

            return false;

         }

         strGnomeCopiedFiles += "\n";
         strGnomeCopiedFiles += pszUri;

         strUriList += pszUri;
         strUriList += "\r\n";

         g_free(pszUri);

      }

      return true;

   }


   bool gtk4_add_file_uri(
      ::file::path_array_base & patha,
      const char * pszUri)
   {

      if(!pszUri || !*pszUri)
      {

         return false;

      }

      GError * perror = nullptr;

      auto pszFilename = g_filename_from_uri(pszUri, nullptr, &perror);

      if(!pszFilename)
      {

         if(perror)
         {

            g_error_free(perror);

         }

         return false;

      }

      patha.add(::file::path(pszFilename));

      g_free(pszFilename);

      return true;

   }


   bool gtk4_parse_uri_list(
      clipboard_data * pdata,
      const char * pszUriList)
   {

      if(!pszUriList)
      {

         return false;

      }

      auto ppszUris = g_uri_list_extract_uris(pszUriList);

      if(!ppszUris)
      {

         return false;

      }

      bool bAddedAny = false;

      for(auto ppszUri = ppszUris; *ppszUri; ++ppszUri)
      {

         if(gtk4_add_file_uri(pdata->m_patha, *ppszUri))
         {

            bAddedAny = true;

         }

      }

      g_strfreev(ppszUris);

      return bAddedAny;

   }


   bool gtk4_parse_file_payload(
      clipboard_data * pdata,
      const char * pszMimeType,
      const guint8 * pData,
      gsize uSize)
   {

      if(!pszMimeType || !pData)
      {

         return false;

      }

      auto pszPayload = g_strndup((const char *)pData, uSize);

      if(!pszPayload)
      {

         return false;

      }

      pdata->m_patha.clear();
      pdata->m_eop = ::user::copydesk::e_op_copy;

      bool bSucceeded = false;

      if(g_strcmp0(pszMimeType, g_pszGnomeCopiedFiles) == 0)
      {

         auto pszLineEnd = std::strpbrk(pszPayload, "\r\n");

         if(pszLineEnd)
         {

            *pszLineEnd = '\0';

            auto pszUriList = pszLineEnd + 1;

            while(*pszUriList == '\r' || *pszUriList == '\n')
            {

               ++pszUriList;

            }

            if(g_ascii_strcasecmp(pszPayload, "copy") == 0)
            {

               pdata->m_eop = ::user::copydesk::e_op_copy;
               bSucceeded = gtk4_parse_uri_list(pdata, pszUriList);

            }
            else if(g_ascii_strcasecmp(pszPayload, "cut") == 0)
            {

               pdata->m_eop = ::user::copydesk::e_op_cut;
               bSucceeded = gtk4_parse_uri_list(pdata, pszUriList);

            }

         }

      }
      else if(g_strcmp0(pszMimeType, g_pszUriList) == 0)
      {

         // text/uri-list has no standard copy-versus-cut indication.
         pdata->m_eop = ::user::copydesk::e_op_copy;
         bSucceeded = gtk4_parse_uri_list(pdata, pszPayload);

      }

      g_free(pszPayload);

      return bSucceeded;

   }


   struct gtk4_clipboard_stream_request
   {

      ::pointer < clipboard_data >       m_pdata;
      GInputStream *         m_pstream;
      GByteArray *           m_pbytearray;
      char *                 m_pszMimeType;

   };


   void gtk4_clipboard_stream_request_destroy(
      gtk4_clipboard_stream_request * prequest,
      bool bSucceeded)
   {

      if(prequest->m_pstream)
      {

         g_object_unref(prequest->m_pstream);

      }

      if(prequest->m_pbytearray)
      {

         g_byte_array_unref(prequest->m_pbytearray);

      }

      g_free(prequest->m_pszMimeType);

      auto pdata = prequest->m_pdata;

      g_free(prequest);

      gtk4_clipboard_request_complete(pdata, bSucceeded);

   }


   void gtk4_clipboard_file_stream_read(
      GObject * psource,
      GAsyncResult * presult,
      gpointer puserData)
   {

      auto prequest = (gtk4_clipboard_stream_request *)puserData;

      GError * perror = nullptr;

      auto pbytes = g_input_stream_read_bytes_finish(
         G_INPUT_STREAM(psource),
         presult,
         &perror);

      if(!pbytes)
      {

         if(perror)
         {

            g_error_free(perror);

         }

         gtk4_clipboard_stream_request_destroy(prequest, false);

         return;

      }

      gsize uSize = 0;

      auto pData = (const guint8 *)g_bytes_get_data(pbytes, &uSize);

      if(uSize == 0)
      {

         g_bytes_unref(pbytes);

         auto bSucceeded = gtk4_parse_file_payload(
            prequest->m_pdata,
            prequest->m_pszMimeType,
            prequest->m_pbytearray->data,
            prequest->m_pbytearray->len);

         gtk4_clipboard_stream_request_destroy(prequest, bSucceeded);

         return;

      }

      if(prequest->m_pbytearray->len + uSize > g_uMaximumClipboardFilePayload)
      {

         g_bytes_unref(pbytes);

         gtk4_clipboard_stream_request_destroy(prequest, false);

         return;

      }

      g_byte_array_append(prequest->m_pbytearray, pData, (guint)uSize);

      g_bytes_unref(pbytes);

      g_input_stream_read_bytes_async(
         prequest->m_pstream,
         g_uClipboardReadBlockSize,
         G_PRIORITY_DEFAULT,
         nullptr,
         &gtk4_clipboard_file_stream_read,
         prequest);

   }


   void gtk4_clipboard_file_read_ready(
      GObject * psource,
      GAsyncResult * presult,
      gpointer puserData)
   {

      auto pdata = (clipboard_data *)puserData;

      GError * perror = nullptr;
      const char * pszMimeType = nullptr;

      auto pstream = gdk_clipboard_read_finish(
         GDK_CLIPBOARD(psource),
         presult,
         &pszMimeType,
         &perror);

      if(!pstream)
      {

         if(perror)
         {

            g_error_free(perror);

         }

         gtk4_clipboard_request_complete(pdata, false);

         return;

      }

      auto prequest = g_new0(gtk4_clipboard_stream_request, 1);

      prequest->m_pdata = pdata;
      prequest->m_pstream = pstream;
      prequest->m_pbytearray = g_byte_array_new();
      prequest->m_pszMimeType = g_strdup(pszMimeType);

      if(!prequest->m_pbytearray || !prequest->m_pszMimeType)
      {

         gtk4_clipboard_stream_request_destroy(prequest, false);

         return;

      }

      g_input_stream_read_bytes_async(
         prequest->m_pstream,
         g_uClipboardReadBlockSize,
         G_PRIORITY_DEFAULT,
         nullptr,
         &gtk4_clipboard_file_stream_read,
         prequest);

   }


   void gtk4_clipboard_text_read_ready(
      GObject * psource,
      GAsyncResult * presult,
      gpointer puserData)
   {

      auto pdata = (clipboard_data *)puserData;

      GError * perror = nullptr;

      auto pszText = gdk_clipboard_read_text_finish(
         GDK_CLIPBOARD(psource),
         presult,
         &perror);

      if(!pszText)
      {

         if(perror)
         {

            g_error_free(perror);

         }

         gtk4_clipboard_request_complete(pdata, false);

         return;

      }

      pdata->m_str = pszText;

      g_free(pszText);

      gtk4_clipboard_request_complete(pdata, true);

   }


   void gtk4_clipboard_texture_read_ready(
      GObject * psource,
      GAsyncResult * presult,
      gpointer puserData)
   {

      auto pdata = (clipboard_data *)puserData;

      GError * perror = nullptr;

      auto ptexture = gdk_clipboard_read_texture_finish(
         GDK_CLIPBOARD(psource),
         presult,
         &perror);

      if(!ptexture)
      {

         if(perror)
         {

            g_error_free(perror);

         }

         gtk4_clipboard_request_complete(pdata, false);

         return;

      }

      auto cx = gdk_texture_get_width(ptexture);
      auto cy = gdk_texture_get_height(ptexture);

      bool bSucceeded = false;

      if(cx > 0 && cy > 0 && pdata->m_pimage)
      {

         pdata->m_pimage->create({cx, cy});
         pdata->m_pimage->map();

#if GTK_CHECK_VERSION(4, 10, 0)

         // ca2 images on Linux are BGRA. The old GdkPixbuf code copied
         // straight-alpha RGBA into straight-alpha BGRA, so request the
         // equivalent non-premultiplied format here.
         auto pdownloader = gdk_texture_downloader_new(ptexture);

         gdk_texture_downloader_set_format(
            pdownloader,
            GDK_MEMORY_B8G8R8A8);

         gdk_texture_downloader_download_into(
            pdownloader,
            (guchar *)pdata->m_pimage->image32(),
            (gsize)pdata->m_pimage->scan_size());

         gdk_texture_downloader_free(pdownloader);

#else

         // GTK 4.0 through 4.8 only provide gdk_texture_download(), whose
         // output is CAIRO_FORMAT_ARGB32 (premultiplied BGRA on the usual
         // little-endian Linux targets). Convert it back to straight alpha
         // to preserve the semantics of the previous GdkPixbuf path.
         gdk_texture_download(
            ptexture,
            (guchar *)pdata->m_pimage->image32(),
            (gsize)pdata->m_pimage->scan_size());

         pdata->m_pimage->div_alpha();

#endif

         bSucceeded = true;

      }

      g_object_unref(ptexture);

      gtk4_clipboard_request_complete(pdata, bSucceeded);

   }


} // anonymous namespace


namespace node_gtk4
{


   copydesk::copydesk()
   {


   }


   copydesk::~copydesk()
   {


   }


   void copydesk::initialize_copydesk(::windowing::window * pwindow)
   {

      ::user::copydesk::initialize_copydesk(pwindow);

   }


   void copydesk::destroy()
   {

      ::user::copydesk::destroy();

   }


   bool copydesk::_set_plain_text(const ::scoped_string & scopedstr)
   {

      ::string str(scopedstr);

      bool bSucceeded = false;

      //auto pnode = system()->node();

      ::procedure procedure;

      procedure = [&]()
      {

         auto pclipboard = gtk4_standard_clipboard();

         if(!pclipboard)
         {

            return;

         }

         gdk_clipboard_set_text(pclipboard, str.c_str());

         bSucceeded = true;

      };

      procedure.set_timeout(1_min);

      system()->send(procedure);

      return bSucceeded;

   }


   bool copydesk::_get_plain_text(::string & str)
   {

      auto pdata =
         allocateø clipboard_data(this, e_clipboard_get_plain_text);

      //pdata->increment_reference_count(
        // REFERENCING_DEBUGGING_P_NOTE(this, "copydesk::_get_plain_text"));

      system()->acme_windowing()->main_post([pdata]
      {

         auto pclipboard = gtk4_standard_clipboard();

         if(!pclipboard)
         {

            gtk4_clipboard_request_complete(pdata, false);

            return;

         }

         gdk_clipboard_read_text_async(
            pclipboard,
            nullptr,
            &gtk4_clipboard_text_read_ready,
            pdata);

      });

      if(!pdata->m_happening.wait(1_min).succeeded())
      {

         return false;

      }

      if(pdata->m_eclipboard == e_clipboard_error)
      {

         return false;

      }

      str = pdata->m_str;

      return true;

   }


   bool copydesk::_has_plain_text()
   {

      bool bHasPlainText = false;

      //auto pnode = system()->node();

      ::procedure procedure;


      procedure = [&]()
      {

         auto pclipboard = gtk4_standard_clipboard();

         if(!pclipboard)
         {

            return;

         }

         bHasPlainText = gtk4_formats_have_plain_text(
            gdk_clipboard_get_formats(pclipboard));

      };


      procedure.set_timeout(1_min);

      system()->send(procedure);

      return bHasPlainText;

   }


   bool copydesk::_has_filea()
   {

      bool bHasFileList = false;

      //auto pnode = system()->node();

      ::procedure procedure;

      procedure = [&]()
      {

         auto pclipboard = gtk4_standard_clipboard();

         if(!pclipboard)
         {

            return;

         }

         bHasFileList = gtk4_formats_have_file_list(
            gdk_clipboard_get_formats(pclipboard));

      };

      procedure.set_timeout(1_min);

      system()->send(procedure);

      return bHasFileList;

   }


   bool copydesk::_get_filea(
      ::file::path_array_base & patha,
      enum_op & eop)
   {

      auto pdata =
         allocateø clipboard_data(this, e_clipboard_get_patha);

      //pdata->increment_reference_count(
//         REFERENCING_DEBUGGING_P_NOTE(this, "copydesk::_get_filea"));

      system()->acme_windowing()->main_post([pdata]
      {

         auto pclipboard = gtk4_standard_clipboard();

         if(!pclipboard)
         {

            gtk4_clipboard_request_complete(pdata, false);

            return;

         }

         static const char * s_ppszMimeTypes[] =
         {

            g_pszGnomeCopiedFiles,
            g_pszUriList,
            nullptr,

         };

         gdk_clipboard_read_async(
            pclipboard,
            s_ppszMimeTypes,
            G_PRIORITY_DEFAULT,
            nullptr,
            &gtk4_clipboard_file_read_ready,
            pdata);

      });

      if(!pdata->m_happening.wait(1_min).succeeded())
      {

         return false;

      }

      if(pdata->m_eclipboard == e_clipboard_error)
      {

         return false;

      }

      eop = pdata->m_eop;
      patha = pdata->m_patha;

      return !patha.is_empty();

   }


   bool copydesk::_set_filea(
      const ::file::path_array_base & patha,
      enum_op eop)
   {

      ::string strGnomeCopiedFiles;
      ::string strUriList;

      if(!gtk4_build_file_payloads(
         patha,
         eop,
         strGnomeCopiedFiles,
         strUriList))
      {

         return false;

      }

      bool bSucceeded = false;

      ///auto pnode = system()->node();
      ///
      ::procedure procedure;

      procedure = [&]()
      {

         auto pclipboard = gtk4_standard_clipboard();

         if(!pclipboard)
         {

            return;

         }

         GdkContentProvider * pprovidera[2] =
         {

            gtk4_content_provider_for_string(
               g_pszGnomeCopiedFiles,
               strGnomeCopiedFiles),

            gtk4_content_provider_for_string(
               g_pszUriList,
               strUriList),

         };

         if(!pprovidera[0] || !pprovidera[1])
         {

            if(pprovidera[0])
            {

               g_object_unref(pprovidera[0]);

            }

            if(pprovidera[1])
            {

               g_object_unref(pprovidera[1]);

            }

            return;

         }

         // The union provider takes ownership of the child providers.
         auto punionprovider = gdk_content_provider_new_union(
            pprovidera,
            2);

         if(!punionprovider)
         {

            g_object_unref(pprovidera[0]);
            g_object_unref(pprovidera[1]);

            return;

         }

         bSucceeded = gdk_clipboard_set_content(
            pclipboard,
            punionprovider);

         g_object_unref(punionprovider);

      };

      procedure.set_timeout(1_min);

      system()->send(procedure);

      return bSucceeded;

   }


   bool copydesk::_desk_to_image(::image::image * pimage)
   {

      if(!pimage)
      {

         return false;

      }

      auto pdata =
         allocateø clipboard_data(this, e_clipboard_get_image);

      pdata->m_pimage = image()->create_image();

      //pdata->increment_reference_count(
        // REFERENCING_DEBUGGING_P_NOTE(this, "copydesk::_desk_to_image"));

      system()->acme_windowing()->main_post([pdata]
      {

         auto pclipboard = gtk4_standard_clipboard();

         if(pclipboard
            && !gtk4_formats_have_image(gdk_clipboard_get_formats(pclipboard)))
         {

            pclipboard = nullptr;

         }

         // GTK4 exposes the normal clipboard and the primary selection.
         // There is no GDK_SELECTION_SECONDARY equivalent in GTK4.
         if(!pclipboard)
         {

            auto pprimaryclipboard = gtk4_primary_clipboard();

            if(pprimaryclipboard
               && gtk4_formats_have_image(
                  gdk_clipboard_get_formats(pprimaryclipboard)))
            {

               pclipboard = pprimaryclipboard;

            }

         }

         if(!pclipboard)
         {

            gtk4_clipboard_request_complete(pdata, false);

            return;

         }

         gdk_clipboard_read_texture_async(
            pclipboard,
            nullptr,
            &gtk4_clipboard_texture_read_ready,
            pdata);

      });

      if(!pdata->m_happening.wait(1_min).succeeded())
      {

         return false;

      }

      if(pdata->m_eclipboard == e_clipboard_error
         || !pdata->m_pimage
         || !pdata->m_pimage->is_ok())
      {

         return false;

      }

      pimage->create(pdata->m_pimage->size());

      pimage->copy(pdata->m_pimage);

      return true;

   }


   bool copydesk::_image_to_desk(const ::image::image * pimage)
   {

      if(!pimage || !pimage->is_ok())
      {

         return false;

      }

      pimage->map();

      auto cx = pimage->width();
      auto cy = pimage->height();
      auto iScan = pimage->scan_size();

      if(cx <= 0 || cy <= 0 || iScan < cx * 4)
      {

         pimage->unmap();

         return false;

      }

      // Copy before entering GDK so the texture is independent of the ca2
      // image mapping and remains valid after this function returns.
      auto pbytes = g_bytes_new(
         pimage->image32(),
         (gsize)iScan * (gsize)cy);

      pimage->unmap();

      if(!pbytes)
      {

         return false;

      }

      bool bSucceeded = false;

      //auto pnode = system()->node();

      ::procedure procedure;

      procedure = [&]()
      {

         auto pclipboard = gtk4_standard_clipboard();

         if(!pclipboard)
         {

            return;

         }

         // This matches ca2's Linux BGRA, straight-alpha image storage.
         // Use GDK_MEMORY_B8G8R8A8_PREMULTIPLIED instead if this particular
         // image path stores premultiplied pixels.
         auto ptexture = gdk_memory_texture_new(
            cx,
            cy,
            GDK_MEMORY_B8G8R8A8,
            pbytes,
            (gsize)iScan);

         if(!ptexture)
         {

            return;

         }

         gdk_clipboard_set_texture(pclipboard, ptexture);

         g_object_unref(ptexture);

         bSucceeded = true;

      };

      procedure.set_timeout(1_min);

      system()->send(procedure);

      g_bytes_unref(pbytes);

      return bSucceeded;

   }


   bool copydesk::_has_image()
   {

      bool bHasImage = false;

      //auto pnode = system()->node();

      ::procedure procedure;

      procedure = [&]()
      {

         auto pclipboard = gtk4_standard_clipboard();

         if(!pclipboard)
         {

            return;

         }

         bHasImage = gtk4_formats_have_image(
            gdk_clipboard_get_formats(pclipboard));

      };

      procedure.set_timeout(1_min);

      system()->send(procedure);

      return bHasImage;

   }


} // namespace node_gtk4