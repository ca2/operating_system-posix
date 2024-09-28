//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/window_base.h"
#include "event_listener.h"
#include "acme/parallelization/manual_reset_event.h"
#include <QWidget>


namespace kde5
{


   namespace nano
   {


      namespace user
      {


         class CLASS_DECL_NANO_USER_KDE5 window :
            virtual public ::windowing::window_base
            //,           virtual public event_listener
         {
         public:


            QWidget *                                 m_pqwidget;

            ::pointer<class display>                  m_pdisplay;
            //xcb_window_t                    m_window;
            //cairo_surface_t *               m_psurface;
            ::pointer<::nano::graphics::device>       m_pnanodevice;
            //::pointer<::nano::graphics::font>         m_pfont;
            //color32_t                     m_colorText;
            //color32_t                     m_colorFocus;
            //color32_t                     m_colorWindow;
            //string                        m_strTitle;
            //bool                          m_bNcActive;

            manual_reset_event                        m_eventEnd;
            //rectangle_i32                 m_rectangle;
            //rectangle_i32                 m_rectangleX;

            //pointer_array < ::nano::user::child >   m_childa;
            //::atom                          m_atomLeftButtonDown;
            //::atom                          m_atomLeftButtonUp;
            //::atom                             m_atomResult;
            //::pointer<::nano::user::child>        m_pchildFocus;

            ::array < QAction * >                     m_qactiona;


            window();
            ~window() override;


            ::nano::user::display * get_display() override;


            void on_initialize_particle() override;

            void create_window() override;

            void _create_window() override;

            void destroy() override;

            void show_window() override;

            //bool _on_event(xcb_generic_event_t *pevent) override;

            virtual void _update_window();

            ::e_status _map_window();
            ::e_status _unmap_window();

            ::e_status _raise_window();


            virtual void _on_mouse_press(QMouseEvent * pevent);
            virtual void _on_mouse_release(QMouseEvent * pevent);
            virtual void _on_mouse_motion(QMouseEvent * pevent);
            virtual void _on_qimage_draw(QImage * pqimage);
            virtual void _on_size(int cx, int cy);


            //void aaa_message_loop() override;

            //virtual bool aaa_message_loop_step();

            virtual void _draw(::nano::graphics::device * pnanodevice);

            //virtual void on_draw(::nano::graphics::device * pnanodevice);

            void on_char(int iChar) override;

            bool is_active_window() override;

            void set_active_window() override;

            ///virtual void draw_children(::nano::graphics::device * pnanodevice);

            // void delete_drawing_objects() override;
            //
            // bool get_dark_mode() override;
            //
            // void create_drawing_objects() override;
            //
            // void update_drawing_objects() override;

            //::nano::user::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;

            //virtual void add_child(::nano::user::child * pchild);

            //::payload get_result() override;

            // void on_mouse_move(::user::mouse * pmouse) override;
            //
            // void on_left_button_down(::user::mouse * pmouse) override;
            //
            // void on_left_button_up(::user::mouse * pmouse) override;
            //
            // void on_right_button_down(::user::mouse * pmouse) override;
            //
            // void on_right_button_up(::user::mouse * pmouse) override;
            //
            // void on_click(const ::payload & payload, ::user::mouse * pmouse) override;
            //
            // void on_right_click(const ::payload & payload, ::user::mouse * pmouse) override;
            //
            // //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);


            void set_interface_client_size(const ::size_i32 & sizeWindow) override;

            void set_position(const ::point_i32 & point) override;

            void redraw() override;

            //void get_client_rectangle(::rectangle_i32 & rectangle) override;

            ::rectangle_i32 get_window_rectangle() override;

            void set_capture() override;

            void release_capture() override;

            //virtual void _wm_nodecorations(int iMap);

            //virtual void _get_geometry(xcb_get_geometry_reply_t * pgeometry);


            //::size_i32 get_main_screen_size() override;
            void defer_show_system_menu(::user::mouse *pmouse) override;


         };
      }//namespace user
   }//namespace nano


} // namespace kde5



