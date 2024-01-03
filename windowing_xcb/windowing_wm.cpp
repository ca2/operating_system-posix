//
// Created by camilo on 17/02/2021. 15:16 BRT <3TBS_!!
//
#include "framework.h"
#include "window.h"
#include "windowing.h"
#include "windowing_xcb.h"
#include "display.h"
#include "aura/user/user/interaction_graphics_thread.h"
#include "aura/user/user/interaction_impl.h"
#include "aura/platform/message_queue.h"
//#include <X11/Xatom.h>
//dnf install xcb-util-wm-devel
#include "acme/operating_system/xcb/nano/display.h"
#include "acme/parallelization/synchronous_lock.h"
#include <xcb/xcb_icccm.h>


namespace windowing_xcb
{

   
   /// must be run in x11 thread (user thread)
   ::e_status window::_mapped_add_net_wm_state(::x11::enum_atom eatomNetWmState)
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto atomFlag = xcb_display()->m_pxcbdisplay->intern_atom(eatomNetWmState, false);

      auto atomWmNetState = xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state, false);

      if (_list_has_atom(atomWmNetState, atomFlag))
      {

         return success_none;

      }

      auto estatus = _send_client_event(atomWmNetState, _NET_WM_STATE_ADD, atomFlag);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_mapped_erase_net_wm_state(::x11::enum_atom eatomNetWmState)
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto atomFlag = xcb_display()->m_pxcbdisplay->intern_atom(eatomNetWmState, false);

      auto atomWmNetState = xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state, false);

      if (!_list_has_atom(atomWmNetState, atomFlag))
      {

          return success_none;

      }

      auto estatus = _send_client_event(atomWmNetState, _NET_WM_STATE_REMOVE, atomFlag);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_add_net_wm_state(::x11::enum_atom eatomNetWmState)
   {

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      auto estatus = _get_window_attributes();

      if(!estatus)
      {

         return estatus;

      }

      if(m_attributes.map_state != XCB_MAP_STATE_UNMAPPED)
      {

         estatus = _mapped_add_net_wm_state(eatomNetWmState);

      }
      else
      {

         estatus = _unmapped_add_net_wm_state(eatomNetWmState);

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_erase_net_wm_state(::x11::enum_atom eatomNetWmState)
   {

      auto estatus = xcb_display()->m_pxcbdisplay->_erase_net_wm_state(m_window, eatomNetWmState);

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_clear_net_wm_state()
   {

      ///synchronous_lock synchronouslock(user_synchronization());

      xcb_display()->m_pxcbdisplay->_clear_net_wm_state(xcb_window());

      auto estatus1 = _erase_net_wm_state(::x11::e_atom_net_wm_state_above);

      auto estatus2 = _erase_net_wm_state(::x11::e_atom_net_wm_state_below);

      auto estatus3 = _erase_net_wm_state(::x11::e_atom_net_wm_state_hidden);

      if(!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;
      
   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_add_net_wm_state_below()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto estatus1 = _erase_net_wm_state_hidden();

      auto estatus2 = _erase_net_wm_state_above();

      auto estatus3 = _add_net_wm_state(::x11::e_atom_net_wm_state_below);

      if(!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;
      
   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_add_net_wm_state_above()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto estatus1 = _erase_net_wm_state_hidden();
      auto estatus2 = _add_net_wm_state(::x11::e_atom_net_wm_state_above);
      auto estatus3 = _erase_net_wm_state_hidden();

      if(!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_add_net_wm_state_hidden()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto estatus1 = _add_net_wm_state(::x11::e_atom_net_wm_state_hidden);
      auto estatus2 = _erase_net_wm_state_above();
      auto estatus3 = _erase_net_wm_state_below();

      if(!estatus1 || !estatus2 || estatus3)
      {

         return error_failed;

      }

      return ::success;

   }




   /// must be run in x11 thread (user thread)
   ::e_status window::_unmapped_add_net_wm_state(::x11::enum_atom eatomNetWmState)
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto atomNetWmState = xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state, false);

      auto atomWmNetState = xcb_display()->m_pxcbdisplay->intern_atom(eatomNetWmState, false);

      auto estatus = _list_add_atom(atomWmNetState, atomWmNetState);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status window::_unmapped_erase_net_wm_state(::x11::enum_atom eatomNetWmState)
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto atomNetWmState = xcb_display()->m_pxcbdisplay->intern_atom(::x11::e_atom_net_wm_state, false);

      auto atomWmNetState = xcb_display()->m_pxcbdisplay->intern_atom(eatomNetWmState, false);

      auto estatus = _list_erase_atom(atomWmNetState, atomWmNetState);

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_erase_net_wm_state_below()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto estatus = _erase_net_wm_state(::x11::e_atom_net_wm_state_below);

      if(!estatus)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_erase_net_wm_state_above()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto estatus = _erase_net_wm_state(::x11::e_atom_net_wm_state_above);

      if(!estatus)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_erase_net_wm_state_hidden()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto estatus = _erase_net_wm_state(::x11::e_atom_net_wm_state_hidden);

      if(!estatus)
      {

         return error_failed;

      }

      return ::success;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_tool_window(bool bToolWindow)
   {

      windowing_output_debug_string("::wm_toolwindow 1");

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      ::e_status estatus;

      if(bToolWindow)
      {

         estatus = _add_net_wm_state(::x11::e_atom_net_wm_state_skip_taskbar);

      }
      else
      {

         estatus = _erase_net_wm_state(::x11::e_atom_net_wm_state_skip_taskbar);

      }

      windowing_output_debug_string("::wm_toolwindow 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;
   
   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_normal_window()
   {

      ::e_status estatus = ::error_failed;

      xcb_atom_t atomWindowType;

      atomWindowType = xcb_display()->m_pxcbdisplay->intern_atom("_NET_WM_WINDOW_TYPE", false);

      if(atomWindowType != XCB_ATOM_NONE)
      {

         xcb_atom_t atomWindowTypeValue;

         atomWindowTypeValue = xcb_display()->m_pxcbdisplay->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", false);

         if(atomWindowTypeValue != XCB_ATOM_NONE)
         {

            estatus = _change_atom_atom(atomWindowType, atomWindowTypeValue);

         }

      }

      if(!estatus)
      {

         informationf("windowing_xcb::window::_set_normal_window failed");

         return estatus;

      }

      informationf("windowing_xcb::window::_set_normal_window succeeded");

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_hidden_state(bool bHidden)
   {

      windowing_output_debug_string("::wm_hidden_state 1");

      information() << "windowing_xcb::window::_set_hidden_state";

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      ::e_status estatus;

      if(bHidden)
      {

         estatus = _add_net_wm_state(::x11::e_atom_net_wm_state_hidden);

      }
      else
      {

         estatus = _erase_net_wm_state(::x11::e_atom_net_wm_state_hidden);

      }

      windowing_output_debug_string("::wm_hidden_state 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_desktop_window(bool bDesktopWindow)
   {

      ::e_status estatus = ::error_failed;

      windowing_output_debug_string("::wm_desktopwindow 1");

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      xcb_atom_t atomWindowType = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE", false);

      if (atomWindowType != XCB_ATOM_NONE)
      {

         xcb_atom_t atomWindowTypeValue;

         if (bDesktopWindow)
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_DESKTOP", false);

         }
         else
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", false);

         }

         if (atomWindowType != XCB_ATOM_NONE)
         {

            estatus = _change_atom_atom(atomWindowType, atomWindowTypeValue);

         }

      }

      windowing_output_debug_string("::wm_desktopwindow 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_center_window(bool bCenterWindow)
   {

      ::e_status estatus = ::error_failed;

      windowing_output_debug_string("::wm_centerwindow 1");

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      xcb_atom_t atomWindowType = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE", false);

      if (atomWindowType != XCB_ATOM_NONE)
      {

         xcb_atom_t atomWindowTypeValue;

         if (bCenterWindow)
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_SPLASH", false);

         }
         else
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", false);

         }

         if (atomWindowType != XCB_ATOM_NONE)
         {

            estatus = _change_atom_atom(atomWindowType, atomWindowTypeValue);

         }

      }

      windowing_output_debug_string("::wm_centerwindow 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;


   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_splash_window(bool bSplashWindow)
   {

      ::e_status estatus = ::error_failed;

      windowing_output_debug_string("::wm_centerwindow 1");

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      xcb_atom_t atomWindowType = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE", false);

      if (atomWindowType != XCB_ATOM_NONE)
      {

         xcb_atom_t atomWindowTypeValue;

         if (bSplashWindow)
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_SPLASH", false);

         }
         else
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", false);

         }

         if (atomWindowType != XCB_ATOM_NONE)
         {

            estatus = _change_atom_atom(atomWindowType, atomWindowTypeValue);

         }

      }

      windowing_output_debug_string("::wm_centerwindow 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_dock_window( bool bDockWindow)
   {

      ::e_status estatus = ::error_failed;

      windowing_output_debug_string("::wm_dockwindow 1");

      //synchronous_lock synchronouslock(user_synchronization());

      //display_lock displaylock(xcb_display());

      xcb_atom_t atomWindowType = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE", false);

      if (atomWindowType != XCB_ATOM_NONE)
      {

         xcb_atom_t atomWindowTypeValue;

         if (bDockWindow)
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_DOCK", false);

         }
         else
         {

            atomWindowTypeValue = xcb_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", false);

         }

         if (atomWindowType != XCB_ATOM_NONE)
         {

            estatus = _change_atom_atom(atomWindowType, atomWindowTypeValue);

         }

      }

      windowing_output_debug_string("::wm_dockwindow 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_nodecorations(int bMap)
   {

      ::e_status estatus = ::error_failed;

      xcb_atom_t atomMotifHints = xcb_display()->intern_atom("_MOTIF_WM_HINTS", true);

      if (atomMotifHints != XCB_ATOM_NONE)
      {

         MWMHints hints = {};

         hints.flags = MWM_HINTS_DECORATIONS;
         hints.decorations = MWM_DECOR_NONE;

         //XChangeProperty(xcb_connection(), xcb_window(), atomMotifHints, atomMotifHints, 32, PropModeReplace,
         //              (unsigned char *) &hints, sizeof(MWMHints) / 4);
         estatus = _change_property(atomMotifHints, atomMotifHints, XCB_PROP_MODE_REPLACE, 32, sizeof(hints) / 4, &hints);

      }

      if (bMap)
      {

         xcb_unmap_window(xcb_connection(), xcb_window());

         xcb_map_window(xcb_connection(), xcb_window());

      }

      windowing_output_debug_string("::wm_nodecorations 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   ::e_status window::_set_iconify_window()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      information() << "_set_iconify_window";

      windowing_output_debug_string("_set_iconify_window 1");

//      _set_keyboard_focus(XCB_NONE);

//      ::u32 uaState[] = {XCB_ICCCM_WM_STATE_ICONIC, XCB_NONE};
//
//      auto estatus  = _change_property(
//         xcb_display()->intern_atom("WM_STATE", true),
//         xcb_display()->intern_atom("WM_STATE", true),
//         XCB_PROP_MODE_REPLACE,
//         32,
//         2,
//         uaState
//         );
//
//      if(estatus.succeeded())
//      {
//
//         information() << "WM_STATE property set to iconic";
//
//      }
//      else
//      {
//
//         information() << "Failed to set WM_STATE property to iconic";
//
//      }

      //_set_hidden_state(true);

      ::e_status estatus = ::success;

//      _unmap_window();
//
//
//      {
//
//         xcb_client_message_event_t event{};
//
//         event.response_type = XCB_CLIENT_MESSAGE;
//         event.format = 32;
//         event.sequence = 0;
//         event.window = m_window;
//         event.type = xcb_display()->intern_atom("_NET_WM_STATE", true);
//         event.data.data32[0] = xcb_display()->intern_atom("_NET_WM_STATE_ADD", true);
//         event.data.data32[1] = xcb_display()->intern_atom("_NET_WM_STATE_HIDDEN", true);
//         event.data.data32[2] = 0;
//         event.data.data32[3] = 0;
//         event.data.data32[4] = 0;
//
//         auto cookie = xcb_send_event(xcb_connection(), 0, xcb_windowing()->m_pdisplay->m_pxcbdisplay->m_windowRoot,
//                                      XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT,
//                                      (const char *) &event);
//
//         auto estatus1 = xcb_display()->_request_check(cookie);
//
//         if (estatus1.succeeded())
//         {
//
//            information() << "Sent _NET_WM_STATE event with Add Hidden";
//
//         }
//         else
//         {
//
//            information() << "Failed to send _NET_WM_STATE event with Add Hidden";
//
//         }
//
//         if(estatus1.failed())
//         {
//
//            estatus = estatus1;
//
//         }
//
//      }

      {

         xcb_client_message_event_t event{};

         event.response_type = XCB_CLIENT_MESSAGE;
         event.format = 32;
         event.sequence = 0;
         event.window = m_window;
         event.type = xcb_display()->intern_atom("WM_CHANGE_STATE", true);
         event.data.data32[0] = XCB_ICCCM_WM_STATE_ICONIC;
         event.data.data32[1] = 0;
         event.data.data32[2] = 0;
         event.data.data32[3] = 0;
         event.data.data32[4] = 0;

         auto cookie = xcb_send_event(xcb_connection(), 0, xcb_windowing()->m_pdisplay->m_pxcbdisplay->m_windowRoot,
                                      XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY | XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT,
                                      (const char *) &event);

         auto estatus2 = xcb_display()->_request_check(cookie);

         if (estatus2.succeeded())
         {

            information() << "Sent WM_CHANGE_STATE event with iconic";

         }
         else
         {

            information() << "Failed to send WM_CHANGE_STATE event with iconic";

         }

         if(estatus2.failed())
         {

            estatus = ::minimum(estatus.m_eenum, estatus2.m_eenum);

         }

      }


      xcb_flush(xcb_connection());

//      if (IsWindowVisibleRaw())
//      {
//
//         estatus = _mapped_net_state_raw(1, xcb_display()->intern_atom("_NET_WM_STATE_HIDDEN", false), 0);
//
//      }
//      else
//      {
//
//         if (m_puserinteractionimpl->m_puserinteraction->const_layout().design().display() != ::e_display_iconic)
//         {
//
//            m_puserinteractionimpl->m_puserinteraction->display(::e_display_iconic);
//
//         }
//
//         estatus = _unmapped_net_state_raw(xcb_display()->intern_atom("_NET_WM_STATE_HIDDEN", false));
//
//      }

//      xcb_get_property_cookie_t cookie = xcb_icccm_get_wm_hints_unchecked(xcb_connection(), m_window);
//      xcb_icccm_wm_hints_t hints{};
//      if (xcb_icccm_get_wm_hints_reply(xcb_connection(), cookie, &hints, nullptr))
//      {
//         //if (state & Qt::WindowMinimized)
//            xcb_icccm_wm_hints_set_iconic(&hints);
//         //else
//           // xcb_icccm_wm_hints_set_normal(&hints);
//         xcb_icccm_set_wm_hints(xcb_connection(), m_window, &hints);
//      }

      windowing_output_debug_string("::wm_iconify_window 2");

      if(!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   /// must be run in x11 thread (user thread)
   int_bool window::IsWindowVisibleRaw()
   {

      //synchronous_lock synchronouslock(user_synchronization());

      auto estatus = _get_window_attributes();

      if(!estatus)
      {

         return false;

      }

      return m_attributes.map_state == XCB_MAP_STATE_VIEWABLE;

   }


} // namespace windowing_xcb




