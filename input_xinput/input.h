#pragma once
#include "apex/input/input.h"
namespace input_xinput
{
   class CLASS_DECL_INPUT_XINPUT input : virtual public ::input::input
   {
   public:
      input();
      ~input() override;
      void __input_task() override;
      ::e_status is_keyboard_message_handling_enabled(::user::interaction_base *) override;
   };
}
