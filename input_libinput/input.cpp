// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "input.h"
#include "acme/constant/message.h"
#include <libinput.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h> // for BTN_LEFT



namespace input_libinput
{


   input::input()
   {

      defer_create_synchronization();

   }


   input::~input()
   {


   }



   static int open_restricted(const char *path, int flags, void *user_data)
   {
      int fd = ::open(path, flags);
      return fd < 0 ? -errno : fd;
   }

   static void close_restricted(int fd, void *user_data)
   {
      ::close(fd);
   }

   const static struct libinput_interface interface = {
      .open_restricted = open_restricted,
      .close_restricted = close_restricted,
   };


   void input::__libinput()
   {

      if(__needs_libinput())
      {

         if (m_ptaskLibInput)
         {

            return;

         }

         m_ptaskLibInput = app_fork([this]()
                                    {

                                       ::libinput_event * p;

                                       auto pudev = udev_new();

                                       auto plibinput = libinput_udev_create_context(&interface, NULL, pudev);

                                       libinput_udev_assign_seat(plibinput, "seat0");

                                       while (true)
                                       {

                                          libinput_dispatch(plibinput);

                                          auto p = libinput_get_event(plibinput);

                                          if (!p)
                                          {

                                             break;

                                          }

                                          __handle(p);

                                       }

                                       libinput_unref(plibinput);

                                       udev_unref(pudev);


                                    });

      }
      else
      {

         if (m_ptaskLibInput)
         {

            m_ptaskLibInput->set_finish();

            m_ptaskLibInput.release();

         }

      }

   }





   void input::__handle(::libinput_event * p)
   {
      auto etype = libinput_event_get_type(p);

      if (m_particleaMouseHandler.has_element())
      {

         if (etype == LIBINPUT_EVENT_POINTER_BUTTON)
         {

            __handle_pointer_button(p);

         }

      }
      if (m_particleaMouseHandler.has_element())
      {

         if (etype == LIBINPUT_EVENT_KEYBOARD_KEY)
         {

            __handle_keyboard_key(p);

         }

      }

      libinput_event_destroy(p);

   }

}



   void windowing::__handle_pointer_button(libinput_event * p)
   {

      auto ppointer = libinput_event_get_pointer_event(p);
      auto button = libinput_event_pointer_get_button(ppointer);
      auto state = libinput_event_pointer_get_button_state(ppointer);

      enum_message emessage = e_message_undefined;

      if(button == BTN_LEFT)
      {

         if(state == LIBINPUT_BUTTON_STATE_PRESSED)
         {

            emessage = e_message_left_button_down;

         }
         else if(state == LIBINPUT_BUTTON_STATE_PRESSED)
         {

            emessage = e_message_left_button_up;

         }

      }

      if(emessage != e_message_undefined)
      {

         auto pmouse = __create_new < ::message::mouse >();

         pmouse->m_atom = emessage;

         //pmouse->m_pointAbsolute.x() =

         for(auto & pparticle : m_particleaMouseHandler)
         {

            pparticle->handle(pmouse);

         }

      }


   }


   void windowing::__handle_keyboard_key(libinput_event * p)
   {

      auto pkeyboard = libinput_event_get_keyboard_event(p);
      auto key = libinput_event_keyboard_get_key(pkeyboard);
      auto state = libinput_event_keyboard_get_key_state(pkeyboard);

      enum_message emessage = e_message_undefined;

      //if(button == BTN_LEFT)
      {

         if(state == LIBINPUT_BUTTON_STATE_PRESSED)
         {

            emessage = e_message_key_down;

         }
         else if(state == LIBINPUT_BUTTON_STATE_PRESSED)
         {

            emessage = e_message_key_up;

         }

      }

      if(emessage != e_message_undefined)
      {

         auto pkey = __create_new < ::message::key >();

         pkey->m_atom = emessage;

         //pmouse->m_pointAbsolute.x() =

         for(auto & pparticle : m_particleaKeyboardHandler)
         {

            pparticle->handle(pkey);

         }

      }

   }





bool input::__needs_libinput()
{

   return m_particleaMouseHandler.has_element() || m_particleaKeyboardHandler.has_element();

}


void input::install_mouse_message_handler(::particle * pparticle)
{

   {

      synchronous_lock synchronouslock(this->synchronization());

      m_particleaMouseHandler.add(pparticle);

   }

   __libinput();

}


void input::install_keyboard_message_handler(::particle * pparticle)
{

   {

      synchronous_lock synchronouslock(this->synchronization());

      m_particleaKeyboardHandler.add(pparticle);

   }

   __libinput();

}


void input::erase_mouse_message_handling(::particle * pparticle)
{

   {

      synchronous_lock synchronouslock(this->synchronization());

      m_particleaMouseHandler.erase(pparticle);

   }

   __libinput();

}


void input::erase_keyboard_message_handling(::particle * pparticle)
{

   {

      synchronous_lock synchronouslock(this->synchronization());

      m_particleaKeyboardHandler.erase(pparticle);

   }

   __libinput();

}


} // namespace windowing



