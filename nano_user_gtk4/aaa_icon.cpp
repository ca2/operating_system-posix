//
// Created by camilo on 9/24/24.
//
#include "framework.h"
#include "icon.h"
#include <gtk/gtk.h>

// Function to convert GdkPixbuf to cairo_surface_t
cairo_surface_t *gdk_pixbuf_to_cairo_surface(GdkPixbuf *pixbuf)
{
   cairo_format_t format;
   int width, height, stride;
   GdkPixbuf *pixbuf_with_alpha = NULL;
   cairo_surface_t *surface;
   cairo_t *cr;

   width = gdk_pixbuf_get_width(pixbuf);
   height = gdk_pixbuf_get_height(pixbuf);
   stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, width);

   // Create an empty cairo surface to hold the image
   surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);

   // Create a Cairo context
   cr = cairo_create(surface);

   // Create GdkPixbuf with alpha if it's not present
   if (!gdk_pixbuf_get_has_alpha(pixbuf))
   {
      pixbuf_with_alpha = gdk_pixbuf_add_alpha(pixbuf, FALSE, 0, 0, 0);
      pixbuf = pixbuf_with_alpha;
   }

   // Paint the GdkPixbuf onto the Cairo surface
   gdk_cairo_set_source_pixbuf(cr, pixbuf, 0, 0);
   cairo_paint(cr);

   // Cleanup
   cairo_destroy(cr);
   if (pixbuf_with_alpha)
      g_object_unref(pixbuf_with_alpha);

   return surface;
}

namespace gtk4 {
namespace nano {
namespace user {

   icon::icon()
   {

   }

   icon::~icon()
   {
   }


   void icon::load_image_file(const void *p, memsize size)
   {


      // Sample JPEG data in memory (you would typically load this from a file or network)
      //const unsigned char jpeg_data[] = { /* ... your JPEG data here ... */ };
      //gsize jpeg_data_size = sizeof(jpeg_data);

      // Load JPEG image from memory into GdkPixbuf
      GdkPixbufLoader *loader = gdk_pixbuf_loader_new();
      GError *error = NULL;

      if (!gdk_pixbuf_loader_write(loader, (const guchar *) p, size, &error)) {
         g_printerr("Error loading image: %s\n", error->message);
         g_error_free(error);
         g_object_unref(loader);
         throw ::exception(error_failed);
      }

      gdk_pixbuf_loader_close(loader, NULL);

      // Get the GdkPixbuf from the loader
      GdkPixbuf *pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);

      if (!pixbuf) {
         g_printerr("Failed to load image.\n");
         g_object_unref(loader);
         throw ::exception(error_failed);
      }

      // Convert GdkPixbuf to cairo_surface_t
      cairo_surface_t *pcairosurface = gdk_pixbuf_to_cairo_surface(pixbuf);

      if (!pcairosurface) {
         g_printerr("Failed to create Cairo surface from GdkPixbuf.\n");
         g_object_unref(loader);
         throw ::exception(error_failed);
      }

      // Use the surface in your GTK/Cairo drawing code (e.g., on a drawing area)
      // For demonstration purposes, just print success message.
      g_print("Successfully loaded image into cairo_surface_t.\n");

      // Cleanup
      g_object_unref(loader);

      m_pcairosurface = pcairosurface;

   }

} // user
} // nano
} // gtk4