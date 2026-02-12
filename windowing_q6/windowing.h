// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "acme_windowing_q6/windowing.h"
#include "windowing_q/windowing.h"
#include "acme/prototype/collection/list.h"
//#include "acme/prototype/collection/pointer_array.h"
#include "_.h"
#include "_q6.h"
#include "acme_windowing_q6/windowing.h"

#include <QApplication>

struct libinput_event;


namespace windowing_q6
{


   class CLASS_DECL_WINDOWING_Q6 windowing :
      virtual public ::windowing_q::windowing,
      virtual public ::q6::acme::windowing::windowing
   {
   public:

      //
      // //gpointer m_pGtkSettingsDefault;
      //
      // //GtkApplication* m_pgtkapplication;
      //
      //  //QApplication * m_pqapplication;
      //
      // ::logic::boolean     m_booleanX11;
      //
      //
      //
      // bool m_bRootSelectInput: 1;
      // bool m_bFirstWindowMap: 1;
      //
      // //::pointer<::windowing_kde5::display> m_pdisplay;
      // bool m_bFinishX11Thread;
      // bool m_bInitX11Thread;
      //
      // itask m_itask;
      //
      // //#ifdef WITH_XI
      // //
      // //      int                                             m_xi_opcode = -1;
      // //      ::pointer<particle_array>                        m_pobjectaExtendedEventListener;
      // //
      // //#endif
      //
      // ::procedure_list m_procedurelist;
      // ::procedure_list m_procedurelistPriority;
      //
      //
      // ::string       m_strOsUserTheme;
      // ::string       m_strOsUserIconTheme;
      // ::task_pointer       m_ptaskOsUserTheme;
      // ::task_pointer       m_ptaskOsUserIconTheme;
      //
      //


      windowing();

      ~windowing() override;

//
//       void initialize(::particle* pparticle) override;
//
//       void initialize_windowing() override;
//
//       bool defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow) override;
//
//
//       bool has_readily_gettable_absolute_coordinates() const override;
//
//
//       bool is_branch_current() const override;
// bool is_x11();
//
//        virtual QApplication * qapplication();
//
//       //virtual void initialize_windowing();
//
//       //virtual void terminate_windowing();
//
//       //virtual void post_ui_message(const MESSAGE& message);
//
//       //virtual void post_ui_message(::message::message* pmessage);
//
//       void windowing_post_quit() override;
//
//       //::pointer <::input::input> _get_input() override;
//
//
//       //void start() override;
//
//       //void _libsnx_start_context()  override;
//
//       ::windowing::display* display() override;
//
//       ::windowing_q6::display* q6_display();
//
//       //void windowing_main() override;
//
//
//       //void windowing_post_quit() override;
//
//
//       //virtual bool os_defer_init_kde5();
//
//        void _user_post(const ::procedure & procedureParam) override;
//
//
//       virtual void _set_os_user_theme(const ::scoped_string & strTheme);
//       virtual void _apply_os_user_theme();
//       virtual void _os_process_user_theme(const ::scoped_string & scopedstrOsUserTheme);
//       virtual ::string _get_os_user_theme();
//
//
//       virtual void _set_os_user_icon_theme(const ::scoped_string & strIconTheme);
//       virtual void _apply_os_user_icon_theme();
//       virtual void _os_process_user_icon_theme(const ::scoped_string & scopedstrOsUserIconTheme);
//
//
//       virtual void _fetch_dark_mode();
//
//       //void set_mouse_capture(::thread* pthread, ::windowing::window* pwindow) override;
//
//       //::windowing::window* get_mouse_capture(::thread* pthread) override;
//
//       //void release_mouse_capture(::thread* pthread) override;
//
//       //bool defer_release_mouse_capture(::thread* pthread, ::windowing::window* pwindow) override;
//
//       virtual void _on_capture_changed_to(::windowing_q6::window* pwindowWithCapture);
//
//       void set_mouse_cursor2(::windowing::cursor* pcursor) override;
//
//       //virtual void x11_main();
//
//       //virtual HCURSOR load_default_cursor(e_cursor ecursor) override;
//       virtual ::pointer<::windowing::cursor> load_default_cursor(enum_cursor ecursor) override;
//
//       //virtual int_bool window_set_mouse_cursor(window * pwindow, HCURSOR hcursor) override;
//
//       //virtual bool set_window_icon(window * pwindow, const ::file::path & path) override;
//
//       //virtual ::windowing::window * new_message_window(::windowing::window * pimpl) override;
//
//       //::windowing::window * new_window(::windowing::window * pimpl) override;
//
//       void erase_window(::windowing::window* pwindow) override;
//
//       //virtual ::wayland::micro::window_base * _window(::wl_surface * pwlsurface);
//
//
//       //virtual void _message_handler(void * p);
//
//       //      SnLauncheeContext* g_psncontext = nullptr;
//
//       //void x_display_error_trap_push(SnDisplay * sndisplay, Display * display);
//
//       //void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);
//       //void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);
//
//
//       // ::windowing::window* get_active_window(::thread* pthread) override;
//
//       ::acme::windowing::window* get_keyboard_focus(::thread* pthread) override;
//
//       //void _on_activate_kde_application();
//       ///::pointer < ::input::input > get_input() override;
//
//       //::windowing::window * get_mouse_capture(::thread * pthread) override;
//
//       // void clear_active_window(::thread* pthread, ::windowing::window* pwindow) override;
//
//       //virtual bool x11_on_event(XEvent * pevent);
//
//       //virtual bool x11_message_handler(XEvent * pevent);
//
//       //virtual bool __x11_hook_process_event(XEvent * pevent, XGenericEventCookie * cookie);
//
//       //virtual bool __x11_hook_list_is_empty();
//
//       //virtual bool x11_message_loop();
//
//       //virtual bool aaa_x11_message_loop_step();
//
//       //void windowing_post(const ::procedure & procedure) override;
//
//       //virtual bool aaa_x11_runnable_step();
//
//       ::acme::windowing::window* window(::acme::windowing::window * pacmewindowingwindow) override;
//
//       //virtual void _libsn_start_context() override;
//
// #ifdef WITH_XI
//
//       //void x11_register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);
//       //bool x11_process_event(XEvent * pevent, XGenericEventCookie *cookie);
//
// #else
//
//       //bool x11_process_event(Display * pdisplay, XEvent * pevent);
//
// #endif
//
//
//       //void _on_wm_state_change(::windowing::window * pwindow) override;
//
//       void windowing_application_main_loop() override;
   };


} // namespace windowing_q6



