#include "platform.h"
#include "input.h"
#include "acme/constant/user_message.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task.h"
#include "aura/message/user.h"
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <poll.h>
#include <errno.h>

namespace input_xinput
{
   input::input() { defer_create_synchronization(); }
   input::~input() { if (m_ptaskInput) m_ptaskInput->set_finish(); }
   ::e_status input::is_keyboard_message_handling_enabled(::user::interaction_base *)
   { return error_not_supported; }

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
      int major = 2, minor = 0;
      if (!XQueryExtension(display, "XInputExtension", &opcode, &event, &error)
          || XIQueryVersion(display, &major, &minor) != Success)
      { warning() << "XInput mouse hook requires XInput 2"; return; }
      unsigned char bits[XIMaskLen(XI_LASTEVENT)] = {};
      XISetMask(bits, XI_RawButtonPress);
      XISetMask(bits, XI_RawButtonRelease);
      XIEventMask mask{};
      mask.deviceid = XIAllMasterDevices;
      mask.mask_len = sizeof(bits);
      mask.mask = bits;
      if (XISelectEvents(display, DefaultRootWindow(display), &mask, 1) != Success)
      { warning() << "XInput mouse hook: could not select raw button events"; return; }
      XFlush(display);
      information() << "XInput global mouse hook started";
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
         if (kind == XI_RawButtonPress || kind == XI_RawButtonRelease)
            button = static_cast<XIRawEvent *>(happening.xcookie.data)->detail;
         XFreeEventData(display, &happening.xcookie);
         if (!button) continue;
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
