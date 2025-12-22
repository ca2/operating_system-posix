// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "windowing_q/window.h"
//#include "kde5_widget.h"
//#include "acme/operating_system/x11/_atom.h"
#include "acme/prototype/geometry2d/rectangle_array.h"
#include "acme_windowing_q6/window.h"
//#include <X11/extensions/sync.h>
#include <QWidget>
//#include <gdk/gdk.h>


//#define HAVE_XSYNC 1
//
//#define _NET_WM_STATE_REMOVE        0    // remove/unset property
//#define _NET_WM_STATE_ADD           1    // add/set property
//#define _NET_WM_STATE_TOGGLE        2    // toggle property
//
//
//#define WINDOWING_X11_WINDOW_MEMBER
////using htask = pthread_t;


namespace windowing_q6
{


   class window;


   class CLASS_DECL_WINDOWING_Q6 window :
      virtual public ::windowing_q::window,
      virtual public ::q6::acme::windowing::window
      //, virtual public ::wayland::micro::window_base
   {
   public:

      //
      // //::int_point m_pointCursor2;
      // //typedef struct {
      // bool moving;
      // bool resizing;
      // enum_window_edge resize_edge;
      // int start_x;
      // int start_y;
      // int start_width;
      // int start_height;
      // int start_window_x;
      // int start_window_y;
      // //::int_size m_sizeOnSize;
      // //} ResizeData;
      //
      // //::int_point                                  m_pointPointer;
      // //XWindowAttributes                            m_attr;
      // //XVisualInfo                                  m_visualinfo;
      // //void *                                       m_pgdkwindow;
      //
      // //bool                                         m_bPendingConfigureRequest;
      // //::pointer<::windowing_kde5::x11data>          m_px11data;
      // //::pointer<::windowing_kde5::display>          m_pwaylanddisplay;
      // //::Window                                     m_parent;
      // //Cursor                                       m_cursorLast;
      // //int                                          m_iXic;
      // //XIC                                          m_xic;
      // //::pointer<::windowing_kde5::display>        m_pdisplay;
      // //::Window                                     m_window;
      // //::Visual                                     m_visual;
      // //int                                          m_iDepth;
      // //int                                        m_iScreen;
      // //::pointer<::windowing::window>        m_pimpl;
      // //::pointer<::message_queue>                 m_pmessagequeue;
      // htask m_htask;
      // //Colormap                                   m_colormap;
      // class ::time m_timeLastMouseMove;
      // //Window                                     m_parent;
      // //::int_rectangle                              m_rect;
      // //string                                       m_strWMClass;
      // //int                                          m_iaNetWmState2[::x11::e_atom_net_wm_state_last-::x11::e_atom_net_wm_state_first+1];
      // //::int_point                                m_pointCursor;
      // //XSyncCounter                                 m_xsynccounterNetWmSync;
      // //XSyncValue                                   m_xsyncvalueNetWmSync;
      // //XSyncValue                                   m_xsyncvalueNetWmSyncPending;
      // ////static oswindow_dataptra *                 s_pdataptra;
      // //static::pointer< ::mutex >                 s_pmutex;
      // //bool                                         m_bNetWmStateHidden;
      // //bool                                         m_bNetWmStateMaximized;
      // //bool                                         m_bNetWmStateFocused;
      // //::comparable_array < Atom >                  m_atomaNetWmState;
      // //XWindowAttributes                            m_xwindowattributes;
      //
      // //static Atom                                s_atomLongType;
      // //static Atom                                s_atomLongStyle;
      // //static Atom                                s_atomLongStyleEx;
      // ::int_rectangle_array m_rectangleaRedraw;
      // ::pointer<::xim::keyboard> m_pximkeyboard;
      // //unsigned long long                                        m_uLastNetWmSyncRequest;
      // ::int_rectangle m_rectangleXShm;
      // //bool                                         m_bFirstConfigure;
      // //bool                                         m_bXShmPutImagePending;
      // //QWidget *m_pqwidget;
      // ::array<QAction *> m_qactiona;
      //
      // // Create a GtkGestureClick for handling button press happenings
      // //GtkGesture *m_pgtkgestureClick;
      // //GtkEventController *m_pgtkeventcontrollerMotion;
      //
      // bool m_bPendingStartMove;
      //

      window();


      //oswindow_data(::user::interaction * puibaseMessageOnlyWindow);
      //oswindow_data(const void * p);
      //oswindow_data(const LPARAM & lparam);
      //oswindow_data(const WPARAM & wparam);
      ~window() override;


   };


} // namespace windowing_q6
