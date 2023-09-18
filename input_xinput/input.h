// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#pragma once


#include "apex/input/input.h"
#include "aura_posix/x11/input.h"


namespace input_libinput
{


   class CLASS_DECL_INPUT_LIBINPUT input :
      virtual public ::input::input,
      virtual public ::xinput::xinput
   {
   public:


      ::pointer_array<::particle> m_particleaMouseHandler;
      ::pointer_array<::particle> m_particleaKeyboardHandler;


//#ifdef WITH_XI

   int                                             m_xi_opcode = -1;
      //::pointer<particle_array>                        m_pobjectaExtendedEventListener;

//#endif


   input();
      ~input() override;


      void initialize(::particle * pparticle) override;


      virtual void __xinput();
      virtual bool __needs_xinput();


      virtual bool __handle(libinput_event * p);
      virtual bool __handle_pointer_button(libinput_event * p);
      virtual bool __handle_keyboard_key(libinput_event * p);


      void add_mouse_message_handler(::particle * pparticle) override;
      void add_keyboard_message_handler(::particle * pparticle)override;

      void erase_mouse_message_handler(::particle * pparticle) override;
      void erase_keyboard_message_handler(::particle * pparticle) override;


      bool __handle_xinput(void * p, void *cookie) override;
      virtual bool __handle_xinput(XEvent * pevent, XGenericEventCookie *cookie);


   };


} // namespace input



