//
// Created by camilo on 05/03/2021. 16:30 BRT ThomasBS_!!
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "aura_posix/x11/xim_keyboard.h"
// apt install libxkbcommon-dev
// dnf install libxkbcommon-devel
#include <xkbcommon/xkbcommon.h>
// apt install libxkbcommon-x11-dev
// dnf install libxkbcommon-x11-devel
#include <xkbcommon/xkbcommon-x11.h>
//#include <xcb/xkb.h>


namespace windowing_xcb
{

//To Get keymap (evdev...)
//   struct xkb_keymap *keymap;
///* Example RMLVO for Icelandic Dvorak. */
//   struct xkb_rule_names names = {
//      .rules = NULL,
//      .model = "pc105",
//      .layout = "is",
//      .variant = "dvorak",
//      .options = "terminate:ctrl_alt_bksp"
//   };
//
//   keymap = xkb_keymap_new_from_names(ctx, &names,

//To Get keymap (Wayland...)
///* From the wl_keyboard::keymap event. */
//   const char *keymap_string = <...>;
//   struct xkb_keymap *keymap;
//
//   keymap = xkb_keymap_new_from_string(ctx, keymap_string,
//                                       XKB_KEYMAP_FORMAT_TEXT_V1,
//                                       XKB_KEYMAP_COMPILE_NO_FLAGS);
//   if (!keymap) <error>

// to get key state
//   m_pkeystate = xkb_state_new(m_pkeymap);

//   if (!m_pkeystate)
//{

  // return error_failed;

//}
//
//   enum xkb_state_component changed;
//
//   if (<key press>)
//   changed = xkb_state_update_key(state, keycode, XKB_KEY_DOWN);
//   else if (<key release>)
//   changed = xkb_state_update_key(state, keycode, XKB_KEY_UP);
//   The changed return value tells us exactly which parts of the state have changed.
//
//   If it is a key-repeat event, we can ask the keymap what to do with it:
//
//   if (<key repeat> && !xkb_keymap_key_repeats(keymap, keycode))
//   <discard event>
//   On the other hand, if we are an X or Wayland client, the server already does the hard work for us. It notifies us when the device's state changes, and we can simply use what it tells us (the necessary information usually comes in a form of some "state changed" event):
//
//   changed = xkb_state_update_mask(state,
//                                   event->depressed_mods,
//                                   event->latched_mods,
//                                   event->locked_mods,
//                                   event->depressed_layout,
//                                   event->latched_layout,
//                                   event->locked_layout);
//   Now that we have an always-up-to-date xkb_state, we can examine it. For example, we can check whether the Control modifier is active, or whether the Num Lock LED is active:
//
//   if (xkb_state_mod_name_is_active(state, XKB_MOD_NAME_CTRL,
//   XKB_STATE_MODS_EFFECTIVE) > 0)
//   <The Control modifier is active>
//
//   if (xkb_state_led_name_is_active(state, XKB_LED_NAME_NUM) > 0)
//   <The Num Lock LED is active>
//   And that's it! Eventually, we should free the objects we've created:
//
//   xkb_state_unref(state);
//   xkb_keymap_unref(keymap);
//   xkb_context_unref(ctx);
   ::e_status window::defer_update_keyboard_context()
   {

      if(!m_pkeyboarcontext)
      {

         m_pkeyboarcontext = xkb_context_new(XKB_CONTEXT_NO_FLAGS);

         if (!m_pkeyboarcontext)
         {

            return ::error_failed;

         }


      }

      if(m_iKeyboardX11DeviceId == -1)
      {

         m_iKeyboardX11DeviceId = xkb_x11_get_core_keyboard_device_id(xcb_connection());

         if (m_iKeyboardX11DeviceId == -1)
         {

            return error_failed;

         }

      }

      if(!m_pkeymap)
      {

         m_pkeymap = xkb_x11_keymap_new_from_device(
            m_pkeyboarcontext,
            xcb_connection(),
            m_iKeyboardX11DeviceId,
            XKB_KEYMAP_COMPILE_NO_FLAGS);

         if (!m_pkeymap)
         {

            return error_failed;

         }

      }

      if(!m_pkeystate)
      {

         m_pkeystate = xkb_x11_state_new_from_device(
            m_pkeymap,
            xcb_connection(),
            m_iKeyboardX11DeviceId);

         if (!m_pkeystate)
         {

            return error_failed;

         }


      }

      return ::success;

   }


   int window::keycode_to_keysym(xcb_keycode_t code)
   {

      defer_update_keyboard_context();

      xkb_keycode_t keycode = (xkb_keycode_t) code;

      xkb_keysym_t keysym;

      keysym = xkb_state_key_get_one_sym(m_pkeystate, keycode);

#ifdef _DEBUG

      char keysym_name[64];

      xkb_keysym_get_name(keysym, keysym_name, sizeof(keysym_name));

#endif

      return keysym;

   }


//   void window::_on_state_change(xcb_key_press_event_t * pevent)
//   {
////      changed = xkb_state_update_mask(state,
////                                      event->depressed_mods,
////                                      event->latched_mods,
////                                      event->locked_mods,
////                                      event->depressed_layout,
////                                      event->latched_layout,
////                                      event->locked_layout);
//
//   }

   void window::release_keyboard()
   {

      if(m_pkeystate)
      {

         xkb_state_unref(m_pkeystate);

         m_pkeystate = nullptr;

      }

      if(m_pkeymap)
      {

         xkb_keymap_unref(m_pkeymap);

         m_pkeymap = nullptr;

      }

      if(m_pkeyboarcontext)
      {

         xkb_context_unref(m_pkeyboarcontext);

         m_pkeyboarcontext = nullptr;

      }

   }


//   string window::_on_key_down(xcb_keycode_t code)
//   {
//
//      string strText;
//
//      int size = xkb_state_key_get_utf8(m_pkeystate, code, NULL, 0);
//
//      if (size <= 1)
//      {
//
//         auto psz = strText.get_string_buffer(size);
//
//         xkb_state_key_get_utf8(m_pkeystate, code, psz, size);
//
//         strText.release_string_buffer(size);
//
//      }
//
//      return strText;
//
//   }


   string window::_on_key_down(xcb_keycode_t code, ::u16 state, KeySym * pkeysym)
   {

      XKeyPressedEvent event;

      zero(event);

      Display * px11display = xcb_display()->m_pX11Display;

      event.type = KeyPress;
      event.display = px11display;
      event.window = m_window;
      event.state = state;
      event.keycode = code;

      string strText;

      if(!m_pximkeyboard)
      {

         m_pximkeyboard = __new(::xim::keyboard(px11display, m_window));

         m_pximkeyboard->initialize(this);

      }

      strText = m_pximkeyboard->get_key_press_text(&event, pkeysym);

      return strText;

   }


} // namespace windowing_xcb



