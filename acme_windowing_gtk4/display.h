//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#pragma once


#include "acme_windowing_g/display.h"
//#include "windowing_system_wayland/xkb_input.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "acme/prototype/geometry2d/size_array.h"
#include "acme/windowing/display.h"

#include <gtk/gtk.h>



//#include "display_base.h"
//#include "event_listener.h"
//#include "windowing_system_x11/_atom.h"


//struct wl_display;


namespace gtk4
{


   namespace acme
   {


      namespace windowing
      {


         class window;


         class CLASS_DECL_ACME_WINDOWING_GTK4 display :
            virtual public ::g::acme::windowing::display
            //virtual public event_listener
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


            bool                                      m_bUnhook;
            //sGdkDisplay*m_pgdkdisplay;
            //::wl_display *                          m_pwldisplay;
            //pointer_array < event_listener >        m_happeninglistenera;
            //pointer_array < nano_window_base >      m_windowa;
            //Window                                  m_windowActive;
            //map_base < enuid(), Atom >                 id()map_base;

            //static display *                          g_pdisplay;


            display();
            ~display() override;


            void initialize(::particle * pparticle) override;


            virtual void set_gdk_display(::GdkDisplay * pgdkdisplay);


            bool is_branch_current() const override;


            //::GdkDisplay * __get_gdk_display() override;


            void open_display() override;


            bool is_wallpaper_associated_with_dark_mode() override;
            //bool is_wallpaper_associated_with_theming() override;


            //virtual Atom intern_atom(const_char_pointer pszAtomName, bool bCreate);
            //virtual Atom intern_atom(enuid() eatom, bool bCreate);

            //virtual Atom _intern_atom_unlocked(const_char_pointer pszAtomName, bool bCreate);
            //virtual Atom _intern_atom_unlocked(enuid() eatom, bool bCreate);

            //unsigned char * _get_string_property(Display *display, Window window, char *property_name);
            //unsigned long _get_long_property(Display *d, Window w, char *property_name);


            //virtual Window _get_active_window();


            //static Window window_from_name_search(Display *display, Window current, char const *needle, int iOffset = 0, int depth = 1);

            //Window window_from_name(char const *name, int iOffset, int depth = 1);


            //bool message_loop_step() override;
            //void aaa_message_loop ();

            //void init_task() override;

            //void run() override;


            //      //void add_listener(event_listener * plistener);
            //      void add_window(nano_window_base * pwindow);
            //
            //      //void erase_listener(event_listener * plistener);
            //      void erase_window(nano_window_base * pwindow);

            //bool _on_event(XEvent * pevent) override;

            //virtual bool aaa_x11_event(XEvent * pevent);

            //virtual bool aaa_x11_posted();

            //void aaa_display_post(const ::procedure & procedure) override;
            //void aaa_display_send(const ::procedure & procedure);
            //bool aaa_display_posted_routine_step();

            ::int_size get_main_screen_size() override;
   //static display_base * get(::particle * pparticle, bool bBranch = true, ::GdkDisplay * pgdkdisplay = nullptr);


            //void initialize(::particle* pparticle) override;


            virtual ::GdkDisplay* __get_gdk_display();


            virtual void open();


            virtual void close();


            void destroy() override;


            //void init_task() override;


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


            //virtual bool message_loop_step();

            //void _set_wallpaper(::collection::index iMonitorIndex, const ::scoped_string & scopedstrWallpaper) override;
            //void enable_wallpaper_change_notification() override;

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
            //                         const_char_pointer make,
            //                         const_char_pointer model,
            //                         int32_t transform);
            //
            //
            // virtual void __handle_wl_output_mode(
            //                     ::wl_output *pwloutput,
            //                     uint32_t flags,
            //                     int32_t width,
            //                     int32_t height,
            //                     int32_t refresh);

            //virtual void message_loop();


            //void run() override;


            // void __handle_pointer_enter(struct wl_pointer * pwlpointer,
            //                      uint32_t serial, struct wl_surface * pwlsurface,
            //                      double x, double y);
            //

            bool is_x11() override;


            bool is_wayland() override;

         };


      } //namespace windowing


   } // namespace acme


} // namespace gtk4



