// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "aura_posix/x11/windowing.h"
#include "acme/primitive/collection/list.h"
//#include "acme/primitive/collection/pointer_array.h"
#include "_.h"
#include "_wayland.h"

struct libinput_event;

namespace windowing_wayland
{


   class CLASS_DECL_WINDOWING_WAYLAND windowing :
      virtual public ::windowing_posix::windowing
   {
   public:


      bool                                            m_bRootSelectInput : 1;
      bool                                            m_bFirstWindowMap : 1;

      ::pointer<::windowing_wayland::display>            m_pdisplay;
      bool                                            m_bFinishX11Thread;
      bool                                            m_bInitX11Thread;

      itask_t                                         m_itask;

//#ifdef WITH_XI
//
//      int                                             m_xi_opcode = -1;
//      ::pointer<particle_array>                        m_pobjectaExtendedEventListener;
//
//#endif

      ::procedure_list                                m_procedurelist;
      ::procedure_list                                m_procedurelistPriority;
      ::pointer < ::windowing_wayland::window >       m_pwindowMouseCapture;


      windowing();
      ~windowing() override;


      void initialize(::particle * pparticle) override;

      void initialize_windowing(::user::user * puser) override;


      bool has_readily_gettable_absolute_coordinates() const override;


      bool is_branch_current() const override;


      //virtual void initialize_windowing();

      virtual void terminate_windowing();

      virtual void post_ui_message(const MESSAGE & message);

      virtual void post_ui_message(::message::message * pmessage);


      ::pointer <::input::input> _get_input() override;


      //void start() override;

      //void _libsn_start_context()  override;

      ::windowing::display * display() override;

      //void windowing_main() override;


      void windowing_post_quit() override;


      void set_mouse_capture(::thread * pthread, ::windowing::window * pwindow) override;

      ::windowing::window * get_mouse_capture(::thread * pthread) override;

      void release_mouse_capture(::thread * pthread) override;

      bool defer_release_mouse_capture(::thread * pthread, ::windowing::window * pwindow) override;

      virtual void _on_capture_changed_to(::windowing_wayland::window * pwindowWithCapture);

      void set_mouse_cursor(::windowing::cursor * pcursor)override;
      //virtual void x11_main();

      //virtual HCURSOR load_default_cursor(e_cursor ecursor) override;
      virtual ::pointer<::windowing::cursor>load_default_cursor(enum_cursor ecursor) override;

      //virtual int_bool window_set_mouse_cursor(window * pwindow, HCURSOR hcursor) override;

      //virtual bool set_window_icon(window * pwindow, const ::file::path & path) override;

      //virtual ::windowing::window * new_message_window(::user::interaction_impl * pimpl) override;

      ::windowing::window * new_window(::user::interaction_impl * pimpl) override;

      void erase_window(::windowing::window * pwindow) override;

      virtual ::wayland::nano_window_base * _window(::wl_surface * pwlsurface);


      //virtual void _message_handler(void * p);

//      SnLauncheeContext* g_psncontext = nullptr;

      //void x_display_error_trap_push(SnDisplay * sndisplay, Display * display);

      //void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);
      //void x_display_error_trap_pop(SnDisplay * sndisplay, Display * display);


      ::windowing::window * get_active_window(::thread * pthread) override;

      ::windowing::window_base * get_keyboard_focus(::thread * pthread) override;


      ///::pointer < ::input::input > get_input() override;

      //::windowing::window * get_mouse_capture(::thread * pthread) override;

      void clear_active_window(::thread * pthread, ::windowing::window * pwindow) override;

      //virtual bool x11_on_event(XEvent * pevent);

      //virtual bool x11_message_handler(XEvent * pevent);

      //virtual bool __x11_hook_process_event(XEvent * pevent, XGenericEventCookie * cookie);

      //virtual bool __x11_hook_list_is_empty();

      //virtual bool x11_message_loop();

      //virtual bool x11_message_loop_step();

      //void windowing_post(const ::procedure & procedure) override;

      //virtual bool x11_runnable_step();

      virtual ::windowing::window * window(oswindow oswindow) override;

      //virtual void _libsn_start_context() override;

#ifdef WITH_XI

      //void x11_register_extended_event_listener(::matter * pdata, bool bMouse, bool bKeyboard);
      //bool x11_process_event(XEvent * pevent, XGenericEventCookie *cookie);

#else

      //bool x11_process_event(Display * pdisplay, XEvent * pevent);

#endif


      //void _on_wm_state_change(::windowing::window * pwindow) override;


   };


} // namespace windowing



