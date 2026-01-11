// Created by camilo on 2024-09-13 07:23 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "icon.h"


#include <stb/stb_image.h>

namespace innate_ui_xaw
{


   icon::icon()
   {
      //m_pgdkpixbuf = nullptr;
   }


   icon::~icon()
   {

   }



   void icon::_create()
   {



      // Example: Simulate reading a JPEG image into a memory buffer (replace with actual data)
      auto data = m_memory.data();
      auto size = m_memory.size();


      int width, height, channels;
      unsigned char *image_data = stbi_load_from_memory(data, size,  &width, &height, &channels, 0);


      m_size.cx = width;
      m_size.cy = height;

      // Display *display = XtDisplay(parent);
      // Pixmap pixmap = XCreatePixmap(display, XtWindow(parent), width, height, DefaultDepth(display, 0));
      // XImage *ximage = XCreateImage(display, DefaultVisual(display, 0), 24, ZPixmap, 0, (char*)image_data, width, height, 32, 0);
      // XPutImage(display, pixmap, DefaultGC(display, 0), ximage, 0, 0, 0, 0, width, height);
      //
      // Widget icon_widget = XtVaCreateManagedWidget("icon", commandWidgetClass, parent,
      //                                              XtNbitmap, pixmap,
      //                                              XtNwidth, width,
      //                                              XtNheight, height,
      //                                              NULL);
      stbi_image_free(image_data);
      // Create a GdkPixbufLoader to load the image from the memory buffer
      //GError * pgerror = NULL;
      //GdkPixbufLoader *loader = gdk_pixbuf_loader_new();

      // // Write the JPEG memory buffer into the loader
      // if (!gdk_pixbuf_loader_write(loader, jpeg_buffer, jpeg_size, &pgerror)) {
      //    g_printerr("Error loading image from buffer: %s\n", pgerror->message);
      //    g_clear_error(&pgerror);
      //    g_object_unref(loader);
      //    throw ::exception(error_failed);
      // }
      //
      // // Finish the loading process
      // if (!gdk_pixbuf_loader_close(loader, &pgerror)) {
      //    g_printerr("Error finalizing image loading: %s\n", pgerror->message);
      //    g_clear_error(&pgerror);
      //    g_object_unref(loader);
      //    throw ::exception(error_failed);
      // }

      // Get the GdkPixbuf from the loader
      GdkPixbuf *pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);

      if (!pixbuf) {
         g_printerr("Failed to load image from buffer\n");
         g_object_unref(loader);
         throw ::exception(error_failed);
      }

      // Convert GdkPixbuf to GdkPaintable
      //pixbuf;

      m_pgdkpixbuf = gdk_pixbuf_scale_simple(pixbuf, m_size.cx, m_size.cy, GDK_INTERP_BILINEAR);

      // Free the original GdkPixbuf since it's no longer needed
      g_object_unref(pixbuf);

   }





} // namespace innate_ui
