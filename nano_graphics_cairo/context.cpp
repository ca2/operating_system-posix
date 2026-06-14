//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#include "framework.h"
#include "context.h"
#include "icon.h"
#include "acme/exception/exception.h"
#include "acme/graphics/image/image32.h"
#include "acme/graphics/image/pixmap.h"
#include "acme/nano/graphics/brush.h"
#include "acme/nano/graphics/font.h"
#include "acme/nano/graphics/font_family.h"
#include "acme/nano/graphics/icon.h"
#include "acme/nano/graphics/image.h"
#include "acme/nano/graphics/pen.h"
#include "acme/prototype/geometry2d/rectangle.h"
#ifdef HAS_X11
#include "acme/operating_system/x11/_x11.h"
#include <cairo/cairo-xlib.h>
#endif


::pixmap as_pixmap(cairo_surface_t * psurface)
{

   ::pixmap pixmap;

   if (!psurface || cairo_surface_get_type(psurface) != CAIRO_SURFACE_TYPE_IMAGE)
   {

      return pixmap;

   }

   cairo_surface_flush(psurface);

   pixmap.m_pimage32 = (::image32_t *) cairo_image_surface_get_data(psurface);
   pixmap.m_sizeRaw.cx = cairo_image_surface_get_width(psurface);
   pixmap.m_sizeRaw.cy = cairo_image_surface_get_height(psurface);
   pixmap.m_iScan = cairo_image_surface_get_stride(psurface);
   pixmap.map(pixmap.m_sizeRaw);

   return pixmap;

}


namespace cairo
{


   namespace nano
   {


      namespace graphics
      {


         namespace
         {


            void throw_if_cairo_error(cairo_status_t status)
            {

               if (status != CAIRO_STATUS_SUCCESS)
               {

                  throw ::exception(error_failed, cairo_status_to_string(status));

               }

            }


            cairo_font_slant_t font_slant(::nano::graphics::font * pfont)
            {

               return pfont && pfont->m_bItalic ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL;

            }


            cairo_font_weight_t font_weight(::nano::graphics::font * pfont)
            {

               return pfont && pfont->m_bBold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL;

            }


            ::f64 font_size(::nano::graphics::font * pfont)
            {

               if (!pfont)
               {

                  return 12.0;

               }

               return pfont->m_bPixelSize ? pfont->m_fFontSize : pfont->m_fFontSize * 96.0 / 72.0;

            }


         } // namespace


         context::context()
         {

            m_psurfaceMemory = nullptr;
            m_pdc = nullptr;
            m_bOwnContext = false;

            //create({1, 1});

         }


         context::context(cairo_t * pdc)
         {

            m_psurfaceMemory = nullptr;
            m_pdc = pdc;
            m_bOwnContext = false;

            if (m_pdc)
            {

               cairo_reference(m_pdc);
               m_bOwnContext = true;

            }

         }


         context::~context()
         {

            destroy();

         }


         void context::destroy()
         {

            if (m_pdc && m_bOwnContext)
            {

               cairo_destroy(m_pdc);

            }

            if (m_psurfaceMemory)
            {

               cairo_surface_destroy(m_psurfaceMemory);

            }

            m_pdc = nullptr;
            m_psurfaceMemory = nullptr;
            m_bOwnContext = false;
            m_size = {};

         }


         void context::create(const ::i32_size & size)
         {

            destroy();

            if (size.cx <= 0 || size.cy <= 0)
            {

               return;

            }

            m_psurfaceMemory = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, size.cx, size.cy);
            throw_if_cairo_error(cairo_surface_status(m_psurfaceMemory));

            m_pdc = cairo_create(m_psurfaceMemory);
            m_bOwnContext = true;
            throw_if_cairo_error(cairo_status(m_pdc));

            m_size = size;

         }


#ifdef HAS_X11

         void context::create_for_x11(const ::x11::handle_t & handle, int w, int h)
         {

            destroy();

            m_psurfaceMemory = cairo_xlib_surface_create(__x11_handle_with_visual(handle), w, h);
            throw_if_cairo_error(cairo_surface_status(m_psurfaceMemory));

            m_pdc = cairo_create(m_psurfaceMemory);
            m_bOwnContext = true;
            throw_if_cairo_error(cairo_status(m_pdc));

            m_size = {w, h};

         }

#endif


         void context::resize(const ::i32_size & size)
         {

            if (size == m_size)
            {

               return;

            }

#ifdef HAS_X11
            if (m_psurfaceMemory && cairo_surface_get_type(m_psurfaceMemory) == CAIRO_SURFACE_TYPE_XLIB)
            {

               cairo_xlib_surface_set_size(m_psurfaceMemory, size.cx, size.cy);
               m_size = size;
               return;

            }
#endif

            auto psurfaceOld = m_psurfaceMemory;

            if (psurfaceOld)
            {

               cairo_surface_reference(psurfaceOld);

            }

            create(size);

            if (psurfaceOld && m_pdc)
            {

               cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);
               cairo_set_source_surface(m_pdc, psurfaceOld, 0.0, 0.0);
               cairo_paint(m_pdc);
               cairo_set_operator(m_pdc, CAIRO_OPERATOR_OVER);

            }

            if (psurfaceOld)
            {

               cairo_surface_destroy(psurfaceOld);

            }

         }


         void context::attach(void * posdata, const ::i32_size & size, ::i32 iType)
         {

            if (iType != 0 || !posdata)
            {

               throw ::exception(error_wrong_type);

            }

            destroy();

            m_pdc = (cairo_t *) posdata;
            cairo_reference(m_pdc);
            m_bOwnContext = true;
            m_size = size;

         }


         void context::set_pen(::nano::graphics::pen * ppen)
         {

            m_ppen = ppen;

         }


         void context::set_brush(::nano::graphics::brush * pbrush)
         {

            m_pbrush = pbrush;

         }


         void context::set_font(::nano::graphics::font * pfont)
         {

            m_pfont = pfont;

         }


         void context::set_blend_mode(::nano::graphics::enum_blend_mode eblendmode)
         {

            cairo_set_operator(m_pdc, eblendmode == ::nano::graphics::e_blend_mode_copy
               ? CAIRO_OPERATOR_SOURCE : CAIRO_OPERATOR_OVER);

         }


         void context::set_smoothing_mode(::nano::graphics::enum_smoothing_mode esmoothingmode)
         {

            cairo_set_antialias(m_pdc, esmoothingmode == ::nano::graphics::e_smoothing_mode_high_quality
               ? CAIRO_ANTIALIAS_BEST : CAIRO_ANTIALIAS_NONE);

         }


         void context::set_text_rendering_hint(::nano::graphics::enum_text_rendering_hint etextrenderinghint)
         {

            cairo_font_options_t * pfontoptions = cairo_font_options_create();

            cairo_font_options_set_antialias(pfontoptions,
               etextrenderinghint == ::nano::graphics::e_text_rendering_hint_clear_type_grid_fit
               ? CAIRO_ANTIALIAS_SUBPIXEL : CAIRO_ANTIALIAS_DEFAULT);

            cairo_set_font_options(m_pdc, pfontoptions);
            cairo_font_options_destroy(pfontoptions);

         }


         void context::clear(const ::color::color & color)
         {

            cairo_save(m_pdc);
            cairo_set_operator(m_pdc, CAIRO_OPERATOR_SOURCE);
            _set_source(color);
            cairo_paint(m_pdc);
            cairo_restore(m_pdc);

         }


         void context::on_begin_draw()
         {

            cairo_save(m_pdc);

         }


         void context::on_end_draw()
         {

            cairo_restore(m_pdc);

            if (m_psurfaceMemory)
            {

               cairo_surface_flush(m_psurfaceMemory);

            }

         }


         void context::_set_font()
         {

            if (!m_pfont)
            {

               return;

            }

            auto strFamilyName = m_pfont->m_pfontfamily
               ? m_pfont->m_pfontfamily->get_font_family_name() : "sans";

            cairo_select_font_face(m_pdc, strFamilyName, font_slant(m_pfont), font_weight(m_pfont));
            cairo_set_font_size(m_pdc, font_size(m_pfont));

         }


         void context::_draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText,
                                  const ::e_draw_text & edrawtext, const ::e_align & ealign)
         {

            if (!m_pfont || !m_pbrush)
            {

               return;

            }

            _set_font();

            cairo_text_extents_t textextents = {};
            cairo_font_extents_t fontextents = {};

            cairo_text_extents(m_pdc, scopedstr, &textextents);
            cairo_font_extents(m_pdc, &fontextents);

            ::f64 x = rectangleText.left - textextents.x_bearing;
            ::f64 y = rectangleText.top + fontextents.ascent;

            if (ealign & e_align_right)
            {

               x = rectangleText.right - textextents.width - textextents.x_bearing;

            }
            else if (ealign & e_align_horizontal_center)
            {

               x = rectangleText.left + (rectangleText.width() - textextents.width) / 2.0 - textextents.x_bearing;

            }

            if (ealign & e_align_bottom)
            {

               y = rectangleText.bottom - fontextents.descent;

            }
            else if (ealign & e_align_vertical_center)
            {

               y = rectangleText.top + (rectangleText.height() - fontextents.height) / 2.0 + fontextents.ascent;

            }

            cairo_save(m_pdc);
            cairo_rectangle(m_pdc, rectangleText.left, rectangleText.top, rectangleText.width(), rectangleText.height());
            cairo_clip(m_pdc);
            _set_source(m_pbrush->m_color);
            cairo_move_to(m_pdc, x, y);
            cairo_show_text(m_pdc, scopedstr);
            cairo_restore(m_pdc);

         }


         ::f64_size context::get_text_extents(const ::scoped_string & scopedstr)
         {

            if (!m_pfont)
            {

               return {};

            }

            _set_font();

            cairo_text_extents_t textextents = {};
            cairo_font_extents_t fontextents = {};

            cairo_text_extents(m_pdc, scopedstr, &textextents);
            cairo_font_extents(m_pdc, &fontextents);

            return {textextents.x_advance, fontextents.height};

         }


         void context::rectangle(const ::f64_rectangle & rectangle)
         {

            if (!m_pbrush && !m_ppen)
            {

               return;

            }

            cairo_save(m_pdc);
            cairo_rectangle(m_pdc, rectangle.left, rectangle.top, rectangle.width(), rectangle.height());

            if (m_pbrush)
            {

               _set_source(m_pbrush->m_color);
               m_ppen ? cairo_fill_preserve(m_pdc) : cairo_fill(m_pdc);

            }

            if (m_ppen && m_ppen->m_fWidth > 0.0)
            {

               _set_source(m_ppen->m_color);
               cairo_set_line_width(m_pdc, m_ppen->m_fWidth);
               cairo_stroke(m_pdc);

            }

            cairo_restore(m_pdc);

         }


         void context::ellipse(const ::f64_rectangle & rectangle)
         {

            if ((!m_pbrush && !m_ppen) || rectangle.width() <= 0.0 || rectangle.height() <= 0.0)
            {

               return;

            }

            cairo_save(m_pdc);
            cairo_translate(m_pdc, rectangle.left + rectangle.width() / 2.0, rectangle.top + rectangle.height() / 2.0);
            cairo_scale(m_pdc, rectangle.width() / 2.0, rectangle.height() / 2.0);
            cairo_arc(m_pdc, 0.0, 0.0, 1.0, 0.0, 2.0 * MATH_PI);
            cairo_restore(m_pdc);

            if (m_pbrush)
            {

               _set_source(m_pbrush->m_color);
               m_ppen ? cairo_fill_preserve(m_pdc) : cairo_fill(m_pdc);

            }

            if (m_ppen && m_ppen->m_fWidth > 0.0)
            {

               _set_source(m_ppen->m_color);
               cairo_set_line_width(m_pdc, m_ppen->m_fWidth);
               cairo_stroke(m_pdc);

            }

         }


         void context::line(const ::f64_point & point1, const ::f64_point & point2)
         {

            if (!m_ppen || m_ppen->m_fWidth <= 0.0)
            {

               return;

            }

            cairo_save(m_pdc);
            _set_source(m_ppen->m_color);
            cairo_set_line_width(m_pdc, m_ppen->m_fWidth);
            cairo_move_to(m_pdc, point1.x, point1.y);
            cairo_line_to(m_pdc, point2.x, point2.y);
            cairo_stroke(m_pdc);
            cairo_restore(m_pdc);

         }


         void context::_draw_surface(cairo_surface_t * psurface, const ::f64_rectangle & rectangleTarget,
                                     const ::f64_rectangle & rectangleSource)
         {

            if (!psurface || rectangleTarget.width() <= 0.0 || rectangleTarget.height() <= 0.0
               || rectangleSource.width() <= 0.0 || rectangleSource.height() <= 0.0)
            {

               return;

            }

            cairo_save(m_pdc);
            cairo_rectangle(m_pdc, rectangleTarget.left, rectangleTarget.top,
                            rectangleTarget.width(), rectangleTarget.height());
            cairo_clip(m_pdc);
            cairo_translate(m_pdc, rectangleTarget.left, rectangleTarget.top);
            cairo_scale(m_pdc, rectangleTarget.width() / rectangleSource.width(),
                        rectangleTarget.height() / rectangleSource.height());
            cairo_set_source_surface(m_pdc, psurface, -rectangleSource.left, -rectangleSource.top);
            cairo_paint(m_pdc);
            cairo_restore(m_pdc);

         }


         void context::draw_icon(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, ::nano::graphics::icon * picon)
         {

            ::pointer < ::cairo::nano::graphics::icon > pcairoicon = picon;

            if (!pcairoicon || !pcairoicon->m_pcairosurface)
            {

               return;

            }

            auto sizeSource = pcairoicon->size();
            _draw_surface(pcairoicon->m_pcairosurface, {x, y, x + cx, y + cy},
                          {0.0, 0.0, (::f64) sizeSource.cx, (::f64) sizeSource.cy});

         }


         void context::draw_image(const ::f64_rectangle & rectangle, ::nano::graphics::image * pimage)
         {

            if (!pimage)
            {

               return;

            }

            auto sizeSource = pimage->size();

            draw_image({rectangle.left, rectangle.top},
                       {0.0, 0.0, (::f64) sizeSource.cx, (::f64) sizeSource.cy}, pimage);

         }


         void context::draw_image(const ::f64_point & point, const ::f64_rectangle & rectangle,
                                  ::nano::graphics::image * pimage)
         {

            if (!pimage || !pimage->get_buffer())
            {

               return;

            }

            auto sizeImage = pimage->size();
            auto iStride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, sizeImage.cx);
            auto psurface = cairo_image_surface_create_for_data((unsigned char *) pimage->get_buffer(),
               CAIRO_FORMAT_ARGB32, sizeImage.cx, sizeImage.cy, iStride);

            throw_if_cairo_error(cairo_surface_status(psurface));

            _draw_surface(psurface,
               {point.x, point.y, point.x + rectangle.width(), point.y + rectangle.height()}, rectangle);

            cairo_surface_destroy(psurface);

         }


         void context::_set_source(const ::color::color & color)
         {

            cairo_set_source_rgba(m_pdc,
               color.f64_red(), color.f64_green(), color.f64_blue(), color.f64_opacity());

         }


         ::pixmap context::pixmap()
         {

            return as_pixmap(m_psurfaceMemory);

         }


         void context::translate(::f64 x, ::f64 y)
         {

            cairo_translate(m_pdc, x, y);

         }


      } // namespace graphics


   } // namespace nano


} // namespace cairo
