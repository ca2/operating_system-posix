//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#pragma once


//#include "acme/user/micro/_nano.h"


#include "acme/nano/graphics/device.h"


#include <cairo/cairo-features.h>
#include <cairo/cairo.h>
//#include <cairo/cairo-ft.h>
//#include <cairo/cairo-xlib.h>


namespace cairo
{


   namespace nano
   {


      namespace graphics
      {


         class CLASS_DECL_ACME device :
            virtual public ::nano::graphics::device
         {
         public:


            cairo_surface_t *    m_psurfaceMemory;
            cairo_t *            m_pdc;


            device();
            device(cairo_t * pdc);
            ~device() override;

#ifdef HAS_X11
            void create_for_x11(const ::x11::handle_t & handle, int w, int h) override;
#endif

            void create(int w, int h) override;


            void resize(const ::int_size & size) override;


            void on_begin_draw() override;
            void on_end_draw() override;


            void _draw_text(const ::string & strMessage, const ::int_rectangle & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack, ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont) override;
            ::int_size get_text_extents(const ::string & str, ::nano::graphics::font * pnanofont) override;
            void rectangle(const ::int_rectangle & rectangle, ::nano::graphics::brush * pnanobrush, ::nano::graphics::pen * pnanopen) override;

void draw(::nano::graphics::icon * picon, int x, int y, int cx, int cy) override;
            //XColor _alloc_xcolor(const ::color::color & color);
            //void _set_foreground(const ::color::color & color);
            //void _set_background(const ::color::color & color);

            void _set_source(const ::color::color & color);


            ::pixmap pixmap() override;

            //void set_antialias(bool bAntialiasOn);
            //void create(int cx, int cy) override;

            void translate(int x, int y) override;


         };


      } // namespace graphics


   } // namespace nano


} // namespace cairo


void operating_system_initialize_cairo_nano(::factory::factory * pfactory);



