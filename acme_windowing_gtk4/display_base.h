//
// Created by camilo on 10/6/23 <3ThomasBorregaardSorensen!!
// From windowing_wayland on 2023-10-06
//
#pragma once


#include "_.h"
//#include "windowing_system_wayland/xkb_input.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/geometry2d/size_array.h"
#include "acme/windowing/display.h"

#include <gtk/gtk.h>


namespace gtk4
{


   namespace acme
   {


      namespace windowing
      {


         //using window_map = map<::GtkWidget*, ::pointer<::gtk4::acme::windowing::window>>;


         class CLASS_DECL_ACME_WINDOWING_GTK4 display_base :
            virtual public ::acme::windowing::display
         {
         public:


            //critical_section m_criticalsectionWindowMap;

            //window_map m_windowmap;

            bool m_bOpened;
            GdkDisplay* m_pgdkdisplay;

            bool m_bOwnDisplay;

            bool m_bMouseCaptured;
            ::int_rectangle m_rectangleMouseCapture;
            ::int_size_array m_sizeaMonitor;

            //::pointer<::gtk4::acme::windowing::window> m_pwindowPointerEnter;
            //::pointer<::gtk4::acme::windowing::window> m_pwindowPointerCapture;
            //::pointer<::gtk4::acme::windowing::window> m_pwindowKeyboardFocus;


            display_base();
            ~display_base() override;


            //static display_base * get(::particle * pparticle, bool bBranch = true, ::GdkDisplay * pgdkdisplay = nullptr);


            void initialize(::particle* pparticle) override;


            virtual ::GdkDisplay* __get_gdk_display();


            virtual void open();


            virtual void close();


            void destroy() override;


            void init_task() override;


            virtual ::GdkDisplay* _gdk_display();


            virtual ::GdkDisplay* _gdk_display() const;


            virtual ::GtkWidget* _gtk_widget_focus();


            void display_post(const procedure& procedure) override;


            // virtual ::gtk4::acme::windowing::window* get_keyboard_focus();
            //
            //
            // virtual ::gtk4::acme::windowing::window* _get_keyboard_focus();
            //
            //
            // virtual ::gtk4::acme::windowing::window* _get_active_window(::thread* pthread);
            //
            //
            //virtual ::gtk4::acme::windowing::window* _window(::GtkWidget* pwlsurface);


            virtual bool message_loop_step();


            //      //void add_listener(event_listener * plistener);
            //      void add_window(nano_window_base * pwindow);
            //
            //      //void erase_listener(event_listener * plistener);
            //      void erase_window(nano_window_base * pwindow);

            //void destroy_wayland_buffer(buffer & waylandbuffer);
            //void update_wayland_buffer(buffer & waylandbuffer, const ::int_size & size);
            //void update_wayland_buffer(buffer & waylandbuffer, ::pixmap * ppixmap);


            //virtual void __handle_pointer_enter(::wl_pointer * pwlpointer, double x, double y, ::wayland::micro::window_base * pwindowPointerEnter);
            // virtual void __handle_pointer_motion(::wl_pointer * pwlpointer, double x, double y, unsigned int time);
            // virtual void __handle_pointer_leave(::wl_pointer * pwlpointer, ::wayland::micro::window_base * pwindowPointerLeave);
            //
            // virtual void __handle_pointer_button(::wl_pointer * pwlpointer, unsigned int linux_button, unsigned int pressed, unsigned int time);
            //

            //virtual void __capture_mouse(::windowing_wayland::window * pwindowMouseCapture, unsigned int serial);


            // virtual void __handle_keyboard_keymap(struct wl_keyboard *keyboard, uint32_t format, int fd, uint32_t size);
            // virtual void __handle_keyboard_enter(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_surface *pwlsurface, ::wl_array *pwlarrayKeys);
            // virtual void __handle_keyboard_leave(::wl_keyboard *pwlkeyboard, uint32_t serial, ::wl_surface *pwlsurface);
            // virtual void __handle_keyboard_key(::wl_keyboard *pwlkeyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state);
            // virtual void __handle_keyboard_modifiers(::wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group);
            //
            // virtual void __handle_wl_output_geometry(::wl_output *pwloutput,
            //                         int32_t x,
            //                         int32_t y,
            //                         int32_t physical_width,
            //                         int32_t physical_height,
            //                         int32_t subpixel,
            //                         const char *make,
            //                         const char *model,
            //                         int32_t transform);
            //
            //
            // virtual void __handle_wl_output_mode(
            //                     ::wl_output *pwloutput,
            //                     uint32_t flags,
            //                     int32_t width,
            //                     int32_t height,
            //                     int32_t refresh);

            virtual void message_loop();


            void run() override;


            // void __handle_pointer_enter(struct wl_pointer * pwlpointer,
            //                      uint32_t serial, struct wl_surface * pwlsurface,
            //                      double x, double y);
            //

            virtual bool is_x11();


            virtual bool is_wayland();

         };
      } // namespace user
   } // namespace nano


} //  namespace gtk4
