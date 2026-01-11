//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#pragma once


#include "acme/prototype/geometry2d/rectangle_array.h"
#include "acme/windowing/display.h"
#include "acme_windowing_x11/_atom.h"
#include <X11/Xlib.h>

#include "happening_listener.h"


namespace x11
{


   namespace acme
   {


      namespace windowing
      {


         class window;


         class CLASS_DECL_ACME_WINDOWING_X11 display :
            virtual public ::acme::windowing::display,
         virtual public ::x11::acme::windowing::happening_listener
         {
         public:


            bool m_bOpened;
            Display* m_pDisplay;
            Window m_windowRoot;
            int m_iScreen;
            bool m_bOwnDisplay;

            bool m_bMouseCaptured;
            Window m_windowActive;
            ::int_rectangle m_rectangleMouseCapture;
            ::int_rectangle_array_base m_rectangleaMonitor;

            bool                                      m_bUnhook;
            //::map<::x11::enum_atom, Atom> m_mapEnumAtom;

            Atom                                         m_atomWmState;
            Atom                                         m_atomNetWmStateFocused;
            Atom                                         m_atomNetWmStateHidden;
            Atom                                         m_atomNetWmStateMaximizedHorz;
            Atom                                         m_atomNetWmStateMaximizedVert;
            Atom                                         m_atomNetWmState;
            Atom                                         m_atomWmProtocols;
            Atom                                         m_atomNetWmSyncRequest;
            Atom                                         m_atomNetWmSyncRequestCounter;

            map < ::x11::enum_atom, Atom >               m_mapAtom;


            pointer_array < happening_listener >         m_happeninglistenera;


            //::task_pointer                               m_ptaskMessageLoop;

            //::pointer < ::manual_reset_happening >       m_pmanualresethappeningDisplayOpen;


            display();
            ~display() override;


            void initialize(::particle * pparticle) override;


            bool is_display_opened() const override;

            //virtual void set_x11_display(::Display * pgdkdisplay);

            virtual void __on_x11_open_display();


            bool is_branch_current() const override;


            void open_display() override;


            bool is_wallpaper_associated_with_dark_mode() override;


            virtual void _enumerate_monitors();


            ::int_size get_main_screen_size() override;


            virtual ::Display* __x11_display();

            virtual ::Window __x11_root_window();

            virtual int __x11_screen();

            virtual Window __x11_get_active_window();


            //virtual ::Display * _get_system_default_display();

            virtual bool __x11_posted();


            //virtual void open();


            //virtual void close();


            void destroy() override;



            //virtual ::Display* _x11_display();


            //virtual ::Display* _x11_display() const;


            virtual Window __x11_focus_window();


            void display_post(const procedure& procedure) override;



            bool is_x11() override;


            bool is_wayland() override;


            virtual Atom intern_atom(const_char_pointer pszAtomName, bool bCreate);
            virtual Atom _intern_atom_unlocked(const_char_pointer pszAtomName, bool bCreate);
            virtual Atom __intern_atom_unlocked(const_char_pointer pszAtomName, bool bCreate);
            virtual Atom intern_atom(::x11::enum_atom eatom, bool bCreate);
            virtual Atom _intern_atom_unlocked(::x11::enum_atom eatom, bool bCreate);
            virtual Atom __x11_atom_wm_state();
            virtual Atom __x11_atom_wm_protocols();
            virtual Atom __x11_atom_net_wm_sync_request();
            virtual Atom __x11_atom_net_wm_sync_request_counter();
            virtual Atom __x11_atom_net_wm_state_focused();
            virtual Atom __x11_atom_net_wm_state_hidden();
            virtual Atom __x11_atom_net_wm_state_maximized_horz();
            virtual Atom __x11_atom_net_wm_state_maximized_vert();
            virtual Atom __x11_atom_net_wm_state();



            virtual void add_listener(happening_listener * plistener);
            virtual void erase_listener(happening_listener * plistener);

            virtual void __message_loop();
            virtual void ____message_loop();
            virtual bool __message_loop_step();
            virtual bool __x11_event(XEvent * pevent);
            virtual bool __on_x11_event(XEvent * pevent);



            virtual unsigned char* _get_string_property(Display * display, Window window, char* property_name);
            virtual unsigned long _get_long_property(Display *d, Window w, char *property_name);



            virtual Window window_from_name_search(Display *display, Window current, char const *needle, int iOffset, int depth = -1);
            virtual Window window_from_name(char const *name, int iOffset, int depth);


            void * _get_x11_display() override;


         };


      } //namespace windowing


   } // namespace acme


} // namespace x11



