//
// Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/operating_system/x11/_.h"
#include "acme/windowing/window.h"
#include "acme/parallelization/manual_reset_happening.h"

#include <X11/Xutil.h>
#include <cairo/cairo.h>

#include "happening_listener.h"


namespace x11
{


   namespace acme
   {


      namespace windowing
      {


         class x11data :
            virtual public ::particle
         {
         public:

            XWindowAttributes m_attr;
            //GdkWindow *                   m_pgdkwindow;

         };




         class CLASS_DECL_ACME_WINDOWING_X11 window :
            virtual public ::acme::windowing::window,
            virtual public ::x11::acme::windowing::happening_listener
         {
         public:


            ::pointer<::x11::acme::windowing::display>   m_px11display;
            ::pointer<::x11::acme::windowing::x11data>   m_px11data;
            Window                                       m_window;
            Window                                       m_windowRoot;
            cairo_surface_t *                            m_psurface;
            ::pointer<::nano::graphics::device>          m_pnanodevice;
            int                                          m_iDepth;
            //XVisualInfo                                  m_visualinfo;
            //Visual *                                     m_pvisual;
            Colormap                                     m_colormap;
            XWindowAttributes                            m_attr;
            XVisualInfo                                  m_visualinfo;
            ::Visual *                                   m_pvisual;
            //int                                          m_iDepth;
            //::pointer<::nano::graphics::font>          m_pfont;
            //color32_t                                  m_colorText;
            //color32_t                                  m_colorFocus;
            //color32_t                                  m_colorWindow;
            //string                                     m_strTitle;
            //bool                                       m_bNcActive;

            manual_reset_happening                       m_happeningEnd;
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

            virtual ::x11::handle_t _x11_handle();

            virtual Display * __x11_display();
            virtual Window __x11_window();
            long __x11_Window() override;
            void * __x11_Display() override;
            //virtual int __x11_screen();


            void on_initialize_particle() override;

            void create_window() override;

            void _create_window() override;

            void destroy() override;

            void show_window() override;

            bool __on_x11_event(XEvent *pevent) override;

            virtual void _update_window();


            //void aaa_message_loop() override;

            //virtual bool aaa_message_loop_step();

            virtual void _draw(::nano::graphics::device * pnanodevice);

            //virtual void on_draw(::nano::graphics::device * pnanodevice);

            virtual void on_char(int iChar);

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


            virtual void set_foreground_window();
            virtual void _set_foreground_window_unlocked();


            virtual bool has_mouse_capture() const;

            virtual bool has_keyboard_focus() const;



            void set_mouse_capture() override;

            void release_mouse_capture() override;

            virtual void _wm_nodecorations(int iMap);

            //bool window::_get_wm_state_unlocked(long &lState);
            virtual bool get_state(long & lState);
            virtual bool _get_wm_state_unlocked(long & lState);
            virtual comparable_array<Atom> _wm_get_list_unlocked(Atom atomList);
            virtual ::comparable_array<Atom> _get_net_wm_state_unlocked();
            virtual int _wm_test_list_unlocked(Atom atomList, Atom atomFlag);
            virtual int _wm_test_state_unlocked(const_char_pointer pszNetStateFlag);
            virtual int wm_test_state(const_char_pointer pszNetStateFlag);
            virtual bool _wm_add_erase_list_unlocked(Atom atomList, Atom atomFlag, bool bSet);

            virtual void _on_cairo_draw(cairo_t *cr);

            virtual void _user_send(const ::procedure & procedure) override;
            virtual void _user_post(const ::procedure & procedure) override;
            virtual void _main_send(const ::procedure & procedure) override;
            virtual void _main_post(const ::procedure & procedure) override;


            //virtual void _draw(::nano::graphics::device * pnanodevice);



         };


      }//namespace windowing


   }//namespace acme


} // namespace x11



