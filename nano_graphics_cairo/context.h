//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#pragma once


#include "acme/nano/graphics/context.h"


#include <cairo/cairo-features.h>
#include <cairo/cairo.h>


namespace cairo
{


   namespace nano
   {


      namespace graphics
      {


         class CLASS_DECL_ACME context :
            virtual public ::nano::graphics::context
         {
         public:


            cairo_surface_t * m_psurfaceMemory;
            cairo_t * m_pdc;
            bool m_bOwnContext;

            ::pointer < ::nano::graphics::font > m_pfont;
            ::pointer < ::nano::graphics::brush > m_pbrush;
            ::pointer < ::nano::graphics::pen > m_ppen;


            context();
            context(cairo_t * pdc);
            ~context() override;


            void destroy() override;

#ifdef HAS_X11
            void create_for_x11(const ::x11::handle_t & handle, int w, int h) override;
#endif

            void create(const ::i32_size & size) override;
            void resize(const ::i32_size & size) override;
            void attach(void * posdata, const ::i32_size & size, ::i32 iType) override;
            void * detach(::i32 iType) override;
            void set_pen(::nano::graphics::pen * ppen) override;
            void set_brush(::nano::graphics::brush * pbrush) override;
            void set_font(::nano::graphics::font * pfont) override;

            void set_blend_mode(::nano::graphics::enum_blend_mode eblendmode) override;
            void set_smoothing_mode(::nano::graphics::enum_smoothing_mode esmoothingmode) override;
            void set_text_rendering_hint(::nano::graphics::enum_text_rendering_hint etextrenderinghint) override;
            void clear(const ::color::color & color) override;

            void on_begin_draw() override;
            void on_end_draw() override;

            void _draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText,
                            const ::e_draw_text & edrawtext, const ::e_align & ealign) override;
            ::f64_size get_text_extents(const ::scoped_string & scopedstr) override;

            void rectangle(const ::f64_rectangle & rectangle) override;
            void ellipse(const ::f64_rectangle & rectangle) override;
            void line(const ::f64_point & point1, const ::f64_point & point2) override;

            void draw_icon(::f64 x, ::f64 y, ::f64 cx, ::f64 cy, ::nano::graphics::icon * picon) override;
            void draw_image(const ::f64_rectangle & rectangle, ::nano::graphics::image * pimage) override;
            void draw_image(const ::f64_point & point, const ::f64_rectangle & rectangle,
                            ::nano::graphics::image * pimage) override;

            ::pixmap pixmap() override;
            void translate(::f64 x, ::f64 y) override;

            void _set_font();
            void _set_source(const ::color::color & color);
            void _draw_surface(cairo_surface_t * psurface, const ::f64_rectangle & rectangleTarget,
                               const ::f64_rectangle & rectangleSource);


         };


      } // namespace graphics


   } // namespace nano


} // namespace cairo


void operating_system_initialize_cairo_nano(::factory::factory * pfactory);
