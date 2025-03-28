//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:50
//
#pragma once


#include "acme/user/micro/window_implementation.h"
#include "event_listener.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "window_base.h"


#include <X11/Xutil.h>
#include <cairo/cairo.h>


namespace wayland
{


   namespace nano
   {
      namespace user
      {
         class CLASS_DECL_ACME window :
            virtual public ::micro::window_implementation,
            //virtual public event_listener,
            virtual public window_base
         {
         public:


            //::pointer<class display>         m_pdisplay;
            Window                           m_window;
            Window                           m_windowRoot;
            //cairo_surface_t *              m_psurface;
            ::pointer<::nano::graphics::device>           m_pnanodevice;
            int                              m_iDepth;
            XVisualInfo                      m_visualinfo;
            Visual *                         m_pvisual;
            Colormap                         m_colormap;
            //::pointer<::nano::graphics::font>           m_pfont;
            //color32_t                      m_colorText;
            //color32_t                      m_colorFocus;
            //color32_t                      m_colorWindow;
            //string                         m_strTitle;
            //bool                           m_bNcActive;

            manual_reset_happening               m_happeningEnd;
            //int_rectangle                  m_rectangle;
            //int_rectangle                  m_rectangleX;

            //pointer_array < ::micro::child >   m_childa;
            //::atom                         m_atomLeftButtonDown;
            //::atom                         m_atomLeftButtonUp;
            //::atom                         m_atomResult;
            //::pointer<::micro::child>          m_pchildFocus;
            //::int_size                     m_sizeWindow;
            //::int_size                     m_sizeRequest;


            window();
            ~window() override;


            virtual ::particle * get_interface_client_particle(); // m_pwindow->m_puserinteraction
            virtual void set_window_width(int iWidth); // m_sizeWindow.cx()
            virtual void set_window_height(int iHeight); // m_sizeWindow.cy()
            virtual ::int_size get_window_size(); // m_sizeWindow
            virtual void set_interface_client_size(const ::int_size & sizeWindow); // m_sizeWindow

            virtual bool is_window_stored_iconic(); // m_pwindow->m_puserinteraction->const_layout().window().display() == e_display_iconic
            virtual void window_maximize(); // m_pwindow->m_puserinteraction->display(::e_display_zoomed);
            virtual void window_full_screen(); // m_pwindow->m_puserinteraction->display(::e_display_full_screen);
            virtual void window_restore(); // m_pwindow->m_puserinteraction->display(::e_display_normal);





            ::acme::windowing::display * get_display() override;


            void on_initialize_particle() override;

            void create() override;

            void destroy() override;

            void show_window() override;

            //bool _on_event(XEvent *pevent) override;

            virtual void _update_window();

            //void aaa_message_loop() override;

            //virtual bool aaa_message_loop_step();

            virtual void _draw(::nano::graphics::device * pnanodevice);

            //virtual void on_draw(::nano::graphics::device * pnanodevice);

            void on_char(int iChar) override;

            bool is_active() override;

            void set_active() override;

            ///virtual void draw_children(::nano::graphics::device * pnanodevice);

            void delete_drawing_objects() override;

            bool get_dark_mode() override;

            void create_drawing_objects() override;

            void update_drawing_objects() override;

            ::micro::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;

            //virtual void add_child(::micro::child * pchild);

            ::payload get_result() override;

            void on_mouse_move(::user::mouse * pmouse) override;

            void on_left_button_down(::user::mouse * pmouse) override;

            void on_left_button_up(::user::mouse * pmouse) override;

            void on_right_button_down(::user::mouse * pmouse) override;

            void on_right_button_up(::user::mouse * pmouse) override;

            void on_click(const ::payload & payload, ::user::mouse * pmouse) override;

            void on_right_click(const ::payload & payload, ::user::mouse * pmouse) override;

            //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

            void move_to(const ::int_point & point) override;

            void redraw() override;

            void get_client_rectangle(::int_rectangle & rectangle) override;

            void get_window_rectangle(::int_rectangle & rectangle) override;

            void set_mouse_capture() override;

            void release_mouse_capture() override;

            virtual void _wm_nodecorations(int iMap);


            bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;


            //::int_size get_main_screen_size() override;


            void __handle_pointer_enter(::wl_pointer * pwlpointer) override;
            void __handle_pointer_motion(::wl_pointer * pwlpointer, unsigned int millis) override;
            void __handle_pointer_leave(::wl_pointer * pwlpointer, ::wayland::micro::window_base * pwaylandwindowLeave) override;
            void __handle_pointer_button(::wl_pointer * pwlpointer, unsigned int linux_button, unsigned int pressed, unsigned int millis) override;



         };


      } // namespace user

   } // namespace nano


} // namespace wayland



