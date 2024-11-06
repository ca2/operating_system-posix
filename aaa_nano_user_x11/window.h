//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "nano_user_x11/window_base.h"
#include "event_listener.h"
#include "acme/parallelization/manual_reset_event.h"

#include <X11/Xutil.h>
#include <cairo/cairo.h>


namespace x11
{


   namespace nano
   {


      namespace user
      {


         class CLASS_DECL_ACME window :
            virtual public ::x11::micro::window_base
         {
         public:


            ::pointer<::x11::acme::windowing::display>        m_pdisplay;
            Window                                       m_window;
            Window                                       m_windowRoot;
            cairo_surface_t *                            m_psurface;
            ::pointer<::nano::graphics::device>          m_pnanodevice;
            int                                          m_iDepth;
            XVisualInfo                                  m_visualinfo;
            Visual *                                     m_pvisual;
            Colormap                                     m_colormap;
            //::pointer<::nano::graphics::font>          m_pfont;
            //color32_t                                  m_colorText;
            //color32_t                                  m_colorFocus;
            //color32_t                                  m_colorWindow;
            //string                                     m_strTitle;
            //bool                                       m_bNcActive;

            manual_reset_event                           m_eventEnd;
            //int_rectangle                              m_rectangle;
            //int_rectangle                              m_rectangleX;

            //pointer_array < ::micro::child >      m_childa;
            //::atom                                     m_atomLeftButtonDown;
            //::atom                                     m_atomLeftButtonUp;
            //::atom                                     m_atomResult;
            //::pointer<::micro::child>          m_pchildFocus;


            window();
            ~window() override;


            ::acme::windowing::display * get_display() override;

            virtual ::x11::acme::windowing::display * x11_display();

            ::x11::handle_t _x11_handle() override;

            void on_initialize_particle() override;

            void create_window() override;

            void _create_window() override;

            void destroy() override;

            void show_window() override;

            bool _on_event(XEvent *pevent);

            virtual void _update_window();

            //void aaa_message_loop() override;

            //virtual bool aaa_message_loop_step();

            virtual void _draw(::nano::graphics::device * pnanodevice);

            //virtual void on_draw(::nano::graphics::device * pnanodevice);

            void on_char(int iChar) override;

            bool is_active_window() override;

            void set_active_window() override;

            ///virtual void draw_children(::nano::graphics::device * pnanodevice);

//            void delete_drawing_objects() override;
//
//            bool get_dark_mode() override;
//
//            void create_drawing_objects() override;
//
//            void update_drawing_objects() override;
//
//            ::micro::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;

            //virtual void add_child(::micro::child * pchild);

//            ::payload get_result() override;
//
//            void on_mouse_move(::user::mouse * pmouse) override;
//
//            void on_left_button_down(::user::mouse * pmouse) override;
//
//            void on_left_button_up(::user::mouse * pmouse) override;
//
//            void on_right_button_down(::user::mouse * pmouse) override;
//
//            void on_right_button_up(::user::mouse * pmouse) override;
//
//            void on_click(const ::payload & payload, ::user::mouse * pmouse) override;
//
//            void on_right_click(const ::payload & payload, ::user::mouse * pmouse) override;

            //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

            //void set_position_unlocked(const ::int_point & point) override;

            void redraw() override;

            //void get_client_rectangle(::int_rectangle & rectangle) override;

            ::int_rectangle get_window_rectangle() override;

            void set_capture() override;

            void release_capture() override;

            virtual void _wm_nodecorations(int iMap);


         };


      }//namespace user


   }//namespace nano


} // namespace x11



