// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "windowing_posix/windowing.h"
#include "acme_windowing_x11/windowing.h"
#include "apex/input/input.h"
#include "_x11.h"


namespace windowing_x11
{


   class CLASS_DECL_WINDOWING_X11 windowing :
      virtual public ::windowing_posix::windowing,
      virtual public ::x11::acme::windowing::windowing,
      virtual public ::input::input
   {
   public:


      class ::time                                    m_timeLastMotionNotify;
      class ::time                                    m_timeLastMotionTracing;
      bool                                            m_bRootSelectInput : 1;
      bool                                            m_bFirstWindowMap : 1;

      //::pointer<::windowing_x11::display>            m_pdisplay;
      bool                                            m_bFinishX11Thread;
      bool                                            m_bInitX11Thread;

      itask                                         m_itask;

#ifdef WITH_XI

      int                                             m_xi_opcode = -1;
      ::pointer<particle_array>                        m_pobjectaExtendedEventListener;

#endif

      ::procedure_list_base                                m_procedurelist;
      ::procedure_list_base                                m_procedurelistPriority;

      windowing();
      ~windowing() override;


      void initialize(::particle * pparticle) override;

      //void initialize_windowing(::user::user * puser) override;

      void initialize_windowing() override;


      bool is_branch_current() const override;


      //virtual void initialize_windowing();

      virtual void terminate_windowing();

      //virtual void post_ui_message(const MESSAGE & message);

      //virtual void post_ui_message(::message::message * pmessage);


      //void _send(const ::procedure & procedure) override;
      //void _post(const ::procedure & procedure) override;

      void _user_send(const ::procedure &procedure) override;
      void _user_post(const ::procedure &procedure) override;

      //void add_mouse_message_handler(::particle * pparticle) override;
      //void add_keyboard_message_handler(::particle * pparticle) override;

      //void erase_mouse_message_handler(::particle * pparticle) override;
      //void erase_keyboard_message_handler(::particle * pparticle) override;

      //void start() override;

      //void _libsnx_start_context()  override;

      //::windowing::display * display() override;

      //void windowing_main() override;

      bool message_loop_step() override;

      void windowing_post_quit() override;


      void release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow) override;

      bool defer_release_mouse_capture(::thread * pthread, ::acme::windowing::window * pwindow) override;


      //virtual void x11_main();

      //virtual HCURSOR load_default_cursor(e_cursor ecursor) override;
      virtual ::pointer<::windowing::cursor>load_default_cursor(enum_cursor ecursor) override;

      //virtual int_bool window_set_mouse_cursor(window * pwindow, HCURSOR hcursor) override;

      //virtual bool set_window_icon(window * pwindow, const ::file::path & path) override;

      //virtual ::windowing::window * new_message_window(::windowing::window * pimpl) override;

      //::windowing::window * new_window(::windowing::window * pimpl) override;

      void erase_window(::windowing::window * pwindow) override;

      virtual ::windowing_x11::window * _window(Window window);


      void _message_handler(void * p) override;

//      SnLauncheeContext* g_psncontext = nullptr;

      //void x_display_error_trap_push(SnDisplay * sndisplay, Display * display);

      //void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);
      //void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);


      ::windowing::window * get_active_window(::thread * pthread) override;

      ::acme::windowing::window * get_keyboard_focus(::thread * pthread) override;

      virtual ::acme::windowing::window * get_mouse_capture(::thread * pthread) override;

      void clear_active_window(::thread * pthread, ::windowing::window * pwindow) override;

      //virtual bool x11_on_event(XEvent * pevent);

      //virtual bool x11_message_handler(XEvent * pevent);

      //virtual bool __x11_hook_process_event(XEvent * pevent, XGenericEventCookie * cookie);

      //virtual bool __x11_hook_list_is_empty();

      //virtual bool aaa_x11_message_loop();

      virtual bool x11_message_loop_step();

      //void windowing_post(const ::procedure & procedure) override;

      virtual bool x11_runnable_step();

      //::acme::windowing::window * get_mouse_capture(::thread * pthread) override;

      //virtual void _libsnx_start_context() override;

      bool __on_x11_event(XEvent * pevent) override;

#ifdef WITH_XI

      //void x11_register_extended_event_listener(::particle * pdata, bool bMouse, bool bKeyboard);
      bool x11_process_event(XEvent * pevent, XGenericEventCookie *cookie);

#else

      bool x11_process_event(Display * pdisplay, XEvent * pevent);

#endif


      virtual void _on_wm_state_change(::windowing::window * pwindow);

      void windowing_application_main_loop();


   };


} // namespace windowing



