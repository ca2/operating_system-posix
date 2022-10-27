// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "acme/operating_system/x11/nano/display.h"
#include "aura_posix/x11/windowing.h"
//#include <xcb/xcb.h>



namespace windowing_xcb
{


   class CLASS_DECL_WINDOWING_XCB windowing :
      virtual public ::windowing_posix::windowing
   {
   public:


      bool                                      m_bFirstWindowMap : 1;
      bool                                      m_bFinishXcbThread;

      ::pointer<::windowing_xcb::display>      m_pdisplay;
      //void *                                    m_pSnLauncheeContext;
      bool                                      m_bFinishX11Thread;
      bool                                      m_bInitX11Thread;



#ifdef WITH_XI

      int                                             m_xi_opcode = -1;
      ::pointer<object_array>                        m_pobjectaExtendedEventListener;

#endif



      windowing();
      ~windowing() override;


      void initialize(::particle * pparticle) override;


      virtual bool initialize_windowing();

      virtual bool terminate_windowing();

      virtual bool post_ui_message(const MESSAGE & message);

      virtual bool post_ui_message(::message::message * pmessage);

      //void start() override;


      void windowing_post(const ::procedure & procedure) override;


      virtual void __defer_post_move_and_or_size(xcb_window_t window);


      //virtual void _libsn_start_context()  override;
      virtual ::windowing::display * display() override;


      Display * _get_Display();
      ::x11::display * _get_display();
      xcb_connection_t * _get_connection();



      virtual void windowing_main() override;


      //virtual void windowing_post_quit() override;


      void release_mouse_capture() override;


      virtual void xcb_main();

      //virtual HCURSOR load_default_cursor(e_cursor ecursor) override;
      virtual ::pointer<::windowing::cursor>load_default_cursor(enum_cursor ecursor);

      //virtual int_bool window_set_mouse_cursor(window * pwindow, HCURSOR hcursor) override;

      //virtual bool set_window_icon(window * pwindow, const ::file::path & path) override;

      //virtual ::windowing::window * new_message_window(::user::interaction_impl * pimpl) override;

      virtual ::windowing::window * new_window(::user::interaction_impl * pimpl) override;

      void erase_window(::windowing::window * pwindow);

      virtual ::windowing_xcb::window * _window(xcb_window_t window);


      virtual void _message_handler(void * p);

//      SnLauncheeContext* g_psncontext = nullptr;

      //void x_display_error_trap_push(SnDisplay * sndisplay, xcb_connection_t * display);

      //void x_display_error_trap_pop(SnDisplay * sndisplay, xcb_connection_t * display);
      //void x_display_error_trap_pop(SnDisplay * sndisplay, xcb_connection_t * display);


//      Display * _get_Display();
//      ::x11::display * _get_display();
//      xcb_connection_t * _get_connection();


      void install_mouse_hook(::matter * pmatterListener) override;
      void install_keyboard_hook(::matter * pmatterListener) override;

      void uninstall_mouse_hook(::matter * pmatterListener) override;
      void uninstall_keyboard_hook(::matter * pmatterListener) override;


      ::windowing::window * get_active_window(::thread * pthread) override;

      ::windowing::window * get_keyboard_focus(::thread * pthread) override;

      ::windowing::window * get_mouse_capture(::thread * pthread) override;

      void clear_active_window(::thread * pthread, ::windowing::window * pwindow) override;

      virtual bool xcb_on_event(xcb_generic_event_t * pevent);

      virtual bool xcb_message_handler(xcb_generic_event_t * pevent);

      //virtual bool __xcb_hook_process_event(xcb_generic_event_t * pevent, XGenericEventCookie * cookie);

      //virtual bool __xcb_hook_list_is_empty();

      virtual bool xcb_message_loop_step();

      virtual ::windowing::window * window(oswindow oswindow) override;

      //virtual void _libsn_start_context() override;


#ifdef WITH_XI

      void register_extended_event_listener(::matter *pdata, bool bMouse, bool bKeyboard);

//      virtual ::e_status install_mouse_hook(::matter * pmatterListener);
//      virtual ::e_status install_keyboard_hook(::matter * pmatterListener);
//
//      virtual ::e_status uninstall_mouse_hook(::matter * pmatterListener);
//      virtual ::e_status uninstall_keyboard_hook(::matter * pmatterListener);

      bool xcb_process_event(xcb_generic_event_t* xcbevent);
      bool xcb_process_ge_event(xcb_ge_event_t * pgeevent);

#else

      bool xcb_process_event(xcb_connection_t * pdisplay, xcb_generic_event_t * pevent);

#endif


      bool _xcb_process_event(void * p) override;



   };


} // namespace windowing



