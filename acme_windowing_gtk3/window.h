//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/window.h"
//#include "event_listener.h"
#include "acme/parallelization/manual_reset_happening.h"

#include <gtk/gtk.h>


namespace gtk3
{


   namespace acme
   {


      namespace windowing
      {


         class CLASS_DECL_ACME_WINDOWING_GTK3 window :
            virtual public ::acme::windowing::window
         {
         public:


           bool m_bHasFocusCached;

            //::pointer<::x11::acme::windowing::display>         m_pdisplay;
            //Window                           m_window;
            //Window                           m_windowRoot;
            //bool m_bLeftButtonDown;
            GtkWidget * m_pgtkwidget;
            GtkWidget *m_pdrawingarea;
            GtkWidget * m_pgtkwidgetSystemMenu;
            GdkEventButton * m_phappeningLastMouseDown;
            GdkEventButton * m_phappeningLastMouseUp;
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
            manual_reset_happening              m_happeningEnd;
            //int_rectangle                 m_rectangle;
            //int_rectangle                 m_rectangleX;


            ::int_rectangle                     __m_rectangleRequest;

            int                                 __m_iAttemptToSetSize;
            int                                 __m_iAttemptToSetPosition;

            //pointer_array < ::micro::child >   m_childa;
            //::atom                          m_atomLeftButtonDown;
            //::atom                          m_atomLeftButtonUp;
            //::atom                             m_atomResult;
            //::pointer<::micro::child>        m_pchildFocus;
            bool m_bGtkWindowMapped;


            window();
            ~window() override;


            ::acme::windowing::display * get_display() override;


            void on_initialize_particle() override;

            void create_window() override;

            void _create_window() override;

            void destroy() override;

            virtual void _destroy_window();

            void destroy_window() override;

            void show_window() override;

            void set_mouse_capture() override;

            void release_mouse_capture() override;

            //bool _on_event(XEvent *pevent) override;

            virtual void _update_window();

            //void aaa_message_loop() override;

            //virtual bool aaa_message_loop_step();

            virtual bool _on_button_press(GtkWidget *widget, GdkEventButton *happening);
            virtual bool _on_button_release(GtkWidget *widget, GdkEventButton *happening);
            virtual bool _on_motion_notify(GtkWidget *widget, GdkEventMotion *happening);
            virtual bool _on_enter_notify(GtkWidget *widget, GdkEventCrossing *happening);
            virtual bool _on_window_state(GtkWidget* widget, GdkEventWindowState* happening);

            virtual bool _on_focus_in(GtkWidget *widget, GdkEventFocus *event);
            virtual bool _on_focus_out(GtkWidget *widget, GdkEventFocus *event);
            virtual bool _on_key_press(GtkWidget *widget, GdkEventKey *event);
            virtual bool _on_key_release(GtkWidget *widget, GdkEventKey *event);

            virtual bool _on_gtk_scroll(GtkWidget *widget, GdkEventScroll * pscroll);

            virtual void _on_cairo_draw(GtkWidget *widget, cairo_t *cr);
            //void create_window(::windowing::window * pimpl) override;

            virtual void _on_configure(int x, int y, int cx, int cy);

            virtual void _draw(::nano::graphics::device * pnanodevice);

            virtual void _on_a_system_menu_item_button_press(::operating_system::a_system_menu_item * pitem, GtkWidget * pwidget, GdkEventButton * peventbutton);


            //virtual void on_draw(::nano::graphics::device * pnanodevice);

            //void on_char(int iChar) override;

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

            void set_position_unlocked(const ::int_point & point) override;

            void set_size_unlocked(const ::int_size & size) override;

            void redraw() override;

            //void get_client_rectangle(::int_rectangle & rectangle) override;

            int_rectangle get_window_rectangle() override;

            //void set_mouse_capture() override;

            //void release_mouse_capture() override;

            //virtual void _wm_nodecorations(int iMap);

            virtual void __unmap();

            void defer_show_system_menu(::user::mouse * pmouse) override;


            void set_interface_client_size(const ::int_size & sizeWindow) ;// set_size
            //::int_size get_main_screen_size() override;

            //void on_a_system_menu_item(::operating_system::a_system_menu_item * psystemmenuitem);

            virtual void _on_map_window();
            virtual void _on_unmap_window();

            bool is_window_zoomed() override;
            void window_minimize() override;
            void window_maximize() override;
            void hide_window() override;

            virtual void _on_configure();

            //virtual void _on_configure_default();

            //virtual void _on_configure_linux_mint_x_cinnamon();

			virtual void _enable_mouse_wheel_messages();
         };


      }//namespace windowing


   }//namespace acme


} // namespace gtk3



