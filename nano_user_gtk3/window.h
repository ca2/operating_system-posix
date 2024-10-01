//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/window_base.h"
//#include "event_listener.h"
#include "acme/parallelization/manual_reset_event.h"

#include <gtk/gtk.h>


namespace gtk3
{


   namespace nano
   {
      namespace user
      {

         class CLASS_DECL_ACME window :
            virtual public ::windowing::window_base
         {
         public:


            //::pointer<::x11::nano::user::display>         m_pdisplay;
            //Window                           m_window;
            //Window                           m_windowRoot;
            GtkWidget * m_pgtkwidget;
            GtkWidget *m_pdrawingarea;
            //cairo_surface_t *                m_psurface;
//            ::pointer<::nano::graphics::device>          m_pnanodevice;
//            int                              m_iDepth;
//            XVisualInfo                      m_visualinfo;
//            Visual *                         m_pvisual;
//            Colormap                         m_colormap;
            //::pointer<::nano::graphics::font>         m_pfont;
            //color32_t                     m_colorText;
            //color32_t                     m_colorFocus;
            //color32_t                     m_colorWindow;
            //string                        m_strTitle;
            //bool                          m_bNcActive;
            ::pointer<::nano::graphics::device>           m_pnanodevice;
            manual_reset_event              m_eventEnd;
            //rectangle_i32                 m_rectangle;
            //rectangle_i32                 m_rectangleX;

            //pointer_array < ::nano::user::child >   m_childa;
            //::atom                          m_atomLeftButtonDown;
            //::atom                          m_atomLeftButtonUp;
            //::atom                             m_atomResult;
            //::pointer<::nano::user::child>        m_pchildFocus;


            window();
            ~window() override;


            ::nano::user::display * get_display() override;


            void on_initialize_particle() override;

            void create_window() override;

            void _create_window() override;

            void destroy() override;

            void show_window() override;

            //bool _on_event(XEvent *pevent) override;

            virtual void _update_window();

            //void aaa_message_loop() override;

            //virtual bool aaa_message_loop_step();

            virtual bool _on_button_press(GtkWidget *widget, GdkEventButton *event);
            virtual bool _on_button_release(GtkWidget *widget, GdkEventButton *event);
            virtual bool _on_motion_notify(GtkWidget *widget, GdkEventMotion *event);
            virtual bool _on_enter_notify(GtkWidget *widget, GdkEventCrossing *event);
            virtual bool _on_window_state(GtkWidget* widget, GdkEventWindowState* event);

            virtual void _on_cairo_draw(GtkWidget *widget, cairo_t *cr);
            //void create_window(::user::interaction_impl * pimpl) override;

            virtual void _on_size(int cx, int cy);

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
//            ::nano::user::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;

            //virtual void add_child(::nano::user::child * pchild);

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

            void set_position_unlocked(const ::point_i32 & point) override;

            void set_size_unlocked(const ::size_i32 & size) override;

            void redraw() override;

            //void get_client_rectangle(::rectangle_i32 & rectangle) override;

            rectangle_i32 get_window_rectangle() override;

            void set_mouse_capture() override;

            void release_mouse_capture() override;

            //virtual void _wm_nodecorations(int iMap);

            virtual void __unmap();


            void set_interface_client_size(const ::size_i32 & sizeWindow) ;// set_size
            //::size_i32 get_main_screen_size() override;


         };
      }//namespace user
   }//namespace nano


} // namespace gtk3



