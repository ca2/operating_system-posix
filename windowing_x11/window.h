// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#define _NET_WM_STATE_REMOVE        0    // remove/unset property
#define _NET_WM_STATE_ADD           1    // add/set property
#define _NET_WM_STATE_TOGGLE        2    // toggle property


#define WINDOWING_X11_WINDOW_MEMBER
//using htask_t = pthread_t;

namespace windowing_x11
{


   class CLASS_DECL_WINDOWING_X11 window :
      virtual public ::windowing::window
   {
   public:


      XWindowAttributes                            m_attr;
      XVisualInfo                                  m_visualinfo;
      void *                                       m_pgdkwindow;
      __pointer(::windowing_x11::x11data)          m_px11data;
      ::Window                                     m_parent;
      Cursor                                       m_cursorLast;
      int                                          m_iXic;
      XIC                                          m_xic;
      //__pointer(::windowing_x11::display)     m_pdisplay;
      ::Window                                     m_window;
      ::Visual                                     m_visual;
      int                                          m_iDepth;
      //int                                          m_iScreen;
      bool                                         m_bMessageOnlyWindow;
      //__pointer(::user::interaction_impl)     m_pimpl;
      //__pointer(::message_queue)              m_pmessagequeue;
      htask_t                                    m_hthread;
      //Colormap                                     m_colormap;
      millis                                       m_millisLastMouseMove;
      //Window                                       m_parent;
      ::rectangle_i32                              m_rect;
      string                                       m_strWMClass;
      int                                          m_iaNetWmState2[x_window::e_atom_net_wm_state_last-x_window::e_atom_net_wm_state_first+1];

      //static oswindow_dataptra *                 s_pdataptra;
      //static::mutex *                            s_pmutex;

      //static Atom                                s_atomLongType;
      //static Atom                                s_atomLongStyle;
      //static Atom                                s_atomLongStyleEx;


      window();
      //oswindow_data(::user::interaction * puibaseMessageOnlyWindow);
      //oswindow_data(const void * p);
      //oswindow_data(const LPARAM & lparam);
      //oswindow_data(const WPARAM & wparam);
      virtual ~window();


      virtual ::e_status create_window(::user::interaction_impl * pimpl) override;


      static Atom get_window_long_atom(i32 nIndex);


      inline int net_wm_state(x_window::enum_atom eatom) const
      {

         return m_iaNetWmState2[eatom - x_window::e_atom_net_wm_state_first];

      }


      virtual ::Display * Display();

      virtual ::Display * Display() const;

      virtual int Screen();

      virtual int Screen() const;

      virtual ::Window Window();

      virtual ::Window Window() const;

      virtual ::Visual * Visual();

      virtual const ::Visual * Visual() const;

      //virtual ::Window root_window_raw() const;

      virtual void unmapped_net_state_raw(Atom atom1, ...);

      virtual ::e_status initialize_x11_window(::windowing_x11::display * pdisplay, ::Window window, ::Visual *pvisual, int iDepth, int iScreen, Colormap colormap);

      virtual void send_client_event(Atom atom, unsigned int numArgs, ...);
      virtual i32 store_name(const char * psz);
      virtual i32 select_input(i32 iInput);
      virtual i32 select_all_input();
      virtual i32 map_window();
      virtual i32 unmap_window(bool bWithdraw);
      virtual void set_wm_class(const char * psz);

      virtual ::e_status exit_iconify() override;

      virtual ::e_status full_screen(const ::rectangle_i32 & rect = nullptr) override;

      virtual ::e_status exit_full_screen() override;

      virtual ::e_status exit_zoomed() override;

      virtual void set_user_interaction(::user::interaction_impl * pinteraction);

      virtual void post_nc_destroy();

      virtual ::e_status set_window_icon(const ::file::path & path);

      virtual bool is_child( WINDOWING_X11_WINDOW_MEMBER ::windowing::window * candidateChildOrDescendant); // or descendant
      virtual ::windowing::window * get_parent() const;
      //virtual ::Window get_parent_handle();
      virtual oswindow get_parent_oswindow() const;

      //virtual ::Window get_parent_handle() const;

      ::windowing_x11::windowing * x11_windowing() const {return (::windowing_x11::windowing *) m_pwindowing->m_pWindowing; }
      ::windowing_x11::display * x11_display() const {return (::windowing_x11::display *) m_pdisplay->m_pDisplay; }

      virtual ::e_status set_parent(::windowing::window * pwindowNewParent);
      //virtual ::e_status set_parent(::windowing::window * pwindowNewParent) override;
      virtual long get_state();
      virtual bool is_iconic();
      virtual bool is_window_visible();
      virtual ::e_status show_window(const ::e_display & edisplay, const ::e_activation & eactivation);
      //virtual iptr get_window_long_ptr(i32 nIndex);
      //virtual iptr set_window_long_ptr(i32 nIndex, iptr l);
      virtual bool _001ClientToScreen(POINT_I32 * ppoint);

      virtual bool _001ScreenToClient(POINT_I32 * ppoint);


      //virtual bool set_window_pos(class::zorder zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);
      //virtual bool _set_window_pos(class::zorder zorder, i32 x, i32 y, i32 cx, i32 cy,::u32 nFlags);
      

      virtual bool is_destroying();
      

      virtual bool bamf_set_icon();


      virtual bool set_icon(::image * pimage);

      virtual int x_change_property(Atom property, Atom type, int format, int mode, const unsigned char * data, int nelements);

      virtual ::e_status set_mouse_cursor(::windowing::cursor * pcursor);

      virtual ::e_status set_mouse_cursor2(::windowing::cursor * pcursor);

      virtual ::e_status set_keyboard_focus() override;
      virtual ::e_status set_mouse_capture() override;
      virtual ::e_status set_active_window() override;


      virtual ::e_status set_foreground_window() override;


      virtual bool has_mouse_capture() const override;

      virtual bool has_keyboard_focus() const override;




      //virtual Atom get_window_long_atom(i32 nIndex);
      virtual void mapped_net_state_raw(bool add,  WINDOWING_X11_WINDOW_MEMBER int iScreen, Atom state1, Atom state2);
      //virtual void unmapped_net_state_raw( WINDOWING_X11_WINDOW_MEMBER ...);
      virtual bool x11_get_window_rect(  WINDOWING_X11_WINDOW_MEMBER  RECTANGLE_I32 * prectangle);
      virtual bool x11_get_client_rect(  WINDOWING_X11_WINDOW_MEMBER  RECTANGLE_I32 * prectangle);
      //virtual oswindow set_capture( WINDOWING_X11_WINDOW_MEMBER );
      //virtual int_bool release_capture();
      //virtual oswindow set_focus( WINDOWING_X11_WINDOW_MEMBER );
      //virtual void x11_check_status(int status, unsigned long window);
      //virtual unsigned long x11_get_long_property( WINDOWING_X11_WINDOW_MEMBER char* property_name);
      virtual string x11_get_name( WINDOWING_X11_WINDOW_MEMBER );
      //virtual ::e_status set_active_window();
      virtual void upper_window_rects( WINDOWING_X11_WINDOW_MEMBER  rectangle_i32_array & ra);
      //virtual oswindow set_active_window( WINDOWING_X11_WINDOW_MEMBER );
//      virtual  WINDOWING_X11_WINDOW_MEMBER _get_if_found(Window w);
      //virtual oswindow get_parent( WINDOWING_X11_WINDOW_MEMBER );
      virtual ::Window _get_window_relative( WINDOWING_X11_WINDOW_MEMBER enum_relative erelative, ::Window * windowa, int numItems);
      virtual ::windowing::window * get_window( WINDOWING_X11_WINDOW_MEMBER enum_relative erelative);

      virtual ::e_status destroy_window();
      //virtual int_bool destroy_window( WINDOWING_X11_WINDOW_MEMBER );
      virtual bool is_window();
      //virtual int_bool is_window( WINDOWING_X11_WINDOW_MEMBER );


      virtual void set_window_text(const char * pszString);


      virtual ::e_status set_tool_window(bool bSet) override;


      virtual bool set_window_position(const class ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags) override;



      virtual comparable_array < Atom > wm_get_list_raw( WINDOWING_X11_WINDOW_MEMBER Atom atomList);
      virtual int wm_test_state( WINDOWING_X11_WINDOW_MEMBER const char * pszNetStateFlag);
      virtual int wm_test_state_raw( WINDOWING_X11_WINDOW_MEMBER const char * pszNetStateFlag);
      virtual int wm_test_list_raw( WINDOWING_X11_WINDOW_MEMBER Atom atomList, Atom atomFlag);
      virtual bool wm_add_remove_list_raw( WINDOWING_X11_WINDOW_MEMBER Atom atomList, Atom atomFlag, bool bSet);
      virtual void wm_add_remove_state_mapped_raw( WINDOWING_X11_WINDOW_MEMBER x_window::enum_atom eatomNetWmState, bool bSet);
      virtual void wm_add_remove_state_mapped( WINDOWING_X11_WINDOW_MEMBER x_window::enum_atom eatomNetWmState, bool bSet);
      virtual void wm_add_remove_state_unmapped_raw( WINDOWING_X11_WINDOW_MEMBER x_window::enum_atom eatomNetWmState, bool bSet);
      virtual void wm_add_remove_state_unmapped( WINDOWING_X11_WINDOW_MEMBER x_window::enum_atom eatomNetWmState, bool bSet);
      virtual void wm_add_remove_state_raw( WINDOWING_X11_WINDOW_MEMBER x_window::enum_atom eatomNetWmState, bool bSet);
      virtual void wm_add_remove_state( WINDOWING_X11_WINDOW_MEMBER x_window::enum_atom eatomNetWmState, bool bSet);
      virtual void wm_state_clear_raw( WINDOWING_X11_WINDOW_MEMBER bool bSet);
      virtual void wm_state_below_raw( WINDOWING_X11_WINDOW_MEMBER bool bSet);
      virtual void wm_state_above_raw( WINDOWING_X11_WINDOW_MEMBER bool bSet);
      virtual void wm_state_hidden_raw( WINDOWING_X11_WINDOW_MEMBER bool bSet);
      virtual void wm_state_above( WINDOWING_X11_WINDOW_MEMBER bool bSet);
      virtual void wm_state_below( WINDOWING_X11_WINDOW_MEMBER bool bSet);
      virtual void wm_state_hidden( WINDOWING_X11_WINDOW_MEMBER bool bSet);
      virtual void wm_toolwindow( WINDOWING_X11_WINDOW_MEMBER bool bToolWindow);
      virtual void wm_normalwindow();
      virtual void wm_hidden_state( WINDOWING_X11_WINDOW_MEMBER bool bHidden);
      virtual void wm_desktopwindow( WINDOWING_X11_WINDOW_MEMBER bool bDesktopWindow);
      virtual void wm_centerwindow( WINDOWING_X11_WINDOW_MEMBER bool bCenterWindow);
      virtual void wm_splashwindow( WINDOWING_X11_WINDOW_MEMBER bool bCenterWindow);
      virtual void wm_dockwindow( WINDOWING_X11_WINDOW_MEMBER bool bDockWindow);
      virtual void wm_nodecorations( WINDOWING_X11_WINDOW_MEMBER int bMap);
      virtual void _wm_nodecorations( WINDOWING_X11_WINDOW_MEMBER int bMap);
      virtual int_bool IsWindowVisibleRaw( WINDOWING_X11_WINDOW_MEMBER);
      virtual void wm_iconify_window( WINDOWING_X11_WINDOW_MEMBER );
      //virtual int_bool IsWindowVisibleRaw( WINDOWING_X11_WINDOW_MEMBER);
      //virtual int_bool IsWindowVisibleRaw(oswindow w);
//      virtual Atom * wm_get_list_raw( WINDOWING_X11_WINDOW_MEMBER Atom atomList, unsigned long int * pnum_items);
//      virtual int wm_test_list_raw( WINDOWING_X11_WINDOW_MEMBER Atom atomList, Atom atomFlag);
//      virtual int wm_test_state_raw( WINDOWING_X11_WINDOW_MEMBER const char * pszNetStateFlag);
//      virtual int wm_test_state( WINDOWING_X11_WINDOW_MEMBER const char * pszNetStateFlag);
//      virtual bool wm_add_remove_list_raw( WINDOWING_X11_WINDOW_MEMBER Atom atomList, Atom atomFlag, bool bSet);


      virtual ::e_status x11_post_message(MESSAGE & msg);
      virtual ::e_status post_ui_message(const MESSAGE & message);
      //virtual bool x11_process_event(osdisplay_data * pdisplaydata, XEvent * pevent, XGenericEventCookie *cookie);
      //virtual ::e_status set_window_position( WINDOWING_X11_WINDOW_MEMBER const ::zorder & zorder, i32 x, i32 y, i32 cx, i32 cy, ::u32 nFlags);
      virtual ::e_status get_window_rect( WINDOWING_X11_WINDOW_MEMBER RECTANGLE_I32 * prectangle);
      virtual ::e_status get_client_rect(  WINDOWING_X11_WINDOW_MEMBER  RECTANGLE_I32 * prectangle);
      //virtual ::e_status wm_full_screen( WINDOWING_X11_WINDOW_MEMBER const ::rectangle_i32 & rectangle);

      virtual ::e_status x11_store_name(const char * pszName);
      //virtual ::e_status set_foreground_window();
      //virtual ::e_status set_active_window();
      //virtual void wm_toolwindow( WINDOWING_X11_WINDOW_MEMBER bool bToolWindow);
      //virtual void wm_state_hidden( WINDOWING_X11_WINDOW_MEMBER bool bSet);
      //virtual void wm_state_hidden_raw( WINDOWING_X11_WINDOW_MEMBER bool bSet);
      virtual ::e_status mq_remove_window_from_all_queues( WINDOWING_X11_WINDOW_MEMBER );

      virtual void update_screen() override;
      virtual void window_show() override;


   };


   using window_map = map < ::Window, __pointer(window) >;


} // namespace windowing_x11



