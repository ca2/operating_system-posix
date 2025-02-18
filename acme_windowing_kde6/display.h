//
// From acme_windowing_gkt3/display on 2025-01-10 01:18 <3ThomasBorregaardSorensen!!
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme_windowing_q6/display.h"


namespace kde6
{


   namespace acme
   {


      namespace windowing
      {


         class window;

         using window_map = map<::QWidget *, ::pointer<window> >;

         class CLASS_DECL_ACME_WINDOWING_KDE6 display :
      virtual public ::q6::acme::windowing::display //,     virtual public event_listener
         {
         public:


//             bool                                         m_bUnhook;
//             //Display   *                                  m_pdisplay;
//             //pointer_array < event_listener >             m_happeninglistenera;
//             //pointer_array < ::x11::micro::elemental >  m_windowa;
//             //Window                                       m_windowActive;
//             //map < enuid(), Atom >                      id()map;
//
// window_map                                               m_windowmap;
//             //static display *                             g_p;
//

            display();
            ~display() override;
//
//
//             //virtual void set_X11_Display(Display * pdisplay);
//
//
//             bool is_branch_current() const override;
//
//
// //            virtual Atom intern_atom(const char *pszAtomName, bool bCreate);
// //            virtual Atom intern_atom(enuid() eatom, bool bCreate);
// //
// //            virtual Atom _intern_atom_unlocked(const char *pszAtomName, bool bCreate);
// //            virtual Atom _intern_atom_unlocked(enuid() eatom, bool bCreate);
// //
// //            unsigned char * _get_string_property(Display *display, Window window, char *property_name);
// //            unsigned long _get_long_property(Display *d, Window w, char *property_name);
//
//
// //            virtual Window _get_active_window();
// //
// //
// //            static Window window_from_name_search(Display *display, Window current, char const *needle, int iOffset = 0, int depth = 1);
// //
// //            Window window_from_name(char const *name, int iOffset, int depth = 1);
//
//
//             bool message_loop_step();
//             void message_loop();
//
//             void init_task() override;
//
//             void run() override;
//
//
// //            void add_listener(event_listener * plistener);
// //            void add_window(::x11::micro::elemental * pwindow);
// //
// //            void erase_listener(event_listener * plistener);
// //            void erase_window(::x11::micro::elemental * pwindow);
// //
// //            bool _on_event(XEvent * pevent) override;
// //
// //            virtual bool x11_event(XEvent * pevent);
// //
// //            virtual bool x11_posted();
//
//             //void aaa_display_post(const ::procedure & procedure) override;
//             //void aaa_display_send(const ::procedure & procedure);
//             //bool aaa_display_posted_routine_step();
//
//             ::int_size get_main_screen_size() override;
//
//
//             //void release_mouse_capture() override;
//
//             bool is_dark_mode_through_theming() override;
//
//             ::string theming_ui_name() override;
//
//
//             void impl_set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrWallpaper) override;
//
//
//             void impl_set_desktop_theme(const ::scoped_string & scopedstrDesktopTheme) override;
//
//             ::string impl_get_desktop_theme() override;
//
//
//             void set_desktop_icon_theme(const ::scoped_string & scopedtrDesktopIconTheme) override;


         };


         //CLASS_DECL_NANO_USER_X11 display * display_get(::particle * pparticle, bool bBranch = true, Display * pdisplay = nullptr);


      } // namespace windowing


   } // namespace acme


} // namespace kde6



