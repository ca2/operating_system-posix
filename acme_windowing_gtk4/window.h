//
// Created by camilo on 10/5/23 <3ThomasBorregaardSorensen!!
// Wayland implementation incoming from windowing_wayland on 2023-10-06
// For nano_user_gtk4 by camilo on 2024-09-23 21:38 <3ThomasBorreggaardSorensen!!ss
//
//
// Created by camilo on 2024-09-16 10:22 <3ThomasBorregaardSorensen!!
// Merged gtk4_widget...
//
// window(1) Created by camilo on 31/01/2022 15:38 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:50
// Merged window(1) by camilo on 2024-09-26 18:23 <3ThomasBorregaardSorensen!!
//

#pragma once


#include "_.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/windowing/window.h"
//#include "micro_window.h"


#include <gtk/gtk.h>
//#include <gdk/x11/gdkx.h>
//#include <X11/Xlib.h>


namespace gtk4
{


   namespace acme
   {


      namespace windowing
      {


         class window :
            //virtual public ::x11::micro::window_base
            virtual public ::acme::windowing::window

         {
         public:


            //::pointer<class display_base>         m_pdisplaybase;
            GtkWidget*m_pgtkwidget;
            bool m_bInhibitQueueDraw;

            //cairo_surface_t *m_pcairosurface;
            //
            // xdg_toplevel_resize_edge m_resizeedge;
            // buffer m_buffer;
            // ::wl_surface * m_pwlsurface;
            // ::wl_subsurface * m_pwlsubsurface;
            // ::xdg_surface * m_pxdgsurface;
            // ::xdg_toplevel * m_pxdgtoplevel;
            // ::xdg_popup * m_pxdgpopup;
            // ::xdg_positioner * m_pxdgpositioner;
            // ::wl_pointer * m_pwlpointer;
            // ::wl_shm_pool * m_pwlshmpool;
            // ::int_point m_pointWindowBestEffort;
            // ::xdg_activation_token_v1 * m_pxdgactivationtokenv1;
            // ::wl_callback * m_pwlcallbackFrame;
            // ::int_size m_sizeDrag;
            //
            // unsigned int m_uLastConfigureSerial;
            // unsigned int m_uLastRequestSerial;
            // unsigned int m_uLastAckSerial;
            // ::string m_strActivationToken;
            // ::int_size                                      m_sizeConfigure;
            // class ::time                                 m_timeLastConfigureRequest;
            // bool                                         m_bXdgInitialConfigure;
            // bool                                            m_bDoneFirstMapping;
            GtkWidget *                                  m_pdrawingarea;
            GtkGesture *                                 m_pgtkgestureClick;
            GtkEventController *                         m_pgtkeventcontrollerMotion;
            /* Create a key happening controller */
            GtkEventController *m_pgtkeventcontrollerKey;
            GtkEventController *m_pgtkeventcontrollerScroll;

            bool                                                  m_bMessageOnlyWindow;
            bool                                                  m_bHasKeyboardFocus;
            ::int_size                                            m_sizeOnSizeRestored;
            ::int_size                                            m_sizeOnSizeZoomed;
            ::int_size                                            m_sizeOnSize;


bool m_bHasFocusCached;
            bool m_bIsActiveCached;
                        //::pointer<class display>         m_pdisplay;
                        //GtkWidget *m_pgtkwidget;
                        //Window                           m_windowRoot;
                        //cairo_surface_t *              m_psurface;
                        ::pointer<::nano::graphics::device>           m_pnanodevice;
                        //int                              m_iDepth;
                        //XVisualInfo                      m_visualinfo;
                        //Visual *                         m_pvisual;
                        //Colormap                         m_colormap;
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


                        //window();
                        //~window() override;



            window();
            ~window() override;
virtual ::gtk4::acme::windowing::windowing * gtk4_acme_windowing();

            void create_window() override;
            void _create_window() override;


            void _enable_mouse_wheel_messages();


            virtual void _destroy_window();
            void destroy_window() override;

            void destroy() override;


            //virtual ::particle * get_interface_client_particle() = 0; // m_pwindow->m_puserinteraction
            //virtual void set_window_width(int iWidth) = 0; // m_sizeWindow.cx()
            //virtual void set_window_height(int iHeight) = 0; // m_sizeWindow.cy()
            //virtual ::int_size get_window_size() = 0; // m_sizeWindow
            void set_interface_client_size(const ::int_size & sizeWindow) override; // m_sizeWindow

            bool is_window_stored_iconic() override; // m_pwindow->m_puserinteraction->const_layout().window().display() == e_display_iconic
            bool is_window_zoomed() override; // m_pwindow->m_puserinteraction->const_layout().window().display() == e_display_iconic
            void window_minimize() override;
            void window_maximize() override; // m_pwindow->m_puserinteraction->display(::e_display_zoomed);
            void window_full_screen() override; // m_pwindow->m_puserinteraction->display(::e_display_full_screen);
            void window_restore() override; // m_pwindow->m_puserinteraction->display(::e_display_normal);


            void on_window_deiconified() override;
            void on_window_activated() override;
            void on_window_iconified() override;
            void on_window_deactivated() override;


            virtual void __activate_window(bool bNormalPriority);

            virtual void __map();

            virtual void __unmap();

            virtual void _on_window_is_active_change(bool bIsActive);
virtual void _on_focus_changed(bool bHasFocus);

            virtual void _on_button_pressed(GtkGestureClick* pgesture, int n_press, double x, double y);

            virtual void _on_button_released(GtkGestureClick* pgesture, int n_press, double x, double y);

            virtual void _on_button_stopped(GtkGestureClick* pgesture);

            virtual void _on_motion_notify(GtkEventControllerMotion* pcontroller, double x, double y);

            virtual void _on_enter_notify(GtkEventControllerMotion* pcontroller, double x, double y);

            virtual void _on_window_visibility_changed(GObject* object, GParamSpec* pspec);

            virtual void _on_cairo_draw(GtkWidget *widget, cairo_t *cr);

            void _on_size(int cx, int cy) override;

            virtual void _on_toplevel_compute_size(GdkToplevel * self, GdkToplevelSize* size);

            virtual void _on_display_change(::e_display edisplay);

            virtual void _on_window_map();

            virtual bool _on_gtk_key_pressed(GtkEventControllerKey *controller, guint keyval, guint keycode, GdkModifierType state);
            virtual bool _on_gtk_key_released(GtkEventControllerKey *controller, guint keyval, guint keycode, GdkModifierType state);

            virtual void _on_gtk_key_pressed(unsigned long long uGtkKey, unsigned long long uGtkKeyCode);
            virtual void _on_gtk_key_released(unsigned long long uGtkKey, unsigned long long uGtkKeyCode);

            virtual bool _on_gtk_scroll(GtkEventControllerScroll * peventcontrollerScroll, double dx, double dy);

            //virtual gboolean _on_gtk_key_press(GtkWidget *widget, GdkEvent *happening);

            virtual void _on_text(const ::scoped_string & scopedstr);

            // virtual void __handle_pointer_enter(::wl_pointer * pwlpointer);
            // virtual void __handle_pointer_motion(::wl_pointer * pwlpointer, unsigned int millis);
            // virtual void __handle_pointer_leave(::wl_pointer * pwlpointer, ::wayland::micro::window_base * pwaylandwindowLeave);
            // virtual void __handle_pointer_button(::wl_pointer * pwlpointer, unsigned int linux_button, unsigned int pressed, unsigned int millis);


            // virtual void __defer_update_wayland_buffer();
            //
            // virtual void __handle_xdg_surface_configure(unsigned int serial);
            //
            // virtual void __handle_xdg_toplevel_configure(int width, int height, ::wl_array * pwlarrayState);
            //
            // virtual void __defer_xdg_surface_ack_configure();
            virtual void _on_window_button_pressed(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture, int n_press, double x, double y);
            virtual void _on_window_button_released(::operating_system::a_system_menu_item * pitem, GtkGestureClick * pgesture, int n_press, double x, double y);

            void defer_show_system_menu(::user::mouse * pmouse) override;


            virtual void _gtk_show_system_menu(int x, int y);


            //virtual bool _perform_entire_reposition_process();

            //virtual bool _perform_entire_resizing_process(::experience::enum_frame eframeSizing);

            bool defer_perform_entire_reposition_process(::user::mouse * pmouse) override;

            bool defer_perform_entire_resizing_process(::experience::enum_frame eframeSizing, ::user::mouse * pmouse) override;


            GMenu* _create_system_menu();
            // virtual void _on_window_simple_action(const_char_pointer pszActionName);


            //void on_destruct_mouse_message(::message::mouse * pmouse) override;


            // virtual void __handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_array *pwlarrayKeys);
            // virtual void __handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial);
            // virtual void __handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
            // virtual void __handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);

            ::gtk4::acme::windowing::display * gtk4_display();

            virtual void _on_simple_key_message(::user::e_key ekey, ::user::enum_message emesssage);
            virtual void _on_text_composition(const ::scoped_string & scopedstrText);
            void _on_windowing_close_window() override;


            virtual void _on_geometry_change();
            virtual void _on_size_allocate(GtkWidget * pwidget, GdkRectangle * prectangle);
            //virtual void _on_x11_configure_notify(XConfigureEvent * pconfigurehappening);


            virtual void _defer_get_window_rectangle_unlocked();
            //void _defer_translate_to_absolute_coordinates_unlocked(::int_point & point) override;

            virtual void _update_window();

            virtual void _on_window_realize();

            bool is_window_visible() override;


            virtual ::particle * get_interface_client_particle(); // m_pwindow->m_puserinteraction
            virtual void set_window_width(int iWidth); // m_sizeWindow.cx()
            virtual void set_window_height(int iHeight); // m_sizeWindow.cy()
            virtual ::int_size get_window_size(); // m_sizeWindow
            // virtual void set_interface_client_size(const ::int_size & sizeWindow); // m_sizeWindow
            //
            // virtual bool is_window_stored_iconic(); // m_pwindow->m_puserinteraction->const_layout().window().display() == e_display_iconic
            // virtual void window_maximize(); // m_pwindow->m_puserinteraction->display(::e_display_zoomed);
            // virtual void window_full_screen(); // m_pwindow->m_puserinteraction->display(::e_display_full_screen);
            // virtual void window_restore(); // m_pwindow->m_puserinteraction->display(::e_display_normal);





            ::acme::windowing::display * get_display() override;


            //::x11::handle_t _x11_handle() override;


            void on_initialize_particle() override;

            //void create_window() erride;

            //void destroy() override;

            void show_window() override;

            void hide_window() override;

            //bool _on_event(XEvent *pevent) override;

            //virtual void _update_window();

            //void aaa_message_loop() override;

            //virtual bool aaa_message_loop_step();

            //virtual void _draw(::nano::graphics::device * pnanodevice);

            //void _on_cairo_draw(GtkWidget *widget, cairo_t *cr) override;

            //virtual void on_draw(::nano::graphics::device * pnanodevice);

            virtual void on_char(int iChar);

            bool is_active_window() override;

            void set_active_window() override;

            ///virtual void draw_children(::nano::graphics::device * pnanodevice);

            //void delete_drawing_objects() override;

            //bool get_dark_mode() override;

            //void create_drawing_objects() override;

            //void update_drawing_objects() override;

            //::micro::child * hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder) override;

            //virtual void add_child(::micro::child * pchild);

            //::payload get_result() override;


            //void _on_size(int cx, int cy) override;


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

            //virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

            //void move_to(const ::int_point & point) override;

            void redraw() override;

            // void get_client_rectangle(::int_rectangle & rectangle) override;
            //
            // void get_window_rectangle(::int_rectangle & rectangle) override;

            void set_mouse_capture() override;

            void release_mouse_capture() override;

            virtual void _wm_nodecorations(int iMap);


            //bool defer_perform_entire_reposition_process(::user) override;


            //::int_size get_main_screen_size() override;


            // void __handle_pointer_enter(::wl_pointer * pwlpointer) override;
            // void __handle_pointer_motion(::wl_pointer * pwlpointer, unsigned int millis) override;
            // void __handle_pointer_leave(::wl_pointer * pwlpointer, ::wayland::micro::window_base * pwaylandwindowLeave) override;
            // void __handle_pointer_button(::wl_pointer * pwlpointer, unsigned int linux_button, unsigned int pressed, unsigned int millis) override;


            // void _on_button_pressed(GtkGestureClick* pgesture, int n_press, double x, double y) override;
            // void _on_button_released(GtkGestureClick* pgesture, int n_press, double x, double y) override;
            // void _on_motion_notify(GtkEventControllerMotion* pcontroller, double x, double y) override;
            // void _on_enter_notify(GtkEventControllerMotion* pcontroller, double x, double y) override;

            ::int_rectangle get_window_rectangle_unlocked() override;
            void set_position_unlocked(const ::int_point & point) override;


         };


      } // namespace windowing


   }// namespace acme


} // namespace gtk4



