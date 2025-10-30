//
// From acme_windowing_gkt3/display on 2025-01-10 01:22 <3ThomasBorregaardSorensen!!
// Created by camilo on 21/02/2022 23:15 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
#include "window.h"
#include "acme/constant/windowing2.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/acme.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
//#include "acme/prototype/geometry2d/rectangle.h"
//#include "acme/user/micro/window.h"
#include "acme/windowing/windowing.h"
//#include "common_gtk/gdk_3_and_4.h"
#include "acme_windowing_kde5/kde5.h"
#include <QScreen>
#include <QRect>
#include <QGuiApplication>
//#include "windowing_system_x11/_.h"


#ifdef OPENBSD

#include <stdio.h>

#endif


//#define MAXSTR 1000


//::e_status defer_initializex_x11();


//int x11_init_threads();
//Display * x11_get_display();


void set_main_user_thread();


namespace kde5
{


   namespace acme
   {


      namespace windowing
      {

         //display * display::g_p = nullptr;


         display::display()
         {

            //m_pdisplay = nullptr;

            m_bUnhook = false;

            //            if(!g_p)
            //            {
            //
            //               g_p = this;
            //
            //            }

            defer_create_synchronization();


         }


         display::~display()
         {


         }


         //         Atom display::intern_atom(const_char_pointer pszAtomName, bool bCreate)
         //         {
         //
         //            return _intern_atom_unlocked(scopedstrAtomName, bCreate);
         //
         //            //      if (m_pdisplay == nullptr)
         //            //      {
         //            //
         //            //         return 0;
         //            //
         //            //      }
         //            //
         //            //      auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
         //            //
         //            //      if (atom == None)
         //            //      {
         //            //
         //            //         windowing_output_debug_string("ERROR: cannot find atom for " + string(scopedstrAtomName) + "\n");
         //            //
         //            //         return None;
         //            //
         //            //      }
         //            //
         //            //      return atom;
         //
         //         }
         //
         //
         //         Atom display::intern_atom(enuid() eatom, bool bCreate)
         //         {
         //
         //            return _intern_atom_unlocked(eatom, bCreate);
         //
         //            //      if (eatom < 0 || eatom >= e_atom_count)
         //            //      {
         //            //
         //            //         return None;
         //            //
         //            //      }
         //            //
         //            //      Atom atom = id()map_base[eatom];
         //            //
         //            //      if (atom == None)
         //            //      {
         //            //
         //            //         atom = intern_atom(atom_name(eatom), bCreate);
         //            //
         //            //         id()map_base[eatom] = atom;
         //            //
         //            //      }
         //            //
         //            //      return atom;
         //
         //         }
         //
         //
         //
         //         Atom display::_intern_atom_unlocked(const_char_pointer pszAtomName, bool bCreate)
         //         {
         //
         //            if (m_pdisplay == nullptr)
         //            {
         //
         //               return 0;
         //
         //            }
         //
         //            auto atom = XInternAtom(m_pdisplay, pszAtomName, bCreate ? True : False);
         //
         //            if (atom == None)
         //            {
         //
         //               windowing_output_debug_string("ERROR: cannot find atom for " + string(scopedstrAtomName) + "\n");
         //
         //               return None;
         //
         //            }
         //
         //            return atom;
         //
         //         }
         //
         //
         //         Atom display::_intern_atom_unlocked(enuid() eatom, bool bCreate)
         //         {
         //
         //            if (eatom < 0 || eatom >= e_atom_count)
         //            {
         //
         //               return None;
         //
         //            }
         //
         //            Atom atom = id()map_base[eatom];
         //
         //            if (atom == None)
         //            {
         //
         //               atom = _intern_atom_unlocked(atom_name(eatom), bCreate);
         //
         //               id()map_base[eatom] = atom;
         //
         //            }
         //
         //            return atom;
         //
         //         }
         //
         //
         //         unsigned char* display::_get_string_property(Display * display, Window window, char* property_name)
         //         {
         //
         //            unsigned char * prop;
         //            Atom actual_type, filter_atom;
         //            int actual_format, status;
         //            unsigned long nitems, bytes_after;
         //
         //            filter_atom = XInternAtom(display, property_name, True);
         //
         //            status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
         //                                        &actual_type, &actual_format, &nitems, &bytes_after, &prop);
         //
         //            x11_check_status(status, window);
         //
         //            return prop;
         //
         //         }
         //
         //
         //         unsigned long display::_get_long_property(Display *d, Window w, char *property_name)
         //         {
         //
         //            unsigned char *prop = _get_string_property(d, w, property_name);
         //
         //            unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);
         //
         //            XFree(prop);
         //
         //            return long_property;
         //
         //         }


         //         Window display::_get_active_window()
         //         {
         //
         //            int screen = XDefaultScreen(m_pdisplay);
         //
         //            Window windowRoot = RootWindow(m_pdisplay, screen);
         //
         //            Window window = _get_long_property(m_pdisplay, windowRoot, (char *) "_NET_ACTIVE_WINDOW");
         //
         //            return window;
         //
         //         }


         //         Window display::window_from_name_search(Display *display, Window current, char const *needle, int iOffset, int depth)
         //         {
         //
         //            Window window, root, parent, *children;
         //
         //            unsigned children_count;
         //
         //            char *name = NULL;
         //
         //            window = 0;
         //
         //            /* If it does not: check all subwindows recursively. */
         //            if(0 != XQueryTree(display, current, &root, &parent, &children, &children_count))
         //            {
         //
         //               unsigned i;
         //
         //               for(i = 0; i < children_count; ++i)
         //               {
         //
         //                  /* Check if this window has the name we seek */
         //                  if(XFetchName(display,  children[i], &name) > 0)
         //                  {
         //
         //                     int r = ansi_cmp(needle, name);
         //
         //                     XFree(name);
         //
         //                     if(r == 0)
         //                     {
         //
         //                        window = children[i+iOffset];
         //
         //                        break;
         //
         //                     }
         //
         //                  }
         //
         //                  if(depth > 1)
         //                  {
         //
         //                     Window win = window_from_name_search(display, children[i], needle, depth - 1);
         //
         //                     if (win != 0)
         //                     {
         //
         //                        window = win;
         //
         //                        break;
         //
         //                     }
         //
         //                  }
         //
         //               }
         //
         //               XFree(children);
         //
         //            }
         //
         //            return window;
         //
         //         }
         //
         //
         //         Window display::window_from_name(char const *name, int iOffset, int depth)
         //         {
         //
         //            auto display = m_pdisplay;
         //
         //            auto windowRoot = XDefaultRootWindow(display);
         //
         //            auto window = window_from_name_search(display, windowRoot, name, iOffset, depth);
         //
         //            return window;
         //
         //         }
         //
         //
         //         display * display_get(::particle * pparticle, bool bBranch, Display * pdisplay)
         //         {
         //
         //            critical_section_lock lock(pparticle->::system()->globals_critical_section());
         //
         //            if (display::g_p == nullptr)
         //            {
         //
         //               auto p = ___new display();
         //
         //               p->initialize(pparticle);
         //
         //               p->add_listener(p);
         //
         //               p->m_pdisplay = pdisplay;
         //
         //               if(bBranch)
         //               {
         //
         //                  p->branch_synchronously();
         //
         //               }
         //               else
         //               {
         //
         //                  p->init_task();
         //
         //               }
         //
         //            }
         //
         //            return display::g_p;
         //
         //         }
         //
         //
         //         void display::add_listener(event_listener * plistener)
         //         {
         //
         //            synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         //
         //            m_happeninglistenera.add(plistener);
         //
         //         }
         //
         //
         //         void display::add_window(micro::interchange * pwindow)
         //         {
         //
         //            synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         //
         //            m_windowa.add(pwindow);
         //
         //         }
         //
         //
         //         void display::erase_listener(event_listener * plistener)
         //         {
         //
         //            synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         //
         //            m_happeninglistenera.erase(plistener);
         //
         //         }
         //
         //
         //         void display::erase_window(::x11::micro::elemental * pwindow)
         //         {
         //
         //            synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         //
         //            m_windowa.erase(pwindow);
         //
         //         }


         bool display::message_loop_step()
         {

            //            if(::is_null(m_pdisplay))
            //            {
            //
            //               return false;
            //
            //            }

            //            if (!XPending(m_pdisplay))
            //            {
            //
            //               return false;
            //
            //            }
            //
            //            XEvent happening{};
            //
            //            XNextEvent(m_pdisplay, &happening);
            //
            //            x11_event(&happening);

            return true;

         }


         //         bool display::x11_posted()
         //         {
         //
         //            return display_posted_routine_step();
         //
         //         }
         //
         //
         //         bool display::x11_event(XEvent * pevent)
         //         {
         //
         //            bool bHandled = false;
         //
         //            ::collection::index i = 0;
         //
         //            _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
         //
         //            for (; i < m_happeninglistenera.get_count(); i++)
         //            {
         //
         //               auto plistener = m_happeninglistenera[i];
         //
         //               synchronouslock.unlock();
         //
         //               if(i == 0)
         //               {
         //
         //                  if (plistener->_on_event(pevent))
         //                  {
         //
         //                     bHandled = true;
         //
         //                     break;
         //
         //                  }
         //
         //               }
         //               else
         //               {
         //
         //                  if (plistener->_on_event(pevent))
         //                  {
         //
         //                     bHandled = true;
         //
         //                     break;
         //
         //                  }
         //
         //               }
         //
         //               synchronouslock._lock();
         //
         //            }
         //
         //            return bHandled;
         //
         //         }


         void display::message_loop()
         {

            bool bHandled1;

            bool bHandled2;

            information() << "x11::acme::windowing::display::message_loop";

            while (::task_get_run())
            {

               if (m_bUnhook)
               {

                  break;

               }

               bHandled1 = false;

               bHandled2 = false;

               while (message_loop_step())
               {

                  bHandled1 = true;

               }

               //               if(!bHandled1)
               //               {
               //
               //                  bHandled2 = x11_posted();
               //
               //               }

               if (!bHandled1 && !bHandled2)
               {

                  preempt(5_ms);

               }

            }

            information() << "Finished display::message_loop for nano::display";

         }


         void display::init_task()
         {

            informationf("x11 nano display init_task");

            //~ if(::windowing::get_ewindowing() == ::windowing::e_windowing_none)
            //~ {

            //~ //set_main_user_thread();

            //~ ::windowing::get_ewindowing() = e_windowing_x11;

            //~ }

            // printf("\n\nx11::display::init_task Going to call x11_defer_initialize\n\n");
            //
            // fflush(stdout);
            //
            // node()->x11_defer_initialize();

            //            if(!m_pdisplay)
            //            {
            //
            //               set_X11_Display((Display *) system()->acme_windowing()->get_display());
            //
            //            }

         }


         //         void display::set_X11_Display(Display * pdisplay)
         //         {
         //
         //            m_pdisplay = pdisplay;
         //
         //            if (!m_pdisplay)
         //            {
         //
         //               throw ::exception(error_null_pointer);
         //
         //            }
         //
         //            ::int_rectangle rectangleMainScreen;
         //
         //            auto pscreen = DefaultScreenOfDisplay(m_pdisplay);
         //
         //            int wScreen = WidthOfScreen(pscreen);
         //            int hScreen = HeightOfScreen(pscreen);
         //
         //            //printf("::x11::display::init_task pscreen=%" PRIxPTR "\n", pscreen);
         //            //printf("::x11::display::init_task (wScreen,hScreen)=%d,%d\n", wScreen, hScreen);
         //
         //            //rectangleMainScreen.left() = 0;
         //            //rectangleMainScreen.top() = 0;
         //            //rectangleMainScreen.right() = wScreen;
         //            //rectangleMainScreen.bottom() = hScreen;
         //
         //            //operating_system_set_main_screen_rectangle(rectangleMainScreen);
         //
         //         }


         bool display::is_branch_current() const
         {

            if (!m_bUnhook && ::object::is_branch_current())
            {

               return true;

            }

            if (m_bUnhook && ::is_main_thread())
            {

               return true;

            }

            return false;

         }


         void display::run()
         {

            ::task_set_name("x11:display:run");

            information() << "x11::display::run";

            //set_main_user_thread();

            message_loop();

            //            if (m_pdisplay != nullptr)
            //            {
            //
            //               XCloseDisplay(m_pdisplay);
            //
            //               m_pdisplay = nullptr;
            //
            //            }

         }


         //         bool display::_on_event(XEvent * pevent)
         //         {
         //
         //            if (pevent->xany.window == DefaultRootWindow(m_pdisplay))
         //            {
         //
         //               if(pevent->xany.type == PropertyNotify)
         //               {
         //
         //                  Atom atom = XInternAtom(m_pdisplay, "_NET_ACTIVE_WINDOW", False);
         //
         //                  if (atom == pevent->xproperty.atom)
         //                  {
         //
         //                     auto windowActive = m_windowActive;
         //
         //                     for(auto & pwindow : m_windowa)
         //                     {
         //
         //                        bool bNcActive = windowActive == pwindow->m_window;
         //
         //                        if (is_different(bNcActive, pwindow->m_pinterface->m_bNcActive))
         //                        {
         //
         //                           pwindow->m_pinterface->m_bNcActive = bNcActive;
         //
         //                           pwindow->redraw();
         //
         //                        }
         //
         //                     }
         //
         //                     m_windowActive = windowActive;
         //
         //                  }
         //
         //               }
         //
         //            }
         //
         //            return false;
         //
         //         }


         ::int_size display::get_main_screen_size()
         {

            //            auto snum = DefaultScreen(m_pdisplay);
            //
            //            auto width = DisplayWidth(m_pdisplay, snum);
            //
            //            auto height = DisplayHeight(m_pdisplay, snum);

            //return {1920, 1080};

            // Get the primary screen
            QScreen* primaryScreen = QGuiApplication::primaryScreen();
            if (!primaryScreen)
            {
               //qWarning() << "No primary screen found!";
               return {1920, 1080};
            }

            // Get the screen geometry
            QRect screenGeometry = primaryScreen->geometry();
            int width = screenGeometry.width();
            int height = screenGeometry.height();

            //qDebug() << "Primary screen size: " << width << "x" << height;
            return {width, height};

         }


         // void * x11_get_display(::particle * pparticle)
         // {
         //
         //    auto pdisplay = ::x11::display::get(pparticle, false);
         //
         //    return pdisplay->m_pdisplay;
         //
         // }


         void process_messages()
         {

            //         if(::x11::acme::windowing::display::g_p)
            //         {
            //
            //            ::x11::acme::windowing::display::g_p->message_loop_step();
            //
            //         }

         }


         //int _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);

         //::e_status g_estatusInitializeX11 = error_not_initialized;
         //
         //
         //
         //         int init_threads()
         //         {
         //
         //            return XInitThreads();
         //
         //         }
         //


         //int _c_XErrorHandler(Display * display, XErrorEvent * perrorevent)
         //{
         //
         //   const_char_pointer pszError;
         //
         //   if(perrorevent->error_code == BadRequest)
         //   {
         //
         //      pszError = "BadRequest";
         //
         //   }
         //   else if(perrorevent->error_code == BadValue)
         //   {
         //
         //      pszError = "BadValue";
         //
         //   }
         //   else if(perrorevent->error_code == BadWindow)
         //   {
         //
         //      pszError = "BadWindow";
         //
         //   }
         //   else if(perrorevent->error_code == BadPixmap)
         //   {
         //
         //      pszError = "BadPixmap";
         //
         //   }
         //   else if(perrorevent->error_code == BadAtom)
         //   {
         //
         //      pszError = "BadAtom";
         //
         //   }
         //   else if(perrorevent->error_code == BadCursor)
         //   {
         //
         //      pszError = "BadCursor";
         //
         //   }
         //   else if(perrorevent->error_code == BadFont)
         //   {
         //
         //      pszError = "BadFont";
         //
         //   }
         //   else if(perrorevent->error_code == BadMatch)
         //   {
         //
         //      pszError = "BadMatch";
         //
         //   }
         //   else if(perrorevent->error_code == BadDrawable)
         //   {
         //
         //      pszError = "BadDrawable";
         //
         //   }
         //   else if(perrorevent->error_code == BadAccess)
         //   {
         //
         //      pszError = "BadAccess";
         //
         //   }
         //   else if(perrorevent->error_code == BadAlloc)
         //   {
         //
         //      pszError = "BadAlloc";
         //
         //   }
         //   else if(perrorevent->error_code == BadColor)
         //   {
         //
         //      pszError = "BadColor";
         //
         //   }
         //   else if(perrorevent->error_code == BadGC)
         //   {
         //
         //      pszError = "BadGC";
         //
         //   }
         //   else if(perrorevent->error_code == BadIDChoice)
         //   {
         //
         //      pszError = "BadIDChoice";
         //
         //   }
         //   else if(perrorevent->error_code == BadName)
         //   {
         //
         //      pszError = "BadName";
         //
         //   }
         //   else if(perrorevent->error_code == BadLength)
         //   {
         //
         //      pszError = "BadLength";
         //
         //   }
         //   else if(perrorevent->error_code == BadImplementation)
         //   {
         //
         //      pszError = "BadImplementation";
         //
         //   }
         //   else
         //   {
         //
         //      pszError = " ( Unknown ) ";
         //
         //   }
         //
         //const_char_pointer pszRequest;
         //   if(perrorevent->request_code == 1)
         //   {
         //
         //      pszRequest = "X_CreateWindow";
         //
         //   }
         //   else if(perrorevent->request_code == 2)
         //   {
         //
         //      pszRequest = "X_ChangeWindowAttributes";
         //
         //   }
         //   else if(perrorevent->request_code == 3)
         //   {
         //
         //      pszRequest = "X_GetWindowAttributes";
         //
         //   }
         //   else if(perrorevent->request_code == 4)
         //   {
         //
         //      pszRequest = "X_DestroyWindow";
         //
         //   }
         //   else if(perrorevent->request_code == 5)
         //   {
         //
         //      pszRequest = "X_DestroySubwindows";
         //
         //   }
         //   else if(perrorevent->request_code == 6)
         //   {
         //
         //      pszRequest = "X_ChangeSaveSet";
         //
         //   }
         //   else if(perrorevent->request_code == 7)
         //   {
         //
         //      pszRequest = "X_ReparentWindow";
         //
         //   }
         //   else if(perrorevent->request_code == 8)
         //   {
         //
         //      pszRequest = "X_MapWindow";
         //
         //   }
         //   else if(perrorevent->request_code == 9)
         //   {
         //
         //      pszRequest = "X_MapSubwindows";
         //
         //   }
         //   else if(perrorevent->request_code == 10)
         //   {
         //
         //      pszRequest = "X_UnmapWindow";
         //
         //   }
         //   else if(perrorevent->request_code == 11)
         //   {
         //
         //      pszRequest = "X_UnmapSubwindows";
         //
         //   }
         //   else if(perrorevent->request_code == 12)
         //   {
         //
         //      pszRequest = "X_ConfigureWindow";
         //
         //   }
         //
         //
         //      #define X_CreateWindow                  1
         //#define X_ChangeWindowAttributes        2
         //#define X_GetWindowAttributes           3
         //#define X_DestroyWindow                 4
         //#define X_DestroySubwindows             5
         //#define X_ChangeSaveSet                 6
         //#define X_ReparentWindow                7
         //#define X_MapWindow                     8
         //#define X_MapSubwindows                 9
         //#define X_UnmapWindow                  10
         //#define X_UnmapSubwindows              11
         //#define X_ConfigureWindow              12
         //#define X_CirculateWindow              13
         //#define X_GetGeometry                  14
         //#define X_QueryTree                    15
         //#define X_InternAtom                   16
         //#define X_GetAtomName                  17
         //#define X_ChangeProperty               18
         //#define X_DeleteProperty               19
         //#define X_GetProperty                  20
         //#define X_ListProperties               21
         //#define X_SetSelectionOwner            22
         //#define X_GetSelectionOwner            23
         //#define X_ConvertSelection             24
         //#define X_SendEvent                    25
         //#define X_GrabPointer                  26
         //#define X_UngrabPointer                27
         //#define X_GrabButton                   28
         //#define X_UngrabButton                 29
         //#define X_ChangeActivePointerGrab      30
         //#define X_GrabKeyboard                 31
         //#define X_UngrabKeyboard               32
         //#define X_GrabKey                      33
         //#define X_UngrabKey                    34
         //#define X_AllowEvents                  35
         //#define X_GrabServer                   36
         //#define X_UngrabServer                 37
         //#define X_QueryPointer                 38
         //#define X_GetMotionEvents              39
         //#define X_TranslateCoords              40
         //#define X_WarpPointer                  41
         //#define X_SetInputFocus                42
         //#define X_GetInputFocus                43
         //#define X_QueryKeymap                  44
         //#define X_OpenFont                     45
         //#define X_CloseFont                    46
         //#define X_QueryFont                    47
         //#define X_QueryTextExtents             48
         //#define X_ListFonts                    49
         //#define X_ListFontsWithInfo    	       50
         //#define X_SetFontPath                  51
         //#define X_GetFontPath                  52
         //#define X_CreatePixmap                 53
         //#define X_FreePixmap                   54
         //#define X_CreateGC                     55
         //#define X_ChangeGC                     56
         //#define X_CopyGC                       57
         //#define X_SetDashes                    58
         //#define X_SetClipRectangles            59
         //#define X_FreeGC                       60
         //#define X_ClearArea                    61
         //#define X_CopyArea                     62
         //#define X_CopyPlane                    63
         //#define X_PolyPoint                    64
         //#define X_PolyLine                     65
         //#define X_PolySegment                  66
         //#define X_PolyRectangle                67
         //#define X_PolyArc                      68
         //#define X_FillPoly                     69
         //#define X_PolyFillRectangle            70
         //#define X_PolyFillArc                  71
         //#define X_PutImage                     72
         //#define X_GetImage                     73
         //#define X_PolyText8                    74
         //#define X_PolyText16                   75
         //#define X_ImageText8                   76
         //#define X_ImageText16                  77
         //#define X_CreateColormap               78
         //#define X_FreeColormap                 79
         //#define X_CopyColormapAndFree          80
         //#define X_InstallColormap              81
         //#define X_UninstallColormap            82
         //#define X_ListInstalledColormaps       83
         //#define X_AllocColor                   84
         //#define X_AllocNamedColor              85
         //#define X_AllocColorCells              86
         //#define X_AllocColorPlanes             87
         //#define X_FreeColors                   88
         //#define X_StoreColors                  89
         //#define X_StoreNamedColor              90
         //#define X_QueryColors                  91
         //#define X_LookupColor                  92
         //#define X_CreateCursor                 93
         //#define X_CreateGlyphCursor            94
         //#define X_FreeCursor                   95
         //#define X_RecolorCursor                96
         //#define X_QueryBestSize                97
         //#define X_QueryExtension               98
         //#define X_ListExtensions               99
         //#define X_ChangeKeyboardMapping        100
         //#define X_GetKeyboardMapping           101
         //#define X_ChangeKeyboardControl        102
         //#define X_GetKeyboardControl           103
         //#define X_Bell                         104
         //#define X_ChangePointerControl         105
         //#define X_GetPointerControl            106
         //#define X_SetScreenSaver               107
         //#define X_GetScreenSaver               108
         //#define X_ChangeHosts                  109
         //#define X_ListHosts                    110
         //#define X_SetAccessControl             111
         //#define X_SetCloseDownMode             112
         //#define X_KillClient                   113
         //#define X_RotateProperties	       114
         //#define X_ForceScreenSaver	       115
         //#define X_SetPointerMapping            116
         //#define X_GetPointerMapping            117
         //#define X_SetModifierMapping	       118
         //#define X_GetModifierMapping	       119
         //#define X_NoOperation                  127
         //
         //   else
         //   {
         //
         //      pszRequest = " ( Unknown ) ";
         //
         //   }
         //
         //   fprintf(stderr, "_c_XErrorHandler error=%d (%s) request =%d (%s)\n", perrorevent->error_code, pszError, perrorevent->request_code, pszRequest);
         //
         //   return 0;
         //
         //}

         // void display::release_mouse_capture()
         // {
         //
         //    // GdkDisplay* display = gdk_display_get_default();
         //    // if (display)
         //    // {
         //    //    GdkSeat* seat = gdk_display_get_default_seat(display);
         //    //    if (seat)
         //    //    {
         //    //       GdkDevice* pointer_device = gdk_seat_get_pointer(seat);
         //    //       if (pointer_device)
         //    //       {
         //    //          gdk_device_ungrab(pointer_device, GDK_CURRENT_TIME);
         //    //          g_print("Pointer ungrabbed.\n");
         //    //       }
         //    //    }
         //    // }
         //
         // }


         bool display::is_dark_mode_through_theming()
         {

            auto edesktop = ::windowing::get_eoperating_ambient();

            switch (edesktop)
            {
               case ::windowing::e_operating_ambient_gnome:
                  return false;
               case ::windowing::e_operating_ambient_mate:
                  return false; // don't know yet
               case ::windowing::e_operating_ambient_lxde:
                  return false; // don't know yet
               case ::windowing::e_operating_ambient_xfce:
                  return true;
               case ::windowing::e_operating_ambient_kde:
                  return true;
               default:
                  return false;
            }
         }


         string display::theming_ui_name()
         {

            auto edesktop = ::windowing::get_eoperating_ambient();

            switch (edesktop)
            {
               case ::windowing::e_operating_ambient_kde:
                  return "KDE Plasma Global Theme";
               default:
                  return ::acme::windowing::display::theming_ui_name();
            };

         }


         void display::impl_set_desktop_theme(const ::scoped_string& scopedstrDesktopTheme)
         {

            ::kde5::set_global_theme(scopedstrDesktopTheme);

            // https://ubuntuforums.org/showthread.php?t=2140488
            // gsettings set org.gnome.desktop.interface gtk-theme your_theme

            // indirect wall-changer sourceforge.net contribution

            //auto psystem = system();

            //auto pnode = psystem->node();

            // ::string strDesktopTheme;
            //
            // strDesktopTheme = scopedstrDesktopTheme;
            //
            // auto edesktop = ::windowing::get_eoperating_ambient();
            //
            // if (edesktop == ::windowing::e_operating_ambient_gnome)
            // {
            //
            //    bool bOk1 = ::gdk::gsettings_set("org.gnome.desktop.interface", "gtk-theme", strDesktopTheme).ok();
            //
            //    bool bOk2 = true;
            //
            //    //if(::file::system_short_name().case_insensitive_contains("manjaro"))
            //    {
            //
            //       bOk2 = ::gdk::gsettings_set("org.gnome.desktop.wm.preferences", "theme", strDesktopTheme).ok();
            //
            //    }
            //
            //    sleep(300_ms);
            //
            //    ::gdk::gsettings_sync();
            //
            //    sleep(300_ms);
            //
            //    if (!bOk1 || !bOk2)
            //    {
            //
            //       throw ::exception(error_failed);
            //
            //    }
            //
            // }
            // else if (edesktop == ::windowing::e_operating_ambient_mate)
            // {
            //
            //    //return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);
            //
            // }
            // else if (edesktop == ::windowing::e_operating_ambient_lxde)
            // {
            //
            //
            //    //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
            //
            // }
            // else if (edesktop & ::windowing::e_operating_ambient_xfce)
            // {
            //    //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //    //          if(entry.contains("image-path") || entry.contains("last-image")){
            //    //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //    //      }
            //    //}
            //    xfce4_set_user_theme(strDesktopTheme);
            //    //warning() <<"Failed to set operating system theme wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
            //
            //    //return error_failed;
            //
            // }
            //
            // //      return ::success;

         }


         string display::impl_get_desktop_theme()
         {


            // // https://ubuntuforums.org/showthread.php?t=2140488
            // // gsettings set org.gnome.desktop.interface gtk-theme your_theme
            //
            // // indirect wall-changer sourceforge.net contribution
            //
            // string strDesktopTheme;
            //
            // bool bOk = false;
            //
            //
            //       auto edesktop = ::windowing::get_eoperating_ambient();
            //
            // switch (edesktop)
            // {
            //
            //    case ::windowing::e_operating_ambient_gnome:
            //    //case ::windowing::e_operating_ambient_ubuntu_gnome:
            //    //case ::windowing::e_operating_ambient_unity_gnome:
            //
            //       bOk = ::gdk::gsettings_get(strDesktopTheme, "org.gnome.desktop.interface", "gtk-theme").ok();
            //
            //       break;
            //
            //    case ::windowing::e_operating_ambient_mate:
            //
            //       bOk = ::gdk::gsettings_get(strDesktopTheme, "org.mate.background", "picture-filename").ok();
            //
            //       break;
            //
            //    case ::windowing::e_operating_ambient_lxde:
            //
            //       //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
            //
            //       break;
            //
            //    case ::windowing::e_operating_ambient_xfce:
            //    {
            //       //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //       //          if(entry.contains("image-path") || entry.contains("last-image")){
            //       //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //       //      }
            //       //}
            //       strDesktopTheme = xfce4_get_user_theme();
            //
            //    }
            //
            //       break;
            //
            //    default:
            //
            //       warningf(
            //               "Failed to get user theme setting. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.");
            //       //return "";
            //    break;
            //
            // }
            //
            // return strDesktopTheme;


            ::string strDesktopTheme;

            strDesktopTheme = ::kde5::get_global_theme_name();

            return strDesktopTheme;

         }


         void display::set_desktop_icon_theme(const ::scoped_string& scopedstrUserIconTheme)
         {

            //             // https://ubuntuforums.org/showthread.php?t=2140488
            //             // gsettings set org.gnome.desktop.interface gtk-theme your_theme
            //
            //             // indirect wall-changer sourceforge.net contribution
            //
            //             // auto psystem = system();
            //             //
            //             // auto pnode = psystem->node();
            //
            //             ::string strDesktopIconTheme;
            //
            //             strDesktopIconTheme = scopedstrUserIconTheme;
            //
            //             auto edesktop = ::windowing::get_eoperating_ambient();
            //
            //             if (edesktop & ::windowing::e_operating_ambient_gnome)
            //             {
            //
            //                bool bOk1 = ::gdk::gsettings_set("org.gnome.desktop.interface", "icon-theme", strDesktopIconTheme).ok();
            //
            //                //bool bOk2 = true;
            //
            //                //         //if(::file::system_short_name().case_insensitive_contains("manjaro"))
            //                //         {
            //                //
            //                //            bOk2 = gsettings_set("org.gnome.desktop.wm.preferences", "theme", strUserTheme);
            //                //
            //                //         }
            //
            //                sleep(300_ms);
            //
            //                ::gdk::gsettings_sync();
            //
            //                sleep(300_ms);
            //
            //                //if (!bOk1 || !bOk2)
            //                if (!bOk1)
            //                {
            //
            //                   information() << "failed to set os user icon theme";
            //
            //
            //                }
            //
            //             }
            //             else if (edesktop == ::windowing::e_operating_ambient_mate)
            //             {
            //
            //                //return ::user::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);
            //
            //             }
            //             else if (edesktop == ::windowing::e_operating_ambient_lxde)
            //             {
            //
            //
            //                //call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
            //
            //             }
            //             else if (edesktop == ::windowing::e_operating_ambient_xfce)
            //             {
            //                //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //                //          if(entry.contains("image-path") || entry.contains("last-image")){
            //                //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //                //      }
            //                //}
            //
            //                warning() <<
            //                   "Failed to set operating system theme wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
            //
            //                //return error_failed;
            //
            //             }
            //
            //   //          return ::success;
            // //
         }


         //   void node::os_process_user_theme(const ::scoped_string & scopedstrTheme)
         //   {
         //
         //      _os_process_user_theme(strTheme);
         //
         //   }


         void display::_set_wallpaper(::collection::index iScreen, const ::scoped_string& scopedstrLocalImagePath)
         {

            ::string strCommand;

            strCommand = "plasma-apply-wallpaperimage";

            strCommand += " \"" + scopedstrLocalImagePath + "\"";

            auto iError = node()->command_system(strCommand, 15_s);

            // if(iError)
            // {
            //
            //    return false;
            //
            // }
            //
            // return true;

            // // wall-changer sourceforge.net contribution
            //
            //    // auto psystem = system();
            //    //
            //    // auto pnode = psystem->node();
            //
            //    //auto edesktop = pnode->get_eoperating_ambient();
            //
            //    ::string strLocalImagePath;
            //
            //    strLocalImagePath = scopedstrLocalImagePath;
            //
            //    auto edesktop = ::windowing::get_eoperating_ambient();
            //
            //    bool bDark = m_strDarkModeAnnotation.case_insensitive_contains("dark");
            //
            //    switch (edesktop)
            //    {
            //
            //       case ::windowing::e_operating_ambient_gnome:
            //       //case ::user::e_operating_ambient_ubuntu_gnome:
            //       case ::windowing::e_operating_ambient_unity:
            //       {
            //
            //          if (bDark)
            //          {
            //
            //             ::gdk::gsettings_set("org.gnome.desktop.background", "picture-uri-dark",
            //                                         "file://" + strLocalImagePath);
            //
            //          }
            //          else
            //          {
            //
            //             ::gdk::gsettings_set("org.gnome.desktop.background", "picture-uri",
            //                                         "file://" + strLocalImagePath);
            //
            //          }
            //
            //       }
            //       break;
            //       case ::windowing::e_operating_ambient_mate:
            //
            //           ::gdk::gsettings_set("org.mate.background", "picture-filename", strLocalImagePath);
            //
            //       break;
            //
            //       case ::windowing::e_operating_ambient_lxde:
            //
            //          node()->call_async("pcmanfm", "-w " + strLocalImagePath, nullptr, e_display_none, false);
            //
            //          break;
            //
            //       case ::windowing::e_operating_ambient_xfce:
            //       {
            //
            //          xfce4_set_wallpaper(strLocalImagePath);
            //          //        Q_FOREACH(QString entry, Global::getOutputOfCommand("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << "/backdrop" << "-l").split("\n")){
            //          //          if(entry.contains("image-path") || entry.contains("last-image")){
            //          //            QProcess::startDetached("xfconf-query", QStringList() << "-c" << "xfce4-desktop" << "-point" << entry << "-s" << image);
            //          //      }
            //          //}
            //
            //       }
            //
            //       break;
            //
            //       default:
            //
            //          warning() <<
            //             "Failed to change wallpaper. If your Desktop Environment is not listed at \"Preferences->Integration-> Current Desktop Environment\", then it is not supported.";
            //          //return false;
            //       break;
            //
            //    }
            //
            //    //return true;

         }


         //#include <KPackage/Package>
         //#include <KPackage/PackageLoader>
         //#include <KF5/plasma/applet.h>
         //#include <KF5/plasma/containment.h>


         // string node::get_file_icon_path(const ::scoped_string & scopedstrPath, int iSize)
         // {
         //
         //    QUrl url((const_char_pointer )("file://"+strPath));
         //
         //    KFileItem fileitem(url, KFileItem::NormalMimeTypeDetermination);
         //
         //    auto name = fileitem.iconName();
         //
         //    //      if(::is_null(m_piconloader))
         //    //      {
         //    //
         //    //         m_piconloader = ___new KIconLoader();
         //    //
         //    //      }
         //
         //    auto path = KIconLoader::global()->iconPath(name, -iSize);
         //
         //    //return ::linux_g_direct_get_file_icon_path(scopedstrPath, iSize);
         //
         //    QByteArray bytea = path.toUtf8();
         //
         //    const_char_pointer pathData = bytea.constData();
         //
         //    return pathData;
         //
         // }
         //


      } // namespace windowing


   } // namespace acme


} // namespace kde5
