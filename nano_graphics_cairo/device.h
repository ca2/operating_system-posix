//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#pragma once


//#include "acme/nano/user/_nano.h"


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


            void on_begin_draw() override;
            void on_end_draw() override;


            void _draw_text(const ::string & strMessage, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack, ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont) override;
            ::size_i32 get_text_extents(const ::string & str, ::nano::graphics::font * pnanofont) override;
            void rectangle(const ::rectangle_i32 & rectangle, ::nano::graphics::brush * pnanobrush, ::nano::graphics::pen * pnanopen) override;

void draw(::nano::graphics::icon * picon, int x, int y, int cx, int cy) override;
            //XColor _alloc_xcolor(const ::color::color & color);
            //void _set_foreground(const ::color::color & color);
            //void _set_background(const ::color::color & color);

            void _set_source(const ::color::color & color);


            virtual void copy_to_pixmap(::pixmap & pixmap);

            //void set_antialias(bool bAntialiasOn);
            void create(int cx, int cy) override;

         };


      } // namespace graphics


   } // namespace nano


} // namespace cairo


void operating_system_initialize_cairo_nano(::factory::factory * pfactory);


