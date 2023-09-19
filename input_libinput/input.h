// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "apex/input/input.h"


namespace input_libinput
{


   class CLASS_DECL_INPUT_LIBINPUT input :
      virtual public ::input::input
   {
   public:




      input();
      ~input() override;


      //void initialize(::particle * pparticle) override;



      void __input_task() override;


      virtual bool __handle(libinput_event * p);
      virtual bool __handle_pointer_button(libinput_event * p);
      virtual bool __handle_keyboard_key(libinput_event * p);


//      void add_mouse_message_handler(::particle * pparticle) override;
//      void add_keyboard_message_handler(::particle * pparticle)override;
//
//
//      void erase_mouse_message_handler(::particle * pparticle) override;
//      void erase_keyboard_message_handler(::particle * pparticle) override;


   };


} // namespace input



