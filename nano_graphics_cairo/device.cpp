//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#include "framework.h"
#include "device.h"

#include <acme/graphics/image/pixmap.h>

#include "icon.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/nano/graphics/brush.h"
#include "acme/nano/graphics/font.h"
#include "acme/nano/graphics/pen.h"
#include "acme/graphics/image/image32.h"


cairo_surface_t * as_cairo_surface(::pixmap & pixmap)
{

   return cairo_image_surface_create_for_data(
       (unsigned char *) pixmap.m_pimage32,              // Pointer to the raw data in memory
       CAIRO_FORMAT_ARGB32,    // Data format (ARGB32)
       pixmap.width(),                  // Width of the surface
       pixmap.height(),                 // Height of the surface
       pixmap.m_iScan                 // Stride (number of bytes per row)
   );

}


namespace cairo
{


   void draw_scaled_part_of_image(cairo_t *cr, cairo_surface_t *image,
                                  double src_x, double src_y, double src_width, double src_height,
                                  double dest_x, double dest_y, double dest_width, double dest_height)
   {

      cairo_save(cr);
      // Step 1: Create a new pattern from the image surface
      cairo_pattern_t *pattern = cairo_pattern_create_for_surface(image);

      // Step 2: Clip the region of the image that you want to paint
      cairo_rectangle(cr, dest_x, dest_y, dest_width, dest_height);
      cairo_clip(cr);

      // Step 3: Set the source for the pattern with appropriate scaling and translation
      cairo_save(cr);  // Save the current transformation matrix

      // Translate the pattern so that the top-left corner of the source area aligns with the destination area
      cairo_translate(cr, dest_x, dest_y);

      // Scale down the image part
      cairo_scale(cr, dest_width / src_width, dest_height / src_height);

      // Move the pattern to the part of the image you want to show (src_x, src_y)
      cairo_set_source_surface(cr, image, -src_x, -src_y);

      // Step 4: Paint the image to the destination
      cairo_paint(cr);

      // Restore the transformation matrix
      cairo_restore(cr);

      // Cleanup
      cairo_pattern_destroy(pattern);

      cairo_restore(cr);
   }

   namespace nano
   {
      namespace graphics
      {
         device::device()
         {

            m_psurfaceMemory = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);

            m_pdc = cairo_create(m_psurfaceMemory);

         }


         device::device(cairo_t * pdc)
         {

            m_psurfaceMemory = nullptr;

            m_pdc = pdc;

         }


         device::~device()
         {

            if(m_pdc)
            {

               cairo_destroy(m_pdc);

            }

            if(m_psurfaceMemory)
            {

               cairo_surface_destroy(m_psurfaceMemory);


            }

         }


         void device::on_begin_draw()
         {

            cairo_push_group(m_pdc);

            cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);

         }


         void device::on_end_draw()
         {

            cairo_pop_group_to_source(m_pdc);

            cairo_paint(m_pdc);

         }


         void device::_draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack, ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont)
         {

            cairo_set_antialias(m_pdc, CAIRO_ANTIALIAS_SUBPIXEL);

            cairo_select_font_face(m_pdc, pnanofont->m_strFontName, CAIRO_FONT_SLANT_NORMAL, pnanofont->m_bBold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);

            cairo_set_font_size(m_pdc, pnanofont->m_iFontSize);

            cairo_text_extents_t textextents = {};

            double x = rectangleText.left();

            double y = rectangleText.top();

            cairo_text_extents(m_pdc, str, &textextents);

            if(ealign & e_align_horizontal_center)
            {

               x += ((double) rectangleText.width() - textextents.width) / 2.0;

            }
            else if(ealign & e_align_right)
            {

               x += (double) rectangleText.width() - textextents.width;

            }

            if(ealign & e_align_vertical_center)
            {

               y += ((double) rectangleText.height() - textextents.height) / 2.0;

            }
            else if(ealign & e_align_bottom)
            {

               y += (double) rectangleText.height() - textextents.height;

            }

            _set_source(pnanobrushText->m_color);

            cairo_move_to(m_pdc, x, y + textextents.height);

            cairo_show_text(m_pdc, str);

         }


         ::size_i32 device::get_text_extents(const ::string & str, ::nano::graphics::font * pnanofont)
         {

            cairo_set_antialias(m_pdc, CAIRO_ANTIALIAS_SUBPIXEL);

            cairo_select_font_face(m_pdc, pnanofont->m_strFontName, CAIRO_FONT_SLANT_NORMAL, pnanofont->m_bBold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);

            cairo_set_font_size(m_pdc, pnanofont->m_iFontSize);

            cairo_text_extents_t textextents = {};

            cairo_text_extents(m_pdc, str, &textextents);

            return { (int) textextents.width, (int) textextents.height };

         }


         void device::rectangle(const ::rectangle_i32 & rectangle, ::nano::graphics::brush * pnanobrush, ::nano::graphics::pen * pnanopen)
         {

            cairo_set_antialias(m_pdc, CAIRO_ANTIALIAS_NONE);

            int iWidth = pnanopen ? pnanopen->m_iWidth : 0;

            if(iWidth > 0 || (pnanobrush && pnanobrush->m_color.has_opacity()))
            {

               cairo_rectangle(m_pdc,
                               rectangle.left() + !!iWidth,
                               rectangle.top()  + !!iWidth,
                               rectangle.width() -  !!iWidth ,
                               rectangle.height() - !!iWidth);

            }

            if (pnanobrush && pnanobrush->m_color.has_opacity())
            {

               _set_source(pnanobrush->m_color);

               if(iWidth > 0)
               {

                  cairo_fill_preserve(m_pdc);

               }
               else
               {

                  cairo_fill(m_pdc);

               }

            }

            if(iWidth > 0)
            {

               _set_source(pnanopen->m_color);

               cairo_set_line_width(m_pdc, iWidth);

               cairo_stroke(m_pdc);

            }

         }


         //   void ::nano::graphics::device::set_antialias(bool bAntialiasOn)
         //   {
         //
         //
         //
         //   }


         //   XColor ::nano::graphics::device::_alloc_xcolor(const ::color::color & color)
         //   {
         //
         //      auto colormap = XDefaultColormap(m_pdisplay, DefaultScreen(m_pdisplay));
         //
         //      XColor xcolor;
         //
         //      xcolor.red = color.red << 8 | color.red;
         //      xcolor.green = color.green << 8 | color.green;
         //      xcolor.blue = color.blue << 8 | color.blue;
         //
         //      XAllocColor(m_pdisplay, colormap, &xcolor);
         //
         //      return xcolor;
         //
         //   }
         //
         //
         //
         //   void ::nano::graphics::device::_set_foreground(const ::color::color & color)
         //   {
         //
         //      auto xcolor = _alloc_xcolor(color);
         //
         //      XSetForeground(m_pdisplay, m_gc, xcolor.pixel);
         //
         //   }
         //
         //
         //   void ::nano::graphics::device::_set_background(const ::color::color & color)
         //   {
         //
         //      auto xcolor = _alloc_xcolor(color);
         //
         //      XSetBackground(m_pdisplay, m_gc, xcolor.pixel);
         //
         //   }


         void device::_set_source(const ::color::color & color)
         {

            cairo_set_source_rgba(m_pdc, __expand_f64_rgba(color));

         }

         void device::draw(::nano::graphics::icon * picon, int x, int y, int cx, int cy)
         {

            ::pointer < ::cairo::nano::graphics::icon > pcairoicon = picon;

            if(pcairoicon)
            {

               if(pcairoicon->m_pcairosurface)
               {

                  auto sizeSource = picon->size();

                  cairo_set_operator(m_pdc, CAIRO_OPERATOR_OVER);

                  ::cairo::draw_scaled_part_of_image(m_pdc, pcairoicon->m_pcairosurface,
                     0., 0., sizeSource.cx(), sizeSource.cy(),
                     x, y, cx, cy);

               }

            }

         }


         void device::copy_to_pixmap(pixmap & pixmap)
         {

            auto psurface = as_cairo_surface(pixmap);

            if(psurface)
            {

               cairo_set_source_surface(m_pdc, psurface, 0., 0.);

               cairo_paint(m_pdc);

               cairo_surface_destroy(psurface);

            }

         }

void device::create(int cx, int cy)
{

   if(m_pdc)
   {
cairo_destroy(m_pdc);
m_pdc = nullptr;

   }

if(m_psurfaceMemory)
{

cairo_surface_destroy(m_psurfaceMemory);
m_psurfaceMemory=nullptr;

}
               m_psurfaceMemory = cairo_image_surface_create(
               CAIRO_FORMAT_ARGB32,
               cx, cy);

            m_pdc = cairo_create(m_psurfaceMemory);


}

      } // namespace graphics


   } // namespace nano


} // namespace cairo


