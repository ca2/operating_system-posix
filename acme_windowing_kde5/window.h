//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme_windowing_q5/window.h"
//#include "micro_window.h"
#include "acme/parallelization/manual_reset_happening.h"
#include <QWidget>


namespace kde5
{


   namespace acme
   {


      namespace windowing
      {


         class CLASS_DECL_ACME_WINDOWING_KDE5 window :
            virtual public ::q5::acme::windowing::window//,
        //virtual public ::kde5::micro::window
         {
         public:


      //      QWidget *                                 m_pqwidget;
           // QWindow *                                    m_pqwindow;

            //::pointer<class display>                  m_pdisplay;
            //xcb_window_t                    m_window;
            //cairo_surface_t *               m_psurface;
    //        ::pointer<::nano::graphics::device>       m_pnanodevice;
            //::pointer<::nano::graphics::font>         m_pfont;
            //color32_t                     m_colorText;
            //color32_t                     m_colorFocus;
            //color32_t                     m_colorWindow;
            //string                        m_strTitle;
            //bool                          m_bNcActive;

  //          manual_reset_happening                        m_happeningEnd;
            //int_rectangle                 m_rectangle;
            //int_rectangle                 m_rectangleX;

            //pointer_array < ::micro::child >   m_childa;
            //::atom                          m_atomLeftButtonDown;
            //::atom                          m_atomLeftButtonUp;
            //::atom                             m_atomResult;
            //::pointer<::micro::child>        m_pchildFocus;

//            ::array < QAction * >                     m_qactiona;


            window();
            ~window() override;


            ::acme::windowing::display * get_display() override;


            void on_initialize_particle() override;

            void create_window() override;

            void _create_window() override;

            void destroy() override;

            void show_window() override;

            //bool _on_event(xcb_generic_event_t *pevent) override;

            void _update_window() override;

            ::e_status _map_window();
            ::e_status _unmap_window();

            ::e_status _raise_window();


            void _on_mouse_press(QMouseEvent * pevent) override;
            void _on_mouse_release(QMouseEvent * pevent) override;
            void _on_mouse_motion(QMouseEvent * pevent) override;
            void _on_qimage_draw(QImage * pqimage) override;
            void _on_reposition(int x, int y) override;
            void _on_size(int cx, int cy) override;

            void _on_key_press(QKeyEvent * pevent) override;
            void _on_key_release(QKeyEvent * pevent) override;

            //void aaa_message_loop() override;

            //virtual bool aaa_message_loop_step();

            void _draw(::nano::graphics::device * pnanodevice) override;

            //virtual void on_draw(::nano::graphics::device * pnanodevice);

            void _on_character(int iChar) override;

            bool is_active_window() override;

            void set_active_window() override;



            bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

            bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;


            ///virtual void draw_children(::nano::graphics::device * pnanodevice);

            // void delete_drawing_objects() override;
            //
            // bool get_dark_mode() override;
            //
            // void create_drawing_objects() override;
            //
            // void update_drawing_objects() override;

            //::micro::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;

            //virtual void add_child(::micro::child * pchild);

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


            void set_interface_client_size(const ::int_size & sizeWindow) override;

            void set_position_unlocked(const ::int_point & point) override;

            void set_size_unlocked(const ::int_size & size) override;

            void redraw() override;

            //void get_client_rectangle(::int_rectangle & rectangle) override;

            ::int_rectangle get_window_rectangle() override;

            // void set_mouse_capture() override;

            // void release_mouse_capture() override;

            //virtual void _wm_nodecorations(int iMap);

            //virtual void _get_geometry(xcb_get_geometry_reply_t * pgeometry);


            //::int_size get_main_screen_size() override;
            void defer_show_system_menu(::user::mouse *pmouse) override;

            //void set_mouse_capture() override;
            //bool is_mouse_captured() override;
            //bool has_mouse_capture() override;
            //void release_mouse_capture() override;


            using ::acme::windowing::window::set_keyboard_focus;
            void set_keyboard_focus() override;
            bool has_keyboard_focus() override;

         };


      } //namespace windowing


   } //namespace acme


} // namespace kde5



