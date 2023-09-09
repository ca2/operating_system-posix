//
// Created by camilo on 17/02/2021. 15:16 BRT <3TBS_!!
//
#include "framework.h"
#include "window.h"
#include "windowing_wayland.h"
#include "display.h"
#include "windowing.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/user/user/interaction_impl.h"
#include "aura_posix/x11/display_lock.h"
#include <X11/Xatom.h>


namespace windowing_wayland
{


//   /// must be run in x11 thread (user thread)
//   void window::_wm_add_remove_state_mapped_unlocked(::x11::enum_atom eatomNetWmState, bool bSet)
//   {
//
//      //synchronous_lock synchronouslock(user_synchronization());
//
//      int iStateIndex = eatomNetWmState - ::x11::e_atom_net_wm_state_first;
//
//      if (m_iaNetWmState2[iStateIndex] == (bSet ? 1 : 0))
//      {
//
//         return;
//
//      }
//
//      m_iaNetWmState2[iStateIndex] = (bSet ? 1 : 0);
//
//      auto windowRoot = DefaultRootWindow(Display());
//
//      auto atomFlag = wayland_display()->intern_atom(eatomNetWmState, true);
//
//      auto atomWmNetState = wayland_display()->net_wm_state_atom(true);
//
//      if (_wm_test_list_unlocked(atomWmNetState, atomFlag))
//      {
//
//         if (bSet)
//         {
//
//            return;
//
//         }
//
//      }
//      else
//      {
//
//         if (!bSet)
//         {
//
//            return;
//
//         }
//
//      }
//
//      XClientMessageEvent xclient;
//
//      zero(xclient);
//
//      xclient.type = ClientMessage;
//      xclient.window = Window();
//      xclient.message_type = atomWmNetState;
//      xclient.format = 32;
//      xclient.data.l[0] = bSet ? _NET_WM_STATE_ADD : _NET_WM_STATE_REMOVE;
//      xclient.data.l[1] = atomFlag;
//      xclient.data.l[2] = 0;
//      xclient.data.l[3] = 0;
//      xclient.data.l[4] = 0;
//
//      XSendEvent(Display(), windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, (XEvent *) &xclient);
//      //XSendEvent(Display(), windowRoot, False, 0, (XEvent *) &xclient);
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_add_remove_state_mapped(::x11::enum_atom eatomNetWmState, bool bSet)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::wm_add_remove_state_mapped 1");
//
//      //display_lock displaylock(x11_display()->Display());
//
//      _wm_add_remove_state_mapped_unlocked(eatomNetWmState, bSet);
//
//      windowing_output_debug_string("::wm_add_remove_state_mapped 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::_wm_add_remove_state_unmapped_unlocked(::x11::enum_atom eatomNetWmState, bool bSet)
//   {
//
//      //synchronous_lock synchronouslock(user_synchronization());
//
//      int iStateIndex = eatomNetWmState - ::x11::e_atom_net_wm_state_first;
//
//      if (m_iaNetWmState2[iStateIndex] == (bSet ? 1 : 0))
//      {
//
//         return;
//
//      }
//
//      m_iaNetWmState2[iStateIndex] = (bSet ? 1 : 0);
//
//      int iScreen = DefaultScreen(Display());
//
//      auto windowRoot = RootWindow(Display(), iScreen);
//
//      Atom atomFlag = x11_display()->intern_atom(eatomNetWmState, true);
//
//      Atom atomWmNetState = x11_display()->net_wm_state_atom(true);
//
//      _wm_add_remove_list_unlocked(atomWmNetState, atomFlag, bSet);
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_add_remove_state_unmapped(::x11::enum_atom eatomNetWmState, bool bSet)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::wm_add_remove_state_unmapped 1");
//
//      //display_lock displaylock(x11_display()->Display());
//
//      _wm_add_remove_state_unmapped_unlocked(eatomNetWmState, bSet);
//
//      windowing_output_debug_string("::wm_add_remove_state_unmapped 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::_wm_add_remove_state_unlocked(::x11::enum_atom eatomNetWmState, bool bSet)
//   {
//
//      if (_wm_is_window_visible_unlocked())
//      {
//
//         _wm_add_remove_state_mapped_unlocked(eatomNetWmState, bSet);
//
//      }
//      else
//      {
//
//         _wm_add_remove_state_unmapped_unlocked(eatomNetWmState, bSet);
//
//      }
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_add_remove_state(::x11::enum_atom eatomNetWmState, bool bSet)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::wm_add_remove_state 1");
//
//      //display_lock displaylock(x11_display()->Display());
//
//      _wm_add_remove_state_unlocked(eatomNetWmState, bSet);
//
//      windowing_output_debug_string("::wm_add_remove_state 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::_wm_state_clear_unlocked(bool bSet)
//   {
//
//      //synchronous_lock synchronouslock(user_synchronization());
//
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_above, false);
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_below, false);
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_hidden, false);
//
//      if (_wm_is_window_visible_unlocked())
//      {
//
//         auto atomMaxH = x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_horz, false);
//
//         auto atomMaxP = x11_display()->intern_atom(::x11::e_atom_net_wm_state_maximized_penn, false);
//
//         _mapped_net_state_unlocked(false, x11_display()->m_iScreen, atomMaxH, atomMaxP);
//
//      }
//      else
//      {
//
//         _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_maximized_horz, false);
//         _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_maximized_penn, false);
//
//      }
//
//   }
//
//
////    _wm_add_remove_state_unlocked(net_wm_state_maximized_horz, false);
////    _wm_add_remove_state_unlocked(net_wm_state_maximized_vert, false);
////    _wm_add_remove_state_unlocked(net_wm_state_fullscreen, false);
//
//
//    /// must be run in x11 thread (user thread)
//   void window::_wm_state_below_unlocked(bool bSet)
//   {
//
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_hidden, false);
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_above, false);
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_below, bSet);
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::_wm_state_above_unlocked(bool bSet)
//   {
//
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_hidden, false);
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_below, false);
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_above, bSet);
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::_wm_state_hidden_unlocked(bool bSet)
//   {
//
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_below, false);
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_above, false);
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_hidden, bSet);
//
//   }
//
//
////void wm_state_hidden(oswindow w, bool bSet)
////{
////
////   synchronous_lock synchronouslock(user_synchronization());
////
////   windowing_output_debug_string("::wm_state_above 1");
////
////   //display_lock displaylock(x11_display()->Display());
////
////   wm_state_hidden_raw(bSet);
////
////}
//
//
//    /// must be run in x11 thread (user thread)
//   void window::wm_state_above(bool bSet)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::wm_state_above 1");
//
//      //display_lock displaylock(x11_display()->Display());
//
//      _wm_state_above_unlocked(bSet);
//
//      windowing_output_debug_string("::wm_state_above 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_state_below(bool bSet)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::wm_state_below 1");
//
//      //display_lock displaylock(x11_display()->Display());
//
//      _wm_state_above_unlocked(bSet);
//
//      windowing_output_debug_string("::wm_state_below 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_state_hidden(bool bSet)
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      windowing_output_debug_string("::wm_state_hidden 1");
//
//      //display_lock displaylock(x11_display()->Display());
//
//      _wm_state_hidden_unlocked(bSet);
//
//      windowing_output_debug_string("::wm_state_hidden 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_toolwindow(bool bToolWindow)
//   {
//
//      x11_windowing()->windowing_post([this, bToolWindow]()
//      {
//
//         windowing_output_debug_string("::wm_toolwindow 1");
//
//         synchronous_lock synchronouslock(user_synchronization());
//
//         //display_lock displaylock(x11_display()->Display());
//
//         if (!m_pdisplay)
//         {
//
//            windowing_output_debug_string("::wm_toolwindow 1.1");
//
//            //fflush(stdout);
//
//            return;
//
//         }
//
//         _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_skip_taskbar, bToolWindow);
//
//         windowing_output_debug_string("::wm_toolwindow 2");
//
//      });
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_normalwindow()
//   {
//
//      Atom atomWindowType;
//
//      atomWindowType = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE", False);
//
//      if(atomWindowType != None)
//      {
//
//         Atom atomWindowTypeNormal;
//
//         atomWindowTypeNormal = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", False);
//
//         //atomWindowTypeNormal = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_DIALOG", False);
//
//         if(atomWindowTypeNormal != None)
//         {
//
//            XChangeProperty(Display(), Window(), atomWindowType, XA_ATOM, 32, PropModeReplace, (unsigned char *) &atomWindowTypeNormal, 1);
//
//         }
//
//      }
//
//      windowing_output_debug_string("::windowing_wayland::window::wm_normalwindow");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_hidden_state(bool bHidden)
//   {
//
//      windowing_output_debug_string("::wm_hidden_state 1");
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      //display_lock displaylock(x11_display()->Display());
//
//      if (!m_pdisplay)
//      {
//
//         windowing_output_debug_string("::wm_hidden_state 1.1");
//
//         fflush(stdout);
//
//         return;
//
//      }
//
//      _wm_add_remove_state_unlocked(::x11::e_atom_net_wm_state_skip_taskbar, bHidden);
//
//      windowing_output_debug_string("::wm_hidden_state 2");
//
//   }
//
//
////void wm_arbitrarypositionwindow(oswindow w, bool bArbitraryPositionWindow)
////{
////
////   x11_fork([=]()
////            {
////
////               windowing_output_debug_string("::wm_arbitrarypositionwindow 1");
////
////               synchronous_lock synchronouslock(user_synchronization());
////
////               //display_lock displaylock(x11_display()->Display());
////
////               if(!m_pdisplay)
////               {
////
////                  windowing_output_debug_string("::wm_arbitrarypositionwindow 1.1");
////
////                  fflush(stdout);
////
////                  return;
////
////               }
////
////
////
////               auto windowRoot = DefaultRootWindow(Display());
////
////               Atom atomWindowType = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE", False);
////
////               if(atomWindowType != None)
////               {
////
////                  Atom atomWindowTypeValue;
////
////                  if(bArbitraryPositionWindow)
////                  {
////
////                     atomWindowTypeValue = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_UTILITY", False);
////
////                  }
////                  else
////                  {
////
////                     atomWindowTypeValue = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", False);
////
////                  }
////
////                  if(atomWindowType != None)
////                  {
////
////                     XChangeProperty(Display(), Window(), atomWindowType, XA_ATOM, 32, PropModeReplace, (unsigned char *) &atomWindowTypeValue, 1);
////
////                  }
////
////               }
////
////               windowing_output_debug_string("::wm_arbitrarypositionwindow 2");
////
////            });
////
////}
//
//
//    /// must be run in x11 thread (user thread)
//   void window::wm_desktopwindow(bool bDesktopWindow)
//   {
//
//      windowing_output_debug_string("::wm_desktopwindow 1");
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      //display_lock displaylock(x11_display()->Display());
//
//      if (!m_pdisplay)
//      {
//
//         windowing_output_debug_string("::wm_desktopwindow 1.1");
//
//         fflush(stdout);
//
//         return;
//
//      }
//
//      auto windowRoot = DefaultRootWindow(Display());
//
//      Atom atomWindowType = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE", False);
//
//      if (atomWindowType != None)
//      {
//
//         Atom atomWindowTypeValue;
//
//         if (bDesktopWindow)
//         {
//
//            atomWindowTypeValue = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_DESKTOP", False);
//
//         }
//         else
//         {
//
//            atomWindowTypeValue = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", False);
//
//         }
//
//         if (atomWindowType != None)
//         {
//
//            XChangeProperty(Display(), Window(), atomWindowType, XA_ATOM, 32, PropModeReplace,
//                            (unsigned char *) &atomWindowTypeValue, 1);
//
//         }
//
//      }
//
//      windowing_output_debug_string("::wm_desktopwindow 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_centerwindow(bool bCenterWindow)
//   {
//
//      windowing_output_debug_string("::wm_centerwindow 1");
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      //display_lock displaylock(x11_display()->Display());
//
//      if (!m_pdisplay)
//      {
//
//         windowing_output_debug_string("::wm_centerwindow 1.1");
//
//         fflush(stdout);
//
//         return;
//
//      }
//
//      auto windowRoot = DefaultRootWindow(Display());
//
//      Atom atomWindowType = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE", False);
//
//      if (atomWindowType != None)
//      {
//
//         Atom atomWindowTypeValue;
//
//         if (bCenterWindow)
//         {
//
//            atomWindowTypeValue = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_SPLASH", False);
//
//         }
//         else
//         {
//
//            atomWindowTypeValue = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", False);
//
//         }
//
//         if (atomWindowType != None)
//         {
//
//            XChangeProperty(Display(), Window(), atomWindowType, XA_ATOM, 32, PropModeReplace,
//                            (unsigned char *) &atomWindowTypeValue, 1);
//
//         }
//
//      }
//
//      windowing_output_debug_string("::wm_centerwindow 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_splashwindow(bool bCenterWindow)
//   {
//
//      windowing_output_debug_string("::wm_centerwindow 1");
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      //display_lock displaylock(x11_display()->Display());
//
//      if (!m_pdisplay)
//      {
//
//         windowing_output_debug_string("::wm_centerwindow 1.1");
//
//         fflush(stdout);
//
//         return;
//
//      }
//
//      auto windowRoot = DefaultRootWindow(Display());
//
//      Atom atomWindowType = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE", False);
//
//      if (atomWindowType != None)
//      {
//
//         Atom atomWindowTypeValue;
//
//         if (bCenterWindow)
//         {
//
//            atomWindowTypeValue = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_SPLASH", False);
//
//         }
//         else
//         {
//
//            atomWindowTypeValue = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", False);
//
//         }
//
//         if (atomWindowType != None)
//         {
//
//            XChangeProperty(Display(), Window(), atomWindowType, XA_ATOM, 32, PropModeReplace,
//                            (unsigned char *) &atomWindowTypeValue, 1);
//
//         }
//
//      }
//
//      windowing_output_debug_string("::wm_centerwindow 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_dockwindow( bool bDockWindow)
//   {
//
//      windowing_output_debug_string("::wm_dockwindow 1");
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      //display_lock displaylock(x11_display()->Display());
//
//      if (!m_pdisplay)
//      {
//
//         windowing_output_debug_string("::wm_dockwindow 1.1");
//
//         fflush(stdout);
//
//         return;
//
//      }
//
//
//
//      auto windowRoot = DefaultRootWindow(Display());
//
//      Atom atomWindowType = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE", False);
//
//      if (atomWindowType != None)
//      {
//
//         Atom atomWindowTypeValue;
//
//         if (bDockWindow)
//         {
//
//            atomWindowTypeValue = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_DOCK", False);
//
//         }
//         else
//         {
//
//            atomWindowTypeValue = x11_display()->intern_atom("_NET_WM_WINDOW_TYPE_NORMAL", False);
//
//         }
//
//         if (atomWindowType != None)
//         {
//
//            XChangeProperty(Display(), Window(), atomWindowType, XA_ATOM, 32, PropModeReplace,
//                            (unsigned char *) &atomWindowTypeValue, 1);
//
//         }
//
//      }
//
//      windowing_output_debug_string("::wm_dockwindow 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_nodecorations(int bMap)
//   {
//
//      windowing_output_debug_string("::wm_nodecorations 1");
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      //display_lock displaylock(x11_display()->Display());
//
//      if (!m_pdisplay)
//      {
//
//         return;
//
//      }
//
//      _wm_nodecorations(bMap);
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   void window::_wm_nodecorations(int bMap)
//   {
//
//      //auto windowRoot = DefaultRootWindow(Display());
//
//      bool bCreateAtom = false;
//
//      Atom atomMotifHints = XInternAtom(Display(), "_MOTIF_WM_HINTS", bCreateAtom ? True : False);
//
//      if (atomMotifHints != None)
//      {
//
//         MWMHints hints = {};
//
//         hints.flags = MWM_HINTS_DECORATIONS;
//         hints.decorations = MWM_DECOR_NONE;
//
//         //XChangeProperty(Display(), Window(), atomMotifHints, atomMotifHints, 32, PropModeReplace,
//           //              (unsigned char *) &hints, sizeof(MWMHints) / 4);
//         XChangeProperty(Display(), Window(), atomMotifHints, atomMotifHints, 32, PropModeReplace,
//                       (unsigned char *) &hints, sizeof(hints) / 4);
//
//      }
//
//      if (bMap)
//      {
//
//         XUnmapWindow(Display(), Window());
//
//         XMapWindow(Display(), Window());
//
//      }
//
//      windowing_output_debug_string("::wm_nodecorations 2");
//
//   }
//
//
//   //int_bool IsWindowVisibleRaw(Display *Display(), Window window);
//
//
//   /// must be run in x11 thread (user thread)
//   void window::wm_iconify_window()
//   {
//
//      synchronous_lock synchronouslock(user_synchronization());
//
//      //display_lock displaylock(x11_display()->Display());
//
//      windowing_output_debug_string("::wm_iconify_window 1");
//
//      if (!m_pdisplay)
//      {
//
//         windowing_output_debug_string("::wm_iconify_window 1.1");
//
//         return;
//
//      }
//
//      auto window = Window();
//
//      int iScreen = DefaultScreen(Display());
//
//      if (_wm_is_window_visible_unlocked())
//      {
//
//         XIconifyWindow(Display(), Window(), iScreen);
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
//         unmapped_net_state_raw(x11_display()->intern_atom("_NET_WM_STATE_HIDDEN", False));
//
//      }
//
//      windowing_output_debug_string("::wm_iconify_window 2");
//
//   }
//
//
//   /// must be run in x11 thread (user thread)
//   int_bool window::_wm_is_window_visible_unlocked()
//   {
//
//      //synchronous_lock synchronouslock(user_synchronization());
//
//      XWindowAttributes attr;
//
//      if (!XGetWindowAttributes(Display(), Window(), &attr))
//      {
//
//         return false;
//
//      }
//
//      return attr.map_state == IsViewable;
//
//   }


} // namespace windowing_wayland



