// Created by camilo on 2024-09-13 07:23 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "icon.h"
#include "acme/filesystem/filesystem/file_context.h"


namespace innate_ui_gtk4
{


   icon::icon()
   {
      m_pgdkpaintable = nullptr;
   }


   icon::~icon()
   {

   }


   void icon::_create()
   {


      // Example: Simulate reading a JPEG image into a memory buffer (replace with actual data)
      const guchar *jpeg_buffer = m_memory.data();
      gsize jpeg_size = m_memory.size();

      // Create a GdkPixbufLoader to load the image from the memory buffer
      GError * pgerror = NULL;
      GdkPixbufLoader *loader = gdk_pixbuf_loader_new();

      // Write the JPEG memory buffer into the loader
      if (!gdk_pixbuf_loader_write(loader, jpeg_buffer, jpeg_size, &pgerror)) {
         if (pgerror)
         {
            g_printerr("Error loading image from buffer: %s\n", pgerror->message);
            g_clear_error(&pgerror);
         }
         g_object_unref(loader);
         throw ::exception(error_failed);
      }
      if (pgerror)
      {
         g_clear_error(&pgerror);
      }

      // Finish the loading process
      if (!gdk_pixbuf_loader_close(loader, &pgerror)) {
         if (pgerror)
         {
            g_printerr("Error finalizing image loading: %s\n", pgerror->message);
            g_clear_error(&pgerror);
         }
         g_object_unref(loader);
         throw ::exception(error_failed);
      }
      if (pgerror)
      {
         g_clear_error(&pgerror);
      }


      // Get the GdkPixbuf from the loader
      GdkPixbuf *pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);

      if (!pixbuf) {
         g_printerr("Failed to load image from buffer\n");
         g_object_unref(loader);
         throw ::exception(error_failed);
      }

      // Convert GdkPixbuf to GdkPaintable
      m_pgdkpaintable = GDK_PAINTABLE(gdk_texture_new_for_pixbuf(pixbuf));




   }

   //
   // void icon::load_file(const ::scoped_string & scopedstrPath)
   // {
   //
   //
   // }


} // namespace innate_ui
