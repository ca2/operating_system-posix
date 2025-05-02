// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "windowing.h"
#include "window.h"
#include "display.h"
#include "cursor.h"
//#include "gdk_gdk.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "apex/input/input.h"
#include "aura/windowing/cursor_manager.h"
#include <X11/cursorfont.h>

#include "acme/windowing/windowing.h"
//#include "aura/user/user/interaction_impl.h"
#include "aura/windowing/display.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "acme_windowing_gtk4/windowing.h"
//#include "windowing_system_x11/display_lock.h"




namespace windowing_gtk4
{
   windowing::windowing()
   {

      printf("windowing_gtk4::windowing::windowing()");

      defer_create_synchronization();

      // m_bRootSelectInput = false;
      //
      // m_itask = -1;

      //m_pWindowing4 = this;

      // m_bFirstWindowMap = false;
      //
      // m_bInitX11Thread = false;
      //
      // m_bFinishX11Thread = false;


      //deferx_initializex_x11();

   }


   windowing::~windowing()
   {

   }


   bool windowing::has_readily_gettable_absolute_coordinates() const
   {

      return false;

   }


   bool windowing::is_branch_current() const
   {

      return system()->acme_windowing()->is_branch_current();


   }


   //   ::windowing::window * windowing::new_window(::windowing::window * pimpl)
   //   {
   //
   //      ::pointer<::windowing_gtk4::window> pwindow = pimpl->__øcreate<::windowing::window>();
   //
   //      if (!pwindow)
   //      {
   //
   //         return nullptr;
   //
   //      }
   //
   //      pwindow->m_pwindowing = this;
   //
   //      pwindow->m_pwindow = pimpl;
   //
   //      pimpl->m_pwindow = pwindow;
   //
   //      pwindow->create_window(pimpl);
   //
   //      return pwindow;
   //
   //   }


   void windowing::erase_window(::windowing::window * pwindow)
   {

      ::pointer < ::windowing_gtk4::display > pdisplay = m_pacmedisplay;

      pdisplay->erase_window(pwindow);

   }


   void windowing::initialize(::particle * pparticle)
   {

      ::windowing::windowing::initialize(pparticle);

      //      ::pointer < ::input::input > windowing::get_input()
      //      {

      //      auto & pfactory = acmesystem()->factory("input", "libinput");
      //
      //      pfactory->merge_to_global_factory();

      //         return windowing_posix::windowing::get_input();
      //
      //      }

   }


   //   ::pointer <::input::input> windowing::_get_input()
   //   {
   //
   //      auto & pfactory = ::system()->factory("input", "libinput");
   //
   //      auto pinput = __øcreate<::input::input>(pfactory);
   //
   //      return pinput;
   //
   //   }


   void windowing::initialize_windowing()
   {

      ::windowing_posix::windowing::initialize_windowing();

      information() << "windowing_gtk4::windowing::initialize_windowing";


      //m_pdisplay->open();

//      _libsn_start_context();

   }


   void windowing::destroy()
   {

      m_pwindowMouseCapture.release();

      ::gtk4::acme::windowing::windowing::destroy();

      ::windowing_posix::windowing::destroy();

   }


   //   void windowing::start()
   //   {
   //
   //      auto psystem = system();
   //
   //      if (psystem->m_bUser)
   //      {
   //
   //         deferx_initializex_x11();
   //
   //      }
   //
   //      auto pnode = psystem->node();
   //
   //      if(pnode)
   //      {
   //
   //         _libsn_start_context();
   //
   //         branch_element(pnode);
   //
   //      }
   //      else
   //      {
   //
   //         x11_main();
   //
   //      }
   //
   //      //return ::success;
   //
   //   }


   //   void windowing::windowing_post(const ::procedure & procedure)
   //   {
   //
   //      if (!procedure)
   //      {
   //
   //         throw ::exception(error_null_pointer);
   //
   //      }
   //
   //      synchronous_lock synchronouslock(this->synchronization());
   //
   //      m_procedurelist.add_tail(procedure);
   //
   //      //return ::success_scheduled;
   //
   //   }


   //   bool windowing::aaa_x11_runnable_step()
   //   {
   //
   //      bool bHandled = false;
   //
   //      process_owned_procedure_list(m_procedurelistPriority, bHandled);
   //
   //      if (m_pdisplay)
   //      {
   //
   //         if (m_pdisplay->m_px11display)
   //         {
   //
   //            while (m_pdisplay->m_px11display->aaa_x11_posted())
   //            {
   //
   //               bHandled = true;
   //
   //            }
   //
   //         }
   //
   //      }
   //
   //      process_owned_procedure_list(m_procedurelist, bHandled);
   //
   //      return bHandled;
   //
   //   }





   void windowing::windowing_post_quit()
   {

      ::gtk4::acme::windowing::windowing::windowing_post_quit();

   }



   //   void windowing::process_procedure_list(::procedure_list & procedurelist, bool & bHandled)
   //   {
   //
   //      synchronous_lock synchronouslock(this->synchronization());
   //
   //      if(procedurelist.is_empty())
   //      {
   //
   //         return;
   //
   //      }
   //
   //      do
   //      {
   //
   //         {
   //
   //            auto routine = procedurelist.pick_head();
   //
   //            synchronouslock.unlock();
   //
   //            routine();
   //
   //         }
   //
   //         synchronouslock.lock();
   //
   //      }
   //      while(procedurelist.has_element());
   //
   //   }


   ::windowing::display * windowing::display()
   {

      return ::windowing::windowing::display();

   }


   // ::wayland::micro::window_base * windowing::_window(::wl_surface * pwlsurface)
   // {
   //
   //    if (!m_pdisplay)
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //    auto pwindow = m_pdisplay->_window(pwlsurface);
   //
   //    return pwindow;
   //
   // }


   ::pointer<::windowing::cursor> windowing::load_default_cursor(enum_cursor ecursor)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_pcursormanager)
      {

         //auto estatus =
         //
         //
         __construct_new(m_pcursormanager);

         //         if (!estatus)
         //         {
         //
         //            return nullptr;
         //
         //         }

      }

      auto & pcursor = m_pcursormanager->m_cursormap[ecursor];

      if (pcursor)
      {

         return pcursor;

      }

      int iCursor = 0;

      if (ecursor == e_cursor_size_top_left)
      {

         iCursor = XC_top_left_corner;

      }
      else if (ecursor == e_cursor_size_top_right)
      {

         iCursor = XC_top_right_corner;

      }
      else if (ecursor == e_cursor_size_top)
      {

         iCursor = XC_top_side;

      }
      else if (ecursor == e_cursor_size_right)
      {

         iCursor = XC_right_side;

      }
      else if (ecursor == e_cursor_size_left)
      {

         iCursor = XC_left_side;

      }
      else if (ecursor == e_cursor_size_bottom)
      {

         iCursor = XC_bottom_side;

      }
      else if (ecursor == e_cursor_size_bottom_left)
      {

         iCursor = XC_bottom_left_corner;

      }
      else if (ecursor == e_cursor_size_bottom_right)
      {

         iCursor = XC_bottom_right_corner;

      }
      else if (ecursor == e_cursor_arrow)
      {

         iCursor = XC_arrow;

      }

      if (iCursor == 0)
      {

         return nullptr;

      }

      //synchronous_lock sl(user_synchronization());

      windowing_output_debug_string("::x11_GetWindowRect 1");

      //display_lock lock(m_pdisplay->Display());

      //      auto cursor = XCreateFontCursor(m_pdisplay->Display(), iCursor);
      //
      //      auto pcursorX11 = __øcreate < ::windowing_gtk4::cursor >();
      //
      //      pcursor = pcursorX11;
      //
      //      pcursorX11->m_cursor = cursor;

      //return pcursor;

      return nullptr;


   }


   //   void windowing::_message_handler(void * p)
   //   {
   //
   //      XEvent * pevent = (XEvent *) p;
   //
   //   }


   void windowing::clear_active_window(::thread *, ::windowing::window * pwindow)
   {

      if(::is_set(pwindow))
      {

         pwindow->window_minimize();

      }

   }


   ::acme::windowing::window * windowing::get_keyboard_focus(::thread *)
   {

      ::pointer < ::windowing_gtk4::display > pdisplay = m_pacmedisplay;

      if (!pdisplay)
      {

         return nullptr;

      }

      //auto pwindow = m_pdisplay->get_keyboard_focus();

      //return pwindow;

      return nullptr;

   }


   ::acme::windowing::window * windowing::get_mouse_capture(::thread *)
   {

      ::pointer < ::windowing_gtk4::display > pdisplay = m_pacmedisplay;

      if (!pdisplay)
      {

         return nullptr;

      }

      //auto pwindow = m_pdisplay->get_mouse_capture();

      //return pwindow;

      return m_pwindowMouseCapture;

   }


   ::acme::windowing::window * windowing::window(oswindow oswindow)
   {

      return oswindow;

   }


   void windowing::set_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow)
   {

      pwindow->set_mouse_capture();

   }


   void windowing::release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow)
   {

//      ::pointer < ::windowing_gtk4::display > pdisplay = m_pacmedisplay;

  //    pdisplay->release_mouse_capture();

//      if (m_pwindowMouseCapture == pwindow)
//      {
//
//         m_pwindowMouseCapture = nullptr;
//
//      }

      pwindow->release_mouse_capture();

   }


   bool windowing::defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow)
   {

      if(m_pwindowMouseCapture != pwindow)
      {

         return false;

      }

      release_mouse_capture(pthread, pwindow);

      return true;

   }


   void windowing::_on_capture_changed_to(::windowing_gtk4::window * pwindowMouseCaptureNew)
   {


   }



   void windowing::set_mouse_cursor2(::windowing::cursor * pcursor)
   {

      if (
         ::is_null(pcursor)
         )
      {

         return;

      }

      ::pointer < ::windowing_gtk4::cursor > pwaylandcursor = pcursor;

      if (!pwaylandcursor)
      {

         throw
            ::exception(error_null_pointer);

      }

      pwaylandcursor->_create_os_cursor();

      ::pointer < ::windowing_gtk4::display > pdisplay = m_pacmedisplay;

      auto pgtk4display = pdisplay;

      // auto pwlpointer = pwaylanddisplay->m_pwlpointer;
      //
      // if (pwlpointer && pwaylandcursor->m_waylandbuffer.m_pwlbuffer)
      // {
      //
      //    auto pwlsurfaceCursor = pwaylanddisplay->m_pwlsurfaceCursor;
      //
      //    wl_pointer_set_cursor(pwlpointer, pwaylanddisplay->m_uLastPointerSerial,
      //                          pwlsurfaceCursor,
      //                          pwaylandcursor->m_szHotspotOffset.cx(),
      //                          pwaylandcursor->m_szHotspotOffset.cy()
      //
      //    );
      //
      //    wl_surface_attach(pwlsurfaceCursor, pwaylandcursor->m_waylandbuffer.m_pwlbuffer, 0, 0);
      //
      //    wl_surface_damage(pwlsurfaceCursor, 0, 0,
      //                      pwaylandcursor->m_waylandbuffer.m_size.cx(),
      //                      pwaylandcursor->m_waylandbuffer.m_size.cy()
      //
      //    );
      //
      //    wl_surface_commit(pwlsurfaceCursor);
      //
      // }


      //
      //      m_pwindowing->windowing_post([this, pcursorx11]()
      //                                   {
      //
      //                                      if (!pcursorx11->m_cursor)
      //                                      {
      //
      //                                         //auto estatus =
      //                                         //
      //                                         pcursorx11->aaa_create_os_cursor();
      //
      ////         if(!estatus)
      ////         {
      ////
      ////            return estatus;
      ////
      ////         }
      //
      //                                      }
      //
      //                                      if (m_cursorLast == pcursorx11->m_cursor)
      //                                      {
      //
      //                                         //return true;
      //
      //                                         return;
      //
      //                                      }
      //
      //                                      synchronous_lock sl(user_synchronization());
      //
      //                                      windowing_output_debug_string("::SetCursor 1");
      //
      //                                      display_lock displaylock(x11_display()->Display());;
      //
      //                                      XDefineCursor(Display(), Window(), pcursorx11->m_cursor);
      //
      //                                      m_cursorLast = pcursorx11->m_cursor;
      //
      //                                   });
      //
      //return true;

   }


   //   static int open_restricted(const char *path, int flags, void *user_data)
   //   {
   //      int fd = ::open(path, flags);
   //      return fd < 0 ? -errno : fd;
   //   }
   //
   //   static void close_restricted(int fd, void *user_data)
   //   {
   //      ::close(fd);
   //   }
   //
   //   const static struct libinput_interface interface = {
   //      .open_restricted = open_restricted,
   //      .close_restricted = close_restricted,
   //   };
   //
   //
   //   void windowing::__handle_pointer_button(libinput_event * p)
   //   {
   //
   //      auto ppointer = libinput_event_get_pointer_event(p);
   //      auto button = libinput_event_pointer_get_button(ppointer);
   //      auto state = libinput_event_pointer_get_button_state(ppointer);
   //
   //      enum_message emessage = e_message_undefined;
   //
   //      if(button == BTN_LEFT)
   //      {
   //
   //         if(state == LIBINPUT_BUTTON_STATE_PRESSED)
   //         {
   //
   //            emessage = e_message_left_button_down;
   //
   //         }
   //         else if(state == LIBINPUT_BUTTON_STATE_PRESSED)
   //         {
   //
   //            emessage = e_message_left_button_up;
   //
   //         }
   //
   //      }
   //
   //      if(emessage != e_message_undefined)
   //      {
   //
   //         auto pmouse = __create_new < ::message::mouse >();
   //
   //         pmouse->m_emessage = emessage;
   //
   //         //pmouse->m_pointAbsolute.x() =
   //
   //         for(auto & pparticle : m_particleaMouseHandler)
   //         {
   //
   //            pparticle->handle(pmouse);
   //
   //         }
   //
   //      }
   //
   //
   //   }
   //
   //
   //   void windowing::__handle_keyboard_key(libinput_event * p)
   //   {
   //
   //      auto pkeyboard = libinput_event_get_keyboard_event(p);
   //      auto key = libinput_event_keyboard_get_key(pkeyboard);
   //      auto state = libinput_event_keyboard_get_key_state(pkeyboard);
   //
   //      enum_message emessage = e_message_undefined;
   //
   //      //if(button == BTN_LEFT)
   //      {
   //
   //         if(state == LIBINPUT_BUTTON_STATE_PRESSED)
   //         {
   //
   //            emessage = e_message_key_down;
   //
   //         }
   //         else if(state == LIBINPUT_BUTTON_STATE_PRESSED)
   //         {
   //
   //            emessage = e_message_key_up;
   //
   //         }
   //
   //      }
   //
   //      if(emessage != e_message_undefined)
   //      {
   //
   //         auto pkey = __create_new < ::message::key >();
   //
   //         pkey->m_emessage = emessage;
   //
   //         //pmouse->m_pointAbsolute.x() =
   //
   //         for(auto & pparticle : m_particleaKeyboardHandler)
   //         {
   //
   //            pparticle->handle(pkey);
   //
   //         }
   //
   //      }
   //
   //   }
   //
   //   void windowing::__libinput()
   //   {
   //
   //      if(__needs_libinput())
   //      {
   //
   //         if (m_ptaskLibInput)
   //         {
   //
   //            return;
   //
   //         }
   //
   //         m_ptaskLibInput = app_fork([this]()
   //                                    {
   //
   //                                       ::libinput_event * p;
   //
   //                                       auto pudev = udev_new();
   //
   //                                       auto plibinput = libinput_udev_create_context(&interface, NULL, pudev);
   //
   //                                       libinput_udev_assign_seat(plibinput, "seat0");
   //
   //                                       while (true)
   //                                       {
   //
   //                                          libinput_dispatch(plibinput);
   //
   //                                          auto p = libinput_get_event(plibinput);
   //
   //                                          if (!p)
   //                                          {
   //
   //                                             break;
   //
   //                                          }
   //
   //                                          __handle(p);
   //
   //                                       }
   //
   //                                       libinput_unref(plibinput);
   //
   //                                       udev_unref(pudev);
   //
   //
   //                                    });
   //
   //      }
   //      else
   //      {
   //
   //         if (m_ptaskLibInput)
   //         {
   //
   //            m_ptaskLibInput->set_finish();
   //
   //            m_ptaskLibInput.release();
   //
   //         }
   //
   //      }
   //
   //   }
   //
   //void windowing::__handle(::libinput_event * p)
   //{
   //auto etype = libinput_event_get_type(p);
   //
   //if (m_particleaMouseHandler.has_element())
   //{
   //
   //if (etype == LIBINPUT_EVENT_POINTER_BUTTON)
   //{
   //
   //__handle_pointer_button(p);
   //
   //}
   //
   //}
   //if (m_particleaMouseHandler.has_element())
   //{
   //
   //if (etype == LIBINPUT_EVENT_KEYBOARD_KEY)
   //{
   //
   //__handle_keyboard_key(p);
   //
   //}
   //
   //}
   //
   //libinput_event_destroy(p);
   //
   //}
   //
   //}
   //
   //
   //
   //
   //bool windowing::__needs_libinput()
   //   {
   //
   //      return m_particleaMouseHandler.has_element() || m_particleaKeyboardHandler.has_element();
   //
   //   }
   //
   //
   //   void windowing::install_mouse_message_handler(::particle * pparticle)
   //   {
   //
   //      {
   //
   //         synchronous_lock synchronouslock(this->synchronization());
   //
   //         m_particleaMouseHandler.add(pparticle);
   //
   //      }
   //
   //      __libinput();
   //
   //   }
   //
   //
   //   void windowing::install_keyboard_message_handler(::particle * pparticle)
   //   {
   //
   //      {
   //
   //         synchronous_lock synchronouslock(this->synchronization());
   //
   //         m_particleaKeyboardHandler.add(pparticle);
   //
   //      }
   //
   //      __libinput();
   //
   //   }
   //
   //
   //   void windowing::erase_mouse_message_handling(::particle * pparticle)
   //   {
   //
   //      {
   //
   //         synchronous_lock synchronouslock(this->synchronization());
   //
   //         m_particleaMouseHandler.erase(pparticle);
   //
   //      }
   //
   //      __libinput();
   //
   //   }
   //
   //
   //   void windowing::erase_keyboard_message_handling(::particle * pparticle)
   //   {
   //
   //      {
   //
   //         synchronous_lock synchronouslock(this->synchronization());
   //
   //         m_particleaKeyboardHandler.erase(pparticle);
   //
   //      }
   //
   //      __libinput();
   //
   //   }


   void windowing::_on_activate_gtk_application()
   {

      //g_object_ref(m_pgtkapplication);

      // auto pdisplay = __øcreate<::windowing::display>();
      //
      // pdisplay->initialize_display(this);
      //
      // m_pdisplay = pdisplay;
      //
      // if (!pdisplay)
      // {
      //
      //    throw ::exception(error_no_interface,
      //                      "Failed to cast pdisplay to m_pdisplay at windowing_gtk4::windowing::initialize");
      //
      // }
      //


      information() << "node_gtk4::_on_activate_gtk_application going to user_post";

      // This seems not to work with "foreign" windows
      // (X11 windows not created with Gdk)
      //x11_add_filter();

      information() << "node_gtk4::_on_activate_gtk_application on user_post";

      //gtk_add_idle_source(this);

      // auto psystem = system();
      //
      // psystem->defer_post_initial_request();

      system()->post_application_start();
      system()->defer_post_file_open();
      system()->post_application_started();

   }


   static void on_activate_gtk_application (GtkApplication *, gpointer p)
   {

      auto * pgtk4windowing=(::windowing_gtk4::windowing*) p;

      pgtk4windowing->_on_activate_gtk_application();

   }


   void windowing::windowing_application_main_loop()
   {
	   
	   information() << "windowing_gtk4::windowing_application_main_loop";

      ::pointer < ::gtk4::acme::windowing::windowing > pgtk4windowingsystem = system()->acme_windowing();

      pgtk4windowingsystem->m_callbackOnActivateGtkApplication=[this]()
      {
         _on_activate_gtk_application();

      };

      ::gtk4::acme::windowing::windowing::windowing_application_main_loop();




      //
      // ::string strId = application()->m_strAppId;
      //
      // strId.find_replace("/", ".");
      // strId.find_replace("_", "-");
      //
      // //gtk_init();
      //
      // m_pgtkapplication = gtk_application_new (strId, G_APPLICATION_DEFAULT_FLAGS);
      //
      // g_signal_connect (m_pgtkapplication, "activate", G_CALLBACK(on_activate_gtk_application), this);
      //
      //
      // // Retrieve system settings and listen for changes in dark mode preference
      // GtkSettings *settings = gtk_settings_get_default();
      // //update_theme_based_on_system(settings, NULL); // Check initial state
      // //g_signal_connect(settings, "notify::gtk-application-prefer-dark-theme", G_CALLBACK(update_theme_based_on_system), NULL);
      //
      // // Get the current GTK theme name (or any other available property)
      // //gboolean b=1;
      // g_object_set(settings, "gtk-application-prefer-dark-theme", TRUE, NULL);
      // //g_print("Current theme: %s\n", theme_name);
      //
      // // Free the allocated string after use
      // //g_free(theme_name);
      //
      // ///GtkSettings *settings = gtk_settings_get_default();
      // g_object_set(settings, "gtk-enable-animations", FALSE, NULL);
      //
      // g_application_hold(G_APPLICATION(m_pgtkapplication));
      //
      //
      // // if(m_pdisplay->is_wayland())
      // // {
      // //
      // //
      // //
      // // }
      //
      // g_application_run (G_APPLICATION(m_pgtkapplication), 0, nullptr);
      //
      // //g_application_run (G_APPLICATION(m_pgtkapplication), ::system()->get_argc(), ::system()->get_args());
      // //aaa_x11_main();
      //
      //
      // while(::task_get_run())
      // {
      //
      //    preempt(1_s);
      //
      // }

   }

   //
   // void windowing::_set_os_user_theme(const ::scoped_string &strOsUserTheme)
   // {
   //
   //    m_strOsUserTheme = strOsUserTheme;
   //
   //    if (!m_ptaskOsUserTheme)
   //    {
   //
   //       m_ptaskOsUserTheme = fork([this]()
   //                                 {
   //
   //                                    preempt(1_s);
   //
   //                                    m_ptaskOsUserTheme = nullptr;
   //
   //                                    _apply_os_user_theme();
   //
   //                                 });
   //
   //    }
   //
   // }

   //
   // void windowing::_set_os_user_icon_theme(const ::scoped_string &strOsUserIconTheme)
   // {
   //
   //    m_strOsUserIconTheme = strOsUserIconTheme;
   //
   //    if (!m_ptaskOsUserTheme)
   //    {
   //
   //       m_ptaskOsUserIconTheme = fork([this]()
   //                                 {
   //
   //                                    preempt(1_s);
   //
   //                                    m_ptaskOsUserIconTheme = nullptr;
   //
   //                                    _apply_os_user_icon_theme();
   //
   //                                 });
   //
   //    }
   //
   // }
   //
   //


   void windowing::set_dark_mode(bool bDarkMode)
   {

      ::gtk4::acme::windowing::windowing::set_dark_mode(bDarkMode);

   }


} // namespace windowing_gkt4




