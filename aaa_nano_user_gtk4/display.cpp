
//
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSorensen!!
// Modified 2023-10-05 23:51
//
#include "framework.h"
#include "display.h"
#include "window.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/system.h"
//#include "acme/prototype/geometry2d/rectangle.h"
//#include "acme/user/micro/window.h"


//#include "windowing_system_x11/_.h"


#define MAXSTR 1000


void x11_init_threads();
//void * x11_get_display();


void set_main_user_thread();


namespace gtk4
{


   //display * display::g_p = nullptr;

namespace nano
{
   namespace user
   {
      display::display()
      {

         m_pgdkdisplay = nullptr;

         m_bUnhook = false;

         //      if(!g_p)
         //      {
         //
         //         g_p = this;
         //
         //      }

         defer_create_synchronization();

         m_bOwnDisplay = false;


      }


      display::~display()
      {


         if(m_bOwnDisplay && m_pgdkdisplay != nullptr)
         {

            //wl_display_disconnect(m_pwldisplay);

            m_pgdkdisplay = nullptr;

            m_bOwnDisplay = false;

            printf("disconnected from display\n");

         }

      }


      void display::initialize(::particle * pparticle)
      {

         ::acme::windowing::display::initialize(pparticle);

         ::gtk4::acme::windowing::display_base::initialize(pparticle);

      }


      //   Atom display::intern_atom(const char *pszAtomName, bool bCreate)
      //   {
      //
      //      return _intern_atom_unlocked(scopedstrAtomName, bCreate);
      //
      ////      if (m_pdisplay == nullptr)
      ////      {
      ////
      ////         return 0;
      ////
      ////      }
      ////
      ////      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
      ////
      ////      if (atom == None)
      ////      {
      ////
      ////         windowing_output_debug_string("ERROR: cannot find atom for " + string(scopedstrAtomName) + "\n");
      ////
      ////         return None;
      ////
      ////      }
      ////
      ////      return atom;
      //
      //   }
      //
      //
      //   Atom display::intern_atom(enuid() eatom, bool bCreate)
      //   {
      //
      //      return _intern_atom_unlocked(eatom, bCreate);
      //
      ////      if (eatom < 0 || eatom >= e_atom_count)
      ////      {
      ////
      ////         return None;
      ////
      ////      }
      ////
      ////      Atom atom = id()map[eatom];
      ////
      ////      if (atom == None)
      ////      {
      ////
      ////         atom = intern_atom(atom_name(eatom), bCreate);
      ////
      ////         id()map[eatom] = atom;
      ////
      ////      }
      ////
      ////      return atom;
      //
      //   }
      //
      //
      //
      //   Atom display::_intern_atom_unlocked(const char *pszAtomName, bool bCreate)
      //   {
      //
      //      if (m_pdisplay == nullptr)
      //      {
      //
      //         return 0;
      //
      //      }
      //
      //      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
      //
      //      if (atom == None)
      //      {
      //
      //         windowing_output_debug_string("ERROR: cannot find atom for " + string(scopedstrAtomName) + "\n");
      //
      //         return None;
      //
      //      }
      //
      //      return atom;
      //
      //   }
      //
      //
      //   Atom display::_intern_atom_unlocked(enuid() eatom, bool bCreate)
      //   {
      //
      //      if (eatom < 0 || eatom >= e_atom_count)
      //      {
      //
      //         return None;
      //
      //      }
      //
      //      Atom atom = id()map[eatom];
      //
      //      if (atom == None)
      //      {
      //
      //         atom = _intern_atom_unlocked(atom_name(eatom), bCreate);
      //
      //         id()map[eatom] = atom;
      //
      //      }
      //
      //      return atom;
      //
      //   }
      //
      //
      //   unsigned char* display::_get_string_property(Display * display, Window window, char* property_name)
      //   {
      //
      //      unsigned char * prop;
      //      Atom actual_type, filter_atom;
      //      int actual_format, status;
      //      unsigned long nitems, bytes_after;
      //
      //      filter_atom = XInternAtom(display, property_name, True);
      //
      //      status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
      //                                  &actual_type, &actual_format, &nitems, &bytes_after, &prop);
      //
      //      x11_check_status(status, window);
      //
      //      return prop;
      //
      //   }
      //
      //
      //   unsigned long display::_get_long_property(Display *d, Window w, char *property_name)
      //   {
      //
      //      unsigned char *prop = _get_string_property(d, w, property_name);
      //
      //      unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);
      //
      //      XFree(prop);
      //
      //      return long_property;
      //
      //   }
      //
      //
      //   Window display::_get_active_window()
      //   {
      //
      //      int screen = XDefaultScreen(m_pdisplay);
      //
      //      Window windowRoot = RootWindow(m_pdisplay, screen);
      //
      //      Window window = _get_long_property(m_pdisplay, windowRoot, (char *) "_NET_ACTIVE_WINDOW");
      //
      //      return window;
      //
      //   }


      //   Window display::window_from_name_search(Display *display, Window current, char const *needle, int iOffset, int depth)
      //   {
      //
      //      Window window, root, parent, *children;
      //
      //      unsigned children_count;
      //
      //      char *name = NULL;
      //
      //      window = 0;
      //
      //      /* If it does not: check all subwindows recursively. */
      //      if(0 != XQueryTree(display, current, &root, &parent, &children, &children_count))
      //      {
      //
      //         unsigned i;
      //
      //         for(i = 0; i < children_count; ++i)
      //         {
      //
      //            /* Check if this window has the name we seek */
      //            if(XFetchName(display,  children[i], &name) > 0)
      //            {
      //
      //               int r = ansi_cmp(needle, name);
      //
      //               XFree(name);
      //
      //               if(r == 0)
      //               {
      //
      //                  window = children[i+iOffset];
      //
      //                  break;
      //
      //               }
      //
      //            }
      //
      //            if(depth > 1)
      //            {
      //
      //               Window win = window_from_name_search(display, children[i], needle, depth - 1);
      //
      //               if (win != 0)
      //               {
      //
      //                  window = win;
      //
      //                  break;
      //
      //               }
      //
      //            }
      //
      //         }
      //
      //         XFree(children);
      //
      //      }
      //
      //      return window;
      //
      //   }


      //   Window display::window_from_name(char const *name, int iOffset, int depth)
      //   {
      //
      ////      auto display = m_pdisplay;
      ////
      ////      auto windowRoot = XDefaultRootWindow(display);
      ////
      ////      auto window = window_from_name_search(display, windowRoot, name, iOffset, depth);
      //
      //
      //
      ////      return window;
      //
      //   }



      ::GdkDisplay * display::__get_gdk_display()
      {

         if(m_pgdkdisplay)
         {

            return m_pgdkdisplay;

         }

         m_pgdkdisplay = gdk_display_get_default();
         if (m_pgdkdisplay == NULL)
         {
            error() << "Can't connect to display";
            throw ::exception(error_failed);
         }
         information() << "connected to display\n";
         m_bOwnDisplay = true;
         //wl_display_disconnect(display);
         //printf("disconnected from display\n");

         return m_pgdkdisplay;

      }


      //   display * display::get(::particle * pparticle, bool bBranch, ::wl_display * pwldisplay)
      //   {
      //
      //      critical_section_lock lock(this->::system()->globals_critical_section());
      //
      //      if (g_p == nullptr)
      //      {
      //
      //         auto p = ___new display();
      //
      //         p->initialize(pparticle);
      //
      //         //p->add_listener(p);
      //
      //         p->m_pwldisplay = pwldisplay;
      //
      //         if(bBranch)
      //         {
      //
      //            p->branch_synchronously();
      //
      //         }
      //         else
      //         {
      //
      //            p->init_task();
      //
      //         }
      //
      //      }
      //
      //      return g_p;
      //
      //   }


      //   void display::add_listener(event_listener * plistener)
      //   {
      //
      //      synchronous_lock synchronouslock(this->synchronization());
      //
      //      m_happeninglistenera.add(plistener);
      //
      //   }
      //
      //
      //   void display::add_window(micro::interchange * pwindow)
      //   {
      //
      //      synchronous_lock synchronouslock(this->synchronization());
      //
      //      m_windowa.add(pwindow);
      //
      //   }

      //
      //   void display::erase_listener(event_listener * plistener)
      //   {
      //
      //      synchronous_lock synchronouslock(this->synchronization());
      //
      //      m_happeninglistenera.erase(plistener);
      //
      //   }
      //
      //
      //   void display::erase_window(micro::interchange * pwindow)
      //   {
      //
      //      synchronous_lock synchronouslock(this->synchronization());
      //
      //      m_windowa.erase(pwindow);
      //
      //   }

      //
      bool display::message_loop_step()
      {

         return ::gtk4::acme::windowing::display_base::message_loop_step();

      }
      //
      //      if (!XPending(m_pdisplay))
      //      {
      //
      //         return false;
      //
      //      }
      //
      //      XEvent happening{};
      //
      //      XNextEvent(m_pdisplay, &happening);
      //
      //      x11_event(&happening);
      //
      //      return true;
      //
      //   }

      //
      //   bool display::aa_x11_posted()
      //   {
      //
      //      return aaa_display_posted_routine_step();
      //
      //   }
      //
      //
      //   bool display::x11_event(XEvent * pevent)
      //   {
      //
      //      bool bHandled = false;
      //
      //      ::collection::index i = 0;
      //
      //      synchronous_lock synchronouslock(this->synchronization());
      //
      //      for (; i < m_happeninglistenera.get_count(); i++)
      //      {
      //
      //         auto plistener = m_happeninglistenera[i];
      //
      //         synchronouslock.unlock();
      //
      //         if(i == 0)
      //         {
      //
      //            if (plistener->_on_event(pevent))
      //            {
      //
      //               bHandled = true;
      //
      //               break;
      //
      //            }
      //
      //         }
      //         else
      //         {
      //
      //            if (plistener->_on_event(pevent))
      //            {
      //
      //               bHandled = true;
      //
      //               break;
      //
      //            }
      //
      //         }
      //
      //         synchronouslock.lock();
      //
      //      }
      //
      //      return bHandled;
      //
      //   }
      //
      //
      //   void display::aaa_message_loop()
      //   {
      //
      //      bool bHandled1;
      //
      //      bool bHandled2;
      //
      //      while (::task_get_run())
      //      {
      //
      //         if(m_bUnhook)
      //         {
      //
      //            break;
      //
      //         }
      //
      //         bHandled1 = false;
      //
      //         bHandled2 = false;
      //
      //         while(aaa_message_loop_step())
      //         {
      //
      //            bHandled1 = true;
      //
      //         }
      //
      //         if(!bHandled1)
      //         {
      //
      //            bHandled2 = aaa_x11_posted();
      //
      //         }
      //
      //         if(!bHandled1 && !bHandled2)
      //         {
      //
      //            preempt(5_ms);
      //
      //         }
      //
      //      }
      //
      //      information() << "Finished display::message_loop for nano::display";
      //
      //   }
      //

      void display::init_task()
      {


         display_base::init_task();

         //      if(::windowing::get_ewindowing() == ::windowing::e_windowing_none)
         //      {
         //
         //         //set_main_user_thread();
         //
         //         ::windowing::get_ewindowing() = e_windowing_x11;
         //
         //      }
         ////
         ////      XInitxThreads();
         ////
         ////      if(!m_pdisplay)
         ////      {
         ////
         ////         set_X11_Display(XOpenxDisplay(nullptr));
         ////
         ////      }

      }


      void display::set_gdk_display(::GdkDisplay * pgdkdisplay)
      {

         m_pgdkdisplay = pgdkdisplay;

         if (!m_pgdkdisplay)
         {

            throw ::exception(error_null_pointer);

         }

         ::int_rectangle rectangleMainScreen;

         //      auto pscreen = DefaultScreenOfDisplay(m_pdisplay);
         //
         //      int wScreen = WidthOfScreen(pscreen);
         //      int hScreen = HeightOfScreen(pscreen);

         //printf("::x11::display::init_task pscreen=%" PRIxPTR "\n", pscreen);
         //printf("::x11::display::init_task (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);

         //rectangleMainScreen.left() = 0;
         //rectangleMainScreen.top() = 0;
         //rectangleMainScreen.right() = wScreen;
         //rectangleMainScreen.bottom() = hScreen;

         //operating_system_set_main_screen_rectangle(rectangleMainScreen);

      }


      bool display::is_branch_current() const
      {

         if(!m_bUnhook && ::object::is_branch_current())
         {

            return true;

         }

         if(m_bUnhook && ::is_main_thread())
         {

            return true;

         }

         return false;

      }


      void display::run()
      {

         display_base::run();

      }


      //   bool display::_on_event(XEvent * pevent)
      //   {
      //
      //      if (pevent->xany.window == DefaultRootWindow(m_pdisplay))
      //      {
      //
      //         if(pevent->xany.type == PropertyNotify)
      //         {
      //
      //            Atom atom = XInternAtom(m_pdisplay, "_NET_ACTIVE_WINDOW", False);
      //
      //            if (atom == pevent->xproperty.atom)
      //            {
      //
      //               auto windowActive = m_windowActive;
      //
      //               for(auto & pwindow : m_windowa)
      //               {
      //
      //                  bool bNcActive = windowActive == pwindow->m_window;
      //
      //                  if (is_different(bNcActive, pwindow->m_pinterface->m_bNcActive))
      //                  {
      //
      //                     pwindow->m_pinterface->m_bNcActive = bNcActive;
      //
      //                     pwindow->redraw();
      //
      //                  }
      //
      //               }
      //
      //               m_windowActive = windowActive;
      //
      //            }
      //
      //         }
      //
      //      }
      //
      //      return false;
      //
      //   }


      ::int_size display::get_main_screen_size()
      {

         //      auto snum = DefaultScreen(m_pdisplay);
         //
         //      auto width = DisplayWidth(m_pdisplay, snum);
         //
         //      auto height = DisplayHeight(m_pdisplay, snum);
         //
         //      return { width, height };

         if(m_sizeaMonitor.is_empty())
         {

            return {};

         }

         return m_sizeaMonitor[0];

      }



      void * get_display(::particle * pparticle)
      {

         auto pdisplay = ::gtk4::acme::windowing::display::get(pparticle, false);

         return pdisplay->m_pgdkdisplay;

      }


      void set_display(::gtk4::acme::windowing::display_base * pdisplaybase)
      {

         ::gtk4::acme::windowing::display_base::s_pdisplaybase = pdisplaybase;

      }


      void initialize_display(::particle * pparticle, void * pgdkdisplay)
      {

         ::gtk4::acme::windowing::display::get(pparticle, false, (::GdkDisplay *) pgdkdisplay);

      }


      void * initialize_display(::particle * pparticle)
      {

         auto pdisplay = ::gtk4::acme::windowing::display::get(pparticle, false);

         return pdisplay->m_pgdkdisplay;

      }


      void process_messages()
      {

         if(::gtk4::acme::windowing::display_base::s_pdisplaybase)
         {

            ::gtk4::acme::windowing::display_base::s_pdisplaybase->message_loop_step();

         }

      }




   }// namespace user
} // namespace nano


} // namespace gtk4

