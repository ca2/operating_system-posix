// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "windowing_posix/windowing.h"
#include "acme/prototype/collection/list.h"
#include "_.h"
#include "acme_windowing_gtk4/windowing.h"
#include "acme_windowing_gtk4/_gtk4.h"


struct libinput_event;


namespace windowing_gtk4
{


   class CLASS_DECL_WINDOWING_GTK4 windowing :
      virtual public ::windowing_posix::windowing,
      virtual public ::gtk4::acme::windowing::windowing
   {
   public:


      ::string m_strOsUserTheme;
      ::string m_strOsUserIconTheme;
      ::task_pointer m_ptaskOsUserTheme;
      ::task_pointer m_ptaskOsUserIconTheme;


      windowing();


      ~windowing() override;


      void initialize(::particle* pparticle) override;


      //void initialize_windowing(::user::user* puser) override;


      void initialize_windowing() override;


      void destroy() override;


      bool has_readily_gettable_absolute_coordinates() const override;


      bool is_branch_current() const override;


      void windowing_post_quit() override;


      //::pointer <::input::input> _get_input() override;


      //void start() override;

      //void _libsnx_start_context()  override;

      ::windowing::display* display() override;


      void set_mouse_capture(::thread* pthread, ::acme::windowing::window* pwindow) override;


      ::acme::windowing::window* get_mouse_capture(::thread* pthread) override;


      void release_mouse_capture(::thread* pthread, ::acme::windowing::window* pwindow) override;


      bool defer_release_mouse_capture(::thread* pthread, ::acme::windowing::window* pwindow) override;


      virtual void _on_capture_changed_to(::windowing_gtk4::window* pwindowWithCapture);


      void set_mouse_cursor2(::windowing::cursor* pcursor) override;


      //virtual void x11_main();

      //virtual HCURSOR load_default_cursor(e_cursor ecursor) override;
      virtual ::pointer<::windowing::cursor> load_default_cursor(enum_cursor ecursor) override;


      //virtual int_bool window_set_mouse_cursor(window * pwindow, HCURSOR hcursor) override;

      //virtual bool set_window_icon(window * pwindow, const ::file::path & path) override;

      //virtual ::windowing::window * new_message_window(::windowing::window * pimpl) override;

      //::windowing::window * new_window(::windowing::window * pimpl) override;

      void erase_window(::windowing::window* pwindow) override;


      //virtual ::wayland::micro::window_base * _window(::wl_surface * pwlsurface);


      //virtual void _message_handler(void * p);

      //      SnLauncheeContext* g_psncontext = nullptr;

      //void x_display_error_trap_push(SnDisplay * sndisplay, Display * display);

      //void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);
      //void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);


      // ::windowing::window* get_active_window(::thread* pthread) override;

      void clear_active_window(::thread*, ::windowing::window*) override;


      ::acme::windowing::window* get_keyboard_focus(::thread* pthread) override;


      void _on_activate_gtk_application() override;


      ///::pointer < ::input::input > get_input() override;

      //::windowing::window * get_mouse_capture(::thread * pthread) override;

      // void clear_active_window(::thread* pthread, ::windowing::window* pwindow) override;

      //virtual bool x11_on_event(XEvent * pevent);

      //virtual bool x11_message_handler(XEvent * pevent);

      //virtual bool __x11_hook_process_event(XEvent * pevent, XGenericEventCookie * cookie);

      //virtual bool __x11_hook_list_is_empty();

      //virtual bool x11_message_loop();

      //virtual bool aaa_x11_message_loop_step();

      //void windowing_post(const ::procedure & procedure) override;

      //virtual bool aaa_x11_runnable_step();

      virtual ::acme::windowing::window* window(oswindow oswindow) override;


      //virtual void _libsn_start_context() override;

#ifdef WITH_XI

      //void x11_register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);
      //bool x11_process_event(XEvent * pevent, XGenericEventCookie *cookie);

#else

      //bool x11_process_event(Display * pdisplay, XEvent * pevent);

#endif


      //void _on_wm_state_change(::windowing::window * pwindow) override;

      void windowing_application_main_loop() override;


      void set_dark_mode(bool bDarkMode) override;


   };


} // namespace windowing_gtk4
