#include "platform.h"
#include "input.h"
#include "acme/constant/user_message.h"
#include "acme/constant/user_key.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task.h"
#include "aura/message/user.h"
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <X11/XKBlib.h>
#include <X11/keysym.h>
#include <poll.h>
#include <errno.h>

namespace input_xinput
{
   input::input() { defer_create_synchronization(); }
   input::~input() { if (m_ptaskInput) m_ptaskInput->set_finish(); }
   ::e_status input::is_keyboard_message_handling_enabled(::user::interaction_base *)
   { return success; }

   void input::__input_task()
   {
      // This connection belongs exclusively to the hook task. Never consume
      // events from the GTK display or hold handler locks while dispatching.
      Display *display = XOpenDisplay(nullptr);
      if (!display) { warning() << "XInput mouse hook: could not open DISPLAY"; return; }
      struct display_guard
      {
         Display *value;
         ~display_guard() { XCloseDisplay(value); }
      } guard{display};
      int opcode, event, error;
      // XI 2.0 suppresses raw events for other clients during a pointer
      // grab. GTK grabs on press, which otherwise hides the release from
      // this connection. XI 2.1 delivers raw events during those grabs.
      int major = 2, minor = 1;
      if (!XQueryExtension(display, "XInputExtension", &opcode, &event, &error)
          || XIQueryVersion(display, &major, &minor) != Success)
      { warning() << "XInput mouse hook requires XInput 2.1"; return; }
      if (major < 2 || (major == 2 && minor < 1))
      { warning() << "XInput 2.1 is required to receive mouse releases during GTK grabs"; return; }
      unsigned char bits[XIMaskLen(XI_LASTEVENT)] = {};
      XISetMask(bits, XI_RawButtonPress);
      XISetMask(bits, XI_RawButtonRelease);
      XISetMask(bits, XI_RawKeyPress);
      XISetMask(bits, XI_RawKeyRelease);
      XIEventMask mask{};
      mask.deviceid = XIAllMasterDevices;
      mask.mask_len = sizeof(bits);
      mask.mask = bits;
      if (XISelectEvents(display, DefaultRootWindow(display), &mask, 1) != Success)
      { warning() << "XInput mouse hook: could not select raw button events"; return; }
      XFlush(display);
      information() << "XInput global input hook started, protocol " << major << "." << minor;
      while (task_get_run())
      {
         if (!XPending(display))
         {
            struct pollfd descriptor{};
            descriptor.fd = ConnectionNumber(display);
            descriptor.events = POLLIN;
            int ready = poll(&descriptor, 1, 100);
            if (ready < 0 && errno == EINTR) continue;
            if (ready < 0 || (descriptor.revents & (POLLERR | POLLHUP | POLLNVAL))) break;
            if (!ready) continue;
         }
         XEvent happening{};
         XNextEvent(display, &happening);
         if (happening.type != GenericEvent || happening.xcookie.extension != opcode) continue;
         if (!XGetEventData(display, &happening.xcookie)) continue;
         int kind = happening.xcookie.evtype;
         int button = 0;
         if (kind == XI_RawButtonPress || kind == XI_RawButtonRelease
             || kind == XI_RawKeyPress || kind == XI_RawKeyRelease)
            button = static_cast<XIRawEvent *>(happening.xcookie.data)->detail;
         XFreeEventData(display, &happening.xcookie);
         if (!button) continue;
         if (kind == XI_RawKeyPress || kind == XI_RawKeyRelease)
         {
            XkbStateRec state{};
            unsigned int group = XkbGetState(display, XkbUseCoreKbd, &state) == Success ? state.group : 0;
            auto symbol = XkbKeycodeToKeysym(display, button, group, 0);
            auto key = create_newø<::message::key>();
            key->m_eusermessage = kind == XI_RawKeyPress ? ::user::e_message_key_down : ::user::e_message_key_up;
            ::user::e_key translated = ::user::e_key_none;
            if (symbol >= XK_a && symbol <= XK_z)
               translated = ::user::e_key_a + (symbol - XK_a);
            else if (symbol >= XK_A && symbol <= XK_Z)
               translated = ::user::e_key_a + (symbol - XK_A);
            else if (symbol >= XK_0 && symbol <= XK_9)
               translated = ::user::e_key_0 + (symbol - XK_0);
            else switch (symbol)
            {
            case XK_Return: case XK_KP_Enter: translated = ::user::e_key_return; break;
            case XK_space: translated = ::user::e_key_space; break;
            case XK_BackSpace: translated = ::user::e_key_back; break;
            case XK_Delete: translated = ::user::e_key_delete; break;
            case XK_Tab: translated = ::user::e_key_tab; break;
            case XK_Escape: translated = ::user::e_key_escape; break;
            case XK_Left: translated = ::user::e_key_left; break;
            case XK_Right: translated = ::user::e_key_right; break;
            case XK_Up: translated = ::user::e_key_up; break;
            case XK_Down: translated = ::user::e_key_down; break;
            case XK_Home: translated = ::user::e_key_home; break;
            case XK_End: translated = ::user::e_key_end; break;
            case XK_Prior: translated = ::user::e_key_page_up; break;
            case XK_Next: translated = ::user::e_key_page_down; break;
            case XK_Shift_L: translated = ::user::e_key_left_shift; break;
            case XK_Shift_R: translated = ::user::e_key_right_shift; break;
            case XK_Control_L: translated = ::user::e_key_left_control; break;
            case XK_Control_R: translated = ::user::e_key_right_control; break;
            case XK_Alt_L: translated = ::user::e_key_left_alt; break;
            case XK_Alt_R: translated = ::user::e_key_right_alt; break;
            case XK_Super_L: translated = ::user::e_key_left_command; break;
            case XK_Super_R: translated = ::user::e_key_right_command; break;
            default: break;
            }
            key->m_ekey = translated;
            ::pointer_array<::particle> handlers;
            {
               synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
               handlers = m_particleaKeyboardHandler;
            }
            for (auto &handler : handlers) handler->handle_message(key);
            continue;
         }
         bool down = kind == XI_RawButtonPress;
         ::user::enum_message message;
         switch (button)
         {
         case 1: message = down ? ::user::e_message_left_button_down : ::user::e_message_left_button_up; break;
         case 2: message = down ? ::user::e_message_middle_button_down : ::user::e_message_middle_button_up; break;
         case 3: message = down ? ::user::e_message_right_button_down : ::user::e_message_right_button_up; break;
         default: continue; // Wheel events are not button-click sounds.
         }
         auto mouse = create_newø<::message::mouse>();
         mouse->m_eusermessage = message;
         ::pointer_array<::particle> handlers;
         {
            synchronous_lock lock(synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
            handlers = m_particleaMouseHandler;
         }
         for (auto &handler : handlers) handler->handle_message(mouse);
      }
   }
}
