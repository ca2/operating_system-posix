// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:35 <3TBS, Mummi and bilbo!!
// hi5 contribution...
#include "framework.h"
#include "input.h"
#include "acme/constant/message.h"
#include "aura/message/user.h"
#include "aura/platform/session.h"
#include "aura/user/user/user.h"
#include "aura/windowing/keyboard.h"
#include "aura/windowing/windowing.h"
#include "aura_posix/xkb_input.h"
#include <libinput.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h> // for BTN_LEFT
#include <sys/poll.h>
#include <xkbcommon/xkbcommon.h>


int poll_for_read(int iFd, const class ::time & time)
{

   pollfd pollfda[1]={};

   pollfda[0].fd = iFd;
   pollfda[0].events = POLLIN;

   auto ret = ::poll(pollfda, 1, time.integral_millisecond());

   return ret;

}


namespace input_libinput
{


   input::input()
   {

      defer_create_synchronization();

      m_pxkbkeymap = nullptr;

      m_pxkbstate = nullptr;

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


   const static struct libinput_interface interface =
   {

      .open_restricted = open_restricted,

      .close_restricted = close_restricted,

   };


   void input::__input_task()
   {

      ::libinput_event * p;

      auto pudev = udev_new();

      if(!pudev)
      {

         throw ::exception(error_failed);

      }

      auto plibinput = libinput_udev_create_context(&interface, NULL, pudev);

      if(!plibinput)
      {

         throw ::exception(error_failed);

      }

      auto ret = libinput_udev_assign_seat(plibinput, "seat0");

      if(ret)
      {

         throw ::exception(error_failed);

      }

      auto iFd = libinput_get_fd(plibinput);

      int iPoll = 0;

      while (::task_get_run())
      {

         //information() << "libinput poll for read : " << iPoll;

         iPoll++;

         if(poll_for_read(iFd, 1_s) > 0)
         {

            auto iRet2 = libinput_dispatch(plibinput);

            if(iRet2 == 0)
            {

               while (true)
               {

                  auto p = libinput_get_event(plibinput);

                  if (!p)
                  {

                     break;

                  }

                  __handle(p);

                  ::libinput_event_destroy(p);

               }

            }

         }

      }

      libinput_unref(plibinput);

      udev_unref(pudev);

   }


   bool input::__handle(::libinput_event * p)
   {

      auto etype = ::libinput_event_get_type(p);

      if (m_particleaMouseHandler.has_element())
      {

         if (etype == LIBINPUT_EVENT_POINTER_BUTTON)
         {

            return __handle_pointer_button(p);

         }

      }

      if (m_particleaKeyboardHandler.has_element())
      {

         if (etype == LIBINPUT_EVENT_KEYBOARD_KEY)
         {

            return __handle_keyboard_key(p);

         }

      }

      return false;

   }


   bool input::__handle_pointer_button(libinput_event * p)
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
         else if(state == LIBINPUT_BUTTON_STATE_RELEASED)
         {

            emessage = e_message_left_button_up;

         }

      }
      else if(button == BTN_RIGHT)
      {

         if(state == LIBINPUT_BUTTON_STATE_PRESSED)
         {

            emessage = e_message_right_button_down;

         }
         else if(state == LIBINPUT_BUTTON_STATE_RELEASED)
         {

            emessage = e_message_right_button_up;

         }

      }
      else if(button == BTN_MIDDLE)
      {

         if(state == LIBINPUT_BUTTON_STATE_PRESSED)
         {

            emessage = e_message_middle_button_down;

         }
         else if(state == LIBINPUT_BUTTON_STATE_RELEASED)
         {

            emessage = e_message_middle_button_up;

         }

      }

      if(emessage != e_message_undefined)
      {

         auto pmouse = __create_new < ::message::mouse >();

         pmouse->m_atom = emessage;

         for(auto & pparticle : m_particleaMouseHandler)
         {

            pparticle->handle(pmouse);

         }

      }

      return true;

   }


   bool input::__handle_keyboard_key(libinput_event * p)
   {

      auto pkeyboard = libinput_event_get_keyboard_event(p);

      auto key = libinput_event_keyboard_get_key(pkeyboard);

      information() << "libinput key : " << key;

      auto state = libinput_event_keyboard_get_key_state(pkeyboard);

      information() << "libinput key state : " << (::iptr) state;

      // XBMC_Event event = {};

      //defer_update_xkb_keymap();

      ::user::e_key ekey = ::user::e_key_a;

      auto paurasession = acmesession()->m_paurasession;

      auto puser = paurasession->user();

      auto pwindowing = puser->windowing();

      auto pwindowingkeyboard = pwindowing->keyboard();

      ::pointer < ::xkb_input::xkb_input > pxkbinput = pwindowingkeyboard;

      if(pxkbinput && pxkbinput->m_pxkbkeymap)
      {


         if(m_pxkbkeymap != pxkbinput->m_pxkbkeymap || !m_pxkbstate)
         {

            if(m_pxkbstate)
            {

               xkb_state_unref(m_pxkbstate);

               m_pxkbstate = nullptr;

            }

            m_pxkbkeymap = pxkbinput->m_pxkbkeymap;

            m_pxkbstate = xkb_state_new(m_pxkbkeymap);

         }

         if(m_pxkbstate)
         {

            const uint32_t xkbkey = key + 8;

            const bool pressed = state == LIBINPUT_KEY_STATE_PRESSED;

            xkb_state_update_key(m_pxkbstate, xkbkey, pressed ? XKB_KEY_DOWN : XKB_KEY_UP);

            const xkb_keysym_t keysym = xkb_state_key_get_one_sym(m_pxkbstate, xkbkey);

            if (keysym == XKB_KEY_Return)
            {

               ekey = ::user::e_key_return;

            }
            else if (keysym == XKB_KEY_space)
            {

               ekey = ::user::e_key_space;

            }

         }

      }

      enum_message emessage = e_message_undefined;

      if(state == LIBINPUT_KEY_STATE_PRESSED)
      {

         emessage = e_message_key_down;

      }
      else if(state == LIBINPUT_KEY_STATE_RELEASED)
      {

         emessage = e_message_key_up;

      }

      if(emessage != e_message_undefined)
      {

         auto pkey = __create_new < ::message::key >();

         pkey->m_atom = emessage;

         pkey->m_ekey = ekey;

         for(auto & pparticle : m_particleaKeyboardHandler)
         {

            pparticle->handle(pkey);

         }

      }

      return true;

   }


} // namespace input_libinput



