#include "windowing_gtk3/platform.h"
#include "windowing_gtk3/window.h"
#include "aura/user/user/interaction.h"
#include "aura/message/user.h"
#include "acme/platform/system.h"
#include "acme/platform/node.h"
#include <gdk/gdkkeysyms.h>
#include <vector>

class test_node : public ::platform::node
{
public:
   ::string get_call_stack_trace(const ::scoped_string &, ::i32, void *, ::i32) override { return {}; }
};

namespace
{
   class interaction : public ::user::interaction
   {
   public:
      std::vector<::procedure> queued;
      string_array_base events;
      int synchronousSends = 0;
      void user_post(const ::procedure & procedure) override { queued.push_back(procedure); }
      ::lresult send_message(::message::message *) override { ++synchronousSends; return 0; }
      void message_handler(::message::message * message) override
      {
         events.add(message->m_eusermessage == ::user::e_message_key_down ? "down" : "up");
      }
   };
   class window : public ::windowing_gtk3::window
   {
   public:
      interaction * target = nullptr;
      void on_text(const_char_pointer text, character_count length) override
      {
         target->events.add(::string(text, length));
      }
   };
}
int main()
{
   ::platform::system runtime;
   runtime.m_pnode = ::pointer<test_node>(allocate_t{});
   ::pointer<interaction> target(allocate_t{});
   ::pointer<window> native(allocate_t{});
   native->target = target;
   native->m_pacmeuserinteraction = target;
   native->_on_gtk_key_pressed(GDK_KEY_c, 54);
   native->_on_text("text");
   native->_on_gtk_key_released(GDK_KEY_c, 54);
   if (target->synchronousSends || target->events.has_element() || target->queued.size() != 3) return 1;
   for (auto & procedure : target->queued) procedure();
   target->queued.clear();
   bool ordered = target->events.size() == 3 && target->events[0] == "down"
      && target->events[1] == "text" && target->events[2] == "up";
   native->m_pacmeuserinteraction.release();
   native->target = nullptr;
   target->destroy();
   return ordered ? 0 : 2;
}
