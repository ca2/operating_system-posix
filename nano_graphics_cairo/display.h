//
// Created by camilo on 21/02/2022 23:09 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/micro/display.h"
#include "event_listener.h"
#include "acme/operating_system/x11/_atom.h"


namespace x11
{


   namespace nano
   {
      namespace graphics
      {
         class window;


         class display :
            virtual public ::acme::windowing::display,
            virtual public event_listener
         {
         public:


            bool                                         m_bUnhook;
            Display   *                                  m_pdisplay;
            pointer_array < event_listener >             m_happeninglistenera;
            pointer_array < ::x11::micro::elemental >  m_windowa;
            Window                                       m_windowActive;
            map < enuid(), Atom >                      id()map;


            static display *                             g_p;


            display();
            ~display() override;


            virtual void set_X11_Display(Display * pdisplay);


            bool is_branch_current() const override;


            virtual Atom intern_atom(const_char_pointer pszAtomName, bool bCreate);
            virtual Atom intern_atom(enuid() eatom, bool bCreate);

            virtual Atom _intern_atom_unlocked(const_char_pointer pszAtomName, bool bCreate);
            virtual Atom _intern_atom_unlocked(enuid() eatom, bool bCreate);

            unsigned char * _get_string_property(Display *display, Window window, char *property_name);
            unsigned long _get_long_property(Display *d, Window w, char *property_name);


            virtual Window _get_active_window();


            static Window window_from_name_search(Display *display, Window current, char const *needle, int iOffset = 0, int depth = 1);

            Window window_from_name(char const *name, int iOffset, int depth = 1);


            static display * _nano_get_x11_display(::particle * pparticle, bool bBranch = true, Display * pdisplay = nullptr);

            bool message_loop_step();
            void message_loop();

            void init_task() override;

            void run() override;


            void add_listener(event_listener * plistener);
            void add_window(::x11::micro::elemental * pwindow);

            void erase_listener(event_listener * plistener);
            void erase_window(::x11::micro::elemental * pwindow);

            bool _on_event(XEvent * pevent) override;

            virtual bool x11_event(XEvent * pevent);

            virtual bool x11_posted();

            //void aaa_display_post(const ::procedure & procedure) override;
            //void aaa_display_send(const ::procedure & procedure);
            //bool aaa_display_posted_routine_step();

            ::int_size get_main_screen_size() override;


         };


      } // namespace graphics


   } // namespace nano


} // namespace x11



